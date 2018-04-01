/*============================================================================================================
													  ID BLOCK
==============================================================================================================

Software Designer:  Daric Martin-Lavoie
Due Date:           September 16, 2014
Deliverable:	    Assignment #1 Version 2 Sifter     

Description         Program runs candidate p from variable
					lo to variable hi and  finds prime numbers and factors
					then echoes results to out put console.

==================================================================================================================
												   PRELIMINARIES
/*================================================================================================================*/
#include <iostream>
using namespace std;

/*================================================================================================================
												  MAIN BLOCK BEGINS
/*================================================================================================================*/

void main()
{

	int hi, lo, p, f, t;

	cout << "Program prints all prime numbers and factors from the lowest value to the highest value" << endl << endl;
	cout << "Enter a positive integer lowest value" << endl;
	cin >> lo;

	cout << "Enter positive integer for the highest value" << endl;
	cin >> hi;

	p = lo;

/*==============================================================================================================
												  SIFTER LOGIC
================================================================================================================*/

	while (p <= hi)                // runs p through range of Lo to hi
	{
		t = 3;
		f = 1;

		while (t*t <= p && f == 1) // is t^2 less then p and is f a factor
		{

			if (p%t == 0)          // verifies if t divides evenly into p, if so we have a factor
			{
				f = t;
				t = p;
			}
			else
			{
				t = t + 2;
			}


		}

/*==============================================================================================================
										PRIME AND FACTOR OUT PUT BLOCK
================================================================================================================*/

		//prints out p as a prime if f = 1 else prints out p as a factor were f divides into p
		if (f == 1)
		{
			cout << p << " is Prime" << endl << endl;
		}
		else
		{
			cout << f << " Divides " << p << endl << endl;;
		}

		p = p + 2;

	}

	system("pause");


/*==============================================================================================================
											MAIN BLOCK ENDS
================================================================================================================*/

}


