
#include<iostream>
#include<string>
#include "deck.h"

using namespace std;

Card::Card()
{
 //calls defult constructor
 //the cards face value wil be ace by defualt, construtor
  faceValue  = Ace;
  //the dard suit will be set to spades by default
  suit = Spades;
}
//has access to privite

///
Card::Card(FaceValue infaceValue, Suit insuit)
{
	
	suit = insuit;
	faceValue = infaceValue;
	
}

FaceValue Card::GetFaceValue()
{
	return faceValue;
}
//**********************************************************************
void Card::SetFaceValue(FaceValue infaceValue)
{
	//use faceValue 
	//aFaceValue is what will be passed in main
	/*Card myCard;
	myCard.faceValue = aFaceValue;*/

	faceValue = infaceValue;
}

//**********************************************************************
 void Card::SetSuit(Suit insuit)
{  
      suit = insuit;
}

//**********************************************************************
  Suit Card::GetSuit()
 {
	 return suit;
 }

//**********************************************************************


//access to privite
bool Card::operator > (Card aCard)
{
	if(faceValue > aCard.faceValue)
		return true;
	else
		return false;
}

bool Card::operator==(Card aCard)
{
	if(faceValue == aCard.faceValue)
		return true;
	else
		return false;
}
 //**********************************************************************

  bool Card::operator<(Card aCard)
 {
	 if(faceValue < aCard.faceValue)
		return true;
	else
		return false;
 }

  void Card::Print()
  {
	  string theface[13] = { "Two", "Three", "Four", "Five", 
		"Six", "Seven", "Eight", "Nine", 
		"Ten", "Jack", "Queen", "King", 
		"Ace"};

	  string thesuit[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};

	  cout << theface[faceValue] << " of " << thesuit[suit] << endl;
  }

   //**********************************************************************

 

  