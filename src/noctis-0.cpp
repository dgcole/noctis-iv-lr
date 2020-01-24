/*

    Noctis.
    -------
    NOTE: This bit was something irrelevant that was too hard to translate.|

    Noctis: Feline People.
    ----------------------------
    Space: The Final Frontier.
    These are the journeys of the cosmic rafts of the feline people.
    Their mission (missions?) is to explore strange, new worlds,
    looking for territory to conquer, and eliminating any new forms
    of life or new civilization... to get there... where no feline has
    been before.

    Story.
    -------
    Complicated. The program is complciated: maybe a little too much,
    certainly more than usual. If you do not find a way to compile it
    (we are at 6900 lines only with the main source), you will have to
    modularize it (Never done before, very laborious and very unpleasant).
    or find another compiler. Currently Implemented: Spaceships, stars
    and planets, an on-board manager, user reflections, planet surfaces,
    atmospheric noises (wind, rain, thunder NOTE: Where?!?!|). NOTE: Last
    sentence made no sense.| -> 27.1.97
    -------
    The program has been split into two modules. -> 28.1.97

    Module Containing the Base Functions of Noctis
    ----------------------------------------
    The project consists of NOCTIS-0.CPP, NOCTIS.CPP, and a file including
    definitions common to the two modules.

*/

#include <iostream>
#include <stack>

#include "brtl.h"
#include "noctis-d.h"

// Date and specific functions imported from ASSEMBLY.H

uint16_t QUADWORDS = 16000;

// Video memory. Because Noctis was originally written to use Mode 0x13, this
// represents a sequence of 64,000 color indices.
uint8_t *adapted;

uint8_t tmppal[768];
uint8_t currpal[768];
int8_t return_palette[768];
int8_t surface_palette[768];

static std::stack<int16_t> keys;

// Wait for a key?
int16_t get_key() {
    if (keys.empty())
        return 0;
    int16_t top = keys.top();
    keys.pop();
    return top;
}

// Return 1 if there is a key press to be processed.
bool is_key() { return !keys.empty(); }

uint8_t range8088[64 * 3] = {
    0,  0,  0,  1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,  5,  5,
    6,  6,  6,  7,  7,  7,  8,  8,  8,  9,  9,  9,  10, 10, 10, 11, 11, 11,
    12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17,
    18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23,
    24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29,
    30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35,
    36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41,
    42, 42, 42, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47,
    48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 53,
    54, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 59,
    60, 60, 60, 61, 61, 61, 62, 62, 62, 63, 63, 63};

// This sets up the vga color palette.
void tavola_colori(const uint8_t *new_palette, uint16_t starting_color,
                   uint16_t num_colors, int8_t red_filter, int8_t green_filter,
                   int8_t blue_filter) {
    int16_t c, cc = 0;
    uint16_t temp;
    num_colors *= 3;
    starting_color *= 3;
    c = starting_color;

    while (cc < num_colors) {
        tmppal[c] = new_palette[cc];
        cc++;
        c++;
    }

    c = starting_color;

    while (c < num_colors + starting_color) {
        temp = tmppal[c];
        temp *= red_filter;
        temp /= 63;

        if (temp > 63) {
            temp = 63;
        }

        tmppal[c] = temp;
        c++;
        temp = tmppal[c];
        temp *= green_filter;
        temp /= 63;

        if (temp > 63) {
            temp = 63;
        }

        tmppal[c] = temp;
        c++;
        temp = tmppal[c];
        temp *= blue_filter;
        temp /= 63;

        if (temp > 63) {
            temp = 63;
        }

        tmppal[c] = temp;
        c++;
    }

    for (uint16_t i = 0; i < (starting_color + num_colors); i++) {
        currpal[i] = tmppal[i];
    }
}

// Variables to hold mouse readings.
int16_t mdltx = 0, mdlty = 0, mouse_x = 0, mouse_y = 0;
uint16_t mpul = 0;

// Holds directions of WASD movement
struct wasdmov key_move_dir;

// Handle SDL events..
void handle_input() {
    static bool ldown = false;
    static bool rdown = false;

    mdltx = 0;
    mdlty = 0;
    mpul  = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            /* WASD player/camera movement. */
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
                key_move_dir.forward = (event.type == SDL_KEYDOWN);
                break;
            case SDL_SCANCODE_A:
                key_move_dir.left = (event.type == SDL_KEYDOWN);
                break;
            case SDL_SCANCODE_S:
                key_move_dir.backward = (event.type == SDL_KEYDOWN);
                break;
            case SDL_SCANCODE_D:
                key_move_dir.right = (event.type == SDL_KEYDOWN);
                break;
            default:
                break;
            }
        }

        if (event.type == SDL_QUIT) {
            exit(0);
        } else if (event.type == SDL_MOUSEMOTION) {
            mdltx = event.motion.xrel;
            mdlty = event.motion.yrel;

            mouse_x += mdltx;
            mouse_y += mdlty;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT)
                ldown = true;
            if (event.button.button == SDL_BUTTON_RIGHT)
                rdown = true;
        } else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT)
                ldown = false;
            if (event.button.button == SDL_BUTTON_RIGHT)
                rdown = false;
        } else if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_1:
            case SDL_SCANCODE_2:
            case SDL_SCANCODE_3:
            case SDL_SCANCODE_4:
            case SDL_SCANCODE_5:
            case SDL_SCANCODE_6:
            case SDL_SCANCODE_7:
            case SDL_SCANCODE_8:
            case SDL_SCANCODE_9:
                keys.push(event.key.keysym.scancode + ('1' - SDL_SCANCODE_1));
                break;
            case SDL_SCANCODE_0:
                keys.push('0');
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_B:
            case SDL_SCANCODE_C:
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_E:
            case SDL_SCANCODE_F:
            case SDL_SCANCODE_G:
            case SDL_SCANCODE_H:
            case SDL_SCANCODE_I:
            case SDL_SCANCODE_J:
            case SDL_SCANCODE_K:
            case SDL_SCANCODE_L:
            case SDL_SCANCODE_M:
            case SDL_SCANCODE_N:
            case SDL_SCANCODE_O:
            case SDL_SCANCODE_P:
            case SDL_SCANCODE_Q:
            case SDL_SCANCODE_R:
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_T:
            case SDL_SCANCODE_U:
            case SDL_SCANCODE_V:
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_X:
            case SDL_SCANCODE_Y:
            case SDL_SCANCODE_Z:
                keys.push(event.key.keysym.scancode + ('a' - SDL_SCANCODE_A));
                break;
            case SDL_SCANCODE_UP:
                keys.push(72);
                keys.push(0);
                break;
            case SDL_SCANCODE_DOWN:
                keys.push(80);
                keys.push(0);
                break;
            case SDL_SCANCODE_LEFT:
                keys.push(75);
                keys.push(0);
                break;
            case SDL_SCANCODE_RIGHT:
                keys.push(77);
                keys.push(0);
                break;
            case SDL_SCANCODE_BACKSPACE:
                keys.push(8);
                break;
            case SDL_SCANCODE_RETURN:
                keys.push(13);
                break;
            case SDL_SCANCODE_ESCAPE:
                keys.push(27);
                break;
            case SDL_SCANCODE_APOSTROPHE:
                keys.push(39);
                break;
            case SDL_SCANCODE_SPACE:
                keys.push(' ');
                break;
            case SDL_SCANCODE_DELETE:
                keys.push('*');
                break;
            case SDL_SCANCODE_MINUS:
                keys.push('-');
                break;
            case SDL_SCANCODE_COMMA:
                keys.push(',');
                break;
            case SDL_SCANCODE_SLASH:
                keys.push('/');
                break;
            case SDL_SCANCODE_KP_COLON:
            case SDL_SCANCODE_SEMICOLON:
                keys.push(':');
            case SDL_SCANCODE_F1: {
                static bool captured = false;
                captured = !captured;
                SDL_SetRelativeMouseMode((SDL_bool) captured);
            }
            default:
                break;
            }
        }
    }

    if (ldown)
        mpul |= 1u;
    if (rdown)
        mpul |= 2u;
}

// Clears a rectangular region of the video memory.
// Either x2 & y2 OR l and h must be specified.
// This may or may not work.
void area_clear(uint8_t *dest, int16_t x, int16_t y, int16_t x2, int16_t y2,
                int16_t l, int16_t h, uint8_t pattern) {
    if (l == 0 || h == 0) {
        l = x2 - x;
        h = y2 - y;
    }

    for (int16_t xPos = x; xPos < x + l; xPos++) {
        for (int16_t yPos = y; yPos < y + h; yPos++) {
            uint16_t netIndex = (yPos * 320) + xPos;
            dest[netIndex]    = pattern;
        }
    }
}

/*

    Another gem: smooth the screen, softening the contrast of the edges by
    averaging 4 x 4 groups of pixels. Pay attention to the trick: Normally there
    would be 16 additions and one division (for 16) to do, for each point. With
    the trick, however, only four 32-bit additions are needed, and another four
    with 8 bits, plus a pair of shifts.

    Normal: 16 + 42 = 58 Cycles.
    Now: 8 + 4 = 12 Cycles.

    Quite obvious: The color table must be unique and compact, to be included in
    the first 64 registers of the video DAC; the color zero is the smallest, 63
    the brightest.

    Note: This procedure can be repeated to obtain greater attenuation.
*/

void psmooth_grays(uint8_t *target) {
    uint16_t count = (QUADWORDS << 2u) - (320u << 2u);
    int index      = 0;
    for (uint16_t i = 0; i < count; i++, index++) {
        uint8_t smoothed;
        uint32_t temp;

        temp = (target[index + 3] << 24u) + (target[index + 2] << 16u) +
               (target[index + 1] << 8u) + target[index];

        temp += (target[index + 323] << 24u) + (target[index + 322] << 16u) +
                (target[index + 321] << 8u) + target[index + 320];

        temp += (target[index + 643] << 24u) + (target[index + 642] << 16u) +
                (target[index + 641] << 8u) + target[index + 641];

        temp += (target[index + 963] << 24u) + (target[index + 962] << 16u) +
                (target[index + 961] << 8u) + target[index + 960];

        temp &= 0xFCFCFCFC;
        temp >>= 2u;

        smoothed = temp & 0xFFu;
        smoothed += temp & 0xFF00u;

        temp >>= 16u;

        smoothed += temp & 0xFFu;
        smoothed += temp & 0xFF00u;
        smoothed >>= 2u;
        target[320] = smoothed;
    }
}

// Produces the fading effect seen during vimana flight.
void pfade(uint8_t *target, uint16_t segshift, uint8_t speed) {
    // Don't know why count is set as it is.
    uint16_t count   = (QUADWORDS - 80u) << 2u;
    uint8_t *shifted = (target + segshift * 16);
    // Quasi-offset might need to be cleared.

    for (uint16_t i = 0; i < count; i++) {
        uint8_t color = shifted[i];
        color &= 0x3Fu;

        if (speed < color) {
            color -= speed;
        } else {
            color = 0;
        }

        shifted[i] = color;
    }
}

// Color version: 4 shades of 64 intensity each.
void psmooth_64(uint8_t *target, uint16_t segshift) {
    // Who knows why this is offset as it is... Definitely not me.
    uint16_t count = (QUADWORDS - 80u) << 2u;
    // We might need to align the shifted pointer to a 16 byte interval to match
    // the former offset clearing. Sketchy.
    uint8_t *shifted = (target + (segshift * 16));

    uint8_t avg, orig;
    for (uint16_t i = 0; i < count; i++) {
        orig = shifted[i + 320] & 0xC0u;
        avg  = (((shifted[i + 320] & 0x3Fu) + (shifted[i + 640] & 0x3Fu)) +
               ((shifted[i + 321] & 0x3Fu) + (shifted[i + 641] & 0x3Fu))) /
              4;

        shifted[i] = avg | orig;
    }
}

// Circular version of the smoothing process.
// Used on the white corners on the hud and on planets.
void smootharound_64(uint8_t *target, int32_t cx, int32_t cy, int32_t r,
                     int8_t diffuse) {
    int32_t x1 = cx - r, y1 = cy - r;
    int32_t x2 = cx + r, y2 = cy + r;
    int32_t px, py, rs = r * r;
    uint16_t cp;

    if (r <= 0 || x1 > 318 || y1 > 198 || x2 < 0 || y2 < 0) {
        return;
    }

    if (y1 < 0) {
        y1 = 0;
    }

    if (x2 > 318) {
        x2 = 318;
    }

    if (y2 > 198) {
        y2 = 198;
    }

    py = -r;

    while (y1 <= y2) {
        px = -r;
        x1 = cx - r;

        if (x1 < 0) {
            px -= x1;
            x1 = 0;
        }

        cp = (320 * y1) + x1;

        if (diffuse) {
            while (x1 <= x2) {
                if (px * px + py * py < rs) {
                    uint8_t colors[4], colormasks[4];

                    colors[0] = target[cp];
                    colors[1] = target[cp + 1];
                    colors[2] = target[cp + 320];
                    colors[3] = target[cp + 321];

                    memcpy(colormasks, colors, 4 * sizeof(uint8_t));
                    for (unsigned char &colormask : colormasks) {
                        colormask &= 0xC0u;
                    }

                    for (unsigned char &color : colors) {
                        color &= 0x3Fu;
                    }

                    colors[0] += colors[2];
                    colors[1] += colors[3];
                    colors[0] += colors[1];

                    colors[0] >>= 2u;

                    colors[1] = colors[0];
                    colors[2] = colors[0];
                    colors[3] = colors[1];

                    for (uint16_t i = 0; i < 4; i++) {
                        colors[i] |= colormasks[i];
                    }

                    target[cp]       = colors[0];
                    target[cp + 1]   = colors[1];
                    target[cp + 320] = colors[2];
                    target[cp + 321] = colors[3];
                }
                cp++;
                px++;
                x1++;
            }
        } else {
            while (x1 <= x2) {
                if (px * px + py * py < rs) {
                    uint8_t colors[4];

                    colors[0] = target[cp];
                    colors[1] = target[cp + 1];
                    colors[2] = target[cp + 320];
                    colors[3] = target[cp + 321];

                    uint8_t temp = colors[0];
                    temp &= 0xC0u;

                    for (unsigned char &color : colors) {
                        color &= 0x3Fu;
                    }

                    colors[0] += colors[2];
                    colors[1] += colors[3];
                    colors[0] += colors[1];

                    colors[0] >>= 2u;
                    colors[0] |= temp;

                    target[cp] = colors[0];
                }

                cp++;
                px++;
                x1++;
            }
        }

        py++;
        y1++;
    }
}

// Using 64 levels in 4 shades, bring the screen to a single gradient.
void mask_pixels(uint8_t *target, uint8_t mask) {
    uint8_t cap = 0x3F;

    // If QUADWORDS is not cast to a long here it overflows and the loop hangs.
    for (uint32_t i = 0; i < ((uint32_t) QUADWORDS) * 4; i++) {
        uint8_t color = target[i];
        color &= cap;
        color += mask;
        target[i] = color;
    }
}

// HSP Inclusions.

#include "tdpolygs.h" // 3D Engine.

// Support files

const char *situation_file = "data/current.bin";
const char *starmap_file   = "data/STARMAP.BIN";
const char *goesoutputfile = "data/GOESfile.txt";
const char *surface_file   = "data/surface.bin";
int16_t sfh; // Surface situation file handle.

// Global variables that are saved.

int8_t nsync                          = 1;         // 0
int8_t anti_rad                       = 1;         // 1
int8_t pl_search                      = 0;         // 2
int8_t field_amplificator             = 0;         // 3
int8_t ilight                         = 63;        // 4
int8_t ilightv                        = 1;         // 5
int8_t charge                         = 120;       // 6
int8_t revcontrols                    = 0;         // 7
int8_t ap_targetting                  = 0;         // 8
int8_t ap_targetted                   = 0;         // 9
int8_t ip_targetting                  = 0;         // 10
int8_t ip_targetted                   = -1;        // 11
int8_t ip_reaching                    = 0;         // 12
int8_t ip_reached                     = 0;         // 13
int8_t ap_target_spin                 = 0;         // 14
int8_t ap_target_r                    = 0;         // 15
int8_t ap_target_g                    = 0;         // 16
int8_t ap_target_b                    = 0;         // 17
int8_t nearstar_spin                  = 0;         // 18
int8_t nearstar_r                     = 0;         // 19
int8_t nearstar_g                     = 0;         // 20
int8_t nearstar_b                     = 0;         // 21
int8_t gburst                         = 0;         // 22
int8_t menusalwayson                  = 1;         // 23
int8_t depolarize                     = 0;         // 24
int16_t sys                           = 4;         // 25
int16_t pwr                           = 20000;     // 27
int16_t dev_page                      = 0;         // 29
int16_t ap_target_class               = 0;         // 31
int16_t f_ray_elapsed                 = 0;         // 33
int16_t nearstar_class                = 0;         // 35
int16_t nearstar_nop                  = 0;         // 37
float pos_x                           = 0;         // 39
float pos_y                           = 0;         // 43
float pos_z                           = -500;      // 47
float user_alfa                       = 0;         // 51
float user_beta                       = 0;         // 55
float navigation_beta                 = 0;         // 59
float ap_target_ray                   = 1000;      // 63
float nearstar_ray                    = 1000;      // 67
double dzat_x                         = +3797120;  // 71
double dzat_y                         = -4352112;  // 79
double dzat_z                         = -925018;   // 87
double ap_target_x                    = 0;         // 95
double ap_target_y                    = 1E8;       // 103
double ap_target_z                    = 0;         // 111
double nearstar_x                     = 0;         // 119
double nearstar_y                     = 1E8;       // 127
double nearstar_z                     = 0;         // 135
double helptime                       = 0;         // 143
double ip_target_initial_d            = 1E8;       // 151
double requested_approach_coefficient = 1;         // 159
double current_approach_coefficient   = 1;         // 167
double reaction_time                  = 0.01;      // 175
int8_t fcs_status[11]                 = "STANDBY"; // 183
int16_t fcs_status_delay              = 0;         // 194
int16_t psys                          = 4;         // 196
double ap_target_initial_d            = 1E8;       // 198
double requested_vimana_coefficient   = 1;         // 206
double current_vimana_coefficient     = 1;         // 214
double vimana_reaction_time           = 0.01;      // 222
int8_t lithium_collector              = 0;         // 230
int8_t autoscreenoff                  = 0;         // 231
int8_t ap_reached                     = 0;         // 232
int16_t lifter                        = 0;         // 233
double secs                           = 0;         // 235
int8_t data                           = 0;         // 243
int8_t surlight                       = 16;        // 244

// Surface landing control data.

int8_t land_now        = 0;
int8_t landing_point   = 0;
int16_t landing_pt_lon = 0;
int16_t landing_pt_lat = 60;

int16_t crepzone;
int16_t nightzone;
int16_t sun_x_factor;

// Global data that isn't saved.
int16_t epoc = 6011;

int8_t ctb[512];
char dec[20];

int8_t _delay     = 12;
int8_t stspeed    = 0;
int8_t elight     = 0;
uint16_t gl_start = 0;
uint16_t point;
uint16_t vptr;
int16_t infoarea  = 0;
int16_t s_control = 1;
int16_t s_command = 0;
int16_t isecs, p_isecs;
double fsecs;
int16_t gl_fps     = 1;
int16_t fps        = 1;
float dlt_alfa     = 0;
float dlt_beta     = 0;
float dlt_nav_beta = 0;
float step         = 0;
float shift        = 0;
double s_m         = 1000;
double plx, ply, plz;
double pxx, pyy;
double delta_x, delta_y;
double nearstar_identity;
int16_t nearstar_labeled;
int16_t nearstar_nob = 0;
int16_t npcs, resident_map1, resident_map2;
int8_t ontheroof;
int16_t datasheetscroll = 0;
int16_t datasheetdelta  = 0;

// Constant data in the global segment.

// Some ordinals (from 0 to 20) for certain representations.
const char *ord[21] = {"zeroth",    "first",       "second",     "third",
                       "fourth",    "fifth",       "sixth",      "seventh",
                       "eight",     "nineth",      "tenth",      "eleventh",
                       "twelveth",  "thiteenth",   "fourteenth", "fifteenth",
                       "sixteenth", "seventeenth", "eighteenth", "nineteenth",
                       "twentyth"};

const char *star_description[star_classes] = {
    "medium size, yellow star, suitable for planets having indigenous "
    "lifeforms.",
    "very large, blue giant star, high energy radiations around.",
    "white dwarf star, possible harmful radiations.",
    "very large, ancient, red giant star.",
    "large and glowing, orange giant star, high nuclear mass.",
    "small, weak, cold, brown dwarf substellar object.",
    "large, very weak, very cold, gray giant dead star.",
    "very small, blue dwarf star, strong gravity well around.",
    "possible MULTIPLE system - planets spread over wide ranges.",
    "medium size, surrounded by gas clouds, young star.",
    "very large and ancient runaway star, unsuitable for planets.",
    "tiny pulsar object, unsafe, high radiation, strong gravity."};

int8_t class_rgb[3 * star_classes] = {
    63, 58, 40, 30, 50, 63, 63, 63, 63, 63, 30, 20, 63, 55, 32, 32, 16, 10,
    32, 28, 24, 10, 20, 63, 63, 32, 16, 48, 32, 63, 40, 10, 10, 00, 63, 63};

int16_t class_ray[star_classes] = {5000, 15000, 300,  20000, 15000, 1000,
                                   3000, 2000,  4000, 1500,  30000, 250};

int16_t class_rayvar[star_classes] = {2000, 10000, 200,  15000, 5000, 1000,
                                      3000, 500,   5000, 10000, 1000, 10};

int8_t class_planets[star_classes] = {12, 18, 8, 15, 20, 3, 0, 1, 7, 20, 2, 5};

int8_t nearstar_p_type[maxbodies];
int16_t nearstar_p_owner[maxbodies];
int8_t nearstar_p_moonid[maxbodies];
double nearstar_p_ring[maxbodies];
double nearstar_p_tilt[maxbodies];
double nearstar_p_ray[maxbodies];
double nearstar_p_orb_ray[maxbodies];
double nearstar_p_orb_seed[maxbodies];
double nearstar_p_orb_tilt[maxbodies];
double nearstar_p_orb_orient[maxbodies];
double nearstar_p_orb_ecc[maxbodies];

int16_t nearstar_p_rtperiod[maxbodies];
int16_t nearstar_p_rotation[maxbodies];
int16_t nearstar_p_term_start[maxbodies];
int16_t nearstar_p_term_end[maxbodies];

int16_t nearstar_p_qsortindex[maxbodies];
float nearstar_p_qsortdist[maxbodies];

const char *planet_description[] = {
    "medium size, internally hot, unstable surface, no atmosphere.",
    "small, solid, dusty, craterized, no atmosphere.",
    "medium size, solid, thick atmosphere, fully covered by clouds.",
    "medium size, felisian, breathable atmosphere, suitable for life.",
    "medium size, rocky, creased, no atmosphere.",
    "small, solid, thin atmosphere.",
    "large, not consistent, covered with dense clouds.",
    "small, solid, icy surface, no atmosphere.",
    "medium size, surface is mainly native quartz, oxygen atmosphere.",
    "very large, substellar object, not consistent.",
    "companion star - not a planet"};

uint8_t planet_rgb_and_var[] = {60, 30, 15, 20, 40, 50, 40, 25, 32, 32, 32,
                                32, 16, 32, 48, 40, 32, 40, 32, 20, 32, 32,
                                32, 32, 32, 32, 32, 32, 32, 40, 48, 24, 40,
                                40, 40, 30, 50, 25, 10, 20, 40, 40, 40, 40};

int16_t planet_possiblemoons[] = {1, 1, 2, 3, 2, 2, 18, 2, 3, 20, 20};

const double planet_orb_scaling = 5.0;
const double avg_planet_sizing  = 2.4;
const double moon_orb_scaling   = 12.8;
const double avg_moon_sizing    = 1.8;

double avg_planet_ray[] = {0.007, 0.003, 0.010, 0.011, 0.010, 0.008,
                           0.064, 0.009, 0.012, 0.125, 5.000};

float mindiff = 0.01;

// Physical and logical video matrices, cartography, and other memory blocks.

uint8_t *s_background;
uint8_t *p_background;
uint8_t *p_surfacemap;
quadrant *objectschart;
uint8_t *ruinschart; // As objectschart, but declared in bytes.
uint8_t *pvfile;
uint8_t *n_offsets_map;
int8_t *n_globes_map;

