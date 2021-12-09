#pragma once

#define DECK_SIZE 52
#define GAME_SIZE 6

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

enum OutcomeType { WIN, LOSE, DRAW };

class Card {
private:
    char face;
    char suit;
    bool visible;
    int value;

public:
    Card() {}
    Card(char face, char suit)
    {
        this->face = face;
        this->suit = suit;
        visible = true;

        switch(face) {
            case 'X': value = 10; break;
            case 'J': value = 10; break;
            case 'Q': value = 10; break;
            case 'K': value = 10; break;
            case 'A': value = 11; break; // ace can be 1 or 11, decided during turn
            default: value = face - '0'; break;
        }
    }

    bool operator==(const Card& rhs) { return this->face == rhs.face && this->suit == rhs.suit; }

    void set_value(int n) { value = n; }
    char get_face() { return face; }
    int get_value() { return value; }

    std::string to_string()
    {
        std::string z = value < 10 ? "0" : "";
        return visible ? std::string(1, face) + ":" + std::string(1, suit) + " (" + z + std::to_string(value) + ")" : "#:#";
    }
};

class Deck {
private:
    char faces[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};
    char suits[4] = {'S', 'D', 'H', 'C'};
    std::vector<Card> cards;

public:
    Deck()
    {
        for (size_t i = 0; i < DECK_SIZE; ++i) {
            cards.push_back(Card(faces[i % 13], suits[i / 13]));
        }
    }

    void shuffle() { std::random_shuffle(cards.begin(), cards.end()); }
    size_t size() { return DECK_SIZE; }
    bool empty() { return cards.empty(); }
    Card* get_at(size_t i) { return &cards[i]; }

    void print();
    Card take_next();
};

class Blackjack {
private:
    Deck decks[GAME_SIZE];
    std::vector<Card> dealer, player;
    int threshold;
    int round;

public:
    Blackjack(int n)
    {
        threshold = n;
        round = 0;

        for (size_t i = 0; i < GAME_SIZE; ++i) {
            decks[i] = Deck();
            decks[i].shuffle();
        }
    }

    size_t size() { return GAME_SIZE; }
    Deck* get_deck(size_t i) { return &decks[i]; }

    void hit(std::vector<Card> &hand);
    void print_hand(std::vector<Card> &hand);
    int get_sum(std::vector<Card> &hand);
    Card take_random();
    OutcomeType play();
};
