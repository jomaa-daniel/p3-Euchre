#include "Player.h"
#include "Pack.h"
#include <cassert>
#include "fstream"
#include <cstring>

using namespace std;

struct playerBundle{
    Card card;
    int player;
};


// god function
// modifies: life
// effects: makes it better
static void cardSort(std::vector<playerBundle> &hand, 
const std::string &trump,Card &ledcard){
    
    Card temp;    
    int temp2;

    for(int i = 0; i<int(hand.size()) - 1; i++){
        
        for(int j = 0; j < int(hand.size()) - i - 1; j++)
        {
            if(Card_less(hand[j].card, hand[j+1].card, ledcard,trump))
            {
                temp = hand[j].card;
                temp2 = hand[j].player;
                
                hand[j].card = hand[j + 1].card;
                hand[j].player = hand[j + 1].player;
            
                hand[j + 1].card = temp;
                hand[j + 1].player = temp2;
            }
        }    	
	}
}

struct teamData
{
    int trick,score;       
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
    int dealer;
    int handNumber;
    int lastTrickWinner;
    //std::vector<Player *> players;
    std::array<Player *, 4> players; 
public:
    //use command line vargs to construct
    Game(istream &packname,  bool shuffling_in, int finalScore_in,
   std::vector<std::string> playerData);


    //getter functions
    bool getShuffle() {return shuffling;}
    int getfinalScore() {return finalScore;}
    std::string getTrump() {return trump;}

    Player * getPlayer(int n){ return players[n];}

    teamData getTeam(int n)
    {
        if (n == 1) return team1;
        else return team2;
    }

    //Pack getDeck() {return deck;} 
    
    void deal();

    int getDealer() {return dealer;}

    int getNextDealer(){
        if(dealer < 3){
            return dealer + 1;
        }
        else{return 0;}

    }

    void iterateDealer() {
        
        if(dealer == 3)
        {
            dealer = 0;
        } 
        else
        {
            dealer++;
        }
        
    }
    void printScore();
    //returns suit of the trump
    void makingTheTrump();
    
    //returns 1 or 2 depending on the team that won the trick
    void playTrick();

    //plays five tricks, or five playTrick()
    void playHand();

    //called at the end of every hand, sets trick to zero, calcs score
    void calcScore();
    
    void printWinner();
    
    //delete the players
    ~Game();
};


//Use varg to construct
Game::Game( istream &packname, bool shuffling_in,int finalScore_in, 
    std::vector<std::string> playerData) 
{
   
    
    deck = Pack(packname);

    finalScore = finalScore_in;


    shuffling = shuffling_in;
    
    //team 1
   
    players[0] = Player_factory(playerData[0],playerData[1]);
    players[2] = Player_factory(playerData[4],playerData[5]);

    //team 2
    players[1] = Player_factory(playerData[2],playerData[3]);
    players[3] = Player_factory(playerData[6],playerData[7]);

    team1.score = 0;
    team1.trick = 0;

    team2.score = 0;
    team2.trick = 0;

    team1.orderedUp = false;
    team2.orderedUp = false;

    dealer = 0;
    handNumber = 0;
    lastTrickWinner = 0;
}

Game::~Game()
{
}

void Game::deal(){

    cout << *players[dealer] << " deals" << endl;
    deck.reset();
    if(shuffling) deck.shuffle();

    int cursor = getNextDealer();

    int j = 0;
    
    //deal 3-2-3-2 then 2-3-2-3
    for(int roundOf = 1; roundOf < 3; roundOf++)
    {      
        if(roundOf == 1) {
            for(int i = 0; i < 4; i++)
            { 
                //deal three times if even
                if(i % 2 == 0) j = 3; 

                else j = 2;

                for(int k = 0; k < j; k++)
                    players[cursor]->add_card(deck.deal_one());

                if(cursor == 3) cursor = 0;
                else cursor++;    
            }
        }

        if(roundOf == 2)
        {
            
            for(int i = 0; i < 4; i++)
            {
            //deal three times if even
            if(i % 2 == 0) j = 2;

            else j = 3;

            for(int k = 0; k < j; k++)
                players[cursor]->add_card(deck.deal_one());

            if(cursor == 3) cursor = 0;
            else cursor++; 
              
        }
    }
    }
    
    
    
    
}

void Game::makingTheTrump(){



    int round = 1;
    bool trumpMade = false;
    Card upcard = deck.deal_one();
    std::cout << upcard <<" turned up" << std::endl;
    int cursor = getNextDealer();
    int leftOfDealer = cursor;
    bool isDealer = false;

    while(!trumpMade){
        
        if(cursor == dealer) isDealer = true;

        trumpMade = players[cursor]->make_trump(upcard, isDealer, round,
        trump);

        if((players[cursor] == players[0]) or (players[cursor] == players[2]))
        {
            if(trumpMade) team1.orderedUp = true;
        }
        else if(trumpMade) team2.orderedUp = true;


        if(trumpMade){
           cout <<  *players[cursor] << " orders up " << trump << endl;
           cout << endl;
        }
        else cout << *players[cursor] << " passes" << endl;

        if(round == 1 and trumpMade) getPlayer(dealer)->add_and_discard(upcard);


        if(isDealer){
            round++;
            cursor = leftOfDealer;
        } 
        else if(cursor == 3)cursor=0;
        else cursor++;
        isDealer = false;
        
    }
    
      
}

