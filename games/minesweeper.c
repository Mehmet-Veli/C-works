/**
 * @file
 * @brief Minesweeper Game Implementation in C
 * @details This console-based Minesweeper initializes a 9x9 grid, places 10 random mines, calculates adjacent mine counts, and allows players to reveal cells until they hit a mine or clear all safe cells.
 */

#include <stdio.h>      ///< Standard I/O library for console input and output functions
#include <stdlib.h>     ///< Standard library for functions like malloc, free, rand, srand
#include <time.h>       ///< Time library for seeding random number generator with the current time

#define ROWS 9           ///< Number of rows in the board
#define COLS 9           ///< Number of columns in the board
#define MINES 10         ///< Number of mines to place on the board

/**
 * @brief Structure representing each cell in the board.
 * @param revealed Indicates if the cell is revealed.
 * @param isMine Indicates if the cell contains a mine.
 * @param flagged Indicates if the cell is flagged by the player.
 * @param adjacentMines Stores the count of mines adjacent to the cell.
 */
typedef struct {
    int revealed;       ///< 1 if revealed, 0 otherwise
    int isMine;         ///< 1 if it contains a mine, 0 otherwise
    int flagged;        ///< 1 if flagged, 0 otherwise
    int adjacentMines;  ///< Count of mines in adjacent cells
} Cell;

Cell board[ROWS][COLS];   ///< The game board
int cellsToReveal = ROWS * COLS - MINES; ///< Number of non-mine cells to be revealed to win

// Function prototypes
void initializeBoard();
void placeMines();
void calculateAdjacentMines();
void printBoard(int revealAll);
void revealCell(int row, int col);
void toggleFlag(int row, int col);
int isInBounds(int row, int col);
void checkWinCondition();

/**
 * @brief Main function for Minesweeper.
 * @returns 0 on successful game completion
 */
int main() {
    int row, col;
    char action;

    initializeBoard();      ///< Initialize the board and set up mines
    printBoard(0);          ///< Print the board for player

    // Game loop
    while (cellsToReveal > 0) {
        printf("\nEnter row, column and action (r for reveal, f for flag/unflag, e.g., '2 3 r'): ");
        scanf("%d %d %c", &row, &col, &action);

        // Validate cell bounds
        if (!isInBounds(row, col)) {
            printf("Invalid cell. Try again.\n");
            continue;
        }

        if (action == 'r') {              // Reveal cell action
            if (board[row][col].flagged) {
                printf("Cell is flagged. Unflag it first.\n");
                continue;
            }
            revealCell(row, col);
            if (board[row][col].isMine) { // If mine, game over
                printf("Game Over! You hit a mine.\n");
                printBoard(1);            // Reveal entire board
                return 0;
            }
        } else if (action == 'f') {       // Toggle flag action
            toggleFlag(row, col);
        } else {
            printf("Invalid action. Use 'r' for reveal or 'f' for flag.\n");
            continue;
        }

        printBoard(0);                    ///< Print updated board state
        checkWinCondition();              ///< Check if player has won
    }

    printf("Congratulations! You've cleared the board.\n");
    return 0;
}

/**
 * @brief Initializes the board by setting each cell as hidden and empty.
 */
void initializeBoard() {
    srand(time(NULL)); // Seed random number generator

    // Initialize each cell
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j].revealed = 0;
            board[i][j].isMine = 0;
            board[i][j].flagged = 0;
            board[i][j].adjacentMines = 0;
        }
    }

    placeMines();                ///< Place random mines on the board
    calculateAdjacentMines();    ///< Calculate adjacent mine counts for each cell
}

/**
 * @brief Randomly places mines on the board.
 */
void placeMines() {
    int placedMines = 0;
    while (placedMines < MINES) {
        int row = rand() % ROWS;
        int col = rand() % COLS;

        if (!board[row][col].isMine) {  // Only place mine if cell is empty
            board[row][col].isMine = 1;
            placedMines++;
        }
    }
}

/**
 * @brief Calculates the number of adjacent mines for each cell.
 */
void calculateAdjacentMines() {
    int directions[8][2] = {         // Define 8 possible neighbor positions
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},         {0, 1},
        {1, -1}, {1, 0}, {1, 1}
    };

    // Iterate over each cell
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].isMine) continue;

            int count = 0;
            // Check adjacent cells for mines
            for (int k = 0; k < 8; k++) {
                int newRow = i + directions[k][0];
                int newCol = j + directions[k][1];

                if (isInBounds(newRow, newCol) && board[newRow][newCol].isMine) {
                    count++;
                }
            }
            board[i][j].adjacentMines = count;
        }
    }
}

/**
 * @brief Checks if a cell is within the board boundaries.
 * @param row Row index
 * @param col Column index
 * @returns 1 if in bounds, 0 otherwise
 */
int isInBounds(int row, int col) {
    return row >= 0 && row < ROWS && col >= 0 && col < COLS;
}

/**
 * @brief Prints the board to the console.
 * @param revealAll If true, reveals all cells including mines
 */
void printBoard(int revealAll) {
    printf("   ");
    for (int j = 0; j < COLS; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf("%d |", i);
        for (int j = 0; j < COLS; j++) {
            if (revealAll || board[i][j].revealed) {
                if (board[i][j].isMine) printf("* ");
                else printf("%d ", board[i][j].adjacentMines);
            } else if (board[i][j].flagged) {
                printf("F ");
            } else {
                printf(". ");
            }
        }
        printf("|\n");
    }
}

/**
 * @brief Reveals a cell, recursively revealing neighbors if no adjacent mines.
 * @param row Row index
 * @param col Column index
 */
void revealCell(int row, int col) {
    if (!isInBounds(row, col) || board[row][col].revealed || board[row][col].flagged) return;

    board[row][col].revealed = 1;
    if (!board[row][col].isMine) cellsToReveal--;

    if (board[row][col].adjacentMines == 0 && !board[row][col].isMine) {
        int directions[8][2] = {
            {-1, -1}, {-1, 0}, {-1, 1},
            {0, -1},         {0, 1},
            {1, -1}, {1, 0}, {1, 1}
        };

        for (int k = 0; k < 8; k++) {
            int newRow = row + directions[k][0];
            int newCol = col + directions[k][1];
            revealCell(newRow, newCol);
        }
    }
}

/**
 * @brief Toggles the flag status of a cell.
 * @param row Row index
 * @param col Column index
 */
void toggleFlag(int row, int col) {
    if (!board[row][col].revealed) {
        board[row][col].flagged = !board[row][col].flagged;
    }
}

/**
 * @brief Checks the win condition.
 */
void checkWinCondition() {
    if (cellsToReveal == 0) {
        printf("Congratulations! You've cleared the board.\n");
        printBoard(1);
        exit(0);
    }
}
