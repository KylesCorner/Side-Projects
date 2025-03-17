#include "doubly_linked_list.h"
#include <stdio.h>

int main() {
  struct List test_list;
  createList(&test_list);

  printf("--------------Insert Beginning------------------\n");
  insertBeginning(&test_list, 3);
  insertBeginning(&test_list, 2);
  insertBeginning(&test_list, 1);
  printList(&test_list);
  printListReversed(&test_list);

  printf("--------------Insert End------------------\n");
  insertEnd(&test_list, 7);
  insertEnd(&test_list, 8);
  insertEnd(&test_list, 9);
  printList(&test_list);
  printListReversed(&test_list);

  printf("--------------InsertAt------------------\n");
  insertAt(&test_list, 3, 4);
  insertAt(&test_list, 4, 5);
  insertAt(&test_list, 5, 6);
  printList(&test_list);
  printListReversed(&test_list);

  printf("--------------Search------------------\n");
  Node *curr = test_list.head;
  for(int i = 1; i <= test_list.size && curr != NULL; i++){
    printf("Search: %d\n", curr->data == (i));
    curr = curr->next;
  }
  printf("--------------Delete Head------------------\n");
  printList(&test_list);
  printListReversed(&test_list);
  printf("Deleting...\n");
  deleteHead(&test_list);
  deleteHead(&test_list);
  deleteHead(&test_list);
  printList(&test_list);
  printListReversed(&test_list);
  

  printf("--------------Delete Tail------------------\n");
  printList(&test_list);
  printListReversed(&test_list);
  printf("Deleting...\n");
  deleteTail(&test_list);
  deleteTail(&test_list);
  printList(&test_list);
  printListReversed(&test_list);

  printf("--------------Delete before------------------\n");
  printList(&test_list);
  printListReversed(&test_list);
  printf("Deleting...\n");
  deleteBefore(&test_list, 4);
  deleteBefore(&test_list, 5);
  deleteBefore(&test_list, 7);
  deleteBefore(&test_list, 69);
  printList(&test_list);
  printListReversed(&test_list);

  printf("--------------Empty List delete------------------\n");
  printf("Deleting...\n");
  deleteHead(&test_list);
  deleteTail(&test_list);
  deleteBefore(&test_list, 0);
  printList(&test_list);
  printListReversed(&test_list);

  printList(&test_list);
  printListReversed(&test_list);

  printf("Freeing list\n");
  freeList(&test_list);
  printList(&test_list);

  return 0;
}
