#include <Arduino.h>

#include<SPI.h>
#include<LoRa.h>

#define RELAY_PIN 4
#define LORA_NSS 17
#define LORA_RESET 14
#define LORA_DIO0 26

void setup()
{
	Serial.begin(9600);
	
	pinMode(RELAY_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, LOW);

	LoRa.setPins(LORA_NSS,LORA_RESET,LORA_DIO0);
	if(!LoRa.begin(433E6))
	{
		Serial.println("LoRa failed ");
		while(1);
	}
	Serial.println("LoRa Intializinng !");
}

void loop()
{
	int packetSize = LoRa.parsePacket();
	if(packetSize)
	{
		String Msg = "";
		while(LoRa.available())
		{
			Msg +=(char)LoRa.read();
		}
		Serial.print("Received: ");
		Serial.println(Msg);

		int status = Msg.toInt();
		if(status == 0)
		{
			digitalWrite(RELAY_PIN, LOW);
		}
		else if(status == 1)
		digitalWrite(RELAY_PIN, HIGH);
	}
	delay(2000);
}

