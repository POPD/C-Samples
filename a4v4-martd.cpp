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
enum CharType  { whsp, lett, expo, digit, plus1, minus1, point, qout, endstr};

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

void numToWhit();
void numTofloat();
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
int mywords[LMAX];
int myints[NINT];
double mydoubles[NDBLE];
int indexW = 0;
int indexI = 0;
int indexD = 0;
int highten = 0;
double mydbles[NDBLE];
int length;
char ch;
char line[LMAX];
CharType  chtype;
StateType state;
int wlen;
int k;
int len;
int wordlen = 0;
int ival;
double fval;
int sign;
int esign;

int   power;
int expt;


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
    printf("TEXT DATA LINES:\n\n\n\n");

    state = white;
    chtype = whsp;
    sign = 1;

    for (int j = 0; j<NLINES; j++)			 // display name strings & matching weights
    {
        strcpy(line, tline[j]);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 90);
        printf("%s\n", line);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

        len = strlen(tline[j]);

        if (len == 0) // break when empty line move to next line
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
            } 

            switch (state)
            {
             case white: whiteState(); break;
             case word: wordToWhite(); break;
             case num: numToWhit(); break;
             case dble: floatToWhite(); break;
             case expnt: expntToWhite(); break;
            }

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            system("PAUSE");
            printf("\n\n");
        }// end of else


    }//end of for
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

/*===========================================================================================
*******************************|  MAIN BLOCK ENDS  |*****************************************
============================================================================================*/



/*===========================================================================================
*******************************|    WHITE STATE    |*****************************************
============================================================================================*/
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

/*===========================================================================================
*******************************|   WORD  STATE   |*******************************************
============================================================================================*/
void wordState()
{
    while (state == word && k < len)
    {

        switch (chtype)
        {
        case whsp:   wordToWhite(); break;
        case endstr: wordToWhite(); break;

        default: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
            printf("%c", ch);
        }
        ch = line[++k];
        wordlen = wordlen + 1;
        chtype = getType(ch);
    }
}

/*===========================================================================================
*******************************|   NUNBER  STATE   |*****************************************
============================================================================================*/
void numState()
{
    while (state == num && k < len)
    {
        switch (chtype)
        {
         case expo: numToExpnt(); break;
         case point: numTofloat(); break;
         case whsp: numToWhit(); break;
         case endstr: numToWhit(); break;
         default:
             SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
             printf("%c", ch);

            if (isdigit(line[k]))
                ival = (ival * 10) + (ch - '0');
    
        }
        ch = line[++k];
        chtype = getType(ch);
    }
}
/*===========================================================================================
*******************************|  DOUBLE   STATE   |*****************************************
============================================================================================*/

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

            fval = (fval * 10) + (ch - '0');
            power = power * 10;
        }
        
        ch = line[++k];
        chtype = getType(ch);
    }
}

/*===========================================================================================
*******************************|  EXPONENT STATE   |*****************************************
============================================================================================*/
void expntState()
{
    while (state == expnt && k < len)
    {
        switch (chtype)
        {
         
         //case endstr : 
         case whsp: expntToWhite(); break;
         default:
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            printf("%c", ch);

            if (toupper(ch) == 'E')
            {
                esign = 1;
            }
            else if (ch == '-')
            {
                esign = -1;
            }
            
             if (isdigit(ch))
                 expt = (expt * 10) + (ch - '0');
        }
        ch = line[++k];
        chtype = getType(ch);
    }
}

/*===========================================================================================
*******************************| GET CHAR TYPE FUNCTION |************************************
============================================================================================*/

CharType getType(char ch)
{
    CharType type;
    type = whsp;

    if (isspace(ch))
    {
        type = whsp;
    }
    else if (isalpha(ch) || ch == '\'')
    {
        if(toupper(ch) == 'E')
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
     case '+':   type = plus1;  sign =  1; break;
     case '-':   type = minus1; sign = -1; break;
     case '.':   type = point; break;
     case '\'':  type = qout;  break;
     case '\0':  type = endstr;  break;
    }

    return type;
}


// { white, word, num, dble, expnt };

/*===========================================================================================*
---------------------------------------------------------------------------------------------
*******************************| STATE TRANSITIONS BLOCK |***********************************
---------------------------------------------------------------------------------------------
============================================================================================*/


void whiteToWord()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);

    printf(" ST%d",state);
    state = word;
    printf("-%d\n", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%c", ch);
    wordlen = 1;
}
void whiteToNum()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf(" ST%d", state);
    state = num;
    printf("-%d\n", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("%c", ch);
    
    //true ival = 0; flase ival = ch-'0'
    ival = (ch == '-' || ch == '+') ? 0 : ch - '0';
}
void whiteToFloat()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf(" ST%d", state);
    state = dble;
    printf("-%d\n", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    printf("%c", ch);

    fval = 0, power = 1;
}

void wordToWhite()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("ST%d", state);
    state = white;
    printf("-%d", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%c", ch);
    printf("Word Length is %d\n", wordlen);
}

void numTofloat()
{
    if (ch == '.' && line[k - 1] == '+' || line[k - 1] == '-')
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("ST%d", state);
        state = dble;
        printf("-%d\n", state);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("%c", ch);
    }
    else
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        printf("ST%d", state);
        state = dble;
        printf("-%d\n", state);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        printf("%c", ch);
    }

    fval = ival, power = 1;
}
void numToWhit()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("ST%d", state);
    state = white;
    printf("-%d", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("%c", ch);
    printf(" Integer Value :%d\n", (ival * sign));

    ival = 0;
}
void numToExpnt()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("ST%d", state);
    state = expnt;
    printf("-%d\n", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("%c", ch);

    fval = ival;
    ival = 0;
}

void floatToWhite()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("ST%d", state);
    state = white;
    printf("-%d", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
    fval = fval/power * sign;
    printf("Double Value:%.7g\n", fval);
    mydbles[indexD++] = fval;

    power = 1, sign = 1, fval = 0;
}
void floatToExpnt()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("ST%d", state);
    state = expnt;
    printf("-%d\n", state);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("%c", ch);

    fval = fval / power * sign;
    power = 1;
}

void expntToWhite()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("ST%d", state);
    state = white;
    printf("-%d", state);

    //printf("fval is %f ", fval);
    if (esign == 1)
    while (expt-- > 0)
    {
        fval *= 10;
        //printf("fval *= is %f", fval);
    }

    if (esign == -1)
    while (expt-- > 0)
    {
        fval/= 10 * esign;
        //printf("fval /= 10 is %f", fval);
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("Double value:%.7g\n", fval);

    fval = 0, expt = 0, esign = 1;
}