// Planetary surface adjustment data.

int8_t sky_red_filter = 63; // Filters for the sky.
int8_t sky_grn_filter = 63;
int8_t sky_blu_filter = 63;
int8_t gnd_red_filter = 63; // Filters for the ground.
int8_t gnd_grn_filter = 63;
int8_t gnd_blu_filter = 63;

float planet_grav = 150; // Corresponds to the planetary gravity.
float rainy       = 0;   // Raininess, based on cloud albedo. [0,5]
int16_t albedo    = 0;   // Albedo average of the landing surface. [0,62]

uint8_t sky_brightness = 32; // Sky luminosity. [0,48]

uint16_t m200[200]; // Numbers from 0 to 199, multipled by 200 (Lookup table)

float rwp     = 15; // Required wind power (in knots).
float iwp     = 0;  // Ideal wind power (from 0 to 1).
float wp      = 0;  // Current wind power.
float wdir    = 0;  // Wind origin direction.
float wdirsin = 0;  // Optimization value.
float wdircos = 1;  // Optimization value.

int8_t landed; // Flag set at the time of landing.
// Coded position quotiento of the lander (quotient:remainder).
int32_t atl_x, atl_z, atl_x2, atl_z2;

double qid = 1.0 / 16384; // Constant to find the x / z id of a quadrant.

// Polygonal graphics area (characters, ships, labels, etc...)

#define handles 16 // 16 handles in this case.

uint32_t pvfile_datatop = 0; // Top of the data.

// Note: dataptr is a relative pointer that can go from 0 to "pvbytes".
uint16_t pvfile_dataptr[handles] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};
uint16_t pvfile_datalen[handles] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};
uint16_t pvfile_npolygs[handles] = {0, 0, 0, 0, 0, 0, 0, 0,
                                    0, 0, 0, 0, 0, 0, 0, 0};

int8_t *pv_n_vtx[handles]; // Number of vertices for each polygon (3 or 4).
float *pvfile_x[handles];  // X coordinate (four vertices) of each polygon.
float *pvfile_y[handles];  // Y coordinate (four vertices) of each polygon.
float *pvfile_z[handles];  // Z coordinate (four vertices) of each polygon.
int8_t *pvfile_c[handles]; // Intensity of the color of each polygon (0 to 63).
float *pv_mid_x[handles];  // X coordinate of the midpoint of each polygon.
float *pv_mid_y[handles];  // Y coordinate of the midpoint of each polygon.
float *pv_mid_z[handles];  // Z coordinate of the midpoint of each polygon.
float
    *pv_mid_d[handles]; // Buffer distance of average points from the observer.
int16_t *pv_dep_i[handles]; // Distance index (sorting of polygons).

// Pseudo-random number generation procedures.

int32_t flat_rnd_seed;

// Pseudo table selection.
// There are 4,294,967,295 possible tables, and about 20000 elements per table.
void fast_srand(int32_t seed) { flat_rnd_seed = ((uint32_t) seed) | 0x03u; }

// Extraction of a number: "mask" activates the bits.
// This is very sketchy!
int32_t fast_random(int32_t mask) {
    uint32_t eax = flat_rnd_seed;
    uint32_t edx = flat_rnd_seed;

    uint64_t result = ((uint64_t) eax) * ((uint64_t) edx);
    eax             = (result & 0xFFFFFFFFu);
    edx             = ((result >> 32u) & 0xFFFFFFFFu);
    uint8_t al      = (eax & 0xFFu);
    uint8_t dl      = (edx & 0xFFu);
    al += dl;
    eax = (eax & 0xFFFFFF00u) | al;
    flat_rnd_seed += eax;

    int32_t num = eax & ((uint32_t)(mask));
    return num;
}

int16_t ranged_fast_random(int16_t range) {
    if (range <= 0) {
        range = 1;
    }

    return (fast_random(0x7FFF) % range);
}

float flandom() { return ((float) brtl_random(32767) * 0.000030518); }

float fast_flandom() { return ((float) fast_random(32767) * 0.000030518); }

// Loads virtual file handles from supports.nct
FILE *sa_open(int32_t offset_of_virtual_file) {
    FILE* fh = fopen("res/supports.nct", "r");

    if (fh == nullptr) {
        return nullptr;
    }

    if (fseek(fh, offset_of_virtual_file, SEEK_END) > -1) {
        return fh;
    } else {
        fclose(fh);
        return nullptr;
    }
}

// Defines a part of the color table so that a gradual gradient goes from one
// color to another, within a certain number of intermediate colors.
void shade(uint8_t *palette_buffer, int16_t first_color,
           int16_t number_of_colors, float start_r, float start_g,
           float start_b, float finish_r, float finish_g, float finish_b) {
    int16_t count = number_of_colors;
    float k       = 1.00 / (float) number_of_colors;
    float delta_r = (finish_r - start_r) * k;
    float delta_g = (finish_g - start_g) * k;
    float delta_b = (finish_b - start_b) * k;
    first_color *= 3;

    while (count) {
        if (start_r >= 0 && start_r < 64) {
            palette_buffer[first_color + 0] = (uint8_t) start_r;
        } else {
            if (start_r > 0) {
                palette_buffer[first_color + 0] = 63;
            } else {
                palette_buffer[first_color + 0] = 00;
            }
        }

        if (start_g >= 0 && start_g < 64) {
            palette_buffer[first_color + 1] = (uint8_t) start_g;
        } else {
            if (start_g > 0) {
                palette_buffer[first_color + 1] = 63;
            } else {
                palette_buffer[first_color + 1] = 00;
            }
        }

        if (start_b >= 0 && start_b < 64) {
            palette_buffer[first_color + 2] = (uint8_t) start_b;
        } else {
            if (start_b > 0) {
                palette_buffer[first_color + 2] = 63;
            } else {
                palette_buffer[first_color + 2] = 00;
            }
        }

        start_r += delta_r;
        start_g += delta_g;
        start_b += delta_b;

        first_color += 3;
        count--;
    }
}

// Display control

// Sets the 3d projection from a still viewpoint.
void from_vehicle() {
    cam_x = dzat_x;
    cam_y = dzat_y;
    cam_z = dzat_z;
    alfa  = user_alfa;
    beta  = user_beta + navigation_beta + 180;

    if (beta >= 360) {
        beta -= 360;
    }

    change_angle_of_view();
}

// Sets the 3d projection from the user's point of view.
void from_user() {
    cam_x = pos_x;
    cam_y = pos_y;
    cam_z = pos_z;
    alfa  = user_alfa;
    beta  = user_beta;
    change_angle_of_view();
}

// Orients the virtual video camera to a certain point given by see_x;y;z,
// fractalizing the lap corner to do it more quickly.
void watch(double cam_x, double cam_y, double cam_z, double see_x, double see_y,
           double see_z) {
    double rx, ry, rz, w, ww, k, q, f1, f2, f3;
    double sinbeta, cosbeta, cosalfa;
    rx = cam_x - see_x;
    ry = cam_y - see_y;
    rz = cam_z - see_z;
    w  = sqrt(rx * rx + ry * ry + rz * rz);
    see_x -= cam_x;
    see_y -= cam_y;
    see_z -= cam_z;
    f1 = 0;
    f2 = 0;
    f3 = 2 * M_PI;

    while (f3 > 0.02) {
        q       = 1e+111;
        ww      = f3 / 10;
        sinbeta = sin(beta);
        cosbeta = cos(beta);

        for (alfa = f2 - f3; alfa < f2 + f3; alfa += ww) {
            rx = -w * sinbeta * cos(alfa) - see_x;
            ry = +w * sin(alfa) - see_y;
            rz = +w * cosbeta * cos(alfa) - see_z;
            k  = rx * rx + ry * ry + rz * rz;

            if (k < q) {
                q  = k;
                f2 = alfa;
            }
        }

        alfa = f2;
        ry   = w * sin(alfa) - see_y;
        ry *= ry;
        cosalfa = cos(alfa);
        q       = 1e+111;
        ww      = f3 / 10;

        for (beta = f1 - f3; beta < f1 + f3; beta += ww) {
            rx = -w * sin(beta) * cosalfa - see_x;
            rz = +w * cos(beta) * cosalfa - see_z;
            k  = rx * rx + ry + rz * rz;

            if (k < q) {
                q  = k;
                f1 = beta;
            }
        }

        beta = f1;
        f3 /= 5;
    }

    alfa /= deg;
    beta /= deg;
}

// Calculates the x-y offset from the center of the display by the point given
// by point_x;y;z, returns the values in delta_x;y.
int8_t xy(double cam_x, double cam_y, double cam_z, double point_x,
          double point_y, double point_z) {
    double xx, yy, zz, z2, rz;
    xx      = point_x - cam_x;
    yy      = point_y - cam_y;
    zz      = point_z - cam_z;
    delta_x = xx * opt_pcosbeta + zz * opt_psinbeta;
    z2      = zz * opt_tcosbeta - xx * opt_tsinbeta;
    rz      = z2 * opt_tcosalfa + yy * opt_tsinalfa;
    delta_y = yy * opt_pcosalfa - z2 * opt_psinalfa;

    if (rz > 0.001) {
        delta_x /= rz;
        delta_y /= rz;
        return (1);
    }

    return (0);
}

// Move the user around inside the stardrifter.
void p_forward(float delta) {
    pos_x -= delta * opt_tsinbeta * opt_tcosalfa;
    pos_z += delta * opt_tcosbeta * opt_tcosalfa;
}

// Calculate the position of a certain planet in orbit around a star (the
// neighbouring one) based on orbital parameters (inclination, eccentricity,
// radius and orientation of major axis), and returns i values in plx, ply, plz.
double mox, moy, moz;
void moonorigin(int16_t n) {
    double xx;
    double p_riv, ors;
    double alfa, beta;
    ors   = nearstar_p_orb_ray[n] * nearstar_p_orb_ray[n];
    p_riv = sqrt(s_m / ors);
    beta  = (secs * p_riv * M_PI) / 180;
    alfa  = nearstar_p_orb_tilt[n] * deg;
    xx    = -nearstar_p_orb_ray[n] * sin(beta) * cos(alfa);
    moz   = nearstar_p_orb_ray[n] * cos(beta) * cos(alfa);
    moy   = nearstar_p_orb_ray[n] * sin(alfa);
    moz *= nearstar_p_orb_ecc[n];
    beta = nearstar_p_orb_orient[n];
    mox  = xx * cos(beta) + moz * sin(beta);
    moz  = moz * cos(beta) - xx * sin(beta);
}

void planet_xyz(int16_t n) {
    double xx;
    double alfa, beta;
    double p_m, p_riv, ors;
    ors = nearstar_p_orb_ray[n] * nearstar_p_orb_ray[n];

    if (nearstar_p_owner[n] > -1) {
        xx    = nearstar_p_ray[nearstar_p_owner[n]];
        p_m   = qt_M_PI * xx * xx * xx * 0.44e-4;
        p_riv = sqrt(p_m / ors);
    } else {
        p_riv = sqrt(s_m / ors);
    }

    beta = (secs * p_riv * M_PI) / 180;
    alfa = nearstar_p_orb_tilt[n] * deg;
    xx   = -nearstar_p_orb_ray[n] * sin(beta) * cos(alfa);
    plz  = nearstar_p_orb_ray[n] * cos(beta) * cos(alfa);
    ply  = nearstar_p_orb_ray[n] * sin(alfa);
    plz *= nearstar_p_orb_ecc[n];
    beta = nearstar_p_orb_orient[n];
    plx  = xx * cos(beta) + plz * sin(beta);
    plz  = plz * cos(beta) - xx * sin(beta);
    plx += nearstar_x;
    ply += nearstar_y;
    plz += nearstar_z;

    if (nearstar_p_owner[n] > -1) {
        moonorigin(nearstar_p_owner[n]);
        plx += mox;
        ply += moy;
        plz += moz;
    }
}

// Calculate the revolution period of a body, in seconds.
// For planets: Around the star.
// For moons: Around the planet.
// .01e-7 is the equivalent, in the virtual cosmos of Noctis.
float rtp(int16_t n) {
    double p_m, p_riv, ors, xx;
    ors = nearstar_p_orb_ray[n] * nearstar_p_orb_ray[n];

    if (nearstar_p_owner[n] > -1) {
        xx    = nearstar_p_ray[nearstar_p_owner[n]];
        p_m   = qt_M_PI * xx * xx * xx * 0.44e-4;
        p_riv = sqrt(p_m / ors);
    } else {
        p_riv = sqrt(s_m / ors);
    }

    return (360 / p_riv);
}

// Calculates the longitude of the point on a planet that the user is looking
// at, given by (plx, ply, plz). The observed is placed at (obs_x, obs_z),
// its y is irrelevant.
int16_t planet_viewpoint(double obs_x, double obs_z) {
    uint16_t a;
    int16_t plwp = 0;
    double xx;
    double zz;
    double min = 1E99;

    for (a = 0; a < 360; a++) {
        xx = plx + cos(deg * (double) a) - obs_x;
        zz = plz + sin(deg * (double) a) - obs_z;
        xx = xx * xx + zz * zz;

        if (xx < min) {
            plwp = a;
            min  = xx;
        }
    }

    return (plwp);
}

int16_t cplx_planet_viewpoint(int16_t logical_id) {
    int16_t owner;
    double ownerplx;
    double ownerplz;

    if (nearstar_p_owner[logical_id] == -1) {
        return (planet_viewpoint(nearstar_x, nearstar_z));
    }

    owner = nearstar_p_owner[logical_id];

    if (nearstar_p_type[owner] == 10) {
        planet_xyz(owner);
        ownerplx = plx;
        ownerplz = plz;
        planet_xyz(logical_id);
        return (planet_viewpoint(ownerplx, ownerplz));
    } else {
        return (planet_viewpoint(nearstar_x, nearstar_z));
    }
}

// Effect selection via "flares" control variable.

int8_t previous_flares_value = 0;
void setfx(int8_t fx) {
    previous_flares_value = flares;
    flares                = fx;
}

void chgfx(int8_t fx) { flares = fx; }

void resetfx() { flares = previous_flares_value; }

// Tracing sticks (2D).
void stick(uint32_t xp, uint32_t yp, uint32_t xa, uint32_t ya) {
    int32_t a, b, L;
    uint16_t pi, pf;
    uint16_t offset = 0;

    if (xp == xa) {
        if (ya >= yp) {
            pi = 320 * yp + xp;
            pf = 320 * (ya + 1);
        } else {
            pi = 320 * ya + xp;
            pf = 320 * (yp + 1);
        }

        pi += offset;
        pf += offset;

        offset = pi;

        switch (flares) {
        case 0:
            while (offset < pf) {
                adapted[offset]     = 0x3E;
                adapted[offset + 1] = 0x00;

                offset += 320;
            }
            break;
        case 1:
            while (offset < pf) {
                uint8_t mask = adapted[offset];
                mask &= 0x3Fu;
                mask += 0x08;

                adapted[offset] &= 0xC0u;

                if (mask > 0x3E) {
                    mask = 0x3E;
                }

                adapted[offset] += mask;
                offset += 320;
            }
            break;
        case 2:
            while (offset < pf) {
                uint8_t mask = adapted[offset];
                mask &= 0x3Fu;
                mask >>= 1u;

                adapted[offset] &= 0xC0u;

                adapted[offset] += mask;
                offset += 320;
            }
            break;
        case 3:
            while (offset < pf) {
                adapted[offset]     = 0x2E;
                adapted[offset + 1] = 0x1E;
                adapted[offset + 2] = 0x13;
                adapted[offset + 3] = 0x0E;
                offset += 320;
            }
            break;
        default:
            break;
        }
        return;
    }

    uint32_t xaTemp = xa - xp;
    if (xa < xp) {
        uint32_t swap;

        swap = xp;
        xp   = xa;
        xa   = swap;

        swap = yp;
        yp   = ya;
        ya   = swap;

        xaTemp = ~xaTemp + 1;
    }
    a = xaTemp;
    L = xaTemp;

    uint32_t yaTemp = ya - yp;
    bool negateB    = false;
    if (ya < yp) {
        negateB = true;
        yaTemp  = ~yaTemp + 1;
    }

    b = yaTemp;

    if (yaTemp > (uint32_t) L) {
        L = yaTemp;
    }
    L++;

    xa <<= 16u;

    uint32_t global_x = xp << 16u;
    uint32_t global_y = yp << 16u;

    a <<= 16;
    a /= L;
    a &= 0xFFFF;

    b <<= 16;
    b /= L;
    b &= 0xFFFF;

    if (negateB) {
        b = -b;
    }

    switch (flares) {
    case 0: // Solid sticks that "reflect" light;
        while (global_x < xa) {
            uint16_t tempB = (global_y >> 16u);
            uint32_t index = global_x >> 16u;

            global_x += a;
            global_y += b;

            index += 320 * tempB;

            adapted[index]     = 0x00;
            adapted[index + 1] = 0x3E;
        }
        break;
    case 1: // Intrinsically luminous sticks.
        while (global_x < xa) {
            uint16_t tempB = (global_y >> 16u);
            uint32_t index = global_x >> 16u;

            global_x += a * 2;
            global_y += b * 2;

            index += 320 * tempB;

            uint16_t color = adapted[index] << 2u;

            if ((color & 0xFFu) <= 0xDF) {
                color += 32;
            } else {
                color = (color & 0xFF00u) + 0xFB;
            }

            adapted[index] = (color >> 2u) & 0xFFu;
        }
        break;
    case 2: // Sticks that absorb light ("smoked")
        while (global_x < xa) {
            uint16_t tempB = (global_y >> 16u);
            uint32_t index = global_x >> 16u;

            global_x += a;
            global_y += b;

            index += 320 * tempB;

            uint16_t color = adapted[index];

            color &= 0x3Fu;
            adapted[index] &= 0xC0u;

            color >>= 1u;
            adapted[index] += color;
        }

        break;

    case 3: // Same as type 0, but wider.
        while (global_x < xa) {
            uint16_t tempB = (global_y >> 16u);
            uint32_t index = global_x >> 16u;

            global_x += a;
            global_y += b;

            index += 320 * tempB;

            adapted[index]     = 0xCE;
            adapted[index + 1] = 0xD3;
            adapted[index + 2] = 0xDE;
            adapted[index + 3] = 0xEE;
        }
    default:
        break;
    }
}

/* Tracing sticks (3D Part). */

int32_t fpx = -1; // First-point-x
int32_t fpy;      // First-point-y

float p_rx, p_ry, p_rz;
float stick_uneg = 200;

void stick3d(float p_x, float p_y, float p_z, float x, float y, float z) {
    int32_t lx, ly;
    float p_z2, diff;
    float rx, ry, rz, z2, kk;
    fpx = -1;

    p_x -= cam_x;
    p_y -= cam_y;
    p_z -= cam_z;
    p_z2 = (p_z * opt_tcosbeta) - (p_x * opt_tsinbeta);
    p_rz = (p_z2 * opt_tcosalfa) + (p_y * opt_tsinalfa);

    x -= cam_x;
    y -= cam_y;
    z -= cam_z;
    z2 = (z * opt_tcosbeta) - (x * opt_tsinbeta);
    rz = (z2 * opt_tcosalfa) + (y * opt_tsinalfa);

    if (rz < stick_uneg && p_rz < stick_uneg) {
        return;
    }

    p_rx = (p_x * opt_pcosbeta) + (p_z * opt_psinbeta);
    p_ry = (p_y * opt_pcosalfa) - (p_z2 * opt_psinalfa);

    rx = (x * opt_pcosbeta) + (z * opt_psinbeta);
    ry = (y * opt_pcosalfa) - (z2 * opt_psinalfa);

    // Conversion of points behind the observer with respect to the screen
    // plane.

    if (rz < stick_uneg) {
        diff = rz - p_rz;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stick_uneg - p_rz) / diff;
            rx = kk * (rx - p_rx) + p_rx;
            ry = kk * (ry - p_ry) + p_ry;
        }

        rz = stick_uneg;
    } else {
        if (p_rz < stick_uneg) {
            diff = p_rz - rz;

            if (diff < -mindiff || diff > mindiff) {
                kk   = (stick_uneg - rz) / diff;
                p_rx = kk * (p_rx - rx) + rx;
                p_ry = kk * (p_ry - ry) + ry;
            }

            p_rz = stick_uneg;
        }
    }

    // Perspective.
    lx = (int32_t)(rx / rz);
    ly = (int32_t)(ry / rz);

    fpx = (int32_t)(p_rx / p_rz);
    fpy = (int32_t)(p_ry / p_rz);

    if (fpy < stk_lby && ly < stk_lby) {
        return; // Out-of-range lines.
    }

    if (fpy > stk_uby && ly > stk_uby) {
        return;
    }

    if (fpx < stk_lbx && lx < stk_lbx) {
        return;
    }

    if (fpx > stk_ubx && lx > stk_ubx) {
        return;
    }

    /*
        Optimize segment tracking by cutting away parts that cannot be seen.
        This part is not effective if the departure and arrival points make it
        so that the segment does not intersect any side of the visible area:
        but in this pecular case the lines are excluded by pregvious checks.
    */

    if (fpx < stk_lbx) {
        diff = fpx - lx;

        if (diff < -mindiff || diff > mindiff) {
            kk  = (stk_lbx - lx) / diff;
            fpy = (int32_t)(kk * (fpy - ly) + ly);
            fpx = stk_lbx;
        }
    }

    if (lx < stk_lbx) {
        diff = lx - fpx;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_lbx - fpx) / diff;
            ly = (int32_t)(kk * (ly - fpy) + fpy);
            lx = stk_lbx;
        }
    }

    if (fpy < stk_lby) {
        diff = fpy - ly;

        if (diff < -mindiff || diff > mindiff) {
            kk  = (stk_lby - ly) / diff;
            fpx = (int32_t)(kk * (fpx - lx) + lx);
            fpy = stk_lby;
        }
    }

    if (ly < stk_lby) {
        diff = ly - fpy;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_lby - fpy) / diff;
            lx = (int32_t)(kk * (lx - fpx) + fpx);
            ly = stk_lby;
        }
    }

    if (fpx > stk_ubx) {
        diff = fpx - lx;

        if (diff < -mindiff || diff > mindiff) {
            kk  = (stk_ubx - lx) / diff;
            fpy = (int32_t)(kk * (fpy - ly) + ly);
            fpx = stk_ubx;
        }
    }

    if (lx > stk_ubx) {
        diff = lx - fpx;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_ubx - fpx) / diff;
            ly = (int32_t)(kk * (ly - fpy) + fpy);
            lx = stk_ubx;
        }
    }

    if (fpy > stk_uby) {
        diff = fpy - ly;

        if (diff < -mindiff || diff > mindiff) {
            kk  = (stk_uby - ly) / diff;
            fpx = (int32_t)(kk * (fpx - lx) + lx);
            fpy = stk_uby;
        }
    }

    if (ly > stk_uby) {
        diff = ly - fpy;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_uby - fpy) / diff;
            lx = (int32_t)(kk * (lx - fpx) + fpx);
            ly = stk_uby;
        }
    }

    if (fpx == lx && fpy == ly) {
        return; // Excludes lines consisting of a single point.
    }

    stick(fpx + VIEW_X_CENTER, fpy + VIEW_Y_CENTER, lx + VIEW_X_CENTER,
          ly + VIEW_Y_CENTER);
}

// Tracing luminous sticks (in 2d, for the glows, generally used with the
// flares flag = 1).

