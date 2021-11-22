#ifndef CHESS_RULES_H
#define CHESS_RULES_H

/* time to define what a board is. It is a 64 array of chars, corrosponding
 * to the positions on the board. 0 is (a, 1),  34 is (e, 3), etc. Also
 * includes a flag for which player's turn it is. White is a 0, Black is a 1
 * 
 * Piece definitions: PNBRQK, uppercase is white
 * 
 * en passant is given as the imagined location of the pawn that could be
 * enpassanted. For any pawn pushed two places it is at the location as if it
 * had only moved one place.
 * 
 * Also includes a set of flags.
 *  List of flags:
 *      * 0x1: can white castle
 *      * 0x2: can black castle
 */

typedef struct board_ {
    char board[64];
    int flags;
    char player;
    int enpassant;
} board;

// definition of a move. Is from location to location. a->b. Includes which
// player is making the move. 

typedef struct move_ {
    short start;
    short end;
    char player;
} move;

int legal_move(board* board, move move);




#endif