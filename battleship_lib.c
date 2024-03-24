#include "battleship_lib.h"

//initialize the random number generator
void initializeRandom() 
{
    srand(time(NULL));
}

//print the game matrix
void printMatrix(const char matrix[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++) 
    {
        for (int j = 0; j < SIZE; j++) 
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

//fillboard with the given characters
void buildBoard(char board[SIZE][SIZE], char c) 
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            board[i][j] = c;
}

//check if it contains water
bool isWater(const char board[SIZE][SIZE], int row, int col) 
{
    return (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == '0');
}

//place ship at certain positions with length
void placeShip(char board[SIZE][SIZE], int row, int col, int shipLength, int deltaRow, int deltaCol) 
{
    for (int i = 0; i < shipLength; i++)
        board[row + i * deltaRow][col + i * deltaCol] = shipLength + '0';
}
//fill thr board randomly with ships
void fillBoard(char board[SIZE][SIZE]) 
{
    int shipLengths[] = {5, 4, 4, 3, 3, 3, 2, 2, 2, 2};

    for (int i = 0; i < sizeof(shipLengths) / sizeof(shipLengths[0]); i++) 
    {
        int orientation = rand() % 2; // 0 for horizontal, 1 for vertical
        int row, col;
        //search for accurate random positions for the ship
        do 
        {
            row = rand() % SIZE;
            col = rand() % SIZE;
        } while (!isWater(board, row, col) || 
                 (orientation == 0 && col > SIZE - shipLengths[i]) || (orientation == 1 && row > SIZE - shipLengths[i]));
                 //place the ship on the board
                  placeShip(board, row, col, shipLengths[i], 1 - orientation, orientation);
    }
}
//update the game board according to the shot
void shoot(const char solution[SIZE][SIZE], char game[SIZE][SIZE], int row, int col) 
{
    game[row][col] = (solution[row][col] == '0') ? 'W' : 'S';
}
//check if the player is victorious
bool checkVictory(const char solution[SIZE][SIZE], const char game[SIZE][SIZE]) 
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (solution[i][j] > '0' && game[i][j] != 'S')
                return false;
    return true;
}
