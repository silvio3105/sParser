
/*

	SIMPLE STRING PARSER EXAMPLE SKETCH
	LAST UPDATE: 27. 6. 2022.
	CREDITS: silvio3105 (c)

	THIS EXAMPLE REQUIRES "SerialBuffer" LIBRARY
	TESTED ON STM32F103C8 AND ARDUINO BOARDS.
	SUPPORTED FORMAT IS - "cmd1,param1,...,paramN;...;cmdN,...,paramN"
	RECOMMENDED DELIMITER FOR COMMAND SETS IS ";"
	RECOMMENDED DELIMITER FOR COMMAND PARAMS IS ","

	EXAMPLE COMMANDS:
	"rtc_set,31,5,2020,10,10,35;eeprom_save;led_13,1"
		- "rtc_set,31,5,2020,10,10,35" IS COMMAND SET OF SEVEN COMMAND PARAMS
		- "eeprom_save" IS COMMAND (SET) WITH ONE COMMAND PARAM
		- "led_13,1" IS COMMAND SET WITH TWO COMMAND PARAMS

*/


// LIBRARIES
#include 																			<sParser.h>
#include 																			<SerialBuffer.h>


// SETTINGS 
#define SBUFF_SIZE 																	256
#define LED_PIN 																	13 // BUILT-IN LED


// OBJECTS
SBuff Buffer(SBUFF_SIZE);
sParser CMDHandler(';', ',');


// VARIABLES
uint8_t LEDStatus 									=								0; // 0 = OFF ; 1 = ON; 2 = LOOP BLINK (0) ; 3 = LOOP BLINK (OFF)
uint16_t blinkDuration 								=								100;


// FUNCTIONS
void exeCMD(const char *set)
{
	/*
		THIRD WAY TO CHECK NUMBER OF PARAMS: TAKE NUMBER OF PARAMS BEFORE GETTING FIRST PARAM(THE COMMAND)
		uint8_t paramCount = CMDHandler.count(set, CMD_PARAM) - 1; // - 1 BECAUSE THE FIRST PARAM IS ALWAYS THE COMMAND
	*/

	char *cmdParam = CMDHandler.find(set, CMD_PARAM);

	if (!strcmp(cmdParam, "led"))
	{
		// ONE WAY TO CHECK IF COMMAND HAS PARAM(S) - BEFORE GETTING PARAM(S) == BETTER WAY
		if (!CMDHandler.count(CMDHandler.getNext(CMD_PARAM), CMD_PARAM))
		{
			// OUTPUT ERROR MESSAGE
			// Serial.println("->> Command led: Expected one parameter!");
			// OR			
			Serial.print(F("->> Command led: Current LED status is "));
			Serial.println(digitalRead(LED_PIN));
			return;		
		}

		cmdParam = CMDHandler.find(nullptr, CMD_PARAM);
		LEDStatus = 0;
		uint8_t status = atoi(cmdParam);

		digitalWrite(LED_PIN, status);
		Serial.print(F("->> Command led: LED Status is "));
		Serial.println(status, DEC);
	}
	else if (!strcmp(cmdParam, "loop"))
	{
		cmdParam = CMDHandler.find(nullptr, CMD_PARAM);

		// SECOND WAY TO CHECK IF COMMAND HAS PARAM(S) - AFTER GETTING EVERY PARAM
		if (cmdParam == nullptr)
		{
			Serial.println(F("->> Command loop: Expected one parameter!"));
			return;
		}	

		uint8_t status = atoi(cmdParam);
		if (status)
		{
			LEDStatus = 2;
			digitalWrite(LED_PIN, HIGH);
			Serial.println(F("->> Command loop: LED Blink Loop is on!"));
			delay(blinkDuration);
		}
		else
		{
			LEDStatus = 0;
			digitalWrite(LED_PIN, LOW);
			Serial.println(F("->> Command loop: LED Blink Loop is off!"));			
		}	
	}
	else if (!strcmp(cmdParam, "duration")) // SOLVES THE PROBLEM WITH "led"
	{
		if (!CMDHandler.count(CMDHandler.getNext(CMD_PARAM), CMD_PARAM))
		{
			Serial.print(F("->> Command duration: Current blink duration is "));
			Serial.print(blinkDuration, DEC);
			Serial.println("ms");
			return;		
		}

		cmdParam = CMDHandler.find(nullptr, CMD_PARAM);
		blinkDuration = atoi(cmdParam);

		Serial.print(F("->> Command duration: New blink duration is "));	
		Serial.print(blinkDuration, DEC);
		Serial.println("ms");	
	}
	else if (!strcmp(cmdParam, "help")) Serial.println(F("------ HELP ------\n-> led [0/1] - Turns off/on LED on pin 13\n-> loop [0/1] - Stops/starts blink loop with LED on pin 13\n-> duration [X] - Changes duration of LED loop blink. Recommended values is 50-500ms\n"));
	else
	{
		Serial.print(F("->> Command "));
		Serial.print(cmdParam);
		Serial.println(F(" doesn't exist!"));
	}
}

void parseCMD()
{
	char *cmdSet = nullptr;

	// FIRST COMMAND SET
	cmdSet = CMDHandler.find(Buffer.buffer(), CMD_SET);
	while (cmdSet != nullptr)
	{
		exeCMD(cmdSet);		

		// NEXT COMMAND SET
		cmdSet = CMDHandler.find(nullptr, CMD_SET);
	}
}

void setup()
{
	delay(100);

	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, LOW);
	Serial.begin(115200);

	if (Buffer.isFail()) Serial.println(F("Serial buffer memory allocation fail!"));
	Serial.println(F("-->> COMMAND HANDLER - LED BLINK EXAMPLE:\nType help for list of the commands.\n"));
}

void loop()
{
	while (Serial.available()) Buffer.buff(Serial.read(), &parseCMD, true);

	if (LEDStatus == 2)
	{
		LEDStatus = 3;
		digitalWrite(LED_PIN, LOW);
		delay(blinkDuration - 10);
	}
	else if (LEDStatus == 3)
	{
		LEDStatus = 2;
		digitalWrite(LED_PIN, HIGH);
		delay(blinkDuration);		
	}
	else delay(1); // SLOWS DOWN
}