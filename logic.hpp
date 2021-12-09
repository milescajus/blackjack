#pragma once
#define DECK_SIZE 52
#include <string>
#include <vector>
#include <iostream>

enum OutcomeType { WIN, LOSE, DRAW };

class Card {
private:
    char face;
    char suit;
    bool discarded;
    bool visible;
    int value;

public:
    Card() {}
    Card(char face, char suit) {
        this->face = face;
        this->suit = suit;
        this->visible = true;
        this->discarded = false;

        switch(face) {
            case 'X': this->value = 10; break;
            case 'J': this->value = 10; break;
            case 'Q': this->value = 10; break;
            case 'K': this->value = 10; break;
            case 'A': this->value = 11; break; // ace can be 1 or 11, decided during turn
            default: this->value = face - '0'; break;
        }
    }

    bool operator==(const Card& rhs) {
        return this->face == rhs.face && this->suit == rhs.suit;
    }

    Card* take() {
        if (!discarded) {
            discarded = true;
            return this;
        } else { return NULL; }
    }

    char get_face() { return face; }
    int get_value() { return value; }
    void set_value(int n) { value = n; }

    std::string to_string() {
        std::string z = value < 10 ? "0" : "";
        return visible ? std::string(1, face) + ":" + std::string(1, suit) + " (" + z + std::to_string(value) + ")" : "#:#";
    }
};

class Deck {
private:
    char faces[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};
    char suits[4] = {'S', 'D', 'H', 'C'};
    Card cards[DECK_SIZE];

public:
    Deck() {
        for (int i = 0; i < DECK_SIZE; ++i) {
            cards[i] = Card(faces[i % 13], suits[i / 13]);
        }
    }

    size_t size() { return DECK_SIZE; }
    Card* get_at(size_t i) { return &cards[i]; }

    Card* get_random();
    void shuffle();
    void print();
};

class Blackjack {
private:
    Deck decks[6];
    std::vector<Card> dealer, player;
    int threshold;
    int round;

public:
    Blackjack(int n) {
        this->threshold = n;
        this->round = 0;

        for (auto deck : decks) {
            deck = Deck();
            deck.shuffle();
        }

        hit(dealer);
        hit(player);
        hit(player);
    }

    Card* get_random();
    OutcomeType play();
    int get_sum(std::vector<Card> &hand);
    void hit(std::vector<Card> &hand);
    void print_hand(std::vector<Card> &hand);
};
