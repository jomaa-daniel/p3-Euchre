// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

TEST(test_default_ctor)
{
	Card c;

	ASSERT_EQUAL(Card::RANK_TWO, c.get_rank());
	ASSERT_EQUAL(Card::SUIT_SPADES, c.get_suit());

}

TEST(test_get_suit)
{
	Card c(Card::RANK_JACK, Card::SUIT_DIAMONDS);

	ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit(Card::SUIT_HEARTS));
}

TEST(test_is_face)
{
	Card c(Card::RANK_JACK, Card::SUIT_CLUBS);

	ASSERT_TRUE(c.is_face());
}

TEST(test_is_right_bower)
{
	Card c(Card::RANK_JACK, Card::SUIT_SPADES);

	std::string trump = Card::SUIT_SPADES;

	ASSERT_TRUE(c.is_right_bower(trump));
}

TEST(test_suit_next)
{
	Card c;
	//TODO odd error
	//ASSERT_EQUAL(Card::SUIT_CLUBS, Suit_next(c));
}

TEST(test_is_left_bower)
{
	Card c(Card::RANK_JACK, Card::SUIT_SPADES);

	ASSERT_TRUE(c.is_left_bower(Card::SUIT_CLUBS));
}

TEST(test_is_trump)
{
	Card c(Card::RANK_JACK, Card::SUIT_HEARTS);

	ASSERT_TRUE(c.is_trump(Card::SUIT_DIAMONDS));
}

TEST(test_operator_less_than)
{
	Card two_spades;
	Card ace_spades(Card::RANK_ACE, Card::SUIT_HEARTS);

	ASSERT_TRUE(two_spades < ace_spades);
}

TEST(test_operator_greater_than)
{
	Card two_spades;
	Card ace_spades(Card::RANK_ACE, Card::SUIT_HEARTS);

	ASSERT_TRUE(ace_spades > two_spades);
}

TEST(test_operator_equal)
{
	Card two_spades;
	Card two_spade;

	ASSERT_TRUE(two_spade == two_spades);
}

TEST(test_operator_not_equal)
{
	Card two_spades;
	Card ace_spade(Card::RANK_ACE, Card::SUIT_SPADES);

	ASSERT_TRUE(two_spades != ace_spade);
}

TEST(test_operator_stream)
{
	Card two_spades;

	string output = "Two of Spades";

	ostringstream os;

	ostringstream correctos(output);

	os << two_spades;

	ASSERT_EQUAL(correctos.str(), os.str());

}

TEST(test_card_less_bowers)
{
	Card right_bower(Card::RANK_JACK, Card::SUIT_SPADES);

	Card ace_spades(Card::RANK_ACE, Card::SUIT_SPADES);

	ASSERT_TRUE(Card_less(ace_spades, right_bower, Card::SUIT_SPADES));

	Card left_bower(Card::RANK_JACK, Card::SUIT_CLUBS);
	

	ASSERT_TRUE(Card_less(ace_spades, left_bower, Card::SUIT_SPADES));

}
TEST(test_card_less_trump)
{
	Card trump_card(Card::RANK_TWO, Card::SUIT_SPADES);

	Card ace_diamond(Card::RANK_ACE, Card::SUIT_DIAMONDS);

	ASSERT_TRUE(Card_less(ace_diamond, trump_card, Card::SUIT_SPADES));
}

TEST(test_card_less_rank)
{
	Card two_spades;
	Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);

	ASSERT_TRUE(Card_less(two_spades, ace_diamonds, Card::SUIT_HEARTS));
}

TEST(test_card_less_suit)
{
	Card two_spades;
	Card two_hearts(Card::RANK_TWO, Card::SUIT_HEARTS);

	ASSERT_TRUE(Card_less(two_spades, two_hearts, Card::SUIT_DIAMONDS));
}

TEST(test_card_less_ledcard)
{
	Card led_card;//two spades
	Card ace_diamonds(Card::RANK_ACE, Card::SUIT_DIAMONDS);

	ASSERT_TRUE(Card_less(ace_diamonds, led_card, led_card,
		Card::SUIT_HEARTS));
}
TEST_MAIN()
