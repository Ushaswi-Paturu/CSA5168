#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 8

void XOR(unsigned char *a, unsigned char *b, unsigned char *out, int len) {
    for (int i = 0; i < len; i++) {
        out[i] = a[i] ^ b[i];
    }
}
void encryptBlock(unsigned char *block, unsigned char *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i % BLOCK_SIZE];
    }
}
void decryptBlock(unsigned char *block, unsigned char *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i % BLOCK_SIZE];
    }
}
int padData(unsigned char *data, int dataLen) {
    int padLength = BLOCK_SIZE - (dataLen % BLOCK_SIZE);
    data[dataLen] = 0x80; 
    for (int i = 1; i < padLength; i++) {
        data[dataLen + i] = 0x00;
    }
    return dataLen + padLength;
}
void ECB_Encrypt(unsigned char *plaintext, int length, unsigned char *key, unsigned char *ciphertext) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        encryptBlock(plaintext + i, key);
        memcpy(ciphertext + i, plaintext + i, BLOCK_SIZE);
    }
}
void ECB_Decrypt(unsigned char *ciphertext, int length, unsigned char *key, unsigned char *plaintext) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        decryptBlock(ciphertext + i, key);
        memcpy(plaintext + i, ciphertext + i, BLOCK_SIZE);
    }
}
void CBC_Encrypt(unsigned char *plaintext, int length, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        XOR(plaintext + i, iv, block, BLOCK_SIZE);
        encryptBlock(block, key);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        iv = ciphertext + i; 
    }
}

// CBC Mode Decryption
void CBC_Decrypt(unsigned char *ciphertext, int length, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, ciphertext + i, BLOCK_SIZE);
        decryptBlock(block, key);
        XOR(block, iv, plaintext + i, BLOCK_SIZE);
        iv = ciphertext + i; // update IV to the current ciphertext block
    }
}

// CFB Mode Encryption
void CFB_Encrypt(unsigned char *plaintext, int length, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        encryptBlock(iv, key); // Encrypt the IV
        XOR(plaintext + i, iv, block, BLOCK_SIZE); // XOR plaintext with encrypted IV
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        iv = ciphertext + i; // Update IV to current ciphertext block
    }
}

// CFB Mode Decryption
void CFB_Decrypt(unsigned char *ciphertext, int length, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        encryptBlock(iv, key); // Encrypt the IV
        XOR(ciphertext + i, iv, block, BLOCK_SIZE); // XOR ciphertext with encrypted IV
        memcpy(plaintext + i, block, BLOCK_SIZE);
        iv = ciphertext + i; // Update IV to current ciphertext block
    }
}

// Main function
int main() {
    unsigned char key[BLOCK_SIZE] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8}; // Example key
    unsigned char iv[BLOCK_SIZE] = {0x00}; // Initialization vector for CBC and CFB

    // Example plaintext (will be padded if necessary)
    unsigned char plaintext[] = "Cryptography";
    int plaintextLen = strlen((char *)plaintext);
    
    // Add padding to the plaintext
    int paddedLen = (plaintextLen % BLOCK_SIZE == 0) ? plaintextLen + BLOCK_SIZE : padData(plaintext, plaintextLen);

    // Buffers for ciphertext and decrypted text
    unsigned char ciphertext[paddedLen];
    unsigned char decrypted[paddedLen];

    printf("Original Plaintext: %s\n", plaintext);

    // ECB Encryption/Decryption
    ECB_Encrypt(plaintext, paddedLen, key, ciphertext);
    ECB_Decrypt(ciphertext, paddedLen, key, decrypted);
    printf("\nECB Encrypted: ");
    for (int i = 0; i < paddedLen; i++) printf("%02x ", ciphertext[i]);
    printf("\nECB Decrypted: %s\n", decrypted);

    // CBC Encryption/Decryption
    CBC_Encrypt(plaintext, paddedLen, key, iv, ciphertext);
    CBC_Decrypt(ciphertext, paddedLen, key, iv, decrypted);
    printf("\nCBC Encrypted: ");
    for (int i = 0; i < paddedLen; i++) printf("%02x ", ciphertext[i]);
    printf("\nCBC Decrypted: %s\n", decrypted);

    // Reset IV for CFB mode
    memset(iv, 0x00, BLOCK_SIZE);

    // CFB Encryption/Decryption
    CFB_Encrypt(plaintext, paddedLen, key, iv, ciphertext);
    CFB_Decrypt(ciphertext, paddedLen, key, iv, decrypted);
    printf("\nCFB Encrypted: ");
    for (int i = 0; i < paddedLen; i++) printf("%02x ", ciphertext[i]);
    printf("\nCFB Decrypted: %s\n", decrypted);

    return 0;
}

