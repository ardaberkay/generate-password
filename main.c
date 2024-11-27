#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define LOWERCASE "abcdefghijklmnopqrstuvwxyz"
#define UPPERCASE "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define NUMBERS "0123456789"
#define SPECIALCHARS "!é€@£#$%½^.,~&*-_+=<>?/(){}[]|"

int main(void) {
    int length;
    bool inNumber = false, specialChar = false, upCase = false, lowCase = false, validLenght = false;
    char controller;

    printf("\n");
    printf("------------------Welcome to the Password Generator------------------");
    printf("\n\n");

    while (!validLenght) {
        printf("How many characters would you like the password to be?");

        if (scanf("%d", &length) == 1) {
            if (length > 0) {
                validLenght = true;
            } else {
                printf("Error: Please enter a positive integer.\n");
            }
        } else {
            printf("Error: Please enter only an integer.\n");
            while (getchar() != '\n');
        }
    }
    printf("\n");
    while (!inNumber) {
        printf("Would you like your password to contain numbers? (Y/N):");
        scanf(" %c", &controller);
        printf("\n");

        if (controller == 'Y' || controller == 'y') {
            inNumber = true;
            break;
        }
        if (controller == 'N' || controller == 'n') {
            inNumber = false;
            break;
        }
        printf("ERROR: Please make a valid choice.\n");
    }

    while (!specialChar) {
        printf("Would you like your password to contain special characters? (Y/N):");
        scanf(" %c", &controller);
        printf("\n");

        if (controller == 'Y' || controller == 'y') {
            specialChar = true;
            break;
        }
        if (controller == 'N' || controller == 'n') {
            specialChar = false;
            break;
        }
        printf("ERROR: Please make a valid choice.\n");
    }

    while (!upCase) {
        printf("Would you like your password to contain uppercase letters? (Y/N):");
        scanf(" %c", &controller);
        printf("\n");

        if (controller == 'Y' || controller == 'y') {
            upCase = true;
            break;
        }
        if (controller == 'N' || controller == 'n') {
            upCase = false;
            break;
        }
        printf("ERROR: Please make a valid choice.\n");
    }

    while (!lowCase) {
        printf("Would you like your password to contain lowercase letters? (Y/N):");
        scanf(" %c", &controller);
        printf("\n");

        if (controller == 'Y' || controller == 'y') {
            lowCase = true;
            break;
        }
        if (controller == 'N' || controller == 'n') {
            lowCase = false;
            break;
        }
        printf("ERROR: Please make a valid choice.\n");
    }

    char excludeChars[50] = "";
    printf("Enter the characters you do not want in your password (end with E):\n ");
    while (scanf(" %c", &controller) && controller != 'E' && controller != 'e') {
        strncat(excludeChars, &controller, 1);
    }

    srand(time(NULL));

    char charset[100] = "";

    if (inNumber) {
        strcat(charset, NUMBERS);
    }

    if (specialChar) {
        strcat(charset, SPECIALCHARS);
    }

    if (upCase) {
        strcat(charset, UPPERCASE);
    }

    if (lowCase) {
        strcat(charset, LOWERCASE);
    }

    char tempCharset[100] = "";
    for (int i = 0; charset[i] != '\0'; i++) {
        if (strchr(excludeChars, charset[i]) == NULL) {
            strncat(tempCharset, &charset[i], 1);
        }
    }
    strcpy(charset, tempCharset);

    char regenerate = 'Y';
    char password[length + 1];
    while (regenerate == 'Y' || regenerate == 'y') {
        for (int i = 0; i < length; i++) {
            password[i] = charset[rand() % strlen(charset)];
        }
        password[length] = '\0';

        printf("\n");
        printf("Generated password: %s", password);

        printf("\n");
        printf("Would you like to generate another password? (Y/N): ");
        scanf(" %c", &regenerate);
    }

    FILE *file = fopen("projectPasswords.txt", "a");
    if (!file) {
        printf("The file could not be opened.\n");
        return 1;
    }

    fprintf(file, "Generated password: %s\n", password);
    fclose(file);

    printf("\n");
    printf("All passwords have been saved to the projectPasswords.txt file.\n");
    printf("The password you generated: %s \n", password);

    return 0;
}
