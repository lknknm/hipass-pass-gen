/**
 * Hipass CLI Password Generator
 * Developed as Final Project for 
 * Harvard's CS50x Introduction to Computer Science
 * 
 * This is the main file for Hipass Password Generator.
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
#include <getopt.h>

#include "generator.h"
#include "clipboard.h"

// metadata
#define VERSION "0.1.0"
#define DATE "may 15th 2023"

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


/**
 * boolean declaration to parse command line into the generator algorithm
 * numeric digits, az-lowercase, AZ-uppercase, symbols;
 */
bool CH_TYPE[4] = { 0, 0, 0, 0 };

int main(int argc, char **argv)
{
    int c;
    int digit_optind = 0;

    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"help",        no_argument,            0,  'a' },
            {"version",     no_argument,            0,  'v' },
            {"sufix",       required_argument,      0,  's' },
            {"passphrase",  no_argument,            0,  'P' },
            {0,             0,                      0,   0  }
        };

        c = getopt_long(argc, argv, "abc:d:012",
                    long_options, &option_index);
        if (c == -1)
            break;

        switch (c) 
        {                       
            case 'a':   
                        printf(C_WHITE "Hipass Password Generator\n\n");    
                        printf(C_RESET "usage: hipass [--flag] [-f]\n");    
                        printf("*no flags           User will be prompted to choose character length\n");
                        printf("                    of a random password with A-Z uppercase, a-z lowercase, numbers and special characters\n");
                        printf("\n");
                        printf("The following arguments will generate passwords with the ones user had selected.\n");
                        printf("Example: ./hipass AZ num sym az\n");
                        printf("\n");
                        printf("    AZ               Include A to Z uppercase characters\n");
                        printf("    az               Include a to z lowercase characters\n");
                        printf("    sym              Include special symbols\n");
                        printf("    num              Include digits from 0 to 9\n");
                        printf("\n");
                        printf(" -h --help          Print out help text\n");
                        printf(" -v --version       Print version\n");
                        printf(" --update           Update to latest release\n");
                        printf("\n");
                        printf(" --prefix PREFIX    Generate password with a desired prefix\n");
                        printf(" --sufix SUFIX      Generate password with a desired sufix\n");
                        printf("\n");
                        printf("Refer to README.md in the GitHub Repository for full notes.\n\n");

                        return 0;

            case 'v':   
                        printf("hipass version " VERSION " release date " DATE);
                        printf("\n");
                        return 0;
            case 's':
                        printf("option %s\n", long_options[option_index].name);
                        char *sufix = optarg;
                        if (sufix)
                        {
                            printf("sufix %s", sufix);
                            printf("\n");
                            memset(CH_TYPE, 1, 4*sizeof(CH_TYPE[0]));
                            generate_random_CLI(CH_TYPE, sufix);
                        }
                        printf("\n");
                        return 0;

            case 'P':   
                        generate_passphrase();
                        return 0;
        }
    }


    /*  If user doesn't input arguments: 
     *  the program should execute normally generating
     *  a random password including
     *  A-Z uppercase + a-z lowercase + symbols (!@#^&*$) + 0-9 numeric
     */

    if (argc == 1) 
    {
        generate_random_complete();
        return 0;
    }

    /*  The following should check the command line arguments to generate a
     *  random password using different inputs as described by README.md
     *
     *  num to add numeric 0-9 characters;
     *  az to add a-z lowercase letters;
     *  AZ to add A-Z uppercase letters;
     *  sym to add symbol (!@#^&*$) characters;
     *  Arguments can be input in any order. 
     */

    for (int i = 1; i < argc; i++)
    {
        if (strncmp("num", argv[i], 3) == 0) {
            printf("option num\n");
            CH_TYPE[0] = true;
        }
        else if (strncmp("az", argv[i], 2) == 0) {
            printf("option az_lower\n");
            CH_TYPE[1] = true;
        }
        else if (strncmp("AZ", argv[i], 2) == 0) {
            printf("option AZ\n");
            CH_TYPE[2] = true;
        }
        else if (strncmp("sym", argv[i], 2) == 0) {
            printf("option !#_symbols\n");
            CH_TYPE[3] = true;
        }
    }
    char *sufix = NULL;
    generate_random_CLI(CH_TYPE, sufix);
    return 0;

}