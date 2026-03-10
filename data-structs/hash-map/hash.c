#include "hash_map.h"

int main ()
{
  map_t* map = (map_t *) malloc(sizeof(map_t));
  init_map(map);

  insert(map, "rock1", "wanni1");
  insert(map, "rock1", "wanni12");
  insert(map, "rock2", "wanni2");
  insert(map, "rock3", "wanni3");
  insert(map, "rock4", "wanni4");

  print_map(map);

  delete(map, "rock1");
  delete(map, "rock2");

  print_map(map);

  printf("rock1: %s\n", search(map, "rock1"));
  printf("rock2: %s\n", search(map, "rock2"));

  return 0;
}
