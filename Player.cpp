#include "Player.h";
#include <cassert>
#include <vector>

class Simple: public Player
{
private:
    
    std::vector<Card> hand;
    std::string name;

    /* data */
public:

    Simple( const std::string &in_name):name(in_name),
		hand(MAX_HAND_SIZE) {}

	//EFFECTS returns player's name
	virtual const std::string & get_name() const;

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
    
    ~Simple();
};

//  EFFECTS: Returns a pointer to a player with the given name and strategy
	//To create an object that won't go out of scope when the function returns,
	//use "return new Simple(name)" or "return new Human(name)"
	//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy) {

	if (strategy == "Simple") return new Simple(name);

	return NULL;
}


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

    assert(round == 1 or round == 2);

    if(round == 1){
       int counter = 0;
       for(int i = 0;i < int(hand.size());i++){
           if(hand[i].is_face() and hand[i].is_trump(upcard.get_suit())
            or hand[i].is_left_bower(upcard.get_suit()) 
            or hand[i].is_right_bower(upcard.get_suit())){
               counter++;
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
           if(hand[i].is_face() and hand[i].is_trump(nextSuit)
            or hand[i].is_left_bower(nextSuit)
            or hand[i].is_right_bower(nextSuit)){
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

    assert(hand.size() > 1);    
    
	//get the lowest card to remove it
	Card min = hand[0];
	int minIndex = 0;
	//note that the removal does not consider trump
	for (int i = 0; i < hand.size(); i++)
	{
		if (min < hand[i])
		{
			min = hand[i];
			minIndex = i;
		}
	}

	//TODO make sure there is no off by one error here
	hand.erase(hand.begin() + minIndex);

	hand.push_back(upcard);
	
}







