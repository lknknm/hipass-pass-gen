#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "lib/generator.h"
#include "lib/clipboard.h"

int main(int argc, char **argv)
{
    printf("Hipass Password Generator\n\n");

    int characters = 0;
    do {
    printf("Type in number of characters (between 14 and 256): ");
    scanf("%i", &characters);
    } while (characters < 14 || characters > 256);

    char *password = malloc(sizeof(characters));
    if (password == NULL)
    {
        printf("Could not allocate memory for password.\n");
        free(password);
        return 1;
    }

    printf("\033[0;32m"); // Green text value
    printf("Password: ");

    generate_random_complete(password, characters);

    char clipCopy;
    printf("\033[0;37m"); // White text value
    printf("\nDo you want to copy the password to the clipboard? (y/n): ");
    scanf("%s", &clipCopy);

    if(clipCopy == 'y' || clipCopy == 'Y')
    {
        copy_to_clipboard(password);
        printf("\033[0;32m");
        printf("Password copied to clipboard.\n\n");
    }

    free(password);
    return 0;
}