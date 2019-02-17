#include "Pack.h"
#include <cassert>
#include "Card.h"


// EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
  //TODO check to makes sure that there are no memory leaks when creating
  // card objects  
  this->next = 0;

  Card nineSpade(RANK_NINE, SUIT_SPADES); 
  cards[0] = nineSpade;
  Card tenSpace(RANK_TEN, SUIT_SPADES); 
  cards[1] = tenSpace;
  Card jackSpade(RANK_JACK,SUIT_SPADES);
  cards[2] = jackSpade;
  Card queenSpade(RANK_QUEEN, SUIT_SPADE);
  card[3] = queenSpade;
  Card kingSpade(RANK_KING,SUIT_SPADES);
  card[4] = kingSpade;
  Card aceSpade(RANK_ACE, SUIT_SPADE);
  card[5] = aceSpade;

  Card nineHearts(RANK_NINE, SUIT_HEARTS);
  cards[6] = nineHearts;
  Card tenHearts(RANK_TEN, SUIT_HEARTS);
  cards[7] = tenHearts;
  Card jackHearts(RANK_JACK,SUIT_HEARTS);
  cards[8] = jackHearts;
  Card queenHearts(RANK_QUEEN, SUIT_HEARTS);
  cards[9] = queenHearts;
  Card kingHearts(RANK_KING,SUIT_HEARTS);
  cards[10] = kingHearts;
  Card aceHearts(RANK_ACE, SUIT_HEARTS);
  cards[11] = aceHearts;

  Card nineClubs(RANK_NINE, SUIT_CLUBS);
  cards[12] = nineClubs;
  Card tenClubs(RANK_TEN, SUIT_CLUBS);
  cards[13] = tenClubs;
  Card jackClubs(RANK_JACK,SUIT_CLUBS);
  cards[14] = jackClubs;
  Card queenClubs(RANK_QUEEN, SUIT_CLUBS);
  cards[15] = queenClubs;
  Card kingClubs(RANK_KING,SUIT_CLUBS);
  cards[16] = kingClubs;
  Card aceClubs(RANK_ACE, SUIT_CLUBS);
  cards[17] = aceClubs;

  Card nineDiamonds(RANK_NINE, SUIT_DIAMONDS);
  card[18] = nineDiamonds;
  Card tenDiamonds(RANK_TEN, SUIT_DIAMONDS);
  card[19] = tenDiamonds;
  Card jackDiamonds(RANK_JACK,SUIT_DIAMONDS);
  card[20] = jackDiamonds;
  Card queenDiamonds(RANK_QUEEN, SUIT_DIAMONDS);
  card[21] = queenDiamonds;
  Card kingDiamonds(RANK_KING,SUIT_DIAMONDS);
  card[22] = kingDiamonds;
  Card aceDiamonds(RANK_ACE, SUIT_DIAMONDS);
  card[23] = aceDiamonds;
}

// REQUIRES: pack_input contains a representation of a Pack in the
//           format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {

  std::string rank, trash, suit;
  this->next = 0;  
  int i = 0;

  while(pack_input >> rank >> trash >> suit)
  {
    Card card(rank, suit);
    cards[i] = card;
    i++;
  }
}

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
	return cards[next++];  
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
	this->next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
  
  //TODO make sure there are deep copies

  const int SEVEN = 7;
  std::array<Card, PACK_SIZE> cpyArray;

  int i = 0;
  int j = 11;

  for(int seven = 0; i < SEVEN; seven++){

    i = 0;
    j = 11;
  
    for(int k = 0; k < cpyArray.size(); k+=2){

      cpyArray[k] = cards[j];
      cpyArray[k + 1] = cards[i];

      i++;
      j++;

    }
    this->cards = cpyArray;
  }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
	if(this->next == PACK_SIZE) return true;
  else return false;
}

