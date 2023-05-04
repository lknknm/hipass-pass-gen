#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "generator.h"

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

// Global variables declaration:
char *digits = "0123456789";
char *lowercase = "abcdefghijklmnopqrstuvwxyz";
char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char *symbols = "!@#^&*$";
int symbols_length = 7;


void generate_random_complete(char *password, int characters)
{
    srand(time(NULL));
    for (int i = 0; i < characters; i++)
    {
        int char_type = rand() % 4;
        
        if (char_type == 0) {
            password[i] = digits[rand() % 10];
            printf(C_BLUE "%c", password[i]);
        }
        else if (char_type == 1) {
            password[i] = lowercase[rand() % 26];
            printf(C_WHITE "%c", password[i]);
        }
        else if (char_type == 2) {
            password[i] = uppercase[rand() % 26];
            printf(C_WHITE "%c", password[i]);
        }
        else if (char_type == 3) {
            password[i] = symbols[rand() % symbols_length];
            printf(C_RED "%c", password[i]);
        }
    }
    printf("\n");
    fflush(stdin);
    return;
}
