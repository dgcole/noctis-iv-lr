#pragma once

// C Standard Library Includes

#include <assert.h>
#include <fcntl.h>
#include <math.h>
#include <memory.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>

/*

    Definitions for Noctis.
    Many.
*/

// Data Area:   Length:     Pointer:        Description:

#define om_bytes 7340 //   n_offsets_map contains "offsets.map",
//           (concave sphere in QT-VR).
#define gl_bytes 22586 //   n_globes_map    contains "globes.map"
//           (convex sphere in QT-VR).
//           sea surface texture.
#define gl_brest 10182 //   remainder of the bytes allocated for:
//           n_globes_map as this?
//           buffer is also used for:
//           the sea surface of 32K,
//           or otherwise for the font 32x36
//           which serves the pilot.
#define st_bytes 64800 //   s_background    star surface map;
//           satellite surface map;
//           surface sky map;
//           surface shading buffer.
#define pl_bytes 65552 //   p_background    planetary map from orbit;
//       texture for the ground.
#define ps_bytes 40000 //   p_surfacemap    elevation map;
//           temporary reading of buffer;
//           screen update buffer.
#define oc_bytes 40000 //   objectschart    map objects on the surface;
//           atmospheric overlay.
#define sc_bytes 65540 //   adapted         the hidden video page?�
//          2 bytes (support for polymap)
//           would give 64002. But I extended
//          it to 64Kb + 4 bytes to avoid it
//          breaking "poly3d", as there is one
//          faulty function I have neither the
//          time nor the care to change currently.
#define pv_bytes 20480 //   pvfile      dynamic data bank of files
//           of polygonal graphics.
// -------------------------//
// totale bytes         334941 //   (Dynamically allocated memory)
// -------------------------//
// +            222099 //   (Maximum length of Noctis.exe)
// +              6160 //   (Stack)
// -------------------------//
// =         (550K) 563200 //   (Maximum memory required)
//                 =========//

// Notes about the 550k: It is a limit that is roughly equivalent to the
//  maximum length of the three modules that the executable is made up of,
// and should not be exceeded.

// Noctis.exe stand-alone file map:
// --------------------------------------
// The supports.nct file must be added to the compiled executable,
//  and must contain the following files in the order shown below:

#define off_digimap2 -60776
#define dm2_bytes 9360

#define mammal_ncc -51416

#define os_voidscrn -48664
#define os_goescomm -44704
#define os_logogoes -40744

#define birdy_ncc -36784
#define vehicle_ncc -35782

#define header_bmp -29980
#define offsets_map -29926
#define globes_map -22586

// Limits, relative to the center of the screen, for 3D sticks.

#define stk_lbx -150
#define stk_lby -90
#define stk_ubx 160
#define stk_uby 90

// Working parameters for "tdpolygs.h", the polygonal 3D library.

#define VERTICI_PER_POLIGONO 4

#define larghezza 306
#define altezza 180
#define x_centro 158
#define y_centro 100

#define lbx -larghezza / 2 + x_centro
#define ubx larghezza / 2 + x_centro
#define lby -altezza / 2 + y_centro
#define uby altezza / 2 + y_centro

// Four thirds of PI.

#define qt_M_PI 4 * M_PI / 3

// Number of star classes and planet types.

#define star_classes 12
#define planet_types 10
#define avgmoons 4
#define log2avgmoons 2
#define maxbodies 20 * avgmoons

// Identification codes for planetary objects.

#define ROCKS 0
#define VEGET 1
#define TREES 2
#define NOTHING 3

// Identification codes of the ruins (in three texture styles).

#define AF1 0x40
#define AF2 0x80
#define AF3 0xC0

// Hand assignment for PV files.

#define vehicle_handle 0

#define bird_base 0
#define bird_result 1

#define mamm_base 2
#define mamm_result 3

// Structure of a byte in the surface object map (objectschart).

struct quadrant {
    uint16_t nr_of_objects : 2;
    uint16_t object0_class : 2;
    uint16_t object1_class : 2;
    uint16_t object2_class : 2;
};

// Structure that identifies a polygon and its vertices for the PV functions.

struct pvlist {
    uint16_t polygon_id : 12;
    uint8_t vtxflag_0 : 1;
    uint8_t vtxflag_1 : 1;
    uint8_t vtxflag_2 : 1;
    uint8_t vtxflag_3 : 1;
};

// Cutoff for double left and right clicks.
#define DBL_CLICK_CUTOFF 250000 // 250 ms? idk...

// Defines to help with porting.

// Some stuff to make porting assembly easier for now.

struct DWORDREGS {
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
};

struct WORDREGS {
    uint16_t di, _upper_di;
    uint16_t si, _upper_si;
    uint16_t bp, _upper_bp;
    uint16_t bx, _upper_bx;
    uint16_t dx, _upper_dx;
    uint16_t cx, _upper_cx;
    uint16_t ax, _upper_ax;
};

struct BYTEREGS {
    uint16_t di, _upper_di;
    uint16_t si, _upper_si;
    uint16_t bp, _upper_bp;
    uint8_t bl;
    uint8_t bh;
    uint16_t _upper_bx;
    uint8_t dl;
    uint8_t dh;
    uint16_t _upper_dx;
    uint8_t cl;
    uint8_t ch;
    uint16_t _upper_cx;
    uint8_t al;
    uint8_t ah;
    uint16_t _upper_ax;
};

union REGS {
    struct DWORDREGS d;
    struct WORDREGS w;
    struct BYTEREGS b;
};