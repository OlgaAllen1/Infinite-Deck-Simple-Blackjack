#include <iostream>
using namespace std;
#include <string>

enum Suit { HEARTS, DIAMONDS, CLUBS, SPADES };

struct Card {
    int value;
    Suit suit;
};

Card getRandomCard() {
    Card card;
    card.value = rand() % 13 + 2;
    int suitValue = rand() % 4;

    switch (suitValue)
    {
    case 0: card.suit = HEARTS; break;
    case 1: card.suit = DIAMONDS; break;
    case 2: card.suit = CLUBS; break;
    default: card.suit = SPADES; break;  
    }
    return card;
}

void showCard(Card card) {
    string output = "|";
    if (card.value>=2 && card.value<=10){
        output += to_string(card.value);
    }
    else {
        switch (card.value) {
        case 11: output += "J";break;
        case 12: output += "Q";break;
        case 13: output += "K";break;
        default: output += "A";break;
        }     
    }
    switch (card.suit) {
    case HEARTS: output += (char) 3;break;
    case DIAMONDS: output += "\4";break;
    case CLUBS: output += "\5"; break;
    default: output += "\6"; break;
    }
    output += "|";
    cout << output;
}

int main()
{   
    srand(time(0));
    Card card = getRandomCard();    
    cout << card.value << card.suit;
    showCard(card);

}



