#ifndef CACHE_H
#define CACHE_H
#include <stdint.h>
#include "game.h"

#ifndef CACHE_SIZE
#define CACHE_SIZE 100000
#endif

typedef struct HashEntry {
    char *string;
    int value;
} HashEntry;

typedef struct Cache {
    HashEntry cache[CACHE_SIZE];
    uint size;
    uint used;
    uint collisions;
} Cache;

Cache cache;

void init_cache(void);
int get_cache(Board *board);
void store_cache(Board *board, int value);
void delete_cache_entry(Board *board);

char *board_to_string(Board *board);
uint hash(Board *board, uint size);

#endif