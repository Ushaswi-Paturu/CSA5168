#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ALPHABET_SIZE 26
void generateRandomKey(int key[], int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % ALPHABET_SIZE; 
    }
}
void vigenereEncrypt(char plaintext[], int key[], char ciphertext[]) {
    int length = strlen(plaintext);

    for (int i = 0; i < length; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
		            ciphertext[i] = ((plaintext[i] - 'A') + key[i]) % ALPHABET_SIZE + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a') + key[i]) % ALPHABET_SIZE + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[length] = '\0';
}
void vigenereDecrypt(char ciphertext[], int key[], char decryptedText[]) {
    int length = strlen(ciphertext);

    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            decryptedText[i] = ((ciphertext[i] - 'A') - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            decryptedText[i] = ((ciphertext[i] - 'a') - key[i] + ALPHABET_SIZE) % ALPHABET_SIZE + 'a';
        } else {
            decryptedText[i] = ciphertext[i];
        }
    }

    decryptedText[length] = '\0'; 
}

int main() {
    srand(time(NULL));
    char plaintext[100];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    int length = strlen(plaintext);
    int key[length];
    char ciphertext[length + 1]; 
    char decryptedText[length + 1]; 
    generateRandomKey(key, length);
    vigenereEncrypt(plaintext, key, ciphertext);
    vigenereDecrypt(ciphertext, key, decryptedText);
    printf("\nPlaintext: %s\n", plaintext);
    printf("Generated Key: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", key[i]);
    }
    printf("\nCiphertext: %s\n", ciphertext);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

