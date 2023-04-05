#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "clipboard.h"

int copy_to_clipboard(const char *str)
{
    const char *proto_cmd = "echo '%s' | clip.exe";

    char cmd[strlen(str) + strlen(proto_cmd) - 1];
    sprintf(cmd, proto_cmd, str);

    return system(cmd);
}