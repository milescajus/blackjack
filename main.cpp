#include "logic.hpp"

int main()
{
    srand(time(NULL));
    int wins = 0, draws = 0, losses = 0;
    int threshold = 17;         // player hit cutoff sum

    for (int i = 0; i < 100; ++i) {
        auto game = Blackjack(threshold);
        std::cout << "\n\nGAME " << i + 1 << "\n--------\n\n";
        switch(game.play()) {
            case OutcomeType::WIN:
                std::cout << "WIN";
                wins++;
                break;
            case OutcomeType::DRAW:
                std::cout << "DRAW";
                draws++;
                break;
            case OutcomeType::LOSE:
                std::cout << "LOSE";
                losses++;
                break;
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n------\n\n" << wins << " wins, " << draws << " draws, " << losses << " losses" << std::endl;

    return 0;
}
