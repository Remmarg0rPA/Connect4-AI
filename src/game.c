#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "game.h"
#include "utils.h"

Board *new_board(uint width, uint height){
    Board *board = calloc(1, sizeof(Board));
    board->width = width;
    board->height = height;
    board->board = calloc(width * height, sizeof(char));
    return board;
}

void delete_board(Board *board){
    free(board->board);
    free(board);
    return;
}

void render(Board *board){
    char empty = '.';

    for (int i = 0; i < board->width; i++){
        printf("  %d ", i);
    }
    printf("\n");
    for (int i = 0; i < board->width; i++){
        printf("----");
    }
    printf("-\n");
    for (int row = 0; row < board->height; row++){
        printf("| ");
        for (int col = 0; col < board->width; col++){
            char c = get_board_elem(board, row, col);
            if (c == 0){
                printf("%c | ", empty);
            }
            else{
                printf("%c | ", c);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < board->width; i++){
        printf("----");
    }
    printf("\n");
    return;
}

uint8_t get_move(void){
    int col;
    printf("Which column do you want to play in? ");
    scanf("%d", &col);
    fflush(stdin);
    return col;
}

uint8_t make_move(Board *board, uint8_t col, char player){
    if (col >= board->width || get_board_elem(board, 0, col) != 0){
        return 1;
    }
    int row = 0;
    while (get_board_elem(board, row+1, col) == 0 && row+1 < board->height){
        row++;
    }
    set_board_elem(board, row, col, player);
    return 0;
}

void undo_move(Board *board, uint8_t move){
    for (int row=0; row<board->height; row++){
        if (get_board_elem(board, row, move) != 0){
            set_board_elem(board, row, move, 0);
            return;
        }
    }
    return;
}

char get_winner(Board *board){
    // Check each row
    for (int row = 0; row < board->height; row++){
        uint p1_count = 0;
        uint p2_count = 0;
        for (int col = 0; col < board->width; col++){
            // increment player counters
            char p = get_board_elem(board, row, col);
            if (p == 'X'){
                p1_count++;
                p2_count = 0;
            } else if (p == 'O'){
                p1_count = 0;
                p2_count++;
            } else {
                p1_count = 0;
                p2_count = 0;
            }
            // Check for 4 in a row
            if (p1_count == 4 || p2_count == 4){
                return p;
            }
        }
    }

    // Check each column
    for (int col = 0; col < board->width; col++){
        uint p1_count = 0;
        uint p2_count = 0;
        for (int row = 0; row < board->height; row++){
            // increment player counters
            char p = get_board_elem(board, row, col);
            if (p == 'X'){
                p1_count++;
                p2_count = 0;
            } else if (p == 'O'){
                p1_count = 0;
                p2_count++;
            } else {
                p1_count = 0;
                p2_count = 0;
            }
            // Check for 4 in a column
            if (p1_count == 4 || p2_count == 4){
                return p;
            }
        }
    }

    // Gets the columns from bottom left to top right
    for (int i = -board->height+1; i < board->width; i++){
        uint p1_count = 0, p2_count = 0;
        int row = 0;
        int col = i;
        char p = 0;
        while (row < board->height && col < board->width){
            while (col < 0){
                col++;
                row++;
            }
            if (row >= board->height){
                break;
            }
            // Get current cell and increment counters
            p = get_board_elem(board, row, col);
            if (p == 'X'){
                p1_count++;
                p2_count = 0;
            } else if (p == 'O'){
                p1_count = 0;
                p2_count++;
            } else {
                p1_count = 0;
                p2_count = 0;
            }

            // Check for 4 in a row
            if (p1_count == 4 || p2_count == 4){
                return p;
            }
            row++;
            col++;
        }
    }


    // Gets the columns from bottom right to top left
    for (int i = -board->height+1; i < board->width; i++){
        uint p1_count = 0, p2_count = 0;
        int row = board->height-1;
        int col = i;
        char p = 0;
        while (row >= 0 && col < board->width){
            while (col < 0){
                col++;
                row--;
            }
            if (row < 0){
                break;
            }
            // Get current cell and increment counters
            p = get_board_elem(board, row, col);
            if (p == 'X'){
                p1_count++;
                p2_count = 0;
            } else if (p == 'O'){
                p1_count = 0;
                p2_count++;
            } else {
                p1_count = 0;
                p2_count = 0;
            }

            // Check for 4 in a row
            if (p1_count == 4 || p2_count == 4){
                return p;
            }
            row--;
            col++;
        }
    }

    return 0;
}

bool is_draw(Board *board){
    // Checks for 0 in top row (= space left to play)
    for (int col = 0; col < board->width; col++){
        if (get_board_elem(board, 0, col) == 0)
            return false;
    }
    if (get_winner(board)){
        return false;
    }
    return true;
}

bool is_valid_move(Board *board, uint col){
    if (col < 0 || col >= board->width || get_board_elem(board, 0, col) != 0){
        return false;
    }
    return true;
}
