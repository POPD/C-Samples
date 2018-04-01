/*============================================================================================
************************************| ID BLOCK |**********************************************
==============================================================================================

Due Date:           November, 17, 2014
Software Designer:  Daric Martin-Lavoie 
Course:             420-306-AB ALGORITHM DESIGN section 00001
Deliverable:	    Assignment 4  Version 5 finale product version


Description: Program Reads string lines, program has 5 state handlers that reflect 
             the current character type being read (white,word,integer,double,exponent).
             program then calculates statistical results for length of words 
             and their frequency, integer values and double values. Program then 
             displays the collected data in separate tables according to 
             there character type.

=============================================================================================
********************************| PRELIMINARIES |********************************************
============================================================================================*/


#include <iostream>
#include <stdio.h>    //for formating color and fonts
#include <windows.h>  //for using windows headers, 
#include <iomanip>    //for setw function to format output
using namespace std;

#pragma warning (disable: 4996) //disable 
#pragma warning (disable: 4309) //disable

/*===========================================================================================
*******************************|        COLOR       |****************************************
============================================================================================*/
// set colors
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

/*===========================================================================================
*******************************|       ENUMS         |***************************************
============================================================================================*/
//State is used to determines how to handle next character
enum StateType { white, word, num, dble, expnt };

//CharType is used to determine what kind of character we are dealing with
enum CharType  { whsp, lett, expo, digit, plus1, minus1, point, qout, endstr };

/*===========================================================================================
*******************************| FUNTION PROTOTYPE   |***************************************
============================================================================================*/

//------[ State Handler Functions ]------\\

void whiteState();      //indicts current state is White
void wordState();       //indicts current state is Word
void numState();        //indicts current state is Number
void dbleState();       //indicts current state is Double
void expntState();      //indicts current state is Exponent

CharType getType(char); //function gets the current character type

//------[ White state Transitions ]-------\\

void whiteToWord(); 
void whiteToNum();
void whiteToFloat();

//-------[ Word State Transitions ]--------\\

void wordToWhite();

//-------[ Number State Transitions ]-------\\

void numToWhit();
void numTofloat();
void numToExpnt();

//--------[ Float State Transitions ]--------\\

void floatToWhite();
void floatToExpnt();

//-------[ Exponent State Transitions ]-------\\

void expntToWhite();

//--------[ Table Out-put Functions ]----------\\

void fill(char, int);
void wordTable(int[], char[], char[], char[], int, int);
void intagerTable(int[], char[], char[], char[], int, int);
void doubelTable(double[], char[], char[], char[], int, int);


/*===========================================================================================
*********************************|   CONSTANTS  |********************************************
============================================================================================*/

const int LMAX = 200;  //maximum number of chars per line 
const int NLINES = 10; //maximum number of lines
const int NDBLE = 10;  //maximum number of doubles
const int NINT = 10;   //maximum number of integers
const int WMAX = 10;   //maximum number of characters in a word


/*===========================================================================================
*******************************|   GLOBAL VARIBLES   |***************************************
============================================================================================*/


int len;               //length of current line being read
char ch;               //current character being processed
char line[LMAX];       //current line being processed
CharType  chtype;      //stores the current character type
StateType state;       //current state of the application
int k;                 //subscript indicating present position within the current line
int wordlen = 0;       //length of current word
int ival;              //variable  stores the converted integers
double fval;           //variable  stores the converted floats
int sign;              //used to determine if numerical value is positive or negative
int esign;             //used to determine if exponent is positive or negative
int power;             //used to determine decimal point position
int expt;              //power of 10,used to convert numerical value from scientific notation


//--------[ Arrays for results ]----------\\

int mywords[LMAX];         //used to store words
int myints[NINT];          //used to store integers
double mydoubles[NDBLE];   //used to store doubles


//------[Index counter for result arrays ]------\\

int indexW = 0;   // counter for word array
int indexI = 0;   // counter for integer array
int indexD = 0;   // counter for double array


/*===========================================================================================
*******************************| MAIN BLOCK BEGINS |*****************************************
============================================================================================*/

