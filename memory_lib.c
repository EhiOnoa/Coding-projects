// Header files
#include "memory_lib.h"
#include <math.h>
#include <string.h>
#include <time.h>

int countWords(const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (!file) 
	{
		// Error opening file message
        perror("Error opening file");
		// exit 
        exit(EXIT_FAILURE);
    }
	// initialize the count assign 0 to count
    int count = 0;
    char buffer[MAX_LETTERS + 1];
    while (fscanf(file, "%s", buffer) != EOF) 
	{
		// Increment count
        count++;
    }
	// Close file
    fclose(file);
	// return count 
    return count;
}

void loadCards(const char *filename, Card *cards, int size) {
    // Open the file
    FILE *file = fopen(filename, "r");
    if (!file) {
        // Print an error message and exit the program if the file cannot be opened
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Loop through each card in the file
    for (int i = 0; i < size; i++) {
        // Read a word from the file into a buffer
        char buffer[MAX_LETTERS + 1];
		// Function: fscanf
        fscanf(file, "%s", buffer);

        // Copy the word from the buffer to the current card in the array
        strcpy(cards[i].word, buffer);
        
        // Set the 'found' flag to false for the current card
        cards[i].found = false;

        // Duplicate the current card in the array to have pairs of cards
        cards[size + i] = cards[i];
    }

    // Close the file
    fclose(file);

    // Shuffle the cards to randomize their order
    shuffleCards(cards, size * 2);
}

// Shuffle cards function
void shuffleCards(Card *cards, int size) {
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Iterate through each card in the array
    for (int i = 0; i < size; i++) {
        // Generate a random index j within the range of the array size
        int j = rand() % size;

        // Swap cards[i] and cards[j]
        Card temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
}

// Get dimensions
void getDimensions(int length, int *row, int *col) 
{
    // Set both the row and column to the square root of the length
    *row = *col = (int)sqrt(length);

    // Adjust the column value until the product of both the row and column is greater than or equal to length
    while (*row * *col < length) 
    {
        (*col)++; // Increment the column value
    }
}

// createBaord function
Card **createBoard(Card *cards, int size, int *rows, int *cols) {
    // Determine the dimensions of the board based on the number of cards
    getDimensions(size * 2, rows, cols);

    // Distribute the memory for the board
    Card **board = (Card **)malloc(*rows * sizeof(Card *));
    for (int i = 0; i < *rows; i++) {
        board[i] = (Card *)malloc(*cols * sizeof(Card));
    }

    // fill the board with cards
    int k = 0;
    for (int i = 0; i < *rows; i++) {
        for (int j = 0; j < *cols; j++) {
            if (k < size * 2) {
                // Copy a card from the array for cards to the board
                board[i][j] = cards[k++];
                board[i][j].found = false; // Set the 'found' flag to false
            } else {
                //set an empty card with an empty string if cards are 0
                strcpy(board[i][j].word, "");
                // Set the 'found' flag to false
                board[i][j].found = false; 
            }
        }
    }

    return board;

// printBoard function
void printBoard(Card **board, int rows, int cols) 
{
    // Loop through each row of the board
    for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) 
		{
            // Check if the card has a word 
            if (strcmp(board[i][j].word, "") != 0) 
			{
                // Check if the card is hidden or found
                if (!board[i][j].found) 
				{
                    printf("HIDDEN\t");
                } 
				else 
				{
                    // Print the word for a found card accurately
						// Function: printf
                    printf("%-20s\t", board[i][j].word);
                }
            }
        }
         // Move to the next line after printing a row
        printf("\n");
    }
    // Flush the output buffer
    fflush(stdout); 
}


// Check for victory
bool checkVictory(Card **board, int rows, int cols) 
{
    // Loop through each row of the board
    for (int i = 0; i < rows; i++) 
	{
        for (int j = 0; j < cols; j++) 
		{
            // Check if the card has a word and is not found
            if (strcmp(board[i][j].word, "") != 0 && !board[i][j].found) 
			{
                return false; 
            }
        }
    }
    return true;
}

