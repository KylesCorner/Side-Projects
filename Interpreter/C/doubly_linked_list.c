#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *createNode(int new_data) {
  Node *new_node = (struct Node *)malloc(sizeof(struct Node));
  new_node->data = new_data;
  new_node->next = NULL;
  new_node->prev = NULL;
  return new_node;
}

void createList(List *empty_list) {
  empty_list->head = NULL;
  empty_list->tail = NULL;
  empty_list->size = 0;
}

void insertBeginning(List *l, int new_data) {
  Node *new_node = createNode(new_data);

  // empty list
  if (l->head == NULL) {

    l->head = new_node;
    l->tail = new_node;
    l->size++;
    return;
  }

  // shift current head down and add new one
  l->head->prev = new_node;
  new_node->next = l->head;
  l->head = new_node;

  l->size++;
}

void insertEnd(List *l, int new_data) {
  struct Node *new_node = createNode(new_data);

  // List is empty
  if (l->tail == NULL) {
    l->head = new_node;
    l->tail = new_node;
    l->size++;
  } else {

    l->tail->next = new_node;
    new_node->prev = l->tail;

    l->tail = new_node;
    l->size++;
  }
}

void insertAt(List *l, int pos, int new_data) {

  // position at beginning
  if (pos == 0) {
    insertBeginning(l, new_data);
    return;
  }

  // position at end
  if (pos == l->size - 1) {
    insertEnd(l, new_data);
    return;
  }

  // Traverse list
  Node *curr = l->head;
  for (int i = 0; i < pos - 1 && curr != NULL; ++i) {
    curr = curr->next;
  }

  if (curr == NULL) {
    printf("Position is out of bounds!\n");
    return;
  }

  Node *new_node = createNode(new_data);

  // Set the prev of new node to curr
  new_node->prev = curr;

  // set the next of new node to next of curr
  new_node->next = curr->next;

  // Update the next of current node to new node
  curr->next = new_node;

  new_node->next->prev = new_node;
  l->size++;
}

void insertBeforeKey(List *l, int key, int new_data) {
  Node *curr = l->head;

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
  Node *new_node = createNode(new_data);

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

void insertAfterKey(List *l, int key, int new_data) {
  Node *curr = l->head;

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
  Node *new_node = createNode(new_data);

  new_node->prev = curr;
  new_node->next = curr->next;
  curr->next = new_node;

  if (new_node->next != NULL) {
    new_node->next->prev = new_node;
  }
  l->size++;
}
// Returns the index value of key, else return -1;
int searchList(List *l, int key) {
  Node *curr = l->head;
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

// TODO: Refactor edge cases.
void deleteHead(List *l) {
  // If empty, return NULL
  if (l->head == NULL)
    return;

  // Store in temp for deletion later
  Node *temp = l->head;

  // Single node
  if(l->head == l->tail){
    l->head = NULL;
    l->tail = NULL;
    free(temp);
    l->size--;
    return;
  }



  // Move head to the next node
  l->head = l->head->next;

  // Set prev of the new head
  if (l->head != NULL){
    l->head->prev = NULL;
  }
  // Free memory and return new head
  free(temp);
  l->size--;
}

// TODO: Refactor edge cases.
void deleteTail(List *l) {
  // If empty, return NULL
  if (l->tail == NULL) {
    return;
  }

  Node *temp = l->tail;

  // Single node
  if(l->head == l->tail){
    l->head = NULL;
    l->tail = NULL;
    free(temp);
    l->size--;
    return;
  }

  // Move tail backwards
  l->tail = l->tail->prev;

  if (l->tail != NULL)
    l->tail->next = NULL;

  free(temp);
  l->size--;
}

void deleteBefore(List *l, int key) {

  // List is already empty
  if(l->size <= 0 ||(l->head == l->tail))
    return;

  int found = 0;
  // If key is at head
  if (l->head->data == key) {
    return;
  }

  // Traverse through list
  Node *curr = l->head;
  while (curr != NULL) {

    // Key found
    if (curr->data == key) {
      found = 1;
      break;
    } else {
      found = 0;
    }
    curr = curr->next;
  }

  // Key not found
  if (!found)
    return;

  Node *toDelete = curr->prev;

  // Node to delete is at head
  if (toDelete == l->head) {
    deleteHead(l);
    return;
  }

  // isolate toDelete and free it
  curr->prev = toDelete->prev;
  toDelete->prev->next = curr;
  free(toDelete);

  l->size--;
}
void deleteAfter(List *l, int key);
void deleteAt(List *l, int key);
void freeList(List *l) {
  Node *current = l->head;
  Node *nextNode;

  while (current) {
    nextNode = current->next; // Store reference to the next node
    free(current);            // Free current node
    current = nextNode;       // Move to the next node
  }

  l->head = NULL; // Ensure the list is empty after freeing
  l->tail = NULL;
  l->size = 0;
}

void printList(List *l) {
  Node *curr = l->head;

  printf("[");
  while (curr != NULL) {
    printf(" %d,", curr->data);
    curr = curr->next;
  }
  printf(" ] size = %d\n", l->size);
}
void printListReversed(List *l) {
  Node *curr = l->tail;

  printf("[");
  while (curr != NULL) {
    printf(" %d,", curr->data);
    curr = curr->prev;
  }
  printf(" ] size = %d\n", l->size);
}
