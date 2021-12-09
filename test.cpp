#include "utils.h"
#include "logic.h"

class BlackjackTestHarness : public AbstractTestHarness {
private:
    Blackjack b = Blackjack(17);
public:
    BlackjackTestHarness() {
        register_test_func("",
                           [this]() -> void { assert_equal(OutcomeType::WIN, b.get_sum()); });
        register_test_func();
        register_test_func();
    }
};

class GlobalTestManager : public TestManager {
public:
    GlobalTestManager() { add_test("Blackjack Tests", BlackjackTestHarness()); }
};

int main()
{
    auto tr = GlobalTestManager();
    tr.execute();
}
