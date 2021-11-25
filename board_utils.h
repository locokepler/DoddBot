#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H
#include "chess_rules.h"

// takes a FEN string and makes a board out of it.
board* fen_to_simple_board(char *fen_string);

// prints the given board
void print_board(board* board);


#endif