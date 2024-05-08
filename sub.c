#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "sub.h"
char* stripstr(char *str) {
    str[strcspn(str, "\n")] = 0;
    str[strcspn(str, "\r")] = 0;
    return str;
}