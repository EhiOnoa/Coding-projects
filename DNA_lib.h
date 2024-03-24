#ifndef DNA_LIB_H
#define DNA_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define DNA_SEQ_LEN 50
#define DEFAULT_SHIFTS 10
#define SEQ_1 1
#define SEQ_2 2
#define NO_SHIFT 0
extern const char* NUCLEOTIDES;

void initializeRandom();
char getChoiceYN();
int getNucleotide(int length);
char* getDNASequence(int length);
int getShifts();
int getScoreShifted(char* shiftSeq, int shiftIndex, char* baselineSeq, int length);
int getSimilarityScore(char* seq1, char* seq2, int numShifts, int* maxShifts, int* sequence, int* chainIndex);

#endif