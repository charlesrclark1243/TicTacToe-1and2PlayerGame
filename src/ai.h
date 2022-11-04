/***
 * File created by Charles R. Clark (call me Charlie :D)
 * File created on September 7, 2022
 * File last edited on September 7, 2022
***/

#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "board.h"

static int evaluate(char board[BOARD_DIM][BOARD_DIM]);
static int isBoardTerminal(char board[BOARD_DIM][BOARD_DIM], int turn);
static int max(int a, int b);
static int min(int a, int b);
static int minimax(char board[BOARD_DIM][BOARD_DIM], int depth, int turn, int isMaximizer);
int makeBestMove(char board[BOARD_DIM][BOARD_DIM], int turn);

#endif