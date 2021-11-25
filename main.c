#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "chess_rules.h"
#include "board_utils.h"

/* 
 * welcome to the main code for DoddBot, the Dodd-Mead chess bot.
 * 
 */










int main(int argc, char** argv) {
    if (!strcmp(argv[1], "-t")) {
        // test run mode
        printf("running tests\n");
        for (int i = 2; i < argc; i++) {
            if (!strcmp(argv[i], "-f")) {
                // looking for FEN string
                if (i + 1 < argc) {
                    board* test_board = fen_to_simple_board(argv[i + 1]);
                    print_board(test_board);
                    i++;
                }
            }
        }
    }
}