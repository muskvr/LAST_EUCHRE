#include "Player.hpp"
#include "Card.hpp"
#include <string>
#include <vector>
#include <cassert>
//#include <iostream>
#include <algorithm>
using namespace std;

/**
 * SimplePlayer class: A basic implementation of a Player.
 * Implements all pure virtual functions from the Player base class.
 */


class SimplePlayer : public Player {
public:
    
    SimplePlayer(const string &name_in) : name(name_in) { }
    
    //EFFECTS returns player's name
    const string & get_name() const override {
        return name;
    }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &upcard) override {
       cards.push_back(upcard);
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.

/*In making trump, a Simple Player considers the upcard, which player dealt,
 and whether it is the first or second round of making trump. A more comprehensive
strategy would consider the other players’ responses, but we will keep it simple.

During round one, a Simple Player considers ordering up the suit of the upcard, 
which would make that suit trump. They will order up if that would mean they have 
two or more cards that are either face or ace cards of the trump suit 
(the right and left bowers, and Q, K, A of the trump suit, which is the suit proposed
by the upcard). (A Simple Player does not consider whether they are the dealer and 
could gain an additional trump by picking up the upcard.)*/

    bool make_trump(const Card &upcard, bool is_dealer,int round, Suit &order_up_suit) const override {
        //cout << "MAKE" << endl;
        //cout <<  "cards in hand: " << endl;
        
       int count = 0;
       if(round == 1){
            for(int i = 0; i<cards.size();i++){
                if(cards[i].is_trump(upcard.get_suit())){
                    if(cards[i].is_face_or_ace()){
                    count++;
                    }
                }
            }
            //if player has 2 or more face or ace cards of the trump suit
            if(count>=2){
            order_up_suit = upcard.get_suit();
            return true;
            }
            else{
                return false;
            }
       }
       if(round != 2){
            return false;
       }
       
        count = 0;
        //screw dealer
        if(is_dealer){
            order_up_suit = Suit_next(upcard.get_suit());
            return true;
        }

        for(int i = 0; i<cards.size();i++){
            if(Suit_next(upcard.get_suit()) == cards[i].get_suit()){
                if(cards[i].is_face_or_ace()){
                count++;
                }
            }
        }
        if(count>=1){
        order_up_suit = Suit_next(upcard.get_suit());
        return true;
        }
       
       return false;
    }
    
    

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.

    //If the trump suit is ordered up during round one, the dealer picks up the upcard. 
    //The dealer then discards the lowest card in their hand, even if this is the upcard, 
    //for a final total of five cards. (Note that at this point, the trump suit is the suit of the upcard.)
    void add_and_discard(const Card &upcard) override {
       
       
       cards.push_back(upcard);
       Card low = cards[0];
       int index = 0;
       for(int i = 0; i < cards.size(); i++){
           if (Card_less(cards[i],low,upcard.get_suit())){
                low = cards[i];
                index= i;
           }
           
       }
     
        cards.erase(cards.begin() + index);
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand accordi1ng to their strategy
    //  "Lead" means to play the first Card in a trick.  The card
    //  is removed the player's hand.
    //When a Simple Player leads a trick, they play the highest 
    //non-trump card in their hand. If they have only trump cards, they play the highest trump card in their hand.
    Card lead_card(Suit trump) override { 
        Card max;
        int index = -1;
        //int index = 0;
        for (int i = 0; i < cards.size(); i++) {
            if (cards[i].get_suit() != trump) {
                max = cards[i];
                index = i;
                //cout << "no trump " << endl;
            }
        }
        if(index != -1){
            for(int i = 0; i < cards.size(); i ++){
                if(max < cards[i] && cards[i].get_suit() != trump){
                    max = cards[i];
                    index = i;
                }
            }
            cards.erase(cards.begin() + index);
            return max;
        }
        //if only having trump cards
        for(int i = 0; i < cards.size(); i++){
            if (cards[i].get_suit() == trump && Card_less(max, cards[i], trump)) {
                max = cards[i];
                index = i;
            }
        }
        cards.erase(cards.begin() + index);
        return max;
         


        
       
       
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Plays one Card from Player's hand according to their strategy.
    //  The card is removed from the player's hand.
    //When playing a card, Simple Players use a simple strategy that considers only 
    //the suit that was led. A more complex strategy would also consider the cards on the table.

//If a Simple Player can follow suit, they play the highest card that follows suit. Otherwise, they play the lowest card in their hand.
    Card play_card(const Card &led_card, Suit trump) override {  
        //cout << "PLAY CARD" << endl;
        Card max = cards[0];
        int index = -1;
        //cout << "BEFOREEEEE" << name << endl;
        /*for(int i = 0; i < cards.size(); i++){
            cout << cards[i] << endl;
        }*/
        //cout << cards.size() << endl;
        //check if player can follow suit
        for (int i = 0; i < cards.size(); i++) {
            //if card is follows suit and is higher than max
            //card less returns true if max < cards[i]
            //bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump){
            
            if (cards[i].get_suit(trump) == led_card.get_suit(trump)) {
                
                max = cards[i]; 
                index = i;
                
            
              
            }
        }
        //we were able to follow suit
        if(index!=-1){
            for(int i = 0; i < cards.size(); i++){
                if(Card_less(max, cards[i],led_card, trump) && cards[i].get_suit() == led_card.get_suit()){
                    max = cards[i]; 
                    index = i;
                }
            }
            cards.erase(cards.begin() + index);
            //cout << name << "followed suit" << endl;
            return max;
        }

        Card min = cards[0];
        index = 0;
        //if we can not follow suit play the lowest card
        for(int i = 0; i < cards.size(); i++){
            if (Card_less(cards[i],min,trump) && cards[i].get_suit(trump)!=led_card.get_suit()){
                min = cards[i];
                index = i;
            }
        }
        //now erase that card
        //cout << "did not followed suit" << endl;
        cards.erase(cards.begin() + index);
        return min;
        
    }

private:
    string name;
    vector<Card> cards;
    
};

/**
 * HumanPlayer class: A player controlled by a human.
 * Implements all pure virtual functions from the Player base class.
 */
class HumanPlayer : public Player {
public:
    HumanPlayer(const string &name_in) : name(name_in) { }

    //EFFECTS returns player's name
    const string & get_name() const override {
        return name;
    }

  //REQUIRES player has less than MAX_HAND_SIZE cards
  //EFFECTS  adds Card c to Player's hand
    void add_card(const Card &upcard) override {
       cards.push_back(upcard);
       sort(cards.begin(), cards.end());
    }

    //REQUIRES round is 1 or 2
    //MODIFIES order_up_suit
    //EFFECTS If Player wishes to order up a trump suit then return true and
    //  change order_up_suit to desired suit.  If Player wishes to pass, then do
    //  not modify order_up_suit and return false.


    void print_hand() const {
        for (size_t i=0; i < cards.size(); ++i)
        cout << "Human player " << name << "'s hand: "
        << "[" << i << "] " << cards[i] << "\n";
    }


    bool make_trump(const Card &upcard, bool is_dealer,int round, Suit &order_up_suit) const override {
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        string decision;
        cin >> decision;
        if(decision == "pass"){
            return false;
        }
        else{
            order_up_suit = string_to_suit(decision);
            return true;
        }
    }
    
    
    

    //REQUIRES Player has at least one card
    //EFFECTS  Player adds one card to hand and removes one card from hand.

    //f a Human Player is the dealer and someone orders up during the first round of making, 
    //the Human Player will pick up the upcard and discard a card of their choice. 
    //Print the Player’s hand and an option to discard the upcard. 
    //Then, prompt the user to select a card to discard. 
    //The user will then enter the number corresponding to the card they want to discard (or -1 if they want to discard the upcard).


    void add_and_discard(const Card &upcard) override {
        
        std::sort(cards.begin(), cards.end());
        print_hand();
        cards.push_back(upcard);
        
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        
        int discard;
        cin >> discard;
        //discard upcard
        if(discard == -1){
            for(int i = 0;i < cards.size(); i++){
                if(cards[i] == upcard){
                    cards.erase(cards.begin() + i);
                    return;
                }
            }
        }
        
        cards.erase(cards.begin() + discard);
        
    }

    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand according to their strategy
   // When it is the Human Player’s turn to lead or play a trick, 
   //first print the Player’s hand. Then, prompt the user to select a card. 
   //The user will then enter the number corresponding to the card they want to play.
    Card lead_card(Suit trump) override {  
        std::sort(cards.begin(), cards.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:"<<endl;
        int lead;
        cin >> lead;
        Card card = cards[lead];
        cards.erase(cards.begin() + lead);
        return card;
    }

    //
    Card play_card(const Card &led_card, Suit trump) override {  
        std::sort(cards.begin(), cards.end());
        print_hand();
        cout << "Human player " << name << ", please select a card:\n";
        int play;
        cin >> play;
        Card card = cards[play];
        cards.erase(cards.begin() + play);
        return card;

        

    }


private:
    string name;
    vector<Card> cards; 
};
Player * Player_factory (const std::string &name, const std::string &strategy) {
    if (strategy == "Simple") {
        return new SimplePlayer(name);
    } else {
        return new HumanPlayer(name);
    }
 };
 std::ostream & operator<<(std::ostream &os, const Player &p) {
    return os << p.get_name();
 }