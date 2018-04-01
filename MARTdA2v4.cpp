/*===========================================================================================
*******************************|   ID BLOCK   |**********************************************
=============================================================================================

Due Date:           September, 30, 2014
Software Designer:  Daric Martin Lavoie
Course:             420-306 Autumn 2014
Deliverable:        Assignment #2 perfect squares



DESCRIPTION:      Program generates Pythagorean numbers. A Pythagorean numbers is made
of two perfect squares and is it self a perfect square.
Program accepts input for variable m were m is the number size limit for the table.
Program accepts input for lo and hi were lo is the min range value and hi is the max range value.
A function then stores Pythagorean values in ascending order and with out duplicates 
into an array. Program then searches Pythagorean numbers made of perfect squares
from the array and store them in PYTH array and prints out the array. 

=============================================================================================
********************************| PRELIMINARIES |********************************************
============================================================================================*/

#include <iostream>
using namespace std;
#include <conio.h> 
#include <math.h>
#include <iomanip>


/*===========================================================================================
*******************************| FUNTION PROTOTYPE   |***************************************
============================================================================================*/

void MakeList(int&, int, int[]); //Builds an array with no duplicates in acsd order




/*===========================================================================================
*******************************| MAIN BLOCK BEGINS |*****************************************
============================================================================================*/

int main()
{

	//****************DECLARATION OF VARIBLES****************//

	///M is our number size limit for our table,
	//xm used for Pythagorean table size limit such that  xm = m + 1; 
	//mm used for Pythagorean table size limit such that  mm = sqrt(xm/2.) +2; 
	//i and j are perfect squares used to generate Pythagorean number
	//c is a variable that stores the  Pythagorean numbers 
	//lo is our min range value for array pcan
	//hi is our max range value for our array pcan
	//pcan is our array that will store Pythagorean values from range hi to lo.
	//tail value is used to increment the sub count, this is used to keep track of the array size, 
	//PYTH is an array used to store perfect squares
	//s has the same functionality as tail but for PYTH array, 
	//sq is a square root value computed by tacking square root value from pcan
	/*sql is the same as sq but gets +1 so it rounds up numbers that were round off in
	  the square root process*/

	int m, i, j, c, lo, hi, s = -1, tail = -1;
	int mm;
	double xm, sq, sql;
	int pcan[9999];
	int PYTH[100];

	//****************** GET INPUT PARAMATERS******************//

	//echoes program description to output console 
	//then ask for input from user console.

	cout << "This program generates Pythagorean candidate numbers and stores"
		 << "the number that are in a range from lo which is low to hi into a them in an array pcan,"
		 << "the array will be made of Pythagorean numbers in ascending order and with no duplicates,"
		 << "progam then checks pcan for perfect squares and inserts them into array PYTH," 
		 << "program then displays PYTH array with column heads" << endl;


	cout << endl << endl;
	cout << "Type integer candidate number size limit m\n";
	cin >> m;

	cout << "Type a integer for the lowest range value" << endl;  
	cin >> lo;
	cout << "Type an integer for the highest range value" << endl;  
	cin >> hi;

	cout << "Program will start to display array actions" << endl;  
	cout << endl << endl;


	//******START OF GENERATING PYHAGOREAN NUNBER LOGIC**********//

	xm = m + 1;				                        //find corresponding table-size mm for this limit
	mm = sqrt(xm / 2.) + 2;

	for (i = 1; i < mm - 1; i++)					//begin calculation for Pythagorean numbers
	{

		for (j = i + 1; j < mm; j++)			    //show p-candidates on rest of row
		{
			c = i*i + j*j;                          // this is the Pythagorean number


			if (c >= lo && c <= hi)                   /* this only allows number greater then lo and
													  less then hi to be stored into the array*/
			{
				MakeList(tail, c, pcan);		      /*Function call, enter the Pythagorean number from range
													    lo to hi into the array  tail is sent as the
														sub count, c is sent as a Pythagorean number,
														pcan is sent as our array*/
			}
		}
	}
	//*******END OF GENERATING PYHAGOREAN NUNBER LOGIC*******//

	cout << " PYTH LIST" << endl << endl;


	//***********START OF PERFECT SQUARES INSERT LOGIC*********//

	for (int a = 0; a <= tail; a++)			 //for loop that loop through the array
	{
		sq = sqrt((double)pcan[a]);			 /*turns values in pcan to a double so it can take
											 the square root of the value with decimals, 
											 if the squire root results in a whole value 
											 we have a perfect square value.
											 */

		sql = sq + 1;						// this is for values that are round off

		if (sq == (int)sq)				   /*verifies if its a whole number, sq is a double
										   and is type cast to an int and then compared,
										   if sq == (int)sq then it means that both values
										   are whole, Example( double 2.0 = int 2)
										   but (double 2.5 = int 2) so if sq is not a whole value
										   then when typecast to int it will round down and values
										   will not be the same)*/

		{

			/* this checks for perfect squares,
			a^2 = a*a were a^2 = pcan and a*a = sq*sq
			if the squares root of the number times
			it self = the squared version of the number
			then we have a perfect square */

			if (sq*sq == pcan[a] || sql *sql == pcan[a]) 
			{
				s += 1;                                 //increments sub count counter s, same as tail

				PYTH[s] = pcan[a];                     //inserts perfect square from pcan into PYHT
			}
		}

	}


	//***********END OF PERFECT SQUARES INSERT LOGIC********//


	//**************START OF PYHAGOREAN TABLE LOGIC**********//

	/*Out puts sub-count and its
	numbers into perfect square table*/

	cout << setw(2) << "i" << setw(12) << "PYTH[i]" << endl;  

	cout << "____________________" << endl;                 
	for (int a = 0; a <= s; a++)
	{

		cout << setw(2) << a << setw(4) << "|" << setw(6) << PYTH[a] << endl; 
	}

	//**************END OF PYHAGOREAN TABLE LOGIC***********//
	cout << endl << endl << endl;
	cout << "End of Program" << endl;
	system("pause");
}



