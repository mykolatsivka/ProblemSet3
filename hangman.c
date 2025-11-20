#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "hangman.h"
#include <time.h>
#include <string.h>
#include <ctype.h>

int get_word(char secret[]){
    FILE *fp = fopen(WORDLIST_FILENAME, "rb");
    if( fp == NULL ){
        fprintf(stderr, "No such file or directory: %s\n", WORDLIST_FILENAME);
        return 1;
    }

    struct stat st;
    stat(WORDLIST_FILENAME, &st);
    long int size = st.st_size;

    do{
        long int random = (rand() % size) + 1;
        fseek(fp, random, SEEK_SET);
        int result = fscanf(fp, "%*s %20s", secret);
        if( result != EOF )
            break;
    }while(1);

    fclose(fp);

    return 0;
}

int is_word_guessed(const char secret[], const char letters_guessed[]) {
    for (int i = 0; secret[i] != '\0'; i++) {
        int found = 0;
        for (int j = 0; letters_guessed[j] != '\0'; j++) {
            if (secret[i] == letters_guessed[j]) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

void get_guessed_word(const char secret[], const char letters_guessed[], char guessed_word[]) {
    int i = 0;
    while (secret[i] != '\0') {
        int found = 0;
        for (int j = 0; letters_guessed[j] != '\0'; j++) {
            if (secret[i] == letters_guessed[j]) {
                found = 1;
                break;
            }
        }
        guessed_word[i] = found ? secret[i] : '_';
        i++;
    }
    guessed_word[i] = '\0';
}

void get_available_letters(const char letters_guessed[], char available_letters[]) {
    const char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    int idx = 0;

    for (int i = 0; alphabet[i] != '\0'; i++) {
        int used = 0;
        for (int j = 0; letters_guessed[j] != '\0'; j++) {
            if (alphabet[i] == letters_guessed[j]) {
                used = 1;
                break;
            }
        }
        if (!used) {
            available_letters[idx++] = alphabet[i];
        }
    }
    available_letters[idx] = '\0';
}

void hangman(const char secret[]) {
    char letters_guessed[100] = "";
    int attempts_left = 8;

    printf("Welcome to the game, Hangman!\n");
    printf("I am thinking of a word that is %d letters long.\n", (int)strlen(secret));

    while (attempts_left > 0) {
        char guessed_word[100];
        char available[50];
        get_guessed_word(secret, letters_guessed, guessed_word);
        get_available_letters(letters_guessed, available);

        printf("-------------\n");
        printf("You have %d guesses left.\n", attempts_left);
        printf("Available letters: %s\n", available);
        printf("Please guess a letter: ");

        char input[100];
        scanf("%s", input);

        if (strlen(input) > 1) {
            if (strcmp(input, secret) == 0) {
                printf("Congratulations, you won!\n");
            } else {
                printf("Sorry, bad guess. The word was %s.\n", secret);
            }
            return;
        }

        char letter = tolower(input[0]);

        if (!isalpha(letter)) {
            printf("Oops! '%c' is not a valid letter: ", letter);
            for (int i = 0; guessed_word[i] != '\0'; i++) {
                printf("%c ", guessed_word[i]);
            }
            printf("\n");
            continue;
        }

        if (strchr(letters_guessed, letter)) {
            printf("Oops! You've already guessed that letter: ");
            for (int i = 0; guessed_word[i] != '\0'; i++) {
                printf("%c ", guessed_word[i]);
            }
            printf("\n");
            continue;
        }

        int len = strlen(letters_guessed);
        letters_guessed[len] = letter;
        letters_guessed[len+1] = '\0';

        if (strchr(secret, letter)) {
            printf("Good guess: ");
            get_guessed_word(secret, letters_guessed, guessed_word);
            for (int i = 0; guessed_word[i] != '\0'; i++) {
                printf("%c ", guessed_word[i]);
            }
            printf("\n");
            
            if (is_word_guessed(secret, letters_guessed)) {
                printf("-------------\n");
                printf("Congratulations, you won!\n");
                return;
            }
        } else {
            printf("Oops! That letter is not in my word: ");
            for (int i = 0; guessed_word[i] != '\0'; i++) {
                printf("%c ", guessed_word[i]);
            }
            printf("\n");
            attempts_left--;
        }
    }

    printf("-------------\n");
    printf("Sorry, you ran out of guesses. The word was %s.\n", secret);
}