int main()
{
    //sets console handle manipulation to change console color
    //set out put handle 
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //change console screen buffer info 
    CONSOLE_SCREEN_BUFFER_INFO *ConsoleInfo = new CONSOLE_SCREEN_BUFFER_INFO();
    // uses out put handle and console buffer info to set changes in console colors
    GetConsoleScreenBufferInfo(hConsoleHandle, ConsoleInfo);
    WORD OriginalColors = ConsoleInfo->wAttributes;


    //array of text lines i.e. the input data
    char tline[NLINES][LMAX] = {
        "  first 123		and then -.1234 but you'll need 123.456		 and 7e-4 plus one like +321. all quite avant-",
        "garde   whereas ellen's true favourites are 123.654E-2	exponent-form which can also be -54321E-03 or this -.9E+5",
        "We'll prefer items like			fmt1-decimal		+.1234567e+05 or fmt2-dec -765.3245 or fmt1-int -837465 and vice-",
        "versa or even format2-integers -19283746   making one think of each state's behaviour for 9 or even 3471e-7 states ",
    };

  //sets defaults state and character type before state and character type operations 
  //assume we are in white state and character type is white space, number values is positive

    state = white; //default state is white, 
    chtype = whsp; //default character type is white space
    sign = 1;      //default number sign is positive

    printf("TEXT DATA LINES:\n\n\n");
    for (int j = 0; j<NLINES; j++)			 
    {
        strcpy(line, tline[j]); //line gets current character line
        len = strlen(tline[j]); //len gets the length of current character line

        if (len > 0)printf("\n%s\n", tline[j]); //print out non empty character line

        if (len == 0) //is the line empty? if so skip it and move to next line
        {
            continue; //skips the remaining lines of code for current loop
        }
        else
        {

            k = 0;                //counter starts at 0
            ch = line[k];         //ch gets char of line index k
            chtype = getType(ch); //chtype gets the char type of ch

            //Loops through the state Handler depending on the current State until the end of line
            while (k < len)
            {
                switch (state) //verify currents states 
                {
                    case white: whiteState(); break;
                    case word: wordState(); break;
                    case num: numState(); break;
                    case dble: dbleState(); break;
                    case expnt: expntState(); break;
                }
            }

            if (line[len] == '-' && state == word)//is state word and hyphenated?
            {
                system("pause"); 
                continue;  //stay in word state and go to next line
            }
            else//end of the line, perform a current state to white transition
            {
                switch (state)
                {
                    case white: whiteState(); break;
                    case word: wordToWhite(); break;
                    case num: numToWhit(); break;
                    case dble: floatToWhite(); break;
                    case expnt: expntToWhite(); break;
                }
            }
        
        }// end of else

    }//end of for loop line processing

    printf("\n\n");
    printf("Program prints out word length frequency's and the Values of integers and doubles  in a table\n");
    //change console stream out put color, 2 = GREEN
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    printf("\n\nANALYSIS OF THE RESULTS\n-------------------------------------------");


    //prints Word table, contains resulting frequencies of word length
    wordTable(mywords, "WORD RESULTS", "WORD LENGTH", "FREQUENCY", 24, indexW );

    //prints Integer table, contains resulting integer values 
    intagerTable(myints, "INTEGER RESULTS", "INDEX", "VALUE", 34, indexI);

    //prints Double table, contains resulting doubles values 
    doubelTable(mydoubles, "DOUBLE RESULTS", "INDEX", "VALUE", 34, indexD);

    printf("\n\n\n");
    return 0;// ends program 
}

/*===========================================================================================
*******************************|  MAIN BLOCK ENDS  |*****************************************
============================================================================================*/



