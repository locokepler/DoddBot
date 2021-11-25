#ifndef BOARD_UTILS_H
#define BOARD_UTILS_H

// takes a FEN string and makes a board out of it.
board* fin_to_simple_board(char *fen_string);

// prints the given board
void print_board(board* board);


#endif