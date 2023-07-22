#include "brtl.h"

#include <cstdint>
#include <cstdlib>
#include <ctype.h>

void brtl_strupr(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void brtl_srand(uint16_t seed) { brtl_seed = seed; }

int16_t brtl_rand() {
    brtl_seed = brtl_seed * ((int32_t) 0x015a4e35) + 1;

    return (int16_t) (brtl_seed >> 16) & 0x7FFF;
}

int16_t brtl_random(int16_t num) { return (int16_t) (((int32_t) brtl_rand() * num) / (((uint16_t) 0x7FFF) + 1)); }