#include "logic.h"

void Deck::shuffle() {
    for (int i = 0; i < DECK_SIZE; ++i) {
        int r_pos = rand() % (DECK_SIZE - 1);
        Card tmp = cards[i];
        cards[i] = cards[r_pos];
        cards[r_pos] = tmp;
    }
}

Card* Deck::get_random() {
    Card* tmp = cards[rand() % (DECK_SIZE - 1)].take();
    if (tmp == NULL) { tmp = get_random(); }
    return tmp;
}

void Deck::print() {
    std::string s = "";

    for (auto card : cards) {
        s += card.to_string() + '\n';
    }

    std::cout << s << std::endl;
}

void Blackjack::hit(std::vector<Card> &hand)
{
    hand.push_back(*Blackjack::get_random());
    if (hand[hand.size()].face == 'A' && Blackjack::get_sum(hand) + 11 > 21) {
        hand[hand.size()].value = 1;
    }
}

OutcomeType Blackjack::play()
{
    std::cout << "INIT PLAYER\t";
    Blackjack::print(Blackjack::player);
    std::cout << "INIT DEALER\t";
    Blackjack::print(Blackjack::dealer);
    
    if (Blackjack::get_sum(Blackjack::player) == 21) {
        std::cout << "NATURAL BLACKJACK\n";
        return OutcomeType::WIN;
    }

    while (Blackjack::get_sum(Blackjack::player) < Blackjack::threshold) {
        Blackjack::hit(Blackjack::player);
        std::cout << "PLAYER\t";
        Blackjack::print(Blackjack::player);
    }

    while(Blackjack::get_sum(Blackjack::dealer) < 17) {
        Blackjack::hit(Blackjack::dealer);
        std::cout << "DEALER\t";
        Blackjack::print(Blackjack::dealer);
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
        sum += card.value;
    }

    return sum;
}

Card* Blackjack::get_random() { return decks[rand() % 5].get_random(); }

void Blackjack::print(std::vector<Card> &hand)
{
    for (auto card : hand) {
        std::cout << card.to_string() << "\t";
    } std::cout << "\n";
}
