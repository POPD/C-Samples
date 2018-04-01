/*============================================================================================
************************************| ID BLOCK |**********************************************
==============================================================================================
|Due Date:           10, 14, 2014                                                            |
|Software Designer:  Daric Martin-Lavoie                                                     |
|Course:             420-306-AB ALGORITHM DESIGN section 00001                               |
|Deliverable:	    Assignment #3  Version 5                                                 |
|                                                                                            |
|Description: This Program start by printing two unsorted arrays nam and wght with           |
|		     columns headings and a title.The data of the two arrays nam and wght are then   |
|			 copied into WKnam and WKwght, the program then                                  |
|			 displays a menu containing a list of sorting and search options to the user     |
|			 the menu contains 3 sorts options and one search option, the sort option are    |
|			 Shell Sort, Insert Sort and Selection Sort, user can then sorts the array WKnam |
|			 and WKwght with the chosen sort, the program then displays the sorted arrays    |
|			 WKnam and WKwght. The program accepts string input from user for variable xnam  |
|			 and searches through arrays WKnam the program then generates 1 of 2 possible    |
|			 out put responses depending on whether xnam was fond if found, program echoes   |
|			 the name and wight with the sub count location of the array if not found program|
|			 echoes not found. Program end when user enter an empty string while searching.  |
=============================================================================================
********************************| PRELIMINARIES |********************************************
============================================================================================*/
#pragma warning (disable:4996) //Disables compiler secure CRT functions warning c4996 
#include  <iostream>
#include  <string>
#include  <iomanip>            
using namespace std;
const int LMAX = 100;          //maximum number of name strings in array
const int NMAX = 10;           //maximum size of each name string
const int LSIZE = 20;		   //number of actual name strings in array
/*===========================================================================================
*******************************| FUNCTION PROTOTYPE   |***************************************
============================================================================================*/

// Displays Arrays with title, heading and columns
void OutList(char[][NMAX], int[], string, string, string);

// Displays the  menu for sort and search options
void PutMenu();

// Copies contents of nam & wght into WKnam & WKwght
void CopyList(char[][NMAX], int[], char[][NMAX], int[]);

// Determines and validates the input from user
char GetChoice();

// Shell sorting algorithm, used for sorting WKnam & WKwght
void shellsort(char[][NMAX], int[]);

// selection sort, used for sorting WKnam & WKwght
void selectSort(char[][NMAX], int[]);

// insert sort,  used for sorting WKnam & WKwght
void insertSort(char[][NMAX], int[]);

// Gap List generator, used to generate gap list array for shell sort
int GetGap(int[LSIZE]);

// Binary search, used for searching xnam int array WKnam
int  Bsrc(char[][NMAX], char[]);

