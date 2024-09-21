#include <stdio.h>
#include <string.h>
#include <ctype.h>
void vigenereEncrypt(char *plaintext, char *key, char *ciphertext) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    int keyIndex = 0;

    for (int i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            int keyShift = tolower(key[keyIndex]) - 'a';
            if (islower(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] - 'a' + keyShift) % 26) + 'a';
            } else {
                ciphertext[i] = ((plaintext[i] - 'A' + keyShift) % 26) + 'A';
            }
            keyIndex = (keyIndex + 1) % keyLen;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    // Null-terminate the ciphertext
    ciphertext[textLen] = '\0';
}

int main() {
    char plaintext[256];
    char key[256];
    char ciphertext[256];
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';
    vigenereEncrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    return 0;
}