/*===========================================================================================
*******************************| MakeList FUNCTION   |***************************************
============================================================================================*/


void MakeList(int &t, int r, int p[])      /*function definition, tail is shared
											 c is sent into r and pcan is sent into p, */
{

	//*********************DECLARATION OF VARIBLES***********************

	// q is a variable used for the sub counts
	// F bool used to determine status of r

	int q, x;
	bool F;

	q = -1;                            /*set q to -1 so when we start our while loop
									   and q gets +1 it will = 0 which we
									   will use to check pcan[0] */

	F = false;						  /* set f to false, this means that
									  r is greater then number in sub count p,*/



	//*******************************SART OF LOOP*********************************

	/*while loop will check if q < t && F == false,
	q is the sub count and t is the length of array, looping will stop once
	q has gone through the array. If F becomes true then r is less then
	sub count value in the array*/

	while (q < t && F == false)
	{

		q = q + 1;                //Increments for next sub count


		/* if r is not bigger then the number in sub count
		p[q] then r is can be entered in the array*/


		if (!(r > p[q]))               /****************START OF R INSERT LOGIC***********/
		{
			F = true;                 // f becomes true indicting that r can be inserted in the array

			if (r != p[q])           /* if r is not = to sub count p[q] then is not a duplicate and
									    we can continue the process of inserting it into the array*/
			{
				x = t;               /*x equle to t because its used to compare in( q > t),
									   once q > t we will know that we have went through the array*/


				//****************START OF SUB COUNT SORTING LOOP***********///

				/* while q >= t sort the array using p[x+1] =p[x] which
				input value of current sub-count into the next sub count.
				De-increment x to read array backwards, t increments so
				once q > t we will know that we have went through the array*/

				while (x >= q)
				{
					p[x + 1] = p[x];
					x = x - 1;
				} //end of while x>=g

				//****************END OF SUB COUNT SORTING LOOP***********/
				t = t + 1;
				p[q] = r;
			} //end of if r!=p[q]

		}

	}
	//**********************END OF LOOP***********************//




	/*if f is false then r is a value bigger then all
	current values in pcan array and pcan size
	must increment by 1 to increase array length to insert r */
	if (F == false)
	{
		t = t + 1;                  // increments size of pcan array by 1
		p[t] = r;                   // inserts r in the end of array
	}
}

/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/






/*===========================================================================================
*******************************|  END OF PROGRAM   |*****************************************
============================================================================================*/