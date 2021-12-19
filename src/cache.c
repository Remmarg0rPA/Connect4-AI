#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "game.h"
#include "utils.h"

void init_cache(void){
    for (int i = 0; i < CACHE_SIZE; i++){
        cache.cache[i] = (HashEntry){.value=0, .string=NULL};
    }
    cache.size = CACHE_SIZE;
    cache.used = 0;
    return;
}

int get_cache(Board *board){
    uint16_t h = hash(board, CACHE_SIZE);
    HashEntry he = cache.cache[h];
    if (he.string == NULL){
        return -1;
    }
    char *s = board_to_string(board);
    int ret = strcmp(s, he.string) == 0 ? he.value : -1;
    free(s);
    return ret;
}

void store_cache(Board *board, uint16_t value){
    uint16_t h = hash(board, CACHE_SIZE);
    if (cache.cache[h].string != NULL){
        free(cache.cache[h].string);
    } else {
        cache.used++;
    }
    cache.cache[h] = (HashEntry){.value = value, .string= board_to_string(board)};
    return;
}

void delete_cache_entry(Board *board){
    uint16_t h = hash(board, CACHE_SIZE);
    if (cache.cache[h].string != NULL){
        free(cache.cache[h].string);
        cache.used--;
    }
    cache.cache[h] = (HashEntry){.value = 0, .string= NULL};
    return;
}

char *board_to_string(Board *board){
    char *str = malloc(board->width*board->height + 1);
    uint idx = 0;
    char c = 0;
    char empty = '.';
    for (int row = 0; row < board->height; row++){
        for (int col = 0; col < board->width; col++){
            c = get_board_elem(board, row, col);
            str[idx] = c ? c : empty;
            idx++;
        }
    }
    return str;
}

uint16_t hash(Board *board, uint size){
    uint16_t h = 0;
    char *s = board_to_string(board);
    for (int i = 0; i < board->width*board->height; i++){
        h += s[i];
        h = (h<<1) + ((h & 0xc)>>8);
    }
    free(s);
    return (h % size);
}
