#include "deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node *newNode(int value, int suit) {
  struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
  temp->value = value;
  temp->suit = suit;
  return temp;
};

void newDeck(struct Deck *d) {
  d->head = NULL;
  d->size = 0;

  for (int s = 0; s < 4; s++) {
    for (int v = 1; v <= 13; v++) {
      struct Node *temp = newNode(v, s);
      push(d, temp);
    };
  };
};

void addDeck(struct Deck *d){
  for (int s = 0; s < 4; s++) {
    for (int v = 1; v <= 13; v++) {
      struct Node *temp = newNode(v, s);
      push(d, temp);
    }
  }
  deckShuffle(d);
}

void push(struct Deck *d, struct Node *n) {

  n->next = d->head;

  d->head = n;
  d->size += 1;
}

void append(struct Deck *d, struct Node *n) {
  n->next = NULL;
  struct Node *p = d->head;
  while (p != NULL) {
    if (p->next == NULL) {
      p->next = n;
      d->size += 1;
      break;
    }
    p = p->next;
  }
}

struct Node *pop(struct Deck *d) {
  if (d->head == NULL) {
    printf("Stack underflow!");
    return NULL;
  }
  struct Node *temp = d->head;
  d->head = d->head->next;
  d->size -= 1;
  return temp;
};

void printDeck(struct Deck *d) {
  struct Node *p = d->head;
  printf("\n[");

  while (p != NULL) {
    printf(" %d:%d ", p->value, p->suit);
    p = p->next;
  }
  printf("]\n");
};
void deckShuffle(struct Deck *d) {

  // Algorithm Overview:
  // Count the number of nodes in the linked list to determine its length.
  // Generate a random permutation of indices representing the positions of
  // nodes in the shuffled list. Traverse the original linked list and copy each
  // node to the corresponding position in the shuffled list based on the random
  // permutation.
  if (d->size <= 1) {
    return;
  };

  // create an array of pointers to nodes;
  struct Node **nodeArray =
      (struct Node **)malloc(d->size * sizeof(struct Node *));
  struct Node *current = d->head;

  // fill the array with node pointers
  for (int i = 0; i < d->size; i++) {
    nodeArray[i] = current;
    current = current->next;
  };

  // fisher-yates shuffle
  srand(time(NULL)); // seed for randomness
  for (int i = d->size - 1; i > 0; i--) {
    int j = rand() % (i + 1); // random index from o to i;

    // swap  nodes in array
    struct Node *temp = nodeArray[i];
    nodeArray[i] = nodeArray[j];
    nodeArray[j] = temp;
  };
  // Rebuild the linked list using the shuffled array
  for (int i = 0; i < d->size - 1; i++) {
    nodeArray[i]->next = nodeArray[i + 1];
  }
  nodeArray[d->size - 1]->next = NULL; // Last node points to NULL

  // Update the head of the deck
  d->head = nodeArray[0];

  free(nodeArray); // Free the temporary array
};

int sumDeck(struct Deck *d) {
  int sum = 0;
  int numAces = 0;
  int valueConv[14] = {0, 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};

  struct Node *p = d->head;

  while (p != NULL) {
    int currentValue = valueConv[p->value];
    if (currentValue == 11) {
      numAces++;
    }

    sum += currentValue;

    p = p->next;
  }

  if (sum > 21 && numAces > 0) {
    for (int i = 0; i < numAces; i++) {
      sum -= 10;
    }
  }
  return sum;
}
void printDeckFancy(struct Deck *d) {
  int sum = sumDeck(d);
  char *fancyValues[] = {"",     "Ace",  "Two",   "Three", "Four",
                     "Five", "Six",  "Seven", "Eight", "Nine",
                     "Ten",  "Jack", "Queen", "King"};
  char *fancySuits[] = {"Hearts","Diamonds","Spades", "Clubs"};


  struct Node *p = d->head;

  printf("\nHand = [");
  while (p != NULL) {

    printf(" %s of %s, ", fancyValues[p->value], fancySuits[p->suit]);


    p = p->next;
  }
  printf("]\n");
  printf("Sum = %d\n", sum);
 
}
void printDeckValues(struct Deck *d) {
  int sum = sumDeck(d);
  int valueConv[14] = {0, 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
  char *fancySuits[] = {"Hearts","Diamonds","Spades", "Clubs"};


  struct Node *p = d->head;

  printf("\n[");
  while (p != NULL) {

    printf(" %d of %s ", valueConv[p->value], fancySuits[p->suit]);


    p = p->next;
  }
  printf("]\n");
  printf("Sum = %d\n", sum);
 
}
void freeDeck(struct Deck *d) {
    struct Node *current = d->head;
    struct Node *nextNode;

    while (current) {
        nextNode = current->next; // Store reference to the next node
        free(current);            // Free current node
        current = nextNode;        // Move to the next node
    }

    d->head = NULL; // Ensure the deck is empty after freeing
}

