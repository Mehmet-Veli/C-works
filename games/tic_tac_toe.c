/**
 * @file tic-tac-toe.c
 * @author [vivekboss99](github.com/vivekboss99)
 * @author [Krishna Vedala](https://github.com/kvedala)
 * @brief Tic-Tac-Toe game implementation in C
 * @details Tic-Tac-Toe Game, where the user can decide to play with the
 * computer (single player mode) or with another user (double player mode).
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Function Declarations
static void singlemode();
static void doublemode();
static void placex(int m); // used for placing position of X by the 1st player
static void place();       // used by the computer to place O
static void placey(int m); // used in Double Player mode by the 2nd player to place O
int checkwin(); // checks every time when a player or computer places 'X' or 'O'

// Tic-Tac-Toe table
static char game_table[9];

// Main program function
int main() {   
    srand((unsigned int)time(NULL));
    int l = 0;

    do {
        // filling the table with asterisks
        for (int i = 0; i < 9; i++) game_table[i] = '*';

        // displaying the main menu
        printf("***************************************\n");
        printf("*************TIC TAC TOE***************\n");
        printf("***************************************\n");
        printf("***********1. YOU vs COMPUTER ***********\n");
        printf("***********2. YOU vs PLAYER ***********\n");
        printf("***********3. EXIT *********************\n");
        printf("Enter your choice: ");
        int n;
        scanf("%d", &n);

        switch (n) {
            case 1:
                singlemode();
                break;
            case 2:
                doublemode();
                break;
            default:
                printf("THANK YOU and EXIT!\n");
        }

        printf("Next game? (1 - YES, 0 - NO): ");
        scanf("%d", &l);

    } while (l == 1);

    return 0;
}

// Single player mode
void singlemode() {
    int m;
    int table_fill_count = 0;

    while (table_fill_count < 9) {
        // Displaying the game table
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%c ", game_table[i * 3 + j]);
            }
            printf("\n");
        }

        printf("Where would you like to place 'X'? ");
        scanf("%d", &m);
        placex(m);

        if (checkwin() == -1) {
            printf("YOU WIN\n");
            return;
        }

        if (table_fill_count < 4) {
            place();
            if (checkwin() == -2) {
                printf("YOU LOSE\n");
                return;
            }
        }

        table_fill_count++;
    }
    printf("DRAW\n");
}

// Double player mode
void doublemode() {
    int m, e1;
    int doublemode_table_count = 0;

    while (doublemode_table_count < 9) {
        // Displaying the game table
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%c ", game_table[i * 3 + j]);
            }
            printf("\n");
        }

        printf("PLAYER 1 - Where would you like to place 'X'? ");
        scanf("%d", &m);
        placex(m);
        if (checkwin() == -1) {
            printf("Player 1 WINS!\n");
            return;
        }

        if (doublemode_table_count < 4) {
            printf("PLAYER 2 - Where would you like to place 'O'? ");
            scanf("%d", &e1);
            placey(e1);
            if (checkwin() == -2) {
                printf("Player 2 WINS!\n");
                return;
            }
        }

        doublemode_table_count++;
    }
    printf("DRAW\n");
}

// Update table by placing an 'X'
void placex(int m) {
    while (1) {
        if (m >= 1 && m <= 9 && game_table[m - 1] == '*') {
            game_table[m - 1] = 'X';
            break; // exit loop after a valid move
        } else {
            printf("Invalid move, try again! (1-9): ");
            scanf("%d", &m);
        }
    }
}

// Update table by placing an 'O' (computer)
void place() {
    int e;
    do {
        e = rand() % 9;
    } while (game_table[e] != '*');

    game_table[e] = 'O';
    printf("\nComputer placed at position %d\n", e + 1);
}

// Update table by placing an 'O' (player 2)
void placey(int e1) {
    while (1) {
        if (e1 >= 1 && e1 <= 9 && game_table[e1 - 1] == '*') {
            game_table[e1 - 1] = 'O';
            break; // exit loop after a valid move
        } else {
            printf("Invalid move, try again! (1-9): ");
            scanf("%d", &e1);
        }
    }
}

// Check win conditions
int checkwin() {
    int win_conditions[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Columns
        {0, 4, 8}, {2, 4, 6}              // Diagonals
    };

    for (int i = 0; i < 8; i++) {
        if (game_table[win_conditions[i][0]] == 'X' &&
            game_table[win_conditions[i][1]] == 'X' &&
            game_table[win_conditions[i][2]] == 'X') {
            return -1; // X wins
        } else if (game_table[win_conditions[i][0]] == 'O' &&
                   game_table[win_conditions[i][1]] == 'O' &&
                   game_table[win_conditions[i][2]] == 'O') {
            return -2; // O wins
        }
    }
    return 0; // No winner
}

