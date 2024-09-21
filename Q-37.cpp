#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 10
const double frequency[ALPHABET_SIZE] = {
    0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 
    0.102, 0.022, 0.061, 0.070, 0.040, 0.024, 0.067, 0.078, 0.063, 0.009, 
    0.001, 0.020, 0.001, 0.003, 0.003, 0.012                                
};
void calculateFrequency(const char *ciphertext, double *freq) {
    int count[ALPHABET_SIZE] = {0};
    int total = 0;

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            count[ch - 'A']++;
            total++;
        } else if (ch >= 'a' && ch <= 'z') {
            count[ch - 'a']++;
            total++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)count[i] / total;
    }
}
void generateSubstitution(const double *cipherFreq, char *substitution) {
    int sortedIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sortedIndices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (cipherFreq[sortedIndices[i]] < cipherFreq[sortedIndices[j]]) {
                int temp = sortedIndices[i];
                sortedIndices[i] = sortedIndices[j];
                sortedIndices[j] = temp;
            }
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        substitution[sortedIndices[i]] = 'A' + i;
    }
}
void decrypt(const char *ciphertext, const char *substitution, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = substitution[ch - 'A'];
        } else if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = substitution[ch - 'a'] + 32; 
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
int main() {
    char ciphertext[256];
    double cipherFreq[ALPHABET_SIZE] = {0};
    char substitution[ALPHABET_SIZE] = {0};
    char plaintext[256];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    calculateFrequency(ciphertext, cipherFreq);
    generateSubstitution(cipherFreq, substitution);
    decrypt(ciphertext, substitution, plaintext);
    printf("Possible plaintext: %s\n", plaintext);

    return 0;
}

