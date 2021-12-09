#include "utils.h"
#include "logic.hpp"

class BlackjackTestHarness : public AbstractTestHarness {
private:
    Blackjack b = Blackjack(17);
    std::vector<Card> test_hand;

    int sum_test()
    {
        test_hand = { Card('K', 'S'), Card('4', 'H'), Card('A', 'C') };
        return b.get_sum(test_hand);
    }

    bool shuffle_test()
    {
        bool shuffled = false;

        for (size_t i = 0; i < b.size() - 2; ++i) {
            if (b.get_deck(i)->get_at(0) != b.get_deck(i + 1)->get_at(0)) {
                shuffled = true;
            }
        }

        return shuffled;
    }

    bool presence_test()
    {
        Blackjack b = Blackjack(17);
        test_hand = {};
        bool decks_empty = true;

        for (int i = 0; i < GAME_SIZE * DECK_SIZE; ++i) {
            test_hand.push_back(b.take_random());
        }

        for (int i = 0; i < GAME_SIZE; ++i) {
            if (!b.get_deck(i)->empty()) { decks_empty = false; }
        }

        return decks_empty;
    }

public:
    BlackjackTestHarness()
    {
        register_test_func("1: Summing Values",
                [this]() -> void { assert_equal(25, sum_test()); });
        register_test_func("2: Deck Shuffling",
                [this]() -> void { assert_equal(true, shuffle_test()); });
        register_test_func("3: Card Presence",
                [this]() -> void { assert_equal(true, presence_test()); });
    }
};

class GlobalTestManager : public TestManager {
    public:
        GlobalTestManager() { add_test("Blackjack Tests", BlackjackTestHarness()); }
};

int main()
{
    srand(time(NULL));

    auto tr = GlobalTestManager();
    tr.execute();
}
