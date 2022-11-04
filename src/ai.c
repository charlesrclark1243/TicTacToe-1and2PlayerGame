/***
 * File created by Charles R. Clark (call me Charlie :D)
 * File created on September 7, 2022
 * File last edited on November 4, 2022
***/

#include <stdio.h>

#include "board.h"
#include "ai.h"

/***
 * evaluates the passed Tic Tac Toe board...
*/
static int evaluate(char board[BOARD_DIM][BOARD_DIM]) {
    int playerOneSum, playerTwoSum;

    // check rows for win...
    int row, col;
    for (row = 0; row < BOARD_DIM; row++) {
        playerOneSum = 0, playerTwoSum = 0;

        for (col = 0; col < BOARD_DIM; col++) {
            if (board[row][col] == PLAYER_ONE_MARK)
                playerOneSum++;
            else if (board[row][col] == PLAYER_TWO_MARK)
                playerTwoSum++;
            else
                break;
        }

        if (playerOneSum == BOARD_DIM || playerTwoSum == BOARD_DIM)
            break;
    }

    // return win value for winning player (if appropriate)...
    if (playerOneSum == BOARD_DIM)
        return PLAYER_ONE_WIN_SCORE;
    else if (playerTwoSum == BOARD_DIM)
        return PLAYER_TWO_WIN_SCORE;
    
    // check columns for win...
    for (col = 0; col < BOARD_DIM; col++) {
        playerOneSum = 0, playerTwoSum = 0;

        for (row = 0; row < BOARD_DIM; row++) {
            if (board[row][col] == PLAYER_ONE_MARK)
                playerOneSum++;
            else if (board[row][col] == PLAYER_TWO_MARK)
                playerTwoSum++;
            else
                break;
        }

        if (playerOneSum == 0 || playerTwoSum == 0)
            break;
    }

    // return win value for winning player (if appropriate)...
    if (playerOneSum == BOARD_DIM)
        return PLAYER_ONE_WIN_SCORE;
    else if (playerTwoSum == BOARD_DIM)
        return PLAYER_TWO_WIN_SCORE;

    // check top left-to-bottom right diagonal for win...
    playerOneSum = 0, playerTwoSum = 0;
    for (row = 0, col = 0; row < BOARD_DIM; row++, col++) {
        if (board[row][col] == PLAYER_ONE_MARK)
            playerOneSum++;
        else if (board[row][col] == PLAYER_TWO_MARK)
            playerTwoSum++;
        else
            break;
    }

    // return win value for winning player (if appropriate)...
    if (playerOneSum == BOARD_DIM)
        return PLAYER_ONE_WIN_SCORE;
    else if (playerTwoSum == BOARD_DIM)
        return PLAYER_TWO_WIN_SCORE;

    // check top right-to-bottom left diagonal for win...
    playerOneSum = 0, playerTwoSum = 0;
    for (row = 0, col = BOARD_DIM - 1; row < BOARD_DIM; row++, col--) {
        if (board[row][col] == PLAYER_ONE_MARK)
            playerOneSum++;
        else if (board[row][col] == PLAYER_TWO_MARK)
            playerTwoSum++;
        else
            break;
    }

    // return win value for winning player (if appropriate); otherwise, return value for no win state...
    if (playerOneSum == BOARD_DIM)
        return PLAYER_ONE_WIN_SCORE;
    else if (playerTwoSum == BOARD_DIM)
        return PLAYER_TWO_WIN_SCORE;
    else
        return NO_WIN_SCORE;
}

/***
 * determines if the passed board state is terminal, i.e., it has a winning state...
*/
static int isBoardTerminal(char board[BOARD_DIM][BOARD_DIM], int turn) {
    int row, col;

    if (evaluate(board) != NO_WIN_SCORE || turn > (BOARD_DIM * BOARD_DIM) - 1)
        return 1;
    
    return 0;
}

/***
 * generic max function (maximum of two passed integers)...
*/
static int max(int a, int b) {
    return (a >= b) ? a : b;
}

/***
 * generic min function (minimum of two passed integers)...
*/
static int min(int a, int b) {
    return (a <= b) ? a : b;
}

/***
 * Perform the minimax algorithm to determine how the AI should choose its next move...
 * 
 * Resources Used:
 *      https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/
 *      https://www.geeksforgeeks.org/introduction-to-evaluation-function-of-minimax-algorithm-in-game-theory/?ref=rp
 *      https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/
*/
static int minimax(char board[BOARD_DIM][BOARD_DIM], int depth, int turn, int isMaximizer) {
    // take appropriate action if board is terminal...
    if (isBoardTerminal(board, turn) == 1)
        return ((BOARD_DIM * BOARD_DIM) - depth) * evaluate(board);
    
    // if current "player" is maximizer, try to find maximum outcome move...
    // else if current "player" is not maximizer (is minimizer), try to find minimum outcome move...
    if (isMaximizer == 1) {
        int maxScore = PLAYER_TWO_WIN_SCORE * BOARD_DIM * BOARD_DIM;

        int row, col;
        for (row = 0; row < BOARD_DIM; row++) {
            for (col = 0; col < BOARD_DIM; col++) {
                if (board[row][col] == EMPTY_MARK) {
                    makeMark(board, (3 * row) + col + 1, turn);
                    int score = minimax(board, depth + 1, turn + 1, 0);
                    board[row][col] = EMPTY_MARK;

                    maxScore = max(maxScore, score);
                }
            }
        }

        return maxScore;
    }
    else {
        int minScore = PLAYER_ONE_WIN_SCORE * BOARD_DIM * BOARD_DIM;

        int row, col;
        for (row = 0; row < BOARD_DIM; row++) {
            for (col = 0; col < BOARD_DIM; col++) {
                if (board[row][col] == EMPTY_MARK) {
                    makeMark(board, (3 * row) + col + 1, turn);
                    int score = minimax(board, depth + 1, turn + 1, 1);
                    board[row][col] = EMPTY_MARK;

                    minScore = min(minScore, score);
                }
            }
        }

        return minScore;
    }
}

/***
 * Uses minimax algorithm defined above to define AI behavior,
 * AI makes the optimal move based on passed Tic Tac Toe board state...
*/
int makeBestMove(char board[BOARD_DIM][BOARD_DIM], int turn) {
    // determine if AI is maximizer...
    int isMaximizer = ((turn % 2) + 1 == 1) ? 1 : 0;

    int bestMoveScore = (BOARD_DIM * BOARD_DIM) * (isMaximizer == 0 ? PLAYER_ONE_WIN_SCORE : PLAYER_TWO_WIN_SCORE);
    int bestMoveIndex = -1;
    
    // determine best move...
    int row, col;
    for (row = 0; row < BOARD_DIM; row++) {
        for (col = 0; col < BOARD_DIM; col++) {
            if (board[row][col] == EMPTY_MARK) {
                int moveIndex = (3 * row) + col + 1;
                int moveScore = minimax(board, 0, turn, isMaximizer);

                if ((isMaximizer == 0 && min(bestMoveScore, moveScore) == moveScore) || 
                    (isMaximizer == 1 && max(bestMoveScore, moveScore) == moveScore)) {
                    
                    bestMoveIndex = moveIndex;
                    bestMoveScore = moveScore;
                }
            }
        }
    }

    // make mark on board based on determined best move...
    int madeMark = makeMark(board, bestMoveIndex, turn);
    if (madeMark == 0)
        printf("\nERROR : DEBUG MINIMAX ANF MAKE_BEST_MOVE AI FUNCTIONS!\n");

    return madeMark;
}