void fline(int32_t fx, int32_t fy, int32_t lx, int32_t ly) {
    float kk, diff;

    /*
        Optimize the tracking of the "Segment", cutting away the parts that
        definitely cannot be seen. This part is not effective if the points of
        departure and arrival make the segment not intersect any side of the
        visible area: but in this peculiar case, the lines are excluded from
        subsequent checks.
    */

    if (fx < stk_lbx) {
        diff = fx - lx;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_lbx - lx) / diff;
            fy = (int32_t)(kk * (fy - ly) + ly);
            fx = stk_lbx;
        }
    }

    if (lx < stk_lbx) {
        diff = lx - fx;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_lbx - fx) / diff;
            ly = (int32_t)(kk * (ly - fy) + fy);
            lx = stk_lbx;
        }
    }

    if (fy < stk_lby) {
        diff = fy - ly;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_lby - ly) / diff;
            fx = (int32_t)(kk * (fx - lx) + lx);
            fy = stk_lby;
        }
    }

    if (ly < stk_lby) {
        diff = ly - fy;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_lby - fy) / diff;
            lx = (int32_t)(kk * (lx - fx) + fx);
            ly = stk_lby;
        }
    }

    if (fx > stk_ubx) {
        diff = fx - lx;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_ubx - lx) / diff;
            fy = (int32_t)(kk * (fy - ly) + ly);
            fx = stk_ubx;
        }
    }

    if (lx > stk_ubx) {
        diff = lx - fx;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_ubx - fx) / diff;
            ly = (int32_t)(kk * (ly - fy) + fy);
            lx = stk_ubx;
        }
    }

    if (fy > stk_uby) {
        diff = fy - ly;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_uby - ly) / diff;
            fx = (int32_t)(kk * (fx - lx) + lx);
            fy = stk_uby;
        }
    }

    if (ly > stk_uby) {
        diff = ly - fy;

        if (diff < -mindiff || diff > mindiff) {
            kk = (stk_uby - fy) / diff;
            lx = (int32_t)(kk * (lx - fx) + fx);
            ly = stk_uby;
        }
    }

    if (fx == lx && fy == ly) {
        return; // Exclude lines consisting of a single point.
    }

    if (fy < stk_lby || ly < stk_lby) {
        return; // Exclude lines that have been seen before.
    }

    if (fy > stk_uby || ly > stk_uby) {
        return;
    }

    if (fx < stk_lbx || lx < stk_lbx) {
        return;
    }

    if (fx > stk_ubx || lx > stk_ubx) {
        return;
    }

    stick(fx + VIEW_X_CENTER, fy + VIEW_Y_CENTER, lx + VIEW_X_CENTER,
          ly + VIEW_Y_CENTER);
}

/*
    Recursive function that divides triangular polygons into four parts,
    equally triangular, slightly casualizing the color.
*/

uint8_t map_color_a = 30;
uint8_t map_color_b = 31;
uint8_t map_color_c = 32;
uint8_t map_color_d = 33;

void randomic_mapper(float x0, float y0, float z0, float x1, float y1, float z1,
                     float x2, float y2, float z2, int8_t divisions) {
    float vx[3], vy[3], vz[3];
    float e0, f0, g0;
    float e1, f1, g1;
    float e2, f2, g2;
    divisions--;

    if (divisions) {
        e0 = (x0 + x1) * 0.5;
        f0 = (y0 + y1) * 0.5;
        g0 = (z0 + z1) * 0.5;
        e1 = (x1 + x2) * 0.5;
        f1 = (y1 + y2) * 0.5;
        g1 = (z1 + z2) * 0.5;
        e2 = (x0 + x2) * 0.5;
        f2 = (y0 + y2) * 0.5;
        g2 = (z0 + z2) * 0.5;

        if (divisions == 1) {
            vx[0] = x0;
            vy[0] = y0;
            vz[0] = z0;
            vx[1] = e0;
            vy[1] = f0;
            vz[1] = g0;
            vx[2] = e2;
            vy[2] = f2;
            vz[2] = g2;
            poly3d(vx, vy, vz, 3, map_color_a);
            randomic_mapper(x0, y0, z0, e0, f0, g0, e2, f2, g2, divisions);
            vx[0] = e1;
            vy[0] = f1;
            vz[0] = g1;
            poly3d(vx, vy, vz, 3, map_color_b);
            randomic_mapper(e1, f1, g1, e0, f0, g0, e2, f2, g2, divisions);
            vx[1] = x2;
            vy[1] = y2;
            vz[1] = z2;
            poly3d(vx, vy, vz, 3, map_color_c);
            randomic_mapper(e1, f1, g1, x2, y2, z2, e2, f2, g2, divisions);
            vx[2] = x1;
            vy[2] = y1;
            vz[2] = z1;
            vx[1] = e0;
            vy[1] = f0;
            vz[1] = g0;
            poly3d(vx, vy, vz, 3, map_color_d);
            randomic_mapper(e1, f1, g1, e0, f0, g0, x1, y1, z1, divisions);
        } else {
            randomic_mapper(x0, y0, z0, e0, f0, g0, e2, f2, g2, divisions);
            randomic_mapper(e1, f1, g1, e0, f0, g0, e2, f2, g2, divisions);
            randomic_mapper(e1, f1, g1, x2, y2, z2, e2, f2, g2, divisions);
            randomic_mapper(e1, f1, g1, e0, f0, g0, x1, y1, z1, divisions);
        }
    }
}

/*
    Free a handle in which a polygonal graphic file was loaded: if the handle
    is already free nothing happens.
*/

void unloadpv(int16_t handle) {
    int16_t h;
    uint16_t eod;

    if (handle >= handles) {
        return;
    }

    if (!pvfile_datalen[handle]) {
        return;
    }

    /*
        Updates the pointers of all handles which are stored beyond the
        specified one. The type cast is used to convince those ANSI dicks
        that the pointer is moved byte by byte, and not depending on the type
        of data to which it is pointing.
    */
    for (h = 0; h < handles; h++)
        if (pvfile_dataptr[h] > pvfile_dataptr[handle]) {
            ((int8_t *) pv_n_vtx)[h] -= pvfile_datalen[handle];
            ((int8_t *) pvfile_x)[h] -= pvfile_datalen[handle];
            ((int8_t *) pvfile_y)[h] -= pvfile_datalen[handle];
            ((int8_t *) pvfile_z)[h] -= pvfile_datalen[handle];
            ((int8_t *) pvfile_c)[h] -= pvfile_datalen[handle];

            if (pv_mid_x[h]) {
                ((int8_t *) pv_mid_x)[h] -= pvfile_datalen[handle];
                ((int8_t *) pv_mid_y)[h] -= pvfile_datalen[handle];
                ((int8_t *) pv_mid_z)[h] -= pvfile_datalen[handle];
                ((int8_t *) pv_mid_d)[h] -= pvfile_datalen[handle];
                ((int8_t *) pv_dep_i)[h] -= pvfile_datalen[handle];
            }

            pvfile_dataptr[h] -= pvfile_datalen[handle];
        }

    // Move data back to free memory in the polyonal area (if necessary).
    eod = pvfile_dataptr[handle] + pvfile_datalen[handle];

    if (eod < pvfile_datatop) {
        memmove(pv_n_vtx[handle], pv_n_vtx[handle] + pvfile_datalen[handle],
                pvfile_datatop - eod);
    }

    // Update the top of the polygonal area.
    pvfile_datatop -= pvfile_datalen[handle];
    // Update the memory situaton for polygonal graphics, to free the handle.
    pvfile_datalen[handle] = 0;
}

// Free all the handles.
void unloadallpv() {
    int16_t h;
    pvfile_datatop = 0;

    for (h = 0; h < handles; h++) {
        pvfile_datalen[h] = 0;
    }
}

/*
    Load a polygonal model file. If the specified handle is busy, it will be
   freed and reassigned. Parameters: Handle: Number of the database in which to
   host the file, from 0 to 15. virtual_file_position: Negative offset from the
   end of SUPPORTS.NCT. x/y/z_scale: Scale correction of the polygons on all the
   axes. x/y/z_move: Translation of the polygons on all the axes. base_color:
   Basic color of the polygons. depth_sort: Flag that specifies whether to
   allocate space for the calculation of the midpoints of the vertices of each
   polygon and carry out the depth-sorting when the object is to be traced.
    Return:
        -1: The file cannot be accessed.
        0: The hndle is unassignable (does not exist), or there is not enough
        memory in the pvfile buffer to load and / or manage the polygons.
        +1: Everything went well.
*/

int8_t loadpv(int16_t handle, int32_t virtual_file_position, float xscale,
              float yscale, float zscale, float xmove, float ymove, float zmove,
              uint8_t base_color, int8_t depth_sort) {
    int16_t c, p;

    // Check availability of the file and the handle.
    if (handle >= handles) {
        return (0);
    }

    FILE* fh = sa_open(virtual_file_position);

    if (fh == nullptr) {
        return -1;
    }

    // Free the handle if it is currently occupied.
    if (pvfile_datalen[handle]) {
        unloadpv(handle);
    }

    // Internal handle update.
    pvfile_datalen[handle] = 0;
    pvfile_dataptr[handle] = pvfile_datatop;
    // Reading polygon numbers.
    fread(&pvfile_npolygs[handle], 2, 1, fh);
    // Pointer preparation.
    pv_n_vtx[handle] = (int8_t *) (pvfile + pvfile_datatop);
    pvfile_datatop += 1 * pvfile_npolygs[handle];
    pvfile_x[handle] = (float *) (pvfile + pvfile_datatop);
    pvfile_datatop += 16 * pvfile_npolygs[handle];
    pvfile_y[handle] = (float *) (pvfile + pvfile_datatop);
    pvfile_datatop += 16 * pvfile_npolygs[handle];
    pvfile_z[handle] = (float *) (pvfile + pvfile_datatop);
    pvfile_datatop += 16 * pvfile_npolygs[handle];
    pvfile_c[handle] = (int8_t *) (pvfile + pvfile_datatop);
    pvfile_datatop += 1 * pvfile_npolygs[handle];
    /*
        Clear the first data pointer for the depth sort. If it is no
       subsequently modified, then depth sorting is not required for the object
       in question.
    */
    pv_mid_x[handle] = 0;

    // Check availabity before reading the data.
    if (pvfile_datatop > pv_bytes) {
        pvfile_datatop = pvfile_dataptr[handle];
        fclose(fh);
        return (0);
    }

    // Reading all the data on the polygons, in a single block.
    fread(pvfile + pvfile_dataptr[handle], pvfile_datatop - pvfile_dataptr[handle], 1, fh);
    // dopodich� si pu� anche richiudere il file...
    fclose(fh);

    // Resetting unused vertex data (for triangles).
    for (p = 0; p < pvfile_npolygs[handle]; p++)
        if (pv_n_vtx[handle][p] == 3) {
            pvfile_x[handle][4 * p + 3] = 0;
            pvfile_y[handle][4 * p + 3] = 0;
            pvfile_z[handle][4 * p + 3] = 0;
        }

    // Prepare pointers for depth sorting management.
    if (depth_sort) {
        pv_mid_x[handle] = (float *) (pvfile + pvfile_datatop);
        pvfile_datatop += 4 * pvfile_npolygs[handle];
        pv_mid_y[handle] = (float *) (pvfile + pvfile_datatop);
        pvfile_datatop += 4 * pvfile_npolygs[handle];
        pv_mid_z[handle] = (float *) (pvfile + pvfile_datatop);
        pvfile_datatop += 4 * pvfile_npolygs[handle];
        pv_mid_d[handle] = (float *) (pvfile + pvfile_datatop);
        pvfile_datatop += 4 * pvfile_npolygs[handle];
        pv_dep_i[handle] = (int16_t *) (pvfile + pvfile_datatop);
        pvfile_datatop += 2 * pvfile_npolygs[handle];

        // Check available memory for newly added data.
        if (pvfile_datatop > pv_bytes) {
            pvfile_datatop = pvfile_dataptr[handle];
            return (0);
        }
    }

    // Scale, color, and translation adaptation.
    for (c = 0; c < 4 * pvfile_npolygs[handle]; c++) {
        pvfile_x[handle][c] *= xscale;
        pvfile_x[handle][c] += xmove;
        pvfile_y[handle][c] *= yscale;
        pvfile_y[handle][c] += ymove;
        pvfile_z[handle][c] *= zscale;
        pvfile_z[handle][c] += zmove;
        pvfile_c[handle][c] += base_color;
    }

    // Calculation of average points and preparation of depth-sorting indices.
    if (depth_sort) {
        for (p = 0; p < pvfile_npolygs[handle]; p++) {
            pv_dep_i[handle][p] = p;
            pv_mid_d[handle][p] = 0;
            pv_mid_x[handle][p] = 0;
            pv_mid_y[handle][p] = 0;
            pv_mid_z[handle][p] = 0;

            if (pv_n_vtx[handle][p]) {
                for (c = 0; c < pv_n_vtx[handle][p]; c++) {
                    pv_mid_x[handle][p] += pvfile_x[handle][4 * p + c];
                    pv_mid_y[handle][p] += pvfile_y[handle][4 * p + c];
                    pv_mid_z[handle][p] += pvfile_z[handle][4 * p + c];
                }

                pv_mid_x[handle][p] /= c;
                pv_mid_y[handle][p] /= c;
                pv_mid_z[handle][p] /= c;
            }
        }
    }

    // All done: Compute the memory used by this handle.
    pvfile_datalen[handle] = pvfile_datatop - pvfile_dataptr[handle];
    return (1);
}

/*
    Recursive sorting. To order the polygons quickly. It also takes care of
    other sorts by distance, the planets and moons for example.
*/

void quick_sort(int16_t *index, float *mdist, int16_t start, int16_t end) {
    int16_t tq;
    int16_t jq = end;
    int16_t iq = start;
    float xq   = mdist[index[(start + end) / 2]];

    while (iq <= jq) {
        while (mdist[index[iq]] > xq) {
            iq++;
        }

        while (mdist[index[jq]] < xq) {
            jq--;
        }

        if (iq <= jq) {
            tq        = index[iq];
            index[iq] = index[jq];
            index[jq] = tq;
            iq++;
            jq--;
        }
    }

    if (start < jq) {
        quick_sort(index, mdist, start, jq);
    }

    if (iq < end) {
        quick_sort(index, mdist, iq, end);
    }
}

/*
    Traccia una figura poligonale.
    handle: l'handle (da 0 a 15) che si � attribuito al file con "loadpv";
    mode: pu� essere -- 0 = tracciamento poligoni in tinta unita;
                1 = tracciamento con texture mapping;
                2 = rimappatura randomica ricorsiva dei poligoni.
    rm_iterations: viene usato solo se mode = 2, indica quante suddivisioni
            devono essere effettuate per ogni poligono rimappato;
    center_x/y/z: coordinate ove piazzare il centro dell'oggetto;
    use_depth_sort: flag per attivare il depth sort, che viene tuttavia
            effettivamente attivato solo se � stato incluso come
            opzione nella chiamata a "loadpv" per quell'handle.
*/

void drawpv(int16_t handle, int16_t mode, int16_t rm_iterations, float center_x,
            float center_y, float center_z, int8_t use_depth_sort) {
    float dx, dy, dz;
    uint16_t p, c, i, k;

    if (handle >= handles) {
        return;
    }

    if (!pvfile_datalen[handle]) {
        return;
    }

    // traslazione intero spazio all'origine dell'oggetto.
    cam_x -= center_x;
    cam_y -= center_y;
    cam_z -= center_z;

    uint16_t mask;
    if (use_depth_sort && pv_mid_x[handle]) {
        // tracciamento con depth sorting.
        // fase 1: calcolo distanza punti medi.
        for (p = 0; p < pvfile_npolygs[handle]; p++) {
            dx                  = pv_mid_x[handle][p] - cam_x;
            dy                  = pv_mid_y[handle][p] - cam_y;
            dz                  = pv_mid_z[handle][p] - cam_z;
            pv_mid_d[handle][p] = dx * dx + dy * dy + dz * dz;
        }

        // fase 2: ordinamento poligoni in base alla distanza.
        quick_sort(pv_dep_i[handle], pv_mid_d[handle], 0,
                   pvfile_npolygs[handle] - 1);

        // fase 3: tracciamento, nell'ordine specificato sopra.
        for (p = 0; p < pvfile_npolygs[handle]; p++) {
            c = pv_dep_i[handle][p];
            i = c * 4;

            switch (mode) {
            case 0:
                poly3d(pvfile_x[handle] + i, pvfile_y[handle] + i,
                       pvfile_z[handle] + i, pv_n_vtx[handle][c],
                       pvfile_c[handle][c]);
                break;

            case 1:
                k = pvfile_c[handle][c];

                mask = k;
                mask &= 0x3Fu;
                k &= 0xC0u;
                mask >>= 1u;
                k |= mask;

                polymap(pvfile_x[handle] + i, pvfile_y[handle] + i,
                        pvfile_z[handle] + i, pv_n_vtx[handle][c], k);
                break;

            case 2:
                map_color_a = pvfile_c[handle][c];
                map_color_b = map_color_a - 2;
                map_color_c = map_color_a - 1;
                map_color_d = map_color_a + 1;
                randomic_mapper(
                    pvfile_x[handle][i + 0], pvfile_y[handle][i + 0],
                    pvfile_z[handle][i + 0], pvfile_x[handle][i + 1],
                    pvfile_y[handle][i + 1], pvfile_z[handle][i + 1],
                    pvfile_x[handle][i + 2], pvfile_y[handle][i + 2],
                    pvfile_z[handle][i + 2], rm_iterations);

                if (pv_n_vtx[handle][p] == 4)
                    randomic_mapper(
                        pvfile_x[handle][i + 2], pvfile_y[handle][i + 2],
                        pvfile_z[handle][i + 2], pvfile_x[handle][i + 3],
                        pvfile_y[handle][i + 3], pvfile_z[handle][i + 3],
                        pvfile_x[handle][i + 0], pvfile_y[handle][i + 0],
                        pvfile_z[handle][i + 0], rm_iterations);
                break;
            default:
                break;
            }
        }
    } else {
        // tracciamento senza depth sorting.
        // in queso caso traccia i poligoni nell'ordine in cui
        // sono stati salvati nel file di grafica di "PolyVert".
        for (p = 0, i = 0; p < pvfile_npolygs[handle]; p++, i += 4)
            switch (mode) {
            case 0:
                poly3d(pvfile_x[handle] + i, pvfile_y[handle] + i,
                       pvfile_z[handle] + i, pv_n_vtx[handle][p],
                       pvfile_c[handle][p]);
                break;

            case 1:
                k = pvfile_c[handle][p];

                mask = k;
                mask &= 0x3Fu;
                k &= 0xC0u;
                mask >>= 1u;
                k |= mask;

                polymap(pvfile_x[handle] + i, pvfile_y[handle] + i,
                        pvfile_z[handle] + i, pv_n_vtx[handle][p], k);
                break;
            case 2:
                map_color_a = pvfile_c[handle][p];
                map_color_b = map_color_a - 2;
                map_color_c = map_color_a - 1;
                map_color_d = map_color_a + 1;
                randomic_mapper(
                    pvfile_x[handle][i + 0], pvfile_y[handle][i + 0],
                    pvfile_z[handle][i + 0], pvfile_x[handle][i + 1],
                    pvfile_y[handle][i + 1], pvfile_z[handle][i + 1],
                    pvfile_x[handle][i + 2], pvfile_y[handle][i + 2],
                    pvfile_z[handle][i + 2], rm_iterations);

                if (pv_n_vtx[handle][p] == 4)
                    randomic_mapper(
                        pvfile_x[handle][i + 2], pvfile_y[handle][i + 2],
                        pvfile_z[handle][i + 2], pvfile_x[handle][i + 3],
                        pvfile_y[handle][i + 3], pvfile_z[handle][i + 3],
                        pvfile_x[handle][i + 0], pvfile_y[handle][i + 0],
                        pvfile_z[handle][i + 0], rm_iterations);
                break;
            default:
                break;
            }
    }

    // traslazione intero spazio all'origine precedente.
    cam_x += center_x;
    cam_y += center_y;
    cam_z += center_z;
}

/*  Replica una forma poligonale, copiandola da un'handle gi� definito
    a uno di uguali dimensioni. In caso d'errore, non succede nulla. */

void copypv(int16_t dest_handle, int16_t src_handle) {
    if (src_handle >= handles) {
        return;
    }

    if (dest_handle >= handles) {
        return;
    }

    if (!pvfile_datalen[src_handle]) {
        return;
    }

    if (pvfile_datalen[dest_handle] != pvfile_datalen[src_handle]) {
        return;
    }

    memcpy(pv_n_vtx[dest_handle], pv_n_vtx[src_handle],
           pvfile_datalen[src_handle]);
}

/*  Ruota una forma poligonale rispetto a uno dei suoi vertici,
    che viene assunto come centro di rotazione, applicando anche
    un fattore di scalatura (che pu� essere 1 se non � necessario
    cambiare le dimensioni, come possono essere 0 gli angoli se
    si stanno cambiando le dimensioni senza ruotare).
    "vertexs_to_affect" � un puntatore a una serie di strutture "pvlist",
    nelle quali sono elencati i vertici che verranno effettivamente modificati:
    se il puntatore "vertexs_to_affect" � nullo, tutti i vertici lo sono.
    Gli angoli sono espressi in gradi. */

void modpv(int16_t handle, int16_t polygon_id, int16_t vertex_id, float x_scale,
           float y_scale, float z_scale, float x_angle, float y_angle,
           float z_angle, pvlist *vertexs_to_affect) {
    if (handle >= handles) {
        return;
    }

    if (!pvfile_datalen[handle]) {
        return;
    }

    float sin_x = sin(deg * x_angle);
    float cos_x = cos(deg * x_angle);
    float sin_y = sin(deg * y_angle);
    float cos_y = cos(deg * y_angle);
    float sin_z = sin(deg * z_angle);
    float cos_z = cos(deg * z_angle);
    int16_t c, p, v, i, j;
    float x1, y1, z1;
    float cx, cy, cz;

    if (polygon_id > -1 && vertex_id > -1) {
        i  = 4 * polygon_id + vertex_id;
        cx = pvfile_x[handle][i];
        cy = pvfile_y[handle][i];
        cz = pvfile_z[handle][i];
    } else {
        cx = 0;
        cy = 0;
        cz = 0;
    }

    if (!vertexs_to_affect) {
        for (p = 0; p < pvfile_npolygs[handle]; p++) {
            i = 4 * p;

            for (v = 0; v < pv_n_vtx[handle][p]; v++) {
                x1 = (pvfile_x[handle][i] - cx) * cos_y +
                     (pvfile_z[handle][i] - cz) * sin_y;
                z1 = (pvfile_z[handle][i] - cz) * cos_y -
                     (pvfile_x[handle][i] - cx) * sin_y;
                pvfile_z[handle][i] =
                    z_scale *
                        (z1 * cos_x + (pvfile_y[handle][i] - cy) * sin_x) +
                    cz;
                y1 = (pvfile_y[handle][i] - cy) * cos_x - z1 * sin_x;
                pvfile_x[handle][i] = x_scale * (x1 * cos_z + y1 * sin_z) + cx;
                pvfile_y[handle][i] = y_scale * (y1 * cos_z - x1 * sin_z) + cy;
                i++;
            }
        }
    } else {
        p = 0;

        while (vertexs_to_affect[p].polygon_id != 0xFFF) {
            c = vertexs_to_affect[p].polygon_id;
            i = 4 * c;
            v = 0;

            do {
                if (v == 0 && vertexs_to_affect[p].vtxflag_0) {
                    j = i;
                    goto perform;
                }

                if (v == 1 && vertexs_to_affect[p].vtxflag_1) {
                    j = i + 1;
                    goto perform;
                }

                if (v == 2 && vertexs_to_affect[p].vtxflag_2) {
                    j = i + 2;
                    goto perform;
                }

                if (v == 3 && vertexs_to_affect[p].vtxflag_3) {
                    j = i + 3;
                    goto perform;
                }

                goto next;
            perform:
                x1 = (pvfile_x[handle][j] - cx) * cos_y +
                     (pvfile_z[handle][j] - cz) * sin_y;
                z1 = (pvfile_z[handle][j] - cz) * cos_y -
                     (pvfile_x[handle][j] - cx) * sin_y;
                pvfile_z[handle][j] =
                    z_scale *
                        (z1 * cos_x + (pvfile_y[handle][j] - cy) * sin_x) +
                    cz;
                y1 = (pvfile_y[handle][j] - cy) * cos_x - z1 * sin_x;
                pvfile_x[handle][j] = x_scale * (x1 * cos_z + y1 * sin_z) + cx;
                pvfile_y[handle][j] = y_scale * (y1 * cos_z - x1 * sin_z) + cy;
            next:
                v++;
            } while (v < pv_n_vtx[handle][c]);

            p++;
        }
    }

    if (pv_mid_x[handle]) {
        for (p = 0; p < pvfile_npolygs[handle]; p++) {
            i  = 4 * p;
            cx = 0;
            cy = 0;
            cz = 0;

            for (v = 0; v < pv_n_vtx[handle][p]; v++) {
                cx += pvfile_x[handle][i];
                cy += pvfile_y[handle][i];
                cz += pvfile_z[handle][i];
                i++;
            }

            pv_mid_x[handle][p] = cx / v;
            pv_mid_y[handle][p] = cy / v;
            pv_mid_z[handle][p] = cz / v;
        }
    }
}

