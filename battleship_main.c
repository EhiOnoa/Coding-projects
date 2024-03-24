#include "battleship_lib.h"

// Function to handle the case when the user gives up
void userGaveUp(const char solutionBoard[SIZE][SIZE]) {
    printf("You gave up! Solution Board:\n");
    printMatrix(solutionBoard);
}

int main() {
    // Part I - Setup
    initializeRandom();

    char solutionBoard[SIZE][SIZE];
    char gameBoard[SIZE][SIZE];

    buildBoard(solutionBoard, '0');
    buildBoard(gameBoard, '_');

    printf("Initial Game Board:\n");
    printMatrix(gameBoard);

    fillBoard(solutionBoard);

    // Part II - the game
    while (!checkVictory(solutionBoard, gameBoard)) {
        int row, col;

        // Ask for user input
        printf("Enter the row (0-9) where you want to shoot (or -1 to give up): ");
        scanf("%d", &row);

        // Validate user input
        if (row < -1 || row > SIZE - 1) {
            printf("Invalid row. Please enter a number between 0 and 9.\n");
            continue;
        }

        // Handle user give up
        if (row == -1) {
            userGaveUp(solutionBoard);
            break;
        }

        printf("Enter the column (0-9) where you want to shoot (or -1 to give up): ");
        scanf("%d", &col);

        // Validate user input
        if (col < -1 || col > SIZE - 1) {
            printf("Invalid column. Please enter a number between 0 and 9.\n");
            continue;
        }

        // Handle user give up
        if (col == -1) {
            userGaveUp(solutionBoard);
            break;
        }

        // Shoot at the specified position
        shoot(solutionBoard, gameBoard, row, col);

        // Print the updated game board
        printf("Updated Game Board:\n");
        printMatrix(gameBoard);

        // Check if the user won
        if (checkVictory(solutionBoard, gameBoard)) {
            printf("Congratulations! You sank all the ships!\n");
            break;
        }
    }

    return 0;
}
