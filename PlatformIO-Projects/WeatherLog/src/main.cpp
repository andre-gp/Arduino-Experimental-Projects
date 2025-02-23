#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <DHT.h>
#include <RTClib.h>

#define FILE_NAME "log.txt"

/* SD Card Reader Pins */
int CS = 10;

/* LED Pin */
int ledPin =  7;

/* Sensor Pin*/
int sensorPin = 2;

File fileLog;

DHT sensor(sensorPin, DHT11);

RTC_DS1307 rtc;

void setup() {
	Serial.begin(9600);

	while(!rtc.begin())
	{
	    Serial.println("RTC was not found.");
	}

	if(!rtc.isrunning())
	{
	    Serial.println("ERROR: RTC is not running!");
		Serial.println("Adjusting to time of compilation.");
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}

	pinMode(CS, OUTPUT);
	pinMode(ledPin, OUTPUT);
	
	sensor.begin();
	
	digitalWrite(ledPin, HIGH);
	
	if(SD.begin())
	{
		Serial.println("SD Card was initialized!");
	}
	else
	{
		Serial.println("Failed to initialize SD Card.");
	}
	
	fileLog = SD.open(FILE_NAME, FILE_WRITE);
	
	if(fileLog)
	{
		Serial.println("Opened the file successfully!");
		
		fileLog.println(" = = = NEW SESSION (André Pacheco) = = =");
		
		fileLog.close();
	}
	else
	{
		Serial.println("Couldn't open file!");
	}
	
	digitalWrite(ledPin, LOW);
}

void printNum(uint16_t digit)
{
    if(digit < 10)
		fileLog.print(0);

	fileLog.print(digit);
}

void printTime()
{
	// unsigned long currentMillis = millis();
	// unsigned long seconds = currentMillis / 1000;
	// unsigned long minutes = seconds / 60;
	// unsigned long hours = minutes / 60;
	// unsigned long days = hours / 24;

	// currentMillis %= 1000;
	// seconds %= 60;
	// minutes %= 60;
	// hours %= 24;

	DateTime time = rtc.now();

	printNum(time.day());
	fileLog.print("/");
	printNum(time.month());
	fileLog.print("/");
	printNum(time.year());

	fileLog.print(" | ");

	printNum(time.hour());
	fileLog.print(":");
	printNum(time.minute());
	fileLog.print(":");
	printNum(time.second());
}

void loop() {
	delay(5000);
	
	float humidity = sensor.readHumidity();
	float temp = sensor.readTemperature();
	
	fileLog = SD.open(FILE_NAME, FILE_WRITE);
	
	if(fileLog)
	{
		digitalWrite(ledPin, HIGH);

		Serial.println("Opened the file successfully!");
		
		printTime();
		
		fileLog.print(" | ");
		fileLog.print(temp);
		
		fileLog.print(" | ");
		fileLog.println(humidity);
		
		fileLog.close();
	}
	else
	{
		Serial.println("Couldn't open file!");
	}
	
	digitalWrite(ledPin, LOW);
}