// Returns the alphabetic correspondent of integers and / or real numbers.

char *alphavalue(double value) {
    gcvt(value, 15, dec);
    return (dec);
}

// Draws the background, with the map offsets.map.
void background(uint16_t start, uint8_t *target, uint8_t *background,
                uint8_t *offsetsmap, uint16_t total_map_bytes,
                uint16_t screenshift) {
    uint16_t tex_loc = start /*+ 4*/;

    for (uint16_t i = (total_map_bytes / 2), si = 0; i > 0; i--, si += 2) {
        uint16_t word = ((uint16_t)(((uint16_t) offsetsmap[si + 1]) << 8u)) |
                        ((uint16_t) offsetsmap[si]);
        if (word >= 64000) {
            uint16_t offset =
                (((uint16_t)(((uint16_t) offsetsmap[si + 1]) << 8u)) |
                 ((uint16_t) offsetsmap[si])) -
                64000;

            tex_loc += offset;
        } else {
            uint16_t screen_loc =
                ((uint16_t)(((uint16_t) offsetsmap[si + 1]) << 8u)) |
                ((uint16_t) offsetsmap[si]);
            screen_loc += screenshift;
            uint8_t color = background[tex_loc];

            memset(&target[screen_loc], color, 5);
            memset(&target[screen_loc + 320], color, 5);
            memset(&target[screen_loc + 640], color, 5);
            memset(&target[screen_loc + 960], color, 5);
            memset(&target[screen_loc + 1280], color, 5);

            tex_loc += 1;
        }
    }
}

/*
    Starry sky, three-of-a-kind. In the amplified view, it has 2,744 stars.
    Star magnitudes go from 0 to +13. Since the player is a cat, with scotopic
    vision, they can probably see more than normal.
*/

void sky(uint16_t limits) {
    uint16_t debug;

    auto min_xy            = (int32_t)(1E9);
    int8_t visible_sectors = 9;

    if (field_amplificator) {
        visible_sectors = 14;
    }

    uint8_t sx, sy, sz;
    float xx, yy, zz, z2, rz, inv_rz, starneg;

    if (!ap_targetting) {
        starneg = 10000;
    } else {
        starneg = 1;
    }

    int32_t sect_x, sect_y, sect_z, rx, ry;
    int32_t advance = 100000, k = 100000 * visible_sectors;
    int32_t temp_x, temp_y, temp_z, temp;
    /*
        The following section changes the rarity factor of the stars as the
        distance from the galactic center increases. The scale on the Y-Axis is
        amplified 30 times, so that the galaxy has the shape of a crushed disk.
        Stars will be rarefied depending on the value of "distance_from_home".
        This is a table that provides the number of stars eliminated (each
        sector contains one star, and the number of sectors visible to the
        amplified field is 14 * 14 * 14 = 2744) as distance_from_home increases
        its value:
            0 - 400,000,000                 0% eliminated
            400,000,000 - 800,000,000       50% eliminated
            1,200,000,000 - 1,600,000,000   75% eliminated
            1,600,000,000 - 2,000,000,000   87.5% eliminated.
        Over 2 billion units, the player can no longer select stars: The rarity
        factor ratio would still be of 1 effective star every 16 sectors.
    */
    int16_t rarity_factor;
    double distance_from_home;

    distance_from_home = sqrt(dzat_x * dzat_x + dzat_z * dzat_z);
    distance_from_home += 30 * fabs(dzat_y);

    rarity_factor = (int16_t)(distance_from_home * 0.25e-8);
    rarity_factor = 1u << (uint16_t) rarity_factor;
    rarity_factor--;

    sect_x = (int32_t)((dzat_x - visible_sectors * 50000) / 100000);
    sect_x *= 100000;

    sect_y = (int32_t)((dzat_y - visible_sectors * 50000) / 100000);
    sect_y *= 100000;

    sect_z = (int32_t)((dzat_z - visible_sectors * 50000) / 100000);
    sect_z *= 100000;

    uint32_t index = 0;

    // Loop over a 3D cube of l,w,h = visible_sectors.
    for (sx = 0; sx < visible_sectors; sx++) {
        for (sy = 0; sy < visible_sectors; sy++) {
            for (sz = 0; sz < visible_sectors; sz++, sect_z += advance) {
                uint16_t cutoff = 50000;

                temp_x = ((sect_x + sect_z) & 0x0001FFFFu) + sect_x;
                // Exclude stars with x coordinate = 0
                if (temp_x == cutoff) {
                    continue;
                }
                temp_x -= cutoff;

                int32_t abc123 = (sect_x + sect_z);
                int32_t accum  = 0;

                int32_t edx = temp_x;
                int32_t eax = abc123;

                // This replaced a very sketchy usage of imul.
                int64_t result = (int64_t) edx * (int64_t) eax;
                eax            = result & 0xFFFFFFFFu;
                edx            = result >> 32u;
                edx += eax;
                accum = edx;

                int32_t idkbro = (sect_x + sect_z) + accum;

                temp_y = (accum & 0x001FFFFu) + sect_y;
                // Exclude stars with y coordinate = 0
                if (temp_y == cutoff) {
                    continue;
                }
                temp_y -= cutoff;

                edx    = temp_y;
                eax    = idkbro;
                result = (int64_t) edx * (int64_t) eax;
                eax    = result & 0xFFFFFFFFu;
                edx    = result >> 32u;
                edx += eax;
                accum = edx;

                temp_z = (accum & 0x0001FFFFu) + sect_z;
                // Exclude stars with z coordinate = 0
                if (temp_z == cutoff) {
                    continue;
                }
                temp_z -= cutoff;

                uint32_t netpos = temp_x + temp_y + temp_z;
                if ((netpos & rarity_factor) != 0) {
                    continue;
                }

                zz = temp_z - dzat_z;
                xx = temp_x - dzat_x;
                yy = temp_y - dzat_y;
                z2 = (zz * opt_tcosbeta) - (xx * opt_tsinbeta);
                rz = (z2 * opt_tcosalfa) + (yy * opt_tsinalfa);

                if (rz < starneg) {
                    continue;
                }

                inv_rz = uno / rz;
                rx     = (int32_t) round(
                    ((xx * opt_pcosbeta) + (zz * opt_psinbeta)) * inv_rz);

                index = rx + VIEW_X_CENTER;
                if (index <= 10 || index >= 310) {
                    continue;
                }

                ry = (int32_t) round((yy * opt_pcosalfa - z2 * opt_psinalfa) *
                                     inv_rz) -
                     2;

                uint16_t nety = ry + VIEW_Y_CENTER;
                if (nety <= 10 || nety >= 190) {
                    continue;
                }

                index += (uint16_t)(320 * nety);

                if (ap_targetting != 1) {
                    uint8_t color = adapted[index];
                    if (color == 68 || color < (limits >> 8u) ||
                        color > (limits & 0xFFu)) {
                        continue;
                    }
                }

                temp              = (int32_t) rz;
                int32_t tempshift = temp >> (13u + field_amplificator);
                int8_t mask       = 63 - tempshift;
                if (mask >= 0) {
                    int8_t color = adapted[index];
                    adapted[index] &= 0xC0u;
                    color &= 0x3Fu;
                    mask += color;
                    if (mask > 63) {
                        mask = 63;
                    }
                    adapted[index] |= mask;
                }

                if (ap_targetting == 1) {
                    temp = (rx * rx) + (ry * ry);

                    if (temp < min_xy) {
                        min_xy      = temp;
                        ap_target_x = temp_x;
                        ap_target_y = temp_y;
                        ap_target_z = temp_z;
                    }
                }
            }
            sect_z -= k;
            sect_y += advance;
        }
        sect_y -= k;
        sect_x += advance;
    }
}

/*
    Still quicktime-vr, unfortunately it is necessary for planets. Otherwise, a
    huge amount of registers and complex machine code macros would be used, b/c
    we can not use the extended registers normally. Better to recap: DS passes
    on GS, ES is the video page (usually hidden, not the adapter area) specified
    in target, FS hosts the tapestry wallpaper to map the globe, and the old DS
    points to the area of the map of the offsets, compressed with MAPS.EXE along
    the x-y plane. In fact, they are not video offset ready, because they must
    becalculated (first byte = Y, second byte = X). When the Y is 100, that
   means the original offset was 64000, and that is not a question of a point,
   but of a series of advances along the segment, indicated for accuracy by byte
   X.
*/

// If set, draw a kind of bubble transparent around the globes drawn with the
// "globe" function. It is used to simulate the presence of the atmosphere, but
// only for planets with considerable quantities of gas.
uint8_t glass_bubble = 1;

void globe(uint16_t start, uint8_t *target, const uint8_t *tapestry,
           const uint8_t *offsetsmap, uint16_t total_map_bytes, double x,
           double y, double z, float mag_factor, int8_t colormask,
           int8_t globe_saturation) {
    uint8_t gman;
    int16_t center_x, center_y, temp;
    double xx, yy, zz, z2, rx, ry, rz;
    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;
    rx = xx * (double) opt_pcosbeta + zz * (double) opt_psinbeta;
    z2 = zz * (double) opt_tcosbeta - xx * (double) opt_tsinbeta;
    rz = z2 * (double) opt_tcosalfa + yy * (double) opt_tsinalfa;
    ry = yy * (double) opt_pcosalfa - z2 * (double) opt_psinalfa;

    if (rz < 0.001) {
        return;
    }

    mag_factor /= rz;
    gman = 1;

    if (mag_factor < 0.01) {
        mag_factor = 0.001;
    }

    if (mag_factor > 0.33) {
        gman = 2;
    }

    if (mag_factor > 0.66) {
        gman = 3;
    }

    if (mag_factor > 0.99) {
        gman = 4;
    }

    if (mag_factor > 1.32) {
        mag_factor = 1.32;
    }

    rx /= rz;
    ry /= rz;

    // 320 = Screen width, 100 = Max x/y pixels of the map,
    // 1.32 = Maximum magnification factor with points of 4 pixels.

    if (rx < -292 || rx > 292) {
        return; // 292 = (320 / 2) + (100 * 1.32)
    }

    if (ry < -232 || ry > 232) {
        return; // 232 = (200 / 2) + (100 * 1.32)
    }

    center_x = (int16_t)(rx + x_centro_f);
    center_y = (int16_t)(ry + y_centro_f);

    uint8_t color = 0;
    uint16_t curr = start;
    for (uint16_t i = (total_map_bytes / 2), j = 0; i > 0; i--, j += 2) {
        if (offsetsmap[j] != 100) {
            int16_t offset = (int8_t) offsetsmap[j];
            temp           = offset;
            temp           = (int16_t) round(((int16_t) temp) * mag_factor);
            uint16_t pos   = temp + center_y;

            if (pos > 6 && pos < 191) {
                offset = (int8_t) offsetsmap[j + 1];
                pos    = 320 * pos;
                temp   = offset;
                temp   = (int16_t) round(((int16_t) temp) * mag_factor);
                offset = temp + center_x;

                if (offset > 6 && offset < 311) {
                    pos += offset;
                    color = tapestry[curr];
                    if (color < globe_saturation) {
                        color = globe_saturation;
                    }

                    color |= colormask;
                    if (gman == 1) {
                        target[pos] = color;
                    } else if (gman == 2) {
                        target[pos]     = color;
                        target[pos + 1] = color;

                        target[pos + 320] = color;
                        target[pos + 321] = color;
                    } else if (gman == 3) {
                        target[pos]     = color;
                        target[pos + 1] = color;
                        target[pos + 2] = color;

                        target[pos + 320] = color;
                        target[pos + 321] = color;
                        target[pos + 322] = color;

                        target[pos + 640] = color;
                        target[pos + 641] = color;
                        target[pos + 642] = color;
                    } else if (gman == 4) {
                        target[pos]     = color;
                        target[pos + 1] = color;
                        target[pos + 2] = color;
                        target[pos + 3] = color;

                        target[pos + 320] = color;
                        target[pos + 321] = color;
                        target[pos + 322] = color;
                        target[pos + 323] = color;

                        target[pos + 640] = color;
                        target[pos + 641] = color;
                        target[pos + 642] = color;
                        target[pos + 643] = color;

                        target[pos + 960] = color;
                        target[pos + 961] = color;
                        target[pos + 962] = color;
                        target[pos + 963] = color;
                    }
                }
            }

            curr += 1;
        } else {
            curr += offsetsmap[j + 1];
        }
    }

    if (!glass_bubble) {
        return;
    }

    temp = mag_factor * 7.25;

    if (!temp) {
        return;
    }

    rx = mag_factor * 110;
    ry = (1.2 * deg) / mag_factor;
    rz = 0.5 * ry;
    z2 = 0.833 * rx;

    while (rz < 2 * M_PI) {
        smootharound_64(target, center_x + rx * cos(rz),
                        center_y + z2 * sin(rz), temp, 1);
        rz += ry;
    }
}

/* Same as above, but modified to make luminous globes, without details but with
 * a clear demarcation between the illuminated and dark hemisphere. Used for
 * planets at a medium distance from the stardrifter.
 */
void glowing_globe(int16_t start, uint8_t *target, const uint8_t *offsetsmap,
                   uint16_t total_map_bytes, double x, double y, double z,
                   float mag_factor, int16_t terminator_start,
                   int16_t terminator_arc, uint8_t color) {
    uint16_t center_x, center_y, temp;
    double xx, yy, zz, z2, rx, ry, rz;
    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;
    rx = xx * (double) opt_pcosbeta + zz * (double) opt_psinbeta;
    z2 = zz * (double) opt_tcosbeta - xx * (double) opt_tsinbeta;
    rz = z2 * (double) opt_tcosalfa + yy * (double) opt_tsinalfa;
    ry = yy * (double) opt_pcosalfa - z2 * (double) opt_psinalfa;

    if (rz < 0.001) {
        return;
    }

    mag_factor /= rz;

    if (mag_factor > 0.66) {
        mag_factor = 0.66;
    }

    if (mag_factor < 0.01) {
        mag_factor = 0.001;
    }

    rx /= rz;
    ry /= rz;

    /*  320 = Largh. schermo, 100 = max x/y pixels della mappa,
        0.66 = massimo fattore d'ingrandimento con punti di 4 pixels. */

    if (rx < -226 || rx > 226) {
        return; // 172 = (320 / 2) + (100 * 0.66)
    }

    if (ry < -166 || ry > 166) {
        return; // 132 = (200 / 2) + (100 * 0.66)
    }

    center_x = (uint16_t)(rx + x_centro_f);
    center_y = (uint16_t)(ry + y_centro_f);
    start -= terminator_start;

    while (start < 0) {
        start += 360;
    }

    uint8_t colorMask = ((color & 0x3Fu) >> 2u) | (color & 0xC0u);
    uint16_t curr     = start;
    for (uint16_t i = (total_map_bytes / 2), j = 0; i > 0; i--, j += 2) {
        if (offsetsmap[j] != 100) {
            if ((curr & 0x03u) == 0) {
                int16_t offset = (int8_t) offsetsmap[j];
                temp           = offset;
                temp         = (uint16_t) round(((int16_t) temp) * mag_factor);
                uint16_t pos = temp + center_y;
                if (pos > 10 && pos < 190) { // Y bounds.
                    offset = (int8_t) offsetsmap[j + 1];
                    pos    = 320 * pos;
                    temp   = offset;
                    temp   = (uint16_t) round(((int16_t) temp) * mag_factor);
                    offset = temp + center_x;
                    // X bounds. Don't ask why it's 6. It just works.
                    if (offset > 6 && offset < 310) {
                        pos += offset;
                        if (curr < terminator_arc) {
                            target[pos] = colorMask;
                        } else {
                            target[pos] = color;
                        }
                    }
                }
            }

            curr += 1;
            if (curr >= 360) {
                curr = 0;
            }
        } else {
            curr += offsetsmap[j + 1];
            curr %= 360;
        }
    }
}

/*
    Modified to make white globes. It is used for stars seen from afar, and for
    the corona. It does not need a globe map. Takes a color from between 0 and
    0x3F, b/c it should only work on the first shade for speed.
*/
void white_globe(uint8_t *target, double x, double y, double z,
                 float mag_factor, float fgm_factor) {
    double center_x, center_y, mag, fgm, shade_ext, ise;
    double xx, yy, zz, z2, rx, ry, rz, xa, ya, xb, yb;
    double magsq, fgmsq;
    uint16_t pixptr;
    int8_t pix;

    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;

    rx = xx * (double) opt_pcosbeta + zz * (double) opt_psinbeta;
    z2 = zz * (double) opt_tcosbeta - xx * (double) opt_tsinbeta;
    rz = z2 * (double) opt_tcosalfa + yy * (double) opt_tsinalfa;
    ry = yy * (double) opt_pcosalfa - z2 * (double) opt_psinalfa;

    if (rz < 0.001) {
        return;
    }

    mag_factor /= rz;

    if (mag_factor > 2.99) {
        mag_factor = 2.99;
    }

    if (mag_factor < 0.01) {
        mag_factor = 0.01;
    }

    rx /= rz;
    ry /= rz;

    /*  320 = Largh. schermo, 100 = max x/y pixels della mappa,
        3.00 = massimo fattore d'ingrandimento con dispersione. */

    if (rx < -460 || rx > 460) {
        return; // 460 = (320 / 2) + (100 * 3.00)
    }

    if (ry < -400 || ry > 400) {
        return; // 400 = (200 / 2) + (100 * 3.00)
    }

    center_x  = rx + x_centro_f + 0.5;
    center_y  = ry + y_centro_f + 0.5;
    mag       = mag_factor * 100 + 1.5;
    fgm       = fgm_factor * mag; // full globe magnitude
    shade_ext = mag - fgm;

    if (shade_ext < 1) {
        shade_ext = 1;
    }

    ise   = 0x3F / shade_ext;
    magsq = mag * mag;
    fgmsq = fgm * fgm;

    ya = -mag * 1.2;
    yb = center_y + mag;
    yy = center_y - mag;

    while (yy < yb) {
        xa = -mag;
        xb = center_x + mag;
        xx = center_x - mag;

        while (xx < xb) {
            if (xx > 9 && xx < 313 && yy > 9 && yy < 190) {
                zz = xa * xa + ya * ya;

                if (zz < magsq) {
                    if (zz > fgmsq) {
                        pix = (int8_t)(0x3F - (sqrt(zz) - fgm) * ise);
                    } else {
                        pix = 0x3F;
                    }

                    pixptr = (uint16_t)(320 * ((int16_t) yy)) + (int16_t) xx;
                    pix += target[pixptr];

                    if (pix > 0x3F) {
                        target[pixptr]       = 0x3F;
                        target[pixptr + 1]   = 0x3F;
                        target[pixptr + 320] = 0x3F;
                        target[pixptr + 321] = 0x3F;
                    } else {
                        target[pixptr]       = pix;
                        target[pixptr + 1]   = pix;
                        target[pixptr + 320] = pix;
                        target[pixptr + 321] = pix;
                    }
                }
            }

            xa += 2;
            xx += 2;
        }

        ya += 2.4;
        yy += 2;
    }
}

/*  Come sopra, ma mentre quella di sopra traccia in 4x4 pixels,
    dimezzando la risoluzione per essere pi� veloce nel tracciamento
    di globi che possono coprire tutto lo schermo, questa traccia in 1x1,
    � pi� precisa ma applicabile solo alla visualizzazione delle stelle
    viste dai pianeti. */

double xsun_onscreen;

void white_sun(uint8_t *target, double x, double y, double z, float mag_factor,
               float fgm_factor) {
    double center_x, center_y, mag, fgm, shade_ext, ise;
    double xx, yy, zz, z2, rx, ry, rz, xa, ya, xb, yb;
    double magsq, fgmsq;
    uint16_t pixptr;
    int8_t pix;
    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;
    rx = xx * (double) opt_pcosbeta + zz * (double) opt_psinbeta;
    z2 = zz * (double) opt_tcosbeta - xx * (double) opt_tsinbeta;
    rz = z2 * (double) opt_tcosalfa + yy * (double) opt_tsinalfa;
    ry = yy * (double) opt_pcosalfa - z2 * (double) opt_psinalfa;

    if (rz < 0.001) {
        return;
    }

    mag_factor /= rz;

    if (mag_factor > 2.99) {
        mag_factor = 2.99;
    }

    if (mag_factor < 0.01) {
        mag_factor = 0.01;
    }

    rx /= rz;
    ry /= rz;
    xsun_onscreen = rx + x_centro_f;

    /*  320 = Largh. schermo, 100 = max x/y pixels della mappa,
        3.00 = massimo fattore d'ingrandimento con dispersione. */

    if (rx < -460 || rx > 460) {
        return; // 460 = (320 / 2) + (100 * 3.00)
    }

    if (ry < -400 || ry > 400) {
        return; // 400 = (200 / 2) + (100 * 3.00)
    }

    center_x  = rx + x_centro_f + 0.5;
    center_y  = ry + y_centro_f + 0.5;
    mag       = mag_factor * 100 + 1.5;
    fgm       = fgm_factor * mag; // full globe magnitude
    shade_ext = mag - fgm;

    if (shade_ext < 1) {
        shade_ext = 1;
    }

    ise   = 0x3F / shade_ext;
    magsq = mag * mag;
    fgmsq = fgm * fgm;
    ya    = -mag * 1.2;
    yb    = center_y + mag;
    yy    = center_y - mag;

    while (yy < yb) {
        xa = -mag;
        xb = center_x + mag;
        xx = center_x - mag;

        while (xx < xb) {
            if (xx > 9 && xx < 313 && yy > 9 && yy < 190) {
                zz = xa * xa + ya * ya;

                if (zz < magsq) {
                    if (zz > fgmsq) {
                        pix = 0x3F - (sqrt(zz) - fgm) * ise;
                    } else {
                        pix = 0x3F;
                    }

                    pixptr = ((int16_t) (((int16_t) 320) * ((int16_t) yy))) + (int16_t) xx;
                    pix += target[pixptr];

                    if (pix > 0x3F) {
                        target[pixptr] = 0x3F;
                    } else {
                        target[pixptr] = pix;
                    }
                }
            }

            xa++;
            xx++;
        }

        ya += 1.2;
        yy++;
    }
}

// Glow around the most intense lights.

/*  float far *lft_sin = (float far *) farmalloc (361*4);
    float far *lft_cos = (float far *) farmalloc (361*4);*/

float lft_sin[361];
float lft_cos[361];

int8_t lens_flares_init() {
    int16_t c;
    double a = 0, interval = M_PI / 180;

    for (c = 0; c <= 360; c++) {
        lft_cos[c] = (float) cos(a);
        lft_sin[c] = (float) sin(a);
        a += interval;
    }

    return (1);
}

void lens_flares_for(double cam_x, double cam_y, double cam_z, double xlight,
                     double ylight, double zlight, double interval,
                     int16_t added, int8_t on_hud, int8_t condition,
                     int16_t xshift, int16_t yshift) {
    double k = 10 / interval, l = 1, u = 1.5;
    double xx, yy, zz, z2, rx, ry, rz;
    int32_t xs, ys, dx, dy;
    float xr, yr;
    uint8_t temp;
    int16_t c, r;
    setfx(1);
    xx = xlight - cam_x;
    yy = ylight - cam_y;
    zz = zlight - cam_z;
    rx = xx * (double) opt_pcosbeta + zz * (double) opt_psinbeta;
    z2 = zz * (double) opt_tcosbeta - xx * (double) opt_tsinbeta;
    rz = z2 * (double) opt_tcosalfa + yy * (double) opt_tsinalfa;
    ry = yy * (double) opt_pcosalfa - z2 * (double) opt_psinalfa;

    if (rz > 1) {
        if (interval < 0) {
            k = -interval / rz;
        } else {
            k = 10 / interval;
        }

        xs = (int32_t)(rx / rz + xshift);
        ys = (int32_t)(ry / rz + yshift);

        if (xs > -150 && ys > -90 && xs < 160 && ys < 90) {
            switch (condition) {
            case 1:
                temp = adapted[xs + VIEW_X_CENTER + 320 * (ys + VIEW_Y_CENTER)];

                if (temp < 64) {
                    goto exit_local;
                }

                break;

            case 2:
                temp = adapted[xs + VIEW_X_CENTER + 320 * (ys + VIEW_Y_CENTER)];

                if (temp < 64 || temp > 127) {
                    goto exit_local;
                }

                break;
            default:
                break;
            }

            for (c = 0; c < 180; c += added) {
                dx = (int32_t)(lft_cos[c] * k * l);
                dy = (int32_t)(lft_sin[c] * k * l);
                fline(xs - dx, ys - dy, xs + dx, ys + dy);

                if (on_hud && !(c % 8)) {
                    dx /= 10;
                    dy /= 10;
                    xr = (float) xs * -0.1;
                    yr = (float) ys * -0.1;

                    for (r = 0; r < 3; r++) {
                        fline((int32_t)(xr - dx), (int32_t)(yr - dy),
                              (int32_t)(xr + dx), (int32_t)(yr + dy));
                        dx *= 4;
                        dy *= 4;
                        xr *= 3;
                        yr *= 3;
                    }
                }

                l *= u;

                if (l > 3 || l < 1) {
                    u = 1 / u;
                }
            }
        }
    }

exit_local:
    resetfx();
}

