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
  Node *curr = searchList(&test_list, 69); 
  if(curr == NULL){
      printf("Passed! 69 not in list\n");
  }
  for(int i = 1; i <= test_list.size; i++){
    curr = searchList(&test_list, i); 
    if(curr != NULL){
      printf("Passed! %d = %d\n",curr->data,i);
    }else{
      printf("Failed! data == NULL on %d\n",i);
    }
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

  printf("--------------Delete after------------------\n");
  insertBeginning(&test_list, 4);
  insertBeginning(&test_list, 3);
  insertBeginning(&test_list, 2);
  insertBeginning(&test_list, 1);
  printList(&test_list);
  printListReversed(&test_list);
  printf("Deleting...\n");
  deleteAfter(&test_list, 69);
  deleteAfter(&test_list, 3);
  deleteAfter(&test_list, 1);
  deleteAfter(&test_list, 1);
  deleteAfter(&test_list, 1);
  deleteAfter(&test_list, 1);
  deleteAfter(&test_list, 1);
  printList(&test_list);
  printListReversed(&test_list);

  printf("--------------Delete at------------------\n");
  insertBeginning(&test_list, 4);
  insertBeginning(&test_list, 3);
  insertBeginning(&test_list, 2);
  printList(&test_list);
  printListReversed(&test_list);
  printf("Deleting...\n");
  deleteAt(&test_list, 69);
  deleteAt(&test_list, 1);
  deleteAt(&test_list, 2);
  deleteAt(&test_list, 3);
  deleteAt(&test_list, 4);
  deleteAt(&test_list, 4);
  deleteAt(&test_list, 4);
  printList(&test_list);
  printListReversed(&test_list);

  printf("--------------Empty List delete------------------\n");
  printf("Deleting...\n");
  deleteHead(&test_list);
  deleteTail(&test_list);
  deleteBefore(&test_list, 0);
  deleteAfter(&test_list, 0);
  deleteAt(&test_list, 0);
  printList(&test_list);
  printListReversed(&test_list);
  printf("--------------Merge List------------------\n");
  List test_list_2;
  createList(&test_list_2);
  insertBeginning(&test_list, 3);
  insertBeginning(&test_list, 2);
  insertBeginning(&test_list, 1);
  insertBeginning(&test_list_2, 6);
  insertBeginning(&test_list_2, 5);
  insertBeginning(&test_list_2, 4);
  printf("List 1: ");
  printList(&test_list);
  printf("List 2: ");
  printList(&test_list_2);

  mergeList(&test_list, &test_list_2);
  printList(&test_list);
  printListReversed(&test_list);

  printf("Freeing list\n");
  freeList(&test_list);
  printList(&test_list);

  return 0;
}
