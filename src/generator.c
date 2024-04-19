/**
 * Hipass CLI Password Generator
 * 
 * Author: @lknknm
 *  Date: April 2024
 *  Version: 0.2.0
 *
 * Contributors:
 *  @FuelledByCoffee
 *  added CMake file and refactor structure.
 * 
 */

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "generator.h"
#include "clipboard.h"
#include "rand.h"

//----------------------------------------------------------------------------
// Output constants to color values:
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

//----------------------------------------------------------------------------
// Global variables declaration:
static const char symbols[] = "!@#^&*$";

//----------------------------------------------------------------------------
char *add_suffix(char *src, const char *suffix) 
{
    const int len = strlen(src);
    char *tmp = realloc(src, len + strlen(suffix) + 1);
    if (!tmp) exit(1);
    strcpy(tmp + len, suffix);
    return tmp;
}

//----------------------------------------------------------------------------
char *add_prefix(char *src, const char *prefix) 
{
    const int len = strlen(src);
    char *tmp = malloc(len + strlen(prefix) + 1);
    if (!tmp) exit(1);
    strcpy(tmp, prefix);
    strcat(tmp, src);
    free(src);
    return tmp;
}

//----------------------------------------------------------------------------
// Recursive function will generate a random number between 
// the 4 available character types. 
// If a character type was not selected within arguments, generate random number again. 
int generate_type(bool CH_TYPE[])
{
    int char_type = random_nr(0, 3); 
    if (CH_TYPE[char_type] == false)
        return generate_type(CH_TYPE);
    return char_type;
}

//----------------------------------------------------------------------------
// This is the main function behind the random characters password generation.
// It uses the set of functions from the Jonathan Leffler library in order to generate
// true random numbers and convert them to the character preferences input by users.
extern int generate_random_CLI(bool CH_TYPE[], char *suffix, char *prefix)
{
    printf(C_WHITE "▘▗ Hipass Password Generator\n\n" C_RESET);    
    int characters = 0;
    do 
    {
        printf("Type in number of characters (between 14 and 1024): ");
        scanf("%i", &characters);

        // Clear input buffer:
        while ((getchar()) != '\n' && (getchar()) != EOF);
    } while (characters < 14 || characters > 1024);

    // Allocate memory as the number of characters * chars
    char *password = malloc(characters + 1);
    password[characters] = '\0';

    if (password == NULL)
    {
        printf("Could not allocate memory for password.\n");
        free(password); // Just being "super safe"
        return 1;
    }

    printf(C_GREEN "Password: ");
    if (prefix != NULL)
        printf(C_CYAN "%s", prefix);
    for (int i = 0; i < characters; i++)
    {
        enum {
            DIGIT,
            LOWER,
            UPPER,
            SYMBOL
        };
        // Selected char_type arguments will be parsed in this recursive function.
        int char_type = generate_type(CH_TYPE);
        
        switch (char_type) 
        {
        case DIGIT:
            password[i] = random_nr('0', '9');
            printf(C_BLUE "%c", password[i]);
            break;
        case LOWER:
            password[i] = random_nr('a', 'z');
            printf(C_WHITE "%c", password[i]);
            break;
        case UPPER:
            password[i] = random_nr('A', 'Z');
            printf(C_WHITE "%c", password[i]);
            break;
        case SYMBOL:
            password[i] = symbols[random_nr(0, sizeof symbols - 1)];
            printf(C_RED "%c", password[i]);
            break;
        }
    }
    if (suffix != NULL)
    {
        password = add_suffix(password, suffix); 
        printf(C_CYAN "%s", suffix);
    }
    if (prefix != NULL)
        password = add_prefix(password, prefix);

    printf("\n");
    copy_to_clipboard_prompt(password);
    printf("\n");
    free(password);
    return 0;
}
