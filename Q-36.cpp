#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 26
void affineEncrypt(char plaintext[], int a, int b, char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (ch >= 'A' && ch <= 'Z') {
            ciphertext[i] = ((a * (ch - 'A') + b) % ALPHABET_SIZE) + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            ciphertext[i] = ((a * (ch - 'a') + b) % ALPHABET_SIZE) + 'a';
        } else {
            ciphertext[i] = ch; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}
void affineDecrypt(char ciphertext[], int a, int b, char plaintext[]) {
    int a_inverse = -1;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if ((a * i) % ALPHABET_SIZE == 1) {
            a_inverse = i; 
            break;
        }
    }
    if (a_inverse == -1) {
        printf("Error: a does not have an inverse under modulo 26.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') {
            plaintext[i] = (a_inverse * ((ch - 'A' - b + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A');
        } else if (ch >= 'a' && ch <= 'z') {
            plaintext[i] = (a_inverse * ((ch - 'a' - b + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a');
        } else {
            plaintext[i] = ch; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}

int main() {
    char plaintext[100];
    char ciphertext[100];
    char decryptedText[100];
    int a, b;

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 

    printf("Enter values for a and b (0 < a < 26, 0 <= b < 26): ");
    scanf("%d %d", &a, &b);
    if (a <= 0 || a >= ALPHABET_SIZE || b < 0 || b >= ALPHABET_SIZE) {
        printf("Invalid values for a and b. Please ensure 0 < a < 26 and 0 <= b < 26.\n");
        return 1;
    }
    affineEncrypt(plaintext, a, b, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    affineDecrypt(ciphertext, a, b, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

