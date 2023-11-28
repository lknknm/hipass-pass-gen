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
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "clipboard.h"

#define MIN_STRING 32

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
int copy_to_clipboard(const char *str)
{
    const char *proto_cmd = "echo '%s' | xclip -sel clipboard";
    char cmd[strlen(str) + strlen(proto_cmd) - 1];
    sprintf(cmd, proto_cmd, str);
    printf(C_GREEN "Password copied to clipboard.\n\n" C_RESET);
    return system(cmd);
}

//----------------------------------------------------------------------------
void copy_to_clipboard_prompt(const char *str)
{
    int clipPrompt;
    do {
        printf(C_WHITE "Do you want to copy the password to the clipboard? (y/n): " C_RESET);
        clipPrompt = getchar();

        if (tolower(clipPrompt) == 'y')
        {
            copy_to_clipboard(str);
            break;
        }
        if (tolower(clipPrompt) == 'n')
        {
            break;
        }
    } while (clipPrompt != 'y' || clipPrompt != 'n');

    // Clear input buffer:
    while ((getchar()) != '\n' && (getchar()) != EOF);
    return;
}
