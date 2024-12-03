#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *plaintext, char *key, char *ciphertext) {
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < textLen; i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            c = (c - offset + (toupper(key[j % keyLen]) - 'A')) % 26 + offset;
            j++;
        }
        ciphertext[i] = c;
    }
    ciphertext[textLen] = '\0';
}

int main() {
    char plaintext[256];
    char key[256];
    char ciphertext[256];
    FILE *ptFile, *ctFile;

    ptFile = fopen("PT.txt", "r");
    if (ptFile == NULL) {
        perror("Error opening PT.txt");
        return 1;
    }

    fgets(plaintext, sizeof(plaintext), ptFile);
    fclose(ptFile);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove newline character

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    encrypt(plaintext, key, ciphertext);

    ctFile = fopen("CT.txt", "w");
    if (ctFile == NULL) {
        perror("Error opening CT.txt");
        return 1;
    }

    fprintf(ctFile, "%s", ciphertext);
    fclose(ctFile);

    printf("Encryption complete. Encrypted text saved to CT.txt\n");

    return 0;
}