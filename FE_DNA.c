#include "DNA_lib.h"

int main() {
    initializeRandom();
    char choice;

    do {
        // Declare necessary variables
        char* seq1, * seq2;
        int numShifts, maxShifts, sequence, chainIndex, similarityScore;

        // Print title
        printf("DNA Similarity Check\n");

        // Calculate DNA Similarity Scores
        seq1 = getDNASequence(DNA_SEQ_LEN);
        seq2 = getDNASequence(DNA_SEQ_LEN);

        // Print sequences
        printf("Sequence 1: %s\n", seq1);
        printf("Sequence 2: %s\n", seq2);

        // Ask user for shifts
        numShifts = getShifts();

        // Calculate similarity score
        similarityScore = getSimilarityScore(seq1, seq2, numShifts, &maxShifts, &sequence, &chainIndex);

        // Print result
        printf("Similarity Score: %d\n", similarityScore);

        if (maxShifts == NO_SHIFT) {
            printf("No shift results in the maximum alignment score.\n");
        } else {
            printf("The maximum alignment score is obtained by shifting Sequence %c by %d shifts.\n",
                   (sequence == SEQ_1) ? '1' : '2', maxShifts);
        }

        printf("Maximum contiguous chain: ");
        for (int i = chainIndex; i < chainIndex + similarityScore; ++i) {
            printf("%c", seq1[i]);
        }
        printf("\n");

        // Ask if user wants to generate a new sequence
        printf("Do you want to generate a new sequence? (y/n): ");
        fflush(stdin);
        scanf(" %c", &choice);
        choice = tolower(choice);

        // Free allocated memory
        free(seq1);
        free(seq2);

    } while (choice == 'y');

    printf("Program ended. Goodbye!\n");

    return 0;
}