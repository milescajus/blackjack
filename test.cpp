#include "utils.h"
#include "logic.hpp"

class BlackjackTestHarness : public AbstractTestHarness {
private:
    Blackjack b = Blackjack(17);
    std::vector<Card> test_hand{ Card('K', 'S'), Card('4', 'H'), Card('A', 'C') };

public:
    BlackjackTestHarness() {
        register_test_func("Hand of 25",
                           [this]() -> void { assert_equal(25, b.get_sum(test_hand)); });
    }
};

class GlobalTestManager : public TestManager {
public:
    GlobalTestManager() { add_test("Blackjack Tests", BlackjackTestHarness()); }
};

int main()
{
    srand(time(NULL));

    /*
    auto tr = GlobalTestManager();
    tr.execute();
    */

    auto b = Blackjack(17);
    std::vector<Card> test_hand;

    std::cout << "TEST 1 -- summing values\n";
    test_hand = { Card('K', 'S'), Card('4', 'H'), Card('A', 'C') };
    assert_equal(25, b.get_sum(test_hand));

    std::cout << "\nTEST 2 -- deck shuffling\n";
    for (size_t i = 0; i < b.size(); ++i) {
        b.get_deck(i)->print();
    }

    assert_equal(0, 1);

    std::cout << "\nTEST 3 -- card presence\n";
    test_hand = {};

    for (int i = 0; i < GAME_SIZE * DECK_SIZE; ++i) {
        test_hand.push_back(b.take_random());
    }

    for (int i = 0; i < GAME_SIZE; ++i) {
        assert_equal(1, (int)b.get_deck(i)->empty());
    }
}
