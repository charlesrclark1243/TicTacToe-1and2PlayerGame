# Tic Tac Toe : 1 and 2 Player Game

**Table of Contents**
  - [File Descriptions](#file-descriptions)
  - [How the AI Works](#how-the-ai-works)
  - [Possible Future Work](#possible-future-work)
  - [Further Reading](#further-reading)

## File Descriptions

| File Name | Description |
| --------- | ----------- |
| [board.h](./src/board.h) | Declares the main functionalities that are specific to the working of the Tic Tac Toe board in a macOS terminal. |
| [board.c](./src/board.c) | Defines the board functionalities declared in [board.h](./src/board.h). |
| [ai.h](./src/ai.h) | Declares the main functionalities that are specific to the working of the AI opponent from single player mode. |
| [ai.c](./src/ai.c) | Defines the AI functionalities declared in [ai.h](./src/ai.h). |
| [main.h](./src/main.h) | Configures constants used throughout the implementation of the game and declares two extra functions used in the main function found in [main.c](./src/main.c). |
| [main.c](./src/main.c) | Defines the extra functions declared in [main.h](./src/main.h), as well as the main function of the game. |

## How the AI Works

The AI was implemented based on the minimax function used in Game Theory. I took a Game Theory class during my final semester as an undergraduate student at SUNY Stony Brook, and I found the material very interesting. However, I never knew that Game Theory is widely used in computer AI until I started researching how to implement an AI opponent for a Tic Tac Toe game.

The AI opponent defined in [ai.h](./src/ai.h) and [ai.c](./src/ai.c) is based on the minimax algorithm. Based on my research, minimax is a backtracking algorithm which uses the concepts of game theory to determine the optimal move for a player. The key assumption of this algorithm - one that's common in game theory, based on what I learned in the class I took at SBU - is that the other player will also play optimally, i.e., make its own optimal moves.

Minimax assigns numeric values to each possible variation of the Tic Tac Toe board based on three distinct states: player 1 wins, player 2 wins, and nobody wins (this refers both to the tie game scenario as well as the simple "game isn't over" scenario). The sum of these three numeric values should be zero, since the minimax algorithm is specific to zero-sum games (games where the sum of all possible numeric outcome values is zero)

The algorithm also assigns a label to each of the two players: one player is the "maximizer" while the other is the "minimizer." The maximizer tries to get the highest possible score, while the minimizer tries to get the lowest possible score. If the minimizer has the upper hand in a given board state, the board's value will be negative. Alternately, a board state in which the maximizer has the upper hand will be positive. The numeric value associated with each board is therefore calculated based on some heuristic which accounts for different principles and rules in game theory and is specific to the game for which the algorithm is being implemented.

## Possible Future Work

While the AI in this game is relatively fast, it's only the case because of the limited size of the board. The minimax algorithm has a time complexity of O(b^d), where b is the branching factor and d is the depth count, and a space complexity of O(bd), where b is the branching factor and d is the maximum depth of the game tree. One way to significantly improve the time complexity is to optimize the algorithm using a technique called Alpha-Beta Pruning. This is something I'd definitely like to explore, either in an expansion of the current repository or in the form of an entirely new repository, most likely using a different programming language such as C++, should time permit it.

## Further Reading
 - [Game Theory in AI - GFG](https://www.geeksforgeeks.org/game-theory-in-ai)
 - [Minimax Algorithm in Game Theory | Set 1 (Introduction) - GFG](https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/)
 - [Minimax Algorithm in Game Theory | Set 2 (Introduction to Evaluation Function) - GFG](https://www.geeksforgeeks.org/introduction-to-evaluation-function-of-minimax-algorithm-in-game-theory/)
 - [Minimax Algorithm in Game Theory | Set 3 (Tic Tac Toe AI - Finding Optimal Move) - GFG](https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-3-tic-tac-toe-ai-finding-optimal-move/)