/*===========================================================================================
*******************************| MAIN BLOCK BEGINS |*****************************************
============================================================================================*/
int main()
{
 char title[50] = "UNSORTED ARRAY DATA";//Display output of title for  array out put lists
 char h1[10] = "NAMES";       //Header title for out put of names arrays
 char h2[10] = "WEIGHTS";     //Out put of columns title of weights arrays 
 int  position = 0;           //Notes the location of xnam when found in the array
 bool aChoice = false;        //Verify if user is done making choices or not
 bool sorted = false;         //Verify that the WK arrays have been sorted
 bool doneSearch = false;     //Verify that user is done searching
 char WKnam[LMAX][NMAX];      //Copie nam array,keeps nam untouched after sort
 int  WKwght[LMAX];           //Copie wght array,keeps nam untouched after sort
 int  gapList[LSIZE];         //Generate an array of gaps for shell sort function
 char xnam[LSIZE];            //The string input from user.
 char st;                     //The input option from user 

	//array for list of names
	char nam[LMAX][NMAX] = { "wendy", "ellen", "freddy", "tom", "susan",
		"dick", "harry", "aloysius", "zelda", "sammy",
		"mary", "hortense", "georgie", "ada", "daisy",
		"paula", "alexander", "louis", "fiona", "bessie" };

	//array of weights corresponding to list of names
	int wght[LMAX] = { 120, 115, 195, 235, 138, 177, 163, 150, 128, 142,
		118, 134, 255, 140, 121, 108, 170, 225, 132, 148 };

	CopyList(WKnam, WKwght, nam, wght);    /* Copies the contents of nam & wght 
										      arrays into WKnam & WKwght */ 

	OutList(WKnam, WKwght, title, h1, h2); /* OutList echos The WKnam & WKwght with a title
										      and a headings for names and weights */

	GetGap(gapList); //GetGap retrieves the size of gapes for shell sort	
	
	while (1)        
	{
		system("pause");
		PutMenu();    //PutMenu will clear screen and echoes menu of options to the screen
		st = GetChoice(); /* ChooseSort accepts valid input from the keyboard and verifies
						     then stores the input into st  */ 

		fflush(stdin); //Impotent clear buffer, remove the last key press
		switch (st)
		{
		 case '1':
			shellsort(WKnam, WKwght); //Shell sorts WKnam & WKwght 
			//Echoes sorted arrays & shell sorted title
			OutList(WKnam, WKwght, "SHELL SHORTED ARRAY", h1, h2);
			sorted = true; 
			break;   //Indicates that at least 1 sort has been done
		 case '2':
			selectSort(WKnam, WKwght);   //Select sorts WKnam & WKwght arrays
			//Out puts sorted arrays & selection sorted title
			OutList(WKnam, WKwght, "SELECTTION SHORTED ARRAY", h1, h2);
			sorted = true;
			break;
		 case '3':
			insertSort(WKnam, WKwght); // Insert sorts WKnam & WKwght arrays
			//Out puts sorted arrays & insert sorted title
			OutList(WKnam, WKwght, "INSERT SHORTED ARRAY", h1, h2);
			sorted = true;
			break;
		 case '4':                   /*********Start of Search logic***************/
			if (sorted == true)
			{
				printf("who do you want to find  \n");
				fflush(stdin); //Clears buffer for gets();
				gets(xnam);
				while (1)                   
				{
					if (xnam[0] == 0)  //Did user input nothing? If so end program
					{        		   //User done searching & ends program
						return (0);
					}

					for (int i = 0; i < LSIZE; i++)
					{
					 xnam[i] = tolower(xnam[i]);//Lower cases all elements to match array
					}
					 //Function returns 1 if xnam was found and -1 if not found
					position = Bsrc(WKnam, xnam);                

					if (position >= 0)
					{
						printf("%s was found at position %d and the body weight is %d "
							    "\n", xnam, position, WKwght[position]);
					}
					else if (position == -1)
					{
						printf( "%s was not found \n", xnam);
					}

					printf("Who do you want to find next (enter nothing to stop) \n");
					fflush(stdin);
					gets(xnam);

				}//End of while
			}
			else //Validates if user has done a sort before searching
			{                   
				system("CLS");
				printf(" you must sort the array before searching for a name \n");
			}
			  break;
		}//End of switch
	}
}//End of main
/*===========================================================================================
*******************************|  MAIN BLOCK ENDS  |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| OUT LIST FUNCTION |*****************************************
============================================================================================*/
/*******************************************************************************************\
+								     Array Display                                          +
+                                                                                           +
+					Function echoes to screen a title with two headings                     +
+						along with the contents of two arrays                               +
+						   the tile display C-style strings,                                +
+																                            +
+											                                                +
\*******************************************************************************************/
void OutList(char WKnam[][NMAX], int WKwght[], string title, string h1, string h2)
{
	cout << title << endl << endl;
	cout << setw(12) << h1 << setw(12) << h2 << endl << endl;

	for (int j = 0; j<LSIZE; j++)  //Display name strings & corresponding weights

		cout << setw(12) << WKnam[j] << setw(12) << WKwght[j] << endl;

	cout << endl << endl;
}
/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| PUT MENU FUNCTION |*****************************************
============================================================================================*/
/*******************************************************************************************\
+								Menu Display Logic                                          +
+					 Function clears the screen and then out puts                           +
+					 4 options, 3 of them being sorts and 1 being                           +
+					 a search, user is given the option of Shell Sorting,                   +
+					 Selection Sorting, Insert sorting and searching in                     +
+					 WKnam and WKwght arrays.                                               +
\*******************************************************************************************/
void PutMenu()
{
	printf(" OPTIONS \n");
	printf("**********\n");
	printf("1:shell\n");
	printf("2:selection\n");
	printf("3:insert\n");
	printf("4:do search\n");
}

