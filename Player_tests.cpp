// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

const std::string SMPL = "Simple";




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


TEST(test_simple_Constructor){
	Player *simple = Player_factory("Sally", SMPL);
	ASSERT_EQUAL(simple->get_name(),"Sally");
	delete simple;
}


TEST(test_simple_add_card)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card two_spades;
	Card jack_spades("Jack", "Spades");
	simple->add_card(two_spades);
	

	ASSERT_EQUAL(simple->play_card(jack_spades,"Hearts"),two_spades);
	delete simple;
}

TEST(test_simple_make_trump)
{
	
}

// TEST(test_simple_add_and_discard){
// 	Player *simple = Player_factory("Sally", SMPL);
	
// 	Card two_spades;
// 	Card jack_hearts("Jack", "Hearts");
// 	Card queen_diamonds("Queen", "Diamonds");
// 	Card king_diamonds("King", "Diamonds");
// 	Card nine_hearts("Nine", "Hearts");

// 	Card upcard("Ace", "Hearts");
// 	//pick up the upcard and drop two spades
// 	simple->add_and_discard(upcard);

// 	static_cast<

// 	ASSERT_EQUAL(simple->hand[4], two_spades);	
	
	
// }

TEST(test_simple_lead_card){

Player *simple = Player_factory("BOT", SMPL);


	Card ace_spades("Ace", "Club");
	Card jack_diamonds("Jack", "Diamonds");
	Card ace_hearts("Ace", "Hearts");
	Card nine_clubs("Jack", "Clubs");
	Card jack_spades("Nine", "Spades");

	std::string trump = "Hearts";
	
	simple->add_card(ace_spades);
	simple->add_card(jack_diamonds);
	simple->add_card(ace_hearts);
	simple->add_card(nine_clubs);
	simple->add_card(jack_spades);

	ASSERT_EQUAL(simple->play_card(ace_spades,trump),ace_spades);


	delete simple;
}

// TEST(test_simple_play_card){


// }




// Add more tests here

TEST_MAIN()