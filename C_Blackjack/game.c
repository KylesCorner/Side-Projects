#include "deck.h"
#include <stdio.h>
int coins = 100;
int pot = 0;
int choice = 0;
int looping = 0;
struct Deck playerHand;
struct Deck dealerHand;
struct Deck dealer;

void playerUI() {
  printf("\n------------------------Player------------------------\n");
  printDeckFancy(&playerHand);
  printf("Your coins = %d\n", coins);
  printf("Pot = %d\n", pot);
  printf("\n------------------------------------------------------\n");
}
void dealerUI() {
  printf("\n------------------------Dealer------------------------\n");
  printDeckFancy(&dealerHand);
  printf("\n------------------------------------------------------\n");
}

void bet(int amount) {
  if (amount > coins) {
    amount = 0;
  }
  pot += amount;
  coins -= amount;
}

void deal() {
  bet(5); // buy in
  freeDeck(&dealerHand);
  freeDeck(&playerHand);

  if (dealer.size < 10) {
    addDeck(&dealer);
  }

  struct Node *card1 = pop(&dealer);
  struct Node *card2 = pop(&dealer);

  push(&dealerHand, card1);
  push(&dealerHand, card2);

  struct Node *card3 = pop(&dealer);
  struct Node *card4 = pop(&dealer);

  push(&playerHand, card3);
  push(&playerHand, card4);
}

void checkWinLose() {
  int dealerSum = sumDeck(&dealerHand);
  int playerSum = sumDeck(&playerHand);

  if (dealerSum == 21) {
    dealerUI();
    printf("Dealer Blackjack.\n");
    pot = 0;
    deal();
    return;
  }

  if (dealerSum > 21) {
    dealerUI();
    printf("Dealer Bust.\n");
    coins += pot;
    pot = 0;
    deal();
    return;
  }

  if (playerSum == 21) {
    playerUI();
    printf("Player Blackjack!\n");
    coins += pot * 2;
    pot = 0;
    deal();
    return;
  }

  if (playerSum > 21) {
    playerUI();
    printf("Player Bust!\n");
    pot = 0;
    deal();
    return;
  }

  if (choice == 3) {
    if (playerSum == dealerSum) {
      playerUI();
      printf("Tied!\n");
      coins += pot;
      pot = 0;
      deal();
      return;
    }
    if (playerSum > dealerSum) {
      playerUI();
      printf("Player Wins!\n");
      coins += pot * 1.5;
      pot = 0;
      deal();
      return;
    } else {
      dealerUI();
      printf("Dealer Wins.\n");
      pot = 0;
      deal();
      return;
    }
  }
}

void init() {
  freeDeck(&playerHand);
  freeDeck(&dealerHand);
  freeDeck(&dealer);

  newDeck(&dealer);
  deckShuffle(&dealer);

  deal();
}

void end() {
  freeDeck(&playerHand);
  freeDeck(&dealerHand);
  freeDeck(&dealer);
  printf("Thanks for playing!\n");
  looping = 0;
}

void hit() {
  if (dealer.size < 10) {
    addDeck(&dealer);
  }
  struct Node *card = pop(&dealer);
  push(&playerHand, card);
  checkWinLose();
}

void dealerTurn() {
  if (dealer.size < 10) {
    addDeck(&dealer);
  }

  int dealerSum = sumDeck(&dealerHand);

  while (1) {
    if (dealerSum < 16) {
      struct Node *card3 = pop(&dealer);
      push(&dealerHand, card3);
      dealerSum = sumDeck(&dealerHand);
    } else {
      break;
    }
  }
}

void go() {
  dealerTurn();
  checkWinLose();
  if (coins <= 0) {
    printf("You ran out of coins.\n");
    end();
  }
}
void gameLoop() {
  looping = 1;
  while (looping == 1) {
    playerUI();
    printf("1. Hit, 2. Bet, 3. Go, 4. Leave\n");
    scanf("%d", &choice);

    if (choice == 1) {
      hit();
    }
    if (choice == 2) {
      printf("How much would you like to bet\n");
      int betAmount = 0;
      scanf("%d", &betAmount);
      bet(betAmount);
    }

    if (choice == 3) {
      go();
    }

    if (choice == 4) {
      end();
    }
  }
}

int main() {
  init();
  gameLoop();

  return 0;
};
