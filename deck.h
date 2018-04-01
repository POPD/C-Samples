#ifndef _DECK_
#define _DECK_

#include "card.h"

class Deck
{
 private:
  Card theDeck[52];
  int currentCard;
 public:
  // Build a proper deck
  Deck();
  // Print the cards remaining in the Deck.
  void Print();

  // Must use time as the random generator seed.
  // Shuffle resets the deck to full
  void Shuffle();


  
  // Is the deck empty?
  bool EmptyDeck();


  
  // Pre-condition: The deck is not empty.
  Card DealACard();


};

#endif
