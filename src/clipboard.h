#ifndef CLIPBOARD_H
#define CLIPBOARD_H

// Definition to copy to clipboard on cmd.
int copy_to_clipboard(const char *str);
void copy_to_clipboard_prompt(const char *str);

#endif // CLIPBOARD_H