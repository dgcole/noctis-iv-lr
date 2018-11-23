#ifndef _INCLUDE_RETARDALERT
#define _INCLUDE_RETARDALERT

#include "noctis-d.h"

int32_t carryAddMultiply(int32_t a, int32_t b) {
    asm pusha;

    _EDX = a;
    _EAX = b;

    asm db 0x66
    asm imul dx
    _EDX += _EAX;

    int32_t result = _EDX;
    asm popa;
    return result;
}

#endif