/*
    Distant dots, for example, planets and moons. The two functions are
    integrated: a dot is drawn if the distance is big. As you approach, the dot
    becomes a disk of 5px diameter max. We then have to pass control to another
    function to draw the planet properly.
*/

const double pix_dst_scale = 0.384;
const double pix_rad_scale = 1228.8;

#define LIGHT_EMITTING 0
#define LIGHT_ABSORBING 1
#define MULTICOLOUR 2

int8_t pixilating_effect = LIGHT_EMITTING;
int8_t pixel_spreads     = 1;
uint8_t multicolourmask  = 0xC0;

// TODO; Might be offset from proper position. Verify against vanilla.
void single_pixel_at_ptr(uint16_t offset, uint8_t pixel_color) {
    // Add ptr shift to the offset.
    uint8_t *shifted = adapted + offset;
    uint8_t alow     = shifted[0];
    alow &= 0x3Fu;
    alow += pixel_color;

    uint8_t ahigh;
    switch (pixilating_effect) {
    case LIGHT_EMITTING:
        if (shifted[0] > 63) {
            ahigh = shifted[0];
            ahigh &= 0xC0u;
            if (alow > 0x3E) {
                alow = 0x3E;
            }
            alow |= ahigh;
            shifted[0] = alow;
        }
        break;
    case LIGHT_ABSORBING:
        if (shifted[0] > 63) {
            ahigh = shifted[0];
            ahigh &= 0xC0u;
            alow >>= 1u;
            alow |= ahigh;
            shifted[0] = alow;
        }
        break;
    case MULTICOLOUR:
        if (shifted[0] > 63) {
            ahigh = multicolourmask;
            ahigh &= 0xC0u;
            alow >>= 1u;
            alow |= ahigh;
            shifted[0] = alow;
        }
        break;
    default:
        break;
    }
}

int8_t far_pixel_at(double xlight, double ylight, double zlight, double radii,
                    uint8_t unconditioned_color) {
    double xx, yy, zz, z2, rz;
    int32_t pixel_color;
    uint8_t edge_color_1;
    uint8_t edge_color_2;
    uint8_t edge_color_3;
    uint8_t edge_color_4;
    xx  = xlight - dzat_x;
    yy  = ylight - dzat_y;
    zz  = zlight - dzat_z;
    pxx = xx * opt_pcosbeta + zz * opt_psinbeta;
    z2  = zz * opt_tcosbeta - xx * opt_tsinbeta;
    rz  = z2 * opt_tcosalfa + yy * opt_tsinalfa;
    pyy = yy * opt_pcosalfa - z2 * opt_psinalfa;

    if (rz > 0.001) {
        if (!unconditioned_color) {
            pixel_color = 64 - (rz * pix_dst_scale) + (radii * pix_rad_scale);

            if (pixel_color > 63) {
                pixel_color = 63;
            }

            if (pixel_color < 0) {
                pixel_color = 0;
            }
        } else {
            pixel_color = unconditioned_color;
        }

        pxx /= rz;
        pxx += VIEW_X_CENTER;
        pyy /= rz;
        pyy += VIEW_Y_CENTER;

        if (pxx > 10 && pyy > 10 && pxx < 310 && pyy < 190) {
            vptr = (uint16_t)(320 * (int16_t) pyy + pxx);

            if (pixel_spreads) {
                edge_color_1 = pixel_color >> 1u;
                edge_color_2 = pixel_color >> 2u;
                edge_color_3 = pixel_color >> 3u;
                edge_color_4 = pixel_color >> 4u;

                if (edge_color_1 > 7) {
                    single_pixel_at_ptr(vptr - 320, edge_color_1);
                    single_pixel_at_ptr(vptr + 320, edge_color_1);
                    single_pixel_at_ptr(vptr - 1, edge_color_1);
                    single_pixel_at_ptr(vptr + 1, edge_color_1);
                }

                if (edge_color_2 > 7) {
                    single_pixel_at_ptr(vptr - 321, edge_color_2);
                    single_pixel_at_ptr(vptr - 319, edge_color_2);
                    single_pixel_at_ptr(vptr + 321, edge_color_2);
                    single_pixel_at_ptr(vptr + 319, edge_color_2);
                }

                if (edge_color_3 > 7) {
                    single_pixel_at_ptr(vptr - 640, edge_color_3);
                    single_pixel_at_ptr(vptr + 640, edge_color_3);
                    single_pixel_at_ptr(vptr - 2, edge_color_3);
                    single_pixel_at_ptr(vptr + 2, edge_color_3);
                }

                if (edge_color_4 > 7) {
                    single_pixel_at_ptr(vptr - 641, edge_color_4);
                    single_pixel_at_ptr(vptr - 639, edge_color_4);
                    single_pixel_at_ptr(vptr + 641, edge_color_4);
                    single_pixel_at_ptr(vptr + 639, edge_color_4);
                    single_pixel_at_ptr(vptr - 322, edge_color_4);
                    single_pixel_at_ptr(vptr - 318, edge_color_4);
                    single_pixel_at_ptr(vptr + 322, edge_color_4);
                    single_pixel_at_ptr(vptr + 318, edge_color_4);
                }

                if (pixel_color > 7) {
                    single_pixel_at_ptr(vptr, pixel_color);
                }
            } else {
                if (pixel_color) {
                    single_pixel_at_ptr(vptr, pixel_color);
                }
            }

            return (1);
        }
    }

    return (0);
}

/*
    The rest of the functions that operate on local data.
    Functions for: Setting the cosmic timer of Noctis, constructing the
    surroundings of the stars and planets, and visualization of the planets
    from orbit.

*/

// Measure the time elapsed from 1-1-1984 to today, accurate to one frame,
// which is 1/25 of a second on average.
void getsecs() {
    // January 1, 1984
    struct tm nepoch = {0};
    nepoch.tm_sec    = 0;
    nepoch.tm_min    = 0;
    nepoch.tm_hour   = 0;
    nepoch.tm_mday   = 1;
    nepoch.tm_mon    = 0;
    nepoch.tm_year   = 84;

    time_t rawtime;
    time(&rawtime);
    struct tm *timeinfo;
    timeinfo = localtime(&rawtime);
    // Have to extract info from timeinfo before doing difftime, or else
    // timeinfo will point to nepoch, for some reason...
    uint8_t currSecond = timeinfo->tm_sec;

    secs = difftime(rawtime, mktime(&nepoch));
    // Offsetting the clock by -82800 seconds is done to fudge it to match the
    // clock in the original. Don't really know where the discrepancy comes
    // from.
    secs -= 82800;
    isecs = currSecond;

    if (p_isecs != isecs) { // Frame timing.
        if (_delay >= 10) {
            _delay--;
        }

        p_isecs = isecs;
        gl_fps  = fps;
        fps     = 1;
    } else { // Fractions of a second
        if (gl_fps) {
            secs += (double) fps / (double) gl_fps;
        }

        fsecs = (double) fps / (double) gl_fps;
        fps++;
    }

    epoc = (int16_t)(6011 + secs / 1e9);
}

// Extracts from the pseudo table, from 74 trillion different elements,
// information about the chosen star.

void extract_ap_target_infos() {
    brtl_srand((uint16_t)(ap_target_x / 100000 * ap_target_y / 100000 *
                          ap_target_z / 100000));
    ap_target_class = brtl_random(star_classes);
    ap_target_ray   = ((float) class_ray[ap_target_class] +
                     (float) brtl_random(class_rayvar[ap_target_class])) *
                    0.001;
    ap_target_r    = class_rgb[3 * ap_target_class + 0];
    ap_target_g    = class_rgb[3 * ap_target_class + 1];
    ap_target_b    = class_rgb[3 * ap_target_class + 2];
    ap_target_spin = 0;

    if (ap_target_class == 11) {
        ap_target_spin = brtl_random(30) + 1;
    }

    if (ap_target_class == 7) {
        ap_target_spin = brtl_random(12) + 1;
    }

    if (ap_target_class == 2) {
        ap_target_spin = brtl_random(4) + 1;
    }
}

// Extracts a whole-type pseudo-random number by converting it to f-p.
float zrandom(int16_t range) {
    return (float) (brtl_random(range) -
                    brtl_random(range)); // NOLINT(misc-redundant-expression)
}

/*  Part of the cartography management.
 *  It has been moved here to be called by "prepare_nearstar".
 *  --------------------------------------------------------------------------------
 *  Search for an identification code (for a planet or for a star) in the
 * stellar mapping file, and show the position of the record. If the result is
 * -1, the code does not exist, i.e. there is no name for the star or for the
 * planet that corresponds to that code. Type can be: 'P' = Planet, 'S' = Star.
 */

double idscale = 0.00001;

int32_t search_id_code(double id_code, int8_t type) {
    int32_t total_pos = 4;
    bool found        = false;
    uint16_t n, curr_pos, index;
    double id_low  = id_code - idscale;
    double id_high = id_code + idscale;
    FILE *smh      = fopen(starmap_file, "r");

    if (smh != nullptr) {
        auto buffer = (int8_t *) malloc(ps_bytes);

        auto buffer_ascii  = (int8_t *) buffer;
        auto buffer_double = (double *) buffer;
        fseek(smh, 4, SEEK_SET);

        while ((n = fread(buffer_ascii, 1, ps_bytes, smh)) > 0) {
            curr_pos = 0;
            index    = 0;

            while (curr_pos < n) {
                if (buffer_ascii[curr_pos + 29] == type) {
                    if (buffer_double[index] > id_low &&
                        buffer_double[index] < id_high) {
                        found = true;
                        goto stop;
                    }
                }

                total_pos += 32;
                curr_pos += 32;
                index += 4;
            }
        }

    stop:
        fclose(smh);
        free(buffer);
    }

    if (found) {
        return (total_pos);
    } else {
        return (-1);
    }
}

/* Prepare information on the nearby star, the one which the player has just
 * approached. Among other things, prepare the planets by extracting them from
 * the pseudo table.
 */

// Estimate the number of major planets associated with the coord. of a star.
int16_t starnop(double star_x, double star_y, double star_z) {
    int16_t r;
    brtl_srand((int32_t) star_x % 10000 * (int32_t) star_y % 10000 *
               (int32_t) star_z % 10000);
    r = brtl_random(class_planets[ap_target_class] + 1);
    r += brtl_random(2);
    r -= brtl_random(2);

    if (r < 0) {
        r = 0;
    }

    return (r);
    return 0;
}

void prepare_nearstar() {
    int16_t n, c, q, r, s, t;
    double key_radius;

    if (!_delay) {
        nearstar_class = ap_target_class;
        nearstar_x     = ap_target_x;
        nearstar_y     = ap_target_y;
        nearstar_z     = ap_target_z;
        nearstar_ray   = ap_target_ray;
        nearstar_spin  = ap_target_spin;
        nearstar_r     = ap_target_r;
        nearstar_g     = ap_target_g;
        nearstar_b     = ap_target_b;
    }

    s_m = qt_M_PI * nearstar_ray * nearstar_ray * nearstar_ray * 0.01e-7;
    nearstar_identity =
        nearstar_x / 100000 * nearstar_y / 100000 * nearstar_z / 100000;
    brtl_srand((int32_t) nearstar_x % 10000 * (int32_t) nearstar_y % 10000 *
               (int32_t) nearstar_z % 10000);
    nearstar_nop = brtl_random(class_planets[nearstar_class] + 1);

    // First draw (almost random, unrealistic);
    for (n = 0; n < nearstar_nop; n++) {
        nearstar_p_owner[n]      = -1;
        nearstar_p_orb_orient[n] = (double) deg * (double) brtl_random(360);
        nearstar_p_orb_seed[n] =
            3.0 * (n * n + 1) * nearstar_ray +
            (float) brtl_random((int16_t)(300 * nearstar_ray)) / 100.0;
        nearstar_p_tilt[n] =
            zrandom((int16_t)(10 * nearstar_p_orb_seed[n])) / 500.0;
        nearstar_p_orb_tilt[n] =
            zrandom((int16_t)(10 * nearstar_p_orb_seed[n])) / 5000.0;
        nearstar_p_orb_ecc[n] =
            1 -
            (double) brtl_random((int16_t)(nearstar_p_orb_seed[n] +
                                           10 * fabs(nearstar_p_orb_tilt[n]))) /
                2000;
        nearstar_p_ray[n] =
            (double) brtl_random((int16_t)(nearstar_p_orb_seed[n])) * 0.001 +
            0.01;
        nearstar_p_ring[n] = zrandom((int16_t) nearstar_p_ray[n]) *
                             (1 + (double) brtl_random(1000) / 100.0);

        if (nearstar_class != 8) {
            nearstar_p_type[n] = brtl_random(planet_types);
        } else {
            if (brtl_random(2)) {
                nearstar_p_type[n] = 10;
                nearstar_p_orb_tilt[n] *= 100;
            } else {
                nearstar_p_type[n] = brtl_random(planet_types);
            }
        }

        if (nearstar_class == 2 || nearstar_class == 7 ||
            nearstar_class == 15) {
            nearstar_p_orb_seed[n] *= 10;
        }
    }

    /* Aumento delle probabilit� di pianeti abitabili su classe zero. */

    if (!nearstar_class) {
        if (brtl_random(4) == 2) {
            nearstar_p_type[2] = 3;
        }

        if (brtl_random(4) == 2) {
            nearstar_p_type[3] = 3;
        }

        if (brtl_random(4) == 2) {
            nearstar_p_type[4] = 3;
        }
    }

    /*  Eliminazione di pianeti impossibili attorno a certe stelle.
        Fase 1: solo quelli impossibili per tipo di stella. */

    for (n = 0; n < nearstar_nop; n++) {
        switch (nearstar_class) {
        case 2:
            while (nearstar_p_type[n] == 3) {
                nearstar_p_type[n] = brtl_random(10);
            }

            break;

        case 5:
            while (nearstar_p_type[n] == 6 || nearstar_p_type[n] == 9) {
                nearstar_p_type[n] = brtl_random(10);
            }

            break;

        case 7:
            nearstar_p_type[n] = 9;
            break;

        case 9:
            while (nearstar_p_type[n] != 0 && nearstar_p_type[n] != 6 &&
                   nearstar_p_type[n] != 9) {
                nearstar_p_type[n] = brtl_random(10);
            }

            break;

        case 11:
            while (nearstar_p_type[n] != 1 && nearstar_p_type[n] != 7) {
                nearstar_p_type[n] = brtl_random(10);
            }
            break;
        default:
            break;
        }
    }

    /*  Eliminazione di pianeti impossibili attorno a certe stelle.
        Fase 2: solo quelli impossibili per distanza dalla stella. */

    for (n = 0; n < nearstar_nop; n++) {
        switch (nearstar_p_type[n]) {
        case 0:
            if (brtl_random(8)) {
                nearstar_p_type[n]++;
            }

            break;

        case 3:
            if ((n < 2) || (n > 6) || (nearstar_class && brtl_random(4))) {
                if (brtl_random(2)) {
                    nearstar_p_type[n]++;
                } else {
                    nearstar_p_type[n]--;
                }
            }

            break;

        case 7:
            if (n < 7) {
                if (brtl_random(2)) {
                    nearstar_p_type[n]--;
                } else {
                    nearstar_p_type[n] -= 2;
                }
            }

            break;
        }
    }

    /* Estrazione dei satelliti naturali (lune). */
    nearstar_nob = nearstar_nop;

    if (nearstar_class == 2 || nearstar_class == 7 || nearstar_class == 15) {
        goto no_moons;
    }

    for (n = 0; n < nearstar_nop; n++) {
        // (t=) Numero di satelliti per pianeta.
        s = nearstar_p_type[n];

        if (n < 2) {
            t = 0;

            if (s == 10) {
                t = brtl_random(3);
            }
        } else {
            t = brtl_random(planet_possiblemoons[s] + 1);
        }

        if (nearstar_nob + t > maxbodies) {
            t = maxbodies - nearstar_nob;
        }

        // Caratteristiche dei satelliti.
        for (c = 0; c < t; c++) {
            q                        = nearstar_nob + c;
            nearstar_p_owner[q]      = n;
            nearstar_p_moonid[q]     = c;
            nearstar_p_orb_orient[q] = (double) deg * (double) brtl_random(360);
            nearstar_p_orb_seed[q] =
                (c * c + 4) * nearstar_p_ray[n] +
                (float) zrandom((int16_t)(300 * nearstar_p_ray[n])) / 100;
            nearstar_p_tilt[q] =
                zrandom((int16_t)(10 * nearstar_p_orb_seed[q])) / 50;
            nearstar_p_orb_tilt[q] =
                zrandom((int16_t)(10 * nearstar_p_orb_seed[q])) / 500;
            nearstar_p_orb_ecc[q] =
                1 - (double) brtl_random(
                        (int16_t)(nearstar_p_orb_seed[q] +
                                  10 * fabs(nearstar_p_orb_tilt[q]))) /
                        2000;
            nearstar_p_ray[q] =
                (double) brtl_random((int16_t) nearstar_p_orb_seed[n]) * 0.05 +
                0.1;
            nearstar_p_ring[q] = 0;
            nearstar_p_type[q] = brtl_random(planet_types);
            // Estrazione tipologia di satellite:
            r = nearstar_p_type[q];

            // Un oggetto substellare come luna?
            // Ce lo pu� avere solo una stella compagna.
            if (r == 9 && s != 10) {
                r = 2;
            }

            // Un gigante gassoso come luna?
            // Ce lo pu� avere solo un oggetto substellare,
            // o una stella compagna in un sistema multiplo.
            if (r == 6 && s < 9) {
                r = 5;
            }

            // "Raffreddamento" satelliti esterni, lontani sia
            // dal pianeta che dalla stella, in genere congelati.
            if (n > 7 && brtl_random(c)) {
                r = 7;
            }

            if (n > 9 && brtl_random(c)) {
                r = 7;
            }

            // Lune relativamente grandi possono esistere solo
            // attorno a pianeti gassosi ed oggetti substellari.
            // Invece, i simil-lunari(1), i simil-marziani(5),
            // le lune come Io(0), e quelle come Europa(7),
            // possono esistere anche attorno ad altri tipi di
            // pianeti, ma di certo in scala piuttosto ridotta.
            if (r == 2 || r == 3 || r == 4 || r == 8) {
                if (s != 6 && s < 9) {
                    r = 1;
                }
            }

            // Attorno ai giganti gassosi, se il test precedente
            // � passato (s = 6/9/10, gassoso/substellare/stella),
            // b�, possono anche esserci, a certe condizioni,
            // delle lune abitabili. Per queste, per�, la stella
            // dev'essere in genere di classe zero ed il pianeta
            // gigante non dev'essere troppo lontano dalla stella.
            // C'� invece uguale probabilit� di trovare mondi
            // abitabili attorno agli oggetti substellari: al di
            // l� della distanza dalla stella, tali lune possono
            // essere scaldate abbastanza da una stella mancata.
            if (r == 3 && s < 9) {
                if (n > 7) {
                    r = 7;
                }

                if (nearstar_class && brtl_random(4)) {
                    r = 5;
                }

                if (nearstar_class == 2 || nearstar_class == 7 ||
                    nearstar_class == 11) {
                    r = 8;
                }
            }

            // Una luna ghiacciata � esclusa, prima di arrivare
            // almeno alla sesta orbita planetaria, perch� fa
            // comunque troppo caldo.
            if (r == 7 && n <= 5) {
                r = 1;
            }

            // Ma lune ghiacciate sono comunque molto pi�
            // frequenti se la stella � molto piccola e fredda:
            // un pianeta in genere pu� avere meccanismi interni
            // che lo scaldano. Una luna no.
            if ((nearstar_class == 2 || nearstar_class == 5 ||
                 nearstar_class == 7 || nearstar_class == 11) &&
                brtl_random(n)) {
                r = 7;
            }

            // Fine estrazione tipologia di satellite.
            nearstar_p_type[q] = r;
        }

        nearstar_nob += t;
    }

    /*  Ri-Normalizzazione delle dimensioni dei pianeti,
        normalizzazione delle orbite in base al principio di Keplero.
        Il principio di Keplero stabilisce che il raggio dell'orbita di
        un pianeta tende ad essere simile alla sommatoria dei raggi delle
        orbite di tutti i pianeti interni ad esso. Per�, per un numero di
        pianeti maggiore di 8, il principio non � pi� valido. Noctis
        rinormalizza le orbite oltre l'ottava, aggiungendo a tali orbite
        il 22% circa della sommatoria delle precedenti. Ovvero:

        SE si applica il principio di Keplero
        per (ad esempio) 12 pianeti, e per Raggio Prima Orbita = 1,
        allora i raggi delle altre orbite sarebbero:
            1  2  3  6  12  24  48  96  192  384  768  1536

        SE si applica l'organizzazione di Noctis, il tutto diventerebbe:
            1  2  3  6  12  24  48  96  117  143  174  212

        Il 22% non � un valore a caso: rappresenta all'incirca il rapporto
        fra i raggi delle orbite di Plutone e di Urano. Plutone � circa del
        22% pi� lontano dal Sole di Urano, cio� l'ottava orbita. Ovvio che
        non significa che un sistema planetario pi� vasto debba per forza
        avere orbite organizzate in questo modo, anche perch� Plutone non
        � certo un pianeta "naturalmente" formatosi assieme agli altri, ma
        pi� probabilmente un satellite sfuggito o un corpo della nube di
        Oort catturato dal Sole. Per� bisogna dire che le influenze delle
        orbite dei pianeti interni, col proseguire della successione di
        Keplero, diventano sempre meno significative. Penso che tale
        successione, semplicemente, debba essere in qualche modo limitata,
        a un certo punto: � improbabile che ci siano pianeti in orbita
        stabile a distanze come quelle risultanti per le orbite oltre
        l'ottava. Noctis annovera anche stelle con ben 20 pianeti!

        Come ultima annotazione, il raggio delle orbite � influenzato
        anche dalla massa dei pianeti. Pianeti che hanno all'interno delle
        loro orbite giganti gassosi saranno un po' pi� lontani della media
        perch� altrimenti le loro orbite potrebbero essere troppo
        destabilizzate dalla massa dei giganti. */
no_moons:
    key_radius = nearstar_ray * planet_orb_scaling;

    if (nearstar_class == 8) {
        key_radius *= 2;
    }

    if (nearstar_class == 2) {
        key_radius *= 16;
    }

    if (nearstar_class == 7) {
        key_radius *= 18;
    }

    if (nearstar_class == 11) {
        key_radius *= 20;
    }

    for (n = 0; n < nearstar_nop; n++) {
        nearstar_p_ray[n] =
            avg_planet_ray[nearstar_p_type[n]] +
            avg_planet_ray[nearstar_p_type[n]] * zrandom(100) / 200;
        nearstar_p_ray[n] *= avg_planet_sizing;
        nearstar_p_orb_ray[n] = key_radius + key_radius * zrandom(100) / 500;
        nearstar_p_orb_ray[n] +=
            key_radius * avg_planet_ray[nearstar_p_type[n]];

        if (n < 8) {
            key_radius += nearstar_p_orb_ray[n];
        } else {
            key_radius += 0.22 * nearstar_p_orb_ray[n];
        }
    }

    /*  Ri-Normalizzazione delle dimensioni delle lune,
        normalizzazione orbite lunari in base al principio di Keplero,
        a sua volta rielaborato come nelle precedenti annotazioni,
        solo che la limitazione avviene per orbite oltre la terza al 12%,
        ed � molto pi� effettiva oltre l'ottava orbita (al 2.5%). */
    n = nearstar_nop;

    while (n < nearstar_nob) {
        q          = 0;
        c          = nearstar_p_owner[n];
        key_radius = nearstar_p_ray[c] * moon_orb_scaling;

        while (n < nearstar_nob && nearstar_p_owner[n] == c) {
            nearstar_p_ray[n] =
                avg_planet_ray[nearstar_p_type[n]] +
                avg_planet_ray[nearstar_p_type[n]] * zrandom(100) / 200;
            nearstar_p_ray[n] *= avg_moon_sizing;
            nearstar_p_orb_ray[n] =
                key_radius + key_radius * zrandom(100) / 250;
            nearstar_p_orb_ray[n] +=
                key_radius * avg_planet_ray[nearstar_p_type[n]];

            if (q < 2) {
                key_radius += nearstar_p_orb_ray[n];
            }

            if (q >= 2 && q < 8) {
                key_radius += 0.12 * nearstar_p_orb_ray[n];
            }

            if (q >= 8) {
                key_radius += 0.025 * nearstar_p_orb_ray[n];
            }

            q++;
            n++;
        }
    }

    /* Eliminazione di anelli improbabili. */

    for (n = 0; n < nearstar_nop; n++) {
        // A meno di un raggio e mezzo dal centro del pianeta,
        // sar� un po' difficile trovarci un anello stabile.
        nearstar_p_ring[n] = 0.75 * nearstar_p_ray[n] * (2 + brtl_random(3));
        // I pianeti piccoli raramente hanno degli anelli.
        // Non hanno abbastanza massa per frantumare
        // una luna che arrivi troppo vicina.
        s = nearstar_p_type[n];

        if (s != 6 && s != 9) {
            if (brtl_random(5)) {
                nearstar_p_ring[n] = 0;
            }
        } else {
            if (brtl_random(2)) {
                nearstar_p_ring[n] = 0;
            }
        }
    }

    /* Conteggio degli oggetti che hanno un nome (suggerimento di Ryan) */
    nearstar_labeled = 0;

    for (n = 1; n <= nearstar_nob; n++) {
        if (search_id_code(nearstar_identity + n, 'P') != -1) {
            nearstar_labeled++;
        }
    }

    /*  Reset dei periodi di rotazione
        (vengono calcolati con la superficie) */

    for (n = 0; n < nearstar_nob; n++) {
        nearstar_p_rtperiod[n] = 0;
    }
}

