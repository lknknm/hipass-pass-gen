#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

// Function prototypes:
int copy_to_clipboard(const char *str);

int main(void)
{
    printf("Hipass Password Generator\n\n");

    int characters = 0;
    do {
    printf("Type in number of characters (between 14 and 128): ");
    scanf("%i", &characters);
    } while (characters < 14 || characters > 128);

    srand(time(NULL));

    char *digits = "0123456789";
    char *lowercase = "abcdefghijklmnopqrstuvwxyz";
    char *uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *symbols = "!@#^&*$";
    int symbols_length = strlen(symbols);

    char *password = malloc(sizeof(characters));
    if (password == NULL)
    {
        printf("Could not allocate memory for password.\n");
        free(password);
        return 1;
    }

    printf("\033[0;32m"); // Green text value
    printf("Password: ");

    for (int i = 0; i < characters; i++)
    {
        //char randomLetter = 'a' + rand() % 26;
        //password[i] = randomLetter;

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

int copy_to_clipboard(const char *str)
{
    const char *proto_cmd = "echo '%s' | clip.exe";

    char cmd[strlen(str) + strlen(proto_cmd) - 1];
    sprintf(cmd, proto_cmd, str);

    return system(cmd);
}