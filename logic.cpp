#include "logic.hpp"

void Deck::print() {
    std::string s = "";

    for (auto card : cards) {
        s += card.to_string() + '\n';
    }

    std::cout << s << std::endl;
}

Card Deck::take_next() {
    Card tmp = cards.back();
    cards.pop_back();
    return tmp;
}

Card Blackjack::take_random() {
    size_t d = rand() % GAME_SIZE;
    if (decks[d].empty()) { return take_random(); }
    return decks[d].take_next();
}

void Blackjack::hit(std::vector<Card> &hand)
{
    Card card = Blackjack::take_random();
    if (card.get_face() == 'A' && Blackjack::get_sum(hand) + 11 > 21) { card.set_value(1); }
    hand.push_back(card);
}

OutcomeType Blackjack::play()
{
    hit(dealer);
    hit(player);
    hit(player);

    std::cout << "INIT PLAYER\t";
    Blackjack::print_hand(Blackjack::player);
    std::cout << "INIT DEALER\t";
    Blackjack::print_hand(Blackjack::dealer);
    
    if (Blackjack::get_sum(Blackjack::player) == 21) {
        std::cout << "NATURAL BLACKJACK\n";
        return OutcomeType::WIN;
    }

    while (Blackjack::get_sum(Blackjack::player) < Blackjack::threshold) {
        round++;
        std::cout << Blackjack::round << ": PLAYER\t";
        Blackjack::hit(Blackjack::player);
        Blackjack::print_hand(Blackjack::player);
    }

    while(Blackjack::get_sum(Blackjack::dealer) < 17) {
        round++;
        std::cout << Blackjack::round << ": DEALER\t";
        Blackjack::hit(Blackjack::dealer);
        Blackjack::print_hand(Blackjack::dealer);
    }

    int dealer_total = Blackjack::get_sum(Blackjack::dealer);
    int player_total = Blackjack::get_sum(Blackjack::player);

    if (dealer_total == player_total) {
        return OutcomeType::DRAW;
    } else if (dealer_total > 21) {
        return OutcomeType::WIN;
    } else if (player_total > 21 || 21 - dealer_total < 21 - player_total) {
        return OutcomeType::LOSE;
    }

    return OutcomeType::WIN;
}

int Blackjack::get_sum(std::vector<Card> &hand)
{
    int sum = 0;
    for (auto card : hand) {
        sum += card.get_value();
    }

    return sum;
}


void Blackjack::print_hand(std::vector<Card> &hand)
{
    for (auto card : hand) {
        std::cout << card.to_string() << "\t";
    } std::cout << "\n";
}
