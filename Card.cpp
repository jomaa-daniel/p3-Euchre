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
	if(is_left_bower(trump)){
		return trump;
	}
	else
	{
		return this->get_suit();
	}
}

//EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
bool Card::is_face() const {
	if(this->get_rank() == RANK_JACK) return true;
	else if (this->get_rank() == RANK_QUEEN) return true;
	else if (this->get_rank() == RANK_KING) return true;
	else if (this->get_rank() == RANK_ACE) return true;
	else return false;
}

//REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
bool Card::is_right_bower(const std::string &trump) const {
	if((this->get_rank() == RANK_JACK) && (this->get_suit() == trump)){
		return true;
	}
	else{
		return false;
	}
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit)
{
	std::string next;
	
 if(suit == Card::SUIT_CLUBS) next = Card::SUIT_SPADES;
	else if (suit == Card::SUIT_SPADES) next = Card::SUIT_CLUBS;
	else if (suit == Card::SUIT_HEARTS) next = Card::SUIT_DIAMONDS;
	else if (suit == Card::SUIT_DIAMONDS) next = Card::SUIT_HEARTS;

	return next;
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if card is the Jack of the next suit
bool Card::is_left_bower(const std::string &trump) const {	
	
	if((this->get_rank() == RANK_JACK) && (this->get_suit() == Suit_next(trump))){
		return true;
	}
	else{
		return false;
	}
}

//REQUIRES trump is a valid suit
 //EFFECTS Returns true if the card is a trump card.  All cards of the trump
 // suit are trump cards.  The left bower is also a trump card.
bool Card::is_trump(const std::string &trump) const {
	
	if(is_left_bower(trump)) return true;
	else if	(this->get_suit() == trump) return true;
	else return false;
}

//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs)
{
	int lhIndex = 0;
	int rhIndex = 0;
	//first convert the lhs rank to index
	for(int i = 0; i < NUM_RANKS; i++){
		
		if(lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i])
		{
			lhIndex = i;
		}
		if(rhs.get_rank() == RANK_NAMES_BY_WEIGHT[i])
		{
			rhIndex = i;
		}
	}

	if(lhIndex < rhIndex) return true;
	return false;
	
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs)
{
	int lhsIndex = 0;
	int rhsIndex = 0;
	
	for(int i = 0; i < NUM_RANKS; i++){
		if(lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i])
		lhsIndex = i;
		if(rhs.get_rank() ==RANK_NAMES_BY_WEIGHT[i])
		rhsIndex = i;
	}
	
	if(lhsIndex > rhsIndex)
	return true;

	return false;

}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs)
{
	int lhsIndex = 0;
	int rhsIndex = 0;
	
	for(int i = 0; i < NUM_RANKS; i++){
		if(lhs.get_rank() == RANK_NAMES_BY_WEIGHT[i])
		lhsIndex = i;
		
		if(rhs.get_rank() ==RANK_NAMES_BY_WEIGHT[i])
		rhsIndex = i;
	}
	
	if(lhsIndex == rhsIndex)
		return true;

	return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs)
{
	if(!(lhs == rhs)) return true;

	return false;
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){
	
	os << card.get_rank() << " of " << card.get_suit();

	return os;
}


//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump)
{	
	//check for bowers
	if(a.is_right_bower(trump)) return false;
	if(b.is_right_bower(trump)) return true;
	if(a.is_left_bower(trump)) return false;
	if(b.is_left_bower(trump)) return true;

	//check if ONE is a trump
	if(a.is_trump(trump) && !b.is_trump(trump)) return false;
	if(b.is_trump(trump) && !a.is_trump(trump)) return true;

	//compare the ranks
	if(a < b) return true;
	if(a > b) return false;

	//at this point they are the same rank, possibly the same suit	

	// checking for D>C>H>S
	int aIndex = 0;
	int bIndex = 0;
	
	for(int i = 0; i < NUM_SUITS; i++){
		if(a.get_suit(trump) == SUIT_NAMES_BY_WEIGHT[i])
		aIndex = i;
		else if(b.get_suit(trump) == SUIT_NAMES_BY_WEIGHT[i])
		bIndex = i;
	}

	if(aIndex < bIndex) return true;

	return false;
	
}


bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
		
	if(a == b) return false;

	//check for bowers
	if(a.is_right_bower(trump)) return false;
	if(b.is_right_bower(trump)) return true;
	if(a.is_left_bower(trump)) return false;
	if(b.is_left_bower(trump)) return true;

	//if they are the same suit compare the ranks
	if(a.get_suit() == b.get_suit())
	{
		if(a < b) return true;
		else return false;
	}
	//if one of them is a trump return
	
	if(a.is_trump(trump)) return false;
	if(b.is_trump(trump)) return true;

  //leds
	if(a.get_suit() == led_card.get_suit()) return false;
	if(b.get_suit() == led_card.get_suit()) return true;

	// checking for D>C>H>S
	int aIndex = 0;
	int bIndex = 0;
	
	for(int i = 0; i < NUM_SUITS; i++){
		if(a.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
		aIndex = i;
		else if(b.get_suit() == SUIT_NAMES_BY_WEIGHT[i])
		bIndex = i;
	}

	if(aIndex < bIndex) return true;

	return false;

}

