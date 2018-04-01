/*
daric Martin-Lavoir
1102764
26-4-2013

Program Simulates a 1 on 1 Poker game, program takes in a bet, program deals 5 cards , 
discards up to 4 cards, program then evluates hands and evaluats a winner and adds amount of bet won or loos.
*/

#include<iostream>
#include<string>
#include"deck.h"
using namespace std;

enum Rank {Nothing, Pair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush};

int GetBet(int);
void DealAHand(Deck &, Card[]);
void PrintHand(Card[]);
void DiscardAndRedeal(Deck &, Card[]);
void PrintHandRank(Rank);
int GetWinnings(Rank, int);
Rank EvaluateHand(Card[]);

void main()
{
	//calls default constructor, creat a constuctor, constucter creats a defult card,defualt is ace and spades for some resone
	/* Card myCard;
	myCard.Print();

	Card myCard1;
	Card myCard2(Ten,Hearts);

	cout << myCard.GetFaceValue;
	myCard.SetFaceValue(Nine);
	myCard.Print();

	if(myCard1 > myCard2)
		cout <<"Player 1 wins";
	else if(myCard1 == myCard2)
		cout << "Its a Tie";
	*/
	
	Card Hand[5];
	int BankRoll = 1000;
	int bet = 0;
	Deck theDeck;
	theDeck.Shuffle();
	Rank theRank;
	int won;

	
	 while(BankRoll > 0)
	 {
         bet = GetBet(BankRoll);
		 BankRoll -= bet;
		 theDeck.Shuffle();
		 DealAHand(theDeck, Hand); 
		 DiscardAndRedeal(theDeck, Hand); 
		 theRank = EvaluateHand(Hand);
		 PrintHandRank(theRank);
		 won = GetWinnings(theRank, bet);
		 BankRoll += (won + bet);
	 }

	 cout << endl;
	 cout << " you lost all your mony, pleas come again and loose all your mony" << endl;
	 system("pause");
	 
}


 int GetBet(int BankRoll)
 {
	 int bet;
	 while (true)
	 {
       cout <<" you have " << BankRoll << " Left";
	   cout << "How much would u like to bet: ";
	   cin  >> bet;

	   while(bet > BankRoll)
	   {
		   cout << " You dont have that much pleas enter a lower bet"<< endl;
		   cin >> bet;
		   cout << bet << endl;
	   }
	   if(bet <= BankRoll)
		 break;
      }
	 return bet;
 }
		 

 void DealAHand(Deck &theDeck, Card Hand[])
 {
	 for(int c =0; c <5; c++)
	 {
		 Hand[c] = theDeck.DealACard();
	 }
 }
		 

void DiscardAndRedeal(Deck &theDeck, Card Hand[])
{
	bool dis[5] = {false,false,false,false,false};
	bool ans = true;
	int a;
	int num = 0;
	int rang = 0;
	int disCard = 0;
	int l = 4;

	while(ans == true)
	{
		for(int i = 0; i < 5; i++)
		{
		  cout << i+1 <<":";
		   Hand[i].Print();
		}
		cout << endl;

	  cout << "Would you like to discard a card(1 for yes pr 0 for no)" << endl;
	  cin >> a;

	 if( a == 1)
	 {
		 ans = true;
	 }
	 else
	 {
		 ans = false;
		 break;
	 }

	  while( num <5)
	  {
		cout << "witch card do you want to dicard(1 to 5) 0 to stop, You can discard " <<l << " More Cards" << endl;
		cin >> disCard;
		//use an if loop to check all condition are true
		//this also dose noth constinly ask the user for stuff

		 if(disCard < 0 || disCard > 5)
		 {
			cout << "error out of rang"<<endl;
		 }
		 else if(disCard == 0 )
		 {
			ans = false;
			break;
		 }
		else if(dis[disCard - 1] == true)
		{
		  cout << "error you allready discarded this" << endl <<endl;
		}
		else 
		{
				dis[disCard - 1] = true;
				 l --;
				num ++;
	     }

	    if(num == 4)
			ans = false;
		 break;
	  }
   }

	   for(int c =0; c < 5; c++)
	    {
		   if(dis[c] == true)
		   Hand[c] = theDeck.DealACard();
	    }

	   cout << " this is your hand" <<endl;
	   cout << endl;
	   for(int c = 0; c <5; c++)
	   {
		cout << c + 1 <<":";
		
		Hand[c].Print();
	   }
	  
}

