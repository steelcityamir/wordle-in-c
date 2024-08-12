<img src="https://img.shields.io/badge/LANGUAGE-C-00599C.svg?style=for-the-badge" alt="C"> <img src="https://img.shields.io/badge/License-MIT-yellow.svg?style=for-the-badge" alt="MIT License">

# Wordle in C
A command-line implementation of a Wordle-like game in C. The game prompts the user to guess a secret 5-letter word, providing color-coded feedback on each guess.

## Features

- **Guess the Word**: The user has up to 6 attempts to guess the secret 5-letter word.
- **Color-Coded Feedback**:
  - **Green Background**: Correct letter in the correct position.
  - **Yellow Background**: Correct letter but in the wrong position.
  - **Grey Background**: Incorrect letter.
- **Uppercase Display**: The secret word is displayed in uppercase if the user runs out of attempts.
- **File-Based Word List**: Reads a list of valid words from a file.

## Prerequisites

- A C compiler (e.g., GCC)
- ANSI escape codes compatible terminal for color output

## Installation

1. **Clone the Repository**:
    ```sh
    git clone https://github.com/steelcity/wordle-in-c.git
    cd wordle-in-c
    ```

2. **Compile the Program**:
    ```sh
    gcc -o wordle wordle.c
    ```

## Usage

1. **Run the Program**:
    ```sh
    ./wordle
    ```

2. **Follow the Prompts**:
   - Enter your guesses when prompted.
   - The program will provide color-coded feedback for each guess.

## Example

<img width="473" alt="image" src="https://github.com/user-attachments/assets/e5508f1a-d7b4-45b8-b151-28c2e5731ee4">


## Contributing
Feel free to open issues or submit pull requests to improve the game.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

