// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

const std::string SMPL = "Simple";


void cardSort(std::vector<Card> &hand, std::string &trump){
    
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

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST(test_add_card) {

	Player *simple = Player_factory("BOT", SMPL);
	//this would be a two of spades
	Card card;

	simple->add_card(card);
	
	delete simple;

	//use hearts as an example trump
//	play_card(card, "Hearts");
}

TEST(test_make_trump_round1_nondealer_ordrup) {
	//this is called upcasting
	Player *simple = Player_factory("BOT", SMPL);

	Card ace_spades("Ace", "Spades");
	Card jack_diamonds("Jack", "Diamonds");
	Card ace_hearts("Ace", "Hearts");
	Card nine_clubs("Nine", "Clubs");
	Card jack_spades("Jack", "Spades");

	
	//create a player without 2 of same suit
	simple->add_card(ace_spades);
	simple->add_card(jack_diamonds);
	simple->add_card(ace_hearts);
	simple->add_card(nine_clubs);
	simple->add_card(jack_spades);

	
	Card upcard("King", "Spades");

	string order_up_suit;

	ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
	ASSERT_EQUAL(order_up_suit, "Spades");
	delete simple;
}

TEST(test_sorting_function){
	
	Card nine_clubs("Queen", "Diamonds");
	Card jack_diamonds("Jack", "Hearts");
	Card ace_hearts("King", "Hearts");
	Card ace_spades("Jack", "Diamonds");
	Card jack_spades("King", "Spades");


	std::vector<Card> hand;
	hand.push_back(ace_spades);
	hand.push_back(jack_diamonds);
	hand.push_back(ace_hearts);
	hand.push_back(nine_clubs);
	hand.push_back(jack_spades);

	std::string trump = "Hearts";

	for(int i = 0; i<int(hand.size());i++){
	std::cout << hand[i] << std::endl;
	}

	cardSort(hand, trump);

	// for(int i = 0; i<int(hand.size());i++){
	// std::cout << hand[i] << std::endl;
	// }
}
// Add more tests here

TEST_MAIN()
