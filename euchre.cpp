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

struct Node
{
    Player *player;
    Node *next;
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
    Node *dealer;
    Node p1,p2,p3,p4;

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

    //Pack getDeck() {return deck;} 
    
    void deal();

    Node* getDealer() {return dealer;}

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
    
    deck = Pack(inFile);

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

    team1.orderedUp = false;
    team2.orderedUp = false;

    Node p1;
    Node p2;
    Node p3;
    Node p4;

    p1.player = team1.p1;
    p2.player = team2.p1;
    p3.player = team1.p2;
    p4.player = team2.p2;

    p1.next = &p2;
    p2.next = &p3;
    p3.next = &p4;
    p4.next = &p1;

    dealer = &p1;
}

Game::~Game()
{
}

void Game::deal(){

    deck.reset();
    if(shuffling) deck.shuffle();


    int j = 0;
    
    //deal 3-2-3-2 then 2-3-2-3
    for(int x = 0; x < 2; x++)
    {      
        if(x == 1) {
        for(int i = 0; i < 4; i++)
        { 
            //deal three times if even
            if(i % 2 == 0) j = 3; 

            else j = 2;

            for(int k = 0; k < j; k++)
                dealer->player->add_card(deck.deal_one());
            iterateDealer();
        }
        
        }
        if(x == 2)
        {
            for(int i = 0; i < 4; i++)
            {
            //deal three times if even
            if(i % 2 == 0) j = 2;

            else j = 3;

            for(int k = 0; k < j; k++)dealer->player->add_card(deck.deal_one());
              iterateDealer();
        }
    }
}
}

void Game::makingTheTrump(){
    
    int round = 1;
    bool trumpMade;
    Card upcard = deck.deal_one();

    Node isDealer = *dealer;

    Node *originalDealer = dealer;

    //start at the eldest player
    iterateDealer();

    while(!trumpMade){
        
        if(&(isDealer.player) == &(dealer->player)) round++;
        

        if(&(isDealer.player) == &(dealer->player))
        {
            trumpMade = dealer->player->make_trump(upcard, true, round, trump);
            if(&(p1.player) == &(dealer->player) or &(p3.player) == &(dealer->player))
            {
                team1.orderedUp = true;
            }
            else if (&(p2.player) == &(dealer->player) or &(p4.player) == &(dealer->player))
                team2.orderedUp = true;
        }
        else
        {
            trumpMade = dealer->player->make_trump(upcard, false, round, trump);
            if(&(p1.player) == &(dealer->player) or &(p3.player) == &(dealer->player))
            {
                team1.orderedUp = true;
            }
            else if (&(p2.player) == &(dealer->player) or &(p4.player) == &(dealer->player))
                team2.orderedUp = true;
        }
        
        
    }

    dealer = originalDealer;

    dealer->player->add_and_discard(upcard);
    
}

void Game::playHand(){

    for(int i = 0; i < 5; i++)
    {
        

    }
    
    iterateDealer();
}

int Game::playTrick(){
	return 0;
    
}

void Game::calcScore(){
	return;
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


    Game game(packfilename,shuffling,finalScore,p1_name,p1_strategy,p2_name,p2_strategy,p3_name,p3_strategy,p4_name,p4_strategy);

    while(((game.getTeam(1).score) < game.getfinalScore()) and ((game.getTeam(2).score) < game.getfinalScore()) ){
        game.deal();
        game.makingTheTrump();
        game.playHand();
        game.calcScore();
        game.iterateDealer();
        
    }
    
    return 0;
}







