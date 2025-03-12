
/* Pack.cpp
 *
 * Represents a pack of playing cards
 *
 * by Andrew DeOrio <awdeorio@umich.edu>
 * 2014-12-21
 */
#include <array>
#include <string>
#include <vector>
#include <cassert>
#include "Pack.hpp"
//make Pack_public_tests.exe
// ./Pack_public_tests.exe
  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on. 
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(){
    int count = 0;
    for (int s = SPADES; s <= DIAMONDS; s++) {
      Suit suit = static_cast<Suit>(s);
      //std::cout << "Suit: " << suit << std::endl;
      for(int r = NINE; r <=ACE; r++){
        Rank rank = static_cast<Rank>(r);
        //std::cout << "Rank: " << rank << std::endl;
        Card card(rank, suit);
        
        cards[count] = card;
        //std::cout << "Added " << cards[count] << " at index " << count << std::endl;
        count++;

      }
    }

    next = 0;
  }
  //make Pack_public_tests.exe
//./Pack_public_tests.exe
  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  // NOTE: The pack is initially full, with no cards dealt.
  Pack::Pack(std::istream& pack_input){
    int count = 0;
    Card card;
    while(pack_input >> card && count < PACK_SIZE){
      
      
     
      cards[count] = card;
      count++;
    }
    next = 0;
 
  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    Card card = cards[next];
    next++;
    return card;

  }
  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
    next = 0; 
  }
  //make Pack_public_tests.exe
//./Pack_public_tests.exe
  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    for (int i = 0; i < 7; i++){
      std::vector<Card> first;
      std::vector<Card> second;
      int firstI = 0;
      int secondI = 0;
      //add cards to either half
      for(int i = 0; i < PACK_SIZE/2; i++){
        first.push_back(cards[i]);
      }
      for(int i =  PACK_SIZE/2; i < PACK_SIZE; i++){
        second.push_back(cards[i]);
      }
      //add cards back to original array
      for(int i = 0; i < PACK_SIZE; i++){
        
        if(i%2==0){//if even
          cards[i] = second[secondI];
          secondI++;
        }
        else{
          
          cards[i] = first[firstI];
          firstI++;
        }
      }
    }
    
    next = 0;
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    //if next is card size then no more cards left
    return next >= cards.size();
  }
  