/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| GETCHOICE FUNCTION	|****************************************
============================================================================================*/
/*******************************************************************************************\
+					            Get user Choice Logic                                       +
+                                                                                           +
+                        Function gets a choice from the user                               +
+					        function  validates the choice                                  +
+							if choice is invalid ask again                                  +
+						     if valid return user choice                                    +
+																		                    +
+											                                                +
\*******************************************************************************************/
char GetChoice()
{
	char choice =' ';                 //Char used to store user input for option
	bool valide = false;              //Flag for checking if input valid 

	fflush(stdin);
	printf("Choose a option by number \n");
	scanf("%c", &choice);
	
	while (valide == false)          
	{
		if (choice > '4' || choice < '1')  //is Input between 1 to 4?
		{
			cout << "invalid answer, a valid option is 1 to 4" << endl;
			cin >> choice;
		}
		else
		{
			valide = true;         
		}
	}

	return choice;
}

/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| COPY LIST FUNCTION |****************************************
============================================================================================*/
/*******************************************************************************************\
+								                                                            +
+					             CopyList Logic                                             +
+					Function copies nam and wght array into 								+
+				WKnam and WKwght array, this is to keep original data                       +
+           nam and wght untouched, WKnam and WKwght will later be sorted.                  +
+																		                    +
+											                                                +
\*******************************************************************************************/
void CopyList(char WKnam[][NMAX], int WKwght[], char nam[][NMAX], int wght[])
{
	for (int i = 0; i < LSIZE; i++)  //Runs through every sub count
	{
		strcpy(WKnam[i], nam[i]);   //Copies nam sub-count data into WKnam sub-counts
		WKwght[i] = wght[i];        //Copies wght sub-count data into WKwght sub-counts
	}
}
/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| GET GAP FUNCTION  |*****************************************
============================================================================================*/
/*******************************************************************************************\
+						Donald Knuth Optimal Gaps Algorithm                                 +
+                                                                                           +
+		     generates an optimal set of gaps for the Shell Sort to follow                  +
+            subscripts of array-elements to be sorted are within a range of                +
+       subscript low to subscript high. In our case low = 0 and high = LSIZE – 1           +
+																                            +
+											                                                +
\*******************************************************************************************/
int GetGap(int gaps[LSIZE])
{
	int gap, pos = 0, high, low, numgaps = 0;
	gap = 1;
	pos = 0;
	low = 0;                
	high = LSIZE - 1;             //Actual amount of strings array, 

	while (gap <(high - low) + 1) // while gap less then amount actual amount names in array
	{
		gaps[pos] = gap;
		gap = gap * 3;
		pos = pos + 1;
		numgaps = pos - 1;
	}

	return numgaps;
}
/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| SHELL SORT FUNCTION |***************************************
============================================================================================*/
/*******************************************************************************************\
+	                              Shell Sort Logic                                          +
+                                                                                           +
+         This function sort successive sub-arrays of j whose elements are				    +
+         gap units apart. The gap size is obtained from the array gap list				    +
+		  Successive smaller values of gap are used until the finale gap size               +
+                is reached. Sort is done in ascending order                                +
+											                                                +
\*******************************************************************************************/
void shellsort(char x[][NMAX], int a[])
{
	int numgaps;         //Amount of gaps from gapList
	bool found = false;  //Boolean finds if current value is greater then value gap apart
	int gap;             //Size of the gap
	int b;               //Subscript of current weight
	int j;               //Counter for current index
	int k;               //Sub-count that is gap apart of current index
	int i;               //Sub-count of gap from gapList 
	char y[NMAX];        //Name index to be compared
	int n = LSIZE;
	int gapList[LSIZE];

	numgaps = GetGap(gapList); //Get number of gaps
	i = numgaps - 1;           //Size of gap array

	do
	{
		gap = gapList[i];     
		j = gap;              //j index starts gap apart of index [0]
		do
		{
			strcpy(y, x[j]);          //y gets current nam index gap apart of index[0]
			b = a[j];                 //b gets current weight index gap apart of index[0]
			k = j - gap;              //k index is set gap size amount before j
			found = false;

			while (k >= 0 && found == false) 
			{

				if (strcmp(y, x[k]) < 0)   //Dose y ranks earlier then x in alphabetic system?
				{
					strcpy(x[k + gap], x[k]); //Swaps the names that are gap size apart
					a[k + gap] = a[k];        //Swaps the weights that are gap size apart
					k = k - gap;              //Move index back by gap size 

				}
				else
				{
					found = true;
				}
			}

			strcpy(x[k + gap], y); //Swap current name
			a[k + gap] = b;        //Swap current weight 
			j = j + 1;             //Increment to set next index of (y,b)


		} while (j <= n - 1);  //Re-loop if current index <=actual size of names in array?

		i = i - 1;             //Decrement for next gap index

	} while (i >= 0);          //Re-loop while gapList has gaps left to use

}
/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| SELECTION SORT FUNTION	|************************************
============================================================================================*/
/*******************************************************************************************\
+		                     Selection Sort Logic				                            +
+                                                                                           +
+					      Function sorts in ascending order                                 +
+			finds the larges value and swaps its index with the value                       +
+           at the end of the array then decrements search length to make a new end index   +
+			for next largest value found. Finds the next largest value and repeats the      +
+			process swapping the largest found value with the new end of array              +
+			index and then repeats reduction of array search length for new end index       +
+			algorithm stops when new end index is at index[0]								+
+											                                                +
\*******************************************************************************************/
void selectSort(char x[][NMAX], int a[])
{
	char lg[NMAX];  //Copy data from a sub-counts
	int  ag;        //Copy data from x sub-counts
	int were = 0;   //Position of the smaller value compared to the index value
	int i = 0;      //Smallest value,  
	int j = 0;      //Counter for index
	int n = LSIZE;  //Size of the array

	i = n - 1;      //Array size, [0] not included
	do
	{
		strcpy(lg, x[0]);  //Copies first name into lg & amused to be smallest value
		ag = a[0];         //Copies first Wight into lg & amused to be smallest value
		were = 0;          //Sets swap, were is the value of subscript that swap will happen
		j = 1;             //Starting index position 

		do
		{
			if (strcmp(x[j], lg) > 0)  //Dose x ranks later then lg in alphabetic system? 
			{
				strcpy(lg, x[j]);      //lg gets x[j],amused t be smallest value;
				ag = a[j];             //lg gets x[j],amused t be smallest value;        
				were = j;              //Keeps track of last swap position
			}
			j = j + 1;              //Increments j for next position
		} while (j <= i);           //While j not bigger then array size

		strcpy(x[were], x[i]);     //copies x[i] in x[were] creating a bigger value in x[i]
		a[were] = a[i];            //copies a[i] in a[were] creating a bigger value in a[i]

		strcpy(x[i], lg);         //x[i] becomes smaller then previous x[i]                
		a[i] = ag;                //a[i] becomes smaller then previous a[i] 
		i = i - 1;                //Decrease array size ever time a swap happens

	} while (i > 0);              //Re-lops till array size is zero

}

