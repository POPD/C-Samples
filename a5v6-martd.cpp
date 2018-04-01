/*============================================================================================
************************************| ID BLOCK |**********************************************
==============================================================================================

Due Date:           December, 6, 2014
Software Designer:  Daric Martin-Lavoie
Course:             420-306-AB ALGORITHM DESIGN section 00001
Deliverable:	    Assignment #5  Version 4

Description :	     Program  converts infix expressions into postfix expressions
					 and evaluate the expressions. The expressions results are given
                     in the form of a numerical value.


=============================================================================================
********************************| PRELIMINARIES |********************************************
============================================================================================*/

#include <iostream>
#include <iomanip>  
#include <windows.h>
#include <vector>
using namespace std;
HANDLE hConsole;

#pragma warning( disable 4996 4244)
/*===========================================================================================
*********************************|   CONSTANTS  |********************************************
============================================================================================*/


const int LMAX = 50;        //maximum number of infix strings in array
const int NMAX = 30;        //maximum size of each infix string
const int LSIZE = 5;        //actual number of infix strings in the array infix
const int NUMOPNDS = 10;    //number of different operands i.e. A through J
const int MAXSTACK = 100;   //maximum number of items allowed in the stack structures


/*===========================================================================================
*********************************|   STRUCTURE  |********************************************
============================================================================================*/
struct OPERATOR_STACK		//declare the operator-stack structure to be used in conversion
{
	int top;
	char item[MAXSTACK];
};

struct OPERAND_STACK
{
	int top;
	double item[MAXSTACK];
};

OPERATOR_STACK opstk;
OPERAND_STACK opndstk;


/*===========================================================================================
*********************************| HAPPY HOLIDAYS DAN |**************************************
============================================================================================*/
enum EFrequency {
	keRest = 0,
	keC1 = 131, keCS1 = 139, keD1 = 147, keDS1 = 156, keE1 = 165, keF1 = 175,
	keFS1 = 185, keG1 = 196, keGS1 = 208, keA1 = 220, keAS1 = 233, keB1 = 247,
	keC2 = 262, keCS2 = 277, keD2 = 294, keDS2 = 311, keE2 = 330, keF2 = 349,
	keFS2 = 370, keG2 = 392, keGS2 = 415, keA2 = 440, keAS2 = 466, keB2 = 494,
	keC3 = 523, keCS3 = 554, keD3 = 587, keDS3 = 622, keE3 = 659, keF3 = 698,
	keFS3 = 740, keG3 = 784, keGS3 = 830, keA3 = 880, keAS3 = 932, keB3 = 988,
};
enum EDuration {
	ke16th = 200, ke8th = (ke16th << 1), keQuart = (ke8th << 1),
	keHalf = (keQuart << 1), keWhole = (keQuart << 1)
};


class CNote {
public:
	CNote(unsigned int uiFrequency, unsigned int uiDuration)
		: muiFrequency(uiFrequency), muiDuration(uiDuration) {}
	void Play() {
		if (muiFrequency > 0) {
			Beep(muiFrequency, muiDuration);
		}
		else {
			Sleep(muiDuration);
		}
	}
	unsigned int muiFrequency;
	unsigned int muiDuration;
};

class CMelody {
public:
	void AddNote(unsigned int uiFrequency, unsigned int uiDuration) {
		mqNotes.push_back(CNote(uiFrequency, uiDuration));
	}
	void Play() {
		const unsigned int kuiNoteCount = mqNotes.size();
		std::vector<CNote>::iterator qIter;
		for (qIter = mqNotes.begin(); qIter != mqNotes.end(); ++qIter) {
			qIter->Play();
		}
	}
	std::vector<CNote> mqNotes;
};
/*===========================================================================================
*******************************|   GLOBAL VARIBLES   |***************************************
============================================================================================*/

