#ifndef UTILS_H
#define UTILS_H

#include "game.h"

char get_board_elem(Board *board, uint8_t row, uint8_t col);
void set_board_elem(Board *board, uint8_t row, uint8_t col, char elem);
#endif