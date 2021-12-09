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

    std::cout << "TEST 1 -- summing values\n";
    std::vector<Card> test_hand{ Card('K', 'S'), Card('4', 'H'), Card('A', 'C') };
    assert_equal(25, b.get_sum(test_hand));

    std::cout << "\nTEST 2 -- card presence\n";
    int count = 0;
    auto deck = Deck();
    auto card = deck.get_random();
    std::cout << "RANDOM: " << card->to_string() << "\n" << std::endl;

    for (size_t i = 0; i < deck.size(); ++i) {
        std::cout << deck.get_at(i)->to_string() << std::endl;

        if (deck.get_at(i) == card) {
            count++;
        }
    }

    assert_equal(0, count);

    std::cout << "\nTEST 3 -- card counting\n";
    assert_equal(0, 1);
}
