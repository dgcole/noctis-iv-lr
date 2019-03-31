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

void brtl_srand(uint32_t seed) {
    srand(seed);
}

int16_t brtl_rand() {
    return (int16_t) rand();
}

int16_t brtl_random(int16_t num) {
    return rand() % num;
}