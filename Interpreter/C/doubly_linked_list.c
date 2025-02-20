#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node *createNode(int new_data) {
  struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = NULL;
  new_node->prev = NULL;
  return new_node;
}

void createList(struct List *empty_list) {
  empty_list->head = NULL;
  empty_list->tail = NULL;
  empty_list->size = 0;
}

void insertBeginning(struct List *l, int new_data) {
  struct Node *new_node = createNode(new_data);

  if (l->head == NULL) {

    l->head = new_node;
    l->tail = new_node;
    l->size++;
    return;
  }

  l->head->prev = new_node;
  new_node->next = l->head;

  l->head = new_node;
  l->size++;
}

void insertEnd(struct List *l, int new_data) {
  struct Node *new_node = createNode(new_data);

  if (l->tail == NULL) {

    l->head = new_node;
    l->tail = new_node;
    l->size++;
    return;
  }

  l->tail->next = new_node;
  new_node->prev = l->tail;

  l->tail = new_node;
  l->size++;
}

void insert(struct List *l, int pos, int new_data) {
  if (pos < 0) {
    pos = l->size + pos + 1;
  }

  if (pos < 0) {
    // todo Print error
    return;
  }

  if ((pos == 0) || (l->head == NULL)) {
    insertBeginning(l, new_data);
    return;
  }

  if (pos == (l->size)) {
    insertEnd(l, new_data);
    return;
  }

  if (pos > (l->size)) {
    // TODO Print error
    return;
  }

  struct Node *new_node = createNode(new_data);
  struct Node *curr = l->head;

  for (int i = 0; i < pos - 1 && curr != NULL; i++) {
    curr = curr->next;
  };

  new_node->prev = curr;
  new_node->next = curr->next;
  curr->next = new_node;
  l->size++;
}

void insertBeforeKey(struct List *l, int key, int new_data) {
  struct Node *curr = l->head;

  while (curr != NULL) {
    if (curr->data == key) {
      break;
    }
    curr = curr->next;
  }

  // given key is not found.
  if (curr == NULL) {
    // print error?
    return;
  }
  struct Node *new_node = createNode(new_data);

  new_node->prev = curr->prev;
  new_node->next = curr;

  if (curr->prev != NULL) {
    curr->prev->next = new_node;

  } else {
    l->head = new_node;
  }
  curr->prev = new_node;
  l->size++;
}

void insertAfterKey(struct List *l, int key, int new_data) {
  struct Node *curr = l->head;

  while (curr != NULL) {
    if (curr->data == key) {
      break;
    }
    curr = curr->next;
  }

  // given key is not found.
  if (curr == NULL) {
    // print error?
    return;
  }
  struct Node *new_node = createNode(new_data);

  new_node->prev = curr;
  new_node->next = curr->next;
  curr->next = new_node;

  if (new_node->next != NULL) {
    new_node->next->prev = new_node;
  }
  l->size++;
}
// Returns the index value of key, else return -1;
int searchList(struct List *l, int key) {
  struct Node *curr = l->head;
  if (curr == NULL) {
    return -1;
  }

  int index = 0;

  while (curr != NULL) {
    if (curr->data == key) {
      break;
    }
    curr = curr->next;
    index++;
  }

  if (index > 0) {
    return index;
  } else {
    return -1;
  }
}

void freeList(struct List *l) {
  struct Node *current = l->head;
  struct Node *nextNode;

  while (current) {
    nextNode = current->next; // Store reference to the next node
    free(current);            // Free current node
    current = nextNode;       // Move to the next node
  }

  l->head = NULL; // Ensure the deck is empty after freeing
  l->tail = NULL;
  l->size = 0;
}

// TODO Fix this shit
void deleteItem(struct List *l, int pos) {}
void deleteItemWithKey(struct List *l, int key) {}

void printList(struct List *l) {
  struct Node *curr = l->head;

  printf("[");
  while (curr != NULL) {
    printf(" %d,", curr->data);
    curr = curr->next;
  }
  printf(" ] size = %d\n", l->size);
}
