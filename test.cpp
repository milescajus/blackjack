#include "utils.h"
#include "logic.h"

class BlackjackTestHarness : public AbstractTestHarness {
private:
    Blackjack b = Blackjack(17);
public:
    BlackjackTestHarness() {
        // TODO: register_test_func();
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
