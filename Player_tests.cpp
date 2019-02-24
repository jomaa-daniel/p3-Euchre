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

TEST(test_play_card_lead)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club("Ace", "Club");
	Card jack_hearts("Jack", "Hearts");
	Card ace_hearts("Ace", "Hearts");
	Card jack_clubs("Jack", "Clubs");
	Card nine_spades("Nine", "Spades");

	Card led_card("Jack", "Diamonds");
	
	std::string trump = "Hearts";
	
	simple->add_card(ace_club);
	simple->add_card(jack_hearts);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);
	//NATURE: 
	// the led card is the left bower
	// the highest card should be the right bower, jack hearts		
	ASSERT_EQUAL(simple->lead_card(trump), ace_club);


	delete simple;
}

TEST(test_play_card_trump)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card five_clubs("Five", "Clubs");
	Card five_diamonds("Five", "Diamonds");
	Card eight_hearts("Eight", "Hearts");
	Card nine_clubs("Nine", "Clubs");
	Card queen_hearts("Queen", "Hearts");

	Card ten_spades("Ten","Spades"); //led card

	std::string trump = "Clubs";
	
	simple->add_card(five_clubs);
	simple->add_card(five_diamonds);
	simple->add_card(eight_hearts);
	simple->add_card(nine_clubs);
	simple->add_card(queen_hearts);

	//NATURE OF TEST:
	// Testing no leds available, must play highest trump
	// highest trump is nine clubs
	// led card is ten spades

	ASSERT_EQUAL(simple->play_card(ten_spades,trump),nine_clubs);

	delete simple;
}

TEST(test_play_card_bower_edge)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club("Ace", "Club");
	Card jack_spades("Jack", "Spades");
	Card ace_hearts("Ace", "Spades");
	Card jack_clubs("Jack", "Clubs");
	Card nine_spades("Ten", "Spades");

	Card led_card("Nine", "Spade");
	
	std::string trump = "Spades";
	
	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);
	//NATURE: 
	// testing bowers, trump is the spades, right bower is highest

	ASSERT_EQUAL(simple->play_card(led_card, trump), jack_spades);


	delete simple;
}

TEST(test_simple_make_trump_round1_isdealer)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club("Ace", "Club");
	Card jack_spades("Jack", "Spades");
	Card ace_hearts("Ace", "Hearts");
	Card jack_clubs("Jack", "Clubs");
	Card nine_spades("Queen", "Hearts");

	Card up_card("Nine", "Spades");
		
	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 1 there is a dealer, 

	ASSERT_TRUE(simple->make_trump(up_card, true, 1,order_up_suit));
	ASSERT_EQUAL(order_up_suit, "Spades");

	delete simple;
}

TEST(aaatest_simple_make_trump_round2_notdealer)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club("Ace", "Hearts");
	Card jack_spades("Jack", "Hearts");
	Card ace_hearts("Ace", "Hearts");
	Card jack_clubs("Queen", "Clubs");
	Card nine_spades("Queen", "Diamonds");

	Card up_card("Nine", "Spades");
		
	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 2 there is NOT a dealer, 
	simple->make_trump(up_card, false, 2 ,order_up_suit);
	ASSERT_EQUAL(order_up_suit, "Clubs");

	delete simple;
}



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

/////////////////// HUMAN TESTS ////////////////////







TEST_MAIN()