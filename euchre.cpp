
#include <iostream> 
#include <vector>
#include "Player.hpp"
#include "Pack.hpp"
#include "Card.hpp"
//#include "Player.cpp"
#include <string>
#include <fstream>

using namespace std;
class Game {


    public:                                                                              
     Game(vector<Player*> players, Pack& pack, int points_to_win, string Shouldshuffle);
     void play();
     void Doshuffle();
     void print_hand(int dealer);
     void deal(int dealer);
     bool game_isover(/* ... */);
     void make_trump(int dealer);
     void play_hand(int round,int dealer);
     void find_scores(/* ... */);   
     void find_Gamewinner();
     

      private:
            std::vector<Player*> players;
            Pack pack;
            //int hands;
            int win_points;
            int hands_played;
            string shuffle;
            Card upCard;
            int previous_winner;
            Suit trump;
            int orderedUp;
            //per hand
            vector<int> scores = {0,0,0,0};
            //overall
            vector<int> points = {0,0,0,0};
};
  // ...
   
   //constructor, pass pack by reference to avoid making a copy
    Game::Game
    (vector<Player*> players, Pack& Apack, int points_to_win, string Shouldshuffle) {
    //  this->players = players;
    //  pack = Apack;
    //  win_points = points_to_win;
        this->players = players;
        win_points = points_to_win;
        shuffle = Shouldshuffle;
     
    }
    
    
    void Game::play() {
        cout << std::endl;
        hands_played = 0;
        int dealer = 0;
        //int round = 0;
        
        //upCard = pack.deal_one();
       
        //print_hand();
        //bool game = true;
        
        while(!game_isover()){
             if(shuffle == "shuffle"){
                Doshuffle();
            }
            deal(dealer);
            upCard = pack.deal_one();
            
            print_hand(dealer);
            hands_played++;
            make_trump(dealer);
            //cout << "trump suit" << trump << endl;
            //cout << endl;
            
            //increment hands played and dealer
 
            //each hand is 5 since 5 cards
            //cout << "playing trick" << endl; // debugging not needed
            //play hands
            for(int round = 0;round < 5; round++){
                //cout << round << endl;
                play_hand(round, dealer);

            }
            //play_hand(); //infinite loop
            //cout << "all trick played" << endl;
            //print and find points
            
            
            find_scores();
            //increment dealer
            dealer = (dealer + 1) % 4;
            pack.reset();
            
            /*if(hands_played == 5){
                game = false;
            }*/
            //game = false;

            
        }
        //find winner
        find_Gamewinner();
        

        
        
    }
    
    
    void Game::Doshuffle() {
     pack.shuffle();
    }
    void Game::print_hand(int dealer) {
        cout << "Hand " << hands_played << endl;
        cout << players[dealer]->get_name() << " deals" << endl;
        //Card upCard = pack.deal_one();
        //using << operator overload on Card
        cout << upCard << " turned up" << endl;
        //cout << endl;


    }
    void Game::deal(int dealer) {
        //first set
        int turn = (dealer+1)%4;
        for(int j = 0;j<4;j++){
            //if the player index is even give 3 cards
            if(j%2 == 0){
                for(int i = 0;i < 3; i++){
                players[turn]->add_card(pack.deal_one());
                
                }
            
            }else{
                for(int i = 0;i<2;i++){
                players[turn]->add_card(pack.deal_one());
                }
            }
            turn = (turn + 1)%4;
        }
        //second time
        for(int j = 0;j<4;j++){
            if(j%2 != 0){
                for(int i = 0;i < 3; i++){
                players[turn]->add_card(pack.deal_one());
                }
            
            }else{
                for(int i = 0;i<2;i++){
                players[turn]->add_card(pack.deal_one());
                }
            }

             turn = (turn + 1) % 4;
        
            }
     // ...
    }





    bool Game::game_isover(){
        for(int i = 0;i<2;i++){
            if(points[i] + points[i+2] >= win_points){
                
                return true;
            }
        }
        //return false if no one has won
        return false;
    }
