#pragma once

// C Standard Library includes

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <memory.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef _WIN32
#define SDL_MAIN_HANDLED
#endif
#include <SDL2/SDL.h>

#include <angelscript.h>

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

#define VERTEXES_PER_POLYGON 4

#define VIEW_WIDTH 306
#define VIEW_HEIGHT 180
#define VIEW_X_CENTER 158
#define VIEW_Y_CENTER 100

#define lbx ((-VIEW_WIDTH / 2) + VIEW_X_CENTER)
#define ubx ((VIEW_WIDTH / 2) + VIEW_X_CENTER)
#define lby ((-VIEW_HEIGHT / 2) + VIEW_Y_CENTER)
#define uby ((VIEW_HEIGHT / 2) + VIEW_Y_CENTER)

#define TEXTURE_X_SIZE 256
#define TEXTURE_Y_SIZE 256

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

// Timing-related defines
#define DBL_CLICK_CUTOFF 125000 // 250 ms? idk...

#define FRAME_TIME_MILLIS 55 // To correspond with the 55ms clock in DOS


// Used to indicate WASD movement direction.
// Exists for ease of readability
struct wasdmov {
	bool forward;
	bool backward;
	bool left;
	bool right;
};
