#include <stdio.h>
#include <stdlib.h>
#include "chess_rules.h"

// takes a FEN string and makes a board out of it.
board* fen_to_simple_board(char *fen_string) {
    // first it locates all of the pieces on the board

    board* new_board = (board*)malloc(sizeof(board));
    new_board->flags = 0;
    int mode = 1; // where in the FEN string we are.
    // 1: board loading, 
    // 2: active player
    // 3: castleing abilities
    // 4: en passant target square
    // 5 and 6 would handle 50 move rule stuff

    int castle_count = 0;
    int board_loc = 56;
    for (unsigned int str_indx; fen_string[str_indx] != '\0'; str_indx++) {
        char current_char = fen_string[str_indx];

        if (current_char == ' ') {
            mode++;
        } else {
            if (mode == 1) {
                if (current_char == '/') {
                    // move to the next row
                    board_loc = 8 * ((board_loc / 8) - 1);
                } else {
                    if (current_char - '0' < 10) {
                        // we have a number here
                        board_loc = board_loc + current_char - '0';
                        // advance by the number of posiitons
                    }
                    new_board->board[board_loc] = current_char;
                }
            } else if (mode == 2) {
                if (current_char == 'w') {
                    new_board->player = 0;
                } else {
                    new_board->player = 1;
                }
            } else if (mode == 3) {
                switch (current_char) {
                    case ('K'):
                        new_board->flags = new_board->flags | W_K_CASTLE;
                        castle_count = 1;
                        break;
                    case ('Q'):
                        new_board->flags = new_board->flags | W_Q_CASTLE;
                        castle_count = 2;
                        break;
                    case ('k'):
                        new_board->flags = new_board->flags | B_K_CASTLE;
                        castle_count = 3;
                        break;
                    case ('q'):
                        new_board->flags = new_board->flags | B_Q_CASTLE;
                        castle_count = 4;
                        break;
                    default:
                        if (castle_count < 4) {
                            int mask = (0x1 << castle_count);
                            new_board->flags = new_board->flags & (~ mask);
                            castle_count++;
                        }
                        break;
                }
            } else if (mode == 4) {
                // en passant target square.
                if (current_char >= 'a') {
                    new_board->enpassant = current_char - 'a';
                } else if (current_char < '9') {
                    new_board->enpassant += 8 * (current_char - '1');
                }
            }
        }
    }
    return new_board;
}


int algebraic_to_int(char* string) {
    // takes a written square like e4 and makes it into a number (28)
    return (string[0] - 'a') + 8 * (string[1] - '1');
}

// prints the given board
void print_board(board* board) {
    if (board->player) {
        printf("Black to play:\n");
    } else {
        printf("White to play:\n");
    }
    /*
     * now to print the board. 8 columns with 8 rows. appears like this
     * Black to play:
     *   _______________________________
     * 8| r | n | b | q | k | b | n | r |
     *  |___|___|___|___|___|___|___|___|
     * 7| p | p | p | p | p | p | p | p |
     *  |___|___|___|___|___|___|___|___|
     * 6|   |   |   |   |   |   |   |   |
     *  |___|___|___|___|___|___|___|___|
     * 5|   |   |   |   |   |   |   |   |
     *  |___|___|___|___|___|___|___|___|
     * 4|   |   |   |   |   |   |   |   |
     *  |___|___|___|___|___|___|___|___|
     * 3|   |   |   |   |   |   |   |   |
     *  |___|___|___|___|___|___|___|___|
     * 2| P | P | P | P | P | P | P | P |
     *  |___|___|___|___|___|___|___|___|
     * 1| R | K | B | Q | K | B | N | R |
     *  |___|___|___|___|___|___|___|___|
     *    a   b   c   d   e   f   g   h
     */
    printf("   _______________________________\n");
    for (int i = 7; i >= 0; i--) {
        printf(" %i|", i + 1);
        for (int j = 0; j < 8; j++) {
            if (board->board[(8 * i) + j] == 0) {
                printf("   |");
            } else {
                printf(" %c |", board->board[(8 * i) + j]);
            }
        }
        printf("\n  |___|___|___|___|___|___|___|___|");
    }
    printf("    a   b   c   d   e   f   g   h\n");
}