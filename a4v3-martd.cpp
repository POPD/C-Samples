/*============================================================================================
************************************| ID BLOCK |**********************************************
==============================================================================================

Due Date:           October, 31, 2014
Software Designer:  Daric Martin-Lavoie
Course:             420-306-AB ALGORITHM DESIGN section 00001
Deliverable:	    Assignment 4  Version 3


Description:

=============================================================================================
********************************| PRELIMINARIES |********************************************
============================================================================================*/


#include <iostream>
#include <stdio.h>    //for formating color and fonts
#include <windows.h>  //for using windows things that c++ cant do
#include <iomanip>    //for setw function to format output

// for speech, not fully function yet, hopefully for version 4.
#define _ATL_APARTMENT_THREADED
#include <atlbase.h>
extern CComModule _Module;
#include <atlcom.h>
//#include <stdafx.h>   // for text to speech
//#include <sapi.h>    // for text to speech 

using namespace std;




/*===========================================================================================
*******************************|        COLOR       |****************************************
============================================================================================*/
//Time to have some fun 

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGREY 7
#define DARKGREY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

#define BACKGROUND_BLUE      0x0010 // background color contains blue.
#define BACKGROUND_GREEN     0x0020 // background color contains green.
#define BACKGROUND_RED       0x0040 // background color contains red.
#define BACKGROUND_INTENSITY 0x0080 // background color is intensified.
#pragma warning (disable: 4996)


/*===========================================================================================
*******************************|   TEXT TO SPEECH  |*****************************************
============================================================================================*/
/* may be implemented by version 4 or 5 hopefully,
   it really depending on other courses work load, ambition is high for this.
   c++ dose no support text to speech, speech is platform Dependant. 
   i will try to get this working on win7 for slandered desktops.
   i plan on doing dome SAPI programming using windows MS Speech API.
*/

/*===========================================================================================
*******************************|       ENUMS         |***************************************
============================================================================================*/

enum StateType { white, word, num, dble, expnt };
enum CharType  { whsp, lett, expo, digit, plus1, minus1, point, qoute, endstr };

/*===========================================================================================
*******************************| FUNTION PROTOTYPE   |***************************************
============================================================================================*/

void whiteState(); 
void numState();
void dbleState();
void expntState();
void wordState();

void whiteToWord();
void whiteToNum();
void whiteToFloat();

void wordToWhite();

void numTofloat();
void numToWhit();
void numToExpnt();

void floatToWhite();
void floatToExpnt();

void expntToWhite();

CharType getType(char);

/*===========================================================================================
*******************************|   GLOBAL VARIBLES   |***************************************
============================================================================================*/

const int LMAX = 200;		//maximum number of chars per line 
const int NLINES = 10;		//maximum number of lines
const int NDBLE = 10;		//maximum number of doubles
const int NINT = 10;		//maximum number of integers
const int WMAX = 10;		//maximum number of characters in a word
int length;
char ch;
char line[LMAX];
CharType  chtype;
StateType state;
int wlen;
int k;
int len;

/*===========================================================================================
*******************************| MAIN BLOCK BEGINS |*****************************************
============================================================================================*/

int main()
{
	//save original default setting in-case i mess up colors 
	//sets handlers for formating data from stream to buffers or something like that?
	//magic dont touch, lol
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO *ConsoleInfo = new CONSOLE_SCREEN_BUFFER_INFO();
	GetConsoleScreenBufferInfo(hConsoleHandle, ConsoleInfo);
	WORD OriginalColors = ConsoleInfo->wAttributes;


	//array of text lines i.e. the input data
	char tline[NLINES][LMAX] = {
		"  first 123 and now second -.1234 and you're needing this 123.456 plus one of these +123. too",
		"  ellen's favourites are 123.654E-2 eg exponent-form which can also be -54321E-03 or this +432e2",
		" I'll prefer numbers like fmt1-dec +.1234567e+05 or fmt2-dec -765.3245 or fmt1-int -837465 or ",
		" even fmt2-int -19283746 which make us think of each state's behaviour for +3 or even .3471e7 states ",
	};

	
	// ARRAYS FOR RESULTS
	// double mydbls [NDBLE];
	// int myints [NINT];
	// int mywords[WMAX];

	/****************************************************************************
	PRINT OUT THE RAW TEXT LINES
	****************************************************************************/
	cout << "TEXT DATA LINES:" << endl << endl;
	cout << endl;
	for (int j = 0; j<NLINES; j++)				//display name strings & matching weights
	{
		strcpy(line, tline[j]);
		length = strlen(tline[j]);
		cout << line << endl;				// first via 1 command 
		for (int z = 0; z < length; z++)	// secondly, in a char-by-char loop
		{
			ch = line[z];
			printf("%c", ch);
		}
		printf("\n");
	}
	
	system("PAUSE");
	cout << endl;
	state = white;
	chtype = whsp;

	for (int j = 0; j<NLINES; j++)			 // display name strings & matching weights
	{ 
		strcpy(line, tline[j]);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),90); 
		cout << line << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

		len = strlen(tline[j]);

		if (len == 0) // break when empty line 
		{
			break;
		}
		else
		{

			k = 0;
			ch = line[k];
			chtype = getType(ch);

			while (k < len)
			{
				switch (state)
				{
				case white: whiteState(); break;
				case word: wordState(); break;
				case num: numState(); break;
				case dble: dbleState(); break;
				case expnt: expntState(); break;
				}
			} cout << endl << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
			system("PAUSE");
		}
	}
	cout << endl << endl;
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	cout << "CYAN = WORD" << endl; 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "YELLOW = NUMBER" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "RED = FLOAT" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	cout << "MAGENTA = exponent " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	return 0;
}

