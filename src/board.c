/***
 * File created by Charles R. Clark (call me Charlie :D)
 * File created on September 6, 2022
 * File last edited on November 4, 2022
***/

#include <stdio.h>

#include "board.h"

/***
 * Displays the Tic Tac Toe board in the terminal window...
*/
void display(char board[BOARD_DIM][BOARD_DIM]) {
    printf("\n");

    // use nested loops to print board, make it pretty
    int row, col;
    for (row = 0; row < BOARD_DIM; row++) {
        printf(" ");

        for (col = 0; col < BOARD_DIM; col++) {
            if (board[row][col] == EMPTY_MARK)
                printf("%2i", (BOARD_DIM * row) + col + 1);
            else
                printf("%2c", board[row][col]);
            
            if (col < BOARD_DIM - 1)
                printf("%2s", "|");
        }

        printf("\n");

        if (row < BOARD_DIM - 1)
            printf(" ---+---+---\n");
    }
}

/***
 * Checks the Tic Tac Toe board to see if the previous player won the game after placing their mark...
*/
int checkForWin(char board[BOARD_DIM][BOARD_DIM], int turn) {
    char mark = ((turn % 2) + 1 == 1) ? 'X' : 'O'; // determines which player the turn belongs to

    // configure returned information based on player the turn belongs to...
    int winScore = (mark == 'X') ? PLAYER_ONE_WIN_SCORE : PLAYER_TWO_WIN_SCORE;
    int win = 0;

    // loop through rows, check for 3-in-a-row...
    int row, col;
    for (row = 0; row < BOARD_DIM; row++) {
        int rowSum = 0;

        for (col = 0; col < BOARD_DIM; col++) {
            if (board[row][col] == mark)
                rowSum++;
        }

        if (rowSum == BOARD_DIM) {
            win = 1;
            break;
        }
    }

    // if player won, return player's win value...
    if (win == 1)
        return winScore;
    
    // loop through columns, check for 3-in-a-row...
    for (col = 0; col < BOARD_DIM; col++) {
        int colSum = 0;

        for (row = 0; row < BOARD_DIM; row++) {
            if (board[row][col] ==  mark)
                colSum++;
        }

        if (colSum == BOARD_DIM) {
            win = 1;
            break;
        }
    }

    // if player won, return player's win score...
    if (win == 1)
        return winScore;

    // check top left-to-bottom right diagonal for 3-in-a-row...
    int diagSum = 0;
    for (row = 0, col = 0; row < BOARD_DIM; row++, col++) {
        if (board[row][col] == mark)
            diagSum++;
    }

    // if player won, return player's win score...
    if (diagSum ==  BOARD_DIM)
        return winScore;
    
    // check top right-to-bottom left diagonal for 3-in-a-row...
    diagSum = 0;
    for (row = 0, col = BOARD_DIM - 1; row < BOARD_DIM; row++, col--) {
        if (board[row][col] == mark)
            diagSum++;
    }

    // if player won, return player's win score; otherwise, return value for no win state...
    if (diagSum == BOARD_DIM)
        return winScore;
    else
        return NO_WIN_SCORE;
}

/***
 * Makes the mark of the current player based on input index...
*/
int makeMark(char board[BOARD_DIM][BOARD_DIM], int index, int turn) {
    // make sure index is in bounds...
    if (index < 1 || index > BOARD_DIM * BOARD_DIM) {
        printf("\nOops! That box index is out of bounds! Please select a box index in the range [1, 9]!\n");

        return 0;
    }

    // debug notifier...
    int x = (index - 1) / BOARD_DIM, y = (index - 1) % BOARD_DIM;
    if ((x < 0 || x >= BOARD_DIM) || (y < 0 || y >= BOARD_DIM)) {
        printf("\nERROR : DEBUG MAKE_MARK FUNCTION!\n");

        return 0;
    }

    // make mark depending on determined player (based on turn number)...
    char mark = ((turn % 2) + 1 == 1) ? PLAYER_ONE_MARK : PLAYER_TWO_MARK;
    board[x][y] = mark;

    return 1;
}
