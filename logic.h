#pragma once
#define DECK_SIZE 52
#include <string>
#include <vector>
#include <iostream>

enum OutcomeType { WIN, LOSE, DRAW };

class Card {
public:
    char face;
    char suit;
    int value;
    bool visible;
    bool discarded;

    Card() {}
    Card(char face, char suit) {
        this->face = face;
        this->suit = suit;
        this->visible = true;
        this->discarded = false;

        switch(face) {
            case '2': this->value = 2; break;
            case '3': this->value = 3; break;
            case '4': this->value = 4; break;
            case '5': this->value = 5; break;
            case '6': this->value = 6; break;
            case '7': this->value = 7; break;
            case '8': this->value = 8; break;
            case '9': this->value = 9; break;
            case 'X': this->value = 10; break;
            case 'J': this->value = 10; break;
            case 'Q': this->value = 10; break;
            case 'K': this->value = 10; break;
            case 'A': this->value = 11; break; // ace can be (1) or (11)
            default: this->value = 0;
        }
    }

    Card* take() {
        if (!discarded) {
            discarded = true;
            return this;
        } else { return NULL; }
    }

    std::string to_string() {
        return visible ? std::string(1, face) + ":" + std::string(1, suit) + " (" + std::to_string(value) + ")" : "#:#";
    }
};

class Deck {
private:
    char faces[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};
    char suits[4] = {'S', 'D', 'H', 'C'};
    Card cards[DECK_SIZE] = {};

public:
    Deck() {
        for (int i = 0; i < DECK_SIZE; ++i) {
            cards[i] = Card(faces[i % 13], suits[i / 13]);
        }
    }

    Card* get_random();
    void shuffle();
    void print();
};

class Blackjack {
private:
    Deck decks[6];
    std::vector<Card> dealer, player;

public:
    int threshold;

    Blackjack(int n) {
        this->threshold = n;

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
    void print(std::vector<Card> &hand);
};
