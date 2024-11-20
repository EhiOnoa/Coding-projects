// Header files
#include "memory_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Main function
int main() 
{
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Part I - Setup

    // Count the words in the "words.csv" file
    int numWords = countWords("words.csv");

    // Create an array to hold 2x cards than the words 
    Card cards[numWords * 2];

    // Load the cards from the "words.csv" file into the array
    loadCards("words.csv", cards, numWords);

    // Initialize variables to store the number of rows and columns in the board
    int rows, cols;

    // Create a 2D array of cards and get the dimensions
    Card **board = createBoard(cards, numWords, &rows, &cols);

    // Print a message indicating the number of pairs of cards on the board
    printf("Your current board contains %d pairs of cards.\n", numWords);

    // Part II - The game
	int attempts = 0;

	// Game loop
	while (true) 
	{
		// Print initial game board
		printBoard(board, rows, cols);

		// Prompt user for the first card
		int row1, col1;
		printf("Enter the first card to reveal (row and column indexes), or enter -1 to exit: ");

		// Check if the user wants to exit the program
		if (scanf("%d", &row1) == 1 || row1 == -1) 
		{
			// Exit the program
			break; 
		}

		// Validate the user input for the first card
		if (scanf("%d", &col1) != 1 || row1 < 0 || row1 >= rows || col1 < 0 || col1 >= cols || board[row1][col1].found) 
		{
			// Handle invalid input or already revealed card
				// Function: printf
			printf("Invalid input or card already revealed. Please try again.\n");
			// Flush input buffer
				// Function: fflush
			fflush(stdin);
			getchar(); // Clear the input buffer
			continue; // Go back to the beginning of the game loop
		}

        // Reveal the first card
			// Function: printBoard
		board[row1][col1].found = true;
		printBoard(board, rows, cols);

		// Prompt the user for the second card
		int row2, col2;
			// Function: scanf
		printf("Enter the second card to reveal (row and column indexes): ");

		// Check and validate user input for the second card
			// Function: scanf
		if (scanf("%d %d", &row2, &col2) != 2 || row2 < 0 || row2 >= rows || col2 < 0 || col2 >= cols || board[row2][col2].found) 
		{
			// Handle invalid input or already revealed card
				// Function: printf
			printf("Invalid input or card already revealed. Please try again.\n");
			// Function: fflush
			fflush(stdin);
			getchar(); // Clear the input buffer
			continue; // Go back to the beginning of the game loop
		}

		// Reveal the second card
		board[row2][col2].found = true;
		printBoard(board, rows, cols);

		// Check if the cards match
			// Function: strcmp
		if (strcmp(board[row1][col1].word, board[row2][col2].word) != 0) 
		{
			// If it id not a match, hide the cards again
			board[row1][col1].found = false;
			board[row2][col2].found = false;
				// Function: printf
			printf("Press Enter to continue...");
			// Function: fflush
			fflush(stdin);
			getchar();
		} 
		else 
		{
			// If a match, check for victory
			attempts++;
			if (checkVictory(board, rows, cols)) 
			{
				// Victory message
					// Function: printf
				printf("You won! You used %d attempts.\n", attempts);
				break; // Exit the game loop
			}
		}

		//hide the board with revealed words
		system("clear");
		// Increment attempts
		attempts++;
    }

    // Part III - Ending the program

	// Deallocate dynamically allocated memory
	for (int i = 0; i < rows; i++) 
	{
		free(board[i]); // Free memory for each row
	}
	free(board); // Free memory for the array of rows
	// End program message
		// Function: printf
	printf("Program ended successfully.\n");
	// Return 0 to indicate successful program execution
	return 0; 
}

