#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "generator.h"

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
            printf("\033[0;34m"); //Blue text value
            printf("%c", password[i]);
        }
        else if (char_type == 1) {
            password[i] = lowercase[rand() % 26];
            printf("\033[0;37m"); //White text value
            printf("%c", password[i]);
        }
        else if (char_type == 2) {
            password[i] = uppercase[rand() % 26];
            printf("\033[0;37m"); //White text value
            printf("%c", password[i]);
        }
        else if (char_type == 3) {
            password[i] = symbols[rand() % symbols_length];
            printf("\033[0;31m"); //Red text value
            printf("%c", password[i]);
        }
    }

    return;
}
