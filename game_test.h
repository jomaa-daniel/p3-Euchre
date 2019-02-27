#pragma once

#include <string>
#include "Player.h"
#include "Pack.h"

struct teamData
{
	int trick, score;
	Player *p1, *p2;
	bool orderedUp;
};

struct Node
{
	Player *player;
	Node *next;
};

class Game
{
public:

	teamData team1;
	teamData team2;

	bool shuffling;
	Pack deck;
	std::string trump;
	int finalScore;
	Node *dealer;
	Node p1, p2, p3, p4;


	//use command line vargs to construct
	Game(std::string &packname, int finalScore_in, bool shuffling_in,
		std::vector<std::string> playerData);


	//getter functions
	bool getShuffle() { return shuffling; }
	int getfinalScore() { return finalScore; }
	std::string getTrump() { return trump; }

	teamData getTeam(int n)
	{
		if (n == 1) return team1;
		else return team2;
	}

	//Pack getDeck() {return deck;} 

	void deal();

	Node* getDealer() { return dealer; }

	void iterateDealer() {
		dealer = dealer->next;
	}

	//returns suit of the trump
	void makingTheTrump();

	//returns 1 or 2 depending on the team that won the trick
	int playTrick();

	//plays five tricks, or five playTrick()
	void playHand();

	//called at the end of every hand, sets trick to zero, calcs score
	void calcScore();

	//delete the players
	~Game();
};