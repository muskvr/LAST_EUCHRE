#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}
TEST(test_player_add_card) {
    Player * alice = Player_factory("Alice", "Simple");
    Card c = Card(TWO, SPADES);
    alice->add_card(c);
    ASSERT_EQUAL(TWO, alice->play_card(Card(TWO, SPADES), SPADES).get_rank());

    delete alice;
}
//make Player_tests.exe
//./Player_tests.exe
TEST(test_player_make_trump) {
    Player * alice = Player_factory("Kylie", "Simple");
    Card c = Card(NINE, HEARTS);
    Card a = Card(QUEEN, HEARTS);
    Card b = Card(JACK, DIAMONDS);
    alice->add_card(c);
    alice->add_card(a);
    alice->add_card(b);
    Suit trump = DIAMONDS;
    ASSERT_TRUE(alice->make_trump(Card(KING, HEARTS), false, 1, trump));
    ASSERT_EQUAL(HEARTS, trump);
    delete alice;


    Player * sam = Player_factory("Kylie", "Simple");
    Card d = Card(NINE, SPADES);
    Card e = Card(TEN, SPADES);
    Card f = Card(JACK, DIAMONDS);
    sam->add_card(d);
    sam->add_card(e);
    sam->add_card(f);
    Suit trum = HEARTS;
    ASSERT_EQUAL(false, sam->make_trump(Card(KING, HEARTS), true, 1, trum));
    ASSERT_EQUAL(HEARTS, trum);
    delete sam;

 Player * musk = Player_factory("Kylie", "Simple");
    Card g = Card(NINE, SPADES);
    Card h = Card(TEN, SPADES);
    Card i = Card(JACK, DIAMONDS);
    musk->add_card(g);
    musk->add_card(h);
    musk->add_card(i);
    Suit t = HEARTS;
    ASSERT_EQUAL(true, musk->make_trump(Card(KING, HEARTS), true, 2, t));
    ASSERT_EQUAL(DIAMONDS, t);
    delete musk;


Player * krith = Player_factory("Kylie", "Simple");
    krith->add_card(Card(NINE, SPADES));
    krith->add_card(Card(JACK, DIAMONDS));
    krith->add_card(Card(ACE, DIAMONDS));
    Suit trumpy = HEARTS;
    ASSERT_EQUAL(true, krith->make_trump(Card(KING, HEARTS), true, 2, trumpy));
    ASSERT_EQUAL(DIAMONDS, trumpy);
    delete krith;

}

TEST(test_player_add_and_discard) {
    Player * alice = Player_factory("Alice", "Simple");
    // Adding initial cards
    alice->add_card(Card(FIVE, HEARTS));
    alice->add_card(Card(SEVEN, DIAMONDS));
    alice->add_card(Card(FOUR, SPADES));

    // Now add and discard
    alice->add_and_discard(Card(THREE, SPADES));
    Card tested = alice->play_card(Card(Card(THREE, CLUBS)), SPADES);
    ASSERT_FALSE(tested.get_rank() == FIVE);

    delete alice;

    Player * musk = Player_factory("Alice", "Simple");
    // Adding initial cards
    musk->add_card(Card(KING, SPADES));
    musk->add_card(Card(NINE, SPADES));
    musk->add_card(Card(ACE, SPADES));

    // Now add and discard
    musk->add_and_discard(Card(THREE, SPADES));
    musk->play_card(Card(THREE, SPADES), SPADES);
    musk->play_card(Card(THREE, SPADES), SPADES);
    Card test = musk->play_card(Card(THREE, SPADES), SPADES);
    ASSERT_FALSE(test.get_rank() == THREE);

    delete musk;


}
TEST(test_player_play_card_suit) {
    Player * alice = Player_factory("Alice", "Simple");
    Card lead = Card(THREE, HEARTS);
    
    alice->add_card(Card(SEVEN, DIAMONDS));
    alice->add_card(Card(THREE, SPADES));
    alice->add_card(Card(FIVE, HEARTS));
    ASSERT_EQUAL(FIVE, alice->play_card(lead, HEARTS).get_rank());

    delete alice;
}
TEST(test_player_play_card_low) {
    Player * alice = Player_factory("Alice", "Simple");
   
    alice->add_card(Card(TWO, SPADES));
    alice->add_card(Card(THREE, DIAMONDS));
    alice->add_card(Card(FIVE, DIAMONDS));
    ASSERT_EQUAL(TWO, alice->play_card(Card(FIVE, HEARTS), HEARTS).get_rank());

    delete alice;
}

TEST(test_lead_card) {
    Player * alice = Player_factory("Alice", "Simple");
    
    alice->add_card(Card(SEVEN, DIAMONDS));
    alice->add_card(Card(THREE, SPADES));
    alice->add_card(Card(FIVE, HEARTS));
    ASSERT_EQUAL(SEVEN, alice->lead_card(HEARTS).get_rank());

    delete alice;

    Player * krith = Player_factory("Alice", "Simple");
    
    krith->add_card(Card(JACK, SPADES));
    krith->add_card(Card(THREE, SPADES));
    krith->add_card(Card(KING, SPADES));
    ASSERT_EQUAL(JACK, krith->lead_card(SPADES).get_rank());

    delete krith;
}


// Add more tests here

TEST_MAIN()
