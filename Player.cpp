#include "Player.h"
#include <cassert>
#include <algorithm>
#include <vector>



static void cardSort(std::vector<Card> &hand, const std::string &trump){
    
    Card temp;    

    for(int i = 0; i<int(hand.size()) - 1;i++){
        
        for(int j = 0; j < int(hand.size()) - i - 1; j++)
        {
            if(Card_less(hand[j], hand[j+1], trump))
            {
                temp = hand[j];
                hand[j] = hand[j + 1];
                hand[j + 1] = temp;
            }
        }    	
	}
}

/////////////////////////// SIMPLE PLAYER CLASS //////////////////////////
class Simple: public Player
{
private:
    //make change it
    std::vector<Card> hand;
    std::string name;

    /* data */
public:
    Simple( const std::string &in_name):
    name(in_name) {}

	//EFFECTS returns player's name
	virtual const std::string & get_name() const { return name; }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand    
    void add_card(const Card &c);

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                int round, std::string &order_up_suit) const;

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard);

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump);

    //Delete this

    void printHand();

    //Delete this

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump);
    
    //TODO Maybe destructor needed
};

void Simple::printHand(){ 
    
    for(int i = 0; i < int(hand.size()); i++){
        std::cout << hand[i] << std::endl;
    }
    std::cout<<std::endl;
}

/////////////////////////// SIMPLE PLAYER IMPLEMENTATION //////////////////////

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand    
void Simple::add_card(const Card &c){
    
    assert(hand.size() < MAX_HAND_SIZE);

    hand.push_back(c);    
}



//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.

//TODO:keep track of round in driver?
bool Simple::make_trump(const Card &upcard, bool is_dealer,
            int round, std::string &order_up_suit) const {

 //HEAVLY Untested
    assert(round == 1 or round == 2);
    bool isFace;
    bool isTrump;
    if(round == 1){
       int counter = 0;
       for(int i = 0;i < int(hand.size());i++){
           isFace = hand[i].is_face();
           isTrump = hand[i].is_trump(upcard.get_suit());
           if(isFace and isTrump)
           {
               counter+=1;
           }
       }
       
       if(counter >= 2){
           order_up_suit = upcard.get_suit();
           return true;
       }
    }
    if(round == 2){
        //IF IT IS THE DEALER DO NOT CONSIDER HAND
        if(is_dealer){
            order_up_suit = Suit_next(upcard.get_suit());
            return true;
        }
        //SCAN HAND FOR 2 OR MORE FACE NEXT CARDS
        int counter = 0;
        std::string nextSuit = Suit_next(upcard.get_suit());
        
        for(int i = 0;i < int(hand.size());i++){
           if((hand[i].is_face() and hand[i].is_trump(nextSuit))){
               counter++;
           }
       }
       if(counter >= 1){
           order_up_suit = nextSuit;
           return true;
       }
    }

    return false;
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void Simple::add_and_discard(const Card &upcard){
    
    std::vector<Card> srtHand = hand;
    srtHand.push_back(upcard);
    
    cardSort(srtHand,upcard.get_suit()); 
    Card smallCard = srtHand[(srtHand.size()-1)];

    if(smallCard == upcard)return;

    srtHand.pop_back();

    hand = srtHand;
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card Simple::lead_card(const std::string &trump){
    
    std::vector<Card> srtHand = hand;
    cardSort(srtHand,trump);
    int highestCardIndex = -1;
    Card playedCard;

    //find the first non-trump card
    //this would be the highest card
    for(int i = 0; i < int(srtHand.size()); i++)
    {
        if(srtHand[i].is_trump(trump)) continue;
        highestCardIndex = i;
        break;
    }
    //if the deck is all trump, then highestcardindex would not
    //be changed, automatically play the highest card because
    // we know that it is trump
    if(highestCardIndex == -1){
        playedCard = srtHand[0];
        srtHand.erase(srtHand.begin());
        hand = srtHand;
        return playedCard;
    }
    //return the highest card, this would be the highest non trump
    // from the earlier for loop
    else{
        playedCard = srtHand[highestCardIndex];
        srtHand.erase(srtHand.begin() + highestCardIndex);
        hand = srtHand;
        return playedCard;
    }
}
        

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
Card Simple::play_card(const Card &led_card, const std::string &trump){
    int highestLedIndex = -1;
    Card playedCard;

    std::vector<Card> srtHand = hand;
    cardSort(srtHand,trump);    
    
    //find the highest led card
    for(int i = 0; i < int(srtHand.size()); i++)
    {
        if(srtHand[i].get_suit(trump) == led_card.get_suit(trump)){
            highestLedIndex = i;
            break;
        }
    }
    //play the highest card
    if(highestLedIndex != -1){
        playedCard = srtHand[highestLedIndex];
        srtHand.erase(srtHand.begin() + highestLedIndex);
        hand = srtHand;
        return playedCard;
    }
    

    playedCard = srtHand[srtHand.size() - 1];
    
  

    srtHand.erase(srtHand.begin() + (int(srtHand.size() - 1)));
    
    hand = srtHand;
    return playedCard;

}

/////////////////////////// HUMAN CLASS ///////////////////////

class Human : public Player
{

public:
    Human (std::string in_name): name(in_name) {}

    //EFFECTS returns player's name
	virtual const std::string & get_name() const { return name; }

    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS  adds Card c to Player's hand    
    void add_card(const Card &c);

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                int round, std::string &order_up_suit) const;

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.
    void add_and_discard(const Card &upcard);
    
    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Leads one Card from Player's hand according to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    Card lead_card(const std::string &trump);

    //DELETE THIS

    void printHand();

    //DELETE THIS

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump);

private:
    std::string name;
    std::vector<Card> hand;
};


