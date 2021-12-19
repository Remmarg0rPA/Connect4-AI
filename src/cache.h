#ifndef CACHE_H
#define CACHE_H
#include <stdint.h>
#include "game.h"

#ifndef CACHE_SIZE
#define CACHE_SIZE 5000
#endif

typedef struct HashEntry {
    char *string;
    uint16_t value;
} HashEntry;

typedef struct Cache {
    HashEntry cache[CACHE_SIZE];
    uint size;
    uint used;
} Cache;

Cache cache;

void init_cache(void);
int get_cache(Board *board);
void store_cache(Board *board, uint16_t value);
void delete_cache_entry(Board *board);

char *board_to_string(Board *board);
uint16_t hash(Board *board, uint size);

#endif