// Smooth the surface of a planet: fast 4x4 average.

void ssmooth(uint8_t *target) {
    uint32_t limit = ((uint32_t) QUADWORDS << 2u) - (360u << 2u);

    for (uint32_t i = 0; i < limit; i++) {
        // 4 columns of 4 pixels each.
        uint8_t col1, col2, col3, col4, average;

        col1 = target[i] + target[i + 360] + target[i + 720] + target[i + 1080];

        col2 = target[i + 1] + target[i + 361] + target[i + 721] +
               target[i + 1081];

        col3 = target[i + 2] + target[i + 362] + target[i + 722] +
               target[i + 1082];

        col4 = target[i + 3] + target[i + 363] + target[i + 723] +
               target[i + 1083];

        col1 = (col1 & 0xFCu) / 4;
        col2 = (col2 & 0xFCu) / 4;
        col3 = (col3 & 0xFCu) / 4;
        col4 = (col4 & 0xFCu) / 4;

        average = col1 + col2 + col3 + col4;
        average /= 4;
        target[i + 360] = average;
    }
}

/* Smooth the surface of a planet slightly: 2x2 average. */
void lssmooth(uint8_t *target) {
    // Offset limit by additional -1 because valgrind told me this ran over.
    uint32_t limit = ((((uint32_t) QUADWORDS) - 80) << 2u) - 1;

    for (uint32_t i = 0; i < limit; i++) {
        uint8_t sample = target[i] & 0xC0u;

        uint8_t dl = target[i] & 0x3Fu;
        uint8_t dh = target[i + 1] & 0x3Fu;

        uint8_t bl = target[i + 360] & 0x3Fu;
        uint8_t bh = target[i + 361] & 0x3Fu;

        uint8_t average = (dl + dh + bl + bh) / 4;

        sample |= average;
        target[i] = sample;
    }
}

int16_t gr, r, g, b, cr, cx, cy;
float a, kfract = 2;
int8_t lave, crays;
uint16_t px, py;

/* Modular functions to detail surfaces. Called only from surface. The
 * parameters are passed in used variables: c, gr, r, g, b, cr, cx, cy, lave,
 * crays, px, py, and a.
 *
 * kfract is the density of fractures on the planets. It is placed at 1 to make
 * lightning in the sky.
 *
 * They all operate on p_background even though, at the time of definition of
 * the surface of a moon, p_background will be exchanged with s_background,
 * which initially is the map of the star surface. The fact that a moon is
 * likely to see the planet around which it orbits means we must separate the
 * planetary and lunar map. We are not worried however, about having more than
 * two visible bodies, because:
 *
 *      - The first and second planet of any non-star cannot, by convention,
 *      have any moons. On the other hand, since the star surface is not visible
 *      in detail from the third planet on, it can be approximated by a white
 *      globe.
 *
 *      - The moons visible from another moon always appear rather small, so it
 *      is not possible to see the details of the surface of one moon from the
 *      point of view of another.
 *
 * Finally, the same considerations on surface maps apply to color maps: The
 * color map of the star is swapped out for that of the moon.
 */

// A small light spot on the surface.
void spot() {
    uint8_t color = p_background[(uint16_t)(py + px)] + gr;
    if (color > 0x3E) {
        color = 0x3E;
    }
    p_background[(uint16_t)(py + px)] = color;
}

// Permanent storm (a colossal stain).
void permanent_storm() {
    for (g = 1; g < cr; g++) {
        for (a = 0; a < 2 * M_PI; a += 4 * deg) {
            px = (uint16_t)(cx + g * cos((double) a));
            py = (uint16_t)(cy + g * sin((double) a));
            py *= 360;
            spot();
        }
    }
}

// A crater.
void crater() {
    for (a = 0; a < 2 * M_PI; a += 4 * deg) {
        for (gr = 0; gr < cr; gr++) {
            px   = cx + cos((double) a) * gr;
            py   = cy + sin((double) a) * gr;
            vptr = px + 360 * py;

            uint8_t color       = p_background[vptr];
            uint8_t colorOffset = gr >> lave;
            if (color >= colorOffset) {
                p_background[vptr] = color - colorOffset;
            } else {
                p_background[vptr] = 0;
            }
        }

        p_background[vptr]     = 0x3E;
        p_background[vptr + 1] = 0x01;

        if (crays && !brtl_random(crays)) {
            b = (2 + brtl_random(2)) * cr;

            if (cy - b > 0 && cy + b < 179) {
                for (gr = cr + 1; gr < b; gr++) {
                    px   = cx + cos((double) a) * gr;
                    py   = cy + sin((double) a) * gr;
                    vptr = px + 360 * py;

                    uint8_t color = p_background[vptr] + ((uint8_t) cr);
                    if (color > 0x3E) {
                        color = 0x3E;
                    }
                    p_background[vptr] = color;
                }
            }
        }
    }
}

// Horizontal dark band: Can be made light be negating the surface from 0x3E
void band() {
    for (uint16_t i = cr, j = py; i > 0; i--, j++) {
        uint8_t color = p_background[j];
        if (color >= g) {
            color -= g;
        } else {
            color = 0;
        }
        p_background[j] = color;
    }
}

// A band, like the above but wavy.
void wave() {
    for (uint16_t i = 360; i > 0; i--) {
        py                  = ((uint16_t) round(cr * sin(a * i))) + cy;
        uint16_t index      = ((uint16_t)(py * 360)) + i;
        p_background[index] = 0;
    }
}

void fracture(uint8_t *target, float max_latitude) {
    /* Dark furrow: like the lines on Europe. Has parameters because it is also
     * used to simulate lightning when it rains on the surface of habitable
     * planets.
     */
    int16_t rand0 = brtl_random(360);
    a             = (float) (rand0 * deg);
    gr++;
    float px = cx;
    float py = cy;

    do {
        a += (float) ((brtl_random(g) - brtl_random(g)) *
                      deg); // NOLINT(misc-redundant-expression)
        px += kfract * cos(a);

        if (px > 359) {
            px -= 360;
        }

        if (px < 0) {
            px += 360;
        }

        py += kfract * sin((double) a);

        if (py > max_latitude - 1) {
            py -= max_latitude;
        }

        if (py < 0) {
            py += max_latitude;
        }

        vptr = px + (float) (360 * (uint16_t) py);
        target[vptr] >>= (uint8_t) b;
        gr--;
    } while (gr);
}

void volcano() { // un krakatoa volcano con Gedeone il gigante coglione.
    for (a = 0; a < 2 * M_PI; a += 4 * deg) {
        b = gr;

        for (g = cr / 2; g < cr; g++) {
            px = (uint16_t)(cx + cos((double) a) * g);
            py = (uint16_t)(cy + sin((double) a) * g);
            py *= 360;
            spot();
            gr--;

            if (gr < 0) {
                gr = 0;
            }
        }

        gr = b;
    }
}

void contrast(float kt, float kq, float thrshld) {
    uint16_t c;

    for (c = 0; c < 64800; c++) {
        a = p_background[c];
        a -= thrshld;

        if (a > 0) {
            a *= kt;
        } else {
            a *= kq;
        }

        a += thrshld;

        if (a < 0) {
            a = 0;
        }

        if (a > 63) {
            a = 63;
        }

        p_background[c] = (uint8_t) a;
    }
}

void randoface(int16_t range, int16_t upon) {
    uint16_t c;

    for (c = 0; c < 64800; c++) {
        gr = p_background[c];

        if ((upon > 0 && gr >= upon) || (upon < 0 && gr <= -upon)) {
            gr += brtl_random(range);
            gr -= brtl_random(range);

            if (gr > 63) {
                gr = 63;
            }

            if (gr < 0) {
                gr = 0;
            }

            p_background[c] = gr;
        }
    }
}

void negate() {
    for (uint16_t i = 64800, j = 0; i > 0; i--, j++) {
        p_background[j] = 0x3E - p_background[j];
    }
}

void crater_juice() {
    lave  = brtl_random(3);
    crays = brtl_random(3) * 2;

    for (int16_t c = 0; c < r; c++) {
        cx = brtl_random(360);
        cr = 2 + brtl_random(1 + r - c);

        while (cr > 20) {
            cr -= 10;
        }

        cy = brtl_random(178 - 2 * cr) + cr;
        crater();

        if (cr > 15) {
            lssmooth(p_background);
        }
    }
}

/* Atmospheric mapping functions. They work like the previous ones, but operate
 * on "objectschart" instead of on "p_background", and at halved resolution.
 * Moreover, the existence of albedo is VERY IMPORTANT if the clouds do not go
 * from 0x00 to 0x3E but rather from 0x00 to 0x1F. That is because at the time
 * of descent on the surface, the average albedo of p_background is used to
 * determine, on habitable planets, if the player is landing on the sea or not.
 * Since the albedo of p_background is altered by that of the clouds contained
 * in objectschart, it is restored when the landing position is chosen, from the
 * "planets" function, by subtracting the clouds albedo from that of the landing
 * position's p_background. If, however, the alteration due to the clouds is
 * left, and the albedo is based on 0x00 to 0x3E, there is a risk of having an
 * overflow, which could result in improper ocean landing calculations. The
 * result would be that in an area normally covered with earth, a large cloud
 * passing over would cause it to become sea.
 */

// A small light spot (bright cloud).
void cirrus() {
    uint16_t index = ((uint16_t)(py + px)) / 2;
    uint8_t val    = ((uint8_t *) objectschart)[index] + gr;
    if (val > 0x1F) {
        val = 0x1F;
    }

    ((uint8_t *) objectschart)[index] = val;
}

// Atmospheric cyclone: a cluster of spiral clouds.
void atm_cyclon() {
    b = 0;

    while (cr > 0) {
        px = cx + cr * cos(a);
        py = cy + cr * sin(a);
        py *= 360;
        cirrus();
        px += brtl_random(4);
        cirrus();
        py += 359;
        cirrus();
        px -= brtl_random(4);
        cirrus();
        py += 361;
        cirrus();
        px += brtl_random(4);
        cirrus();
        b++;
        b %= g;

        if (!b) {
            cr--;
        }

        a += 6 * deg;
    }
}

void storm() { // tempesta (una grande macchia chiara sull'atmosfera).
    for (g = 1; g < cr; g++) {
        for (a = 0; a < 2 * M_PI; a += 4 * deg) {
            px = (uint16_t)(cx + (int16_t)(g * cos((double) a)));
            py = (uint16_t)(cy + (int16_t)(g * sin((double) a)));
            py *= 360;
            cirrus();
        }
    }
}

/* Calculate the surface by extapolating it from the data on the planet and from
 * the pseudo-random table assigned to it. Includes the day-night terminator by
 * darkening the night hemisphere for an angle of 130 (not 180 due to the
 * diffused light and the reduced field at the edges of the globes). "colorbase"
 * is assigned to 192 for the planets, to 128 for the moons.
 */

void surface(int16_t logical_id, int16_t type, double seedval,
             uint8_t colorbase) {
    int16_t plwp, c;
    uint16_t seed = 0;
    int8_t knot1  = 0, brt;
    int16_t QW    = QUADWORDS;
    float r1, r2, r3, g1, g2, g3, b1, b2, b3;
    uint8_t *overlay = (uint8_t *) objectschart;

    if (type == 10) {
        return; // Companion star: has star surface...
    }

    /* Setting of the rotation period. "rotation" represents the current
     * rotation of the planet, in degrees, from 0 to 359. The rotation period is
     * extracted in a very wide range, with 1 second resolution.
     */
    fast_srand(((int32_t)(uint32_t) seedval) + 4112);

    /* "rtperiod" is the time, in seconds, that it takes the planet to rotate
     * one degree on its axis. The time taken for a complete rotation is
     * therefore 360 * rtperiod.
     */
    nearstar_p_rtperiod[logical_id] = 10.0 * (ranged_fast_random(50) + 1) +
                                      10.0 * ranged_fast_random(25) +
                                      ranged_fast_random(250) + 41;
    nearstar_p_rotation[logical_id] = secs / nearstar_p_rtperiod[logical_id];
    nearstar_p_rotation[logical_id] %= 360;

    /* Calculation of the planet's current orientation for the masking of the
     * dark side (with respect to the position of the star).
     */
    plwp = 89 - cplx_planet_viewpoint(logical_id);
    plwp += nearstar_p_rotation[logical_id];
    plwp %= 360;

    if (plwp < 0) {
        plwp += 360;
    }

    /* Selection of the pseudo-table relative to this planet. The pseudo-table
     * of the "random" function in C++ has a fair probability of recurrence, but
     * with "ranged_fast_random", the recurrence is cancelled
     * ("ranged_fast_random" has a huge amount of tables).
     *
     * NOTE: The above comment is preserved for posterity, but its statements on
     * the standard library random functions are not necessarily accurate.
     */
    fast_srand((int32_t)(uint32_t)(seedval * 10));
    seed = fast_random(0xFFFF);

    /* Preparation of a standard surface (random pattern 0 .. 62): it is then
     * processed according to the type of planet.
     */
    brtl_srand(seed);
    int16_t currSeed = seed;
    for (uint16_t i = 64800, j = 0; i > 0; i--, j++) {
        currSeed += i;
        int32_t result  = ((int32_t) currSeed) * ((int32_t) currSeed);
        auto resultHigh = static_cast<int16_t>(result >> 16u);
        auto resultLow  = static_cast<int16_t>(result & 0xFFFFu);
        currSeed        = resultLow + resultHigh;
        uint8_t color   = currSeed & 0xFFu;
        color &= 0x3Eu;
        p_background[j] = color;
    }

    /* Preparation of the overlay for mapping the changes in the atmosphere: it
     * is initially reset, as it must be subsequently reworked according to the
     * type of planet. Obviously the planet is not reworked if it has no
     * atmosphere.
     */
    memset(overlay, 0, 32400);

    /* Specific surface processing. Atmosphere overlay processing, if there is
     * a need for it, is also done.
     */
    brtl_srand(seed);
    QUADWORDS = 16200;

    int16_t rVal0 = 0, rVal1 = 0, rVal2 = 0;
    switch (type) {
    case 0:
        r = ranged_fast_random(3) + 5;

        for (c = 0; c < r; c++) {
            ssmooth(p_background);
        }

        for (uint16_t i = 64800, j = 0; i > 0; i--, j++) {
            if (p_background[j] >= 28) {
                p_background[j] = 62;
            }
        }

        r = ranged_fast_random(5) + 5;

        for (c = 0; c < r; c++) {
            ssmooth(p_background);
        }

        r = 5 + ranged_fast_random(26);

        for (c = 0; c < r; c++) {
            cr = 5 + ranged_fast_random(20);
            cx = ranged_fast_random(360);
            cy = ranged_fast_random(130) + 25;
            gr = ranged_fast_random(cr / 2) + cr / 2 + 2;
            volcano();
        }

        r = 100 + ranged_fast_random(100);
        b = ranged_fast_random(3) + 1;
        g = 360;

        for (c = 0; c < r; c++) {
            cx = ranged_fast_random(360);
            cy = ranged_fast_random(180);
            gr = ranged_fast_random(100);
            fracture(p_background, 180);
        }

        lssmooth(p_background);
        break;

    case 1:
        if (ranged_fast_random(2)) {
            ssmooth(p_background);
        }

        r = 10 + ranged_fast_random(41);
        crater_juice();
        lssmooth(p_background);

        if (!ranged_fast_random(5)) {
            negate();
        }

        break;

    case 2:
        r = 5 + ranged_fast_random(25);

        for (c = 0; c < r; c++) {
            cr = ranged_fast_random(20) + 1;
            cy = ranged_fast_random(178 - 2 * cr) + cr;

            switch (brtl_random(2)) {
            case 0:
                cx = (((int32_t)(uint32_t)(10 * secs)) /
                      (ranged_fast_random(3600) + 180)) %
                     360;
                gr = ranged_fast_random(12) + 2;
                storm();
                break;

            case 1:
                gr = ranged_fast_random(15) + 3;
                py = cy * 360;
                cr *= 360;
                g = 1 + ranged_fast_random(gr);
                band();
            }
        }

        if (!ranged_fast_random(3)) {
            negate();
        }

        break;

    case 3:
        r = ranged_fast_random(3) + 4;
        g = 26 + ranged_fast_random(3) - ranged_fast_random(5);

        for (c = 0; c < r; c++) {
            ssmooth(p_background);
        }

        currSeed = seed;
        for (uint16_t i = 64000, j = 0; i > 0; i--, j++) {
            if (p_background[j] >= g) {
                currSeed += i;
                int32_t result  = ((int32_t) currSeed) * ((int32_t) currSeed);
                auto resultHigh = static_cast<int16_t>(result >> 16u);
                auto resultLow  = static_cast<int16_t>(result & 0xFFFFu);
                currSeed        = resultLow + resultHigh;
                uint8_t color   = currSeed & 0xFFu;
                color &= 0x3Eu;
                p_background[j] = color;
                if (p_background[j] > 0x3E) {
                    p_background[j] = 0x3E;
                }
            } else {
                p_background[j] = 16;
            }
        }

        r = 20 + ranged_fast_random(40);

        for (c = 0; c < r; c++) {
            gr = ranged_fast_random(5) + 1;
            cr = ranged_fast_random(10) + 10;

            if (ranged_fast_random(3)) {
                cy = ranged_fast_random(172 - 2 * cr) + cr + 2;
            } else {
                cy = 60 + ranged_fast_random(10) - ranged_fast_random(10);
            }

            cx = ((int32_t)(secs) / (ranged_fast_random(360) + 180)) % 360;
            g  = ranged_fast_random(5) + 7;
            a  = ranged_fast_random(360) * deg;
            atm_cyclon();
        }

        break;

    case 4:
        ssmooth(p_background);

        if (ranged_fast_random(2)) {
            ssmooth(p_background);
        }

        for (uint16_t i = 64000, j = 0; i > 0; i--, j++) {
            if (p_background[j] == 32) {
                p_background[j]       = 0x01;
                p_background[j + 1]   = 0x3E;
                p_background[j + 360] = 0x01;
            }
        }

        r = ranged_fast_random(30);

        if (r > 20) {
            r *= 10;
        }

        b = ranged_fast_random(3) + 1;
        g = 200 + ranged_fast_random(300);

        for (c = 0; c < r; c++) {
            cx = ranged_fast_random(360);
            cy = ranged_fast_random(180);
            gr = 50 + ranged_fast_random(100);
            fracture(p_background, 180);
        }

        r = ranged_fast_random(25) + 1;
        crater_juice();
        lssmooth(p_background);

        if (ranged_fast_random(2)) {
            lssmooth(p_background);
        }

        break;

    case 5:
        r = ranged_fast_random(3) + 4;

        for (c = 0; c < r; c++) {
            ssmooth(p_background);
        }

        /* These have been pulled out of the function call b/c the borland
         * compiler evaluated them the other way around.
         */
        rVal0 = ranged_fast_random(3);
        rVal1 = ranged_fast_random(350);
        rVal2 = ranged_fast_random(200);
        contrast((float) ((float) rVal2 / 900 + 0.6),
                 (float) ((float) rVal1 / 100 + 4.0), (float) (25 + rVal0));
        rVal0 = ranged_fast_random(3);
        rVal1 = ranged_fast_random(3);
        randoface(5 + rVal1, -20 * (rVal0 + 1));
        r = 5 + ranged_fast_random(5);

        for (c = 0; c < r; c++) {
            cr = 5 + ranged_fast_random(10);
            cx = ranged_fast_random(360);
            cy = ranged_fast_random(145) + 15;
            gr = ranged_fast_random(cr / 2) + 2;
            volcano();
        }

        r = 5 + ranged_fast_random(5);

        for (c = 0; c < r; c++) {
            cr = ranged_fast_random(30) + 1;
            cy = ranged_fast_random(178 - 2 * cr) + cr;
            cx =
                ((int32_t)(60 * secs) / (ranged_fast_random(3600) + 360)) % 360;
            gr = ranged_fast_random(2) + 1;
            permanent_storm();
        }

        for (c = 0; c < 10000; c++) {
            gr = ranged_fast_random(10) + 10;
            px = ranged_fast_random(360);
            py = ranged_fast_random(10);
            py *= 360;
            spot();
            px = ranged_fast_random(360);
            py = 125 - ranged_fast_random(10);
            py *= 360;
            spot();
        }

        if (ranged_fast_random(2)) {
            ssmooth(p_background);
        } else {
            lssmooth(p_background);
        }

        break;

    case 6:
        r = 3 + ranged_fast_random(5);

        for (c = 0; c < r; c++) {
            ssmooth(p_background);
        }

        r = 50 + ranged_fast_random(100);

        for (c = 0; c < r; c++) {
            cr = ranged_fast_random(10) + 1;
            cy = ranged_fast_random(178 - 2 * cr) + cr;

            if (ranged_fast_random(8)) {
                gr = ranged_fast_random(5) + 2;
                g  = 1 + ranged_fast_random(gr);
                py = cy * 360;
                cr *= 360;
                band();
            } else {
                a  = (float) (5 + ranged_fast_random(10)) / 30;
                cr = cr / 4 + 1;
                wave();
            }
        }

        r = 50 + ranged_fast_random(100);

        for (c = 0; c < r; c++) {
            cr = ranged_fast_random(15) + 1;
            cy = ranged_fast_random(178 - 2 * cr) + cr;
            cx =
                ((int32_t)(60 * secs) / (ranged_fast_random(8000) + 360)) % 360;
            gr = ranged_fast_random(2) + 1;

            if (ranged_fast_random(10)) {
                cr = cr / 2 + 1;
            } else {
                gr *= 3;
            }

            storm();
        }

        lssmooth(p_background);

        if (!ranged_fast_random(3)) {
            negate();
        }

        break;

    case 7:
        r = 5 + ranged_fast_random(5);

        for (c = 0; c < r; c++) {
            ssmooth(p_background);
        }

        r = 10 + ranged_fast_random(50);
        g = 5 + ranged_fast_random(20);
        b = ranged_fast_random(2) + 1;

        for (c = 0; c < r; c++) {
            cx = ranged_fast_random(360);
            cy = ranged_fast_random(180);
            gr = ranged_fast_random(300);
            fracture(p_background, 180);
        }

        if (ranged_fast_random(2)) {
            lssmooth(p_background);
        }

        randoface(1 + ranged_fast_random(10), 1);

        if (ranged_fast_random(2)) {
            negate();
        }

        break;

    case 8:
        r = ranged_fast_random(10) + 1;

        for (c = 0; c < r; c++) {
            lssmooth(p_background);
        }

        r = 100 + ranged_fast_random(50);

        for (c = 0; c < r; c++) {
            cr = ranged_fast_random(5) + 1;
            gr = ranged_fast_random(5) + 1;
            cx = ranged_fast_random(360);
            cy = ranged_fast_random(178 - 2 * cr) + cr;
            permanent_storm();
        }

        if (ranged_fast_random(2)) {
            negate();
        }

        break;

    case 9:
        memset(adapted, 0x1F, QUADWORDS * 4);

        for (px = 0; px < 32400; px++) {
            overlay[px] = 0x1F;
        }

        break;
    default:
        break;
    }

    /* Surface renormalization at interval 0x00..0x1F: Only if the planet's
     * atmosphere doesn't have an effect on the appearance of the underlying
     * surface, then for Felisian / Mars-like planets.
     */
    if (type == 3 || type == 5) {
        for (px = 0; px < 64800; px++) {
            p_background[px] >>= 1u;
        }
    }

    // Specific final touches to the surface for Felisian planets.
    if (type == 3) {
        if (ranged_fast_random(2)) {
            lssmooth(p_background);
        } else {
            ssmooth(p_background);
        }
    }

    /* Terrain map + atmosphere overlay fusion and renormalization of the
     * terrain map so that it adapts to the range 0x00..0x1F.
     */
    for (px = 0, py = 0; px < 32400; py += 2, px++) {
        p_background[py] += overlay[px];

        if (p_background[py] > 0x3E) {
            p_background[py] = 0x3E;
        }

        p_background[py + 1] += overlay[px];

        if (p_background[py + 1] > 0x3E) {
            p_background[py + 1] = 0x3E;
        }
    }

    // Specific final touches to the surface for Venusian planets.
    if (type == 2) {
        if (!brtl_random(3)) {
            psmooth_grays(p_background);
            knot1 = 1;
        }
    }

    // Day-night terminator application.
    nearstar_p_term_start[logical_id] = plwp + 35;

    if (nearstar_p_term_start[logical_id] >= 360) {
        nearstar_p_term_start[logical_id] -= 360;
    }

    nearstar_p_term_end[logical_id] = nearstar_p_term_start[logical_id] + 130;

    if (nearstar_p_term_end[logical_id] >= 360) {
        nearstar_p_term_end[logical_id] -= 360;
    }

    for (uint16_t i = 179, j = (plwp + 35); i > 0; i--, j += 230) {
        for (uint16_t k = 130; k > 0; k--) {
            p_background[j] >>= 2u;
            j++;
        }
    }

    // Specific final touches to the surface for other planets.
    if (type == 2) {
        if (knot1) {
            ssmooth(p_background);
        } else {
            r = 3 + ranged_fast_random(5);

            for (c = 0; c < r; c++) {
                ssmooth(p_background);
            }
        }
    }

    if (type == 6) {
        for (c = 0; c < 3; c++)
            if (ranged_fast_random(2)) {
                ssmooth(p_background);
            }
    }

    if (type == 9)
        for (c = 0; c < 6; c++) {
            ssmooth(p_background);
        }

    // Color table processing (redefines from 192 to 255).
    if (colorbase == 255) {
        QUADWORDS = QW;
        return;
    }

    type = ((uint16_t) type) << 2;
    r    = planet_rgb_and_var[type + 0];
    g    = planet_rgb_and_var[type + 1];
    b    = planet_rgb_and_var[type + 2];
    c    = planet_rgb_and_var[type + 3];
    r <<= 1;
    r += nearstar_r;
    r >>= 1;
    g <<= 1;
    g += nearstar_g;
    g >>= 1;
    b <<= 1;
    b += nearstar_b;
    b >>= 1;
    r1 = r + brtl_random(c) - brtl_random(c);
    g1 = g + brtl_random(c) - brtl_random(c);
    b1 = b + brtl_random(c) - brtl_random(c);
    r2 = r + brtl_random(c) - brtl_random(c);
    g2 = g + brtl_random(c) - brtl_random(c);
    b2 = b + brtl_random(c) - brtl_random(c);
    r3 = r + brtl_random(c) - brtl_random(c);
    g3 = g + brtl_random(c) - brtl_random(c);
    b3 = b + brtl_random(c) - brtl_random(c);
    r1 *= 0.25;
    g1 *= 0.25;
    b1 *= 0.25;
    r2 *= 0.75;
    g2 *= 0.75;
    b2 *= 0.75;
    r3 *= 1.25;
    g3 *= 1.25;
    b3 *= 1.25;
    type >>= 2;
    shade(tmppal, colorbase + 00, 16, 00, 00, 00, r1, g1, b1);
    shade(tmppal, colorbase + 16, 16, r1, g1, b1, r2, g2, b2);
    shade(tmppal, colorbase + 32, 16, r2, g2, b2, r3, g3, b3);
    shade(tmppal, colorbase + 48, 16, r3, g3, b3, 64, 64, 64);
    brt = nearstar_p_owner[logical_id];

    if (brt == -1) {
        brt = logical_id;
    }

    if (brt <= 4) {
        brt = 64;
    } else {
        brt = 64 - (4 * (brt - 4));
    }

    tavola_colori(tmppal + 3 * colorbase, colorbase, 64, brt, brt, brt);
    QUADWORDS = QW;
}

