#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
#define TOP_N 10
void calculateFrequency(const char *ciphertext, int *frequency) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = toupper(ciphertext[i]);
        if (ch >= 'A' && ch <= 'Z') {
            frequency[ch - 'A']++;
        }
    }
}
void generateFrequencyTable(const int *frequency, char *substitution) {
    char mostFrequent[ALPHABET_SIZE];
    int freqIndices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freqIndices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = 0; j < ALPHABET_SIZE - i - 1; j++) {
            if (frequency[freqIndices[j]] < frequency[freqIndices[j + 1]]) {
                int temp = freqIndices[j];
                freqIndices[j] = freqIndices[j + 1];
                freqIndices[j + 1] = temp;
            }
        }
    }
    char englishFreq[TOP_N] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D'};
    for (int i = 0; i < TOP_N; i++) {
        mostFrequent[i] = 'A' + freqIndices[i];
        substitution[mostFrequent[i] - 'A'] = englishFreq[i];
    }
}
void decryptCiphertext(const char *ciphertext, const char *substitution, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = toupper(ciphertext[i]);
        if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = substitution[ch - 'A'];
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

int main() {
    char ciphertext[100];
    char plaintext[100];
    char substitution[ALPHABET_SIZE] = {0};
    int frequency[ALPHABET_SIZE] = {0};

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; 
    calculateFrequency(ciphertext, frequency);
    generateFrequencyTable(frequency, substitution);
    decryptCiphertext(ciphertext, substitution, plaintext);
    printf("Possible Plaintext: %s\n", plaintext);

    return 0;
}

