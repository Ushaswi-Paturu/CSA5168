#include <stdio.h>
#include <string.h>
int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2, 
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
int FP[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};
void permute(unsigned char *in, unsigned char *out, int *table, int n) {
    for (int i = 0; i < n; i++) {
        int pos = table[i] - 1;
        int bit = (in[pos / 8] >> (7 - (pos % 8))) & 0x01;
        out[i / 8] |= (bit << (7 - (i % 8)));
    }
}
void DES_encrypt_decrypt(unsigned char *block, unsigned char *key, int mode) {
    unsigned char permutedBlock[8] = {0};
    permute(block, permutedBlock, IP, 64);
    unsigned char finalBlock[8] = {0};
    permute(permutedBlock, finalBlock, FP, 64);
    memcpy(block, finalBlock, 8);
}

int main() {
    unsigned char inputBlock[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    unsigned char key[7] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF};

    printf("Plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", inputBlock[i]);
    }
    printf("\n");
    DES_encrypt_decrypt(inputBlock, key, 1); 

    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", inputBlock[i]);
    }
    printf("\n");
    DES_encrypt_decrypt(inputBlock, key, 0); 

    printf("Decrypted Plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%02X ", inputBlock[i]);
    }
    printf("\n");

    return 0;
}

