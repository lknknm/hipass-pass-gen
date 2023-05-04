/**
 * Hipass CLI Password Generator
 * Developed as Final Project for 
 * Harvard's CS50x Introduction to Computer Science
 *
 * Author: @lknknm
 *  Date: 04 may 2023
 *  Version: 0.1.0
 *
 * Contributors:
 *  @FuelledByCoffee
 *  added CMake file and refactor structure.
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "generator.h"
#include "clipboard.h"

// output constants
#define C_CLEAR  "\033[2J\033[1;1H"
#define C_RESET  "\e[m"
#define C_GREEN  "\e[32m"
#define C_YELLOW "\e[33m"
#define C_CYAN   "\e[36m"
#define C_BLUE   "\e[34m"
#define C_RED    "\e[31m"
#define C_WHITE  "\e[37m"
#define C_BOLD   "\e[1m"
#define C_BWHITE "\e[47m"

int main(void)
{
    printf("Hipass Password Generator\n\n");

    int characters = 0;
    do {
        printf("Type in number of characters (between 14 and 256): ");
        scanf("%i", &characters);

        // Clear input buffer:
        while ((getchar()) != '\n' && (getchar()) != EOF);
    } while (characters < 14 || characters > 256);

    // Allocate memory as the number of characters * chars
    char *password = malloc(characters*sizeof(char));
    if (password == NULL)
    {
        printf("Could not allocate memory for password.\n");
        free(password);
        return 1;
    }

    printf(C_GREEN "Password: ");

    generate_random_complete(password, characters);
    copy_to_clipboard_prompt(password);

    free(password);
    return 0;
}
