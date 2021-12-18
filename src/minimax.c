#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "minimax.h"
#include "game.h"
#include "utils.h"

int minimax_score(Board* board, char player, bool isMaxPlayer, uint maxDepth){
    char c = get_winner(board);
    if (c){
        if (c == player){
            return isMaxPlayer ? 10 : -10;
        } else {
            return isMaxPlayer ? -10 : 10;
        }
    }
    else if (is_draw(board)){
        return 0;
    } 
    else if (maxDepth <= 0){
        return 0;
    }
    
    int *scores = calloc(board->width, sizeof(int));
    for (int mv = 0; mv < board->width; mv++){
        if (get_board_elem(board, 0, mv) != 0){
            continue;
        }
        make_move(board, mv, player);
        scores[mv] = minimax_score(board, (player == 'X' ? 'O' : 'X'), !isMaxPlayer, maxDepth-1);
        undo_move(board, mv);
    }

    int best_mv = 0;
    if (isMaxPlayer){
        for (int i = 0; i < board->width; i++){
            if (scores[i] == 10){
                best_mv = i;
                break;
            } else if (scores[i] == 0){
                best_mv = i;
            }
        }
    } else {
        for (int i = 0; i < board->width; i++){
            if (scores[i] == -10){
                best_mv = i;
                break;
            } else if (scores[i] == 0){
                best_mv = i;
            }
        } 
    }
    free(scores);
    return best_mv;
}

int minimax_ai(Board* board, char player, uint maxDepth){
    int *scores = malloc(board->width * sizeof(int));
    for (int mv = 0; mv < board->width; mv++){
        if (is_valid_move(board, mv)){
            make_move(board, mv, player);
            scores[mv] = minimax_score(board, (player == 'X' ? 'O' : 'X'), false, maxDepth);
            undo_move(board, mv);
        } else {
            scores[mv] = -10;
        }
    }

    int best_mv = 0;
    for (int mv = 0; mv < board->width; mv++){
        if (scores[mv] == 10){
            best_mv = mv;
            break;
        } else if (scores[mv] == 0){
            best_mv = mv;
        }
    }
    free(scores);
    return best_mv;
}