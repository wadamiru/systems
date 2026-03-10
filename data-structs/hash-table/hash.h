#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct item item_t;
typedef struct item {
  char* key;
  char* val;
  item_t* next;
} item_t;

typedef struct map {
  int cap;  // capacity
  int size; // curr nitems
  // array of pointers to linked lists
  item_t** bucket;
} map_t;

void set_item (item_t* item, char* key, char* val) {
  item->key = key;
  item->val = val;
  item->next = NULL;
}

void init_map (map_t* map) {
  map->cap = 24; // initial temp cap
  map->size = 0;
  // init memory to zero --calloc
  map->bucket = (item_t**)calloc(map->cap, sizeof(item_t*));
}

int hash (map_t* map, const char* key) {
  uint64_t hash =  14695981039346656037ull; // fnv offset 64-bit, unsigned long long
  while (*key) {
    hash ^= (uint8_t)(*key++); // ops: *key -> key++
    hash *= 1099511628211ull;  // fnv 64-bit prime
  }
  return hash % map->cap;
}

int resize_&_rehash (map_t* map) { // return 1 if success, 0 if not
  int cap0 = map->cap;
  item_t** bucket0 = map->bucket;
  // double capacity
  map->cap *= 2;
  map->bucket = (item_t**)calloc(map->cap, sizeof(item_t*));
  if (map->bucket==NULL) {
    perror("[ERROR] resizing failed --calloc\n");
    map->bucket = bucket0;
    return 0;
  }
  map->size = 0;
  for (int i=0; i<cap0; i++) {
    item_t* item = bucket0[i];
    while (item) {
      item_t* next = item->next;
      int idx = hash(map, item->key);
      // set new item's next to curr head
      item->next = map->bucket[idx];
      // set head to new item
      map->bucket[idx] = item;
      item = next;
      map->size++;
    }
  }
  free(bucket0); // free odl bucket
  return 1;
}