/*===========================================================================================
*******************************|    WHITE STATE    |*****************************************
============================================================================================*
|																							|
|                    Default state, changes when any non white space				        |
|             has been found, or changes back when whit space been found					|
|                          																	|
|-----------------------------------------------------------------------------------------*/
void whiteState()
{
    //Loop until the state is no longer white or we reach the end of line
    while (state == white && k < len)
    {
        //CharType handler for transitions to other state
        switch (chtype)
        {
            // transition conditions are self explanatory
            case expo:
            case word:
            whiteToWord(); break;
            case digit:
            case plus1:
            case minus1:
            whiteToNum(); break;
            case point:
            whiteToFloat(); break;
            default: ; // all other types stay in current state

        }
        //If there is no transition, get the next character & CharType
        ch = line[++k]; //gets next character
        chtype = getType(ch); // gets char type

    }
}

/*===========================================================================================
*******************************|   WORD  STATE   |*******************************************
============================================================================================*
|																							|
|          Handel's word state, stay in word while alphabetical values are found		    |
|                   in the current line, change state at end of line 	                    |
|					       or when whitespace encountered								    |
|                                                                                           |
|-----------------------------------------------------------------------------------------*/
void wordState()
{
    //Loops until the state is no longer word or till end of line reached
    while (state == word && k < len)
    {
        //check certain CharTypes that triggers transitions to a different states
        switch (chtype)
        {   
            //transition conditions are self explanatory
            case whsp:   wordToWhite(); break;
            case endstr: wordToWhite(); break;
            default: ; // all other types stay in current state
        }

        /*  If no transition occurs, get next character & its CharType
            & increment the word length by 1 
        */	ch = line[++k];
            wordlen = wordlen + 1;
            chtype = getType(ch);

    }
}

/*===========================================================================================
*******************************|   NUNBER  STATE   |*****************************************
============================================================================================*
|																							|
|   Handel's num state, 3 state transition possible, integer to white, integer to double,   |
|           integer to exponent. stay in num while numerical values are found		        |
|              in the current line, change to white state  at end of line 	                |
|		 or when whitespace encountered or to double state when a point is found	        |
|                         change exponent state when a e is found                           |
|																							|
|-----------------------------------------------------------------------------------------*/
void numState()
{ 
    //Loop until the state is no longer num or end of line is reached
    while (state == num && k < len)
    {   
        //check certain CharTypes that triggers transitions to a different states
        switch (chtype)
        {   
            //transition conditions are self explanatory
            case expo: numToExpnt(); break;
            case point: numTofloat(); break;//decimal indicants a double
            case whsp: numToWhit(); break;
            case endstr: numToWhit(); break;
            default: 
            if (isdigit(line[k]))// is current char a numerical value?

            ival = (ival * 10) + (ch - '0'); //builds a number value from ASCII character's 
        }
        //If there is no transition, get the next character & CharType
        ch = line[++k];
        chtype = getType(ch);
    }
}
/*===========================================================================================
*******************************|  DOUBLE   STATE   |*****************************************
============================================================================================*
|																							|
| Handel's double state, 2 state transition possible, double to white, double to exponent   |
|       stay in double state while numerical values are found in the current line,		    |
|         change to white state at end of line or when whitespace encountered               |
|                      change to exponent state when a e is found                           |
|																							|
|-----------------------------------------------------------------------------------------*/
void dbleState()
{
    //Loop until the state is no longer dbl or end of line is reached
    while (state == dble && k < len)
    {
        //CharType transitions to a different state
        switch (chtype)
        {
            //transition conditions are self explanatory
            case expo: floatToExpnt(); break;
            case whsp: floatToWhite(); break;
            default:
            //builds a number value from ASCII characters (ch - '0')
            fval = (fval * 10) + (ch - '0');
            //calculates decimal places for double value
            power = power * 10;
        }
        //If there is no transition, get the next character & CharType
        ch = line[++k]; 
        chtype = getType(ch);
    }
}

