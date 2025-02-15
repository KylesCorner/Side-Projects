#ifndef DECK_H
#define DECK_H

#include <stdio.h>
#include <stdlib.h>

// Node structure
struct Node {
    int value;
    int suit;
    struct Node *next;
};

// Deck structure
struct Deck {
    struct Node *head;
    int size;
};

// Function declarations
void newDeck(struct Deck *d);
void addDeck(struct Deck *d);
void push(struct Deck *d, struct Node *n);
struct Node* pop(struct Deck *d);
void printDeck(struct Deck *d);
void printDeckFancy(struct Deck *d);
void printDeckValues(struct Deck *d);
void deckShuffle(struct Deck *d);
int sumDeck(struct Deck *d);
void append(struct Deck *d, struct Node *n);
void freeDeck(struct Deck *d);


#endif // DECK_H

