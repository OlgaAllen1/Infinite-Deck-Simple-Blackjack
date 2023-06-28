#include <iostream>
#include <string>
using namespace std;
enum Suit {
	HEARTS,
	CLUBS,
	SPADES,
	DIAMONDS
};

struct Card {
	int value;
	Suit suit;
};

Card getRandomCard() {
	Card card;
	card.value = rand() % 13 + 2;
	int suitValue = rand() % 4;
	switch (suitValue) {
	case 0: card.suit = HEARTS; break;
	case 1: card.suit = CLUBS; break;
	case 2: card.suit = SPADES; break;
	default: card.suit = DIAMONDS; break;
	}
	return card;
}

void showCard(Card card) {
	string output = "|";
	if (card.value >= 2 && card.value <= 10) {
		output += to_string(card.value);
	}
	else {
		switch (card.value) {
		case 11: output += "J"; break;
		case 12: output += "Q"; break;
		case 13: output += "K"; break;
		default: output += "A"; break;
		}
	}
	switch (card.suit) {
	case HEARTS: output += "H"; break;
	case DIAMONDS: output += "D"; break;
	case CLUBS: output += "C"; break;
	default: output += "S"; break;
	}
	output += "|";
	cout << output;
}

void showCards(Card* cards, int cardsCount) {
	for (int i = 0; i < cardsCount; i++) {
		showCard(cards[i]);
	}
}

void dealCardAndTotal(
	int& aceCount,
	int& total,
	Card* hand, // it's a reference to array of cards
	int& cardCount // it's a total amount of player cards
) {
	Card card = getRandomCard();
	if (card.value == 14) {
		aceCount++;
		total += 11;
	}
	else if (card.value > 10) {
		total += 10;
	}
	else {
		total += card.value;
	}
	while (aceCount > 0 && total > 21) {
		aceCount--;
		total -= 10;
	}
	hand[cardCount++] = card; // Add a card to array

}

int main()
{
	Card playerHand[10]; // array of player cards
	Card dealerHand[10]; // array of dealer cards
	int playerCardsCount = 0, dealerCardsCount = 0; // total amount of cards in hand for both players
	int playerTotal = 0, dealerTotal = 0, playerAceCount = 0, dealerAceCount = 0;
	char hitOrStand;
	srand(time(0));

	// Dealer hand
	cout << "Dealer: ";
	dealCardAndTotal(dealerAceCount, dealerTotal, dealerHand, dealerCardsCount);
	showCard(dealerHand[0]);
	dealCardAndTotal(dealerAceCount, dealerTotal, dealerHand, dealerCardsCount);
	cout << "|?|";

	// Player hand
	cout << "\nPlayer: ";
	dealCardAndTotal(playerAceCount, playerTotal, playerHand, playerCardsCount);
	dealCardAndTotal(playerAceCount, playerTotal, playerHand, playerCardsCount);
	showCards(playerHand, playerCardsCount);
	cout << "\nPlayer Total: " << playerTotal;

	while (true) {
		cout << "\n(H)it or (S)tand: ";
		cin >> hitOrStand;
		hitOrStand = tolower(hitOrStand);
		if (hitOrStand == 'h') {
			dealCardAndTotal(playerAceCount, playerTotal, playerHand, playerCardsCount);
			showCard(playerHand[playerCardsCount - 1]);
			cout << "\nPlayer Total: " << playerTotal;
			if (playerTotal > 21) {
				cout << "\nPlayer BUSTS!";
				break;
			}
		}
		else if (hitOrStand == 's') {
			cout << "Dealer: ";
			while (dealerTotal < 17) {
				dealCardAndTotal(dealerAceCount, dealerTotal, dealerHand, dealerCardsCount);
			}
			showCards(dealerHand, dealerCardsCount);
			cout << "\nDealer Total: " << dealerTotal;
			if (dealerTotal > 21) {
				cout << "\nDealer BUSTS!";
				break;
			}

			if (playerTotal == dealerTotal) {
				cout << "\nPUSH!";
				break;
			}
			else if (playerTotal < dealerTotal) {
				cout << "\nPlayer LOSE!";
				break;
			}
			else {
				cout << "\nPlayer WINS!";
				break;
			}
		}


	}

}