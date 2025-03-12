#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;
//make Pack_tests.exe
//./Pack_tests.exe
TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}
TEST(test_dealOne){
    Pack pack;
    Card first = pack.deal_one();
    Card second = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
}
TEST(test_reset){
    Pack pack;
    Card card = pack.deal_one();
    pack.reset();
    Card third = pack.deal_one();
    ASSERT_EQUAL(NINE, card.get_rank());
    ASSERT_EQUAL(NINE, third.get_rank());
}
TEST(test_shuffle){
    Pack pack;
    Card card = pack.deal_one();
    pack.shuffle();
    Card card2 = pack.deal_one();
    ASSERT_NOT_EQUAL(card, card2);
}
TEST(test_empty){
    Pack pack;
    for(int i = 0;i < 24; i++){
        pack.deal_one();
    }
    ASSERT_TRUE(pack.empty());
}
// Add more tests here

TEST_MAIN()
