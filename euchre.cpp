#include "Player.h"
#include "Pack.h"
#include <cassert>
#include "fstream"


 struct teamData
{
    int trick,score;
    Player *p1,*p2;        
    bool orderedUp;  
};

class Game
{
private:

   

    teamData team1;
    teamData team2;

    bool shuffling;
    Pack deck;
    std::string trump;
    int finalScore;

public:
    //use command line vargs to construct
    Game(std::string &packname, int finalScore_in, bool shuffling_in, 
    std::string p1Name, std::string p1_strategy, std::string p2_name,
    std::string p2_strategy, std::string p3_name, std::string p3_strategy,
    std::string p4_name, std::string p4_strategy);


    //getter functions
    bool getShuffle() {return shuffling;}
    int getfinalScore() {return finalScore;}
    std::string getTrump() {return trump;}

    teamData getTeam(int n)
    {
        if (n == 1) return team1;
        else return team2;
    }

    Pack getDeck() {return deck;} 
    
    
    void deal();
    
    //returns suit of the trump
    void makingTheTrump();
    
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
Game::Game( std::string &packname,int finalScore_in, bool shuffling_in, 
    std::string p1_name, std::string p1_strategy, std::string p2_name,
    std::string p2_strategy, std::string p3_name, std::string p3_strategy,
    std::string p4_name, std::string p4_strategy) 
{
    std::ifstream inFile;

    inFile.open(packname);

    if(!inFile.is_open())
    {
        std::cout << "Could not open file\n";
        exit(EXIT_FAILURE);
    }
    
    deck = Pack::Pack(inFile);

    finalScore = finalScore_in;

    shuffling = shuffling_in;
    
    //team 1
    team1.p1 = Player_factory(p1_name, p1_strategy);
    team1.p2 = Player_factory(p3_name, p3_strategy);

    //team 2
    team1.p1 = Player_factory(p2_name, p2_strategy);
    team2.p2 = Player_factory(p4_name, p4_strategy);

    team1.score = 0;
    team1.trick = 0;

    team2.score = 0;
    team2.trick = 0;

}

Game::~Game()
{
}

void Game::deal(){


}

void Game::makingTheTrump(){

}

void Game::playHand(){

}

void Game::calcScore(){

}

using namespace std;

int main(int argc, char *argv[])
{

    string packfilename = argv[1];
    bool shuffling = *argv[2];
    int finalScore = *argv[3];
    string p1_name = argv[4];
    string p1_strategy = argv[5];
    string p2_name = argv[6];
    string p2_strategy = argv[7];
    string p3_name = argv[8];
    string p3_strategy = argv[9];
    string p4_name = argv[10];
    string p4_strategy = argv[11]; 

    int theDealer = 0;



     Game game(packfilename,shuffling,finalScore,p1_name,p1_strategy,p2_name,p2_strategy,p3_name,p3_strategy,p4_name,p4_strategy);

    while(((game.getTeam(1).score) < game.getfinalScore()) and ((game.getTeam(2).score) < game.getfinalScore()) ){
        game.deal();
        game.makingTheTrump();
        game.playHand();
        game.calcScore();
    }
    
    return 0;
}







