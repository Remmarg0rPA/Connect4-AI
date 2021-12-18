#ifndef MINIMAX_H
#define MINIMAX_H
#include <stdbool.h>
#include "game.h"

int minimax_score(Board* board, char player, bool isMaxPlayer, uint maxDepth);
int minimax_ai(Board* board, char player, uint maxDepth);

#endif