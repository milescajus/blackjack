#define SIZE 52
#include <string>
#include <iostream>

class Card
{
    public:
        char face;
        char suit;
        int value;
        int value_alt;
        bool visible;
        bool discarded;

        Card() {}
        Card(char face, char suit) {
            this->face = face;
            this->suit = suit;
            this->visible = true;
            this->discarded = false;
            this->value_alt = 0;

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
                case 'A': this->value = 11; this->value_alt = 1; break; // ace can be (1) or (11)
                default: this->value = 0;
            }
        }

        Card* take() {
            if (!discarded) { return this; }
            else { return NULL; }
        }

        std::string to_string() {
            return visible ? std::string(1, face) + ":" + std::string(1, suit) + " (" + std::to_string(value) + ")" : "#:#";
        }
};

class Deck
{
    char faces[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 'X', 'J', 'Q', 'K', 'A'};
    char suits[4] = {'S', 'D', 'H', 'C'};

    public:
        Card cards[SIZE] = {};

        Deck() {
            for (int i = 0; i < SIZE; ++i) {
                cards[i] = Card(faces[i % 13], suits[i / 13]);
            }
        }

        void shuffle() {
            for (int i = 0; i < SIZE; ++i) {
                int r_pos = rand() % (SIZE - 1);
                Card tmp = cards[i];
                cards[i] = cards[r_pos];
                cards[r_pos] = tmp;
            }
        }

        Card* get_random() {
            Card* tmp = cards[rand() % (SIZE - 1)].take();
            if (tmp == NULL) { tmp = get_random(); }
            return tmp;
        }

        std::string to_string() {
            std::string s = "";

            for (auto card : cards) {
                s += card.to_string() + '\n';
            }

            return s;
        }
};

int main()
{
    srand(time(NULL));

    auto deck = new Deck();

    std::cout << deck->to_string() << std::endl;

    deck->shuffle();

    std::cout << deck->to_string() << std::endl;

    return 0;
}