/* Tracciamento degli anelli (eventuali). */

void ring(int16_t planet_id, double ox, double oy, double oz, int16_t start,
          int16_t layers) {
    int16_t a, b, c, n, m, partn, partcls;
    double sx, sy, sz;
    double ringray  = nearstar_p_ring[planet_id];
    double ringtilt = 0.1 * ringray * nearstar_p_tilt[planet_id];
    double interval = 0.0075 * ringray;
    fast_srand((int32_t)(10000 * ringray + planet_id));
    b       = 1 + fast_random(0x1F) - layers;
    partcls = 1 + fast_random(3);

    while (b > 0) {
        if (!fast_random(7)) {
            c             = 1 + fast_random(3);
            pixel_spreads = 0;
        } else {
            c             = 1 + fast_random(7);
            pixel_spreads = 1;
        }

        a                 = start - (start % c);
        pixilating_effect = fast_random(1) + fast_random(1);

        if (a < 0) {
            a += 360;
        }

        n = c;

        while (n + c < 180) {
            m = c + fast_random(1);
            n += m;
            a += m;

            if (a > 360) {
                a -= 360;
            }

            sy    = oy - ringtilt * lft_sin[a];
            sx    = ox + ringray * lft_sin[a];
            sz    = oz + ringray * lft_cos[a];
            partn = partcls;

            while (partn) {
                sz += interval - (fast_flandom() * interval);
                sx += interval - (fast_flandom() * interval);
                far_pixel_at(sx, sy, sz, -0.042, 0);
                partn--;
            }
        }

        ringray += interval;

        if (!fast_random(7)) {
            ringray += 5 * interval;
        }

        ringtilt = 0.1 * ringray * nearstar_p_tilt[planet_id];
        b--;
    }

    pixilating_effect = LIGHT_EMITTING;
    pixel_spreads     = 1;
}

/*  Visualizza appopriatamente i pianeti, come punti, barlumi di luce
    o globi ben visibili, a seconda di distanza e raggio. C'� un terzo
    modo in cui un corpo planetario pu� rendersi visibile: con una falce.
    L'effetto falce viene realizzato da "glowing_globe". */

void planets() {
    auto *atmosphere     = (int8_t *) objectschart;
    auto *surface_backup = (uint8_t *) p_background;
    int8_t is_moon;
    int32_t poffs;
    int32_t test;
    int16_t i1, i2, n1, n2, c1, c2, pnpcs;
    int16_t c, n, t, ts, te, ll, plwp = 0, riwp;
    int16_t te_ll_distance, te_ll_distance_1, te_ll_distance_2;
    int16_t ts_ll_distance, ts_ll_distance_1, ts_ll_distance_2;
    double xx, yy, zz;
    double d3, d2, md2 = 1E9;
    uint8_t colorbase, showdisc, showrings, surfacemap;
    int16_t ringlayers = 0;

    if (ip_targetting) {
        ip_targetted = -1;
    }

    if (!nearstar_nop) {
        return;
    }

    for (n = 0; n < nearstar_nob; n++) {
        planet_xyz(n);
        xx                       = plx - dzat_x;
        yy                       = ply - dzat_y;
        zz                       = plz - dzat_z;
        nearstar_p_qsortindex[n] = n;
        nearstar_p_qsortdist[n]  = sqrt(xx * xx + yy * yy + zz * zz);
    }

    quick_sort(nearstar_p_qsortindex, nearstar_p_qsortdist, 0,
               nearstar_nob - 1);

    if (nearstar_nob == 1) {
        pnpcs = npcs;
        npcs  = 0;

        if (npcs != pnpcs) {
            resident_map1 = 0;
            resident_map2 = -1;
        }
    } else {
        pnpcs = npcs;
        n1    = nearstar_nob - 1;
        i1    = nearstar_p_qsortindex[n1];
        c1    = nearstar_p_owner[i1];
        n2    = nearstar_nob - 2;
        i2    = nearstar_p_qsortindex[n2];
        c2    = nearstar_p_owner[i2];

        if (c1 > -1) {
            while (c2 > -1) {
                n2--;
                i2 = nearstar_p_qsortindex[n2];
                c2 = nearstar_p_owner[i2];
            }
        }

        npcs = i1 * maxbodies - i2;

        if (npcs != pnpcs) {
            resident_map1 = i1;
            resident_map2 = i2;
        }
    }

    for (c = 0; c < nearstar_nob; c++) {
        n = nearstar_p_qsortindex[c];
        //
        d3 = nearstar_p_qsortdist[n];
        planet_xyz(n);

        if (nearstar_p_owner[n] > -1) {
            p_background = s_background;
            colorbase    = 128;
            is_moon      = 1;
        } else {
            p_background = surface_backup;
            colorbase    = 192;
            is_moon      = 0;
        }

        showdisc   = 0;
        showrings  = 0;
        surfacemap = 0;

        if (d3 < 250 * nearstar_p_ray[n]) {
            showrings  = 1;
            ringlayers = (int16_t)(0.05 * (d3 / nearstar_p_ray[n]));

            if (d3 < 100 * nearstar_p_ray[n]) {
                showdisc = 1;

                if (d3 < 25 * nearstar_p_ray[n]) {
                    surfacemap = 1;
                }
            }
        }

        //
        if (ip_targetting || !showdisc) {
            far_pixel_at(plx, ply, plz, nearstar_p_ray[n], 0);

            if (ip_targetting) {
                pxx -= VIEW_X_CENTER;
                pyy -= VIEW_Y_CENTER;
                d2 = pxx * pxx + pyy * pyy;

                if (d2 < md2) {
                    md2          = d2;
                    ip_targetted = n;
                }
            }
        }

        //
        if (nearstar_p_type[n] == 10) {
            goto notaplanet;
        }

        //
        if (showrings) {
            if (surfacemap) {
                multicolourmask = 0xC0;
            } else {
                multicolourmask = 0x40;
            }

            plwp = 359 - planet_viewpoint(dzat_x, dzat_z);

            if (nearstar_p_ring[n] != 0.0) {
                riwp = plwp + 180;

                if (riwp > 359) {
                    riwp -= 360;
                }

                ring(n, plx, ply, plz, riwp, ringlayers);
            }
        }

        if (showdisc) {
            if (surfacemap) {
                if (n == resident_map1 || n == resident_map2) {
                    if (is_moon) {
                        if (nearstar_p_type[n]) {
                            surface(n, nearstar_p_type[n],
                                    1000000.0 * nearstar_ray *
                                        nearstar_p_type[n] *
                                        nearstar_p_orb_orient[n],
                                    128);
                        } else {
                            surface(n, nearstar_p_type[n],
                                    2000000.0 * n * nearstar_ray *
                                        nearstar_p_orb_orient[n],
                                    128);
                        }
                    } else {
                        if (nearstar_p_type[n]) {
                            surface(n, nearstar_p_type[n],
                                    1000000.0 * nearstar_p_type[n] *
                                        nearstar_p_orb_seed[n] *
                                        nearstar_p_orb_tilt[n] *
                                        nearstar_p_orb_ecc[n] *
                                        nearstar_p_orb_orient[n],
                                    192);
                        } else {
                            surface(n, nearstar_p_type[n],
                                    2000000.0 * n * nearstar_p_orb_seed[n] *
                                        nearstar_p_orb_tilt[n] *
                                        nearstar_p_orb_ecc[n] *
                                        nearstar_p_orb_orient[n],
                                    192);
                        }
                    }

                    if (n == resident_map1) {
                        resident_map1 = -1;
                    }

                    if (n == resident_map2) {
                        resident_map2 = -1;
                    }
                }

                if (n == ip_targetted && landing_point) {
                    nightzone = 0;
                    //
                    ts = nearstar_p_term_start[n];
                    te = nearstar_p_term_end[n];
                    ll = landing_pt_lon;

                    //
                    if (ts > te) {
                        if (ll >= ts || ll < te) {
                            nightzone = 1;
                        }
                    } else {
                        if (ll >= ts && ll < te) {
                            nightzone = 1;
                        }
                    }

                    //
                    te_ll_distance_1 = 0;
                    ll               = landing_pt_lon;

                    while (ll != te) {
                        te_ll_distance_1++;
                        ll++;

                        if (ll >= 360) {
                            ll = 0;
                        }
                    }

                    te_ll_distance_2 = 0;
                    ll               = landing_pt_lon;

                    while (ll != te) {
                        te_ll_distance_2++;
                        ll--;

                        if (ll <= -1) {
                            ll = 359;
                        }
                    }

                    if (te_ll_distance_1 < te_ll_distance_2) {
                        te_ll_distance = te_ll_distance_1;
                    } else {
                        te_ll_distance = te_ll_distance_2;
                    }

                    ts_ll_distance_1 = 0;
                    ll               = landing_pt_lon;

                    while (ll != ts) {
                        ts_ll_distance_1++;
                        ll++;

                        if (ll >= 360) {
                            ll = 0;
                        }
                    }

                    ts_ll_distance_2 = 0;
                    ll               = landing_pt_lon;

                    while (ll != ts) {
                        ts_ll_distance_2++;
                        ll--;

                        if (ll <= -1) {
                            ll = 359;
                        }
                    }

                    if (ts_ll_distance_1 < ts_ll_distance_2) {
                        ts_ll_distance = ts_ll_distance_1;
                    } else {
                        ts_ll_distance = ts_ll_distance_2;
                    }

                    if (ts_ll_distance <= te_ll_distance) {
                        sun_x_factor = +1;
                        crepzone     = ts_ll_distance;
                    } else {
                        sun_x_factor = -1;
                        crepzone     = te_ll_distance;
                    }

                    fast_srand((int32_t)(nearstar_p_orb_seed[n] *
                                         nearstar_p_orb_ecc[n] * 12345));
                    ptr            = 360 * landing_pt_lat + landing_pt_lon;
                    sky_red_filter = fast_random(31) + 32;
                    sky_grn_filter = fast_random(15) + 48;
                    sky_blu_filter = fast_random(15) + 48;

                    if (is_moon) {
                        gnd_red_filter =
                            tmppal[(3 * p_background[ptr]) + 128 * 3 + 0];
                        gnd_grn_filter =
                            tmppal[(3 * p_background[ptr]) + 128 * 3 + 1];
                        gnd_blu_filter =
                            tmppal[(3 * p_background[ptr]) + 128 * 3 + 2];
                    } else {
                        gnd_red_filter =
                            tmppal[(3 * p_background[ptr]) + 192 * 3 + 0];
                        gnd_grn_filter =
                            tmppal[(3 * p_background[ptr]) + 192 * 3 + 1];
                        gnd_blu_filter =
                            tmppal[(3 * p_background[ptr]) + 192 * 3 + 2];
                    }

                    gnd_red_filter += fast_random(15);
                    gnd_grn_filter += fast_random(15);
                    gnd_blu_filter += fast_random(15);
                    test = nearstar_p_type[n];

                    if (nightzone) {
                        albedo = p_background[ptr];
                        albedo <<= 2u;

                        if (test == 3 || test == 5) {
                            albedo -= atmosphere[ptr >> 1u];
                        }

                        albedo >>= 2u;
                        albedo <<= 2u;
                    } else {
                        albedo = p_background[ptr];

                        if (test == 3 || test == 5) {
                            albedo -= atmosphere[ptr >> 1u];
                        }

                        albedo >>= 2u;
                        albedo <<= 2u;
                    }

                    if (test == 3 || test == 5) {
                        albedo *= 2; // da 0 a 1F --> da 0 a 3F
                    }

                    rainy = (float) atmosphere[ptr >> 1u] * 0.25;

                    if (rainy > 5) {
                        rainy = 5;
                    }

                    if (nightzone) {
                        sky_grn_filter /= 2;
                        sky_blu_filter /= 2;

                        if (crepzone > 5) {
                            sky_red_filter /= 2;
                            sky_brightness = 8;
                        } else {
                            sky_brightness = 32;
                        }
                    } else {
                        if (crepzone > 5) {
                            sky_brightness = 48;
                        } else {
                            sky_grn_filter /= 2;
                            sky_blu_filter /= 3;
                            sky_brightness = 40;
                        }
                    }

                    for (poffs = -180; poffs < 180; poffs++) {
                        test = poffs + ptr;

                        if (test > 0 && test < 64800) {
                            p_background[test] ^= 0x1Eu;
                        }
                    }

                    for (poffs = -60; poffs < 60; poffs++) {
                        if (poffs) {
                            test = 360 * poffs + ptr;

                            if (test > 0 && test < 64800) {
                                p_background[test] ^= 0x1Eu;
                            }
                        }
                    }
                }

                t = nearstar_p_type[n];

                if (t == 2 || t == 3 || t == 6 || t == 8 || t == 9) {
                    glass_bubble = 1;
                } else {
                    glass_bubble = 0;
                }

                globe(plwp + nearstar_p_rotation[n], adapted, p_background,
                      (uint8_t *) n_globes_map, gl_bytes, plx, ply, plz,
                      nearstar_p_ray[n], colorbase, 0);

                if (n == ip_targetted && landing_point) {
                    for (poffs = -180; poffs < 180; poffs++) {
                        test = poffs + ptr;

                        if (test > 0 && test < 64800) {
                            p_background[test] ^= 0x1Eu;
                        }
                    }

                    for (poffs = -60; poffs < 60; poffs++) {
                        if (poffs) {
                            test = 360 * poffs + ptr;

                            if (test > 0 && test < 64800) {
                                p_background[test] ^= 0x1Eu;
                            }
                        }
                    }
                }
            } else {
                ts = (89 + 35) - cplx_planet_viewpoint(n);

                if (ts < 0) {
                    ts += 360;
                }

                if (ts > 359) {
                    ts -= 360;
                }

                glowing_globe(plwp, adapted, (uint8_t *) n_globes_map, gl_bytes,
                              plx, ply, plz, nearstar_p_ray[n], ts, 130, 127);
            }
        }

        if (showrings) {
            if (nearstar_p_ring[n] != 0.0) {
                ring(n, plx, ply, plz, plwp, ringlayers);

                if (!showdisc) {
                    far_pixel_at(plx, ply, plz, nearstar_p_ray[n], 0);
                }
            }
        }

    notaplanet:
        int abc123;
    }

    p_background = surface_backup;
}

/* Galactic Mapping
 *
 * Each star is assigned a unique identification code, resulting from its
 * coordinates. This code is referred to for the association of the names of the
 * stars. The identification codes of planets are calculated starting from their
 * star, plus the (progressive) number of the planet in order of distance.
 */

double laststar_x, laststar_y, laststar_z;

/* Determines whether a certain star, of which the id is specified, is currently
 * in sensor range. Return 1 when visible, 0 if not. When visible, the
 * coordinates of the star are reported in the variables laststar_x/y/z.
 */
int8_t isthere(double star_id) {
    int8_t visible_sectors = 9;
    int32_t sect_x, sect_y, sect_z;
    int32_t k, advance = 100000;
    double sidlow  = star_id - idscale;
    double sidhigh = star_id + idscale;
    uint8_t sx, sy, sz;
    double laststar_id;
    sect_x = (dzat_x - visible_sectors * 50000) / 100000;
    sect_x *= 100000;
    sect_y = (dzat_y - visible_sectors * 50000) / 100000;
    sect_y *= 100000;
    sect_z = (dzat_z - visible_sectors * 50000) / 100000;
    sect_z *= 100000;

    if (field_amplificator) {
        visible_sectors = 14;
    }

    k = 100000 * visible_sectors;

    for (sx = visible_sectors; sx > 0; sx--, sect_y -= k, sect_x += advance) {
        for (sy = visible_sectors; sy > 0;
             sy--, sect_z -= k, sect_y += advance) {
            for (sz = visible_sectors; sz > 0; sz--, sect_z += advance) {
                // TODO; Cleanup, rename properly. No teletubby names.
                int32_t eax = sect_x;
                int32_t edx = sect_z;

                eax += edx;
                int32_t ecx = eax;
                edx         = eax;
                edx &= 0x0001FFFF;

                edx += sect_x;
                edx -= 0xC350;
                laststar_x = edx;

                int64_t result = (int64_t) edx * (int64_t) eax;
                eax            = result & 0xFFFFFFFF;
                edx            = result >> 32;

                edx += eax;
                ecx += edx;
                edx &= 0x0001FFFF;

                edx += sect_y;
                edx -= 0xC350;
                laststar_y = edx;
                eax        = ecx;

                result = (int64_t) edx * (int64_t) eax;
                eax    = result & 0xFFFFFFFF;
                edx    = result >> 32;

                edx += eax;
                edx &= 0x0001FFFF;

                edx += sect_z;
                edx -= 0xC350;
                laststar_z = edx;

                laststar_x = round(laststar_x);
                laststar_y = round(laststar_y);
                laststar_z = round(laststar_z);

                laststar_id = (laststar_x * idscale) * (laststar_y * idscale) *
                              (laststar_z * idscale);

                if (laststar_id > sidlow && laststar_id < sidhigh) {
                    return 1;
                }
            }
        }
    }

    return 0;
}

/*  Ricerca tutte le stelle note visibili, fino a 50 contemporaneamente.
    Compila una tabella contenente l'ID di ogni stella e la sua
    posizione in coordinate Parsis. */

const int16_t tgt_bytes_per_scan = 5 * 32;
int32_t tgt_collect_lastpos      = 0;

int16_t targets           = 0;
int16_t topmost_target    = 0;
int16_t target_line       = 0;
int8_t update_targets     = 0;
int8_t collecting_targets = 0;

double targets_table_id[50];
double targets_table_px[50];
double targets_table_py[50];
double targets_table_pz[50];

void collect_targets() {
    uint16_t n, ptr, index, toread;
    int8_t *buffer_ascii  = (int8_t *) p_surfacemap;
    double *buffer_double = (double *) p_surfacemap;
    FILE* local_smh             = fopen(starmap_file, "r");

    if (local_smh != nullptr) {
        toread = tgt_bytes_per_scan;

        while (toread) {
            fseek(local_smh, tgt_collect_lastpos, SEEK_SET);
            n = fread(buffer_ascii, 1, toread, local_smh);

            if (!n) {
                collecting_targets = 0;
                goto stop;
            }

            ptr    = 0;
            index  = 0;
            toread = 0;

            while (ptr < n) {
                if (buffer_ascii[ptr + 29] == 'S') {
                    if (isthere(buffer_double[index])) {
                        targets_table_id[targets] = buffer_double[index];
                        targets_table_px[targets] = laststar_x;
                        targets_table_py[targets] = laststar_y;
                        targets_table_pz[targets] = laststar_z;

                        if (targets < 3) {
                            target_line = targets;
                        } else {
                            target_line = 2;
                        }

                        if (targets > 2) {
                            topmost_target = targets - 2;
                        }

                        update_targets = 1;
                        targets++;

                        if (targets == 50) {
                            collecting_targets = 0;
                            goto stop;
                        }
                    }
                } else {
                    toread += 32;
                }

                ptr += 32;
                index += 4;
                tgt_collect_lastpos += 32;
            }
        }

    stop:
        fclose(local_smh);
    }
}

