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
#include <string.h>
#include <stdbool.h>

#include "generator.h"
#include "clipboard.h"

#include "posixver.h"
#include <assert.h>
#include "randseed.h"
#include "prng48.h"

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
static const char digits[] = "0123456789";
static const char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
static const char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char symbols[] = "!@#^&*$";

static const enum len 
{
    NUM_DIGITS = sizeof(digits) - 1,
    NUM_LOWERCASE = sizeof(lowercase) - 1,
    NUM_UPPERCASE = sizeof(uppercase) - 1,
    NUM_SYMBOLS = sizeof(symbols) - 1
} types;

//----------------------------------------------------------------------------
char *add_suffix(char *src, const char *suffix) 
{
    const int len = sizeof(src);
    char *tmp = realloc(src, len + sizeof(suffix) + 1);
    if (!tmp) exit(1);
    strcpy(tmp + len, suffix);
    return tmp;
}

//----------------------------------------------------------------------------
extern int generate_random_complete(void)
{
    unsigned short seed[3];
    random_seed_bytes(sizeof(seed), seed);
    prng48_seed(seed);

    printf(C_WHITE "Hipass Password Generator\n\n" C_RESET);    

    int characters = 0;
    do 
    {
        printf("Type in number of characters (between 14 and 256): ");
        scanf("%i", &characters);

        // Clear input buffer:
        while ((getchar()) != '\n' && (getchar()) != EOF);
    } while (characters < 14 || characters > 256);

    // Allocate memory as the number of characters * chars
    char *password = malloc(sizeof(char[characters]) + 1);
    password[characters] = '\0';
    if (password == NULL)
    {
        printf("Could not allocate memory for password.\n");
        free(password); // Just being "super safe"
        return 1;
    }

    printf(C_GREEN "Password: ");
    for (int i = 0; i < characters; i++)
    {
        // sizeof(types) will return the size of an int, which is 4 bytes.
        // Silly modulo bitwise operation
        int char_type = prng48_rand(0, 0xABCDE) & (sizeof(types) - 1); 
        
        if (char_type == 0) 
        {
            password[i] = digits[prng48_rand(0, 0xABCDE) % NUM_DIGITS];
            printf(C_BLUE "%c", password[i]);
        }
        else if (char_type == 1) 
        {
            password[i] = lowercase[prng48_rand(0, 0xABCDE) % NUM_LOWERCASE];
            printf(C_WHITE "%c", password[i]);
        }
        else if (char_type == 2) 
        {
            password[i] = uppercase[prng48_rand(0, 0xABCDE) % NUM_UPPERCASE];
            printf(C_WHITE "%c", password[i]);
        }
        else if (char_type == 3) 
        {
            password[i] = symbols[prng48_rand(0, 0xABCDE) % NUM_SYMBOLS];
            printf(C_RED "%c", password[i]);
        }
    }
    
    printf("\n");
    copy_to_clipboard_prompt(password);
    printf("\n");
    free(password);
    return 0;
}

//----------------------------------------------------------------------------
// Recursive function will generate a random number between 
// the 4 available character types. 
// If a character type was not selected within arguments, generate random number again. 
int generate_type(bool CH_TYPE[])
{
    unsigned short seed[3];
    random_seed_bytes(sizeof(seed), seed);
    prng48_seed(seed);
    int char_type = prng48_rand(0, 0xABCDE) & (sizeof(types) - 1); 
    if (CH_TYPE[char_type] == false)
        return generate_type(CH_TYPE);
    return char_type;
}

//----------------------------------------------------------------------------
extern int generate_random_CLI(bool CH_TYPE[], char *suffix)
{
    unsigned short seed[3];
    random_seed_bytes(sizeof(seed), seed);
    prng48_seed(seed);

    printf(C_WHITE "Hipass Password Generator\n\n" C_RESET);    
    int characters = 0;
    do 
    {
        printf("Type in number of characters (between 14 and 256): ");
        scanf("%i", &characters);

        // Clear input buffer:
        while ((getchar()) != '\n' && (getchar()) != EOF);
    } while (characters < 14 || characters > 256);

    // Allocate memory as the number of characters * chars
    char *password = malloc(sizeof(char[characters]) + 1);
    password[characters] = '\0';
    if (suffix != NULL)
    {
        password = add_suffix(password, suffix);
    }

    if (password == NULL)
    {
        printf("Could not allocate memory for password.\n");
        free(password); // Just being "super safe"
        return 1;
    }

    printf(C_GREEN "Password: ");
    for (int i = 0; i < characters; i++)
    {
        // Selected char_type arguments will be parsed in this recursive function.
        int char_type = generate_type(CH_TYPE);
        
        if (char_type == 0) 
        {
            password[i] = digits[prng48_rand(0, 0xABCDE) % NUM_DIGITS];
            printf(C_BLUE "%c", password[i]);
        }
        else if (char_type == 1) 
        {
            password[i] = lowercase[prng48_rand(0, 0xABCDE) % NUM_LOWERCASE];
            printf(C_WHITE "%c", password[i]);
        }
        else if (char_type == 2) 
        {
            password[i] = uppercase[prng48_rand(0, 0xABCDE) % NUM_UPPERCASE];
            printf(C_WHITE "%c", password[i]);
        }
        else if (char_type == 3) 
        {
            password[i] = symbols[prng48_rand(0, 0xABCDE) % NUM_SYMBOLS];
            printf(C_RED "%c", password[i]);
        }
    }
    if (suffix != NULL)
        printf(C_CYAN "%s", suffix);

    printf("\n");
    copy_to_clipboard_prompt(password);
    printf("\n");
    free(password);
    return 0;
}

//----------------------------------------------------------------------------
// Passphrase generator wip.
extern void generate_passphrase(void)
{
    printf("hello world!\n");
}