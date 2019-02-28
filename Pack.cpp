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
  this->next = 0;
  Card nineSpade(Card::RANK_NINE, Card::SUIT_SPADES); cards[0] = nineSpade;
  Card tenSpace(Card::RANK_TEN, Card::SUIT_SPADES); cards[1] = tenSpace;
  Card jackSpade(Card::RANK_JACK,Card::SUIT_SPADES);cards[2] = jackSpade;
  Card queenSpade(Card::RANK_QUEEN, Card::SUIT_SPADES);cards[3] = queenSpade;
  Card kingSpade(Card::RANK_KING,Card::SUIT_SPADES);cards[4] = kingSpade;
  Card aceSpade(Card::RANK_ACE, Card::SUIT_SPADES);cards[5] = aceSpade;
  Card nineHearts(Card::RANK_NINE, Card::SUIT_HEARTS);cards[6] = nineHearts;
  Card tenHearts(Card::RANK_TEN, Card::SUIT_HEARTS);cards[7] = tenHearts;
  Card jackHearts(Card::RANK_JACK,Card::SUIT_HEARTS);cards[8] = jackHearts;
  Card queenHearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);cards[9] = queenHearts;
  Card kingHearts(Card::RANK_KING,Card::SUIT_HEARTS);cards[10] = kingHearts;
  Card aceHearts(Card::RANK_ACE, Card::SUIT_HEARTS);cards[11] = aceHearts;
  Card nineClubs(Card::RANK_NINE, Card::SUIT_CLUBS);cards[12] = nineClubs;
  Card tenClubs(Card::RANK_TEN, Card::SUIT_CLUBS);cards[13] = tenClubs;
  Card jackClubs(Card::RANK_JACK,Card::SUIT_CLUBS);cards[14] = jackClubs;
  Card queenClubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);cards[15] = queenClubs;
  Card kingClubs(Card::RANK_KING,Card::SUIT_CLUBS);cards[16] = kingClubs;
  Card aceClubs(Card::RANK_ACE, Card::SUIT_CLUBS);cards[17] = aceClubs;
  Card nineDiamonds(Card::RANK_NINE, Card::SUIT_DIAMONDS);cards[18] = nineDiamonds;
  Card tenDiamonds(Card::RANK_TEN, Card::SUIT_DIAMONDS);cards[19] = tenDiamonds;
  Card jackDiamonds(Card::RANK_JACK,Card::SUIT_DIAMONDS);cards[20] = jackDiamonds;
  Card queenDiamonds(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);cards[21] = queenDiamonds;
  Card kingDiamonds(Card::RANK_KING,Card::SUIT_DIAMONDS);cards[22] = kingDiamonds;
  Card aceDiamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);cards[23] = aceDiamonds;
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
  //Puts every even element in its place and every odd element in its place 7 times.
  for(int z = 0; z < 7 ; z++){
    std::array<Card, PACK_SIZE> cpyArray;
    int evensIndex = 12;
    int oddsIndex = 0;
    for(int i = 0; i < PACK_SIZE;i++){
      if( i%2 == 0){
        cpyArray[i] = cards[evensIndex]; 
        evensIndex++;
      }
      else{
        cpyArray[i] = cards[oddsIndex];
        oddsIndex++;
      }
    }
    cards = cpyArray;
  }  
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
	if(this->next == PACK_SIZE) return true;
  else return false;
}

