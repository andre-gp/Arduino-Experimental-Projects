#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <DHT.h>

#define FILE_NAME "log.txt"

File fileLog;

/* SD Card Reader Pins */
int CS = 10;

/* LED Pin */
int ledPin =  7;

/* Sensor Pin*/
int sensorPin = 2;

DHT sensor(sensorPin, DHT11);


void setup() {
	Serial.begin(9600);
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
		
		fileLog.println(" = = = NEW SESSION = = =");
		
		fileLog.close();
	}
	else
	{
		Serial.println("Couldn't open file!");
	}
	
	digitalWrite(ledPin, LOW);
}

void printTime()
{
	unsigned long currentMillis = millis();
	unsigned long seconds = currentMillis / 1000;
	unsigned long minutes = seconds / 60;
	unsigned long hours = minutes / 60;
	unsigned long days = hours / 24;
	
	fileLog.print(hours);
	fileLog.print("::");
	fileLog.print(minutes);
	fileLog.print("::");
	fileLog.print(seconds);
	fileLog.print("::");
	fileLog.print(currentMillis);
}

void loop() {
	delay(5000);
	
	digitalWrite(ledPin, HIGH);
	
	float humidity = sensor.readHumidity();
	float temp = sensor.readTemperature();
	
	fileLog = SD.open(FILE_NAME, FILE_WRITE);
	
	if(fileLog)
	{
		Serial.println("Opened the file successfully!");
		
		printTime();
		
		fileLog.print(" | ");
		fileLog.print(" Temperature: ");
		fileLog.print(temp);
		
		fileLog.print(" | ");
		fileLog.print(" Humidity: ");
		fileLog.println(humidity);
		
		fileLog.close();
	}
	else
	{
		Serial.println("Couldn't open file!");
	}
	
	digitalWrite(ledPin, LOW);
}

