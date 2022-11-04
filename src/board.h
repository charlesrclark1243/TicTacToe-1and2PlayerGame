/***
 * File created by Charles R. Clark (call me Charlie :D)
 * File created on September 6, 2022
 * File last edited on September 12, 2022
***/

#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#define BOARD_DIM 3

#define PLAYER_ONE_MARK 'X'
#define PLAYER_TWO_MARK 'O'
#define EMPTY_MARK '\0'

#define PLAYER_ONE_WIN_SCORE 1
#define PLAYER_TWO_WIN_SCORE -1
#define NO_WIN_SCORE 0

void display(char board[BOARD_DIM][BOARD_DIM]);
int checkForWin(char board[BOARD_DIM][BOARD_DIM], int turn);
int makeMark(char board[BOARD_DIM][BOARD_DIM], int index, int turn);

#endif