#include "Player.h"
#include <cassert>
#include <algorithn>
#include <vector>

class Simple: public Player
{
private:
    
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

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump);
    
    //TODO Maybe destructor needed
};


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

    if(round == 1){
       int counter = 0;
       for(int i = 0;i < int(hand.size());i++){
           if(hand[i].is_face() and hand[i].is_trump(upcard.get_suit()))
               counter++;
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
       if(counter >= 2){
           order_up_suit = nextSuit;
           return true;
       }
    }

    return false;
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
void Simple::add_and_discard(const Card &upcard){
    //should work.
    std::string trump = upcard.get_suit();

    assert(hand.size() > 1);    
    
	//get the lowest card to remove it
	Card min = hand[0];
	int minIndex = 0;
	
	for (int i = 0; i < hand.size(); i++)
	{
		if (Card_less(hand[i],min,trump))
		{
			min = hand[i];
			minIndex = i;
		}
	}

	hand.erase(hand.begin() + minIndex);

    if(Card_less(upcard, min, trump))
    {
        return;
    }
    
	hand.push_back(upcard);
	
}

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
Card Simple::lead_card(const std::string &trump){

//TODO shits broke
    Card max = hand[0];
    Card maxTrump = hand[0];
    int maxIndex = 0;
    int maxtrmpIndex = 0;
    int numTrumps;

    for(int i = 0; i < int(hand.size()); i++) 
    {
        if(!hand[i].is_trump(trump) and (hand[i] > max))
        {
            max = hand[i];
            maxIndex = i;
        }
        else if (hand[i].is_trump(trump) and (hand[i] > maxTrump))
        {
            maxTrump = hand[i];
            maxtrmpIndex = i;
            numTrumps++;
        }
    }
    

}
        

//REQUIRES Player has at least one card, trump is a valid suit
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
Card Simple::play_card(const Card &led_card, const std::string &trump){
//Untested.

   bool haveLed = false;
   bool haveTrump = false;
   int highIndex = 0;
   Card highCard = hand[0];
   
    //check for the highest ultimate card
    //flag it if there exists a led card in the hand
   for(int i=0; i < int(hand.size()); i++){
       if(Card_less(highCard, hand[i], led_card, trump)){
         highCard = hand[i];
         highIndex = i;
       } 
        if(hand[i].get_suit(trump) == trump) haveTrump = true;
    
        if(hand[i].get_suit(trump) == led_card.get_suit(trump)) haveLed = true;

   }
  
    //if the highest card is a led card play it
    if(highCard.get_suit(trump) == led_card.get_suit(trump))
    {
        hand.erase(hand.begin() + highIndex);
        return highCard;
    }
    
    //if the highest card is a trump card then there are two options:
    //if there is a led card go back and get it
    // if there is no led card, trump should be played
    if(highCard.is_trump(trump))
    {
        if(haveLed)
        { // go back and get the highest led
            highCard = hand[0];
            highIndex = 0;
            for(int i = 0; i < int(hand.size()); i++){
                if(hand[i].get_suit(trump) == trump) continue;
                else{
                    if(Card_less(highCard,hand[i],led_card,trump)){
                        highCard = hand[i];
                        highIndex = i;
                    }
                }
            }
        }
        else
        {
            //play trump
            hand.erase(hand.begin() + highIndex);
            return highCard;
        }
    }
    
    Card leastCard = hand[0];
    int lowestIndex= 0;

    if(!haveLed and !haveTrump)
    {
        //for loop and find least value
        for(int i = 0; i < int(hand.size()); i++)
        {
            if(Card_less(hand[i], leastCard, led_card, trump))
            {
                leastCard = hand[i];
                lowestIndex = i;
            }
        }
        
        hand.erase(hand.begin() + lowestIndex);
        return leastCard;
    }  

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

    //REQUIRES Player has at least one card, trump is a valid suit
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    Card play_card(const Card &led_card, const std::string &trump);

private:

    std::vector<Card> hand;
    std::string name;
};


////////////////////// HUMAN IMPLEMENTATION ////////////////

void Human::add_card(const Card &c)
{
    assert(int(hand.size()) < MAX_HAND_SIZE);

    hand.push_back(c);
}

bool Human::make_trump(const Card &upcard, bool is_dealer,
                int round, std::string &order_up_suit) const
{
    std::string input;
    std::sort(hand.begin(), hand.end());

    for(int i = 0; i < int(hand.size()); i++){
        std::cout << "Human player " << name <<  "\'s hand: ["<<i<<"] "<< hand[i] << std::endl;
    }
    std::cout << "Human player" << name <<", please enter a suit, or \"pass\":" << std:endl;
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
                order_up_suit = SUIT_SPADES;
                break;
            case 'H':
                order_up_suit = SUIT_HEARTS;
                break;
            case 'C':
                order_up_suit = SUIT_CLUBS;
                break;
            case 'D': 
                order_up_suit = SUIT_DIAMONDS;
            default:
                break;
        }
        return true;
    }
    
    
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

