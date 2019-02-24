#include "Player.h"
#include "Pack.h"
#include <cassert>


class Game
{
private:

    struct teamData
    {
        int trick,score;
        Player *p1,*p2;          
    };
    
    bool shuffling;
    Pack deck;
    
public:
    //use command line vargs to construct
    Game(/* args */);


    void deal();
    
    //returns suit of the trump
    std::string makingTheTrump();
    
    //returns 1 or 0 depending on the team that won the trick
    int playTrick();

    //plays five tricks, or five playTrick()
    void playHand();

    //called at the end of every hand, sets trick to zero, calcs score
    void calcScore();
    
    //delete the players
    ~Game();
};
//Use varg to construct
Game::Game(/* args */)
{



}

Game::~Game()
{
}