Rank EvaluateHand(Card Hand[])
{
	enum Rank;
	bool aHi             = false;
	bool straight        = false;
	bool flush           = false;
	bool fullHouse	     = false;
	bool fourOfAKind     = false;
	bool straightFlush   = false;
	int suit[4]  = {0};
	int face[13] = {0};
	int dub[3]   = {0};
	int w =0;

	//recordes value of cards in array, face value in face and suit value in suit
	for(int c =0; c < 5; c++)
	{
		 face[Hand[c].GetFaceValue()]++;
	     suit[Hand[c].GetSuit()]++;
	}

	//checks for the pairs
	for ( int i = 0; i < 13; i++ )
	{
		if(face[i] == 2)
		{
			dub[0] += 1;
		}
		else if(face[i] == 3)
		{
			dub[1] += 1;
		}
		else if(face[i] == 4)
		{
			dub[2] += 1;
		}
		else
		{		}
	}

    //checks for the straight
	for(int i = 0; i < 9; i++)
	{
		if(face[i] == 1 && face[i+1 ] == 1 && face[i+2] ==1 && face[i+3] == 1 && face[i+4] == 1 )
		{
			 straight = true;
		}

	}

	for(int i = 0; i <5; i++)
	{
		// checks if all suit are same for a flush
		if(suit[i] == 5 )
		{
			flush = true;
		}
	}

	    //checks for aHi
	    w = 8;
	  if(face[w] == 1 && face[w+1] == 1 && face[w+2] == 1 && face[w+3] && face[w+4] == 1)
		{
			 aHi = true;
		}


	if(flush == true && straight == true && aHi == true)
	{
		return RoyalFlush;
	}
	else if(flush == true && straight == true)
	{
		return StraightFlush;
	}
	else if(dub[2] == 1 )
	{
	   return FourOfAKind;
	}
	else if(dub[1] ==1 && dub[0] ==1 )
	{
		return  FullHouse;
	}
	else if(flush == true)
	{
		return Flush;
	}
	else if(straight == true)
	{
		return Straight;
	}
	else if(dub[1] == 1) 
	{
		return ThreeOfAKind;

	}
	else if(dub[0] == 2) 
	{
		return TwoPair;
	}
	else if(dub[0] == 1 && (face[9] == 1 || face[10] == 1 || face[11] == 1  || face[12] == 1) )
	{
		return  Pair;
	}
	else
	{
		return Nothing;
	}
}

 void PrintHandRank(Rank theRank)
 {

	 string aRank[] = {"Nothing", "Pair", "TwoPair", "ThreeOfAKind", "Straight", "Flush", "FullHouse", "FourOfAKind", "StraightFlush", "RoyalFlush"};
	 cout << aRank[theRank] << endl;
 }
	
int GetWinnings(Rank theRank, int bet)
{
	int win = 0;

	//{Nothing, Pair, TwoPair, ThreeOfAKind, Straight, Flush, FullHouse, FourOfAKind, StraightFlush, RoyalFlush}
	if(theRank == RoyalFlush)
	{
		win = bet * 250;
	}
	else if(theRank == StraightFlush)
	{
		win = bet * 50;
	}
	else if(theRank == FourOfAKind)
	{
		win = bet * 25;
	}
	else if(theRank ==FullHouse)
	{
		win = bet * 9;
	}
	else if(theRank == Flush)
	{
		win = bet * 6;
	}
	else if(theRank == Straight)
	{
		win = bet * 4;
	}
	else if(theRank ==  ThreeOfAKind)
	{
		win = bet * 3;
	}
	else if(theRank ==  TwoPair)
	{
		win = bet * 2;
	}
	else if(theRank ==  Pair)
	{
		win = bet * 1;
	}
	else
	{
		return win;
	}
	
	return win;
}




