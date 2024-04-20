#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#include <stdbool.h>

// Definition to copy to clipboard on cmd.
bool can_run_command(const char *cmd);
int copy_to_clipboard(const char *str);
extern void copy_to_clipboard_prompt(const char *str);

#endif // CLIPBOARD_H
