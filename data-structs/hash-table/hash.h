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


