#ifndef _INCLUDE_ASMHACKS
#define _INCLUDE_ASMHACKS

#include "noctis-d.h"

/**
 * Multiply two 32-bit numbers together, and add the low 32 bits of the result
 * to the high 32 bits of the result, returning that.
 */

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

/// Shift the segment of a given far pointer by a given segment count.
uint8_t far* shiftSegment(uint8_t far* in, int16_t segshift) {
    int32_t address = (int32_t) in;
    address += ((int32_t) segshift) << 16;
    return (uint8_t far*) address;
}

/// Clear the offset on a given far pointer.
uint8_t far* clearOffset(uint8_t far* in) {
    int32_t address = (int32_t) in;
    address &= 0xFFFF0000;
    return (uint8_t far*) address;
}



#endif
