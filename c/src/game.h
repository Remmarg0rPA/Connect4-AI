#ifndef GAME_H
#define GAME_H
#include <stdint.h>
#include <stdbool.h>
#include "game.h"

typedef struct Board {
    uint8_t height;
    uint8_t width;
    char *board;
} Board;


Board *new_board(uint width, uint height);
void delete_board(Board *board);

void render(Board *board);
uint8_t get_move(void);

uint8_t make_move(Board *board, uint8_t col, char player);
void undo_move(Board *board, uint8_t move);

char get_winner(Board *board);
bool is_draw(Board *board);
bool is_valid_move(Board *board, uint col);

#endif