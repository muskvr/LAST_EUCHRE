#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}
TEST(test_card_ctorDefault) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}
TEST(test_getRank){
    Card c(KING, HEARTS);
    ASSERT_EQUAL(KING, c.get_rank());

    Card a(QUEEN, HEARTS);
    ASSERT_EQUAL(QUEEN, a.get_rank());
    Card b(JACK, HEARTS);
    ASSERT_EQUAL(JACK, b.get_rank());
    Card d(TEN, HEARTS);
    ASSERT_EQUAL(TEN, d.get_rank());
}
TEST(test_getSuit){
    Card a(KING, HEARTS);
    ASSERT_EQUAL(HEARTS, a.get_suit());

    Card b(KING, DIAMONDS);
    ASSERT_EQUAL(DIAMONDS, b.get_suit());

    Card c(KING, CLUBS);
    ASSERT_EQUAL(CLUBS, c.get_suit());

    Card d(KING, SPADES);
    ASSERT_EQUAL(SPADES, d.get_suit());
}
TEST(test_getSuitTrump){
    
    Card a(JACK, DIAMONDS);
    ASSERT_EQUAL(HEARTS, a.get_suit(HEARTS));

    Card b(JACK, HEARTS);
    ASSERT_EQUAL(DIAMONDS, b.get_suit(DIAMONDS));

    Card c(KING, DIAMONDS);
    ASSERT_EQUAL(DIAMONDS, c.get_suit(HEARTS));

    Card d(TEN, SPADES);
    ASSERT_EQUAL(SPADES, d.get_suit(CLUBS));
}


TEST(test_isFaceOrAceTrue){
    Card a(QUEEN, HEARTS);
    ASSERT_TRUE(a.is_face_or_ace());

    Card b(JACK, HEARTS);
    ASSERT_TRUE(b.is_face_or_ace());

     Card c(KING, HEARTS);
    ASSERT_TRUE(c.is_face_or_ace());

     Card d(JACK, DIAMONDS);
    ASSERT_TRUE(d.is_face_or_ace());

     Card e(JACK, SPADES);
    ASSERT_TRUE(e.is_face_or_ace());
    
    Card z(ACE, CLUBS);
    ASSERT_TRUE(z.is_face_or_ace());
     Card f(JACK, CLUBS);
    ASSERT_TRUE(f.is_face_or_ace());
}
TEST(isFaceOrAceFalse){
    Card a(NINE, SPADES);
    ASSERT_FALSE(a.is_face_or_ace());

    Card b(TEN, HEARTS);
    ASSERT_FALSE(b.is_face_or_ace());

    Card c(NINE, HEARTS);
    ASSERT_FALSE(c.is_face_or_ace());

     Card d(TEN, HEARTS);
    ASSERT_FALSE(d.is_face_or_ace());

     Card e(NINE, DIAMONDS);
    ASSERT_FALSE(e.is_face_or_ace());

     Card f(TEN, SPADES);
    ASSERT_FALSE(f.is_face_or_ace());

     Card g(NINE, CLUBS);
    ASSERT_FALSE(g.is_face_or_ace());
}



TEST(test_isrightbowerTrue){
    Card a(JACK, SPADES);
    ASSERT_TRUE(a.is_right_bower(SPADES));

    Card b(JACK, HEARTS);
    ASSERT_TRUE(b.is_right_bower(HEARTS));

    Card c(JACK, DIAMONDS);
    ASSERT_TRUE(c.is_right_bower(DIAMONDS));

    Card d(JACK, CLUBS);
    ASSERT_TRUE(d.is_right_bower(CLUBS));
}
TEST(test_isrightbowerFALSE){
    Card a(JACK, SPADES);
    ASSERT_EQUAL(a.is_right_bower(HEARTS), false);

    Card b(TEN, SPADES);
    ASSERT_EQUAL(b.is_right_bower(SPADES), false);

    Card c(JACK, SPADES);
    ASSERT_EQUAL(c.is_right_bower(CLUBS), false);

}
TEST(test_isleftbowerTrue){
     Card a(JACK, SPADES);
    ASSERT_TRUE(a.is_left_bower(CLUBS));

    Card b(JACK, HEARTS);
    ASSERT_TRUE(b.is_left_bower(DIAMONDS));

    Card c(JACK, DIAMONDS);
    ASSERT_TRUE(c.is_left_bower(HEARTS));

    Card d(JACK, CLUBS);
    ASSERT_TRUE(d.is_left_bower(SPADES));
}

