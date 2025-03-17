#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

// struct Node {
//   int data;
//   struct Node *prev;
//   struct Node *next;
// };

typedef struct Node {
  int data;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct List {
  struct Node *head;
  struct Node *tail;
  int size;
} List;

void createList(List *empty_list);
void printList(List *l);
void printListReversed(List *l);
void insertBeginning(List *l, int new_data);
void insertEnd(List *l, int new_data);
void insertAt(List *l, int index, int new_data);
void insertBeforeKey(List *l, int key, int new_data);
void insertAfterKey(List *l, int key, int new_data);
int searchList(List *l, int key);
void deleteHead(List *l);
void deleteBefore(List *l, int key);
void deleteAfter(List *l, int key);
void deleteAt(List *l, int key);
void deleteTail(List *l);
void freeList(List *l);
#endif