////////////////////// HUMAN IMPLEMENTATION ////////////////

static  void printHandSorted(const std::vector<Card> &hand,const Player *player){
    std::vector<Card> sortHand = hand;
    std::sort(sortHand.begin(), sortHand.end());
    for(int i = 0; i < int(sortHand.size()); i++){
        std::cout << "Human player " << *player << 
         "\'s hand: ["<<i<<"] "<< sortHand[i] << std::endl;
    }
}

void Human::add_card(const Card &c)
{
    assert(int(hand.size()) < MAX_HAND_SIZE);

    hand.push_back(c);
}

bool Human::make_trump(const Card &upcard, bool is_dealer,
                int round, std::string &order_up_suit) const
{
    
    std::string input;

    printHandSorted(hand, this);
    
    std::cout << "Human player " << *this 
    <<", please enter a suit, or \"pass\":" << std::endl;
    std::cin >> input;
    if(input == "pass")
    {
        return false;
    }
    else
    {
        switch (input[0])
        {
            case 'S':
                order_up_suit = Card::SUIT_SPADES;
                break;
            case 'H':
                order_up_suit = Card::SUIT_HEARTS;
                break;
            case 'C':
                order_up_suit = Card::SUIT_CLUBS;
                break;
            case 'D': 
                order_up_suit = Card::SUIT_DIAMONDS;
            default:
                break;
        }
        return true;
    }
    
    
}


void Human::add_and_discard(const Card &upcard)
{
    std::sort(hand.begin(), hand.end());
    printHandSorted(hand,this);
    int discard;

    std::cout << "Discard upcard: [-1]\n";
    
    std::cout<< "Human player" << *this << ", please select a card to discard:";
    std::cin >> discard;

    if(discard == -1) return;

    hand.erase(hand.begin() + discard);

    add_card(upcard);


}

Card Human::lead_card(const std::string &trump)
{
    std::sort(hand.begin(), hand.end());
    printHandSorted(hand,this);
    int input;
    Card playedCard;

    std::cout << "Human player "<< *this <<", please select a card:"<< std::endl;
    std::cin >> input;

    playedCard = hand[input];



    hand.erase(hand.begin() + input);
    return playedCard;

       
}

Card Human::play_card(const Card &led_card, const std::string &trump){
    std::sort(hand.begin(), hand.end());
    printHandSorted(hand,this);
    int input;
    Card playedCard;

    std::cout << "Human player "<< *this <<", please select a card:"<< std::endl;
    std::cin >> input;

    playedCard = hand[input];

    hand.erase(hand.begin() + input);
    return playedCard;
    
}


void Human::printHand()
{
    return;
}
//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p){
    
    os << (p.get_name());
    
    return os;
}

//////////////////////// player factory /////////////////////

//  EFFECTS: Returns a pointer to a player with the given name and strategy
	//To create an object that won't go out of scope when the function returns,
	//use "return new Simple(name)" or "return new Human(name)"
	//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {

	if (strategy == "Simple") return new Simple(name);
    if (strategy == "Human") return new Human(name);
	return NULL;
}