//Barbara passes
// Chi-Chih passes
// Dabbala passes
// Adi passes
// Barbara orders up Hearts
    void Game::make_trump(int dealer) {
        //sets trump to upcard suit
        Suit trump_suit = upCard.get_suit();
        //cout << "trump suit" << trump_suit << endl;
        //to find the turn, do dealer + 1 (eldest hand) and then mod 4
        int turn = (dealer+1)%4;
        //round 1 and 2 loop
        for(int j=1; j<3; j++){
            //go through players
            for(int i = 0;i<4;i++){
                //if player did order up
                if(players[turn]->make_trump(upCard, turn==dealer,j, trump_suit)){
                    //prints out name and orders up suit
                    cout << players[turn]->get_name() << " orders up "
                    << trump_suit << endl << endl;
                    if(j==1){
                        players[dealer] ->add_and_discard(upCard);
                    }
                    //cout << " index ordering up" <<turn << endl;
                    //set ordered up to the player index
                    orderedUp = turn;
                    trump = trump_suit;
                    return;
                }
                else{
                    //if someone did not ordered up
                    //cout << players[turn]->get_name() << " passing index: " 
                    //<< turn <<endl;
                    cout << players[turn]->get_name() << " passes" << endl;
                }
                
                turn = (turn + 1)%4;
                
            }
        }
        
       
    }

    //Jack of Spades led by Barbara
    // King of Spades played by Chi-Chih
    // Ace of Spades played by Dabbala
    // Nine of Diamonds played by Adi
    // Dabbala takes the trick

    void Game::play_hand(int round,int dealer) {
        //make a vector of all the cards in pile
        vector<Card> pile;
        vector<int> turns;
        
        //cout << "found lead" << endl;
        int lead_player = (dealer+1)%4;
        //since it is the first hand, eldest hand is leader
        if(round == 0){
            //cout << "first hand" << endl;
            lead_player = (dealer+1)%4;
        }
        else{
            //since previous winner is the lead now
            //cout << "not first trick" << endl;
            lead_player = previous_winner;
            //cout << "set lead player" << endl;
        }
        Card leadcard = players[lead_player]->lead_card(trump);
        
        cout << leadcard << " led by "<< players[lead_player]->get_name() << endl;
        pile.push_back(leadcard);
        Card max = pile[0];
        int winner = lead_player;
        turns.push_back(lead_player);
        //one round of trickery starting frm  player after lead player
        for (int i = 1; i<4; i++){
            int turn = (lead_player+i)%4;
            //cout << "playing card" << endl;
            Card playerPutCard = players[turn]->play_card(leadcard, trump);
            cout << playerPutCard << " played by " << players[turn]->get_name() 
            << endl;
            pile.push_back(playerPutCard);
            turns.push_back(turn);
        }
       
        

        //do who wins the trick!!!!!
        //finding the highest played card
        for(int i = 0;i < 4; i++){
            //bool Card_less(const Card &a, const Card &b, 
            //const Card &led_card, Suit trump);

            if(Card_less(max, pile[i],leadcard, trump)){
                max = pile[i];
                winner = turns[i];
            }
        }
        
        //position of winner = player index
        scores[winner]++;
        //cout << "added score to player" << players[winner]->get_name()<< endl;
        previous_winner = winner;
        cout << players[winner]->get_name() << " takes the trick" << endl;
        cout << endl;
    }
        
    void Game::find_Gamewinner(){
        if(points[0] + points[2] > points[1] + points[3]){
            cout << players[0]->get_name() << " and " 
            << players[2]->get_name() << " win!" << endl;
        } else {
            cout << players[1]->get_name() << " and " 
            << players[3]->get_name() << " win!" << endl;
        }
        
    }
        
        
    
        
       
    //If the team that ordered up the trump suit takes 3 or 4 tricks,
    // they get 1 point.
    //If the team that ordered up the trump suit takes 
    //all 5 tricks, they get 2 points. This is called a march.
    //If the team that did not order up takes 3, 4, or 
    //5 tricks, they receive 2 points. This is called euchred.

    void Game::find_scores() {
       
        
        //iterate through the scores
        string thingy = "";
        for(int i = 0;i < 2; i++){
            if(i == orderedUp || i+2 == orderedUp){
                if(scores[i] + scores[i+2] == 3 || scores[i]+ scores[i+2] == 4){
                    points[i] += 1;
                }else if(scores[i] + scores[i+2] == 5){
                    //a march
                    points[i] += 2;
                    thingy = "march!";
                }
            }
            else{
                //getting euchred
                if(scores[i] + scores[i+2] == 3 || scores[i]+ scores[i+2]== 4 
                || scores[i] + scores[i+2] == 5){
                    points[i] += 2;
                    thingy = "euchred!";
                }
            }


        }
        if(scores[0] + scores[2] > scores[1] + scores[3]){
            cout << players[0]->get_name() << " and " 
            << players[2]->get_name() << " win the hand" << endl;
        } else {
            cout << players[1]->get_name() << " and " 
            << players[3]->get_name() << " win the hand" << endl;
        }
        //Adi and Chi-Chih have 2 points
        if(thingy != ""){
            cout << thingy << endl;
        }
        
        cout << players[0]->get_name() << " and " 
        << players[2]->get_name() << " have " << points[0] + points [2] 
        << " points" << endl;
        cout << players[1]->get_name() << " and " 
        << players[3]->get_name() << " have " << points[1] + points [3] 
        << " points" << endl;
        cout << endl;
         //now reset scores for each hand
         scores = {0,0,0,0};
         
        
    }
    
        




    
   
   int main(int argc, char **argv) {
        // Read command line args and check for errors
        string error_string = "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle]";
        error_string+="POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 NAME4 TYPE4";
        //cout << "Reading in" << endl;
        if(argc != 12){
           cout << error_string << endl;
           return 1;
        //convert pointer to string
        }else if(string(argv[2]) != "shuffle" && string(argv[2]) != "noshuffle"){
           cout << error_string << endl;
           return 1;
        }else if(stoi(argv[3]) < 1 || stoi(argv[3]) > 10){
           cout << error_string << endl;
           return 1;
        }else{
           for(int i = 5;i<12;i+=2){
               if(string(argv[i]) != "Human"){
               if(string(argv[i]) != "Simple" && string(argv[i]) != "Random"){
                   cout << error_string << endl;
                   return 1;
               }
               }
           }
        }
       ifstream fin(argv[1]);
       if(!fin.is_open()){
           cout << "Error opening file" << endl;
           return 1;
       }
       string string_shuffle = argv[2];
       int points = stoi(argv[3]);
       vector<Player*> players;
       //add players
       for(int i = 4;i<12;i+=2){
           players.push_back(Player_factory (string(argv[i]),(argv[i+1])));
       }
       //make pack
       Pack pack(fin);
       
       Game game(players, pack, points, string_shuffle);
       for(int i = 0;i<argc;i++){
           cout << argv[i] << " ";
       }
       game.play();
       
       //delete at end
       for (int i = 0; i < players.size(); ++i) {
           delete players[i];
       }
   }