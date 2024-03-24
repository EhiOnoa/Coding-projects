#include "DNA_lib.h"

void generateAndCalculateSimilarity() {
    // Declare necessary variables
    char seq1[DNA_SEQ_LEN + 1];
    char seq2[DNA_SEQ_LEN + 1];
    int max_shifts, sequence, num_shifts;

    // Generate two DNA sequences
    getDNASequence(seq1, DNA_SEQ_LEN);
    getDNASequence(seq2, DNA_SEQ_LEN);

    printf("===============================\n");
    printf("Sequence 1: %s\n", seq1);
    printf("Sequence 2: %s\n", seq2);

    // Ask the user for the number of shifts or use the default
    printf("\nHow many shifts would you like to try (hit enter for default)? ");
    num_shifts = getShifts();

    if (num_shifts == DEFAULT_SHIFTS) {
        printf("Calculating the DNA Similarity Score using a maximum of 10 shifts...\n");
    } else {
        printf("Calculating the DNA Similarity Score using a maximum of %d shifts...\n", num_shifts);
    }

    // Calculate the similarity score
    int similarityScore = getSimilarityScore(seq1, seq2, &max_shifts, &sequence, num_shifts);

    // Print the result
    printf("\nSimilarity Score: %d\n", similarityScore);
    if (sequence == NO_SHIFT) {
        printf("No shift results in the maximum alignment score.\n");
    } else {
        printf("The maximum alignment score is obtained by shifting Sequence %d by %d shifts.\n", sequence, max_shifts);
    }

    // Ask if the user wants to generate a new sequence and start over
    printf("Generate new sequences [y|n]? ");
}

int main() {
    char choice;

    printf("DNA Similarity Check\n");

    do {
        generateAndCalculateSimilarity();
        choice = getChoiceYN();
    } while (choice == 'y');

    printf("Program ended.\n");

    return 0;
}