/* Cambia lo stato visualizzato dall'FCS sull'Head-Up-Display. */

void status(const char *status_description, int16_t message_delay) {
    if (message_delay >= fcs_status_delay) {
        strcpy((char *) fcs_status, status_description);
        fcs_status_delay = message_delay;
    }
}

// Character map for the hud, 3x5 pixels.
int8_t digimap[65 * 5] = {
    0, 0, 0, 0, 0, // 32. ' '
    2, 2, 2, 0, 2, // 33. '!'
    5, 0, 0, 0, 0, // 34. '"'
    0, 0, 3, 5, 5, // 35. '#'
    2, 2, 6, 2, 2, // 36. sistro
    1, 4, 2, 1, 4, // 37. '%'
    0, 0, 2, 0, 0, // 38. e commericale (non � possibile visualizzarla)
    0, 2, 2, 0, 0, // 39. apice
    4, 2, 2, 2, 4, // 40. '('
    1, 2, 2, 2, 1, // 41. ')'
    0, 0, 7, 2, 2, // 42. '*'
    0, 2, 7, 2, 0, // 43. segno pi�
    0, 0, 0, 2, 1, // 44. ','
    0, 0, 7, 0, 0, // 45. '-'
    0, 0, 0, 0, 2, // 46. '.'
    0, 4, 2, 1, 0, // 47. barra destrorsa
    7, 5, 5, 5, 7, // 48. '0'
    3, 2, 2, 2, 7, // 49. '1'
    7, 4, 7, 1, 7, // 50. '2'
    7, 4, 6, 4, 7, // 51. '3'
    4, 6, 5, 7, 4, // 52. '4'
    7, 1, 7, 4, 7, // 53. '5'
    7, 1, 7, 5, 7, // 54. '6'
    7, 4, 4, 4, 4, // 55. '7'
    7, 5, 7, 5, 7, // 56. '8'
    7, 5, 7, 4, 4, // 57. '9'
    0, 2, 0, 2, 0, // 58. duepunti
    0, 2, 0, 2, 1, // 59. ';'
    4, 2, 1, 2, 4, // 60. '<'
    0, 7, 0, 7, 0, // 61. '='
    1, 2, 4, 2, 1, // 62. '>'
    7, 4, 6, 0, 2, // 63. '?'
    0, 2, 0, 0, 0, // 64. a commerciale (non visualizzabile)
    7, 5, 7, 5, 5, // 65. 'A'
    7, 5, 3, 5, 7, // 66. 'B'
    7, 1, 1, 1, 7, // 67. 'C'
    3, 5, 5, 5, 3, // 68. 'D'
    7, 1, 3, 1, 7, // 69. 'E'
    7, 1, 3, 1, 1, // 70. 'F'
    7, 1, 5, 5, 7, // 71. 'G'
    5, 5, 7, 5, 5, // 72. 'H'
    2, 2, 2, 2, 2, // 73. 'I'
    4, 4, 4, 5, 7, // 74. 'J'
    5, 5, 3, 5, 5, // 75. 'K'
    1, 1, 1, 1, 7, // 76. 'L'
    7, 7, 5, 5, 5, // 77. 'M'
    5, 7, 7, 5, 5, // 78. 'N'
    7, 5, 5, 5, 7, // 79. 'O'
    7, 5, 7, 1, 1, // 80. 'P'
    7, 5, 5, 1, 5, // 81. 'Q'
    7, 5, 3, 5, 5, // 82. 'R'
    7, 1, 7, 4, 7, // 83. 'S'
    7, 2, 2, 2, 2, // 84. 'T'
    5, 5, 5, 5, 7, // 85. 'U'
    5, 5, 5, 5, 2, // 86. 'V'
    5, 5, 7, 7, 5, // 87. 'W'
    5, 5, 2, 5, 5, // 88. 'X'
    5, 5, 7, 2, 2, // 89. 'Y'
    7, 4, 2, 1, 7, // 90. 'Z'
    0, 0, 6, 2, 2, // 91. '['
    1, 3, 7, 3, 1, // 92. barra sinistrorsa
    2, 2, 6, 0, 0, // 93. ']'
    2, 2, 2, 2, 2, // 94. ordinale femminile
    0, 0, 0, 0, 7, // 95. sottolinea
    1, 2, 0, 0, 0  // 96. accento
};

/*
    Character map for the computer and operating system. The resolution is
    32x36 pixels. It is loaded in n_globes_map + gl_bytes and occupies 10800
    bytes. These 10182 bytes (gl_brest) are practically a tiny extension of
    the n_globes_map area which by itself, containing a semi-texture of 32Kb
    for the sea, has been extended from 22586 to 32768.
*/

uint32_t *digimap2; // Will be assigned to n_globes_map + gl_bytes.

// Panoramic dome.

const float cupsize   = 1800;
const float cupheight = 1667;

void cupola(float y_or, float brk) {
    float xx, yy, zz;
    float lat, lon, dlat, dlon, dlon_2, k, clon, slon, ck, sk;
    dlat   = M_PI / 20;
    dlon   = M_PI / 10;
    dlon_2 = dlon / 2;

    for (lon = 0; lon < 2 * M_PI - dlon_2; lon += dlon) {
        k    = lon + dlon;
        ck   = cos(k);
        sk   = sin(k);
        clon = cos(lon);
        slon = sin(lon);

        for (lat = dlat; lat < brk * dlat; lat += dlat) {
            xx = cupsize * sin(lat + dlat);
            yy = -cupheight * cos(lat) * y_or;
            zz = cupsize * sin(lat);
            stick3d(zz * clon, yy, zz * slon, xx * clon,
                    -cupheight * cos(lat + dlat) * y_or, xx * slon);
            stick3d(zz * clon, yy, zz * slon, zz * ck, yy, zz * sk);
        }

        if (gburst > 1) {
            lat = (M_PI / 20) * 8 * ((float) gburst / 63);
            lens_flares_for(cam_x, cam_y, cam_z, +cupsize * clon * sin(lat),
                            -cupheight * cos(lat), +cupsize * slon * sin(lat),
                            -50000, 10, 1, 0, 1, 1);
            flares = 0;
        }
    }
}

void polycupola(float y_or, int8_t textured) {
    float d1, d2, d3, dd;
    float x[4], y[4], z[4];
    float lat, lon, dlat, dlon, dlon_2, k, clon, slon, ck, sk;
    dlat   = M_PI / 20;
    dlon   = M_PI / 10;
    dlon_2 = dlon / 2;

    if (textured) {
        setfx(4);
    } else {
        setfx(2);
    }

    for (lon = 0; lon < 2 * M_PI - dlon_2; lon += dlon) {
        k    = lon + dlon;
        ck   = cos(k);
        sk   = sin(k);
        clon = cos(lon);
        slon = sin(lon);

        for (lat = dlat; lat < 8 * dlat; lat += dlat) {
            float xx = cupsize * sin(lat + dlat);
            float yy = -cupheight * cos(lat) * y_or;
            float zz = cupsize * sin(lat);
            x[0]     = zz * clon;
            y[0]     = yy;
            z[0]     = zz * slon;
            x[1]     = zz * ck;
            y[1]     = yy;
            z[1]     = zz * sk;
            x[2]     = xx * ck;
            y[2]     = -cupheight * cos(lat + dlat) * y_or;
            z[2]     = xx * sk;
            x[3]     = xx * clon;
            y[3]     = -cupheight * cos(lat + dlat) * y_or;
            z[3]     = xx * slon;

            if (ontheroof && y_or == 1) {
                d1 = 0.5 * (x[0] + x[1]) - cam_x;
                d2 = 0.5 * (z[0] + z[1]) - cam_z;
                dd = 1000 - sqrt(d1 * d1 + d2 * d2);

                if (dd > 600) {
                    dd = 600;
                }

                if (dd < 0) {
                    dd = 0;
                }

                cam_y += dd;
                poly3d(x, y, z, 4, 64);
                cam_y -= dd;
            } else {
                if (textured) {
                    d1 = 0.5 * (x[0] + x[1]) - cam_x;
                    d2 = 0.5 * (y[0] + y[2]) - cam_y;
                    d3 = 0.5 * (z[0] + z[1]) - cam_z;
                    dd = 500 - sqrt(d1 * d1 + d2 * d2 + d3 * d3);

                    if (dd > 500) {
                        dd = 500;
                    }

                    if (dd < 0) {
                        dd = 0;
                    }

                    cam_y += 4 * dd * y_or;
                    xx   = x[3];
                    yy   = y[3];
                    zz   = z[3];
                    x[3] = x[2];
                    y[3] = y[2];
                    z[3] = z[2];
                    x[2] = x[1];
                    y[2] = y[1];
                    z[2] = z[1];
                    x[1] = x[0];
                    y[1] = y[0];
                    z[1] = z[0];
                    x[0] = xx;
                    y[0] = yy;
                    z[0] = zz;
                    polymap(x, y, z, 4, 0);
                    cam_y -= 4 * dd * y_or;
                } else {
                    poly3d(x, y, z, 4, 64);
                }
            }
        }
    }

    resetfx();
}

// Synchronizer: up to 18 frames per second on any PC.

clock_t gtime;

void sync_start() { gtime = clock(); }

void sync_stop() {
    while (clock() == gtime)
        ;
}

int32_t global_surface_seed;
float ppos_x, ppos_y, ppos_z;
double dsd; // To measure distances.

// Load the bitmap for the star surface.
// Implementation is sketchy at best.
void load_starface() {
    auto seed  = static_cast<uint16_t>(nearstar_identity * 12345);
    int16_t ax = seed;
    for (int i = 0; i < 64800; i++) {
        ax += (64800 - i);
        int32_t result    = ax * ax;
        auto resultHigh   = static_cast<int16_t>(result >> 16u);
        auto resultLow    = static_cast<int16_t>(result & 0xFFFFu);
        int16_t netResult = resultHigh + resultLow;
        auto blarg        = static_cast<uint8_t>(netResult & 0xFFu);
        blarg &= 0x3Eu;
        s_background[i] = blarg;
    }

    int16_t smoothcount;
    fast_srand(seed);
    smoothcount = static_cast<int16_t>(fast_random(3));

    if (nearstar_class == 11 || nearstar_class == 7 || nearstar_class == 2) {
        smoothcount += fast_random(3) + 2;
    }

    while (smoothcount) {
        ssmooth(s_background);
        smoothcount--;
    }
}

void load_QVRmaps() {
    FILE* fh = sa_open(offsets_map);

    if (fh != nullptr) {
        fread(n_offsets_map, 1, om_bytes, fh);
        fclose(fh);
    }

    fh = sa_open(globes_map);

    if (fh != nullptr) {
        fread(n_globes_map, 1, gl_bytes, fh);
        fclose(fh);
    }
}

void load_digimap2() {
    FILE* fh = sa_open(off_digimap2);

    if (fh != nullptr) {
        fread(digimap2, 1, dm2_bytes, fh);
        fclose(fh);
    }
}

int8_t outhudbuffer[81];
const char *compass =
    "N.........E.........S.........W.........N.........E.........S.......";

float tp_gravity = 1, pp_gravity = 1;
float tp_temp = 22, pp_temp = 22;
float tp_pressure = 1, pp_pressure = 1;
float tp_pulse = 118, pp_pulse = 118;

void wrouthud(uint16_t x, uint16_t y, uint16_t l, const char *text) {
    int16_t j, i, n;
    uint16_t spot;
    n = 0;

    if (!l) {
        l = 32767;
    }

    spot = y * 320 + x;

    while (text[n] && n < l) {
        j = (text[n] - 32) * 5;

        for (i = 0; i < 5; i++) {
            if (digimap[j + i] & 1) {
                adapted[spot + 0] = 191 - adapted[spot + 0];
            }

            if (digimap[j + i] & 2) {
                adapted[spot + 1] = 191 - adapted[spot + 1];
            }

            if (digimap[j + i] & 4) {
                adapted[spot + 2] = 191 - adapted[spot + 2];
            }

            spot += 320;
        }

        spot -= 320 * 5;
        spot += 4;
        n++;
    }
}

void surrounding(int8_t compass_on, int16_t openhudcount) {
    int16_t cpos, crem;
    int32_t lsecs, lptr;
    float pp_delta, ccom;

    for (lptr = 0; lptr < 04; lptr++) {
        area_clear(adapted, 10, openhudcount + 9 - lptr, 0, 0, 300, 1,
                   54 + surlight + 3 * lptr);
    }

    for (lptr = 0; lptr < 10; lptr++) {
        area_clear(adapted, 0, 9 - lptr, 0, 0, 320, 1, 64 + surlight - lptr);
    }

    for (lptr = 0; lptr < 10; lptr++) {
        area_clear(adapted, 0, 190 + lptr, 0, 0, 320, 1, 64 + surlight - lptr);
    }

    for (lptr = 0; lptr < 10; lptr++) {
        area_clear(adapted, 9 - lptr, 10, 0, 0, 1, 180, 64 + surlight - lptr);
    }

    for (lptr = 0; lptr < 10; lptr++) {
        area_clear(adapted, 310 + lptr, 10, 0, 0, 1, 180, 64 + surlight - lptr);
    }

    lptr = 64 + 3 * surlight;

    if (lptr > 127) {
        lptr = 127;
    }

    area_clear(adapted, 9, 9, 0, 0, 4, 4, lptr);
    smootharound_64(adapted, 9, 9, 5, 1);
    area_clear(adapted, 308, 9, 0, 0, 4, 4, lptr);
    smootharound_64(adapted, 308, 9, 5, 1);
    area_clear(adapted, 9, 188, 0, 0, 4, 4, lptr);
    smootharound_64(adapted, 9, 188, 5, 1);
    area_clear(adapted, 308, 188, 0, 0, 4, 4, lptr);
    smootharound_64(adapted, 308, 188, 5, 1);
    // Print time on outer HUD.
    sprintf((char *) outhudbuffer, "EPOC %d & ", epoc);

    auto sinisters = (uint16_t)(fmod(secs, 1e9) / 1e6);
    // Pad with a 0.
    if (sinisters < 100) {
        strcat((char *) outhudbuffer, "0");
    }
    strcat((char *) outhudbuffer, alphavalue(sinisters));
    strcat((char *) outhudbuffer, ".");

    auto medii = (uint16_t)(fmod(secs, 1e6) / 1e3);
    if (medii < 100) {
        strcat((char *) outhudbuffer, "0");
    }
    strcat((char *) outhudbuffer, alphavalue(medii));
    strcat((char *) outhudbuffer, ".");

    auto dexters = (uint16_t)(fmod(secs, 1e3));
    if (dexters < 100) {
        strcat((char *) outhudbuffer, "0");
    }
    strcat((char *) outhudbuffer, alphavalue(dexters));

    if (compass_on) {
        strcat((char *) outhudbuffer, " & SQC ");
        strcat((char *) outhudbuffer, alphavalue(landing_pt_lon));
        strcat((char *) outhudbuffer, ".");
        strcat((char *) outhudbuffer, alphavalue(landing_pt_lat));
        strcat((char *) outhudbuffer, ":");
        strcat((char *) outhudbuffer,
               alphavalue((((int32_t)(pos_x)) >> 14u) - 100));
        strcat((char *) outhudbuffer, ".");
        strcat((char *) outhudbuffer,
               alphavalue((((int32_t)(pos_z)) >> 14u) - 100));
        area_clear(adapted, 254, 1, 0, 0, 5, 7, 64 + 0);
        area_clear(adapted, 256, 8, 0, 0, 1, 1, 64 + 63);
        ccom = 360 - user_beta;

        if (ccom > 359) {
            ccom -= 360;
        }

        cpos = (int16_t)(ccom / 9);
        crem = (int16_t)(ccom * 0.44444);
        wrouthud(200 - (crem % 4), 2, 28, (char *) (compass + cpos));
    } else {
        if (!ontheroof) {
            strcat((char *) outhudbuffer, " & ");

            if (sys == 4) {
                strcat(
                    (char *) outhudbuffer,
                    "(5\\FLIGHTCTR R\\DEVICES    P\\PREFS      X\\SCREEN OFF)");
            } else {
                cpos                    = strlen((char *) outhudbuffer);
                outhudbuffer[cpos + 00] = '6';
                outhudbuffer[cpos + 01] = '\\';
                memcpy(outhudbuffer + cpos + 02, ctb + 20 + 27 * 0, 10);
                outhudbuffer[cpos + 12] = ' ';
                outhudbuffer[cpos + 13] = '7';
                outhudbuffer[cpos + 14] = '\\';
                memcpy(outhudbuffer + cpos + 15, ctb + 20 + 27 * 1, 10);
                outhudbuffer[cpos + 25] = ' ';
                outhudbuffer[cpos + 26] = '8';
                outhudbuffer[cpos + 27] = '\\';
                memcpy(outhudbuffer + cpos + 28, ctb + 20 + 27 * 2, 10);
                outhudbuffer[cpos + 38] = ' ';
                outhudbuffer[cpos + 39] = '9';
                outhudbuffer[cpos + 40] = '\\';
                memcpy(outhudbuffer + cpos + 41, ctb + 20 + 27 * 3, 10);
                outhudbuffer[cpos + 51] = 0;
                brtl_strupr((char *) outhudbuffer);
            }
        }
    }

    wrouthud(2, 2, 0, (char *) outhudbuffer);
    pp_delta = (pp_gravity - tp_gravity) * 0.25;
    tp_gravity += pp_delta;
    pp_delta = (pp_temp - tp_temp) * 0.05;
    tp_temp += pp_delta;
    pp_delta = (pp_pressure - tp_pressure) * 0.02;
    tp_pressure += pp_delta;
    pp_delta = (pp_pulse - tp_pulse) * 0.01;
    tp_pulse += pp_delta;
    // unit� di debugging dell'albedo:
    // sprintf (outhudbuffer, "GRAVITY %2.3f FG & TEMPERATURE %+3.1f@C &
    // PRESSURE %2.3f ATM & PULSE %3.0f PPS", tp_gravity, tp_temp, tp_pressure,
    // (float)albedo);
    sprintf(
        (char *) outhudbuffer,
        "GRAVITY %2.3f FG & TEMPERATURE %+3.1f@C & PRESSURE %2.3f ATM & PULSE "
        "%3.0f PPS",
        tp_gravity, tp_temp, tp_pressure, tp_pulse);
    wrouthud(2, 192, 0, (char *) outhudbuffer);
}

extern int32_t star_label_pos;
extern int8_t star_label[25];
extern int32_t planet_label_pos;
extern int8_t planet_label[25];

int8_t snapfilename[24];
/* Save a photo of the screen into the file "SNAP[XXXX].BMP", where [XXXX] is a
 * progressive disambiguation number.
 */
void snapshot(int16_t forcenumber, int8_t showdata) {
    int16_t prog;
    uint16_t pqw;
    double parsis_x, parsis_y, parsis_z;
    uint16_t ptr, c;
    int8_t a, b, t[54];
    FILE* ih = sa_open(header_bmp);

    if (ih == nullptr) {
        return;
    }

    fread(t, 1, 54, ih);
    fclose(ih);

    if (!forcenumber) {
        prog = -1;

        do {
            prog++;

            if (prog == 9999) {
                return;
            }

            sprintf((char *) snapfilename, "gallery/SNAP%04d.BMP", prog);
            ih = fopen((char *) snapfilename, "r");

            if (ih != nullptr) {
                fclose(ih);
            }
        } while (ih != nullptr);
    } else {
        sprintf((char *) snapfilename, "gallery/SNAP%04d.BMP", forcenumber);
    }

    if (showdata) {
        area_clear(adapted, 2, 191, 0, 0, 316, 7, 64 + 63);

        parsis_x = round(dzat_x);
        parsis_y = round(dzat_y);
        parsis_z = round(dzat_z);

        strcpy((char *) outhudbuffer, "LOCATION PARSIS: ");
        strcat((char *) outhudbuffer, alphavalue(parsis_x));
        strcat((char *) outhudbuffer, ";");
        strcat((char *) outhudbuffer, alphavalue(-parsis_y));
        strcat((char *) outhudbuffer, ";");
        strcat((char *) outhudbuffer, alphavalue(parsis_z));

        if (ip_targetted > -1) {
            if (nearstar_p_owner[ip_targetted] > -1) {
                strcat((char *) outhudbuffer, " & TGT: MOON N@");
                strcat((char *) outhudbuffer,
                       alphavalue(nearstar_p_moonid[ip_targetted] + 1));
                strcat((char *) outhudbuffer, " OF PLANET N@");
                strcat((char *) outhudbuffer,
                       alphavalue(nearstar_p_owner[ip_targetted] + 1));
            } else {
                strcat((char *) outhudbuffer, " & TGT: PLANET N@");
                strcat((char *) outhudbuffer, alphavalue(ip_targetted + 1));
            }
        }

        wrouthud(3, 192, 0, (char *) outhudbuffer);

        if (ap_targetted == 1 && star_label_pos != -1) {
            area_clear(adapted, 14, 14, 0, 0, 102, 7, 64 + 63);
            wrouthud(15, 15, 20, (char *) star_label);
        }

        if (ip_targetted != -1 && planet_label_pos != -1) {
            area_clear(adapted, 14, 23, 0, 0, 102, 7, 64 + 63);
            wrouthud(15, 24, 20, (char *) planet_label);
        }
    }

    ih = fopen((char*) snapfilename, "w+");

    if (ih != nullptr) {
        a = 0;
        fwrite(t, 1, 54, ih);

        for (c = 0; c < 768; c += 3) {
            b = tmppal[c + 2] * 4;
            fwrite(&b, 1, 1, ih);
            b = tmppal[c + 1] * 4;
            fwrite(&b, 1, 1, ih);
            b = tmppal[c + 0] * 4;
            fwrite(&b, 1, 1, ih);
            fwrite(&a, 1, 1, ih);
        }

        for (ptr = 63680; ptr < 64000; ptr -= 320) {
            fwrite(adapted + ptr, 1, 320, ih);
        }

        fclose(ih);
    }
}

/*
    Consumi supplementari di litio, dal pi� dispendioso al pi� economico:
    - orbita vimana:            1 KD ogni 7 secondi.
    - inseguimento a punto lontano:     1 KD ogni 18 secondi.
    - inseguimento a punto fisso:       1 KD ogni 29 secondi.
    - inseguimento a punto vicino:      1 KD ogni 33 secondi.
    - amplificatore di campo stellare:  1 KD ogni 41 secondi.
    - orbita geosincrona:           1 KD ogni 58 secondi.
    - lampada interna:          1 KD ogni 84 secondi.
    - cercapianeti:             1 KD ogni 155 secondi.
*/

int32_t iqsecs = 0;
void additional_consumes() {
    if (iqsecs < (int32_t) secs) {
        iqsecs = (int32_t) secs;
    }

    //
    if (ip_targetted > -1 && pwr > 15000) {
        if (ip_reached && nsync) {
            if (nsync == 1) // fixed-point chase
                if (!(iqsecs % 29)) {
                    pwr--;
                    iqsecs++;
                }

            if (nsync == 2) // far chase
                if (!(iqsecs % 18)) {
                    pwr--;
                    iqsecs++;
                }

            if (nsync == 3) // syncrone orbit
                if (!(iqsecs % 58)) {
                    pwr--;
                    iqsecs++;
                }

            if (nsync == 4) // vimana orbit
                if (!(iqsecs % 7)) {
                    pwr--;
                    iqsecs++;
                }

            if (nsync == 5) // near chase
                if (!(iqsecs % 33)) {
                    pwr--;
                    iqsecs++;
                }
        }
    }

    //
    if (pl_search && !(iqsecs % 155)) {
        pwr--;
        iqsecs++;
    }

    if (ilightv == 1 && !(iqsecs % 84)) {
        pwr--;
        iqsecs++;
    }

    if (field_amplificator && !(iqsecs % 41)) {
        pwr--;
        iqsecs++;
    }

    //
    if (pwr <= 15000) {
        if (charge) {
            charge--;
            pwr = 20000;
            status("FCS: READY", 100);
        } else {
            stspeed      = 0;
            ip_reaching  = 0;
            ip_reached   = 1;
            ip_targetted = -1;

            if (pwr != 15000) {
                status("POWER LOSS", 100);
                pwr = 15000;
            }
        }
    }
}