//array of infix strings
char infix[LMAX][NMAX] = { "A+B-C",
"(A+B)*(C-D)",
"A$B*C-D+E/F/(G+H)",
"((A+B)*C-(D-E))$(F+G)",
"A-B/(C*D$E)" };
//array of postfix strings
char postfix[LMAX][NMAX] = { "AB+C-",
"AB+CD-*",
"AB$C*D-EF/GH+/+",
"AB+C*DE--FG+$",
"ABCDE$*/-" };
char  opnd[NUMOPNDS] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J' };
float opndval[NUMOPNDS] = { 3, 1, 2, 5, 2, 4, -1, 3, 7, 187 };
int j;
int k;
float end_result[LSIZE];
char  pofix[LMAX][NMAX];
bool und;
bool full;
char chrct[NMAX];
int  letter;
int  nextchar;
char topsym;
char s[NMAX];
char pop[NMAX];


/*===========================================================================================
*******************************| FUNTION PROTOTYPE   |***************************************
============================================================================================*/

void Infix_To_Postfix();
void In_To_Po_output();
bool finish();
bool end();
bool nothing();
bool ending();

float Pop_And_Test();
void  Push_And_Test(float);
char  Pop_Test();
void  Push_Test(char);
void  Dump_Stack(OPERATOR_STACK);
float Exprssion_Evaluator();
float Evaluate_Operator(char[], float, float);
bool  Operand(char[], int);
bool  prcd(char, char[], int);


