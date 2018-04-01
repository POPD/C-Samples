/*=============================================================================================
************************************| ID BLOCK |***********************************************
===============================================================================================

Software Designer:  Daric Martin-Lavoie
Course:             420-306-AB ALGORITHM DESIGN section 00001
Deliverable:	    Assignment #1 Version 3 Gap N Twins
Due Date:           September 16, 11:59PM, 2014 

Description         Program runs a odd integer candidate p within a rang of 
					lowest integer to hight integer and finds prime number 
					that are within gap size apart of each other. 
					Program then echo results of two prime values that are
					gap size apart to out put console.

==============================================================================================
********************************| PRELIMINARIES |*********************************************
===============================================================================================*/
#include <iostream>
using namespace std; // For std::string


/*============================================================================================
*******************************| MAIN BLOCK BEGINS |******************************************
==============================================================================================*/
void main()
{

	int  hi;   // odd integer max value of the range
	int  lo;   // odd integer min value of the range 
	int  p;    // integer used to test candidates within range 
	int  f;    // used to find if p is a prime
	int  t;    // used to find if p is a prime
	int  gap;  // integer for jump size,i.e. size of gap between prime twines
	bool jump; // Boolean used to indicate if we jumped



	cout << "This program prints prime twines that are gap size apart with in a range of lowest value to the highest value" << endl << endl;
	cout << "Enter a positive integer for lowest value" << endl;
	cin >> lo;

	cout << "Enter positive integer for the highest value" << endl;
	cin  >> hi;

	cout << "Enter a gap size for the prime twins" << endl;
	cin  >> gap;
	jump = 0;
	p = lo;


	while (p <= hi)  // loop runs Canada p through range Lo to hi
	{
		t = 3;
		f = 1;      


/*============================================================================================
***********************************| SIFTER LOGIC LOOP |**************************************
==============================================================================================*/
		
		while (t*t <= p && f == 1) // is t^2 less then p and is f a factor?
		 {

			if (p%t == 0)          // Dose t divides evenly into p ? if so we have a factor
			{
				f = t;            
				t = p;
			}
			else
			{
				t = t + 2;        
			}

		 }
		
/*===========================================================================================
***********************************| GAP TWIN LOGIC |**************************************** 
==============================================================================================*/
		
			if (f == 1)           // is current value a prime?
			{
				if (jump == 1)    // was previous value a prime? i.e. have we jump?
				{

					//if previous value and current value are both prime we have gap twins
					cout << p - gap << " and " << p << " are Gap " << gap << " Prime Twines " << endl;
					p = p - gap; //rest the gap to find next gap twins,i.e. p jumps back gap times.
					p = p + 2;   //Set odd candidate to find next prime twines
					jump = 0;    //reset jump to false to indicate no prime has been previously found


				}
				else//else current value is prime, set jump to true, jump by gap
				{

					jump = 1;    //set jump to true to indicates a prime value has been found
					p = p + gap; // increment by gap to find next prime that is gap apart

				}
			}
			else //else was previous value prime but current value not prime?
			{
				
				if (jump == 1)  // was previous value a prime? i.e. have we jump?
				{
								
					p = p - gap; //rest the gap to find next gap twins,i.e. p jumps back gap times.
					jump = 0;    //reset jump to show previous value not prime
					p = p + 2;   //Set odd candidate to find next prime twines

				}
				else//else no prime values were found so far
				{

					p = p + 2;   //Set odd candidate to find next prime twines

				}
			}				
		
	}

/*=============================================================================================
*************************************| MAIN BLOCK ENDS |***************************************
===============================================================================================*/

	system("pause");

}

/*=============================================================================================
*************************************| END OF PROGRAM  |***************************************
===============================================================================================*/




