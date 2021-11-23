#include "chess_rules.h"

// only include this if you are not also including the math libary

// returns the absolute value of a
int abs(int a) {
    if (a < 0)
        return -a;
    else
        return a;
}

// returns the value of the bitmap at the given index
int bit_array_return(int *array, unsigned int index) {
    int result = array[0] >> index;
    return 0x1 & result;
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

    // now check if the movement leads to the king being attacked. If so the
    // cannot be done.

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
    int mvmt = move.end - move.start;

    switch (abs(mvmt))
    {
    case K_UP_LFT:
    case K_UP_RGT:
    case K_RGT_UP:
    case K_LFT_UP:
        return 1;
        break;
    
    default:
        return 0;
        break;
    }
}

int legal_pawn(board* board, move move) {
    // first allowing movement foward for the player. If black then the allowed
    // movement is -16 or -8 if the pawn is on the / 8 = 6 row, or - 8 otherwise
    // If white then the allowed movement is +16 or +8 if on the / 8 = 1 row or
    // + 8 otherwise. Cannot move onto another piece this way. WILL NOT CHANGE
    // THE EN PASSANT STATE OF THE BOARD!!!

    int mvmt = move.end - move.start;

    if ((!board->player) && (move.start / 8 == 1)) {
        // white moving from row 2
        if (mvmt != 8 || mvmt != 16) {
            // not straight ahead movement
            if (((mvmt == 7) || (mvmt == 9)) && (board->board[move.end] != 0)) {
                // we have an angle move by the pawn, is a take
                return 1;
            }
            return 0;
        }
        if (board->board[move.end] != 0) {
            return 0;
            // we tried to move onto a piece
        } else if ((mvmt > 8) && (board->board[move.start + 8] != 0)) {
            return 0;
            // we tried to jump a piece
        }
        return 1;
    }
    if ((board->player) && (move.start / 8 == 6)) {
        // black moving from row 7
        if (mvmt != -8 || mvmt != -16) {
            // not straight ahead movement
            if (((mvmt == -7) || (mvmt == -9)) && (board->board[move.end] != 0)) {
                // angle move, lands on a piece (can't be ours by the legal move
                // function having already checked that we don't end on one of
                // our own pieces)
                return 1;
            }
            return 0;
        }
        if (board->board[move.end] != 0) {
            return 0;
            // piece on the square we want to land
        } else if ((mvmt < -8) && (board->board[move.start + 8] != 0)) {
            return 0;
            // we tried to jump a piece
        }
        return 1;
    }
    // now for standard pawn movement. Check if movement in right direction
    if ((!board->player && (mvmt > 0)) || (board->player && (mvmt < 0))) {
        // going in right direction. Movement should be +-7,8,9
        if ((abs(mvmt) / 8 == 1) && (mvmt % 8 == 0)) {
            // we are going along a column and only by one step
            if (board->board[move.end] != 0) {
                return 0;
            }
            return 1;
        }
        if ((abs(mvmt) == 7) || (abs(mvmt) == 9)) {
            if ((board->board[move.end] != 0) || (move.end == board->enpassant)) {
                return 1;
                // movement in capture pattern, landed on another piece/en passant
            }
        }
    }
    return 0;
}

int legal_king(board* board, move move) {
    // cannot move to a location that is attacked by the opponent
    if ((!board->player) && bit_array_return(board->black_attacking, move.end)) {
        return 0;
    } else if ((board->player) && bit_array_return(board->white_attacking, move.end)) {
        return 0;
    }
    int mvmt = move.end - move.start;
    switch (mvmt)
    {
    case RIGHT_DOWN:
    case DOWN:
    case LEFT_DOWN:
    case LEFT:
    case RIGHT:
    case LEFT_UP:
    case UP:
    case RIGHT_UP:
        return 1;
        break;
    
    default:
        return 0;
        break;
    }
}

