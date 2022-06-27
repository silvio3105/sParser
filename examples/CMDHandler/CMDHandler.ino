
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


// OBJECTS
SBuff Buffer(SBUFF_SIZE);
sParser CMDHandler(';', ',');


// FUNCTIONS
void parseCMD()
{
	char *cmdSet = nullptr;
	char *cmdParam = nullptr;

	Serial.print(F(">> Input command set(s): "));
	Serial.print(Buffer.buffer());
	Serial.print(F(" | # sets: "));
	Serial.println(CMDHandler.count(Buffer.buffer(), CMD_SET));
	Serial.print('\n');

	// FIRST COMMAND SET
	cmdSet = CMDHandler.find(Buffer.buffer(), CMD_SET);
	while (cmdSet != nullptr)
	{
		Serial.print(F("Command Set: "));
		Serial.print(cmdSet);
		Serial.print(F(" | # params: "));
		Serial.println(CMDHandler.count(cmdSet, CMD_PARAM));
		Serial.print(F("Command params: "));

		// FIRST COMMAND PARAM
		cmdParam = CMDHandler.find(cmdSet, CMD_PARAM);
		while (cmdParam != nullptr)
		{
			Serial.print(cmdParam);
			Serial.print(' ');

			// NEXT COMMAND PARAM
			cmdParam = CMDHandler.find(nullptr, CMD_PARAM);
		}

		Serial.println('\n');

		// NEXT COMMAND SET
		cmdSet = CMDHandler.find(nullptr, CMD_SET);
	}
}

void setup()
{
	delay(100);

	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	Serial.begin(115200);

	if (Buffer.isFail())
	{
		Serial.println("Serial buffer memory allocation fail!");
		while (true) delay(1000);
	}
	Serial.println(F("-->> COMMAND HANDLER EXAMPLE:\nSupported format is: \"cmd1,param1,...,paramN;...;cmdN,...,paramN\"\nStart typing commands now!\n"));
}

void loop()
{
	while (Serial.available()) Buffer.buff(Serial.read(), &parseCMD, true);

	delay(1); // SLOWS DOWN
}