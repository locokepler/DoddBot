#ifndef CHESS_RULES_H
#define CHESS_RULES_H

#define LEFT_UP 7
#define UP 8
#define RIGHT_UP 9
#define LEFT -1
#define RIGHT 1
#define LEFT_DOWN -7
#define DOWN -8
#define RIGHT_DOWN -9

#define K_UP_LFT 15
#define K_UP_RGT 17
#define K_RGT_UP 10
#define K_RGT_DN -6
#define K_DN_RGT -15
#define K_DN_LFT -17
#define K_LFT_DN -10
#define K_LFT_UP 6

#define W_K_CASTLE 0x1
#define W_Q_CASTLE 0x2
#define B_K_CASTLE 0x4
#define B_Q_CASTLE 0x8

/* time to define what a board is. It is a 64 array of chars, corrosponding
 * to the positions on the board. 0 is (a, 1),  34 is (e, 3), etc. Also
 * includes a flag for which player's turn it is. White is a 0, Black is a 1
 * 
 * Piece definitions: PNBRQK, uppercase is white
 * 
 * en passant is given as the en passant target square
 * 
 * Also includes a set of flags.
 *  List of flags:
 *      * 0x1: white can castle kingside
 *      * 0x2: white can castle queenside
 *      * 0x4: black can castle kingside
 *      * 0x8: black can castle queenside
 * 
 * The array of pieces is setup with the piece char on the even indeces and the
 * location of that piece on the following odd index. Ex. b_pieces[0] == 'K',
 * w_pieces[1] == 59
 */

typedef struct board_ {
    char board[64];
    int flags;
    char player;
    int enpassant;
    int white_attacking[2];
    int black_attacking[2];
    char w_pieces[32];
    char b_pieces[32];
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