
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
//#define DEBUG // UNCOMMENT THIS LINE TO PRINT COMMAND SETS AND PARAMS DURING BENCHMARK TEST


// OBJECTS
SBuff Buffer(SBUFF_SIZE);
sParser CMDHandler(';', ',');


// VARIABLES
char *stringCopy 								= 									nullptr;
uint16_t iterations 							= 									100;


// FUNCTIONS
void benchmark()
{
	Serial.print(F("\nBENCHMARK START!\nInput commands: "));
	Serial.println(Buffer.buffer());

	#ifdef DEBUG
		Serial.println(F("\n----- BENCHMARK OUTPUT"));
	#endif

	// INIT STUFF
	char *cmdSet = nullptr;
	char *cmdParam = nullptr;		
	uint32_t startMillis = 0;
	uint32_t sumMillis = 0;
	uint8_t setCount = CMDHandler.count(Buffer.buffer(), CMD_SET);

	// MAKE A COPY OF SERIAL BUFFER
	memcpy(stringCopy, Buffer.buffer(), Buffer.buffed());

	for (uint16_t i = 0; i < iterations; i++)
	{
		#ifdef DEBUG
			Serial.print("Iteration: ");
			Serial.println(i + 1, DEC);
		#endif

		startMillis = millis();

		// FIRST COMMAND SET
		cmdSet = CMDHandler.find(stringCopy, CMD_SET);
		while (cmdSet != nullptr)
		{
			#ifdef DEBUG
				Serial.print(">> Command Set: ");
				Serial.println(cmdSet);
			#endif

			// FIRST COMMAND PARAM
			cmdParam = CMDHandler.find(cmdSet, CMD_PARAM);

			#ifdef DEBUG
				Serial.print(">>>> Command Params: ");
			#endif

			// ALL OTHER COMMAND PARAMS
			while (cmdParam != nullptr)
			{
				#ifdef DEBUG
					Serial.print(cmdParam);
					Serial.print(' ');
				#endif

				cmdParam = CMDHandler.find(nullptr, CMD_PARAM);
			}

			#ifdef DEBUG
				Serial.print('\n');
			#endif

			// NEXT COMMAND SET
			cmdSet = CMDHandler.find(nullptr, CMD_SET);
		}

		sumMillis += millis() - startMillis;
		memcpy(stringCopy, Buffer.buffer(), Buffer.size());	

		#ifdef DEBUG
			Serial.print('\n');
		#endif	
	}

	memset(stringCopy, '\0', Buffer.buffed());

	Serial.print(F("BENCHMARK END!\nIt takes "));
	Serial.print(sumMillis, DEC);
	Serial.print(F("ms for "));
	Serial.print(iterations, DEC);
	Serial.print(F(" iterations. That is "));
	Serial.print(sumMillis / (float)iterations, 3);
	Serial.println(F("ms on average for one iteration."));

	#ifdef DEBUG
		Serial.println(F("BUT, SINCE BENCHMARK OUTPUT IS TURNED ON, RESULT IS MUCH GREATER. TURN OFF BENCMARK OUTPUT TO GET REAL RESULTS."));
	#endif

	Serial.print(F("Number of command sets: "));
	Serial.print(setCount, DEC);
	Serial.print('\n');
}

void setup()
{
	delay(100);

	Serial.begin(115200);

	if (Buffer.isFail()) Serial.println(F("Serial buffer memory allocation fail!"));
	else
	{
		stringCopy = new char [Buffer.size()];
		if (stringCopy == nullptr)
		{
			Serial.println(F("Copy buffer memory allocation fail!"));
			while (true) delay(1000);
		}

		memset(stringCopy, '\0', Buffer.size());
	}	
	Serial.println(F("-->> COMMAND HANDLER - BENCHMARK EXAMPLE:\nSupported format is:\"cmd1,param1,..,paramN;..;cmdN,..,paramN\"\nType commands now!\n"));
}

void loop()
{
	while (Serial.available()) Buffer.buff(Serial.read(), &benchmark, true);

	delay(1); // SLOWS DOWN
}