#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node* next;
  struct node* prev;
};

struct linkedlist {
  struct node* head;
  struct node* tail;
};

struct node* newnode(int data) {
  struct node* nd = (struct node*)malloc(sizeof(struct node));
  if (nd==NULL) {
    printf("malloc failed\n");
    exit(-1);
  }
  nd->data = data;
  nd->next = NULL;
  nd->prev = NULL;
  return nd;
}

void appendfront(struct linkedlist* list, int data) {
  struct node* nd = newnode(data);
  if (list->head==NULL) {
    list->head = nd;
    list->tail = nd;
    return;
  }
  nd->next = list->head;
  list->head->prev = nd;
  list->head = nd;
}

void appendback(struct linkedlist* list, int data) {
  struct node* nd = newnode(data);
  if (list->tail==NULL) {
    list->head = nd;
    list->tail = nd;
    return;
  }
  nd->prev = list->tail;
  list->tail->next = nd;
  list->tail = nd;
}

void printlist(struct linkedlist* list, int fromfront) { // fromfront: print from front to back, else back to front
  if (fromfront) {
    struct node* curr = list->head;
    while (curr) {
      printf("%d -> ", curr->data);
      curr = curr->next;
    }
  }
  else {
    struct node* curr = list->tail;
    while (curr) {
      printf("%d <- ", curr->data);
      curr = curr->prev;
    }
  }
  printf("NULL\n");
}

int main() {
  struct linkedlist list;
  list.head = NULL;
  list.tail = NULL;

  appendfront(&list, 10);
  appendfront(&list, 5);
  appendback(&list, 20);
  appendback(&list, 30);

  printlist(&list, 1); // fromfront
  printlist(&list, 0); // !fromfront

  return 0;
}