void whiteState()
{
	while (state == white && k < len)
	{
		switch (chtype)
		{
			case expo:
			case word:  
			whiteToWord(); break;
			case digit:
			case plus1:
			case minus1:
			whiteToNum(); break;
			case point:
			whiteToFloat(); break;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			default: printf("%c", ch); break;
			

		}
		ch = line[++k];
		chtype = getType(ch);
	}
}

void numState()
{
	while (state == num && k < len)
	{
		switch (chtype)
		{
		  case expo: numToExpnt(); break;
		  case point: numTofloat(); break;
		  case whsp: numToWhit(); break;
		  default:
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			printf("%c", ch);
		}

		ch = line[++k];
		chtype = getType(ch);
		
	}
}

void dbleState()
{
	while (state == dble && k < len)
	{
		switch (chtype)
		{
		  case expo: floatToExpnt(); break;
		  case whsp: floatToWhite(); break;
		  default: 
			   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
			   printf("%c", ch);
		}

		ch = line[++k];
		chtype = getType(ch);
	}
}

void expntState()
{
	while (state == expnt && k < len)
	{

		switch (chtype)
		{
		  case whsp: expntToWhite(); break;
		  default: 
			  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); 
			  printf("%c", ch);
		}
		ch = line[++k];
		chtype = getType(ch);
	}
}

void wordState()
{
	while (state == word && k < len)
	{

		switch (chtype)
		{
		case whsp: wordToWhite(); break;

		default: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
			     printf("%c", ch);
		}
		ch = line[++k];
		chtype = getType(ch);
	}
}

CharType getType(char ch)
{
	CharType type;
	type = whsp;

	if (isspace(ch))
	{
		type = whsp;
	}
	else if (isalpha(ch) || ch == '\'' )
	{
		if (toupper(ch) == 'E')
		{
			type = expo;
		}
		else
		{
			type = lett;
		}
	}
	else if (isdigit(ch))
	{
		type = digit;
	}
	else switch (ch)
	{
	   case '+': type = plus1; break;
	   case '-': type = minus1; break;
	   case '.': type = point; break;
	}
	return type;
}

// { white, word, num, dble, expnt };

void whiteToWord()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d", state);
	state = word;
	printf("-%d\n", state);
	
}
void whiteToNum()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d", state);
	state = num;
	printf("-%d\n", state);
}
void whiteToFloat()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d", state);
	state = dble;
	printf("-%d\n", state);
}

void wordToWhite()
{
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d", state);
	state = white;
	printf("-%d", state);
}

void numTofloat()
{
	if ( ch == '.' && line[k-1] == '+' || line[k-1] == '-')
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("%c", ch);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ST%d", state);
		state = dble;
		printf("-%d\n", state);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		printf("\n%c", ch);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ST%d", state);
		state = dble;
		printf("-%d\n", state);
	}
}
void numToWhit()
{
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d", state);
	state = white;
	printf("-%d", state);
}
void numToExpnt()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d", state);
	state = expnt;
	printf("-%d\n", state);
}

void floatToWhite()
{
	if (ch == ' ' && line[k - 1] == '.')
	{
		printf("%c", ch);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ST%d", state);
		state = white;
		printf("-%d", state);
	}
	else
	{  
		printf("\n%c", ch); 
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
		printf("ST%d", state);
		state = white;
		printf("-%d", state);

	}
	
}
void floatToExpnt()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d",state);
	state = expnt;
	printf("-%d\n", state);
}

void expntToWhite()
{
	printf("\n%c", ch);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	printf("ST%d", state);
	state = white;
	printf("-%d", state);
}