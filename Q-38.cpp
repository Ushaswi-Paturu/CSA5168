#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2 // 2x2 Hill cipher

// Function to calculate the determinant of a 2x2 matrix
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
}

// Function to calculate the modular inverse of a number under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse found
}

// Function to find the inverse of a 2x2 matrix modulo 26
int inverseMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int invMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(matrix);
    int detInv = modInverse(det, 26);
    
    if (detInv == -1) {
        return -1; // Inverse does not exist
    }
    
    invMatrix[0][0] = (matrix[1][1] * detInv) % 26;
    invMatrix[0][1] = (-matrix[0][1] * detInv + 26) % 26;
    invMatrix[1][0] = (-matrix[1][0] * detInv + 26) % 26;
    invMatrix[1][1] = (matrix[0][0] * detInv) % 26;

    return 0;
}

// Function to encrypt plaintext using Hill cipher
void encryptHillCipher(char *plaintext, int key[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0, 0};
        for (int j = 0; j < MATRIX_SIZE; j++) {
            if (i + j < len) {
                block[j] = plaintext[i + j] - 'A'; // Convert char to index (0-25)
            }
        }
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += key[j][k] * block[k];
            }
            ciphertext[i / MATRIX_SIZE * MATRIX_SIZE + j] = (sum % 26) + 'A'; // Convert back to char
        }
    }
    ciphertext[len] = '\0'; // Null-terminate the ciphertext
}

// Function to decrypt ciphertext using Hill cipher
void decryptHillCipher(char *ciphertext, int key[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int invKey[MATRIX_SIZE][MATRIX_SIZE];
    if (inverseMatrix(key, invKey) == -1) {
        printf("Key does not have an inverse.\n");
        return;
    }

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += MATRIX_SIZE) {
        int block[MATRIX_SIZE] = {0, 0};
        for (int j = 0; j < MATRIX_SIZE; j++) {
            block[j] = ciphertext[i + j] - 'A'; // Convert char to index (0-25)
        }
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += invKey[j][k] * block[k];
            }
            plaintext[i / MATRIX_SIZE * MATRIX_SIZE + j] = (sum % 26 + 26) % 26 + 'A'; // Convert back to char
        }
    }
    plaintext[len] = '\0'; // Null-terminate the plaintext
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char decryptedText[100];

    // Example key for the Hill cipher (must be invertible)
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24},
        {1, 13}
    };

    printf("Enter the plaintext (only uppercase A-Z): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    // Encrypt the plaintext
    encryptHillCipher(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decryptHillCipher(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

