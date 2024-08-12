/*
 * File: wordle.c
 * Author: Amir Boroumand
 * Date: 8/11/2024
 * Description: A simple implementation of a Wordle-like game in C.
 *
 * Purpose:
 *   This program is a command-line implementation of a Wordle game.
 *
 *   The user has to guess a secret 5-letter word in up to 6 attempts.
 *   The program provides feedback on each guess using color-coded blocks to
 *   indicate correct and incorrect letters.
 *
 * Features:
 *   - Reads a list of 5-letter words from a file.
 *   - Chooses a random word from the list as the secret word.
 *   - Prompts the user to guess the secret word.
 *   - Provides color-coded feedback on the guess:
 *     - Green background for correct letter and position.
 *     - Yellow background for correct letter but wrong position.
 *     - Grey background for incorrect letters.
 *   - Displays the secret word if the user runs out of attempts.
 *
 * Functions:
 *   - void check_guess(const char *secret, const char *guess, int *result):
 *       Compares the user's guess with the secret word and fills the result array with appropriate score.
 *
 *   - char* choose_random_word(const char* filename):
 *       Reads words from a file, selects a random valid word, and returns it.
 *
 *   - void display_result(const char *guess, const int *result):
 *       Displays the user's guess with color-coded feedback based on the result array.
 *
 * Usage:
 *   - Ensure that `word_list.txt` contains a list of valid 5-letter words, one per line.
 *   - Compile the program using a C compiler (e.g., gcc).
 *   - Run the executable and follow the prompts to guess the secret word.
 *
 * Note:
 *   - The program assumes that the `word_list.txt` file is located in the same directory as the executable.
 *   - Memory allocated with `strdup` is freed before the program exits to avoid memory leaks.
 *   - Colors are displayed using ANSI escape codes and may not be supported by all terminals.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "wordle.h"

void check_guess(const char *secret, const char *guess, int *scores) {
    bool letter_used[WORD_LENGTH] = {false}; // Track used letters in the secret word

    // Initialize the result array with zeroes
    // This is critical to calculating the correct score for each guess
    memset(scores, 0, WORD_LENGTH * sizeof(int));

    // First pass: Check for correct positions
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (tolower(guess[i]) == tolower(secret[i])) {
            scores[i] = CORRECT_LETTER_CORRECT_POSITION;
            letter_used[i] = true;
        }
    }

    // Second pass: Check for correct letters in wrong positions
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (scores[i] != CORRECT_LETTER_CORRECT_POSITION) {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!letter_used[j] && tolower(guess[i]) == tolower(secret[j])) {
                    scores[i] = CORRECT_LETTER_WRONG_POSITION;
                    letter_used[j] = true;
                    break;
                }
            }
        }
    }
}

char *choose_random_word(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    char word[MAX_WORDS][WORD_LENGTH + 1];
    int word_count = 0;

    // Read words from the file
    while (fgets(word[word_count], sizeof(word[word_count]), file)) {
        // Remove newline character if present
        word[word_count][strcspn(word[word_count], "\n")] = '\0';

        // Check if the word length matches the required word length
        if (strlen(word[word_count]) == WORD_LENGTH) {
            word_count++;
            if (word_count >= MAX_WORDS) break; // Prevent overflow
        }
    }

    fclose(file);

    if (word_count == 0) {
        fprintf(stderr, "No valid words found in the file.\n");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));
    int random_index = rand() % word_count;
    char *chosen_word = strdup(word[random_index]); // strdup allocates memory for the chosen word

    return chosen_word;
}

void display_result(const char *guess, const int *result) {
    printf("Result: ");
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result[i] == CORRECT_LETTER_CORRECT_POSITION) {
            // Correct letter and position (green background)
            printf("%s%c%s ", GREEN_BACKGROUND WHITE_TEXT, toupper(guess[i]), RESET_COLOR);
        } else if (result[i] == CORRECT_LETTER_WRONG_POSITION) {
            // Correct letter, wrong position (yellow background)
            printf("%s%c%s ", YELLOW_BACKGROUND WHITE_TEXT, toupper(guess[i]), RESET_COLOR);
        } else {
            // Incorrect letter (grey background)
            printf("%s%c%s ", GREY_BACKGROUND WHITE_TEXT, toupper(guess[i]), RESET_COLOR);
        }
    }
    printf("\n");
}

int main(void) {
    char *secret_word = choose_random_word("word_list.txt");
    char guess[WORD_LENGTH + 1];
    int scores[WORD_LENGTH];
    int attempts = 0;
    bool guessed_correctly = false;

    printf("Welcome to Wordle!\n");
    printf("Guess the %d-letter word. You have %d attempts.\n", WORD_LENGTH, MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS && !guessed_correctly) {
        printf("Attempt %d of %d: ", attempts + 1, MAX_ATTEMPTS);
        scanf("%s", guess);

        // Ensure the guess is the correct length
        if (strlen(guess) != WORD_LENGTH) {
            printf("Please enter a %d-letter word.\n", WORD_LENGTH);
            continue;
        }

        check_guess(secret_word, guess, scores);
        display_result(guess, scores);

        // Calculate the total points
        int total_points = 0;
        for (int i = 0; i < WORD_LENGTH; i++) {
            total_points += scores[i];
        }

        if (total_points == WORD_LENGTH * CORRECT_LETTER_CORRECT_POSITION) {
            guessed_correctly = true;
            printf("Congratulations! You've guessed the word!\n");
        } else {
            attempts++;
        }
    }

    if (!guessed_correctly) {
        printf("Sorry, you've run out of attempts. The word was '%s'.\n", secret_word);
    }

    free(secret_word);
    return EXIT_SUCCESS;
}
