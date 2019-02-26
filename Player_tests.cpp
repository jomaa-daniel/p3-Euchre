// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "Card.h"
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
	//play_card(card, Card::SUIT_HEARTS);
}

TEST(test_make_trump_round1_nondealer_ordrup) {
//this is called upcasting
	Player *simple = Player_factory("BOT", SMPL);

	Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
	Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);


	//create a player without 2 of same suit
	simple->add_card(ace_spades);
	simple->add_card(jack_diamonds);
	simple->add_card(ace_hearts);
	simple->add_card(nine_clubs);
	simple->add_card(jack_spades);


	Card upcard(Card::RANK_KING, Card::SUIT_SPADES);

	string order_up_suit;

	ASSERT_TRUE(simple->make_trump(upcard, false, 1, order_up_suit));
	ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);
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
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
	simple->add_card(two_spades);


	ASSERT_EQUAL(simple->play_card(jack_spades,Card::SUIT_HEARTS),two_spades);
	delete simple;
}

TEST(test_play_card_lead)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_NINE, Card::SUIT_SPADES);

	Card led_card(Card::RANK_JACK, Card::SUIT_DIAMONDS);

	std::string trump = Card::SUIT_HEARTS;


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
TEST(test_play_card_lead_all_trump)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card two_club(Card::RANK_TWO, Card::SUIT_CLUBS);


	Card led_card(Card::RANK_JACK, Card::SUIT_HEARTS);

	std::string trump = Card::SUIT_CLUBS;


	simple->add_card(ace_club);
	simple->add_card(two_club);

	//NATURE: 
	// the led card is the left bowe
	// the highest card should be the right bower, jack hearts
	ASSERT_EQUAL(simple->lead_card(trump), ace_club);


	delete simple;
}


TEST(test_play_card_bower_edge)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, "Club");
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_SPADES);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_TEN, Card::SUIT_SPADES);

	Card led_card(Card::RANK_NINE, Card::SUIT_SPADES);

	std::string trump = Card::SUIT_SPADES;

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

	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_QUEEN, Card::SUIT_HEARTS);

	Card up_card(Card::RANK_NINE, Card::SUIT_SPADES);

	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 1 there is a dealer, 

	ASSERT_TRUE(simple->make_trump(up_card, true, 1,order_up_suit));
	ASSERT_EQUAL(order_up_suit, Card::SUIT_SPADES);

	delete simple;
}

TEST(test_simple_make_trump_round2_notdealer)
{
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card jack_clubs(Card::RANK_QUEEN, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_QUEEN, Card::SUIT_DIAMONDS);

	Card up_card(Card::RANK_NINE, Card::SUIT_SPADES);

	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 2 there is NOT a dealer, 
	simple->make_trump(up_card, false, 2 ,order_up_suit);
	ASSERT_EQUAL(order_up_suit, Card::SUIT_CLUBS);

	delete simple;
}



TEST(test_simple_lead_card){

	Player *simple = Player_factory("BOT", SMPL);

	Card ace_spades(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card jack_diamonds(Card::RANK_JACK, Card::SUIT_DIAMONDS);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card nine_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_NINE, Card::SUIT_SPADES);

	std::string trump = Card::SUIT_HEARTS;

	simple->add_card(ace_spades);
	simple->add_card(jack_diamonds);
	simple->add_card(ace_hearts);
	simple->add_card(nine_clubs);
	simple->add_card(jack_spades);

	ASSERT_EQUAL(simple->play_card(ace_spades,trump),ace_spades);


	delete simple;
}


TEST(test_play_card_trump)
{
	Player *simple = Player_factory("Sally", SMPL);
	Card five_clubs(Card::RANK_FIVE, Card::SUIT_CLUBS);
	Card five_diamonds(Card::RANK_FIVE, Card::SUIT_DIAMONDS);
	Card eight_hearts(Card::RANK_EIGHT, Card::SUIT_HEARTS);
	Card nine_clubs(Card::RANK_NINE, Card::SUIT_CLUBS);
	Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);

	Card ten_spades(Card::RANK_TEN,Card::SUIT_SPADES); //led card
	std::string trump = Card::SUIT_CLUBS;
	simple->add_card(five_clubs);
	simple->add_card(five_diamonds);
	simple->add_card(eight_hearts);
	simple->add_card(nine_clubs);
	simple->add_card(queen_hearts);

	//NATURE OF TEST:
	// Testing no leds available, must play highest trump
	// highest trump is nine clubs
	// led card is ten spades


	ASSERT_EQUAL(simple->play_card(ten_spades,trump),five_diamonds);

	delete simple;
}


