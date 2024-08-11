// wordle.h

#ifndef WORDLE_H
#define WORDLE_H

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6
#define MAX_WORDS 1500

#define CORRECT_LETTER_CORRECT_POSITION 2
#define CORRECT_LETTER_WRONG_POSITION 1

// Function declarations
void check_guess(const char *secret, const char *guess, int *result);
char* choose_random_word(const char* filename);
void display_result(const char *guess, const int *result);

#endif
