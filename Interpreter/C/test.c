#include "doubly_linked_list.h"
#include <stdio.h>

int main() {
  struct List test_list;
  createList(&test_list);

  printf("Testing Insert\n");
  printf("Goal = [ 1, 2, 3, ]\n");

  insertBeginning(&test_list, 1);
  insertEnd(&test_list, 3);
  insert(&test_list, 1, 2);

  printList(&test_list);

  printf("Inserting after 3\n");
  insertAfterKey(&test_list, 3, 4);
  printList(&test_list);

  printf("Inserting before 1\n");
  insertBeforeKey(&test_list, 1, 0);
  printList(&test_list);

  int searchResults = searchList(&test_list, 3);
  printf("Searching for 3: %d\n", searchResults);

  printf("Deleting 3\n");
  deleteItem(&test_list, 4);
  printList(&test_list);

  printf("Freeing list\n");
  freeList(&test_list);
  printList(&test_list);

  return 0;
}
