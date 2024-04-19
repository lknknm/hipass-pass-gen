/**
 * Hipass CLI Password Generator
 * 
 * Author: @lknknm
 *  Date: April 2024
 *  Version: 0.2.0
 *
 * Contributors:
 *  @FuelledByCoffee
 * 
 */

#include <stdbool.h>
#include <unistd.h>
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
// This function is used to detect which platform Hipass is running on, so in this
// way it can be platform agnostic between Windows, MacOS and Linux.
// This function is originally from a Stack Overflow answer, more information in the link below.
// https://stackoverflow.com/questions/41230547/check-if-program-is-installed-in-c
bool can_run_command(const char *cmd) 
{
    if(strchr(cmd, '/')) 
    {
        // if cmd includes a slash, no path search must be performed,
        // go straight to checking if it's executable
        return access(cmd, X_OK)==0;
    }
    const char *path = getenv("PATH");
    if(!path) return false; // something is horribly wrong...
    // we are sure we won't need a buffer any longer
    char *buf = malloc(strlen(path)+strlen(cmd)+3);
    if(!buf) return false; // actually useless, see comment
    // loop as long as we have stuff to examine in path
    for(; *path; ++path) 
    {
        // start from the beginning of the buffer
        char *p = buf;
        // copy in buf the current path element
        for(; *path && *path!=':'; ++path,++p) {
            *p = *path;
        }
        // empty path entries are treated like "."
        if(p==buf) *p++='.';
        // slash and command name
        if(p[-1]!='/') *p++='/';
        strcpy(p, cmd);
        // check if we can execute it
        if(access(buf, X_OK)==0) {
            free(buf);
            return true;
        }
        // quit at last cycle
        if(!*path) break;
    }
    // not found
    free(buf);
    return false;
}


//----------------------------------------------------------------------------
// Function used to copy the password to the clipboard. 
// It uses the can_run_command bool function to check which platform Hipass is running on.
int copy_to_clipboard(const char *str)
{
    const char       *tool         = NULL;
    const char *const clip_tools[] = {"clip.exe", // windows
                                      "pbcopy",   // mac
                                      "xclip"};
    if (can_run_command(clip_tools[0]))
        tool = clip_tools[0];
    else if (can_run_command(clip_tools[1]))
        tool = clip_tools[1];
    else if (can_run_command(clip_tools[2]))
        tool = "xclip -sel clipboard";

    const char *proto_cmd = "echo '%s' | %s"; 
    char cmd[strlen(str) + strlen(proto_cmd) + strlen(tool) - 1];
    sprintf(cmd, proto_cmd, str, tool);
    printf(C_GREEN "Password copied to clipboard.\n" C_RESET);
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
