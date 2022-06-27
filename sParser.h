
/*

	STRING PARSER FUNCTIONS
	LAST UPDATE: 27. 6. 2022.
	CREDITS: silvio3105 (c)

*/

#ifndef _SPARSER_H_
#define _SPARSER_H_

// LIBRARIES
#include 																			<stdint.h>


// CODES
#define SPARSER_DEL_0																0
#define SPARSER_DEL_1																1


// CLASS
class sParser
{
public:

	// ----- CONSTRUCTOR & DECONSTRUCTOR
	sParser(const char, const char);
	~sParser();

	// ----- FUNCTIONS
	/*
		Finds string set in given C string and returns address of first character in set
		@params:
			- input: Pointer to the C string; Pass nullptr/NULL to continue with new address from last call 
			- type: Selects delimiter
		@return:
			- Pointer to first char in string set
	*/
	char *find(const char*, uint8_t const);

	/*
		Counts number of string sets in C string from @input
		@params:
			- input: Pointer to the C string
			- type: Selects delimiter
		@return:
			- Number of string sets in given C string
	*/
	uint8_t count(const char*, uint8_t const) const;

	/*
		Counts number of string sets in C strings from "next[type]"
		@params:
			- type: Selects delimiter
		@return:
			- Number of string sets in given C string
	*/
	uint8_t count(uint8_t const) const;

	/*
		Returns address of next selected string set in find function
		@params:
			- type: Selects delimiter
		@return:
			- Address of next string set in given C string
	*/
	char *getNext(uint8_t const) const;

	/*
		Returns address of last string set found in find function
		@params:
			- type: Selects delimiter
		@return:
			- Address of last string set in given C string
	*/
	char *getLast(uint8_t const) const;

private:

	// ----- FUNCTIONS
	/*
		Counts number of string parts in given C string
		@params:
			- input: Pointer to the C string
			- type: Selects delimiter
		@return:
			- Number of found parts in given C string
	*/
	uint8_t countParts(const char*, uint8_t const) const;

	// ----- VARIABLES
	char *next[2];
	char *last[2];
	char *constrain[2];
	char delimiter[2][2];
};

#endif // _SPARSER_H_