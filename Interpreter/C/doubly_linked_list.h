#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

struct Node {
  int data;
  struct Node *prev;
  struct Node *next;
};

struct List {
  struct Node *head;
  struct Node *tail;
  int size;
};

void createList(struct List *empty_list);
void printList(struct List *l);
void insertBeginning(struct List *l, int new_data);
void insertEnd(struct List *l, int new_data);
void insert(struct List *l, int index, int new_data);
void insertBeforeKey(struct List *l, int key, int new_data);
void insertAfterKey(struct List *l, int key, int new_data);
int searchList(struct List *l, int key);
void freeList(struct List *l);
void deleteItem(struct List *l, int index);
void deleteItemWithKey(struct List *l, int key);
#endif