/*===========================================================================================
*******************************| MAIN BLOCK BEGINS |*****************************************
============================================================================================*/
int main()
{
	// Change stream out put color 
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 43);
	cout << "INFIX CONVERSION TO POSTFIX WITH THE EXPRESION NUMERICAL VALUE" << endl << endl;
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Program  converts infix expressions into postfix expressions" << endl <<
		    "and evaluates the expressions which yields results in the "    << endl <<
		    "form of a numerical value." << endl << endl;


	/**************************************************************************
	             PRINT OUT THE OPERANDS AND THEIR VALUES
	**************************************************************************/
	SetConsoleTextAttribute(hConsole, 5.3);
	cout << setw(40) << "OPERANDS AND THEIR VALUES:" << endl << endl;
	for (j = 0; j<NUMOPNDS; j++)
		cout << setw(5) << opnd[j];
	cout << endl << endl;
	for (j = 0; j<NUMOPNDS; j++)
		cout << setw(5) << opndval[opnd[j] - 'A']; //is not SIMPLER to just use j ONLY as the subscript?
	//Q:  why the more complex syntax?   A:  j ONLY assumes that operands are in lexical order
	cout << endl << endl << endl;;

	In_To_Po_output();
	SetConsoleTextAttribute(hConsole, 7);
	system("PAUSE");

	SetConsoleTextAttribute(hConsole, 47);
	cout << " Happy Holidays Dan!" << endl;
	SetConsoleTextAttribute(hConsole, 74.8);
	cout << " Make sure to turn up speakers to hear special bonus song ^_^ " << endl;
	SetConsoleTextAttribute(hConsole, 47);
	cout << " Computer must support the beep function in order to hear any thing" << endl;
	SetConsoleTextAttribute(hConsole, 5147);
	cout << " I wish you a great Winter break" << endl;
	SetConsoleTextAttribute(hConsole, 7);
	system("PAUSE");


	/**********************************************
	        Silent Night Beep Song
			 Author: Michael Hall
			       XoaX.net 
	***********************************************/
	CMelody qSilentNight;

	qSilentNight.AddNote(keA2, ke8th + ke16th);
	qSilentNight.AddNote(keB2, ke16th);
	qSilentNight.AddNote(keA2, ke8th);
	qSilentNight.AddNote(keFS2, keQuart);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.AddNote(keA2, ke8th + ke16th);
	qSilentNight.AddNote(keB2, ke16th);
	qSilentNight.AddNote(keA2, ke8th);
	qSilentNight.AddNote(keFS2, keQuart);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.AddNote(keE3, ke8th + ke16th);
	qSilentNight.AddNote(keDS2, ke16th);
	qSilentNight.AddNote(keE3, ke8th);
	qSilentNight.AddNote(keCS3, keQuart);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.AddNote(keD3, ke8th + ke16th);
	qSilentNight.AddNote(keCS3, ke16th);
	qSilentNight.AddNote(keD3, ke8th);
	qSilentNight.AddNote(keA2, keQuart);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.AddNote(keB2, keQuart);
	qSilentNight.AddNote(keB2, ke8th);
	qSilentNight.AddNote(keD3, ke8th + ke16th);
	qSilentNight.AddNote(keC3, ke16th);
	qSilentNight.AddNote(keB2, ke8th);

	qSilentNight.AddNote(keA2, ke8th + ke16th);
	qSilentNight.AddNote(keB2, ke16th);
	qSilentNight.AddNote(keA2, ke8th);
	qSilentNight.AddNote(keFS2, keQuart);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.AddNote(keB2, keQuart);
	qSilentNight.AddNote(keB2, ke8th);
	qSilentNight.AddNote(keD3, ke8th + ke16th);
	qSilentNight.AddNote(keCS3, ke16th);
	qSilentNight.AddNote(keB2, ke8th);

	qSilentNight.AddNote(keA2, ke8th + ke16th);
	qSilentNight.AddNote(keB2, ke16th);
	qSilentNight.AddNote(keA2, ke8th);
	qSilentNight.AddNote(keFS2, keQuart);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.AddNote(keCS3, ke8th + ke16th);
	qSilentNight.AddNote(keCS3, ke16th);
	qSilentNight.AddNote(keCS3, ke8th);
	qSilentNight.AddNote(keE3, ke8th + ke16th);
	qSilentNight.AddNote(keD3, ke16th);
	qSilentNight.AddNote(keCS3, ke8th);

	qSilentNight.AddNote(keD3, keQuart + ke8th);
	qSilentNight.AddNote(keFS3, keQuart);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.AddNote(keD3, ke8th + ke16th);
	qSilentNight.AddNote(keA2, ke16th);
	qSilentNight.AddNote(keFS2, ke8th);
	qSilentNight.AddNote(keA2, ke8th + ke16th);
	qSilentNight.AddNote(keG2, ke16th);
	qSilentNight.AddNote(keE2, ke8th);

	qSilentNight.AddNote(keD2, keHalf + ke8th);
	qSilentNight.AddNote(keRest, ke8th);

	qSilentNight.Play();
	

	return 0;
}
/*===========================================================================================
*******************************|  MAIN BLOCK ENDS  |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| CONVERSION FUNCTION |**************************************
============================================================================================*
|																							|
|                            INFIX TO POSTFIX NOTATION										|
|																							|
|																							|
|																							|
===========================================================================================*/
void Infix_To_Postfix()
{
	for (j = 0; j < LSIZE; j++) //runs through every line of char
	{
		int ifxIDX = 0;  //variable to keep track of every symbol
		int outlen = 0;
		int count = 0;
		topsym = '+';
		strcpy(s, infix[j]);
		while (s[ifxIDX] != '\0')
		{
			if (Operand(s, ifxIDX)) //checks to see if current symbol is an operand
			{
				pofix[j][count] = s[ifxIDX];  //add symbol to postfix expression
				count++;
				outlen++;
			}
			else              //  current symbol of the operator
			{
				if (nothing()) // checks if the stack is empty
					Pop_Test();
				else
					topsym = Pop_Test(); //take the symbol from the stack for comparison
				while (und == 0 && prcd(topsym, s, ifxIDX) == 1) /*verify the first priority when get
																 a char from the stack*/
				{
					pofix[j][count] = topsym;  //joins topsym to the postfix expression
					topsym = Pop_Test();  //pop the stack to get  the next symbol,
					outlen++;
					count++;
				}
				if (und != 1) // checks to see if we got something from the stack
					Push_Test(topsym);  //puts topsym on to the stack
				if (und != 0 || s[ifxIDX] != ')') /*checks if the stack was empty or if the current
												  symbol is a right brace*/
												  Push_Test(s[ifxIDX]);  //joins the symbol to the stack
				else
					topsym = Pop_Test();  //pop and get the next symbol from stack 
			}
			if (ifxIDX <= MAXSTACK) //checks to see if we reached the end end of the stack
				ifxIDX++;  // increments in order to get the next symbol
			else
				s[ifxIDX] = '\0';
		}
		while (nothing() == 0) // runs the loop while the stack is not empty
		{
			outlen++;
			pop[outlen] = Pop_Test();
			pofix[j][outlen - 1] = pop[outlen];
		}
	}
}

