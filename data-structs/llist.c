#include <stdio.h>
#include <stdlib.h>

struct node {
  int data;
  struct node* next;
};

struct llist {
  struct node* head;
};

void append(struct llist* ll, int new) {
  struct node* newnd = (struct node*)malloc(sizeof(struct node));
  newnd->data = new;
  newnd->next = NULL;

  if (ll->head==NULL) {
    ll->head = newnd;
    return;
  }

  struct node* curr = ll->head;
  while (curr->next) {
    curr = curr->next;
  }
  curr->next = newnd;
}

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

void print(struct llist* ll) {
  struct node* curr = ll->head;
  while (curr) {
    printf("%d -> ", curr->data);
    curr = curr->next;
  }
  printf("NULL\n");
}

int main() {
  printf("linked list impl.\n");
  struct llist ll;
  ll.head = NULL;
  append(&ll, 4);
  append(&ll, 6);
  append(&ll, 9);
  print(&ll);
  delete(&ll, 4);
  print(&ll);
  return 0;
}