TEST(MakeTrump_round2_dealer){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE,Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_QUEEN, Card::SUIT_HEARTS);

	Card up_card(Card::RANK_NINE, Card::SUIT_SPADES);

	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 1 there is a dealer, 

	ASSERT_TRUE(simple->make_trump(up_card, true, 2,order_up_suit));
	ASSERT_EQUAL(order_up_suit, Card::SUIT_CLUBS);

	delete simple;

}

TEST(add_and_discard_theSameCard){

	Player *simple = Player_factory("Sally", SMPL);


	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);

	simple->add_card(ace_club);



	Card upcard(Card::RANK_FOUR,Card::SUIT_CLUBS);	

	Card ledcard(Card::RANK_FIVE,Card::SUIT_HEARTS);

	std::string trump = Card::SUIT_DIAMONDS;

	simple->add_and_discard(upcard);
	// should stay ace

	ASSERT_EQUAL(simple->play_card(ledcard,trump),ace_club);

	delete simple;
}


TEST(lead_card_almostOnlyTrumps){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_ACE,Card::SUIT_HEARTS);
	Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card five_hearts(Card::RANK_FIVE, Card::SUIT_HEARTS);
	Card eight_diamonds(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
	Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);


	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_diamonds);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_HEARTS;

	ASSERT_EQUAL(simple->lead_card(trump),eight_diamonds);

	delete simple;

}
TEST(Lead_card_OnlyTrumps){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_ACE,Card::SUIT_HEARTS);
	Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card five_hearts(Card::RANK_FIVE, Card::SUIT_HEARTS);
	Card eight_hearts(Card::RANK_EIGHT, Card::SUIT_HEARTS);
	Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);



	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_hearts);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_HEARTS;

	ASSERT_EQUAL(simple->lead_card(trump),jack_hearts);

	delete simple;

}
TEST(Play_card_TrumpsOnly){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_ACE,Card::SUIT_HEARTS);
	Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card five_hearts(Card::RANK_FIVE, Card::SUIT_HEARTS);
	Card eight_hearts(Card::RANK_EIGHT, Card::SUIT_HEARTS);
	Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);



	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_hearts);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_HEARTS;

	Card ledcard(Card::RANK_TEN,Card::SUIT_SPADES);

	ASSERT_EQUAL(simple->play_card(ledcard,trump),five_hearts);

	delete simple;

}

TEST(Making_trump_Fail){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_QUEEN, Card::SUIT_HEARTS);

	Card up_card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 1 there is a dealer, 


	ASSERT_EQUAL(order_up_suit, "");

	delete simple;

}
TEST(Making_trump_Fail_round_2){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
	Card ace_hearts(Card::RANK_ACE, Card::SUIT_HEARTS);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_QUEEN, Card::SUIT_HEARTS);

	Card up_card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_hearts);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 1 there is a dealer, 

	ASSERT_TRUE(simple->make_trump(up_card, false, 2,order_up_suit));
	ASSERT_EQUAL(order_up_suit, Card::SUIT_HEARTS);

	delete simple;

}

