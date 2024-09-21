#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
int main() {
    char key[100], plaintext[100], ciphertext[100];
    char matrix[SIZE][SIZE];
    int used[26] = {0};
    int i, j, k = 0, row1, col1, row2, col2;
    printf("Enter the key (without duplicates): ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  
    for (i = 0; key[i] != '\0'; i++) {
        if (key[i] == 'J') key[i] = 'I';  
        key[i] = toupper(key[i]);  
    }
    for (i = 0; i < strlen(key); i++) {
        if (!used[key[i] - 'A'] && isalpha(key[i])) {
            matrix[k / SIZE][k % SIZE] = key[i];
            used[key[i] - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !used[i]) {
            matrix[k / SIZE][k % SIZE] = 'A' + i;
            used[i] = 1;
            k++;
        }
    }
    printf("Enter the plaintext (uppercase letters only, no spaces): ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    int len = strlen(plaintext);
    for (i = 0; i < len; i += 2) {
        if (plaintext[i] == plaintext[i+1]) {
            for (j = len; j > i+1; j--) {
                plaintext[j] = plaintext[j-1];
            }
            plaintext[i+1] = 'X';  
            len++;
        }
        if (len % 2 != 0) {
            plaintext[len] = 'X';
            len++;
            plaintext[len] = '\0';
        }
        for (row1 = 0; row1 < SIZE; row1++) {
            for (col1 = 0; col1 < SIZE; col1++) {
                if (matrix[row1][col1] == plaintext[i]) break;
            }
            if (col1 < SIZE) break;
        }

        for (row2 = 0; row2 < SIZE; row2++) {
            for (col2 = 0; col2 < SIZE; col2++) {
                if (matrix[row2][col2] == plaintext[i+1]) break;
            }
            if (col2 < SIZE) break;
        }
        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i+1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i+1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i+1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';  
    printf("Encrypted message: %s\n", ciphertext);

    return 0;
}
