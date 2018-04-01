


#include<iostream>
#include<string>
#include <cstdlib>/* srand, rand */
#include <ctime> /* time */
                  
#include "deck.h"
using namespace std; 

Deck::Deck()
{
// initialize random seed: 
  srand (time(NULL));

  //use sran()%51 ---> 0to51

	Suit theSuit;
	FaceValue theFaceValue;
	int count = 0;
	Card aCard;

	//sets the deck,will creat 52 uniqe card for the constuctor, will be used in theDeck in main,use print fution to know if good
	//add +1 to incremant, then type cast becuse adding + 1 will turn to int

	for(theSuit = Hearts; theSuit <= Spades; theSuit = (Suit)(theSuit + 1))
	{
		for(theFaceValue = Two; theFaceValue <= Ace; theFaceValue  = (FaceValue)(theFaceValue + 1))
		{
			aCard.SetFaceValue(theFaceValue);
			aCard.SetSuit(theSuit);
			theDeck[count]=aCard;
			count ++;
		}
	}

}

//**********************************************************************
 void Deck::Print()
{
	//prints card 52 times
	int i = 0;

	for(i = 0; i < 52; i++)
	{
		theDeck[i].Print();
	}


}

//**********************************************************************	
		
void Deck::Shuffle()
{
	srand (time(NULL));
	int c = 0;
	int random = 0;

	for( c = 0; c <= 52; c++)
	{
		random =rand()%52;
		swap(theDeck[c],theDeck[random]);
	
	}
}
//**********************************************************************
 bool Deck::EmptyDeck()
 {
	 if (currentCard == 52)
		 return true;
	 else
		 return false;
 }

//**********************************************************************

 Card Deck::DealACard()
 {
	 //in main check if deck is empty befor using this,
	 /*
	 Card temp;

	 temp = theDeck[current];
	 current++;
	 return temp;
	 */

	 //int current = 0;

	 Card aCard;
	 aCard = theDeck[currentCard];
	 currentCard++;
	 return aCard;
 }



