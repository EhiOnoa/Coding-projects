#ifndef BATTLESHIP_LIB_H
#define BATTLESHIP_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 10

//initialize the random number generator
void initializeRandom();

//print the game matrix
void printMatrix(const char matrix[SIZE][SIZE]);

//fill the board with a given character
void buildBoard(char board[SIZE][SIZE], char c);

//check if a given position contains water
bool isWater(const char board[SIZE][SIZE], int row, int col);

//place a ship horizontally on the board
void placeShipHorizontal(char board[SIZE][SIZE], int shipLength);

//place a ship vertically on the board
void placeShipVertical(char board[SIZE][SIZE], int shipLength);

//randomly fill the board with ships
void fillBoard(char board[SIZE][SIZE]);

//update the game board based on a shot
void shoot(const char solution[SIZE][SIZE], char game[SIZE][SIZE], int row, int col);

//check if the player has won
bool checkVictory(const char solution[SIZE][SIZE], const char game[SIZE][SIZE]);

#endif 