/*===========================================================================================
*******************************|  EXPONENT STATE   |*****************************************
============================================================================================*
|																							|
|        Handel's exponent state, 1 state transition possible, exponent to white            |
|      stay in exponent state while numerical values are found in the current line,	        |
|         change to white state at end of line or when whitespace encountered               |
|																							|
|-----------------------------------------------------------------------------------------*/
void expntState()
{
    //Loops as long as in exponent state and till the end of the line  
    while (state == expnt && k <= len)
    {
        switch (chtype)
        {
            case whsp: expntToWhite(); break;
            default:

            if (toupper(ch) == 'E')//is ch E?, default action set to positive
            {
                esign = 1; //sign of exponent value will be positive
            }
            else if (ch == '-') //minus indicates a negative numerical value
            {
                esign = -1;  //sign of exponent value will be negative
            }

            //If numerical value, increase the power of 10 by one
            // and adds a builds a number value from ASCII character's
            if (isdigit(ch))
                expt = (expt * 10) + (ch - '0');
        }
        //If there is no transition, get the next character & CharType
        ch = line[++k];
        chtype = getType(ch);
    }
}

/*===========================================================================================
*******************************| GET CHAR TYPE FUNCTION |************************************
============================================================================================*
|                                                                                           |
|                     Function returns the current character type                           |
|               character type are white, word, integer, double, exponent                   |
|                                                                                           |
------------------------------------------------------------------------------------------*/

CharType getType(char ch)
{
    CharType type;
    type = whsp;

    if (isspace(ch)) //if character is whitespace set type to whitespace
    {
        type = whsp;
    }
    else if (isalpha(ch) || ch == '\'') //is it alpha or a ' ?
    {
        if (toupper(ch) == 'E') //f character found is 'E' set type to exponent
        {
            type = expo;
        }
        else //if not E it must be a letter
        {
            type = lett;
        }
    }
    else if (isdigit(ch)) //is character found is a digit? yes then set type to digit
    {
        type = digit;
    }
    else switch (ch) //check for operand types and set sing for numerical values
    {
        case '+':  type = plus1;  sign = 1; break; //character plus,number will be positive
        case '-':  type = minus1; sign = -1; break;//character minus,number will be negative
        case '.':  type = point; break; 
        case '\'':  type = qout;  break;
    }

    return type;
}


// { white, word, num, dble, expnt };

/*===========================================================================================
*******************************|     OUT-PUT LOOPER    |*************************************
=============================================================================================
|                                                                                           |
|					 Function out puts characters using a for loop,                         |
|                                                                                           |
 ------------------------------------------------------------------------------------------*/

//Outputs characters using a for loop.
void Fill(char ch, int b)
{
    for (int a = 0; a < b; a++)
        printf("%c", ch);
}

/*===========================================================================================
*********************************| WORD OUT-PUT TABLE |**************************************
============================================================================================*
|																							|
|                  Function out puts statistic frequency of word length					    |
|                      into word table using word array and passed							|
|                           to function header and indexes									|
|							using extended ASSCI characters			                        |
|																							|
|-----------------------------------------------------------------------------------------*/

void wordTable(int Array[], char Title[], char h1[], char h2[], int width, int height)
{
    //change console stream out put color, 3 = CYAN
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("\n\n%s\n", Title);

    //Determines the space between both column headers
    int spacing = width - strlen(h1) - strlen(h2);

    for (int q = 0; q <= height; q++)
    {
        //Top of table with the headers.
        if (q == 0)
        {  
            //print characters using extended ASCII characters and formated spacing
            printf("%c", 201); //print extended ASCII character
            Fill(205, width); //fill function formats spacing
            printf("%c\n", 187);
            printf("%c%s", 186, h1);//print  extended ASCII character and heading 1
            Fill(' ', spacing);//call Fill pass and determined spacing
            printf("%s%c\n", h2, 186);//print  extended ASCII character and heading 2
        }


        //display data for table
        if (Array[q] != 0)
        {
            printf("%c", 204);
            Fill(205, width);
            printf("%c", 185);
            printf("\n%c", 186);
            //change console stream out put color, 2 = GREEN
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            printf("%-2d%*d", q+1 , width - 2, Array[q]); 
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);

            printf("%c\n", 186);
        }



        //Bottom of  table
        if (q == height)
        {
            printf("%c", 200); Fill(205, width); printf("%c", 188);
        }
    }
}

