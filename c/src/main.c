#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "game.h"
#include "minimax.h"

int main(int argc, char** argv){
    char p1 = 'X';
    char p2 = 'O';
    Board *board = new_board(7,6);

    int first = 0;
    char turn = 0;
    printf("1. Computer makes first move \n2. Player makes first move \n> ");
    scanf("%i", &first);
    fflush(stdin);
    if (first == 1){
        turn = p1;
    } else {
        render(board);
        turn = p2;
    }

    int mv = 0;
    char winner = 0;
    while (1){
        if (turn == p1){
            printf("Waiting for the computer to make a move...");
            fflush(stdout);
            mv = minimax_ai(board, p1, 5);
            printf("\r\x1B[0K\n");
        } else {
            mv = get_move();
            while (!is_valid_move(board, mv)){
                printf("Invalid move '%i'\n", mv);
                fflush(stdin);
                mv = get_move();
            }
        }
        make_move(board, mv, turn);
        render(board);

        winner = get_winner(board);
        if (winner){
            printf("'%c' won the game!\n", turn);
            break;
        } else if (is_draw(board)){
            printf("The game is a draw\n");
            break;
        }

        turn = turn == p1 ? p2 : p1;
    }

    return 0;
}