/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
******************************| INSERTION SORT FUCTION |*************************************
============================================================================================*/
/*******************************************************************************************\
+								 Insertion sort Logic                                       +
+					                                                                        +
+	      Function read array from left to right with and compares current				    +
+		  index value with previous index value, if current index value is less then        +
+         previous index value then the two indexes get swap and current index              +
+		  is decremented, if the current index value less then the previous index value     +
+		  the algorithm dose not swap and keeps current index value as it is and increments +
+		  position of current index and re-loops the search and compare, algorithm stops    +
+		  when current index counter is equal to the last index of array.                   +
+											                                                +
\*******************************************************************************************/
void insertSort(char x[][NMAX], int a[])
{
	int k;               //Index of current value 
	int n;               //Actual amount of names in array
	int i;               //Comparison index the value to be compared to current index
	bool found = false;  //Flag for checking if current index is less then comparison index
	char y[NMAX];        //Current name value
	int  l;              //Current weight value


	n = LSIZE;                    
	k = 1;              //staring index[1] for current value

	do
	{
		strcpy(y, x[k]); //copy current name value 
		l = a[k];        //copy current weight value
		i = k - 1;       //set position of comparison index
		found = false;   

		while (i >= 0 && found == false)
		{
			if (strcmp(y, x[i]) < 0)    //Dose y ranks earlier then x in alphabetic system?
			{
				strcpy(x[i + 1], x[i]); //Swaps the names 
				a[i + 1] = a[i];        //Swaps the weights 
				i = i - 1;              //comparison Index moves back for next comparison 
			}
			else
			{
				found = true;
			}

		}//end of while

		strcpy(x[i + 1], y);          //Swaps the current name
		a[i + 1] = l;                 //Swaps the current weights
		k = k + 1;                    //Increment current index for next comparison

	} while (k <= n - 1);             //Check if k is less then number of strings in array

}
/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| BINARY SEARCH FUNCTION |************************************
============================================================================================*/
/*******************************************************************************************\
+								                                                            +
+					         Binary Search Logic                                            +
+	   Function searches for xnam in WKnam array, search logic starts the position in       +
+	   the middle of the array,if xnam is less then middle value then new middle position   +
+	   will move to the left of the array, else new middle position will move to            +
+	   the right array, every time a new position is created  array is split in half,       +
+	   if xnam is found then function return 1 else if not fund it return -1.               +
+																                            +
+											                                                +
\*******************************************************************************************/
int Bsrc(char x[][NMAX], char xn[])
{
	int lsearch;        // Indicates found or not found for search result
	int low;            // Min search size      
	int high;           // Max search size      
	int n = LSIZE;      // Size of array
	int mid;            // Middle position, reduces array by half
	bool found = false; // Indicates that we have not found x nam

	lsearch = -1;       //Returned value, if -1 means we did not find xnam,
	low = 0;            //Sets lowers value
	high = n - 1;       //Sets highest value

	while (low <= high)
	{
		mid = ((low + high) / 2);    //Cuts array in two

		if (strcmp(xn, x[mid]) == 0) //Is xn the equal to x?
		{
			found = true;
			lsearch = mid;       //xnam position found, a position will be returned
			low = n;             //low becomes > high  then breaks the while loop
		}
		else if (strcmp(xn, x[mid]) < 0)//Dose xn ranks earlier then x in alphabetic system?
		{
			high = mid - 1;             //Cuts out not needed par of the array, lowers the max
		}
		else if (strcmp(xn, x[mid]) > 0)//Dose xn ranks later then x in alphabetic system?
		{
			low = mid + 1;           //Cuts out not needed par of the array, increases the min
		}
	}

	return lsearch;                 //Returns postilion found, else -1 if not found
}

/*===========================================================================================
*******************************| END OF FUNCTION   |*****************************************
============================================================================================*/


/*===========================================================================================
*******************************| END OF PROGRAM   |*****************************************
============================================================================================*/

