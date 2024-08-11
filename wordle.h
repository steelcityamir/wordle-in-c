// wordle.h

#ifndef WORDLE_H
#define WORDLE_H

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define MAX_WORDS 1500

#define CORRECT_LETTER_CORRECT_POSITION 2
#define CORRECT_LETTER_WRONG_POSITION 1

// ANSI escape codes for colors
#define RESET_COLOR "\033[0m"
#define GREEN_BACKGROUND "\033[42m"
#define YELLOW_BACKGROUND "\033[43m"
#define GREY_BACKGROUND "\033[100m"
#define WHITE_TEXT "\033[97m"

// Function declarations
void check_guess(const char *secret, const char *guess, int *result);
char* choose_random_word(const char* filename);
void display_result(const char *guess, const int *result);

#endif
