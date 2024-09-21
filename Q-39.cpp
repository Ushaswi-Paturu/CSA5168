#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ALPHABET_SIZE 26
#define TOP_N 10
void calculateFrequency(char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            frequency[ch - 'A']++;
        } else if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
        }
    }
}
void decryptWithShift(char *ciphertext, int shift, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = (ch - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = (ch - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
void frequencyAttack(char *ciphertext) {
    int frequency[ALPHABET_SIZE] = {0};
    calculateFrequency(ciphertext, frequency);
    int maxFreqIndex = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > frequency[maxFreqIndex]) {
            maxFreqIndex = i;
        }
    }
    int shift = (maxFreqIndex - ('E' - 'A') + ALPHABET_SIZE) % ALPHABET_SIZE;
    char possiblePlaintexts[TOP_N][100];
    for (int i = 0; i < TOP_N; i++) {
        decryptWithShift(ciphertext, (shift + i) % ALPHABET_SIZE, possiblePlaintexts[i]);
    }
    printf("Top %d Possible Plaintexts:\n", TOP_N);
    for (int i = 0; i < TOP_N; i++) {
        printf("%d: %s\n", i + 1, possiblePlaintexts[i]);
    }
}

int main() {
    char ciphertext[100];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 

    frequencyAttack(ciphertext);

    return 0;
}

