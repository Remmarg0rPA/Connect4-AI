#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minimax.h"
#include "game.h"
#include "utils.h"
#include "cache.h"

int minimax_score(Board* board, char player, int alpha, int beta, bool isMaxPlayer, uint maxDepth){
    int value = get_cache(board);
    if (value != -1){
        return value;
    }
    
    char c = get_winner(board);
    if (c){
        int ret = 0;
        if (c == player){
            ret = isMaxPlayer ? 10 : -10;
        } else {
            ret = isMaxPlayer ? -10 : 10;
        }
        store_cache(board, ret);
        return ret;
    }
    else if (is_draw(board)){
        store_cache(board, 0);
        return 0;
    } 
    else if (maxDepth <= 0){
        return 0;
    }
    
    int score;
    int mv = 0;
    while (mv < board->width){
        if (get_board_elem(board, 0, mv) != 0){
            mv++;
            continue;
        }
        make_move(board, mv, player);
        score = minimax_score(board, (player == 'X' ? 'O' : 'X'), alpha, beta, !isMaxPlayer, maxDepth-1);
        undo_move(board, mv);

        if (isMaxPlayer){
            alpha = alpha < score ? score : alpha;
            if (beta <= alpha){
                break;
            }
        }
        else {
            beta = beta > score ? score : beta;
            if (beta <= alpha){
                break;
            }
        }
        mv++;
    }
    store_cache(board, score);
    return score;
}

int minimax_ai(Board* board, char player, uint maxDepth){
    int score;
    int best_mv = -1;
    for (int mv = 0; mv < board->width; mv++){
        if (is_valid_move(board, mv)){
            make_move(board, mv, player);
            score = minimax_score(board, (player == 'X' ? 'O' : 'X'), -100, 100, false, maxDepth);
            undo_move(board, mv);
            if (score == 10){
                return mv;
            } else if (score == 0 || best_mv == -1) {
                best_mv = mv;
            }
        }
    }
    return best_mv;
}