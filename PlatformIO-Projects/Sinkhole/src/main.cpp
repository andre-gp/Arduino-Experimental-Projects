#include <Arduino.h>
#include "set"
#include "map"

// ESP-32 and net headers
#include "WiFi.h"
#include "AsyncUDP.h"

// Custom headers
#include "dns.h"
#include "blockedDomains.h"

std::set<String> blockedDomainsSet;

// WiFi Connection
const char* ssid = "ssid";
const char* password = "pw";

// Cloudfare DNS
const IPAddress DNS_SERVER(1, 1, 1, 1);
const int DNS_PORT = 53;

// Using UDP for the DNS
AsyncUDP clientDnsUdp;
AsyncUDP cloudflareDnsUdp;



// map used for looking up info of client that made the original request to esp32
std::map<uint16_t, ClientInfo> dnsRequests;

void onReceiveDnsQuery(AsyncUDPPacket packet)
{    
    int index = 0;
    bool needDot = false; // Add dots between labels
    
    char fullDomainName[253]; // 
    Serial.println("Received DNS query!");
    
    for (int i = sizeof(DNSHeader); i < packet.length(); i++)
    {
      uint8_t length = packet.data()[i];
      
      if(length == 0) // End of domain name
      {
          break;
      }
      
      if(needDot) // Add dot if we've gone past the first label
      {
          fullDomainName[index++] = '.';
      }
      
      for (int j = 0; j < length && (i + 1 + j) < packet.length(); j++)
      {
        fullDomainName[index++] = (char)packet.data()[i + 1 + j];
      }
      
      i += length;
      
      needDot = true;
      
    }
    
    fullDomainName[index] = '\0';
    
    int dotsSeen = 0; // track number of dots

    // run through the string backwards
    while (--index >= 0)
    {
      if (fullDomainName[index] == '.')
      {
        dotsSeen++;
        if (dotsSeen == 2)
        {
          index += 1;
          break;
        }
      }
    }

    // <second_level_domain>.<TLD>
    char *primaryDomain = fullDomainName + index;

    // copy response into a buffer that's 16 bytes bigger (will write the answer section to this buffer)
    int position = packet.length();
    uint8_t response[position + 16];
    memcpy(response, packet.data(), position);
    DNSHeader *responseHeader = (DNSHeader *)response;
    
    if(blockedDomainsSet.count(String(primaryDomain)))
    {
      responseHeader->flags = htons(ntohs(responseHeader->flags) | 0x8000); // sets the QR bit to 1
      responseHeader->ancount = htons(1);

      // name
      response[position++] = 0xC0;
      response[position++] = 0x0C;

      // record: A record
      response[position++] = 0x00;
      response[position++] = 0x01;

      // class: set to standard
      response[position++] = 0x00;
      response[position++] = 0x01;

      // ttl: set to standard
      response[position++] = 0x00;
      response[position++] = 0x00;
      response[position++] = 0x00;
      response[position++] = 0x3C; // 60s

      // Data length (4 bytes for IPv4)
      response[position++] = 0x00;
      response[position++] = 0x04;

      // IP address (0.0.0.0)
      response[position++] = 0x00;
      response[position++] = 0x00;
      response[position++] = 0x00;
      response[position++] = 0x00;

      // send response
      packet.write(response, position);

      return;
    }
    
    // if domain not in blocklist, save client info in map for later lookup
  ClientInfo client = { packet.remoteIP(), packet.remotePort() };
  dnsRequests[ntohs(responseHeader->id)] = client;

  // query cloudflare to ask about the domain
  cloudflareDnsUdp.writeTo(packet.data(), packet.length(), DNS_SERVER, DNS_PORT);
}

void onReceiveCloudflareResponse(AsyncUDPPacket packet)
{
  Serial.println("Received cloudflare response!");
  DNSHeader* responseHeader = (DNSHeader*) packet.data();
  uint16_t id = ntohs(responseHeader->id);

  // to be safe, just check that the request is still in the map
  if (dnsRequests.count(id)) {
    // if it is, respond to the client with the packet we received
    ClientInfo& client = dnsRequests[id];
    clientDnsUdp.writeTo(packet.data(), packet.length(), client.addr, client.port);

    // remove request from map
    dnsRequests.erase(id);
  }
}


void setup() {
  Serial.begin(9600);
  Serial.println("Teste");
  
  for (int i = 0; i < BLOCKED_DOMAINS_COUNT; i++)
  {
    blockedDomainsSet.insert(String(BLOCKED_DOMAINS[i]));
  }
  

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while(WiFi.waitForConnectResult() != WL_CONNECTED)
  {
      Serial.println("Failed to connect to wifi! Trying again!");
      delay(1000);
  }
  
  // Listen requests on port 53
  if(clientDnsUdp.listen(DNS_PORT))
  {
      Serial.println("Started Listening.");
      clientDnsUdp.onPacket(onReceiveDnsQuery);
  }
  
  // Call onCloudFlareResponse anytime cloudflare returns a response
  if(cloudflareDnsUdp.connect(DNS_SERVER, DNS_PORT))
  {
      Serial.println("Connected to 8.8.8.8");
      cloudflareDnsUdp.onPacket(onReceiveCloudflareResponse);
  }
  
  Serial.println(WiFi.localIP());
}

void loop() {
}