/*===========================================================================================
*******************************| INTEGER OUT-PUT TABLE |*************************************
=============================================================================================
|																							|
|                     Function out puts statistic values of integers					    |
|                    into integer table using integer array and passed						|
|                            to function header and indexes 							    |
|							using extended ASCII characters	                                |
|																							|
|-----------------------------------------------------------------------------------------*/
void intagerTable(int Array[], char Title[], char h1[], char h2[], int width, int height)
{
    //change console stream out put color, 14 = YELLOW
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    printf("\n\n%s\n", Title);
    //Determines the space between both column headers
    int spacing = width - strlen(h1) - strlen(h2);

    for (int q = 0; q <= height; q++)
    {
        //Top of table with the headers.
        if (q == 0)
        {
            //print characters using extended ASCII characters and formated spacing
            printf("%c", 201);// print extended ASCII character
            Fill(205, width);//call Fill pass extended ASCII and spacing
            printf("%c\n", 187);
            printf("%c%s", 186, h1);
            Fill(' ', spacing);//call Fill pass it determined spacing
            printf("%s%c\n", h2, 186);//print  extended ASCII character and heading 2
        }


        //display data for table
        if (Array[q] != 0)
        {
            printf("%c", 204);
            Fill(205, width);//call Fill pass it extended ASCII and spacing
            printf("%c", 185);
            printf("\n%c", 186);//print  extended ASCII character and heading 1
            //change console stream out put color
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            //prints length & frequency width-2 apart
            printf("%-2d%*d", q - 1, width - 2, Array[q]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);

            printf("%c\n", 186);
        }

        //Bottom of  table
        if (q == height)
        {
            printf("%c", 200); Fill(205, width); printf("%c", 188);
        }
    }
}


/*===========================================================================================
*******************************| DOUBLE OUT-PUT TABLE |**************************************
=============================================================================================
|																							|
|                      Function out puts statistic values of doubles					    |
|                    into double table using double array and passed						|
|                            to function header and indexes.							    |
|									                                                        |
|-----------------------------------------------------------------------------------------*/