TEST(Making_trump_round_2){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_SPADES);
	Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_QUEEN, Card::SUIT_HEARTS);

	Card up_card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_spades);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 1 there is a dealer, 

	ASSERT_TRUE(simple->make_trump(up_card, false, 2,order_up_suit));
	ASSERT_EQUAL(order_up_suit, Card::SUIT_HEARTS);

	delete simple;

}
TEST(making_trump_round2_bower){

	Player *simple = Player_factory("Sally", SMPL);

	Card ace_club(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card jack_spades(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);
	Card jack_clubs(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card nine_spades(Card::RANK_EIGHT, Card::SUIT_HEARTS);

	Card up_card(Card::RANK_NINE, Card::SUIT_DIAMONDS);

	simple->add_card(ace_club);
	simple->add_card(jack_spades);
	simple->add_card(ace_spades);
	simple->add_card(jack_clubs);
	simple->add_card(nine_spades);

	std::string order_up_suit;

	// round 1 there is a dealer, 

	ASSERT_TRUE(simple->make_trump(up_card, false, 2,order_up_suit));
	ASSERT_EQUAL(order_up_suit, Card::SUIT_HEARTS);

	delete simple;
}

TEST(lead_card_no_trumps){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_ACE,Card::SUIT_HEARTS);
	Card jack_hearts(Card::RANK_JACK, Card::SUIT_HEARTS);
	Card five_hearts(Card::RANK_FIVE, Card::SUIT_HEARTS);
	Card eight_diamonds(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
	Card queen_hearts(Card::RANK_QUEEN, Card::SUIT_HEARTS);


	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_diamonds);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_CLUBS;

	ASSERT_EQUAL(simple->lead_card(trump),five_hearts);

	delete simple;
}

TEST(lead_card_trump_and_4_ties){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_EIGHT,Card::SUIT_HEARTS);
	Card jack_hearts(Card::RANK_KING, Card::SUIT_CLUBS);
	Card five_hearts(Card::RANK_EIGHT, Card::SUIT_CLUBS);
	Card eight_diamonds(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
	Card queen_hearts(Card::RANK_EIGHT, Card::SUIT_SPADES);


	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_diamonds);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_CLUBS;

	ASSERT_EQUAL(simple->lead_card(trump),eight_diamonds);

	delete simple;
}

TEST(play_card_ties){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_FIVE,Card::SUIT_DIAMONDS);
	Card jack_hearts(Card::RANK_KING, Card::SUIT_CLUBS);
	Card five_hearts(Card::RANK_EIGHT, Card::SUIT_CLUBS);
	Card eight_diamonds(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
	Card queen_hearts(Card::RANK_NINE, Card::SUIT_DIAMONDS);



	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_diamonds);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_HEARTS;

	Card ledcard(Card::RANK_TEN,Card::SUIT_SPADES);

	ASSERT_EQUAL(simple->play_card(ledcard,trump),five_hearts);

	delete simple;

}

TEST(play_card_left_bower_only){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_FIVE,Card::SUIT_DIAMONDS);
	Card jack_hearts(Card::RANK_KING, Card::SUIT_CLUBS);
	Card five_hearts(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card eight_diamonds(Card::RANK_EIGHT, Card::SUIT_DIAMONDS);
	Card queen_hearts(Card::RANK_NINE, Card::SUIT_DIAMONDS);



	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_diamonds);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_SPADES;

	Card ledcard(Card::RANK_TEN,Card::SUIT_SPADES);

	ASSERT_EQUAL(simple->play_card(ledcard,trump),five_hearts);

	delete simple;
}

TEST(play_card_left_bower_highest){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_FIVE,Card::SUIT_DIAMONDS);
	Card jack_hearts(Card::RANK_KING, Card::SUIT_CLUBS);
	Card five_hearts(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card eight_diamonds(Card::RANK_JACK, Card::SUIT_SPADES);
	Card queen_hearts(Card::RANK_NINE, Card::SUIT_DIAMONDS);



	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_diamonds);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_CLUBS;

	Card ledcard(Card::RANK_TEN,Card::SUIT_CLUBS);

	ASSERT_EQUAL(simple->play_card(ledcard,trump),eight_diamonds);

	delete simple;
}

TEST(play_card_right_bower_highest){
	Player *simple = Player_factory("Sally", SMPL);

	Card ace_hearts(Card::RANK_FIVE,Card::SUIT_DIAMONDS);
	Card jack_hearts(Card::RANK_KING, Card::SUIT_CLUBS);
	Card five_hearts(Card::RANK_ACE, Card::SUIT_CLUBS);
	Card eight_diamonds(Card::RANK_JACK, Card::SUIT_CLUBS);
	Card queen_hearts(Card::RANK_NINE, Card::SUIT_DIAMONDS);



	simple->add_card(ace_hearts);
	simple->add_card(jack_hearts);
	simple->add_card(five_hearts);
	simple->add_card(eight_diamonds);
	simple->add_card(queen_hearts);

	std::string trump = Card::SUIT_CLUBS;

	Card ledcard(Card::RANK_TEN,Card::SUIT_CLUBS);

	ASSERT_EQUAL(simple->play_card(ledcard,trump),eight_diamonds);

	delete simple;
}
TEST_MAIN()