/*===========================================================================================
***************************| EXPRESSIONS OUT-PUT FUNCTION |**********************************
============================================================================================*
|																							|
|                Function displays infix and postfix expression in a table	                |
|																							|
|																							|
|																							|
===========================================================================================*/
void In_To_Po_output()
{
	Infix_To_Postfix();
	SetConsoleTextAttribute(hConsole, 14);
	cout << "         INFIX Expression            POSTFIX Expression        Value" << endl;
	cout << "        -----------------            ------------------        -----" << endl;
	for (j = 0; j<LSIZE; j++)  //display name strings & corresponding weights 
	{
		end_result[j] = Exprssion_Evaluator();
		cout << setw(25) << infix[j] << setw(30) << postfix[j] << setw(13) << end_result[j] << endl;
	}
	cout << endl << endl << endl << endl;
}

/*===========================================================================================
****************************| POSTFIX EVALUATION FUNCTION |**********************************
============================================================================================*
|																							|
|                     FUNCTION TO EVALUATE THE POSTFIX EXPRESSION							|
|																							|
|																							|
|																							|
===========================================================================================*/
float Exprssion_Evaluator()
{
	k = 0;
	float op1; //1st operator
	float op2; //2nd operator
	float total; //the end result 

	strcpy(chrct, pofix[nextchar]); //gets each symbol 
	while (chrct[k] != '\0')  //checks to see if we reach end of string, the string terminator
	{
		if (Operand(chrct, k))  // verify if we got an operand
		{
			letter = chrct[k] - '0' - 17; //from A to J
			total = opndval[letter];  // get the final result
			Push_And_Test(total);  //gets the numerical value of operand
		}    //checks for a mathematical symbol ?
		else if (chrct[k] == '+' || chrct[k] == '-' || chrct[k] == '*' || chrct[k] == '/' || chrct[k] == '$')
		{
			op2 = Pop_And_Test();
			op1 = Pop_And_Test();
			total = Evaluate_Operator(chrct, op1, op2);
			Push_And_Test(total);
		}
		if (k <= MAXSTACK)
			k += 1;
		else
			chrct[k] = '\0';
	}
	total = Pop_And_Test();
	nextchar++; // increments to get next symbol

	return total; //return the end result
}


/*===========================================================================================
********************************|   EVALUATION FUNCTION    |*********************************
============================================================================================*
|																							|
|                       FUNCTION TO EVALUATE THE MATHEMATICAL SIGNS                         |
|                 Function logic converts operator symbols into its actual                  |
|	               operator calculations Function evaluates 1st and 2nd                     |
|	                         values to determine a total value							    |
|																							|
|																							|
|																							|
===========================================================================================*/
float Evaluate_Operator(char ch[], float op1, float op2)
{
	float tot;
	if (ch[k] == '+' || ch[k] == '-' || ch[k] == '*' || ch[k] == '/' || ch[k] == '$') //if we get one
	{
		switch (ch[k])																  //of these symbols 
		{
		case '+':
			tot = op1 + op2;  //logic to convert "+" symbol to performs addition of 1st & 2nd values
			break;
		case '-':
			tot = op1 - op2;  //converts the "-" char to performs subtraction of 1st & 2nd values
			break;
		case '*':
			tot = op1 * op2;  //if "*" performs multiplication 1st & 2nd values
			break;
		case '/':
			tot = op1 / op2;  //converts "/" character to performs division of 1st & 2nd values
			break;
		case '$':
			tot = pow(op1, op2); //convert "$" to perform exponent calculation of 1st & 2nd values
			break;
		}
	}
	return tot;
}


/*===========================================================================================
****************************| EVALUATE OPERANDS FUNCTION   |*********************************
============================================================================================*
|																							|
|                                 Self explanatory                     				        |
|																							|
|																							|
|																							|
===========================================================================================*/
bool Operand(char ch[], int k)
{                                  
	if (ch[k] >= 64 && ch[k] <= 74)//Rang 64 to 74 is A to J
		return 1; else  return 0;
}

/*===========================================================================================
********************************|   FINISH FUNCTION   |**************************************
============================================================================================*
|																							|
|                           Functions determines if stack empty					            |
|																							|
|																							|
|																							|
===========================================================================================*/

