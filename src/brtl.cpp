#include "brtl.h"

#include <ctype.h>

void brtl_strupr(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}