#include "DNA_lib.h"
const char* NUCLEOTIDES = "AGCT";

//initialize the random number generator
void initializeRandom() { srand((unsigned int)time(NULL)); }

//Declare a function to account for the yes or no answer from the choice
char getChoiceYN() {
    char choice;
    do {
        printf("Do you want to repeat? (y/n): ");
        fflush(stdin); scanf(" %c", &choice);
        choice = tolower(choice);
        if (choice != 'y' && choice != 'n') {
            printf("Invalid option. Please type 'y' to repeat or 'n' to exit: ");
        }
    } while (choice != 'y' && choice != 'n');
    return choice;
}

//get a random nucleotide with the specified length
int getNucleotide(int length) { return rand() % length; }

//get a random dna sequence of a certain length
char* getDNASequence(int length) {
    char* seq = (char*)calloc(length + 1, sizeof(char));
    if (!seq) { fprintf(stderr, "Memory allocation error.\n"); exit(EXIT_FAILURE); }
    for (int i = 0; i < length; ++i) seq[i] = NUCLEOTIDES[getNucleotide(strlen(NUCLEOTIDES))];
    seq[length] = '\0'; return seq;
}

//get the number of shifts from the user
int getShifts() {
    int shifts; char value[3];
    do {
        printf("Enter the number of shifts (or press Enter for default): ");
        fflush(stdin); fgets(value, sizeof(value), stdin);
        if (value[0] == '\n') return DEFAULT_SHIFTS;
        shifts = atoi(value);
        if (shifts < 0) printf("Invalid option. The number of shifts cannot be negative. Please try again: ");
        else if (shifts > DNA_SEQ_LEN / 2) printf("Invalid option. The number of shifts cannot be more than half of the DNA sequence's length: ");
    } while (shifts < 0 || shifts > DNA_SEQ_LEN / 2);
    return shifts;
}

int getScoreShifted(char* shiftSeq, int shiftIndex, char* baselineSeq, int length) {
    int maxScore = 0, currentScore = 0;
    for (int i = 0; i < length; ++i) {
        if (shiftSeq[shiftIndex + i] == baselineSeq[i]) {
            currentScore++;
            if (currentScore > maxScore) maxScore = currentScore;
        } else currentScore = 0;
    }
    return maxScore;
}

int getSimilarityScore(char* seq1, char* seq2, int numShifts, int* maxShifts, int* sequence, int* chainIndex) {
    int maxScore = 0;
    int scoreNoShift = getScoreShifted(seq1, 0, seq2, DNA_SEQ_LEN);

    if (scoreNoShift > maxScore) *maxShifts = NO_SHIFT, *sequence = SEQ_1, *chainIndex = 0;

    for (int shifts = 1; shifts <= numShifts; ++shifts) {
        int scoreShifted = getScoreShifted(seq1, shifts, seq2, DNA_SEQ_LEN);
        if (scoreShifted > maxScore) maxScore = scoreShifted, *maxShifts = shifts, *sequence = SEQ_1, *chainIndex = shifts;
    }

    for (int shifts = 1; shifts <= numShifts; ++shifts) {
        int scoreShifted = getScoreShifted(seq2, shifts, seq1, DNA_SEQ_LEN);
        if (scoreShifted > maxScore) maxScore = scoreShifted, *maxShifts = shifts, *sequence = SEQ_2, *chainIndex = shifts;
    }

    return maxScore;
}