bool finish()
{
	if (opndstk.top == -1)
		return 1;  else  return 0;
}
bool nothing()
{
	if (opstk.top == -1)
		return 1;  else  return 0;
}

bool end()
{
	if (opndstk.top == MAXSTACK - 1)
		return 1;  else  return 0;
}
bool ending()
{
	if (opstk.top == MAXSTACK - 1)
		return 1;  else  return 0;
}


/*===========================================================================================
********************************|   POP TEST FUNCTION     |**********************************
============================================================================================*
|																							|
|                       pops the stack, the last value meaning the                          |
|                 top value of the stack is taken off the operator stack                    |
|                  function regulates the und bool to true if stack empty			        |
|																							|
|																							|
|																							|
===========================================================================================*/

float Pop_And_Test()
{
	if (finish())
		und = 1;
	else
	{
		und = 0;
		opndstk.top--;
	}
	return opndstk.item[opndstk.top + 1];
}
char Pop_Test()
{
	if (nothing())
		und = 1;
	else
	{
		und = 0;
		opstk.top--;
	}
	return opstk.item[opstk.top + 1];
}


/*===========================================================================================
********************************|   PUSH TEST FUNCTION     |*********************************
============================================================================================*
|																							|
|                       Puts the value onto the stack, the values                           |
|                       is pushed onto the top of the  value stack                          |
|                and the operand is pushed onto the top of the operand stack			    |
|																							|
|																							|
|																							|
===========================================================================================*/
void Push_And_Test(float opndval)
{
	if (end())
		full = 1;
	else
	{
		full = 0;
		opndstk.top++;
		opndstk.item[opndstk.top] = opndval;
	}
}
void Push_Test(char opnd)
{
	if (ending())
		full = 1;
	else
	{
		full = 0;
		opstk.top++;
		opstk.item[opstk.top] = opnd;
	}
}


/*===========================================================================================
********************************|  OUT-PUT STACK FUNCTION     |******************************
============================================================================================*
|																							|
|                              Function out puts the stack							        |
|																							|
|																							|
|																							|
===========================================================================================*/

void Dump_Stack(OPERATOR_STACK opstk)
{
	for (int i = 1; i <= opstk.top; i++)
		cout << opstk.item[i] << " | ";
	cout << endl;
}


/*===========================================================================================
********************************|     PRCD FUNCTION     |************************************
============================================================================================*
|																							|
|                            									                            |
|																							|
|																							|
|																							|
===========================================================================================*/

bool prcd(char topsym, char symbolC[], int ifxIDX)
{
	if (topsym == '(' || symbolC[ifxIDX] == '(')
		return 0;
	// + and - is priority is less then $, *, /
	else if ((topsym == '+' || topsym == '-') &&
		(symbolC[ifxIDX] == '$' || symbolC[ifxIDX] == '*' || symbolC[ifxIDX] == '/'))
		return 0;
	// + and - evaluation priority is in the order in which they appear first 
	else if ((topsym == '+' || topsym == '-') &&
		(symbolC[ifxIDX] == '+' || symbolC[ifxIDX] == '-'))
		return 1;
	// * and /  evaluation priority is in the order in which they appear first 
	else if ((topsym == '*' || topsym == '/') &&
		(symbolC[ifxIDX] == '*' || symbolC[ifxIDX] == '/'))
		return 1;
	// *, /, or $ evaluation priority is greater then  + and -
	else if ((topsym == '*' || topsym == '/' || topsym == '$') &&
		(symbolC[ifxIDX] == '+' || symbolC[ifxIDX] == '-'))
		return 1;
	// operations that are before the closing right bracket are evaluated  
	else if ((topsym == '+' || topsym == '-' || topsym == '*' || topsym == '/' || topsym == '$') &&
		(symbolC[ifxIDX] == ')'))
		return 1;
	// $ evaluation priotity is greater then * and /
	else if ((topsym == '$') &&
		(symbolC[ifxIDX] == '*' || symbolC[ifxIDX] == '/'))
		return 1;
	else
		return 0;
}

/*===========================================================================================
********************************|    END OF CPP    |*****************************************
============================================================================================*/