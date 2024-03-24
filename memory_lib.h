#ifndef MEMORY_LIB_H
#define MEMORY_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define MAX_LETTERS 20

// Structure representing a card
typedef struct {
    char word[MAX_LETTERS + 1];
    bool found;
} Card;

// Function prototypes
int countWords(const char *filename);
void loadCards(const char *filename, Card *cards, int size);
void shuffleCards(Card *cards, int size);
Card **createBoard(Card *cards, int size, int *rows, int *cols);
void getDimensions(int length, int *row, int *col);
void printBoard(Card **board, int rows, int cols);
bool checkVictory(Card **board, int rows, int cols);

#endif

