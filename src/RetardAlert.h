#ifndef _INCLUDE_RETARDALERT
#define _INCLUDE_RETARDALERT

#include "noctis-d.h"

int32_t carryAddMultiply(int32_t a, int32_t b) {
    int32_t result;
    asm {
        pusha

        db 0x66
        mov dx, word ptr a
        db 0x66
        mov ax, word ptr b

        db 0x66
        imul dx
        db 0x66
        add dx, ax

        db 0x66
        mov word ptr result, dx

        popa
    }
    return result;
}

#endif