void Game::playHand(){
    lastTrickWinner = getNextDealer();

    for(int i = 0; i < 5; i++)
    {
        playTrick();

    }
    iterateDealer();
   
}

void Game::playTrick(){


    Card leadCard;
    std::vector<Card> cards_played;
    
 
    int cursor = lastTrickWinner;
    
    leadCard = players[cursor]->lead_card(trump);
    
    cout << leadCard << " led by " << *players[cursor]<<endl;
    
    playerBundle p0 = {leadCard, cursor};

    std::vector<playerBundle> bundleofPlayerBundles;
    bundleofPlayerBundles.push_back({leadCard,cursor});

    for(int i = 1; i < 4; i++)
    {
        if(cursor == 3) cursor = 0;
        else cursor++;
        Card playedCard = players[cursor]->play_card(leadCard,trump);
        bundleofPlayerBundles.push_back({playedCard,cursor});
        cout << playedCard << " played by " << *players[cursor] << "\n";
    }
    
    cardSort(bundleofPlayerBundles, trump, leadCard);

    lastTrickWinner = bundleofPlayerBundles[0].player;

    cout << *players[lastTrickWinner] << " takes the trick\n\n";
    
    if(lastTrickWinner % 2)
    {
        
        team2.trick++;
        
    }    
    else{
        team1.trick++;
    }
    
}

void Game::calcScore(){

    
    if(team1.trick > team2.trick)
    {

        cout << *(players[0]) << " and " << *(players[2]) << " win the hand\n";
        if(team1.orderedUp){
            if(team1.trick == 3 or team1.trick == 4){
                team1.score++;
                //nothing
                
            }
            else if(team1.trick == 5) 
            {
                team1.score += 2;
                //march
                cout << "march!\n";
            }
        }
        else{
            team1.score += 2;
            cout << "euchred!\n";
        }
    }

    else
    {
        cout << *(players[1]) << " and " << *(players[3]) << " win the hand\n";

        if(team2.orderedUp){
            if(team2.trick == 3 or team2.trick == 4){
                team2.score++;
                //nothing
                
            }
            else if(team2.trick == 5) 
            {
                team2.score += 2;
                //march
                cout << "march!\n";
            }
        }
        else{
            team2.score += 2;
            cout << "euchred!\n";
        }
    }

    team1.trick = 0;
    team2.trick = 0;
    team1.orderedUp = false;
    team2.orderedUp = false;

}


void Game::printScore()
{
    cout << *(players[0]) << " and " << *(players[2]) 
    << " have " << team1.score << " points\n";
    cout << *(players[1]) << " and " << *(players[3]) 
    << " have " << team2.score << " points\n";
    cout<<endl;

}

void Game::printWinner()
{
    if(team1.score > team2.score){
        cout << *(players[0]) << " and " << *(players[2]) << " win!\n";
    }

    else
    {
        cout << *(players[1]) << " and " << *(players[3]) << " win!\n";
    }
    
}


using namespace std;

int printProblem(bool prob)
{
 if(prob)
    {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
        << "NAME4 TYPE4" << endl;

     return 1;
    }
    return 0;
}

int checkOpen(ifstream &inFile, std::string &filename)
{
    if(!inFile.is_open())
    {
        cout << "Error opening " << filename << endl;
        return 1;
    }
    return 0;
}


int main(int argc, char *argv[])
{
     
for(int i = 0; i < argc; i++)
    {
        //std::string arg(argv[i]);
        cout << argv[i] << " ";
    }
    cout << endl;    

    int hand = 0;

    bool problem = false;
    bool shuffling;

    if(argc != 12 or *argv[3] < 1 or *argv[3] > 100)
    {
         problem = true;
    }
    std::string shuffletest = argv[2];
    if( shuffletest == "shuffle" and shuffletest == "noshuffle")
    {
       problem = true; 
    }

    for(int i = 5;i < 12;i = i+2){
        std::string test = argv[i];
        if(test == "Simple"  and test == "Human"){
            problem = true;
        } 

    }

    if(printProblem(problem)) return 1;
    
    vector<std::string> playerData;

    
    string packfilename = argv[1];
    
    if(shuffletest != "shuffle"){
        shuffling = false;
    }
    else shuffling = true;
    

    int finalScore = atoi(argv[3]);
    
    for(int i = 4; i < 12; i++)
    {
        playerData.push_back(argv[i]);
    }
    

    // playerData.push_back(argv[4]);//p1 name
    // playerData.push_back(argv[5]); //p1 strat
    // playerData.push_back(argv[6]); //p2 name
    // playerData.push_back(argv[7]); //p2 strat
    // playerData.push_back(argv[8]); //p3 name 
    // playerData.push_back(argv[9]); //p3 strat
    // playerData.push_back(argv[10]); //p4 name
    // playerData.push_back(argv[11]); //p4 strat


    std::ifstream inFile;

    inFile.open(packfilename);

    if(checkOpen(inFile, packfilename)) return 1;

    Game game(inFile,shuffling,finalScore,playerData);

    while(((game.getTeam(1).score) < game.getfinalScore()) 
    and ((game.getTeam(2).score) < game.getfinalScore()) ){
       
        cout << "Hand " << hand << endl;
        game.deal();
        game.makingTheTrump();
       
        game.playHand();
        game.calcScore();       
        
        game.printScore();
        hand++;
        
    }
    game.printWinner();
    return 0;
}


