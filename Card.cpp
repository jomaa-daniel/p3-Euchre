#include "Card.h"
#include <cassert>
//CARD CONSTRUCTOR
 //EFFECTS Initializes Card to the Two of Spades
Card::Card() {
	rank = RANK_TWO;
	suit = SUIT_SPADES;
}

//REQUIRES rank is one of "Two", "Three", "Four", "Five", "Six", "Seven",
//  "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"
//  suit is one of "Spades", "Hearts", "Clubs", "Diamonds"
//EFFECTS Initializes Card to specified rank and suit
Card::Card(const std::string &rank_in, const std::string &suit_in) {
	rank = rank_in;
	suit = suit_in;
}

//REQUIRES trump is a valid suit
 //EFFECTS Returns the suit
 //HINT: the left bower is the trump suit!
std::string Card::get_suit() const {
	return suit;
}

std::string Card::get_rank() const {
	return rank;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns the suit
//HINT: the left bower is the trump suit!
std::string Card::get_suit(const std::string &trump) const {
	assert(false);
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
	assert(false);
}

//REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
	assert(false);
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {
	assert(false);
}

//REQUIRES trump is a valid suit
 //EFFECTS Returns true if the card is a trump card.  All cards of the trump
 // suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
	assert(false);
}