TEST(test_isleftbowerFalse){
     Card a(JACK, SPADES);
    ASSERT_EQUAL(a.is_left_bower(HEARTS), false);

    Card b(TEN, SPADES);
    ASSERT_EQUAL(b.is_left_bower(SPADES), false);

    Card c(JACK, SPADES);
    ASSERT_EQUAL(c.is_left_bower(SPADES), false);
}

TEST(test_suitNext){
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
}
TEST(test_isTrumpFALSE){
    Card c(TWO, SPADES);
    ASSERT_FALSE(c.is_trump(HEARTS));
    Card a(JACK, SPADES);
    ASSERT_FALSE(a.is_trump(HEARTS));
}
TEST(test_isTrumpTRUE){
    Card c(TWO, SPADES);
    ASSERT_TRUE(c.is_trump(SPADES));
    Card b(JACK, SPADES);
    ASSERT_TRUE(b.is_trump(CLUBS));
    Card d(JACK, CLUBS);
    ASSERT_TRUE(d.is_trump(CLUBS));
}
//comparing low-rank trumps with high-rank non-trumps, or comparing bowers against other cards.
TEST(test_cardLessTrue){
    Card a(TWO, HEARTS);
    Card b(FIVE, HEARTS);
    ASSERT_TRUE(Card_less(a, b, HEARTS));

    Card c(KING, HEARTS);
    Card d(JACK, HEARTS);
    ASSERT_TRUE(Card_less(c, d, HEARTS));

    Card e(JACK, DIAMONDS);
    Card f(JACK, HEARTS);
    ASSERT_TRUE(Card_less(e, f, HEARTS));

    Card g(KING, DIAMONDS);
    Card h(TEN, HEARTS);
    ASSERT_TRUE(Card_less(g, h, HEARTS));

    Card i(KING, SPADES);
    Card j(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(e, f, HEARTS));

    Card k(KING, DIAMONDS);
    Card l(JACK, DIAMONDS);
    ASSERT_TRUE(Card_less(k, l, HEARTS));

}
TEST(test_cardLessFalse){
    Card a(TWO, HEARTS);
    Card b(FIVE, HEARTS);
    ASSERT_FALSE(Card_less(b, a, HEARTS));

    Card c(KING, HEARTS);
    Card d(JACK, HEARTS);
    ASSERT_FALSE(Card_less(d, c, HEARTS));

    Card e(JACK, DIAMONDS);
    Card f(JACK, HEARTS);
    ASSERT_FALSE(Card_less(f,e, HEARTS));

    Card g(JACK, DIAMONDS);
    Card h(JACK, DIAMONDS);
    ASSERT_FALSE(Card_less(h,g, HEARTS));
}
TEST(test_operatorLess){
    Card a(THREE, HEARTS);
    Card b(NINE, SPADES);
    ASSERT_TRUE(a < b);
    ASSERT_FALSE(a > b);
    ASSERT_TRUE(b > a);
    ASSERT_FALSE(b < a);

    Card c(QUEEN, SPADES);
    Card d(KING, SPADES);
    ASSERT_TRUE(c < d);
    ASSERT_FALSE(c > d);
    ASSERT_FALSE(d < c);
    ASSERT_TRUE(d > c);

    Card e(QUEEN, SPADES);
    Card f(QUEEN, DIAMONDS);
    ASSERT_TRUE(e < f);
    ASSERT_FALSE(e > f);
}

TEST(test_operatorLessorEqual){
    Card a(THREE, CLUBS);
    Card b(THREE, CLUBS);
    ASSERT_TRUE(a <= b);
}
TEST(test_operatorGreater){
    Card a(FOUR, CLUBS);
    Card b(THREE, CLUBS);
    ASSERT_TRUE(a > b);
}
TEST(test_operatorGreaterorEqual){
    Card a(FOUR, CLUBS);
    Card b(FOUR, CLUBS);
    ASSERT_TRUE(a >= b);
    Card c(FOUR, CLUBS);
    Card d(THREE, CLUBS);
    ASSERT_TRUE(a >= b);
}
TEST(test_operatorEqual){
    Card a(FOUR, CLUBS);
    Card b(FOUR, CLUBS);
    ASSERT_TRUE(a == b);

    Card c(FOUR, DIAMONDS);
    Card d(FOUR, CLUBS);
    ASSERT_FALSE(c == d);

    Card e(TWO, CLUBS);
    Card f(FOUR, CLUBS);
    ASSERT_FALSE(e == f);
}
TEST(test_operatorNotEqual){
    Card a(FOUR, CLUBS);
    Card b(THREE, CLUBS);
    ASSERT_TRUE(a != b);
}
// Add more test cases here

TEST_MAIN()
