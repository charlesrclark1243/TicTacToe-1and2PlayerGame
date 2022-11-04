/***
 * File created by Charles R. Clark (call me Charlie :D)
 * File created on September 6, 2022
 * File last edited on September 12, 2022
***/

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "board.h"
#include "ai.h"

// define command line screen clear command based on OS...
#ifdef _WIN32
    #define CLEAR_TERMINAL_CMD_STR "cls"
#elif (__APPLE__ || __linux__)
    #define CLEAR_TERMINAL_CMD_STR "clear"
#else
    #define CLEAR_TERMINAL_CMD_STR NULL
#endif

int main(void) {
    // define clear command string...
    char * clearCmd;
    clearCmd = CLEAR_TERMINAL_CMD_STR;

    // make sure user's OS is supported...
    start : if (clearCmd != NULL)  // code jumps here whenever answer to play again prompt is yes ('y')
        system(clearCmd);
    else {
        perror("ERROR : YOUR OS IS NOT SUPPORTED!"); // inform user that their OS is unsupported if necessary

        exit(-1);
    }
    
    // call printTitle function to print TIC TAC TOE banner...
    printTitle();

    // ask user if they prefer singleplayer or twoplayer modes...
    modeSelect : printf("\nHow many players? (1/2): "); // code jumps here if invalid input is given to mode prompt
    int numPlayers;
    scanf("%i", &numPlayers);

    // make sure input response to mode prompt is valid...
    if (numPlayers < 1 || numPlayers > 2) {
        printf("\nUh oh! Number of players must either be 1 or 2!\n");

        goto modeSelect; // go back to modeSelect prompt if input was invalid (line 41)
    }

    // ask player one to enter their name...
    printf("\nPlayer One, enter your name: ");
    char * playerOneName = getname();
    if (playerOneName == NULL)
        playerOneName = "Player One"; // if gamename function failed, just use name "Player One"

    // get player two's name...
    char * playerTwoName;
    if (numPlayers == 2) {
        // if mode is twoplayer, ask player two to enter their name...
        printf("\nPlayer Two, enter your name: ");
        playerTwoName = getname();
        if (playerTwoName == NULL)
            playerTwoName = "Player Two"; // if getname function failed, just use name "Player Two"
    }
    else
        playerTwoName = "Steve-AI"; // if mode is singleplayer, player two name is "Steve-AI"

    // initialize game board...
    char board[BOARD_DIM][BOARD_DIM] = { 0 };

    // initialize and declare loop data...
    int turn = 0, score = 0;
    while (turn < BOARD_DIM * BOARD_DIM && score == NO_WIN_SCORE) {
        // at start of each turn, print current game board...
        display(board);

        // determine which player is making their move in the current turn and store their name...
        char * playerName = ((turn % 2) + 1 == 1) ? playerOneName : playerTwoName;

        // ask player to make their move...
        printf("\n%s, make your move: ", playerName);
        
        // if singleplayer mode and turn is odd number, or, if twoplayer mode, get user input for move index...
        if ((numPlayers == 1 && (turn % 2) + 1 == 1) || numPlayers == 2) {
            int index;
            scanf("%i", &index);

            int markMade = makeMark(board, index, turn);
            if (markMade == 0) {
                // if player's mark couldn't be made at the input index, notify player and let them retake their turn...
                printf("\nUh oh! Couldn't make your mark at the specified box, please try again!\n");

                continue;
            }
        }
        else {
            // if singleplayer and turn is even number, have Steve-AI make the best possible move using minimax algorithm...
            printf("\n");

            int madeBestMove = makeBestMove(board, turn);

            if (madeBestMove == 0) {
                // this should not happen!
                perror("ERROR : AI COULD NOT MAKE BEST MOVE, MOVE MAKING FUNCTIONS NEED TO BE DEBUGGED!");
                
                exit(-2);
            }
        }

        // at the end of every turn, check if someone won (if possible) and increment turn...
        score = (turn >= 2 * (BOARD_DIM - 1)) ? checkForWin(board, turn) : NO_WIN_SCORE;
        turn++;
    }

    // after game ends, display final game board...
    display(board);

    if (score == NO_WIN_SCORE)
        printf("\nTie Game!\n"); // tie game score is 0
    else if (score == PLAYER_ONE_WIN_SCORE)
        printf("\n%s Wins!\n", playerOneName); // player one win score is 1
    else
        printf("\n%s Wins!\n", playerTwoName); // player two win score is -1

    // ask user(s) if they want to play again...
    printf("\nWanna play again? (y/n): ");
    
    char playAgain;
    scanf("\n%c", &playAgain);

    // check if input to play again prompt is yes ('y') or no (anything else)...
    if (playAgain == 'y')
        goto start; // go back to start location to start from scratch in new game (line 29)

    // make sure character strings are freed from heap (getname function allocates their space dynamically and stores them on heap)...
    free(playerOneName);
    free(playerTwoName);

    // exit main function with no error...
    return 0;
}

/***
 * this function prints the TIC TAC TOE title banner
***/
void printTitle(void) {
    // print title bar (= signs)...
    printf("\n%s\n", TITLE_BAR);

    // declare and initialize buffer character array so that TIC TAC TOE is printed in center of title bars...
    char preBuff[TITLE_PRE_BUFF_LEN + 1];
    int preBuffIndex;
    for (preBuffIndex = 0; preBuffIndex < TITLE_PRE_BUFF_LEN; preBuffIndex++)
        preBuff[preBuffIndex] = ' ';

    // print buffer before title...
    printf("%s", preBuff);

    // print title...
    printf("TIC TAC TOE\n");

    // print second title bar...
    printf("%s\n", TITLE_BAR);
}

/***
 * this function uses dynamic memory allocation to allow users to input variable-length character strings and store them on heap...
 * 
 * source of inspiration: https://stackoverflow.com/questions/8164000/how-to-dynamically-allocate-memory-space-for-a-string-and-get-that-string-from-u
***/
char * getname(void) {
    // declare and initialize character pointers...
    char * name = malloc(sizeof(char)), * temp = NULL;

    // if malloc failed, return NULL as indication that getname failed...
    if (name == NULL) {
        printf("\nERROR : COULD NOT MALLOC SPACE ON HEAP FOR PLAYER NAME, RETURNING NULL!\n");

        return name;
    }

    // declare and initialize position-tracking and character data variables...
    size_t size = sizeof(char), index = 0;
    int currChar = EOF;

    // loop until null character is detected...
    while (currChar != 0) {
        currChar = getc(stdin);

        // if user accidentally presses enter before typing out desired name, keep iterating through loop (go to next iteration)...
        if (index == 0 && currChar == '\n')
            continue;
        
        // if EOF or non-starting newline character detected, set character variable to null character (indicates end of name string)...
        if (currChar == EOF || (currChar == '\n' && index > 0))
            currChar = 0;

        // if index is at last position in the allocates space for the string, reallocate more space by doubling size...
        if (index >= size - 1) {
            temp = realloc(name, 2 * size);
            if (temp == NULL) {
                printf("\nERROR : COULD NOT REALLOC SPACE ON HEAP FOR EXPANDED NAME STRING, RETURNING NULL!\n");
                name = NULL;

                break;
            }

            name = temp;
        }

        name[index++] = currChar;
    }

    if (name != NULL) {
        temp = realloc(name, index * sizeof(char));
        if (temp == NULL)
            printf("\nWARNING : COULD NOT TRIM FINAL NAME STRING TO BETTER FIT CONTENT!\n");
        else
            name = temp;
    }

    return name;
}