/***
 * File created by Charles R. Clark (call me Charlie :D)
 * File created on September 6, 2022
 * File last edited on September 6, 2022
***/

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <string.h>

#define TITLE_BAR "======================================================"
#define TITLE_PRE_BUFF_LEN ((strlen(TITLE_BAR) - strlen("Tic Tac Toe")) / 2)

void printTitle(void);
char * getname(void);

#endif