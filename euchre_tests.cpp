#include "game_test.h"
#include "Player.h"

#include <iostream>
#include <cassert>
using namespace std;


int main(){
	std::vector<string> playerData = {"Bot0", "Simple", "Bot1", "Simple",
	"Bot2", "Simple", "Bot3", "Simple"}; 
		 
	
	std::string packIN = "pack.in";
	
	Game game(packIN,10, false, playerData);

	assert(game.getShuffle() == false);
	assert(game.getfinalScore() == 10);
	assert(game.getTeam(1).p1->get_name() == "Bot0");
	assert(game.getTeam(1).p2->get_name() == "Bot2");
	assert(game.getTeam(2).p1->get_name() == "Bot1");
	assert(game.getTeam(2).p2->get_name() == "Bot3");
	
	
	assert(game.getDealer()->player->get_name() == game.team1.p1->get_name());

 	game.deal();	
	
	
 	std::vector<Player *> players = {game.team1.p1, game.team1.p2, game.team2.p1
 	, game.team2.p2};
 	Card two_spades;

 	string trump = Card::SUIT_CLUBS;

 	// for(int i = 0; i < 4; i++)
 	// {
 	// 	for(int j = 0; j < 5; j++)
 	// 	{
 	// 	    cout <<	players[i]->play_card(two_spades,trump);
 	// 	}
		
 	// }

 cout << game.p1.player->play_card(two_spades,trump);
//  delete game.p2.player;
 // delete game.p3.player;
  //delete game.p4.player;

}



