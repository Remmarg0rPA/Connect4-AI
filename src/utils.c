#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "game.h"

char get_board_elem(Board *board, uint8_t row, uint8_t col){
    return *(board->board + row*board->width + col);
}

void set_board_elem(Board *board, uint8_t row, uint8_t col, char elem){
    *(board->board + row*board->width + col) = elem;
    return;
}