/**
 * Hipass CLI Password Generator
 * 
 * This is the main file for Hipass Password Generator.
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

#include "rand.h"
#include "generator.h"
#include "clipboard.h"

//----------------------------------------------------------------------------
// Metadata:
#define VERSION "0.2.0"
#define DATE "April 12th 2024"

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


/**
 * boolean declaration to parse command line into the generator algorithm
 * numeric digits, az-lowercase, AZ-uppercase, symbols;
 */
bool CH_TYPE[4] = { 0, 0, 0, 0 };

//----------------------------------------------------------------------------
// Program entrypoint
int main(int argc, char **argv)
{
    int c;
    int digit_optind = 0;
    char *prefix = NULL;
    char *suffix = NULL;
    char *separator = NULL;

    while (1)
    {
        int this_option_optind = optind ? optind : 1;
        int option_index = 0;
        static struct option long_options[] = {
            {"help",        no_argument,            0,  'h' },
            {"version",     no_argument,            0,  'v' },
            {"suffix",      required_argument,      0,  '1' },
            {"prefix",      required_argument,      0,  '2' },
            {"passphrase",  required_argument,      0,  'p' },
            {0,             0,                      0,   0  }
        };

        c = getopt_long(argc, argv, "hv:p:12",
                    long_options, &option_index);
        if (c == -1)
            break;

        switch (c) 
        {                       
            case 'h':   
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
                        printf(" -h --help           Print out help text\n");
                        printf(" -v --version        Print version\n");
                        printf(" --update            Update to latest release\n");
                        printf("\n");
                        printf(" --prefix PREFIX     Generate password with a desired prefix\n");
                        printf(" --suffix suffix     Generate password with a desired suffix\n");
                        printf(" --passphrase sep    Generate passphrase with a desired char separator and a random number in the end\n");
                        printf("\n");
                        printf("Refer to README.md in the GitHub Repository for full notes.\n\n");

                        return 0;

            case 'v':   
                        printf("hipass version " VERSION " release date " DATE);
                        printf("\n");
                        return 0;
            case '1':
                        printf("option %s\n", long_options[option_index].name);
                        suffix = optarg;
                        if (suffix)
                        {
                            printf("suffix %s", suffix);
                            printf("\n");
                        }
                        printf("\n");
                        continue;

            case '2':
                        printf("option %s\n", long_options[option_index].name);
                        prefix = optarg;
                        if (prefix)
                        {
                            printf("prefix %s", prefix);
                            printf("\n");
                        }
                        printf("\n");
                        break;

            case 'p':  
                        separator = optarg;
                        generate_passphrase(separator);
                        return 0;

            case '?':
                printf("Option not available please prompt Hipass again\n");
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
        for (int i = 0; i < 4; i++)
            CH_TYPE[i] = 1;
        generate_random_CLI(CH_TYPE, NULL, NULL);
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

    memset(CH_TYPE, 0, 4*sizeof(CH_TYPE[0]));
    for (int i = 1; i < argc; i++)
    {
        if (strncmp("num", argv[i], 3) == 0) {
            printf("include num\n");
            CH_TYPE[0] = true;
        }
        else if (strncmp("az", argv[i], 2) == 0) {
            printf("include az_lower\n");
            CH_TYPE[1] = true;
        }
        else if (strncmp("AZ", argv[i], 2) == 0) {
            printf("include AZ\n");
            CH_TYPE[2] = true;
        }
        else if (strncmp("sym", argv[i], 2) == 0) {
            printf("include !#_symbols\n");
            CH_TYPE[3] = true;
        }
    }
    for (int i = 0; i < 4; i++)
        printf("CHAR TYPES = %i\n", CH_TYPE[i]);
    generate_random_CLI(CH_TYPE, suffix, prefix);
    return 0;
}