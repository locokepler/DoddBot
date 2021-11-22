#include "chess_rules.h"

// only include this if you are not also including the math libary

// returns the absolute value of a
int abs(int a) {
    if (a < 0)
        return -a;
    else
        return a;
}

/* 
 * legal_move:
 * checks to see if a move is a legal play on a given board. For a given move
 * it first looks to see if the player actually has a piece on the start square
 * and if it does not have a piece on the end square. Then it checks if the
 * move pattern is legal. Movement in right direction, not jumping pieces, etc.
 * The movement of specific pieces is generally done in their own functions.
 */
int legal_move(board* board, move move) {
    // first check that it is the right player
    if (board->player != move.player)
        return 0;

    // is there actually any movement given?
    if (move.start == move.end)
        return 0;
    
    // now check both moves are on the board
    if ((move.start < 0) || (move.start > 63) || (move.end < 0) || (move.end > 63))
        return 0;

    // does the player have a piece on that square?
    char move_piece = board->board[move.start];
    if (((move_piece > 'Z') && (!move.player)) || ((move_piece < 'Z') && move.player))
        return 0;

    // does the player already have a piece on the ending square?
    char end_piece = board->board[move.end];
    if (((end_piece > 'Z') && move.player) || ((end_piece < 'Z') && (!move.player)))
        return 0;

    // general checks done, now we need to check the behavior using the rules
    // of individual pieces. 

}

int legal_rook(board* board, move move) {
    // first, is the move along a row or column
    int mvmt;
    if (move.start / 8 == move.end / 8) {
        // we goin sideways
        mvmt = abs(move.start - move.end) / (move.start - move.end);
    } else if (move.start % 8 == move.end % 8) {
        mvmt = 8 * abs(move.start - move.end) / (move.start - move.end);
    } else {
        return 0;
    }

    // finally check if the movement is trying to jump another piece
    for (int i = move.start; i != move.end; i + mvmt) {
        if (board->board[i] != 0) {
            // there is another piece on this location! We cannot jump in
            return 0;
        }
    }
    return 1;
}

int legal_bishop(board* board, move move) {
    // first is it along a diagonal?
    int mvmt;
    if (move.start % 9 == move.end % 9) {
        mvmt = 9 * (abs(move.start - move.end) / (move.start - move.end));
    } else if (move.start % 7 == move.end % 7) {
        mvmt = 7 * (abs(move.start - move.end) / (move.start - move.end));
    }

    // finally check if the movement is trying to jump another piece
    for (int i = move.start; i != move.end; i + mvmt) {
        if (board->board[i] != 0) {
            return 0;
        }
    }
    return 1;
}

int legal_queen(board* board, move move) {
    if (legal_bishop(board, move))
        return 1;
    if (legal_rook(board, move))
        return 1;
    return 0;
}

int legal_knight(board* board, move move) {
    int mvmt = abs(move.end - move.start);

    switch (mvmt)
    {
    case 6:
        return 1;
        break;
    case 10:
        return 1;
        break;
    case 15:
        return 1;
        break;
    case 17:
        return 1;
        break;
    
    default:
        return 0;
        break;
    }
}

int legal_pawn(board* board, move move) {
    // first allowing movement foward for the player. If black then the allowed
    // movement is -16 or -8 if the pawn is on the / 8 = 7 row, or - 8 otherwise
    // If white then the allowed movement is +16 or +8 if on the / 8 = 1 row or
    // + 8 otherwise. Cannot move onto another piece this way. WILL NOT CHANGE
    // THE EN PASSANT STATE OF THE BOARD!!!

    int mvmt = move.start - move.end;

    if ((!player) && (move.start / 8 == 1)) {
        if (mvmt != 8 || mvmt !=)
    }
}