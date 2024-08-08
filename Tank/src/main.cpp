#include <Arduino.h>

#include<SPI.h>
#include<LoRA.h>

#define RADAR_SENSOR_PIN 35
#define LORA_NSS 17
#define LORA_RESET 14
#define LORA_DIO0 26

void setup()
{
	Serial.begin(9600);
	pinMode(RADAR_SENSOR_PIN, INPUT);
	LoRa.setPins(LORA_NSS, LORA_RESET,LORA_DIO0);

	if(!LoRa.begin(433E6))
	{
		Serial.println("LoRa failed");
		while(1);
	}
	Serial.println("LoRa Intializing ...");
}

void loop()
{
	int waterlevel = analogRead(RADAR_SENSOR_PIN);
	Serial.print("Water Level : ");
	Serial.print(waterlevel);
	
	bool isTankFull =(waterlevel > 2000);
	LoRa.beginPacket();
	LoRa.print(isTankFull ? 0 : 1);
	LoRa.endPacket();
	
	delay(2000);
}