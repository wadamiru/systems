#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node* next;
};

struct llist {
  struct node* head;
  struct node* tail;
};

// append a new node at the end of list: O(1)
void append(struct llist* ll, int new) {
  struct node* newnd = (struct node*)malloc(sizeof(struct node));
  if (newnd==NULL) {
    printf("malloc failed\n");
    return;
  }
  newnd->data = new;
  newnd->next = NULL;

  if (ll->head==NULL) {
    ll->head = newnd;
    ll->tail = newnd;
    return;
  }

  ll->tail->next = newnd;
  ll->tail = newnd;
}

// delete an existing node given the data it holds: O(n)
void delete(struct llist* ll, int data) {
  struct node* curr = ll->head;
  struct node* prev = NULL;
  if (curr==NULL) {
    printf("deletion failed - list empty\n");
    return;
  }
  if (curr->data==data) {
    ll->head = curr->next;
    free(curr);
    return;
  }
  while (curr && curr->data != data) {
    prev = curr;
    curr = curr->next;
  }
  if (!curr) {
    printf("node not found\n");
    return;
  }
  prev->next = curr->next;
  free(curr);
}

void print_list(struct llist* ll) {
  struct node* curr = ll->head;
  while (curr) {
    printf("%d -> ", curr->data);
    curr = curr->next;
  }
  printf("NULL\n");
}

void free_list(struct llist* ll) {
  struct node* curr = ll->head;
  struct node* next;
  while (curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  ll->head = NULL;
}

int main() {
  printf("linked list impl.\n");

  struct llist list;
  list.head = NULL;
  list.tail = NULL;

  append(&list, 10);
  append(&list, 20);
  append(&list, 30);
  append(&list, 40);

  printf("Original list:\n");
  print_list(&list);

  delete(&list, 10);  // delete head
  delete(&list, 30);  // delete middle
  delete(&list, 50);  // delete non-existent: 'node to found'

  printf("After deletions:\n");
  print_list(&list);

  free_list(&list);
  return 0;
}