void doubelTable(double Table_Array[], char Title[], char h1[], char h2[], int width, int height)
{
    //change console stream out put color, 5 = MAGENTA,
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
    printf("\n\n%s\n", Title);


    //Determines the space between both column headers
    int headingSpace = width - strlen(h1) - strlen(h2);


    for (int i = 0; i <= height; i++)
    {

        //Prints top of table with headers
        if (i == 0)
        {
            //print characters using extended ASCII characters and formated spacing
            printf("%c", 201);//print extended ASCII character
            Fill(205, width);  //fill function formats spacing
            printf("%c\n", 187);
            printf("%c%s", 186, h1);//print  extended ASCII character and heading 1
            Fill(' ', headingSpace);//call Fill pass extended ASCII and spacing
            printf("%s%c\n", h2, 186);//print  extended ASCII character and heading 2
        }

        //Prints indexes of table 
        if (i != height)
        {
            printf("%c", 204);//extended ASCII 
            Fill(205, width);//call Fill pass extended ASCII and spacing
            printf("%c", 185);
            printf("\n%c", 186);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            //prints index & its value width-2 apart
            printf("%-2d%*.10g", i, width - 2, Table_Array[i]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
            printf("%c\n", 186);


        }


        //prints bottom section of table
        if (i == height)
        {
            printf("%c", 200); Fill(205, width); printf("%c", 188);
        }
    }
}



/*===========================================================================================*
---------------------------------------------------------------------------------------------
*******************************| STATE TRANSITIONS BLOCK |***********************************
---------------------------------------------------------------------------------------------
============================================================================================*
|																							|
|          Functions handles state transitions, their are 10 transitions are possible	    |
|            3 white state transition, 1 word transition 3 integer state transitions 	    |
|                 2 double state transitions, 1 exponent state transition				    |
|																							|
|-----------------------------------------------------------------------------------------*/



/*===========================================================================================*
******************************|     WHITE TRANSITIONS     |**********************************
============================================================================================*
|																							|
|                      Functions handles whits state transitions,                           |
|                   their are 3 white state transitions are possible                        |
|                 white to word, white to integer and white to double,                      |
|																							|
|-----------------------------------------------------------------------------------------*/

void whiteToWord()
{
    state = word;
    wordlen = 1;
}
void whiteToNum()
{
    state = num;

/*   checks if ch is an operator or a number
     if true ival = 0; false ival = ch-'0' which is the converted ASCII value of ch
*/   ival = (ch == '-' || ch == '+') ? 0 : ch - '0';

}
    
void whiteToFloat()
{
    state = dble;
    fval = 0; //reset fval to store value of determine double
    power = 1;//reset power to reset decimal position
}

/*===========================================================================================*
******************************|     WORD TRANSITIONS     |**********************************
============================================================================================*
|																							|
|                       Functions handles word state transitions,                           |
|              their is 1 white state transitions possible, word to white                   |
|																							|
|-----------------------------------------------------------------------------------------*/

void wordToWhite()
{
    indexW++;//increment word index for new word found
    mywords[wordlen - 1]++;//Increments frequency for word length 
    state = white;
}


/*===========================================================================================*
******************************|     INTEGER TRANSITIONS     |*********************************
=============================================================================================*
|																							|
|                      Functions handles integer state transitions,                         |
|                   their are 3 integer state transitions are possible                      |
|               integer to double, integer to white and integer to exponent,                |
|																							|
|-----------------------------------------------------------------------------------------*/

void numTofloat()
{   
    //double check previous char type in case it was a operand of a integer type
    if (ch == '.' && line[k - 1] == '+' || line[k - 1] == '-')
    {
        state = dble;
    }
    else//false could only mean previous char type was a numerical integer char type
    {
        state = dble;
    }

    
    fval = ival, power = 1;//Double value get integer value
}
void numToWhit()
{
    myints[++indexI] = ival*sign; //store integer value at the end of the integer array
    state = white;
    ival = 0;//reset ival for next integer value
    sign = 1;//reset sign for next sign of numerical value 
}
void numToExpnt()
{
    state = expnt;
    fval = ival;//Double value get integer value
    ival = 0;   //reset ival for next integer value
}


/*===========================================================================================*
******************************|     FLOAT TRANSITIONS     |**********************************
============================================================================================*
|																							|
|                      Functions handles double state transitions,                          |
|                   their are 2 double state transitions are possible                       |
|                         double to white and double to exponent                            |
|																							|
|-----------------------------------------------------------------------------------------*/

void floatToWhite()
{
    fval = fval / power * sign;//Double value gets decimal position and sign type.
    mydoubles[indexD++] = fval;//store double value at the end of the double array
    state = white;

    power = 1, sign = 1, fval = 0;//resets power, sign & value for next value,sign,position
}
void floatToExpnt()
{
    state = expnt;
    fval = fval / power * sign;//Double value gets decimal position and sign type
    sign = 1;                  //reset sign for next sign of numerical value 
    power = 1;
}

/*===========================================================================================*
******************************|    EXPONENT TRANSITIONS    |*********************************
============================================================================================*
|																							|
|                     Functions handles exponent state transitions,                         |
|           their is 1 exponent state transitions possible, exponent to white               |
|																							|
|-----------------------------------------------------------------------------------------*/

void expntToWhite()
{
    state = white;

    //positions the decimals points for the double value

    if (esign == 1)// if positive move decimal points to the right
    while (expt-- > 0)//expt is the amount of decimal places to be moved
    {
        fval *= 10; //moves one decimal point to right of the double value
    }

    if (esign == -1)// if negative move decimal points to the left
    while (expt-- > 0)//expt is the amount of decimal places to be moved
    {
        fval /= 10 * esign; //moves one decimal point to left for the double value
    }

    mydoubles[indexD++] = fval; //store current double value at end of array
    state = white;
    fval = 0, expt = 0, esign = 1; //resets power, sign & value for next value,sign,position
}

/*===========================================================================================*
---------------------------------------------------------------------------------------------
***************************|[ END OF STATE TRANSITIONS BLOCK ]|******************************
---------------------------------------------------------------------------------------------
============================================================================================*/



/*===========================================================================================*
******************************|        END OF CPP       |*************************************
============================================================================================*/