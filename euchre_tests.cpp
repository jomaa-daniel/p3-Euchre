#include "game_test.h"
#include "Player.h"

#include <iostream>
#include <cassert>
using namespace std;


int main(){
	std::vector<string> playerData = {"Bot0", "Simple", "Bot1", "Simple",
	"Bot2", "Simple", "Bot3", "Simple"}; 
		 
	Player* plr = Player_factory("Sally", "Simple");

	std::string packIN = "pack.in";
	
	Game game(packIN,10, false, playerData);

	 assert(game.getShuffle() == false);
	  assert(game.getfinalScore() == 10);
	  assert(plr->get_name() == "Sally");
	assert((game.getPlayer(0)->get_name()) == "Bot0");
	//  assert(game.getPlayer(1)->get_name() == "Bot2");
	//  assert(game.getPlayer(2)->get_name() == "Bot1");
	//  assert(game.getPlayer(3)->get_name() == "Bot3");
	
	
	// assert((game.getPlayer(game.getDealer()))->get_name() == "Bot0");

 	//game.deal();	
	
	
 
 	// Card two_spades;

 	// string trump = Card::SUIT_CLUBS;

 	// for(int i = 0; i < 4; i++)
 	// {
 	// 	for(int j = 0; j < 5; j++)
 	// 	{
 	// 	    cout <<	game.getPlayer(i)->play_card(two_spades,trump);
 	// 	}
		
 	// }

	// for(int i = 0; i < 4; i++)
	// {
	// 	delete game.getPlayer(i);
	// }
	

}



