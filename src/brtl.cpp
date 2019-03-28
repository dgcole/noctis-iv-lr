#include "brtl.h"

#include <cstdint>
#include <ctype.h>

void brtl_strupr(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}