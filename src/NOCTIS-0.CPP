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

#include "noctis-d.h"

// Date and specific functions imported from ASSEMBLY.H

int QUADWORDS = 16000;

// Adaptor points to the main video memory, which should be 64kb.
unsigned char far * adaptor    = (unsigned char far *) 0xA0000000;
// Adapted points to some other vga memory. I think it's used as a back buffer.
unsigned char far * adapted    = (unsigned char far *) 0xB0000000;

unsigned char   tmppal[768];
char        return_palette[768];
char        surface_palette[768];

int lstri(char *stri) {
    // Measure a string and copy it to tmppal.
    // This is a support function for reach_your_dir()

    int c;

    for (c=0; c<768; c++) {
        if (stri[c])
            tmppal[c] = stri[c];
        else {
            tmppal[c] = '\0';
            return (c);
        }
    }

    return (0);
}

void reach_your_dir() {
    /*
        NOTE: There was a comment here saying something about this being
        used to reach beyond the current directory.
    */

    int c;
    char d;

    c = lstri(_argv[0]) - 1;
    while (c>=0&&tmppal[c]!='\\') c--;

    if (c>=0) {
        if (tmppal[c-1] != ':')
            tmppal[c] = 0;
        else
            tmppal[c+1] = 0;
    }

    if (_argv[0][0]>='a'&&_argv[0][0]<='z')
        d = _argv[0][0] - 'a';
    else
        d = _argv[0][0] - 'A';

    union REGS regs;

    regs.h.ah = DOS_SELECT_DRIVE;
    regs.h.dl = d;
    intdos(&regs, &regs);

    regs.h.ah = DOS_SET_WORKING_DIR;
    regs.x.dx = *tmppal;
    intdos(&regs, &regs);
}

// Initialize the 320x200x256 graphics mode.
void _320_200_256 () {
    union REGS regs;
   regs.x.ax = VIDEO_MODE_VGA;

    int86(INTERRUPT_VIDEO_MODE, &regs, &regs);
}

// Initialize the 80x25 text mode.
void _80_25_C () {
    union REGS regs;
   regs.x.ax = VIDEO_MODE_TEXT;

   int86(INTERRUPT_VIDEO_MODE, &regs, &regs);
}

// Wait for a key?
int attendi_pressione_tasto () {
   union REGS regs;
   regs.h.ah = DOS_CHAR_READ_NO_ECHO;
   intdos(&regs, &regs);

    return regs.h.al;
}

// Return 1 if there is a key press to be processed.
int tasto_premuto () {
    union REGS regs;
    regs.h.ah = DOS_GET_STDIN_STATUS;
   intdos(&regs, &regs);

    if (regs.h.al == 0xff) return 1;
   else return 0;
}

unsigned char range8088[64*3] = {
 0,  0,  0,  1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,  5,  5,
 6,  6,  6,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10, 10, 10, 11, 11, 11,
12, 12, 12, 13, 13, 13, 14, 14, 14, 15, 15, 15, 16, 16, 16, 17, 17, 17,
18, 18, 18, 19, 19, 19, 20, 20, 20, 21, 21, 21, 22, 22, 22, 23, 23, 23,
24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 27, 27, 28, 28, 28, 29, 29, 29,
30, 30, 30, 31, 31, 31, 32, 32, 32, 33, 33, 33, 34, 34, 34, 35, 35, 35,
36, 36, 36, 37, 37, 37, 38, 38, 38, 39, 39, 39, 40, 40, 40, 41, 41, 41,
42, 42, 42, 43, 43, 43, 44, 44, 44, 45, 45, 45, 46, 46, 46, 47, 47, 47,
48, 48, 48, 49, 49, 49, 50, 50, 50, 51, 51, 51, 52, 52, 52, 53, 53, 53,
54, 54, 54, 55, 55, 55, 56, 56, 56, 57, 57, 57, 58, 58, 58, 59, 59, 59,
60, 60, 60, 61, 61, 61, 62, 62, 62, 63, 63, 63 };

// This sets up the vga color palette.
void tavola_colori (unsigned char *new_palette,
            unsigned starting_color, unsigned num_colors,
            char red_filter, char green_filter, char blue_filter) {
    int c, cc = 0;
    unsigned temp;
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
        if (temp > 63) temp = 63;
        tmppal[c] = temp;
        c++;
        temp = tmppal[c];
        temp *= green_filter;
        temp /= 63;
        if (temp > 63) temp = 63;
        tmppal[c] = temp;
        c++;
        temp = tmppal[c];
        temp *= blue_filter;
        temp /= 63;
        if (temp > 63) temp = 63;
        tmppal[c] = temp;
        c++;
    }

   // Port 0x3c8 takes the index of the first color.
   outp(0x3c8, 0);
   for (int i = 0; i < starting_color + num_colors; i++) {
    // Port 0x3c9 takes up to 255 consecutive r, g, b, colors.
    outp(0x3c9, tmppal[i]);
   }
}

// Variables to hold mouse readings.
int mdltx = 0, mdlty = 0, mx = 0, my = 0, mpul = 0;

// Read mouse input.
void mouse_input () {
    union REGS regs;

   regs.x.ax = MOUSE_READ_MOTION;
   int86(INTERRUPT_MOUSE, &regs, &regs);
   mdltx = regs.x.cx;
   mdlty = regs.x.dx;
   mx += mdltx;
   my += mdlty;

   regs.x.ax = MOUSE_READ_PRESS;
   int86(INTERRUPT_MOUSE, &regs, &regs);
    if (regs.x.ax != 0) {
    mpul = regs.x.ax;
   }
}

// Check the presence of the mouse (or the support for it).
// And initialize the driver (empty the movement buffer).

char test_and_init_mouse () {
    union REGS regs;

   regs.x.ax = MOUSE_READ_STATUS;
   int86(INTERRUPT_MOUSE, &regs, &regs);

   if (regs.x.ax == 0) {
       return 0;
   } else {
      // Here we read in the mouse data to get a clean slate.
    regs.x.ax = MOUSE_READ_MOTION;
      int86(INTERRUPT_MOUSE, &regs, &regs);

      regs.x.ax = MOUSE_READ_PRESS;
      int86(INTERRUPT_MOUSE, &regs, &regs);

      return 1;
   }
}

// Copies QUADWORDS * 4 bytes from the source to the destination.
void pcopy (unsigned char far *dest, unsigned char far *source) {
    memcpy(dest, source, QUADWORDS * 4);
}

// Clears QUADWORDS * 4 bytes starting at the target.
void pclear (unsigned char far *target, unsigned char pattern) {
    memset(target, pattern, QUADWORDS * 4);
}

// Clears a rectangular region of the video memory.
// Either x2 & y2 OR l and h must be specified.
// This may or may not work.
void areaclear (unsigned char far *dest, int x, int y,
        int x2, int y2, int l, int h, unsigned char pattern) {
    if (l == 0 || h == 0) {
            l = x2 - x;
            h = y2 - y;
    }
    for (int xPos = x; xPos < x + l; xPos++) {
        for (int yPos = y; yPos < y + h; yPos++) {
            unsigned int netIndex = (yPos * 320) + xPos;
            dest[netIndex] = pattern;
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
    Note 2: This procedure is only used to smoooth the background, and that
    isn't even being rendered at the moment for some reason.

*/

void psmooth_grays(unsigned char far *target) {
    unsigned int count = (QUADWORDS << 2) - (320 << 2);
    asm {   
        pusha
        push    ds
        mov     cx, count
        lds     di, dword ptr target
        add     di, 320 
        }
    smooth: 
    asm {   
        db      0x66
        mov     dx, [di-320]
        db      0x66
        add     dx, [di]
        db      0x66 
        add     dx, [di+320]
        db      0x66
        add     dx, [di+640]
        db      0x66, 0x81, 0xE2, 0xFC, 0xFC, 0xFC, 0xFC
        db      0x66 
        shr     dx, 2
        mov     al, dl
        add     al, dh
        db      0x66; shr dx, 16
        add     al, dl
        add     al, dh
        shr     al, 2
        mov     [di], al 
    }
    next:   
    asm {   
        inc     di
        dec     cx
        jnz     smooth
        pop     ds
        popa 
    }
}

// Produces the fading effect seen during vimana flight.
void pfade (unsigned char far *target, unsigned segshift, unsigned char speed) {
    // ?
    unsigned int count = (QUADWORDS - 80) << 2;
    
    unsigned long address = (unsigned long) target;
    address += ((unsigned long) segshift) << 16;
    // Clear offset of address.
    address &= 0xFFFF0000;
    
    unsigned char far * shifted = (unsigned char far *) address;
    
    for (int i = 0; i < count; i++) {
        unsigned char color = shifted[i];
        color &= 0x3F;
        
        if (speed < color) {
            color -= speed;
        } else {
            color = 0;
        }
        
        shifted[i] = color;
    }
}

// Color version: 4 shades of 64 intensity each.
void psmooth_64(unsigned char far *target, unsigned segshift) {
    // Who knows why this is offset as it is... Definitely not me.
    unsigned int count = (QUADWORDS - 80) << 2;
    
    unsigned long address = (unsigned long) target;
    // Add segshift to the segment portion of the address by shifting up 16 bits.
    address += ((unsigned long) segshift) << 16;
    // Clear offset of address.
    address &= 0xFFFF0000;
    
    unsigned char far * shifted = (unsigned char far *) address;
    
    for (unsigned int i = 0; i < count; i++) {
        unsigned char ahigh = shifted[i + 320];
        unsigned char alow = shifted[i + 321];
        unsigned char blow = shifted[i + 640];
        unsigned char bhigh = shifted[i + 641];
        unsigned char clow = alow;
        
        // Bitwise AND with 63 for some reason...
        ahigh &= 0x3F;
        alow &= 0x3F;
        bhigh &= 0x3F;
        blow &= 0x3F;
        // Ideally these shouldn't overflow.
        ahigh += bhigh;
        alow += blow;
        // No idea why we do this.
        clow &= 0xC0;
        alow += ahigh;
        // This will drop the low 2 bits of alow.
        alow >>= 2;
        // Who knows why italy man does this...
        alow |= clow;
        
        shifted[i] = alow;
    }
}


// Circular version of the smoothing process.
void smootharound_64(unsigned char far *target, long cx, long cy, long r, char diffuse) {
    long x1 = cx - r, y1 = cy - r;
    long x2 = cx + r, y2 = cy + r;
    long px, py, rs = r*r;
    unsigned cp;

    if (r <= 0) return;

    if (x1 > 318) return;
    if (y1 > 198) return;
    if (y1 < 0) y1 = 0;

    if (x2 < 0) return;
    if (x2 > 318) x2 = 318;
    if (y2 < 0) return;
    if (y2 > 198) y2 = 198;

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
                if (px*px + py*py < rs) {
                asm {   les     di, dword ptr target
                    add di, cp
                    mov ax, es:[di]
                    mov cx, ax
                    mov bx, es:[di+320]
                    mov dx, bx
                    and ax, 0x3F3F
                    and bx, 0x3F3F
                    add ax, bx
                    and cx, 0xC0C0
                    add al, ah
                    and dx, 0xC0C0
                    shr al, 2
                    mov     ah, al
                    mov bx, ax
                    or  ax, cx
                    or  bx, dx
                    mov     es:[di], ax
                    mov     es:[di+320], bx }
                }
                cp++;
                px++;
                x1++;
            }
        }
        else {
            while (x1 <= x2) {
                if (px*px + py*py < rs) {
                asm {   les     di, dword ptr target
                    add di, cp
                    mov ax, es:[di]
                    mov bx, es:[di+320]
                    mov cl, al
                    and ax, 0x3F3F
                    and bx, 0x3F3F
                    and cl, 0xC0
                    add ax, bx
                    add al, ah
                    shr al, 2
                    or      al, cl
                    mov     es:[di], al }
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
void mask_pixels(unsigned char far *target, unsigned char mask) {
    unsigned char cap = 0x3F;
    // If QUADWORDS is not cast to a long here it overflows and the loop hangs.
    for (unsigned long i = 0; i < ((unsigned long) QUADWORDS) * 4; i++) {
        unsigned char color = target[i];
        color &= cap;
        color += mask;
        target[i] = color;
    }
}

// HSP Inclusions.

#include <tdpolygs.h> // 3D Engine.

// Support files

char   *situation_file  = "data\\Current.BIN";
char   *starmap_file    = "data\\StarMap.BIN";
char   *goesoutputfile  = "data\\GOESfile.TXT";
char   *surface_file    = "data\\Surface.BIN";
int     sfh; // Surface situation file handle.

// Global variables that are saved.

char   sync               = 1;      // 0
char   anti_rad           = 1;          // 1
char   pl_search          = 0;          // 2
char   field_amplificator = 0;          // 3
char   ilight             = 63;         // 4
char   ilightv            = 1;          // 5
char   charge             = 3;          // 6
char   revcontrols        = 0;          // 7
char   ap_targetting      = 0;          // 8
char   ap_targetted       = 0;          // 9
char   ip_targetting      = 0;          // 10
char   ip_targetted       = -1;     // 11
char   ip_reaching        = 0;          // 12
char   ip_reached         = 0;          // 13
char   ap_target_spin     = 0;          // 14
char   ap_target_r        = 0;          // 15
char   ap_target_g        = 0;          // 16
char   ap_target_b        = 0;          // 17
char   nearstar_spin      = 0;          // 18
char   nearstar_r         = 0;          // 19
char   nearstar_g         = 0;          // 20
char   nearstar_b         = 0;          // 21
char   gburst             = 0;          // 22
char   menusalwayson      = 1;      // 23
char   depolarize     = 0;          // 24
int    sys                = 4;      // 25
int    pwr                = 20000;  // 27
int    dev_page           = 0;      // 29
int    ap_target_class    = 0;      // 31
int    f_ray_elapsed      = 0;      // 33
int    nearstar_class     = 0;      // 35
int    nearstar_nop       = 0;      // 37
float  pos_x              = 0;      // 39
float  pos_y              = 0;      // 43
float  pos_z              = -500;   // 47
float  user_alfa          = 0;      // 51
float  user_beta          = 0;      // 55
float  navigation_beta    = 0;      // 59
float  ap_target_ray      = 1000;   // 63
float  nearstar_ray       = 1000;   // 67
double dzat_x             = +3797120;   // 71
double dzat_y             = -4352112;   // 79
double dzat_z             = -925018;    // 87
double ap_target_x        = 0;      // 95
double ap_target_y        = 1E8;    // 103
double ap_target_z        = 0;      // 111
double nearstar_x         = 0;      // 119
double nearstar_y         = 1E8;    // 127
double nearstar_z         = 0;      // 135
double helptime           = 0;      // 143
double ip_target_initial_d= 1E8;    // 151
double requested_approach_coefficient=1;// 159
double current_approach_coefficient = 1;// 167
double reaction_time      = 0.01;   // 175
char   fcs_status[11]     = "STANDBY";  // 183
int    fcs_status_delay   = 0;      // 194
int    psys               = 4;      // 196
double ap_target_initial_d= 1E8;    // 198
double requested_vimana_coefficient = 1;// 206
double current_vimana_coefficient = 1;  // 214
double vimana_reaction_time = 0.01; // 222
char   lithium_collector  = 0;      // 230
char   autoscreenoff      = 0;      // 231
char   ap_reached         = 0;      // 232
int    lifter         = 0;      // 233
double secs       = 0;      // 235
char   data       = 0;      // 243
char   surlight       = 16;     // 244

// Surface landing control data.

char   land_now       = 0;
char   landing_point      = 0;
int    landing_pt_lon     = 0;
int    landing_pt_lat     = 60;

int     crepzone;
int     nightzone;
int sun_x_factor;

// Global data that isn't saved.

char seconds[3], minutes[3], hours[3], day[3], month[3], year[5];
int  epoc = 6011;

char        ctb[512];
char        dec[20];

char        _delay          = 12;
char        stspeed         = 0;
char        bright;
char        elight          = 0;
unsigned    gl_start        = 0;
unsigned    point;
unsigned    vptr;
int         infoarea        = 0;
int         s_control       = 1;
int         s_command       = 0;
int         isecs, p_isecs;
double      fsecs;
int         gl_fps          = 1;
int         fps             = 1;
float       dlt_alfa        = 0;
float       dlt_beta        = 0;
float       dlt_nav_beta    = 0;
float       step            = 0;
float       shift           = 0;
double      s_m             = 1000;
double      plx, ply, plz;
double      pxx, pyy;
double      delta_x, delta_y;
double      nearstar_identity;
int         nearstar_labeled;
int         nearstar_nob    = 0;
int         npcs, resident_map1, resident_map2;
char        ontheroof;
int         datasheetscroll = 0;
int         datasheetdelta  = 0;

// Constant data in the global segment.

// Some ordinals (from 0 to 20) for certain representations.

char *ord[21] = { "zeroth", "first", "second", "third", "fourth", "fifth",
          "sixth", "seventh", "eight", "nineth", "tenth", "eleventh",
          "twelveth", "thiteenth", "fourteenth",
          "fifteenth", "sixteenth", "seventeenth",
          "eighteenth", "nineteenth", "twentyth" };

char *star_description[star_classes] = {
    "medium size, yellow star, suitable for planets having indigenous lifeforms.",
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
    "tiny pulsar object, unsafe, high radiation, strong gravity." };

char class_rgb[3 * star_classes] = {
    63, 58, 40,
    30, 50, 63,
    63, 63, 63,
    63, 30, 20,
    63, 55, 32,
    32, 16, 10,
    32, 28, 24,
    10, 20, 63,
    63, 32, 16,
    48, 32, 63,
    40, 10, 10,
    00, 63, 63
};

int class_ray[star_classes] = { 
    5000, 15000, 
    300, 20000, 
    15000, 1000, 
    3000, 2000, 
    4000, 1500, 
    30000, 250 
};

int class_rayvar[star_classes] = {
    2000, 10000, 
    200, 15000, 
    5000, 1000, 
    3000, 500, 
    5000, 10000, 
    1000, 10 
};

int class_act[star_classes] = { 
    2, 4, 1, 
    6, 5, 10, 
    100, 1, 2, 
    1, 10, 1 
};

char class_planets[star_classes] = { 
    12, 18, 8, 
    15, 20, 3, 
    0, 1, 7, 
    20, 2, 5 
};

char   nearstar_p_type       [maxbodies];
int    nearstar_p_owner      [maxbodies];
char   nearstar_p_moonid     [maxbodies];
double nearstar_p_ring       [maxbodies];
double nearstar_p_tilt       [maxbodies];
double nearstar_p_ray        [maxbodies];
double nearstar_p_orb_ray    [maxbodies];
double nearstar_p_orb_seed   [maxbodies];
double nearstar_p_orb_tilt   [maxbodies];
double nearstar_p_orb_orient [maxbodies];
double nearstar_p_orb_ecc    [maxbodies];

int    nearstar_p_rtperiod   [maxbodies];
int    nearstar_p_rotation   [maxbodies];
int    nearstar_p_term_start [maxbodies];
int    nearstar_p_term_end   [maxbodies];

int    nearstar_p_qsortindex [maxbodies];
float  nearstar_p_qsortdist  [maxbodies];

char *planet_description[] = { 
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
    "companion star - not a planet" 
};

unsigned char planet_rgb_and_var[] = { 
    60, 30, 15, 20,
    40, 50, 40, 25,
    32, 32, 32, 32,
    16, 32, 48, 40,
    32, 40, 32, 20,
    32, 32, 32, 32,
    32, 32, 32, 32,
    32, 40, 48, 24,
    40, 40, 40, 30,
    50, 25, 10, 20,
    40, 40, 40, 40 
};

int planet_possiblemoons[] = { 
    1, 1, 
    2, 3, 
    2, 2, 
    18, 2, 
    3, 20, 
    20 
};

const double planet_orb_scaling = 5.0;
const double avg_planet_sizing  = 2.4;
const double moon_orb_scaling   = 12.8;
const double avg_moon_sizing    = 1.8;

double avg_planet_ray[] = { 
    0.007, 0.003, 0.010, 
    0.011, 0.010, 0.008, 
    0.064, 0.009, 0.012, 
    0.125, 5.000 
};

float mindiff = 0.01;


// Physical and logical video matrices, cartography, and other memory blocks.

unsigned char far  *s_background;
unsigned char far  *p_background;
unsigned char huge *p_surfacemap;
quadrant      far  *objectschart;
unsigned char far  *ruinschart; // As objectschart, but declared in bytes.
unsigned char far  *pvfile;

unsigned char far  *n_offsets_map;
char far           *n_globes_map;

unsigned            seg_adapted;

// Planetary surface adjustment data.

char sky_red_filter = 63; // Filters for the sky.
char sky_grn_filter = 63;
char sky_blu_filter = 63;
char gnd_red_filter = 63; // Filters for the ground.
char gnd_grn_filter = 63;
char gnd_blu_filter = 63;

float planet_grav   = 150; // Corresponds to the planetary gravity.
float rainy         = 0; // Raininess, based on cloud albedo. [0,5]
int   albedo        = 0; // Albedo average of the landing surface. [0,62]

unsigned char sky_brightness = 32; // Sky luminosity. [0,48]
unsigned char horiz_brt      = 20; // Brightness of the low horizon. [0,48]

unsigned m200[200]; // Numbers from 0 to 199, multipled by 200 (Lookup table)

float   rwp        = 15; // Required wind power (in knots).
float   iwp        = 0; // Ideal wind power (from 0 to 1).
float   wp         = 0; // Current wind power.
float   wdir       = 0; // Wind origin direction.
float   wdirsin    = 0; // Optimization value.
float   wdircos    = 1; // Optimization value.

char    landed; // Flag set at the time of landing.
// Coded position quotiento of the lander (quotient:remainder).
long    atl_x, atl_z, 
        atl_x2, atl_z2;

double qid = 1.0 / 16384; // Constant to find the x / z id of a quadrant.

// Polygonal graphics area (characters, ships, labels, etc...)

#define handles 16 // 16 handles in this case.

unsigned long pvfile_datatop = 0; // Top of the data.

// Note: dataptr is a relative pointer that can go from 0 to "pvbytes".
unsigned pvfile_dataptr[handles] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
unsigned pvfile_datalen[handles] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
unsigned pvfile_npolygs[handles] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

char  far *pv_n_vtx[handles]; // numero vertici per ogni poligono (3 o 4).
float far *pvfile_x[handles]; // coord. X (quattro vertici) di ogni poligono.
float far *pvfile_y[handles]; // coord. Y (quattro vertici) di ogni poligono.
float far *pvfile_z[handles]; // coord. Z (quattro vertici) di ogni poligono.
char  far *pvfile_c[handles]; // intensitÖ del colore di ogni poligono (0..63).
float far *pv_mid_x[handles]; // coordinate X dei punti medi di ogni poligono.
float far *pv_mid_y[handles]; // coordinate Y dei punti medi di ogni poligono.
float far *pv_mid_z[handles]; // coordinate Z dei punti medi di ogni poligono.
float far *pv_mid_d[handles]; // buffer distanza di punti medi dall'osservatore.
int   far *pv_dep_i[handles]; // indice distanza (ordinamento poligoni).

/* Procedimenti d'estrazione di numeri pseudo-casuali. */

long flat_rnd_seed;

void fast_srand (long seed) // selezione tabella pseudo.
                // 4.294.967.295 tabelle possibili.
                // (ca. 20000 elementi diversi per tabella)
{
    asm {
        or word ptr seed, 3
        db 0x66; mov ax, word ptr seed
        db 0x66; mov word ptr flat_rnd_seed, ax
    }
}

long fast_random (long mask) // estrazione di un numero: "mask" attiva i bits.
{
    long num;

    asm {
        db 0x66; mov ax, word ptr flat_rnd_seed
        db 0x66; mov dx, word ptr flat_rnd_seed
        db 0x66; mul dx
             add al, dl
        db 0x66; add word ptr flat_rnd_seed, ax
        db 0x66; and ax, word ptr mask
        db 0x66; mov word ptr num, ax
    }

    return (num);
}

int ranged_fast_random (int range)
{
    if (range<=0) range = 1;
    return (fast_random(0x7FFF) % range);
}

float flandom ()
{ return ((float)random(32767) * 0.000030518); }

float fast_flandom ()
{ return ((float)fast_random(32767) * 0.000030518); }

// Loads virtual file handles from supports.nct
int sa_open (long offset_of_virtual_file) {
    int fh;

    fh = _rtl_open ("res/supports.nct", 0);
    if (fh==-1) return (-1);

    if (lseek (fh, offset_of_virtual_file, SEEK_END) > -1)
        return (fh);
    else {
        _rtl_close (fh);
        return (-1);
    }
}

/* Definisce una parte della tavola colori in modo che una sfumatura graduale
   vada da una tinta ad un'altra, entro un certo numero di tinte intermedie */

void shade (unsigned char far *palette_buffer,
        int first_color, int number_of_colors,
        float start_r,  float start_g,  float start_b,
        float finish_r, float finish_g, float finish_b)
{
    int   count = number_of_colors;

    float k = 1.00 / (float)number_of_colors;
    float delta_r = (finish_r - start_r) * k;
    float delta_g = (finish_g - start_g) * k;
    float delta_b = (finish_b - start_b) * k;

    first_color *= 3;

    while (count) {
        if (start_r >= 0 && start_r < 64)
            palette_buffer[first_color + 0] = start_r;
        else {
            if (start_r > 0)
                palette_buffer[first_color + 0] = 63;
            else
                palette_buffer[first_color + 0] = 00;
        }
        //
        if (start_g >= 0 && start_g < 64)
            palette_buffer[first_color + 1] = start_g;
        else {
            if (start_g > 0)
                palette_buffer[first_color + 1] = 63;
            else
                palette_buffer[first_color + 1] = 00;
        }
        //
        if (start_b >= 0 && start_b < 64)
            palette_buffer[first_color + 2] = start_b;
        else {
            if (start_b > 0)
                palette_buffer[first_color + 2] = 63;
            else
                palette_buffer[first_color + 2] = 00;
        }
        //
        start_r += delta_r;
        start_g += delta_g;
        start_b += delta_b;
        //
        first_color += 3;
        count--;
    }
}

/* Copia aree video pió grandi di 4 per 1 pixels. */

void copia (unsigned char far *dest, unsigned char far *sorg, unsigned x, unsigned y, int l, int a)
{
    if (l<4) return;
    if (a<1) return;

    asm {
        push ax
        push bx
        push cx
        push dx
        push es
        push ds
        push si
        push di
        cld
    }

    x = 320*y + x;
    _BX = x + 320*a;
    _AX = x; _DX = l;

    asm {
        lds si, dword ptr sorg
        les di, dword ptr dest
        add bx, si
        add si, ax
        add di, ax
        mov ax, 320
        sub ax, dx
    }

chiclo: asm {
        cmp si, bx
        jnb fine
        mov cx, dx
        shr cx, 2
        db 0xf3 // macro: rep movsd
        db 0x66
        db 0xa5
        mov cx, dx
        and cx, 3
        rep movsb
        add si, ax
        add di, ax
        jmp chiclo
    }

fine:   asm {
        pop di
        pop si
        pop ds
        pop es
        pop dx
        pop cx
        pop bx
        pop ax
    }
}

/*

    Controllo visualizzazione.

*/

/* Imposta le proiezioni 3d dal punto di vista dell'astrozattera. */

void from_vehicle ()
{
    cam_x = dzat_x; cam_y = dzat_y; cam_z = dzat_z;
    alfa = user_alfa; beta = user_beta + navigation_beta + 180;
    if (beta>=360) beta -= 360;
    change_angle_of_view ();
}

/* Imposta le proiezioni 3d dal punto di vista del protagonista. */

void from_user ()
{
    cam_x = pos_x; cam_y = pos_y; cam_z = pos_z;
    alfa = user_alfa; beta = user_beta;
    change_angle_of_view ();
}

/* Orienta la videocamera virtuale verso un certo punto dato da see_x;y;z,
   frattalizzando l'angolo giro per fare pió in fretta. */

void watch (double cam_x, double cam_y, double cam_z,
        double see_x, double see_y, double see_z)
{
    double rx, ry, rz, w, ww, k, q, f1, f2, f3;
    double sinbeta, cosbeta, cosalfa;

    rx     = cam_x - see_x;
    ry     = cam_y - see_y;
    rz     = cam_z - see_z;
    w      = sqrt (rx*rx+ry*ry+rz*rz);

    see_x -= cam_x;
    see_y -= cam_y;
    see_z -= cam_z;

    f1     = 0;
    f2     = 0;

    f3     = 2 * M_PI;

    while (f3 > 0.02) {

        q       = 1e+111;
        ww      = f3 / 10;

        sinbeta = sin(beta);
        cosbeta = cos(beta);

        for (alfa=f2-f3; alfa<f2+f3; alfa+=ww) {
            rx  = - w * sinbeta * cos(alfa) - see_x;
            ry  = + w * sin(alfa)           - see_y;
            rz  = + w * cosbeta * cos(alfa) - see_z;
            k   = rx*rx + ry*ry + rz*rz;
            if (k<q) {
                q = k;
                f2 = alfa;
            }
        }

        alfa    = f2;

        ry      = w * sin(alfa) - see_y;
        ry     *= ry;

        cosalfa = cos(alfa);

        q       = 1e+111;
        ww      = f3 / 10;

        for (beta=f1-f3; beta<f1+f3; beta+=ww) {
            rx  = - w * sin(beta) * cosalfa - see_x;
            rz  = + w * cos(beta) * cosalfa - see_z;
            k   = rx*rx + ry + rz*rz;
            if (k<q) {
                q = k;
                f1 = beta;
            }
        }

        beta = f1;

        f3 /= 5;

    }

    alfa /= deg;
    beta /= deg;
}

/* Calcola lo scostamento x-y dal centro del video di un certo punto
   dato da point_x;y;z. Restituisce i valori in delta_x;y. */

char xy (double cam_x, double cam_y, double cam_z,
     double point_x, double point_y, double point_z)
{
    double xx, yy, zz, z2, rz;

    xx = point_x - cam_x;
    yy = point_y - cam_y;
    zz = point_z - cam_z;

    delta_x = xx * opt_pcosbeta + zz * opt_psinbeta;
    z2      = zz * opt_tcosbeta - xx * opt_tsinbeta;
    rz      = z2 * opt_tcosalfa + yy * opt_tsinalfa;
    delta_y = yy * opt_pcosalfa - z2 * opt_psinalfa;

    if (rz>0.001) {
        delta_x /= rz;
        delta_y /= rz;
        return (1);
    }

    return (0);
}

/* Sposta il protagonista all'interno dell'astrozattera. */

void p_Forward (float delta)
{
    pos_x -= delta * opt_tsinbeta * opt_tcosalfa;
    pos_z += delta * opt_tcosbeta * opt_tcosalfa;
}

/* Calcola la posizione di un certo pianeta in orbita attorno ad una certa
   stella (quella vicina), sulla base dei parametri orbitali (inclinazione,
   eccentricitÖ, raggio ed orientamento dell'asse maggiore) e ritorna i
   valori in plx, ply, plz. */

double mox, moy, moz;
void   moonorigin (int n)
{
    double xx;
    double p_riv, ors;
    double alfa, beta;

    ors = nearstar_p_orb_ray[n] * nearstar_p_orb_ray[n];
    p_riv = sqrt (s_m / ors);

    beta = (secs * p_riv * M_PI) / 180;
    alfa = nearstar_p_orb_tilt[n] * deg;

    xx  = -nearstar_p_orb_ray[n] * sin(beta) * cos(alfa);
    moz =  nearstar_p_orb_ray[n] * cos(beta) * cos(alfa);
    moy =  nearstar_p_orb_ray[n] * sin(alfa);

    moz *= nearstar_p_orb_ecc[n];

    beta = nearstar_p_orb_orient[n];

    mox = xx * cos(beta) + moz * sin(beta);
    moz = moz * cos(beta) - xx * sin(beta);
}

void planet_xyz (int n)
{
    double xx;
    double alfa, beta;
    double p_m, p_riv, ors;

    ors = nearstar_p_orb_ray[n] * nearstar_p_orb_ray[n];

    if (nearstar_p_owner[n] > -1) {
        xx = nearstar_p_ray[nearstar_p_owner[n]];
        p_m = qt_M_PI * xx * xx * xx * 0.44e-4;
        p_riv = sqrt (p_m / ors);
    }
    else
        p_riv = sqrt (s_m / ors);

    beta = (secs * p_riv * M_PI) / 180;
    alfa = nearstar_p_orb_tilt[n] * deg;

    xx  = -nearstar_p_orb_ray[n] * sin(beta) * cos(alfa);
    plz =  nearstar_p_orb_ray[n] * cos(beta) * cos(alfa);
    ply =  nearstar_p_orb_ray[n] * sin(alfa);

    plz *= nearstar_p_orb_ecc[n];

    beta = nearstar_p_orb_orient[n];

    plx = xx * cos(beta) + plz * sin(beta);
    plz = plz * cos(beta) - xx * sin(beta);

    plx += nearstar_x;
    ply += nearstar_y;
    plz += nearstar_z;

    if (nearstar_p_owner[n] > -1) {
        moonorigin (nearstar_p_owner[n]);
        plx += mox;
        ply += moy;
        plz += moz;
    }
}

/* Calcola il periodo di rivoluzione di un corpo, in secondi:
   per i pianeti, attorno alla stella;
   per le lune, attorno al pianeta...
   0.01e-7 ä l'equivalente, nel cosmo virtuale di Noctis,
   della costante gravitazionale. */

float rtp (int n)
{
    double p_m, p_riv, ors, xx;

    ors = nearstar_p_orb_ray[n] * nearstar_p_orb_ray[n];

    if (nearstar_p_owner[n] > -1) {
        xx = nearstar_p_ray[nearstar_p_owner[n]];
        p_m = qt_M_PI * xx * xx * xx * 0.44e-4;
        p_riv = sqrt (p_m / ors);
    }
    else
        p_riv = sqrt (s_m / ors);

    return (360 / p_riv);
}

/* Calcola la longitudine d'incidenza dello sguardo sulla superficie
   di un certo pianeta dato da (plx, ply, plz). L'osservatore ä posto
   nel punto (obs_x; obs_z) dato che la sua Y ä ininfluente... */

int planet_viewpoint (double obs_x, double obs_z)
{
    unsigned a;
    int plwp = 0;

    double xx;
    double zz;

    double min = 1E99;

    for (a=0; a<360; a++) {
        xx = plx + cos(deg*(double)a) - obs_x;
        zz = plz + sin(deg*(double)a) - obs_z;
        xx = xx*xx + zz*zz;
        if (xx<min) {
            plwp = a;
            min = xx;
        }
    }

    return (plwp);
}

int cplx_planet_viewpoint (int logical_id)
{
    int owner;

    double ownerplx;
    double ownerplz;

    if (nearstar_p_owner[logical_id] == -1)
        return (planet_viewpoint (nearstar_x, nearstar_z));

    owner = nearstar_p_owner[logical_id];
    if (nearstar_p_type[owner] == 10) {
        planet_xyz (owner);
        ownerplx = plx;
        ownerplz = plz;
        planet_xyz (logical_id);
        return (planet_viewpoint (ownerplx, ownerplz));
    }
    else
        return (planet_viewpoint (nearstar_x, nearstar_z));
}

/* Selezione effetti tramite variabile di controllo "flares". */

char previous_flares_value = 0;
void setfx (char fx) { previous_flares_value = flares; flares = fx; }
void chgfx (char fx) { flares = fx; }
void resetfx (void)  { flares = previous_flares_value; }

/* Tracciamento bastoncini (parte 2d). */

void Stick (unsigned long xp, unsigned long yp,
        unsigned long xa, unsigned long ya)
{
    long a, b, L;
    unsigned pi, pf;

    if (xp==xa) {
        if (ya>=yp) {
            pi = riga[yp] + xp;
            pf = riga[ya+1];
        }
        else {
            pi = riga[ya] + xp;
            pf = riga[yp+1];
        }
        asm {   les si, dword ptr adapted
            add pi, si
            add pf, si
            mov si, pi }
        switch (flares) {
            case 0:
            clu:    asm {   cmp si, pf
                    jnb _ret
                    mov word ptr es:[si], 0x3E00
                    add si, 320
                    jmp clu }
                break;
            case 1:
            _clu:   asm {   cmp si, pf
                    jnb _ret
                    mov cl, es:[si]
                    and cl, 0x3F
                    and byte ptr es:[si], 0xC0
                    add cl, 0x08
                    cmp cl, 0x3E
                    jb _cl_ok
                    mov cl, 0x3E }
            _cl_ok: asm {   add es:[si], cl
                    add si, 320
                    jmp _clu }
                break;
            case 2:
            __clu:  asm {   cmp si, pf
                    jnb _ret
                    mov cl, es:[si]
                    and cl, 0x3F
                    and byte ptr es:[si], 0xC0
                    shr cl, 1
                    add es:[si], cl
                    add si, 320
                    jmp __clu }
                break;
            case 3:
            ___clu: asm {   cmp si, pf
                    jnb _ret
                    db 0x66, 0x26, 0xC7, 0x04, 0x0E, 0x13, 0x1E, 0x2E // mov dword ptr es:[si], 0x2E1E130E
                    add si, 320
                    jmp ___clu }
        }
    _ret:   return;
    }

    asm {   db 0x66; mov si, word ptr xa
        db 0x66; sub si, word ptr xp
        jnc a_posit
        db 0x66; mov ax, word ptr xp
        db 0x66; mov bx, word ptr xa
        db 0x66; mov cx, word ptr yp
        db 0x66; mov dx, word ptr ya
        db 0x66; mov word ptr xa, ax
        db 0x66; mov word ptr xp, bx
        db 0x66; mov word ptr ya, cx
        db 0x66; mov word ptr yp, dx
        db 0x66; neg si }
a_posit:asm {   db 0x66; mov word ptr a, si
        db 0x66; mov word ptr L, si
             xor ch, ch
        db 0x66; mov ax, word ptr ya
        db 0x66; sub ax, word ptr yp
        jnc b_posit
             not ch
        db 0x66; neg ax }
b_posit:asm {   db 0x66; mov word ptr b, ax
        db 0x66; cmp ax, word ptr L
        jb b_lower
        db 0x66; mov word ptr L, ax }
b_lower:asm {   db 0x66; inc word ptr L
        db 0x66; shl word ptr xa, 16
        db 0x66; mov ax, word ptr xp
        db 0x66; mov bx, word ptr yp
        db 0x66; shl ax, 16
        db 0x66; shl bx, 16
        db 0x66; mov word ptr global_x, ax
        db 0x66; mov word ptr global_y, bx
        db 0x66; shl word ptr a, 16 // a *= 65536, unsigned
        db 0x66; sal word ptr b, 16 // b *= 65536, signed
             mov dx, word ptr a[2]
             mov ax, word ptr a
             div word ptr L     // a /= L, 16bit - unsigned
             mov word ptr a, ax
             mov word ptr a[2], 0
             mov dx, word ptr b[2]
             mov ax, word ptr b
             div word ptr L     // b /= L, 16bit - false unsigned
             mov word ptr b, ax
             mov word ptr b[2], 0
             test ch, ch
             jz trace
        db 0x66; neg word ptr b }

trace:  asm mov es, seg_adapted;

    switch (flares) {

        case 0: // bastoncini solidi che "riflettono" luce.

        asm {   db 0x66; mov ax, word ptr a    // passa in eax il delta_x (ovvero a).
            db 0x66; mov dx, word ptr b    // passa in edx il delta_y (ovvero b).
            db 0x66; mov cx, word ptr xa } // passa in ecx il limite superiore del ciclo (come coordinata x d'arrivo).

    _do:    asm {   mov bx, word ptr global_y[2]
            mov di, word ptr global_x[2]
            add bx, bx
           db 0x66; add word ptr global_x, ax
            add di, word ptr riga[bx]
           db 0x66; add word ptr global_y, dx
           db 0x66; cmp word ptr global_x, cx
            mov word ptr es:[di+4], 0x3E00
            jb  _do }

        break;

        case 1: // bastoncini intrinsecamente luminosi.

        asm {   db 0x66; mov ax, word ptr a    // passa in eax il delta_x (ovvero a).
            db 0x66; mov dx, word ptr b    // passa in edx il delta_y (ovvero b).

            db 0x66; shl ax, 1         // moltiplica i delta per 2:
            db 0x66; shl dx, 1         // un punto sç, uno no.

            push bp                // salva bp sullo stack
            db 0x66; mov bp, word ptr xa } // passa in ebp il limite superiore del ciclo (come coordinata x d'arrivo).

    __do:   asm {   mov bx, word ptr global_y[2]
            mov di, word ptr global_x[2]
            add bx, bx
           db 0x66; add word ptr global_x, ax
            add di, word ptr riga[bx]
           db 0x66; add word ptr global_y, dx
            mov cl, es:[di+4]
            shl cx, 2
            add cl, 32
            jnc cl_ok
            mov cl, 0xFB }
    cl_ok:  asm {   shr cx, 2
           db 0x66; cmp word ptr global_x, bp
            mov es:[di+4], cl
            jb __do }

        asm pop bp                 // riprende bp

        break;

        case 2: // bastoncini che assorbono luce ("affumicati").

        asm {   db 0x66; mov ax, word ptr a    // passa in eax il delta_x (ovvero a).
            db 0x66; mov dx, word ptr b    // passa in edx il delta_y (ovvero b).

            push bp                // salva bp sullo stack
            db 0x66; mov bp, word ptr xa } // passa in ebp il limite superiore del ciclo (come coordinata x d'arrivo).

    ___do:  asm {   mov bx, word ptr global_y[2]
            mov di, word ptr global_x[2]
            add bx, bx
           db 0x66; add word ptr global_x, ax
            add di, word ptr riga[bx]
           db 0x66; add word ptr global_y, dx
            mov cl, es:[di+4]
            and cl, 0x3F
            and byte ptr es:[di+4], 0xC0
            shr cl, 1
            add es:[di+4], cl
           db 0x66; cmp word ptr global_x, bp
            jb ___do }

        asm pop bp                 // riprende bp

        break;

        case 3: // come tipo 0, ma pió larghi.

        asm {   db 0x66; mov ax, word ptr a    // passa in eax il delta_x (ovvero a).
            db 0x66; mov dx, word ptr b    // passa in edx il delta_y (ovvero b).
            db 0x66; mov cx, word ptr xa } // passa in ecx il limite superiore del ciclo (come coordinata x d'arrivo).

    ____do: asm {   mov bx, word ptr global_y[2]
            mov di, word ptr global_x[2]
            add bx, bx
           db 0x66; add word ptr global_x, ax
            add di, word ptr riga[bx]
           db 0x66; add word ptr global_y, dx
           db 0x66; cmp word ptr global_x, cx
           db 0x66, 0x26, 0xC7, 0x45, 0x04 // mov dword ptr es:[di+4],
//         db 0x0E, 0x13, 0x1E, 0x2E       // 0x2E1E130E
           db 0xCE, 0xD3, 0xDE, 0xEE       // 0x2E1E130E
            jb  ____do }
    }
}

/* Tracciamento bastoncini (parte 3d). */

long fpx = -1; // first-point-x
long fpy;      // first-point-y

float p_rx, p_ry, p_rz;
float stick_uneg = 200;

void stick3d (float p_x, float p_y, float p_z,
          float x, float y, float z)
{
    long  lx, ly;

    float p_z2, diff;

    float rx, ry, rz, z2, kk;

    fpx = -1;

//  p_x -= cam_x;
//  p_y -= cam_y;
//  p_z -= cam_z;

//  p_z2 = p_z * opt_tcosbeta - p_x * opt_tsinbeta;
//  p_rz = p_z2 * opt_tcosalfa + p_y * opt_tsinalfa;

    asm {   fld p_x
        fsub cam_x
        fst p_x
        fmul opt_tsinbeta
        fld p_z
        fsub cam_z
        fst p_z
        fmul opt_tcosbeta
        fsubrp
        fst p_z2
        fmul opt_tcosalfa
        fld p_y
        fsub cam_y
        fst p_y
        fmul opt_tsinalfa
        faddp
        fstp p_rz }

//  x -= cam_x;
//  y -= cam_y;
//  z -= cam_z;

//  z2 = z * opt_tcosbeta - x * opt_tsinbeta;
//  rz = z2 * opt_tcosalfa + y * opt_tsinalfa;

    asm {   fld x
        fsub cam_x
        fst x
        fmul opt_tsinbeta
        fld z
        fsub cam_z
        fst z
        fmul opt_tcosbeta
        fsubrp
        fst z2
        fmul opt_tcosalfa
        fld y
        fsub cam_y
        fst y
        fmul opt_tsinalfa
        faddp
        fstp rz }

    if (rz<stick_uneg&&p_rz<stick_uneg) return;

//  p_rx = p_x * opt_pcosbeta + p_z * opt_psinbeta;
//  p_ry = p_y * opt_pcosalfa - p_z2 * opt_psinalfa;

    asm {   fld p_x
        fmul opt_pcosbeta
        fld p_z
        fmul opt_psinbeta
        faddp
        fstp p_rx
        fld p_y
        fmul opt_pcosalfa
        fld p_z2
        fmul opt_psinalfa
        fsubp
        fstp p_ry }

//  rx = x * opt_pcosbeta + z * opt_psinbeta;
//  ry = y * opt_pcosalfa - z2 * opt_psinalfa;

    asm {   fld x
        fmul opt_pcosbeta
        fld z
        fmul opt_psinbeta
        faddp
        fstp rx
        fld y
        fmul opt_pcosalfa
        fld z2
        fmul opt_psinalfa
        fsubp
        fstp ry }

    /* Conversione punti alle spalle dell'osservatore rispetto al piano
       dello schermo. */

    if (rz<stick_uneg) {
        diff = rz-p_rz;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stick_uneg-p_rz) / diff;
            rx = kk * (rx-p_rx) + p_rx;
            ry = kk * (ry-p_ry) + p_ry;
        }
        rz = stick_uneg;
    }
    else {
        if (p_rz<stick_uneg) {
            diff = p_rz-rz;
            if (diff<-mindiff || diff>mindiff) {
                kk = (stick_uneg-rz) / diff;
                p_rx = kk * (p_rx-rx) + rx;
                p_ry = kk * (p_ry-ry) + ry;
            }
            p_rz = stick_uneg;
        }
    }

    // Prospettiva.

//  lx = rx / rz; ly = ry / rz;
//  fpx = p_rx / p_rz; fpy = p_ry / p_rz;

    asm {   fld uno
        fdiv rz
        fld st(0)
        fmul rx
        fistp lx
        fmul ry
        fistp ly
        fld uno
        fdiv p_rz
        fld st(0)
        fmul p_rx
        fistp fpx
        fmul p_ry
        fistp fpy }

    if (fpy<stk_lby&&ly<stk_lby) return; // Linee del tutto fuori campo.
    if (fpy>stk_uby&&ly>stk_uby) return;
    if (fpx<stk_lbx&&lx<stk_lbx) return;
    if (fpx>stk_ubx&&lx>stk_ubx) return;

    /* Ottimizza il tracciamento del segmento, tagliando via le parti
       che di sicuro non si vedono. Questa parte non ä efficace se
       i punti di partenza e di arrivo fanno sç che il segmento non
       intersechi alcun lato dell'area visibile: ma in questo peculiare
       caso le linee vengono escluse dai controlli precedenti. */

    if (fpx<stk_lbx) {
        diff = fpx-lx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lbx-lx) / diff;
            fpy = kk * (fpy-ly) + ly;
            fpx = stk_lbx;
        }
    }
    if (lx<stk_lbx) {
        diff = lx-fpx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lbx-fpx) / diff;
            ly = kk * (ly-fpy) + fpy;
            lx = stk_lbx;
        }
    }
    if (fpy<stk_lby) {
        diff = fpy-ly;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lby-ly) / diff;
            fpx = kk * (fpx-lx) + lx;
            fpy = stk_lby;
        }
    }
    if (ly<stk_lby) {
        diff = ly-fpy;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lby-fpy) / diff;
            lx = kk * (lx-fpx) + fpx;
            ly = stk_lby;
        }
    }
    if (fpx>stk_ubx) {
        diff = fpx-lx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_ubx-lx) / diff;
            fpy = kk * (fpy-ly) + ly;
            fpx = stk_ubx;
        }
    }
    if (lx>stk_ubx) {
        diff = lx-fpx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_ubx-fpx) / diff;
            ly = kk * (ly-fpy) + fpy;
            lx = stk_ubx;
        }
    }
    if (fpy>stk_uby) {
        diff = fpy-ly;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_uby-ly) / diff;
            fpx = kk * (fpx-lx) + lx;
            fpy = stk_uby;
        }
    }
    if (ly>stk_uby) {
        diff = ly-fpy;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_uby-fpy) / diff;
            lx = kk * (lx-fpx) + fpx;
            ly = stk_uby;
        }
    }

    if (fpx==lx&&fpy==ly) return; // Esclude le linee costituite da un punto solo.

    Stick (fpx+x_centro, fpy+y_centro, lx+x_centro, ly+y_centro);
}

/* Se uno "stick" ä un "bastoncino" tridimensionale delimitato da due
   estremitÖ, un "link" ä un "ponte" tra il punto iniziale dell'ultimo stick
   tracciato ed il punto passato a questa funzione.
   Sembrerebbe un sistema efficace per velocizzare le proiezioni 3d, ma
   in realtÖ non si puï applicare sempre: a parte il fatto che uno dei punti
   ä sempre lo stesso, quando questo non ä risultato visibile in precedenza
   neanche i link saranno visibili.
   Attualmente, Noctis usa "link3d" per mostrare i singoli fili d'erba
   sulla superficie di pianeti abitabili. */

void link3d (float x, float y, float z)
{
    long lx, ly;

    float rx, ry, rz, z2;

    if (fpx == -1) return;

    if (fpy<=stk_lby) return;
    if (fpy>=stk_uby) return;

    if (fpx<=stk_lbx) return;
    if (fpx>=stk_ubx) return;

//  x -= cam_x;
//  y -= cam_y;
//  z -= cam_z;

//  z2 = z * opt_tcosbeta - x * opt_tsinbeta;
//  rz = z2 * opt_tcosalfa + y * opt_tsinalfa;

    asm {   fld x
        fsub cam_x
        fst x
        fmul opt_tsinbeta
        fld z
        fsub cam_z
        fst z
        fmul opt_tcosbeta
        fsubrp
        fst z2
        fmul opt_tcosalfa
        fld y
        fsub cam_y
        fst y
        fmul opt_tsinalfa
        faddp
        fstp rz }

    if (rz<stick_uneg) return;

//  rx = x * opt_pcosbeta + z * opt_psinbeta;
//  ry = y * opt_pcosalfa - z2 * opt_psinalfa;

    asm {   fld x
        fmul opt_pcosbeta
        fld z
        fmul opt_psinbeta
        faddp
        fstp rx
        fld y
        fmul opt_pcosalfa
        fld z2
        fmul opt_psinalfa
        fsubp
        fstp ry }

    // Prospettiva.

//  lx = rx / rz;
//  ly = ry / rz;

    asm {   fld uno
        fdiv rz
        fld st(0)
        fmul rx
        fistp lx
        fmul ry
        fistp ly }

    // Chopping.

    if (ly<=stk_lby) return;
    if (ly>=stk_uby) return;

    if (lx<=stk_lbx) return;
    if (lx>=stk_ubx) return;

    if (fpx==lx&&fpy==ly) return;

    Stick (fpx+x_centro, fpy+y_centro, lx+x_centro, ly+y_centro);
}

/* Tracciamento bastoncini luminosi (in 2d, per i bagliori,
   generalmente usata con il flag flares = 1). */

void fline (long fx, long fy,
        long lx, long ly)
{
    float kk, diff;

    /* Ottimizza il tracciamento del "Segmento", tagliando via le parti
       che di sicuro non si vedono. Questa parte non ä efficace se
       i punti di partenza e di arrivo fanno sç che il segmento non
       intersechi alcun lato dell'area visibile: ma in questo peculiare
       caso le linee vengono escluse dai controlli successivi. */

    if (fx<stk_lbx) {
        diff = fx-lx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lbx-lx) / diff;
            fy = kk * (fy-ly) + ly;
            fx = stk_lbx;
        }
    }
    if (lx<stk_lbx) {
        diff = lx-fx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lbx-fx) / diff;
            ly = kk * (ly-fy) + fy;
            lx = stk_lbx;
        }
    }
    if (fy<stk_lby) {
        diff = fy-ly;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lby-ly) / diff;
            fx = kk * (fx-lx) + lx;
            fy = stk_lby;
        }
    }
    if (ly<stk_lby) {
        diff = ly-fy;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_lby-fy) / diff;
            lx = kk * (lx-fx) + fx;
            ly = stk_lby;
        }
    }
    if (fx>stk_ubx) {
        diff = fx-lx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_ubx-lx) / diff;
            fy = kk * (fy-ly) + ly;
            fx = stk_ubx;
        }
    }
    if (lx>stk_ubx) {
        diff = lx-fx;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_ubx-fx) / diff;
            ly = kk * (ly-fy) + fy;
            lx = stk_ubx;
        }
    }
    if (fy>stk_uby) {
        diff = fy-ly;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_uby-ly) / diff;
            fx = kk * (fx-lx) + lx;
            fy = stk_uby;
        }
    }
    if (ly>stk_uby) {
        diff = ly-fy;
        if (diff<-mindiff || diff>mindiff) {
            kk = (stk_uby-fy) / diff;
            lx = kk * (lx-fx) + fx;
            ly = stk_uby;
        }
    }

    if (fx==lx&&fy==ly) return; // Esclude le linee costituite da un punto solo.

    if (fy<stk_lby||ly<stk_lby) return; // Esclude le linee che mai e poi mai si vedranno.
    if (fy>stk_uby||ly>stk_uby) return;
    if (fx<stk_lbx||lx<stk_lbx) return;
    if (fx>stk_ubx||lx>stk_ubx) return;

    Stick (fx+x_centro, fy+y_centro, lx+x_centro, ly+y_centro);
}

/* Funzione ricorsiva che suddivide poligoni triangolari in quattro parti
   ugualmente triangolari, casualizzandone leggermente la colorazione. */

unsigned char map_color_a = 30;
unsigned char map_color_b = 31;
unsigned char map_color_c = 32;
unsigned char map_color_d = 33;

void randomic_mapper (float x0,
              float y0,
              float z0,
              float x1,
              float y1,
              float z1,
              float x2,
              float y2,
              float z2,
              char divisions)
{
    float vx[3], vy[3], vz[3];

    float e0, f0, g0;
    float e1, f1, g1;
    float e2, f2, g2;

    divisions--;

    if (divisions) {
        e0 = (x0 + x1) * 0.5; f0 = (y0 + y1) * 0.5; g0 = (z0 + z1) * 0.5;
        e1 = (x1 + x2) * 0.5; f1 = (y1 + y2) * 0.5; g1 = (z1 + z2) * 0.5;
        e2 = (x0 + x2) * 0.5; f2 = (y0 + y2) * 0.5; g2 = (z0 + z2) * 0.5;
        if (divisions==1) {
            vx[0] = x0; vy[0] = y0; vz[0] = z0;
            vx[1] = e0; vy[1] = f0; vz[1] = g0;
            vx[2] = e2; vy[2] = f2; vz[2] = g2;
            poly3d (vx, vy, vz, 3, map_color_a);
            randomic_mapper (x0, y0, z0, e0, f0, g0, e2, f2, g2, divisions);
            vx[0] = e1; vy[0] = f1; vz[0] = g1;
            poly3d (vx, vy, vz, 3, map_color_b);
            randomic_mapper (e1, f1, g1, e0, f0, g0, e2, f2, g2, divisions);
            vx[1] = x2; vy[1] = y2; vz[1] = z2;
            poly3d (vx, vy, vz, 3, map_color_c);
            randomic_mapper (e1, f1, g1, x2, y2, z2, e2, f2, g2, divisions);
            vx[2] = x1; vy[2] = y1; vz[2] = z1;
            vx[1] = e0; vy[1] = f0; vz[1] = g0;
            poly3d (vx, vy, vz, 3, map_color_d);
            randomic_mapper (e1, f1, g1, e0, f0, g0, x1, y1, z1, divisions);
        }
        else {
            randomic_mapper (x0, y0, z0, e0, f0, g0, e2, f2, g2, divisions);
            randomic_mapper (e1, f1, g1, e0, f0, g0, e2, f2, g2, divisions);
            randomic_mapper (e1, f1, g1, x2, y2, z2, e2, f2, g2, divisions);
            randomic_mapper (e1, f1, g1, e0, f0, g0, x1, y1, z1, divisions);
        }
    }
}

/* Libera un handle in cui era stato caricato un file di grafica poligonale:
   se l'handle ä giÖ libero, non succede nulla. */

void unloadpv (int handle)
{
    int      h;
    unsigned eod;

    if (handle >= handles) return;
    if (!pvfile_datalen[handle]) return;

    // aggiorna i puntatori di tutti gli handle
    // che sono memorizzati oltre quello specificato.
    // il type cast serve per convincere le cacchio di specifiche ANSI
    // che il puntatore ä spostato byte per byte, e non come penserebbe
    // a seconda del tipo di dati a cui punta. se trovo quello che ha
    // definito l'ANSI cosç lo faccio nero.
    for (h = 0; h < handles; h++)
        if (pvfile_dataptr[h] > pvfile_dataptr[handle]) {
            (char far*)pv_n_vtx[h] -= pvfile_datalen[handle];
            (char far*)pvfile_x[h] -= pvfile_datalen[handle];
            (char far*)pvfile_y[h] -= pvfile_datalen[handle];
            (char far*)pvfile_z[h] -= pvfile_datalen[handle];
            (char far*)pvfile_c[h] -= pvfile_datalen[handle];
            if (pv_mid_x[h]) {
                (char far*)pv_mid_x[h] -= pvfile_datalen[handle];
                (char far*)pv_mid_y[h] -= pvfile_datalen[handle];
                (char far*)pv_mid_z[h] -= pvfile_datalen[handle];
                (char far*)pv_mid_d[h] -= pvfile_datalen[handle];
                (char far*)pv_dep_i[h] -= pvfile_datalen[handle];
            }
            pvfile_dataptr[h] -= pvfile_datalen[handle];
        }

    // sposta indietro i dati per liberare memoria nell'area poligonale.
    // (se ä necessario...)
    eod = pvfile_dataptr[handle] + pvfile_datalen[handle];
    if (eod < pvfile_datatop)
        _fmemmove (pv_n_vtx[handle],
               pv_n_vtx[handle] + pvfile_datalen[handle],
               pvfile_datatop - eod);

    // aggiorna la cima dei dati dell'area poligonale.
    pvfile_datatop -= pvfile_datalen[handle];

    // aggiorna la situazione della memoria per grafica poligonale,
    // in modo che l'handle sia ora considerato libero.
    pvfile_datalen[handle] = 0;
}

/* Libera tutti gli handles.
   (E non guarda in faccia a nessuno). */

void unloadallpv ()
{
    int h;

    pvfile_datatop = 0;

    for (h = 0; h < handles; h++)
        pvfile_datalen[h] = 0;
}

/* Carica un file di dati per la grafica poligonale.
   Se l'handle specificato era occupato, esso viene liberato e riassegnato.
    handle: numero della banca dati in cui ospitare il file, da 0 a 15;
    viturtual_file_position: offset negativo dalla fine di Noctis.EXE;
    x/y/z_scale: correzione in scala dei poligoni su tutti gli assi;
    x/y/z_move: traslazione dei poligoni su tutti gli assi;
    base_color: colore di base dei poligoni;
    depth_sort: flag che specifica se allocare spazio per il calcolo
            dei punti medi dei vertici di ogni poligono ed effettuare
            il depth-sorting quando si deve tracciare l'oggetto.
      * Ritorno: -1 se non ä possibile accedere al file;
          0 se l'handle non ä assegnabile (non esiste),
            oppure se non c'ä abbastanza memoria nel buffer
            della grafica poligonale ("pvfile") per caricare
            e/o gestire tutti i poligoni che compongono l'oggetto;
         +1 se tutto ä andato bene. */

char loadpv (int   handle, long virtual_file_position,
         float xscale, float yscale, float zscale,
         float xmove,  float ymove,  float zmove,
         unsigned char base_color,   char depth_sort)
{
    int fh, c, p;

    // verifica disponibilitÖ del file e dell'handle.
    if (handle >= handles) return (0);
    fh = sa_open (virtual_file_position);
    if (fh == -1) return (-1);

    // verifica se l'handle ä giÖ occupato. se lo ä, lo libera.
    if (pvfile_datalen[handle]) unloadpv (handle);

    // aggiornamento handle interno.
    pvfile_datalen[handle] = 0;
    pvfile_dataptr[handle] = pvfile_datatop;

    // lettura numero poligoni.
    _rtl_read (fh, &pvfile_npolygs[handle], 2);

    // preparazione puntatori.
    pv_n_vtx[handle] = (char far *)  (pvfile + pvfile_datatop);
    pvfile_datatop  +=  1 * pvfile_npolygs[handle];
    pvfile_x[handle] = (float far *) (pvfile + pvfile_datatop);
    pvfile_datatop  += 16 * pvfile_npolygs[handle];
    pvfile_y[handle] = (float far *) (pvfile + pvfile_datatop);
    pvfile_datatop  += 16 * pvfile_npolygs[handle];
    pvfile_z[handle] = (float far *) (pvfile + pvfile_datatop);
    pvfile_datatop  += 16 * pvfile_npolygs[handle];
    pvfile_c[handle] = (char far *)  (pvfile + pvfile_datatop);
    pvfile_datatop  +=  1 * pvfile_npolygs[handle];

    // azzera il primo puntatore dei dati per il depth sort
    // (sta a significare, se non viene successivamente modificato,
    // che non ä richiesto il depth sorting per l'oggetto in questione).
    pv_mid_x[handle] = 0;

    // verifica disponibilitÖ memoria prima di leggere i dati.
    if (pvfile_datatop > pv_bytes) {
        pvfile_datatop = pvfile_dataptr[handle];
        _rtl_close (fh);
        return (0);
    }

    // lettura di tutti i dati sui poligoni, in un unico blocco.
    _rtl_read (fh, pvfile + pvfile_dataptr[handle],
           pvfile_datatop - pvfile_dataptr[handle]);

    // dopodichÇ si puï anche richiudere il file...
    _rtl_close (fh);

    // azzeramento dati sui vertici non usati (per i triangoli)
    for (p=0; p<pvfile_npolygs[handle]; p++)
        if (pv_n_vtx[handle][p] == 3) {
            pvfile_x[handle][4*p+3] = 0;
            pvfile_y[handle][4*p+3] = 0;
            pvfile_z[handle][4*p+3] = 0;
        }

    // preparazione puntatori per la gestione del depth sorting.
    if (depth_sort) {
        pv_mid_x[handle] = (float far *) (pvfile + pvfile_datatop);
        pvfile_datatop  += 4 * pvfile_npolygs[handle];
        pv_mid_y[handle] = (float far *) (pvfile + pvfile_datatop);
        pvfile_datatop  += 4 * pvfile_npolygs[handle];
        pv_mid_z[handle] = (float far *) (pvfile + pvfile_datatop);
        pvfile_datatop  += 4 * pvfile_npolygs[handle];
        pv_mid_d[handle] = (float far *) (pvfile + pvfile_datatop);
        pvfile_datatop  += 4 * pvfile_npolygs[handle];
        pv_dep_i[handle] = (int far *)   (pvfile + pvfile_datatop);
        pvfile_datatop  += 2 * pvfile_npolygs[handle];
        // verifica disponibilitÖ memoria per i dati appena aggiunti.
        if (pvfile_datatop > pv_bytes) {
            pvfile_datatop = pvfile_dataptr[handle];
            return (0);
        }
    }

    // adattamento scala, colore e traslazione.
    for (c=0; c<4*pvfile_npolygs[handle]; c++) {
        pvfile_x[handle][c] *= xscale;
        pvfile_x[handle][c] += xmove;
        pvfile_y[handle][c] *= yscale;
        pvfile_y[handle][c] += ymove;
        pvfile_z[handle][c] *= zscale;
        pvfile_z[handle][c] += zmove;
        pvfile_c[handle][c] += base_color;
    }

    // calcolo punti medi e preparazione indici per il depth-sorting.
    if (depth_sort) {
        for (p=0; p<pvfile_npolygs[handle]; p++) {
            pv_dep_i[handle][p] = p;
            pv_mid_d[handle][p] = 0;
            pv_mid_x[handle][p] = 0;
            pv_mid_y[handle][p] = 0;
            pv_mid_z[handle][p] = 0;
            if (pv_n_vtx[handle][p]) {
                for (c=0; c<pv_n_vtx[handle][p]; c++) {
                    pv_mid_x[handle][p] += pvfile_x[handle][4*p+c];
                    pv_mid_y[handle][p] += pvfile_y[handle][4*p+c];
                    pv_mid_z[handle][p] += pvfile_z[handle][4*p+c];
                }
                pv_mid_x[handle][p] /= c;
                pv_mid_y[handle][p] /= c;
                pv_mid_z[handle][p] /= c;
            }
        }
    }

    // tutto fatto: computo memoria utilizzata da questo handle.
    pvfile_datalen[handle] = pvfile_datatop - pvfile_dataptr[handle];
    return (1);
}

/* Ordinamento a ricorsione. Per mettere in ordine in fretta i poligoni.
   Si occupa anche di altri ordinamenti per distanza... per esempio ordina
   i pianeti e le lune... */

void QuickSort (int far *index, float far *mdist, int start, int end)
{
    int   tq;

    int   jq = end;
    int   iq = start;

    float xq = mdist[index[(start+end)/2]];

    while (iq<=jq) {
        while (mdist[index[iq]] > xq) iq++;
        while (mdist[index[jq]] < xq) jq--;
        if (iq<=jq) {
            tq = index[iq];
            index[iq] = index[jq];
            index[jq] = tq;
            iq++;
            jq--;
        }
    }

    if (start < jq) QuickSort (index, mdist, start, jq);
    if (iq < end)   QuickSort (index, mdist, iq, end);
}

/* 
    Traccia una figura poligonale.
    handle: l'handle (da 0 a 15) che si ä attribuito al file con "loadpv";
    mode: puï essere -- 0 = tracciamento poligoni in tinta unita;
                1 = tracciamento con texture mapping;
                2 = rimappatura randomica ricorsiva dei poligoni.
    rm_iterations: viene usato solo se mode = 2, indica quante suddivisioni
            devono essere effettuate per ogni poligono rimappato;
    center_x/y/z: coordinate ove piazzare il centro dell'oggetto;
    use_depth_sort: flag per attivare il depth sort, che viene tuttavia
            effettivamente attivato solo se ä stato incluso come
            opzione nella chiamata a "loadpv" per quell'handle. 
*/

void drawpv (int handle, int mode, int rm_iterations,
         float center_x, float center_y, float center_z,
         char use_depth_sort) {
    float dx, dy, dz;
    unsigned p, c, i, k;

    if (handle >= handles) return;
    if (!pvfile_datalen[handle]) return;

    // traslazione intero spazio all'origine dell'oggetto.
    cam_x -= center_x;
    cam_y -= center_y;
    cam_z -= center_z;

    if (use_depth_sort && pv_mid_x[handle]) {
        // tracciamento con depth sorting.
        // fase 1: calcolo distanza punti medi.
        for (p=0; p<pvfile_npolygs[handle]; p++) {
            dx                  = pv_mid_x[handle][p] - cam_x;
            dy                  = pv_mid_y[handle][p] - cam_y;
            dz                  = pv_mid_z[handle][p] - cam_z;
            pv_mid_d[handle][p] = dx*dx + dy*dy + dz*dz;
        }
        // fase 2: ordinamento poligoni in base alla distanza.
        QuickSort (pv_dep_i[handle], pv_mid_d[handle],
               0, pvfile_npolygs[handle] - 1);
        // fase 3: tracciamento, nell'ordine specificato sopra.
        for (p=0; p<pvfile_npolygs[handle]; p++) {
            c = pv_dep_i[handle][p];
            i = c * 4;
            switch (mode) {
                case 0: poly3d (pvfile_x[handle] + i,
                        pvfile_y[handle] + i,
                        pvfile_z[handle] + i,
                        pv_n_vtx[handle][c],
                        pvfile_c[handle][c]);
                    break;
                case 1: k = pvfile_c[handle][c];
                    asm {   push    ax
                        mov     ax, k
                        and     ax, 0x3F
                        and     k,  0xC0
                        shr     ax, 1
                        or  k,  ax
                        pop ax }
                    polymap (pvfile_x[handle] + i,
                         pvfile_y[handle] + i,
                         pvfile_z[handle] + i,
                         pv_n_vtx[handle][c], k);
                    break;
                case 2: map_color_a = pvfile_c[handle][c];
                    map_color_b = map_color_a - 2;
                    map_color_c = map_color_a - 1;
                    map_color_d = map_color_a + 1;
                    randomic_mapper (pvfile_x[handle][i+0], pvfile_y[handle][i+0], pvfile_z[handle][i+0],
                             pvfile_x[handle][i+1], pvfile_y[handle][i+1], pvfile_z[handle][i+1],
                             pvfile_x[handle][i+2], pvfile_y[handle][i+2], pvfile_z[handle][i+2], rm_iterations);
                    if (pv_n_vtx[handle][p] == 4)
                        randomic_mapper (pvfile_x[handle][i+2], pvfile_y[handle][i+2], pvfile_z[handle][i+2],
                                 pvfile_x[handle][i+3], pvfile_y[handle][i+3], pvfile_z[handle][i+3],
                                 pvfile_x[handle][i+0], pvfile_y[handle][i+0], pvfile_z[handle][i+0], rm_iterations);
            }
        }
    }
    else {
        // tracciamento senza depth sorting.
        // in queso caso traccia i poligoni nell'ordine in cui
        // sono stati salvati nel file di grafica di "PolyVert".
        for (p=0, i=0; p<pvfile_npolygs[handle]; p++, i+=4)
            switch (mode) {
                case 0: poly3d (pvfile_x[handle] + i,
                        pvfile_y[handle] + i,
                        pvfile_z[handle] + i,
                        pv_n_vtx[handle][p],
                        pvfile_c[handle][p]);
                    break;
                case 1: k = pvfile_c[handle][p];
                    asm {   push    ax
                        mov     ax, k
                        and     ax, 0x3F
                        and     k,  0xC0
                        shr     ax, 1
                        or  k,  ax
                        pop ax }
                    polymap (pvfile_x[handle] + i,
                         pvfile_y[handle] + i,
                         pvfile_z[handle] + i,
                         pv_n_vtx[handle][p], k);
                    break;
                case 2: map_color_a = pvfile_c[handle][p];
                    map_color_b = map_color_a - 2;
                    map_color_c = map_color_a - 1;
                    map_color_d = map_color_a + 1;
                    randomic_mapper (pvfile_x[handle][i+0], pvfile_y[handle][i+0], pvfile_z[handle][i+0],
                             pvfile_x[handle][i+1], pvfile_y[handle][i+1], pvfile_z[handle][i+1],
                             pvfile_x[handle][i+2], pvfile_y[handle][i+2], pvfile_z[handle][i+2], rm_iterations);
                    if (pv_n_vtx[handle][p] == 4)
                        randomic_mapper (pvfile_x[handle][i+2], pvfile_y[handle][i+2], pvfile_z[handle][i+2],
                                 pvfile_x[handle][i+3], pvfile_y[handle][i+3], pvfile_z[handle][i+3],
                                 pvfile_x[handle][i+0], pvfile_y[handle][i+0], pvfile_z[handle][i+0], rm_iterations);
            }
    }

    // traslazione intero spazio all'origine precedente.
    cam_x += center_x;
    cam_y += center_y;
    cam_z += center_z;
}

/* Replica una forma poligonale, copiandola da un'handle giÖ definito
   a uno di uguali dimensioni. In caso d'errore, non succede nulla. */

void copypv (int dest_handle, int src_handle)
{
    if (src_handle >= handles) return;
    if (dest_handle >= handles) return;
    if (!pvfile_datalen[src_handle]) return;
    if (pvfile_datalen[dest_handle] != pvfile_datalen[src_handle]) return;
    _fmemmove (pv_n_vtx[dest_handle], pv_n_vtx[src_handle], pvfile_datalen[src_handle]);
}

/* Ruota una forma poligonale rispetto a uno dei suoi vertici,
   che viene assunto come centro di rotazione, applicando anche
   un fattore di scalatura (che puï essere 1 se non ä necessario
   cambiare le dimensioni, come possono essere 0 gli angoli se
   si stanno cambiando le dimensioni senza ruotare).
   "vertexs_to_affect" ä un puntatore a una serie di strutture "pvlist",
   nelle quali sono elencati i vertici che verranno effettivamente modificati:
   se il puntatore "vertexs_to_affect" ä nullo, tutti i vertici lo sono.
   Gli angoli sono espressi in gradi. */

void modpv (int handle, int polygon_id, int vertex_id,
        float x_scale, float y_scale, float z_scale,
        float x_angle, float y_angle, float z_angle,
        pvlist *vertexs_to_affect)
{
    if (handle >= handles) return;
    if (!pvfile_datalen[handle]) return;

    float sin_x = sin (deg * x_angle);
    float cos_x = cos (deg * x_angle);
    float sin_y = sin (deg * y_angle);
    float cos_y = cos (deg * y_angle);
    float sin_z = sin (deg * z_angle);
    float cos_z = cos (deg * z_angle);

    int   c, p, v, i, j;

    float x1, y1, z1;
    float cx, cy, cz;

    if (polygon_id > -1 && vertex_id > -1) {
        i = 4 * polygon_id + vertex_id;
        cx = pvfile_x[handle][i];
        cy = pvfile_y[handle][i];
        cz = pvfile_z[handle][i];
    }
    else {
        cx = 0;
        cy = 0;
        cz = 0;
    }

    if (!vertexs_to_affect) {
        for (p = 0; p < pvfile_npolygs[handle]; p++) {
            i = 4 * p;
            for (v = 0; v < pv_n_vtx[handle][p]; v++) {
                x1 = (pvfile_x[handle][i]-cx) * cos_y + (pvfile_z[handle][i]-cz) * sin_y;
                z1 = (pvfile_z[handle][i]-cz) * cos_y - (pvfile_x[handle][i]-cx) * sin_y;
                pvfile_z[handle][i] = z_scale * (z1 * cos_x + (pvfile_y[handle][i]-cy) * sin_x) + cz;
                y1 = (pvfile_y[handle][i]-cy) * cos_x - z1 * sin_x;
                pvfile_x[handle][i] = x_scale * (x1 * cos_z + y1 * sin_z) + cx;
                pvfile_y[handle][i] = y_scale * (y1 * cos_z - x1 * sin_z) + cy;
                i++;
            }
        }
    }
    else {
        p = 0;
        while (vertexs_to_affect[p].polygon_id != 0xFFF) {
            c = vertexs_to_affect[p].polygon_id;
            i = 4 * c;
            v = 0;
            do {    if (v==0 && vertexs_to_affect[p].vtxflag_0) { j = i;     goto perform; }
                if (v==1 && vertexs_to_affect[p].vtxflag_1) { j = i + 1; goto perform; }
                if (v==2 && vertexs_to_affect[p].vtxflag_2) { j = i + 2; goto perform; }
                if (v==3 && vertexs_to_affect[p].vtxflag_3) { j = i + 3; goto perform; }
                goto next;
               perform: x1 = (pvfile_x[handle][j]-cx) * cos_y + (pvfile_z[handle][j]-cz) * sin_y;
                z1 = (pvfile_z[handle][j]-cz) * cos_y - (pvfile_x[handle][j]-cx) * sin_y;
                pvfile_z[handle][j] = z_scale * (z1 * cos_x + (pvfile_y[handle][j]-cy) * sin_x) + cz;
                y1 = (pvfile_y[handle][j]-cy) * cos_x - z1 * sin_x;
                pvfile_x[handle][j] = x_scale * (x1 * cos_z + y1 * sin_z) + cx;
                pvfile_y[handle][j] = y_scale * (y1 * cos_z - x1 * sin_z) + cy;
              next: v ++;
            } while (v < pv_n_vtx[handle][c]);
            p ++;
        }
    }

    if (pv_mid_x[handle]) {
        for (p = 0; p < pvfile_npolygs[handle]; p++) {
            i = 4 * p;
            cx = 0; cy = 0; cz = 0;
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

/* Ritorna il corrispondente alfabetico di numeri interi e/o reali. */

char *alphavalue (double value)
{
    gcvt (value, 15, dec);
    return (dec);
}

/* Background, con la mappa offsets.map, in quicktime vr. */

void background (unsigned start,
         unsigned char far *target,
         unsigned char far *background,
         unsigned char far *offsetsmap,
         unsigned total_map_bytes,
         unsigned screenshift)
{
    asm {   pusha
        push ds
        les ax, dword ptr target
        add screenshift, ax
        mov dx, screenshift
        mov ax, es
        les bx, dword ptr background
        mov bx, es
        mov cx, total_map_bytes
        shr cx, 1
        lds si, dword ptr offsetsmap
        mov bp, start
        add bp, 4
        db 0x8E, 0xE3 // mov fs, bx
        mov es, ax }
rigiro: asm {   cmp word ptr [si], 64000
        jnb blanket
        mov di, [si]
        add di, dx
        db 0x64, 0x8A, 0x46, 0x00 // mov al, fs:[bp]
        mov ah, al
        db 0x66; shl ax, 8
        mov al, ah
        db 0x66; shl ax, 8
        mov al, ah
        db 0x66; mov es:[di], ax
        mov es:[di+4], al
        db 0x66; mov es:[di+320], ax
        mov es:[di+324], al
        db 0x66; mov es:[di+640], ax
        mov es:[di+644], al
        db 0x66; mov es:[di+960], ax
        mov es:[di+964], al
        db 0x66; mov es:[di+1280], ax
        mov es:[di+1284], al
        add bp, 1
        add si, 2
        dec cx
        jnz rigiro
        jmp fine }
blanket:asm {   mov bx, [si]
        sub bx, 64000
        add bp, bx
        add si, 2
        dec cx
        jnz rigiro }
fine:   asm {   pop ds
        popa }
}

/* Cielo stellato, tre-di vero. A campo amplificato, annovera 2744 stelle,
   con magnitudine da 0 a +13 (ho pensato che un gatto, con vista scotopica,
   e nello spazio, ne possa vedere parecchie di pió del normale...). */

void sky (unsigned limits)
{
    long min_xy = 1E9;

    char visible_sectors = 9;
    if (field_amplificator) visible_sectors = 14;

    unsigned char sx, sy, sz;
    float xx, yy, zz, z2, rz, inv_rz, starneg;

    if (!ap_targetting)
        starneg = 10000;
    else
        starneg = 1;

    long sect_x, sect_y, sect_z, rx, ry;
    long advance = 100000, k = 100000*visible_sectors;

    long temp_x, temp_y, temp_z, temp;

    /*  Il seguente frammento controlla la rarefazione delle stelle
        all'aumentare della distanza dal centro galattico. La scala
        sull'asse Y ä amplificata di 30 volte per matenere credibili
        le proporzioni della galassia che, pur essendo piuttosto
        ellittica (o grassottella), ha la forma di un disco
        schiacciato. Le stelle si rarefanno a seconda del valore
        di "distance_from_home". Questa ä una tabella che fornisce
        il numero di stelle eliminate (ogni settore contiene una
        stella, e il numero di settori visibili a campo amplificato
        ä di 14*14*14 = 2744) man mano che distance_from_home
        aumenta il suo valore:

        0-400.000.000           0 stelle eliminate
        400.000.000-800.000.000     1 su 2 stelle eliminate
        1.200.000.000-1.600.000.000 3 su 4 stelle eliminate
        1.600.000.000-2.000.000.000 7 su 8 stelle eliminate

        Oltre 2 miliardi di unitÖ, non ä pió permesso selezionare
        stelle: il rapporto di rarefazione sarebbe comunque di
        1 stella effettiva ogni 16 settori. */

    int rarity_factor;
    double distance_from_home;

    distance_from_home = sqrt (dzat_x*dzat_x + dzat_z*dzat_z);
    distance_from_home += 30 * fabs(dzat_y);
    rarity_factor = distance_from_home * 0.25e-8;
    rarity_factor = 1 << rarity_factor;
    rarity_factor--;

    sect_x = (dzat_x - visible_sectors*50000) / 100000; sect_x *= 100000;
    sect_y = (dzat_y - visible_sectors*50000) / 100000; sect_y *= 100000;
    sect_z = (dzat_z - visible_sectors*50000) / 100000; sect_z *= 100000;

    asm {   les ax, dword ptr adapted
        mov al, visible_sectors
        mov sx, al }
e_while:asm {   mov al, visible_sectors
        mov sy, al }
m_while:asm {   mov al, visible_sectors
        mov sz, al }
i_while:asm {   db 0x66, 0xBB, 0x50, 0xC3, 0x00, 0x00 // mov ebx, 50000
        db 0x66; mov ax, word ptr sect_x
        db 0x66; mov cx, word ptr sect_y
        db 0x66; mov dx, word ptr sect_z
        db 0x66, 0x0F, 0xAF, 0xCA // imul ecx, edx
        db 0x66; add ax, dx
        db 0x66; mov cx, ax
        db 0x66; mov dx, cx
        db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
        db 0x66; add dx, word ptr sect_x
        db 0x66; sub dx, bx
        jnz i_cont_x }  // |
        asm jmp next;   // | excludes stars with x coordinate = 0
i_cont_x: asm {                 // |
        db 0x66; mov word ptr temp_x, dx
        db 0x66; mov ax, cx
        db 0x66; imul dx
        db 0x66; add dx, ax
        db 0x66; add cx, dx
        db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
        db 0x66; add dx, word ptr sect_y
        db 0x66; sub dx, bx
        jnz i_cont_y }  // |
        asm jmp next;   // | excludes stars with y coordinate = 0
i_cont_y: asm {                 // |
        db 0x66; mov word ptr temp_y, dx
        db 0x66; mov ax, cx
        db 0x66; imul dx
        db 0x66; add dx, ax
        db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
        db 0x66; add dx, word ptr sect_z
        db 0x66; sub dx, bx
        jnz i_cont_z }  // |
        asm jmp next;   // | excludes stars with z coordinate = 0
i_cont_z: asm {                 // |
        db 0x66; mov word ptr temp_z, dx
        mov ax, word ptr temp_x
        add ax, word ptr temp_y
        add ax, word ptr temp_z
        test ax, rarity_factor
        jz ispresent
        jmp endgame }
ispresent:asm { fild dword ptr temp_z
        fsub dzat_z
        fst zz
        fmul opt_tcosbeta
        fild dword ptr temp_x
        fsub dzat_x
        fst xx
        fmul opt_tsinbeta
        fsubp
        fst z2
        fmul opt_tcosalfa
        fild dword ptr temp_y
        fsub dzat_y
        fst yy
        fmul opt_tsinalfa
        faddp
        fst rz
        fcomp starneg
        fstsw ax
        sahf
        jnb _123stella
        jmp endgame }
_123stella:asm {fld xx
        fmul opt_pcosbeta
        fld zz
        fmul opt_psinbeta
        faddp
        fld uno
        fdiv rz
        fst inv_rz
        fmulp
        fistp rx
        mov di, word ptr rx
        add di, x_centro
        cmp di, 10
        ja _x_low_ok
        jmp endgame }
_x_low_ok:asm { cmp di, 310
        jb _x_high_ok
        jmp endgame }
_x_high_ok:asm{ fld yy
        fmul opt_pcosalfa
        fld z2
        fmul opt_psinalfa
        fsubp
        fmul inv_rz
        fistp ry
            sub word ptr ry, 2
        mov bx, word ptr ry
        add bx, y_centro
        cmp bx, 10
        ja _y_low_ok
        jmp endgame }
_y_low_ok:asm { cmp bx, 190
        jb _y_high_ok
        jmp endgame }
_y_high_ok:asm{ shl bx, 1
        add di, word ptr riga[bx]
        cmp ap_targetting, 1
        je newgame
        cmp byte ptr es:[di+4], 68
        je endgame
        mov ax, limits
        cmp byte ptr es:[di+4], ah
        jb endgame
        cmp byte ptr es:[di+4], al
        ja endgame }
newgame: asm {  fld rz
        fistp temp
        mov cl, 13
        add cl, field_amplificator
        db 0x66; mov dx, word ptr temp
        db 0x66; shr dx, cl
        mov al, 63
        sub al, dl
        jc colorout
        mov dl, es:[di+4]
        and byte ptr es:[di+4], 0xC0
        and dl, 0x3F
        add al, dl
        cmp al, 63
        jbe colorin
        mov al, 63 }
colorin: asm {  or es:[di+4], al }
colorout:asm {  cmp ap_targetting, 1
        je extend }
endgame: asm    jmp next
extend: asm {   fild rx
        fmul st(0), st(0)
        fild ry
        fmul st(0), st(0)
        faddp
        fistp temp
        db 0x66; mov ax, word ptr temp
        db 0x66; cmp ax, word ptr min_xy
        jnb next
        db 0x66; mov word ptr min_xy, ax
        fild dword ptr temp_x
        fstp ap_target_x
        fild dword ptr temp_y
        fstp ap_target_y
        fild dword ptr temp_z
        fstp ap_target_z }
next:     asm { db 0x66; mov ax, word ptr advance
        db 0x66; add word ptr sect_z, ax
        dec sz
        jz i_end
        jmp i_while }
i_end:    asm { db 0x66; mov dx, word ptr k
        db 0x66; sub word ptr sect_z, dx
        db 0x66; add word ptr sect_y, ax
        dec sy
        jz m_end
        jmp m_while }
m_end:    asm { db 0x66; sub word ptr sect_y, dx
        db 0x66; add word ptr sect_x, ax
        dec sx
        jz e_end
        jmp e_while }
e_end:    // No more...
}

/* Ancora quicktime-vr, purtroppo ä necessaria: una sfera che poi puï essere
   un pianeta o una stella (non ä il caso di andare per il sottile).
   Usa un'enormitÖ di registri: salti mortali con le macro in codice macchina
   perchÇ il c++ non mi considera i registri estesi. Meglio ricapitolare:
   DS passa su GS, ES ä la pagina video (solitamente nascosta, non ä
   l'area dell'adattatore) specificata in target, FS ospita la tapestry,
   la tappezzeria da mappare sul globo, e il vecchio DS punta all'area
   della mappa degli offsets, compressa con il sistema di MAPS.EXE nella
   sua sezione X-Y. In effetti non sono offsets video giÖ pronti, perchÇ
   vanno calcolati (primo byte = Y, secondo byte = X). Quando la Y ä 100
   significa che l'offset originario era 64000 e che quindi non si tratta
   di un punto, ma di una serie di avanzamenti consecutivi lungo il
   segmento della tappezzeria, indicati per la precisione dal byte X. */

unsigned char glass_bubble = 1; // Se settato, disegna una specie di bolla
                // trasparente attorno ai globi tracciati con
                // la funzione "globe". Serve per simulare la
                // presenza dell'atmosfera, ma solo per i
                // pianeti che hanno CONSIDEREVOLI quantitÖ
                // di gas attorno.

/* Cacchio, dei veri e propri fill managers, e funzionano!
   Da non crederci, in C++, e pure dopo aver cambiato ES, FS e GS! */

void gman1x1 ()
{
    asm mov es:[di+4], dl
}

void gman2x2 ()
{
    asm {   mov dh, dl
        mov es:[di+4], dx
        mov es:[di+324], dx }
}

void gman3x3 ()
{
    asm {   mov dh, dl
        mov es:[di+4], dx
        mov es:[di+6], dl
        mov es:[di+324], dx
        mov es:[di+326], dl
        mov es:[di+644], dx
        mov es:[di+646], dl }
}

void gman4x4 ()
{
    asm {   mov dh, dl
        mov es:[di+4], dx
        mov es:[di+6], dx
        mov es:[di+324], dx
        mov es:[di+326], dx
        mov es:[di+644], dx
        mov es:[di+646], dx
        mov es:[di+964], dx
        mov es:[di+966], dx }
}

void globe (unsigned start,
        unsigned char far *target,
        unsigned char far *tapestry,
        unsigned char far *offsetsmap,
        unsigned total_map_bytes,
        double x, double y, double z,
        float mag_factor, char colormask, char globe_saturation)
{
    void    *gman;
    int center_x, center_y, temp;
    double  xx, yy, zz, z2, rx, ry, rz;

    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;

    rx = xx * (double)opt_pcosbeta + zz * (double)opt_psinbeta;
    z2 = zz * (double)opt_tcosbeta - xx * (double)opt_tsinbeta;
    rz = z2 * (double)opt_tcosalfa + yy * (double)opt_tsinalfa;
    ry = yy * (double)opt_pcosalfa - z2 * (double)opt_psinalfa;

    if (rz<0.001) return;

    mag_factor /= rz;
    gman = gman1x1;

    if (mag_factor<0.01) mag_factor = 0.001;
    if (mag_factor>0.33) gman = gman2x2;
    if (mag_factor>0.66) gman = gman3x3;
    if (mag_factor>0.99) gman = gman4x4;
    if (mag_factor>1.32) mag_factor = 1.32;

    rx /= rz; ry /= rz;

    /* 320 = Largh. schermo, 100 = max x/y pixels della mappa,
       1.32 = massimo fattore d'ingrandimento con punti di 4 pixels. */

    if (rx<-292||rx>292) return; // 292 = (320 / 2) + (100 * 1.32)
    if (ry<-232||ry>232) return; // 232 = (200 / 2) + (100 * 1.32)

    center_x = rx + x_centro_f;
    center_y = ry + y_centro_f;

    asm {   pusha
        push ds
        push ds
        db 0x0F, 0xA9 // pop gs
        mov cx, total_map_bytes
        shr cx, 1
        les ax, dword ptr tapestry
        add start, ax
        mov bx, start
        mov ax, es
        db 0x8E, 0xE0 // mov fs, ax
        les ax, dword ptr target
        lds si, dword ptr offsetsmap }
rigiro: asm {   cmp byte ptr [si], 100
        jne pixel
        jmp blanket }
pixel:  asm {   mov al, [si]
        cbw
        mov temp, ax
        fild word ptr temp
        fmul dword ptr mag_factor
        fistp word ptr temp
        mov di, temp
        add di, center_y
        cmp di, 6
        jb clipout
        cmp di, 191
        jnb clipout
        mov al, [si+1]      // istruzione di caricamento x #1
        add di, di
        cbw         // istruzione di caricamento x #2
        db 0x65, 0x8B, 0xBD /* mov di, gs:riga[di] - prima parte */
        dw offset riga      /* mov di, gs:riga[di] - 2nda parte */
        mov temp, ax        // istruzione di caricamento x #3
        fild word ptr temp
        fmul dword ptr mag_factor
        fistp word ptr temp
        mov ax, temp
        add ax, center_x
        cmp ax, 6
        jb clipout
        cmp ax, 311
        jnb clipout
        add di, ax
        db 0x64, 0x8A, 0x17 // mov dl, fs:[bx]
        cmp dl, globe_saturation
        jnb asis
        mov dl, globe_saturation }
asis:   asm {   or dl, colormask
        call [gman] }
clipout:asm {   add bx, 1
        add si, 2
        dec cx
        jz fine
        jmp rigiro }
blanket:asm {   mov al, [si+1]
        xor ah, ah
        add bx, ax
        add si, 2
        dec cx
        jz fine
        jmp rigiro }
fine:   asm {   pop ds
        popa }

    if (!glass_bubble) return;

    temp = mag_factor * 7.25;

    if (!temp) return;

    rx = mag_factor * 110;
    ry =(1.2 * deg) / mag_factor;
    rz = 0.5 * ry;
    z2 = 0.833 * rx;
    while (rz < 2*M_PI) {
        smootharound_64 (target,
                 center_x + rx*cos(rz),
                 center_y + z2*sin(rz), temp, 1);
        rz += ry;
    }
}

/* Come precedente, modificata per fare globi luminosi, senza dettagli
   ma con un evidente demarcazione fra emisfero illuminato e buio.
   Viene usata per i pianeti in media distanza. */

void glowinglobe (int start,
          unsigned char far *target,
          unsigned char far *offsetsmap,
          unsigned total_map_bytes,
          double x, double y, double z, float mag_factor,
          int terminator_start, int terminator_arc,
          unsigned char color)
{
    unsigned center_x, center_y, temp;
    double xx, yy, zz, z2, rx, ry, rz;

    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;

    rx = xx * (double)opt_pcosbeta + zz * (double)opt_psinbeta;
    z2 = zz * (double)opt_tcosbeta - xx * (double)opt_tsinbeta;
    rz = z2 * (double)opt_tcosalfa + yy * (double)opt_tsinalfa;
    ry = yy * (double)opt_pcosalfa - z2 * (double)opt_psinalfa;

    if (rz<0.001) return;

    mag_factor /= rz;

    if (mag_factor>0.66) mag_factor = 0.66;
    if (mag_factor<0.01) mag_factor = 0.001;

    rx /= rz; ry /= rz;

    /* 320 = Largh. schermo, 100 = max x/y pixels della mappa,
       0.66 = massimo fattore d'ingrandimento con punti di 4 pixels. */

    if (rx<-226||rx>226) return; // 172 = (320 / 2) + (100 * 0.66)
    if (ry<-166||ry>166) return; // 132 = (200 / 2) + (100 * 0.66)

    center_x = rx + x_centro_f;
    center_y = ry + y_centro_f;

    start -= terminator_start;
    while (start < 0) start += 360;

    asm {   pusha
        push ds
        push ds
        db 0x0F, 0xA9 // pop gs
        mov cx, total_map_bytes
        shr cx, 1
        mov bl, color
        and bl, 0xC0
        mov bh, color
        and bh, 0x3F
        shr bh, 2
        or  bh, bl
        mov bl, color
        mov dx, start
        les ax, dword ptr target
        lds si, dword ptr offsetsmap }
rigiro: asm {   cmp byte ptr [si], 100
        jne pixel
        jmp blanket }
pixel:  asm {   test dx, 3
        jz doit
        jmp clipout }
doit:   asm {   mov al, [si]
        cbw
        mov temp, ax
        fild word ptr temp
        fmul dword ptr mag_factor
        fistp word ptr temp
        mov di, temp
        add di, center_y
        cmp di, 10
        jnb y_ok
        cmp di, 190
        jb y_ok
        jmp clipout }
y_ok:   asm {   mov al, [si+1]
        add di, di
        cbw
        db 0x65, 0x8B, 0xBD /* mov di, gs:riga[di] */
        dw offset riga
        mov temp, ax
        fild word ptr temp
        fmul dword ptr mag_factor
        fistp word ptr temp
        mov ax, temp
        add ax, center_x
        cmp ax, 9
        jb  clipout
        cmp ax, 310
        jnb clipout
        add di, ax
        cmp dx, terminator_arc
        jb darkdot
        mov es:[di+4], bl
        jmp clipout }
darkdot:asm     mov es:[di+4], bh
clipout:asm {   add dx, 1
        cmp dx, 360
        jb rtn_ok
        xor dx, dx }
rtn_ok: asm {   add si, 2
        dec cx
        jz fine
        jmp rigiro }
blanket:asm {   mov al, [si+1]
        xor ah, ah
        add dx, ax }
rtj_lp: asm {   cmp dx, 360
        jb rtj_ok
        sub dx, 360
        jmp rtj_lp }
rtj_ok: asm {   add si, 2
        dec cx
        jz fine
        jmp rigiro }
fine:   asm {   pop ds
        popa }
}

/* Modificata per fare globi bianchi.
   Viene usata per le stelle viste da lontano, e per la corona stellare.
   Non ha bisogno della mappa dei globi. Color compreso fra 0 e 0x3F,
   perchÇ per maggior velocitÖ funziona sulla prima sfumatura. */

void whiteglobe (unsigned char far *target,
         double x, double y, double z,
         float mag_factor, float fgm_factor)
{
    double center_x, center_y, mag, fgm, shade_ext, ise;
    double xx, yy, zz, z2, rx, ry, rz, xa, ya, xb, yb;
    double magsq, fgmsq;

    unsigned pixptr;
    char pix;

    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;

    rx = xx * (double)opt_pcosbeta + zz * (double)opt_psinbeta;
    z2 = zz * (double)opt_tcosbeta - xx * (double)opt_tsinbeta;
    rz = z2 * (double)opt_tcosalfa + yy * (double)opt_tsinalfa;
    ry = yy * (double)opt_pcosalfa - z2 * (double)opt_psinalfa;

    if (rz<0.001) return;

    mag_factor /= rz;

    if (mag_factor>2.99) mag_factor = 2.99;
    if (mag_factor<0.01) mag_factor = 0.01;

    rx /= rz; ry /= rz;

    /* 320 = Largh. schermo, 100 = max x/y pixels della mappa,
       3.00 = massimo fattore d'ingrandimento con dispersione. */

    if (rx<-460||rx>460) return; // 460 = (320 / 2) + (100 * 3.00)
    if (ry<-400||ry>400) return; // 400 = (200 / 2) + (100 * 3.00)

    center_x = rx + x_centro_f + 0.5;
    center_y = ry + y_centro_f + 0.5;

    mag = mag_factor * 100 + 1.5;
    fgm = fgm_factor * mag; // full globe magnitude
    shade_ext = mag - fgm;
    if (shade_ext < 1) shade_ext = 1;
    ise = 0x3F / shade_ext;

    magsq = mag * mag;
    fgmsq = fgm * fgm;

    asm les dx, dword ptr target
    asm mov ax, es
    asm shr dx, 4
    asm add ax, dx
    asm db 0x8e, 0xe0 // mov fs, ax

    ya = - mag * 1.2;
    yb = center_y + mag;
    yy = center_y - mag;
    while (yy < yb) {
        xa = - mag;
        xb = center_x + mag;
        xx = center_x - mag;
        while (xx < xb) {
            if (xx > 9 && xx < 313 && yy > 9 && yy < 190) {
                zz = xa*xa + ya*ya;
                if (zz < magsq) {
                    if (zz > fgmsq)
                        pix = 0x3F - (sqrt(zz) - fgm) * ise;
                    else
                        pix = 0x3F;
                    pixptr = riga[(int)yy] + (int)xx;
                    pix += target[pixptr];
                    if (pix > 0x3F) {
                        asm {
                            mov di, pixptr
                            db 0x64, 0xC7, 0x45, 0x04, 0x3F, 0x3F
                            db 0x64, 0xC7, 0x85, 0x44, 0x01, 0x3F, 0x3F
                        }
                        //target[pixptr] = 0x3F;
                    }
                    else {
                        asm {
                            mov al, pix
                            mov di, pixptr
                            mov ah, al
                            db 0x64, 0x89, 0x45, 0x04
                            db 0x64, 0x89, 0x85, 0x44, 0x01
                        }
                        //target[pixptr] = pix;
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

/* Come sopra, ma mentre quella di sopra traccia in 4x4 pixels,
   dimezzando la risoluzione per essere pió veloce nel tracciamento
   di globi che possono coprire tutto lo schermo, questa traccia in 1x1,
   ä pió precisa ma applicabile solo alla visualizzazione delle stelle
   viste dai pianeti. */

double xsun_onscreen;

void whitesun (unsigned char far *target,
           double x, double y, double z,
           float mag_factor, float fgm_factor)
{
    double center_x, center_y, mag, fgm, shade_ext, ise;
    double xx, yy, zz, z2, rx, ry, rz, xa, ya, xb, yb;
    double magsq, fgmsq;

    unsigned pixptr;
    char pix;

    xx = x - dzat_x;
    yy = y - dzat_y;
    zz = z - dzat_z;

    rx = xx * (double)opt_pcosbeta + zz * (double)opt_psinbeta;
    z2 = zz * (double)opt_tcosbeta - xx * (double)opt_tsinbeta;
    rz = z2 * (double)opt_tcosalfa + yy * (double)opt_tsinalfa;
    ry = yy * (double)opt_pcosalfa - z2 * (double)opt_psinalfa;

    if (rz<0.001) return;

    mag_factor /= rz;

    if (mag_factor>2.99) mag_factor = 2.99;
    if (mag_factor<0.01) mag_factor = 0.01;

    rx /= rz; ry /= rz;
    xsun_onscreen = rx + x_centro_f;

    /* 320 = Largh. schermo, 100 = max x/y pixels della mappa,
       3.00 = massimo fattore d'ingrandimento con dispersione. */

    if (rx<-460||rx>460) return; // 460 = (320 / 2) + (100 * 3.00)
    if (ry<-400||ry>400) return; // 400 = (200 / 2) + (100 * 3.00)

    center_x = rx + x_centro_f + 0.5;
    center_y = ry + y_centro_f + 0.5;

    mag = mag_factor * 100 + 1.5;
    fgm = fgm_factor * mag; // full globe magnitude
    shade_ext = mag - fgm;
    if (shade_ext < 1) shade_ext = 1;
    ise = 0x3F / shade_ext;

    magsq = mag * mag;
    fgmsq = fgm * fgm;

    ya = - mag * 1.2;
    yb = center_y + mag;
    yy = center_y - mag;
    while (yy < yb) {
        xa = - mag;
        xb = center_x + mag;
        xx = center_x - mag;
        while (xx < xb) {
            if (xx > 9 && xx < 313 && yy > 9 && yy < 190) {
                zz = xa*xa + ya*ya;
                if (zz < magsq) {
                    if (zz > fgmsq)
                        pix = 0x3F - (sqrt(zz) - fgm) * ise;
                    else
                        pix = 0x3F;
                    pixptr = riga[(int)yy] + (int)xx;
                    pix += target[pixptr];
                    if (pix > 0x3F)
                        target[pixptr] = 0x3F;
                    else
                        target[pixptr] = pix;
                }
            }
            xa ++;
            xx ++;
        }
        ya += 1.2;
        yy ++;
    }
}

/* Bagliori attorno alle luci pió intense. */

/*float far *lft_sin = (float far *) farmalloc (361*4);
float far *lft_cos = (float far *) farmalloc (361*4);*/

float far lft_sin[361];
float far lft_cos[361];

char lens_flares_init ()
{
    int c;

    double a = 0, step = M_PI / 180;

    if (!lft_sin||!lft_cos) return (0);

    for (c = 0; c <= 360; c++) {
        lft_cos[c] = cos (a);
        lft_sin[c] = sin (a);
        a += step;
    }

    return (1);
}

void lens_flares_for (double cam_x, double cam_y, double cam_z,
              double xlight, double ylight, double zlight,
              double step, int added, char on_hud, char condition,
              int xshift, int yshift)
{
    double k = 10 / step, l = 1, u = 1.5;

    double xx, yy, zz, z2, rx, ry, rz;

    long xs, ys, dx, dy;
    float xr, yr;

    unsigned char temp;

    int c, r;

    setfx (1);

    xx = xlight - cam_x;
    yy = ylight - cam_y;
    zz = zlight - cam_z;

    rx = xx * (double)opt_pcosbeta + zz * (double)opt_psinbeta;
    z2 = zz * (double)opt_tcosbeta - xx * (double)opt_tsinbeta;
    rz = z2 * (double)opt_tcosalfa + yy * (double)opt_tsinalfa;
    ry = yy * (double)opt_pcosalfa - z2 * (double)opt_psinalfa;

    if (rz>1) {
        if (step<0)
            k = -step / rz;
        else
            k = 10 / step;
        xs = rx / rz + xshift;
        ys = ry / rz + yshift;
        if (xs>-150&&ys>-90&&xs<160&&ys<90) {
            switch (condition) {
                case 1: temp = adapted[xs+x_centro+riga[ys+y_centro]];
                    if (temp<64) goto exit_local;
                    break;
                case 2: temp = adapted[xs+x_centro+riga[ys+y_centro]];
                    if (temp<64||temp>127) goto exit_local;
                    break;
            }
            for (c=0; c<180; c+=added) {
                dx = lft_cos[c] * k * l;
                dy = lft_sin[c] * k * l;
                fline (xs-dx, ys-dy, xs+dx, ys+dy);
                if (on_hud && !(c%8)) {
                    dx /= 10; dy /= 10;
                    xr = (float)xs * -0.1;
                    yr = (float)ys * -0.1;
                    for (r = 0; r < 3; r++)  {
                        fline (xr-dx, yr-dy, xr+dx, yr+dy);
                        dx *= 4; dy *= 4;
                        xr *= 3; yr *= 3;
                    }
                }
                l *= u;
                if (l>3||l<1) u = 1 / u;
            }
        }
    }

    exit_local:
    resetfx ();
}

/* Puntini lontani, per esempio pianeti e lune.
   Le due funzioni si integrano: viene disegnato un puntino se la distanza
   ä grande. Man mano che ci si avvicina, il puntino diventa un dischetto,
   del diametro massimo di 5 pixels. Ovviamente, per fare dischi pió grandi,
   bisogna passare il controllo a un'altra funzione (sul tipo di globe). */

const double  pix_dst_scale = 0.384;
const double  pix_rad_scale = 1228.8;
#define       LIGHT_EMITTING    0
#define       LIGHT_ABSORBING   1
#define       MULTICOLOUR   2
char          pixilating_effect = LIGHT_EMITTING;
char          pixel_spreads = 1;
unsigned char multicolourmask = 0xC0;

void single_pixel_at_ptr (unsigned ptr, unsigned char pixel_color)
{
    _DX = ptr;
    _CL = pixel_color;

    switch (pixilating_effect) {
        case LIGHT_EMITTING:
        asm {   les di, dword ptr adapted
            add di, dx
            cmp byte ptr es:[di], 64
            jb c0vered
            mov al, es:[di]
            mov ah, es:[di]
            and al, 0x3F
            and ah, 0xC0
            add al, cl
            cmp al, 0x3E
            jbe grd_ok
            mov al, 0x3E }
    grd_ok: asm {   or  al, ah
            mov es:[di], al }
           c0vered: break;
        case LIGHT_ABSORBING:
        asm {   les di, dword ptr adapted
            add di, dx
            cmp byte ptr es:[di], 64
            jb c1vered
            mov al, es:[di]
            mov ah, es:[di]
            and al, 0x3F
            and ah, 0xC0
            add al, cl
            shr al, 1
            or  al, ah
            mov es:[di], al }
           c1vered: break;
        case MULTICOLOUR:
        asm {   les di, dword ptr adapted
            add di, dx
            cmp byte ptr es:[di], 64
            jb c2vered
            mov al, es:[di]
            mov ah, multicolourmask
            and al, 0x3F
            and ah, 0xC0
            add al, cl
            shr al, 1
            or  al, ah
            mov es:[di], al }
           c2vered: break;
    }
}

char far_pixel_at (double xlight, double ylight, double zlight,
           double radii, unsigned char unconditioned_color)
{
    double  xx, yy, zz, z2, rz;
    long    pixel_color;

    unsigned char edge_color_1;
    unsigned char edge_color_2;
    unsigned char edge_color_3;
    unsigned char edge_color_4;

    xx = xlight - dzat_x;
    yy = ylight - dzat_y;
    zz = zlight - dzat_z;

    pxx = xx * opt_pcosbeta + zz * opt_psinbeta;
    z2  = zz * opt_tcosbeta - xx * opt_tsinbeta;
    rz  = z2 * opt_tcosalfa + yy * opt_tsinalfa;
    pyy = yy * opt_pcosalfa - z2 * opt_psinalfa;

    if (rz>0.001) {
        if (!unconditioned_color) {
            pixel_color = 64 - (rz * pix_dst_scale) + (radii * pix_rad_scale);
            if (pixel_color > 63) pixel_color = 63;
            if (pixel_color < 0) pixel_color = 0;
        }
        else
            pixel_color = unconditioned_color;
        pxx /= rz; pxx += x_centro;
        pyy /= rz; pyy += y_centro;
        if (pxx>10&&pyy>10&&pxx<310&&pyy<190) {
            vptr = 320*(int)pyy + pxx;
            if (pixel_spreads) {
                edge_color_1 = pixel_color >> 1;
                edge_color_2 = pixel_color >> 2;
                edge_color_3 = pixel_color >> 3;
                edge_color_4 = pixel_color >> 4;
                if (edge_color_1 > 7) {
                    single_pixel_at_ptr (vptr - 320, edge_color_1);
                    single_pixel_at_ptr (vptr + 320, edge_color_1);
                    single_pixel_at_ptr (vptr -   1, edge_color_1);
                    single_pixel_at_ptr (vptr +   1, edge_color_1);
                }
                if (edge_color_2 > 7) {
                    single_pixel_at_ptr (vptr - 321, edge_color_2);
                    single_pixel_at_ptr (vptr - 319, edge_color_2);
                    single_pixel_at_ptr (vptr + 321, edge_color_2);
                    single_pixel_at_ptr (vptr + 319, edge_color_2);
                }
                if (edge_color_3 > 7) {
                    single_pixel_at_ptr (vptr - 640, edge_color_3);
                    single_pixel_at_ptr (vptr + 640, edge_color_3);
                    single_pixel_at_ptr (vptr -   2, edge_color_3);
                    single_pixel_at_ptr (vptr +   2, edge_color_3);
                }
                if (edge_color_4 > 7) {
                    single_pixel_at_ptr (vptr - 641, edge_color_4);
                    single_pixel_at_ptr (vptr - 639, edge_color_4);
                    single_pixel_at_ptr (vptr + 641, edge_color_4);
                    single_pixel_at_ptr (vptr + 639, edge_color_4);
                    single_pixel_at_ptr (vptr - 322, edge_color_4);
                    single_pixel_at_ptr (vptr - 318, edge_color_4);
                    single_pixel_at_ptr (vptr + 322, edge_color_4);
                    single_pixel_at_ptr (vptr + 318, edge_color_4);
                }
                if (pixel_color > 7)
                    single_pixel_at_ptr (vptr, pixel_color);
            }
            else {
                if (pixel_color)
                    single_pixel_at_ptr (vptr, pixel_color);
            }
            return (1);
        }
    }

    return (0);
}

/*

    Resto delle funzioni che operano su dati locali.
    Funzioni per: regolazione del timer cosmico di NOCTIS,
              costruzione dei dintorni delle stelle e dei pianeti,
              visualizzazione dei pianeti dall'orbita.

*/

/* Misura il tempo trascorso dal 1-1-1984 ad oggi, con la precisione di
   un fotogramma (in media, 1/25 di secondo). */

void getsecs ()
{
    int m;

    char dfm[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    asm {   mov ah, 4
        int 0x1a
        lea bx, year
        mov ah, ch
        shr ah, 4
        mov al, ch
        and al, 0xF
        add ax, '00'
                xchg al, ah
        mov [bx], ax
        mov ah, cl
        shr ah, 4
        mov al, cl
        and al, 0xF
        add ax, '00'
        xchg al, ah
        mov [bx+2], ax
        lea bx, month
        mov ah, dh
        shr ah, 4
        mov al, dh
        and al, 0xF
        add ax, '00'
        xchg al, ah
        mov [bx], ax
        lea bx, day
        mov ah, dl
        shr ah, 4
        mov al, dl
        and al, 0xF
        add ax, '00'
        xchg al, ah
        mov [bx], ax
        mov ah, 2
        int 0x1a
        lea bx, hours
        mov ah, ch
        shr ah, 4
        mov al, ch
        and al, 0xF
        add ax, '00'
        xchg al, ah
        mov [bx], ax
        lea bx, minutes
        mov ah, cl
        shr ah, 4
        mov al, cl
        and al, 0xF
        add ax, '00'
        xchg al, ah
        mov [bx], ax
        lea bx, seconds
        mov ah, dh
        shr ah, 4
        mov al, dh
        and al, 0xF
        add ax, '00'
        xchg al, ah
        mov [bx], ax }

    secs = atol (year) - 1984;            // anni dal 1984
    secs = secs * 365 + (long)(secs / 4);         // anni * 365 + anni / 4

    for (m=1; m<atoi(month); m++)
        secs += dfm[m];               // giorni per mese

    if (atoi(month)>2 && !(atol(year)%4)) secs++; // se l'anno ä bisestile

    secs += atoi(day) - 1;                // + giorni mese attuale
    secs *= 86400;                                // secondi in un giorno

    secs += 3600 * atol(hours);           // ora corrente in sec.
    secs += 60 * atoi(minutes);           // minuti corr. in sec.

    isecs = atoi(seconds);                // secondi correnti.
    secs += isecs;

    if (p_isecs != isecs) {               // timing dei fotogrammi
        if (_delay>=10) _delay--;
        p_isecs = isecs;
        gl_fps = fps;
        fps = 1;
    }
    else {                        // frazioni di secondo
        if (gl_fps) secs += (double)fps / (double)gl_fps;
        fsecs = (double)fps / (double)gl_fps;
        fps++;
    }

    epoc = 6011 + secs / 1e9;
}

/* Estrae dalla tabella pseudo, da 74000 miliardi di elementi diversi, le
   informazioni sulla stella che si ä scelta. */

void extract_ap_target_infos ()
{
    srand (ap_target_x/100000*ap_target_y/100000*ap_target_z/100000);

    ap_target_class = random (star_classes);
    ap_target_ray = ((float)class_ray[ap_target_class] + (float)random(class_rayvar[ap_target_class])) * 0.001;

    ap_target_r = class_rgb[3*ap_target_class+0];
    ap_target_g = class_rgb[3*ap_target_class+1];
    ap_target_b = class_rgb[3*ap_target_class+2];

    ap_target_spin = 0;
    if (ap_target_class==11) ap_target_spin = random (30) + 1;
    if (ap_target_class==7) ap_target_spin = random (12) + 1;
    if (ap_target_class==2) ap_target_spin = random (4) + 1;
}

/* Estrae un numero pseudo-casuale di tipo intero convertendolo a f-p. */

float zrandom (int range) { return (random(range) - random(range)); }

/* Parte della gestione della cartografia.
   E' stata spostata qui perchÇ possa essere chiamata da "prepare_nearstar".
   -------------------------------------------------------------------------
   Cerca un codice d'identificazione (per un pianeta o per una stella)
   nel file di cartografia stellare, e riporta la posizione del record.
   Se il risultato ä -1, il codice non esiste, ovvero non c'ä un nome
   per la stella o per il pianeta che corrisponde a quel codice.
   Type puï essere: P = Pianeta, S = Stella.
   * usa come buffer di lettura "p_surfacemap". */

int smh;
double  idscale = 0.00001;

long search_id_code (double id_code, char type)
{
    long        pos = 4;
    char        found = 0;
    unsigned    n, ptr, index;

    char far    *buffer_ascii = (char far *)p_surfacemap;
    double far  *buffer_double = (double far *)p_surfacemap;

    double      id_low = id_code - idscale;
    double      id_high = id_code + idscale;

    smh = _rtl_open (starmap_file, 0);
    if (smh > -1) {
        lseek (smh, 4, SEEK_SET);
        while ((n = _rtl_read (smh, buffer_ascii, ps_bytes)) > 0) {
            ptr = 0;
            index = 0;
            while (ptr < n) {
                if (buffer_ascii[ptr + 29] == type) {
                    if (buffer_double[index] > id_low &&
                        buffer_double[index] < id_high) {
                        found = 1;
                        goto stop;
                    }
                }
                pos   += 32;
                ptr   += 32;
                index += 4;
            }
        }
        stop:
        _rtl_close (smh);
    }

    if (found)
        return (pos);
    else
        return (-1);
}

/* Prepara le informazioni sulla stella vicina, quella attorno alla quale
   ci si troverÖ: tra l'altro, prepara i pianeti estraendoli dalla
   tabella pseudo. */

int starnop (double star_x, double star_y, double star_z)
// stima il numero di pianeti maggiori associato alle coord. di una stella
{
    int r;
    srand ((long)star_x%10000*(long)star_y%10000*(long)star_z%10000);
    r = random (class_planets[ap_target_class] + 1);
    r += random (2);
    r -= random (2);
    if (r < 0) r = 0;
    return (r);
}

void prepare_nearstar ()
{
    int    n, c, q, r, s, t;
    double key_radius;

    if (!_delay) {
        nearstar_class = ap_target_class;
        nearstar_x = ap_target_x;
        nearstar_y = ap_target_y;
        nearstar_z = ap_target_z;
        nearstar_ray = ap_target_ray;
        nearstar_spin = ap_target_spin;
        nearstar_r = ap_target_r;
        nearstar_g = ap_target_g;
        nearstar_b = ap_target_b;
    }

    s_m = qt_M_PI * nearstar_ray * nearstar_ray * nearstar_ray * 0.01e-7;

    nearstar_identity = nearstar_x/100000*nearstar_y/100000*nearstar_z/100000;

    srand ((long)nearstar_x%10000*(long)nearstar_y%10000*(long)nearstar_z%10000);

    nearstar_nop = random (class_planets[nearstar_class] + 1);

    /* Prima estrazione (pressochÇ casuale, non realistica). */

    for (n=0; n<nearstar_nop; n++) {
        nearstar_p_owner[n]  = -1;
        nearstar_p_orb_orient[n] = (double) deg * (double) random (360);
        nearstar_p_orb_seed[n]   = 3 * (n*n+1) * nearstar_ray + (float) random (300 * nearstar_ray) / 100;
        nearstar_p_tilt[n]       = zrandom (10*nearstar_p_orb_seed[n]) / 500;
        nearstar_p_orb_tilt[n]   = zrandom (10*nearstar_p_orb_seed[n]) / 5000;
        nearstar_p_orb_ecc[n]    = 1 - (double) random (nearstar_p_orb_seed[n] + 10*fabs(nearstar_p_orb_tilt[n])) / 2000;
        nearstar_p_ray[n]        = (double) random (nearstar_p_orb_seed[n]) * 0.001 + 0.01;
        nearstar_p_ring[n]   = zrandom (nearstar_p_ray[n]) * (1 + (double) random (1000) / 100);
        if (nearstar_class != 8)
            nearstar_p_type[n] = random (planet_types);
        else {
            if (random(2)) {
                nearstar_p_type[n] = 10;
                nearstar_p_orb_tilt[n] *= 100;
            }
            else
                nearstar_p_type[n] = random (planet_types);
        }
        if (nearstar_class==2||nearstar_class==7||nearstar_class==15)
            nearstar_p_orb_seed[n] *= 10;
    }

    /* Aumento delle probabilitÖ di pianeti abitabili su classe zero. */

    if (!nearstar_class) {
        if (random(4)==2) nearstar_p_type[2] = 3;
        if (random(4)==2) nearstar_p_type[3] = 3;
        if (random(4)==2) nearstar_p_type[4] = 3;
    }

    /* Eliminazione di pianeti impossibili attorno a certe stelle.
       Fase 1: solo quelli impossibili per tipo di stella. */

    for (n=0; n<nearstar_nop; n++) {
        switch (nearstar_class) {
            case 2: while (nearstar_p_type[n]==3)
                    nearstar_p_type[n] = random (10);
                break;
            case 5: while (nearstar_p_type[n]==6||
                       nearstar_p_type[n]==9)
                    nearstar_p_type[n] = random (10);
                break;
            case 7: nearstar_p_type[n] = 9;
                break;
            case 9: while (nearstar_p_type[n]!=0&&
                       nearstar_p_type[n]!=6&&
                       nearstar_p_type[n]!=9)
                    nearstar_p_type[n] = random (10);
                break;
            case 11:while (nearstar_p_type[n]!=1&&
                       nearstar_p_type[n]!=7)
                    nearstar_p_type[n] = random (10);
        }
    }

    /* Eliminazione di pianeti impossibili attorno a certe stelle.
       Fase 2: solo quelli impossibili per distanza dalla stella. */

    for (n=0; n<nearstar_nop; n++) {
        switch (nearstar_p_type[n]) {
            case 0:
                if (random(8))
                    nearstar_p_type[n] ++;
                break;
            case 3:
                if ((n<2)||(n>6)||(nearstar_class&&random(4))) {
                    if (random(2))
                        nearstar_p_type[n]++;
                    else
                        nearstar_p_type[n]--;
                }
                break;
            case 7:
                if (n<7) {
                    if (random(2))
                        nearstar_p_type[n] --;
                    else
                        nearstar_p_type[n] -= 2;
                }
                break;
        }
    }

    /* Estrazione dei satelliti naturali (lune). */

    nearstar_nob = nearstar_nop;

    if (nearstar_class==2||nearstar_class==7||nearstar_class==15)
        goto no_moons;

    for (n=0; n<nearstar_nop; n++) {
        // (t=) Numero di satelliti per pianeta.
        s = nearstar_p_type[n];
        if (n < 2) {
            t = 0;
            if (s == 10)
                t = random (3);
        }
        else
            t = random (planet_possiblemoons[s] + 1);
        if (nearstar_nob + t > maxbodies)
            t = maxbodies - nearstar_nob;
        // Caratteristiche dei satelliti.
        for (c=0; c<t; c++) {
            q            = nearstar_nob + c;
            nearstar_p_owner[q]  = n;
            nearstar_p_moonid[q]     = c;
            nearstar_p_orb_orient[q] = (double) deg * (double) random (360);
            nearstar_p_orb_seed[q]   = (c*c+4) * nearstar_p_ray[n] + (float) zrandom (300 * nearstar_p_ray[n]) / 100;
            nearstar_p_tilt[q]       = zrandom (10*nearstar_p_orb_seed[q]) / 50;
            nearstar_p_orb_tilt[q]   = zrandom (10*nearstar_p_orb_seed[q]) / 500;
            nearstar_p_orb_ecc[q]    = 1 - (double) random (nearstar_p_orb_seed[q] + 10*fabs(nearstar_p_orb_tilt[q])) / 2000;
            nearstar_p_ray[q]        = (double) random (nearstar_p_orb_seed[n]) * 0.05 + 0.1;
            nearstar_p_ring[q]   = 0;
            nearstar_p_type[q]       = random (planet_types);
            // Estrazione tipologia di satellite:
            r = nearstar_p_type[q];
            // Un oggetto substellare come luna?
            // Ce lo puï avere solo una stella compagna.
            if (r==9 && s != 10) r = 2;
            // Un gigante gassoso come luna?
            // Ce lo puï avere solo un oggetto substellare,
            // o una stella compagna in un sistema multiplo.
            if (r==6 && s < 9) r = 5;
            // "Raffreddamento" satelliti esterni, lontani sia
            // dal pianeta che dalla stella, in genere congelati.
            if (n > 7 && random(c)) r = 7;
            if (n > 9 && random(c)) r = 7;
            // Lune relativamente grandi possono esistere solo
            // attorno a pianeti gassosi ed oggetti substellari.
            // Invece, i simil-lunari(1), i simil-marziani(5),
            // le lune come Io(0), e quelle come Europa(7),
            // possono esistere anche attorno ad altri tipi di
            // pianeti, ma di certo in scala piuttosto ridotta.
            if (r==2 || r==3 || r==4 || r==8) {
                if (s != 6 && s < 9)
                    r = 1;
            }
            // Attorno ai giganti gassosi, se il test precedente
            // ä passato (s = 6/9/10, gassoso/substellare/stella),
            // bä, possono anche esserci, a certe condizioni,
            // delle lune abitabili. Per queste, perï, la stella
            // dev'essere in genere di classe zero ed il pianeta
            // gigante non dev'essere troppo lontano dalla stella.
            // C'ä invece uguale probabilitÖ di trovare mondi
            // abitabili attorno agli oggetti substellari: al di
            // lÖ della distanza dalla stella, tali lune possono
            // essere scaldate abbastanza da una stella mancata.
            if (r==3 && s < 9) {
                if (n > 7)
                    r = 7;
                if (nearstar_class && random(4))
                    r = 5;
                if (nearstar_class == 2 ||
                    nearstar_class == 7 ||
                    nearstar_class == 11)
                    r = 8;
            }
            // Una luna ghiacciata ä esclusa, prima di arrivare
            // almeno alla sesta orbita planetaria, perchÇ fa
            // comunque troppo caldo.
            if (r==7 && n <= 5) r = 1;
            // Ma lune ghiacciate sono comunque molto pió
            // frequenti se la stella ä molto piccola e fredda:
            // un pianeta in genere puï avere meccanismi interni
            // che lo scaldano. Una luna no.
            if ((nearstar_class==2||nearstar_class==5||
                 nearstar_class==7||nearstar_class==11)
                 && random(n)) r = 7;
            // Fine estrazione tipologia di satellite.
            nearstar_p_type[q] = r;
        }
        nearstar_nob += t;
    }

    /* Ri-Normalizzazione delle dimensioni dei pianeti,
       normalizzazione delle orbite in base al principio di Keplero.
       Il principio di Keplero stabilisce che il raggio dell'orbita di
       un pianeta tende ad essere simile alla sommatoria dei raggi delle
       orbite di tutti i pianeti interni ad esso. Perï, per un numero di
       pianeti maggiore di 8, il principio non ä pió valido. Noctis
       rinormalizza le orbite oltre l'ottava, aggiungendo a tali orbite
       il 22% circa della sommatoria delle precedenti. Ovvero:

       SE si applica il principio di Keplero
       per (ad esempio) 12 pianeti, e per Raggio Prima Orbita = 1,
       allora i raggi delle altre orbite sarebbero:
       *    1  2  3  6  12  24  48  96  192  384  768  1536

       SE si applica l'organizzazione di Noctis, il tutto diventerebbe:
       *    1  2  3  6  12  24  48  96  117  143  174  212

       Il 22% non ä un valore a caso: rappresenta all'incirca il rapporto
       fra i raggi delle orbite di Plutone e di Urano. Plutone ä circa del
       22% pió lontano dal Sole di Urano, cioä l'ottava orbita. Ovvio che
       non significa che un sistema planetario pió vasto debba per forza
       avere orbite organizzate in questo modo, anche perchÇ Plutone non
       ä certo un pianeta "naturalmente" formatosi assieme agli altri, ma
       pió probabilmente un satellite sfuggito o un corpo della nube di
       Oort catturato dal Sole. Perï bisogna dire che le influenze delle
       orbite dei pianeti interni, col proseguire della successione di
       Keplero, diventano sempre meno significative. Penso che tale
       successione, semplicemente, debba essere in qualche modo limitata,
       a un certo punto: ä improbabile che ci siano pianeti in orbita
       stabile a distanze come quelle risultanti per le orbite oltre
       l'ottava. Noctis annovera anche stelle con ben 20 pianeti!

       Come ultima annotazione, il raggio delle orbite ä influenzato
       anche dalla massa dei pianeti. Pianeti che hanno all'interno delle
       loro orbite giganti gassosi saranno un po' pió lontani della media
       perchÇ altrimenti le loro orbite potrebbero essere troppo
       destabilizzate dalla massa dei giganti. */

no_moons:
    key_radius = nearstar_ray * planet_orb_scaling;
    if (nearstar_class == 8) key_radius *= 2;
    if (nearstar_class == 2) key_radius *= 16;
    if (nearstar_class == 7) key_radius *= 18;
    if (nearstar_class == 11) key_radius *= 20;
    for (n=0; n<nearstar_nop; n++) {
        nearstar_p_ray[n] = avg_planet_ray[nearstar_p_type[n]]
                  + avg_planet_ray[nearstar_p_type[n]] * zrandom (100) / 200;
        nearstar_p_ray[n] *= avg_planet_sizing;
        nearstar_p_orb_ray[n] = key_radius + key_radius * zrandom (100) / 500;
        nearstar_p_orb_ray[n] += key_radius * avg_planet_ray[nearstar_p_type[n]];
        if (n < 8)
            key_radius += nearstar_p_orb_ray[n];
        else
            key_radius += 0.22 * nearstar_p_orb_ray[n];
    }

    /* Ri-Normalizzazione delle dimensioni delle lune,
       normalizzazione orbite lunari in base al principio di Keplero,
       a sua volta rielaborato come nelle precedenti annotazioni,
       solo che la limitazione avviene per orbite oltre la terza al 12%,
       ed ä molto pió effettiva oltre l'ottava orbita (al 2.5%). */

    n = nearstar_nop;
    while (n < nearstar_nob) {
        q = 0;
        c = nearstar_p_owner[n];
        key_radius = nearstar_p_ray[c] * moon_orb_scaling;
        while (n<nearstar_nob && nearstar_p_owner[n] == c) {
            nearstar_p_ray[n] = avg_planet_ray[nearstar_p_type[n]]
                      + avg_planet_ray[nearstar_p_type[n]] * zrandom (100) / 200;
            nearstar_p_ray[n] *= avg_moon_sizing;
            nearstar_p_orb_ray[n] = key_radius + key_radius * zrandom (100) / 250;
            nearstar_p_orb_ray[n] += key_radius * avg_planet_ray[nearstar_p_type[n]];
            if (q < 2) key_radius += nearstar_p_orb_ray[n];
            if (q >= 2 && q < 8) key_radius += 0.12 * nearstar_p_orb_ray[n];
            if (q >= 8) key_radius += 0.025 * nearstar_p_orb_ray[n];
            q++;
            n++;
        }
    }

    /* Eliminazione di anelli improbabili. */

    for (n = 0; n < nearstar_nop; n++) {
        // A meno di un raggio e mezzo dal centro del pianeta,
        // sarÖ un po' difficile trovarci un anello stabile.
        nearstar_p_ring[n] = 0.75 * nearstar_p_ray[n] * (2 + random(3));
        // I pianeti piccoli raramente hanno degli anelli.
        // Non hanno abbastanza massa per frantumare
        // una luna che arrivi troppo vicina.
        s = nearstar_p_type[n];
        if (s != 6 && s != 9) {
            if (random(5))
                nearstar_p_ring[n] = 0;
        }
        else {
            if (random(2))
                nearstar_p_ring[n] = 0;
        }
    }

    /* Conteggio degli oggetti che hanno un nome (suggerimento di Ryan) */

    nearstar_labeled = 0;
    for (n = 1; n <= nearstar_nob; n++) {
        if (search_id_code (nearstar_identity + n, 'P') != -1)
            nearstar_labeled++;
    }

    /* Reset dei periodi di rotazione
       (vengono calcolati con la superficie) */

    for (n = 0; n < nearstar_nob; n++)
        nearstar_p_rtperiod[n] = 0;
}

/* Smussa la superficie di un pianeta: media 4x4 rapida. */

void ssmooth (unsigned char far *target)
{
    asm {
        pusha
        push es
        mov cx, QUADWORDS
        shl cx, 2
        mov ax, 360
        shl ax, 2
        sub cx, ax
        les di, dword ptr target
        add di, 360
    }
smooth: asm {   db 0x66; mov dx, es:[di-360]
        db 0x66; add dx, es:[di]
        db 0x66; add dx, es:[di+360]
        db 0x66; add dx, es:[di+720]
        /* and edx, 11111100111111001111110011111100b */
        db 0x66, 0x81, 0xE2, 0xFC, 0xFC, 0xFC, 0xFC
        db 0x66; shr dx, 2
        mov al, dl
        add al, dh
        db 0x66; shr dx, 16
        add al, dl
        add al, dh
        shr al, 2
        mov es:[di], al
        inc di
        dec cx
        jnz smooth
        pop es
        popa }
}

/* Smussa leggermente la superficie di un pianeta: media 2x2. */

void lssmooth (unsigned char far *target)
{
    asm {   pusha
        push es
        mov cx, QUADWORDS
        sub cx, 80
        shl cx, 2
        les di, dword ptr target }
smooth: asm {   mov dx, es:[di]
        mov al, dl
        and dx, 0011111100111111b
        mov bx, es:[di+360]
        add dl, dh
        and bx, 0011111100111111b
        add dl, bl
        and al, 11000000b
        add dl, bh
        shr dl, 2
        or al, dl
        mov es:[di], al
        inc di
        dec cx
        jnz smooth
        pop es
        popa }
}

int      c, gr, r, g, b, cr, cx, cy;
float    a, kfract = 2;
char     lave, crays;
unsigned px, py;

/*

    Funzioni modulari per particolareggiare le superfici.
    Chiamate solo da surface. I parametri vengono passati nelle
    variabili all'uopo adibite: c, gr, r, g, b, cr, cx, cy, lave,
    crays, px, py, ed a.

    kfract ä la densitÖ delle fratture sui pianeti.
    viene posta a 1 per fare i fulmini nel cielo.

    Alcune ne chiamano altre, dello stesso gruppo, per risparmiare sui
    ritornelli di codice ripetuto. I pianeti particolarissimi non le
    usano, o comunque non usano solo queste.

    Lavorano tutte su p_background anche se, al momento della definizione
    della superficie di una luna, p_background verrÖ scambiato con
    s_background, che inizialmente ä la mappa della superficie stellare.
    Il fatto ä che da una luna ä probabile vedere il pianeta attorno al
    quale quella data luna sta girando, quindi bisogna mantenere separate
    la mappa planetaria e quella lunare. Non ci si preoccupa, invece, di
    avere pió di due corpi visibili, perchÇ:

        - il primo e il secondo pianeta di qualsiasi stella non
          possono, per convenzione, avere lune; d'altra parte, dal
          terzo pianeta in poi la superficie stellare non ä visibile
          nei dettagli, e puï essere approssimata da un "whiteglobe",
          un globo bianco in tinta unita.
        - le lune visibili da un'altra luna appaiono sempre piuttosto
          piccole, per cui non ä possibile scorgere i dettagli della
          superficie di una luna dal punto di vista di un'altra.

    Infine, le stesse considerazioni sulle mappe delle superfici,
    valgono per le mappe dei colori: la mappa dei colori della stella
    viene usata per conservare quella delle lune.

*/

void spot () // una piccola macchia chiara sulla superficie.
{
    asm {   les di, dword ptr p_background
        add di, py
        add di, px
        mov al, es:[di]
        add al, byte ptr gr
        cmp al, 0x3E
        jb min
        mov al, 0x3E }
   min: asm     mov es:[di], al
}

void permanent_storm () // tempesta permanente (una macchia colossale).
{
    for (g=1; g<cr; g++) {
        for (a=0; a<2*M_PI; a+=4*deg) {
            px = cx + g * cos (a);
            py = cy + g * sin (a);
            py *= 360;
            spot ();
        }
    }
}

void crater () // un cratere.
{
    for (a=0; a<2*M_PI; a+=4*deg) {
        for (gr=0; gr<cr; gr++) {
            px = cx + cos (a) * gr;
            py = cy + sin (a) * gr;
            vptr = px + 360*py;
            asm {   les di, dword ptr p_background
                add di, vptr
                mov al, es:[di]
                mov ah, byte ptr gr
                mov cl, lave
                shr ah, cl
                sub al, ah
                jnc entro
                xor al, al }
        entro:  asm     mov es:[di], al
        }
        asm {   les di, dword ptr p_background
            add di, vptr
            mov ax, 0x013E
            mov es:[di], ax }
        if (crays&&!random(crays)) {
            b = (2+random(2)) * cr;
            if (cy-b>0&&cy+b<179) {
                for (gr=cr+1; gr<b; gr++) {
                    px = cx + cos (a) * gr;
                    py = cy + sin (a) * gr;
                    vptr = px + 360*py;
                    asm {   les di, dword ptr p_background
                        add di, vptr
                        mov al, es:[di]
                        mov ah, byte ptr cr
                        add al, ah
                        cmp al, 0x3E
                        jb entro2
                        mov al, 0x3E }
                entro2: asm     mov es:[di], al
                }
            }
        }
    }
}

void band () /* banda scura orizzontale: puï essere portata al chiaro
        negando la superficie sulla base del fondo scala 0x3E */
{
    asm {   les di, dword ptr p_background
        add di, py
        mov cx, cr
        mov ah, byte ptr g }
nvrain: asm {   mov al, es:[di]
        sub al, ah
        jnc min
        xor al, al }
   min: asm {   mov es:[di], al
        inc di
        dec cx
        jnz nvrain }
}

void wave () // Una banda come sopra, perï ondulata.
{
    asm {   les di, dword ptr p_background
        mov px, 360
        mov bx, cy }
nvrain: asm {   fild px
        fmul a
        db 0xd9, 0xfe // fsin
        fild cr
        fmulp
        fistp py
        add py, bx
        mov ax, py
        mov dx, 360
        mul dx
        add ax, 4
        mov di, ax
        add di, px
        mov byte ptr es:[di], 0
        dec px
        jnz nvrain }
}

void fracture (unsigned char far *target, float max_latitude)
{ // solco scuro: tipo le linee su Europa.
  // ha dei parametri perchÇ viene usata anche per simulare i fulmini
  // quando piove sulla superficie dei pianeti abitabili.
    a = random (360) * deg;
    gr ++;

    float px = cx;
    float py = cy;

    do {
        a += (random (g) - random (g)) * deg;
        px += kfract * cos(a);
        if (px>359) px -= 360;
        if (px<0) px += 360;
        py += kfract * sin(a);
        if (py>max_latitude-1) py -= max_latitude;
        if (py<0) py += max_latitude;
        vptr = px + 360 * (unsigned)py;
        target[vptr] >>= (unsigned char) b;
    gr--; } while (gr);
}

void volcano () // un krakatoa volcano con Gedeone il gigante coglione.
{
    for (a=0; a<2*M_PI; a+=4*deg) {
        b = gr;
        for (g=cr/2; g<cr; g++) {
            px = cx + cos (a) * g;
            py = cy + sin (a) * g;
            py *= 360;
            spot ();
            gr--;
            if (gr<0) gr = 0;
        }
        gr = b;
    }
}

void contrast (float kt, float kq, float thrshld)
{
    unsigned c;

    for (c=0; c<64800; c++) {
        a = p_background[c];
        a -= thrshld;
        if (a>0)
            a *= kt;
        else
            a *= kq;
        a += thrshld;
        if (a<0) a = 0;
        if (a>63) a = 63;
        p_background[c] = a;
    }
}

void randoface (int range, int upon)
{
    unsigned c;

    for (c=0; c<64800; c++) {
        gr = p_background[c];
        if ((upon>0&&gr>=upon)||(upon<0&&gr<=-upon)) {
            gr += random (range);
            gr -= random (range);
            if (gr>63) gr = 63;
            if (gr<0) gr = 0;
            p_background[c] = gr;
        }
    }
}

void negate ()
{
    asm {   les di, p_background
        mov cx, 64800 }
negat:  asm {   mov al, 0x3E
        sub al, es:[di]
        mov es:[di], al
        inc di
        dec cx
        jnz negat }
}

void crater_juice ()
{
    lave = random (3);
    crays = random (3) * 2;
    for (c=0; c<r; c++) {
        cx = random (360);
        cr = 2 + random (1+r-c);
        while (cr>20) cr -= 10;
        cy = random (178 - 2*cr) + cr;
        crater ();
        if (cr>15) lssmooth (p_background);
    }
}

/* Funzioni di mappatura dell'atmosfera.
   Lavorano come le precedenti, ma lavorano su "objectschart"
   piuttosto che su "p_background", e a risoluzione dimezzata.
   Inoltre, MOLTO IMPORTANTE, il campo d'esistenza dell'albedo
   delle nubi non va da 0 a 0x3E ovvero da 0 a 62, MA da 0 a 0x1F,
   ovvero da 0 a 31. Questo perchÇ, al momento della discesa sulla
   superficie, l'albedo media di p_background viene usata per
   determinare, sui pianeti abitabili, qualora lo scenario ä
   oceanico o no (se si scende in mare, si deve sempre trovare
   il mare). Dato che l'albedo di p_background ä alterata da
   quella delle nubi contenuta in objectschart, essa viene
   ripristinata al momento della scelta del luogo di sbarco,
   dalla funzione "planets", SOTTRAENDO l'albedo delle nubi
   a quella della superficie di sbarco di p_background.
   Se perï, si lascia l'alterazione dovuta alle nubi, alterare
   l'albedo del territorio sottostante di oltre la metÖ del campo
   d'esistenza 0..62, si rischia di sottrarre un valore troppo alto
   e di ricondurre l'albedo che viene calcolata sotto al limite che
   determina quando lo scenario ä oceanico (i mari hanno l'albedo pió
   bassa in assoluto). Il risultato sarebbe che una zona normalmente
   coperta di terra, al passaggio di una grossa nube diventerebbe mare. */

void cirrus () // una piccola macchia chiara (nube brillante).
{
    asm {   les di, dword ptr objectschart
        mov bx, py
        add bx, px
        shr bx, 1
        mov al, es:[bx+di]
        add al, byte ptr gr
        cmp al, 0x1F
        jb min
        mov al, 0x1F }
   min: asm     mov es:[bx+di], al
}

void atm_cyclon () // ciclone atmosferico: un'ammasso di nubi a spirale.
{
    b = 0;
    while (cr>0) {
        px = cx + cr * cos (a);
        py = cy + cr * sin (a);
        py *= 360; cirrus ();
        px += random(4); cirrus ();
        py += 359; cirrus ();
        px -= random(4); cirrus ();
        py += 361; cirrus ();
        px += random(4); cirrus ();
        b++; b %= g;
        if (!b) cr--;
        a += 6 * deg;
    }
}

void storm () // tempesta (una grande macchia chiara sull'atmosfera).
{
    for (g=1; g<cr; g++) {
        for (a=0; a<2*M_PI; a+=4*deg) {
            px = cx + g * cos (a);
            py = cy + g * sin (a);
            py *= 360;
            cirrus ();
        }
    }
}

/* Calcola la superficie estrapolandola dai dati sul pianeta e dalla
   tabella pseudo-casuale assegnatagli.
   Include il terminatore giorno-notte scurendo l'emisfero notturno
   per un angolo di 130¯, non di 180¯ per via della luce diffusa e del
   campo ridotto ai bordi dei globi.
   "colorbase" viene assegnato a 192 per i pianeti, a 128 per le lune. */

void surface (int logical_id, int type,
          double seedval, unsigned char colorbase)
{
    int         plwp;
    unsigned        seed;
    char            knot1 = 0, brt;
    int             QW = QUADWORDS;
    float           r1, r2, r3, g1, g2, g3, b1, b2, b3;
    unsigned char far   *overlay = (unsigned char far *)objectschart;

    if (type == 10) return; // stella compagna: ha superficie stellare...

    /* impostazione del periodo di rotazione
       "rotation" marca un punto ideale che rappresenta
       l'attuale rotazione del pianeta, in gradi, fra 0 e 359.
       il periodo di rotazione ä estratto in un range molto ampio,
       con risoluzione di 1 secondo. */

    fast_srand (seedval + 4112);

    /* "rtperiod" ä il tempo, in secondi, che il pianeta impiega a
       ruotare di un grado sul proprio asse. Il tempo impiegato per
       una rotazione completa ä quindi, in secondi, 360 * rtperiod. */

    nearstar_p_rtperiod[logical_id] = 10 * (ranged_fast_random(50) + 1)
                    + 10 * ranged_fast_random(25)
                    + ranged_fast_random (250)
                    + 41;

    nearstar_p_rotation[logical_id] = secs / nearstar_p_rtperiod[logical_id];
    nearstar_p_rotation[logical_id] %= 360;

    /* calcolo dell'orientamento del pianeta per il successivo
       oscuramento del lato buio (rispetto alla posizione della stella) */

    plwp = 89 - cplx_planet_viewpoint (logical_id);
    plwp += nearstar_p_rotation[logical_id];
    plwp %= 360; if (plwp<0) plwp += 360;

    /* selezione della tabella pseudo relativa a questo pianeta
       la tabella pseudo della funzione "random" propria al C++ ha
       una discreta probabilitÖ di ricorrenza, ma essendo integrata
       con la "ranged_fast_random", la ricorrenza viene annullata
       ("ranged_fast_random" ha un'enormitÖ in pió di tabelle). */

    fast_srand (seedval * 10);
    seed = fast_random (0xFFFF);

    /* preparazione di una superficie standard (random pattern 0..62):
       viene elaborata in seguito a seconda del tipo di pianeta. */

    srand (seed);
    asm {   les di, dword ptr p_background
        mov cx, 64800
        mov ax, seed }
rndpat: asm {   add ax, cx
        xor dx, dx
        imul ax
        add ax, dx
        mov bl, al
        and bl, 0x3E
        mov es:[di], bl
        inc di
        dec cx
        jnz rndpat }

    /* 
        preparazione dell'overlay per la mappatura delle evoluzioni
       dell'atmosfera: viene inizialmente azzerato, in quanto deve
       essere successivamente rielaborato a seconda del tipo di
       pianeta. ovviamente non viene rielaborato se il pianeta
       non ha un atmosfera. 
    */

    _fmemset (overlay, 0, 32400);

    /* 
        elaborazione della superficie specifica.
       l'elaborazione dell'overlay per l'atmosfera,
       nel caso ce ne sia bisogno, ä contemporanea. 
    */

    srand (seed);
    QUADWORDS = 16200;

    switch (type) {
        case 0: r = ranged_fast_random (3) + 5;
            for (c=0; c<r; c++) ssmooth (p_background);
            asm {   les di, dword ptr p_background
                mov cx, 64800 }
           sep: asm {   cmp byte ptr es:[di], 28
                jb low
                mov byte ptr es:[di], 62 }
           low: asm {   inc di
                dec cx
                jnz sep }
            r = ranged_fast_random (5) + 5;
            for (c=0; c<r; c++) ssmooth (p_background);
            r = 5 + ranged_fast_random (26);
            for (c=0; c<r; c++) {
                cr = 5 + ranged_fast_random (20);
                cx = ranged_fast_random (360);
                cy = ranged_fast_random (130) + 25;
                gr = ranged_fast_random (cr/2) + cr/2 + 2;
                volcano ();
            }
            r = 100 + ranged_fast_random (100);
            b = ranged_fast_random (3) + 1;
            g = 360;
            for (c=0; c<r; c++) {
                cx = ranged_fast_random (360);
                cy = ranged_fast_random (180);
                gr = ranged_fast_random (100);
                fracture (p_background, 180);
            }
            lssmooth (p_background);
            break;
        case 1: if (ranged_fast_random(2)) ssmooth (p_background);
            r = 10 + ranged_fast_random (41);
            crater_juice ();
            lssmooth (p_background);
            if (!ranged_fast_random(5)) negate ();
            break;
        case 2: r = 5 + ranged_fast_random (25);
            for (c=0; c<r; c++) {
                cr = ranged_fast_random (20) + 1;
                cy = ranged_fast_random (178 - 2*cr) + cr;
                switch (random(2)) {
                    case 0: cx = ((long)(10 * secs) / (ranged_fast_random (3600) + 180)) % 360;
                        gr = ranged_fast_random (12) + 2;
                        storm ();
                        break;
                    case 1: gr = ranged_fast_random (15) + 3;
                        py = cy * 360; cr *= 360;
                        g = 1 + ranged_fast_random (gr);
                        band ();
                }
            }
            if (!ranged_fast_random(3)) negate ();
            break;
        case 3: r = ranged_fast_random(3) + 4;
            g = 26 + ranged_fast_random(3) - ranged_fast_random(5);
            for (c=0; c<r; c++) ssmooth (p_background);
            asm {   les di, dword ptr p_background
                mov cx, 64000
                mov ax, seed }
           sda: asm {   mov dl, byte ptr g
                cmp es:[di], dl
                jnb terra
                mov byte ptr es:[di], 16
                jmp mare }
         terra: asm {   add ax, cx
                imul ax
                add ax, dx
                mov bl, al
                and bl, 0x3E
                add es:[di], bl
                cmp byte ptr es:[di], 0x3E
                jb mare
                mov word ptr es:[di], 0x3E }
          mare: asm {   inc di
                dec cx
                jnz sda }
            r = 20 + ranged_fast_random (40);
            for (c=0; c<r; c++) {
                gr = ranged_fast_random (5) + 1;
                cr = ranged_fast_random (10) + 10;
                if (ranged_fast_random(3))
                    cy = ranged_fast_random (172 - 2*cr) + cr + 2;
                else
                    cy = 60 + ranged_fast_random (10) - ranged_fast_random (10);
                cx = ((long)(secs) / (ranged_fast_random (360) + 180)) % 360;
                g  = ranged_fast_random (5) + 7;
                a  = ranged_fast_random (360) * deg;
                atm_cyclon ();
            }
            break;
        case 4: ssmooth (p_background);
            if (ranged_fast_random(2)) ssmooth (p_background);
            asm {   les di, dword ptr p_background
                mov cx, 64000 }
         lmrip: asm {   cmp byte ptr es:[di], 32
                jne proxy
                mov word ptr es:[di], 0x3E01
                mov byte ptr es:[di+360], 0x01 }
         proxy: asm {   inc di
                dec cx
                jnz lmrip }
            r = ranged_fast_random (30);
            if (r>20) r *= 10;
            b = ranged_fast_random (3) + 1;
            g = 200 + ranged_fast_random (300);
            for (c=0; c<r; c++) {
                cx = ranged_fast_random (360);
                cy = ranged_fast_random (180);
                gr = 50 + ranged_fast_random (100);
                fracture (p_background, 180);
            }
            r = ranged_fast_random (25) + 1; crater_juice ();
            lssmooth (p_background);
            if (ranged_fast_random(2)) lssmooth (p_background);
            break;
        case 5: r = ranged_fast_random (3) + 4;
            for (c=0; c<r; c++) ssmooth (p_background);
            contrast ((float)ranged_fast_random(200) / 900 + 0.6,
                  (float)ranged_fast_random(350) / 100 + 4.0,
                  25 + ranged_fast_random(3));
            randoface (5 + ranged_fast_random(3), -20 * (ranged_fast_random(3) + 1));
            r = 5 + ranged_fast_random (5);
            for (c=0; c<r; c++) {
                cr = 5 + ranged_fast_random (10);
                cx = ranged_fast_random (360);
                cy = ranged_fast_random (145) + 15;
                gr = ranged_fast_random (cr/2) + 2;
                volcano ();
            }
            r = 5 + ranged_fast_random (5);
            for (c=0; c<r; c++) {
                cr = ranged_fast_random (30) + 1;
                cy = ranged_fast_random (178 - 2*cr) + cr;
                cx = ((long)(60*secs) / (ranged_fast_random (3600) + 360)) % 360;
                gr = ranged_fast_random (2) + 1;
                permanent_storm ();
            }
            for (c=0; c<10000; c++) {
                gr = ranged_fast_random (10) + 10;
                px = ranged_fast_random (360);
                py = ranged_fast_random (10);
                py *= 360; spot ();
                px = ranged_fast_random (360);
                py = 125 - ranged_fast_random (10);
                py *= 360; spot ();
            }
            if (ranged_fast_random(2))
                ssmooth (p_background);
            else
                lssmooth (p_background);
            break;
        case 6: r = 3 + ranged_fast_random (5);
            for (c=0; c<r; c++) ssmooth (p_background);
            r = 50 + ranged_fast_random (100);
            for (c=0; c<r; c++) {
                cr = ranged_fast_random (10) + 1;
                cy = ranged_fast_random (178 - 2*cr) + cr;
                if (ranged_fast_random(8)) {
                    gr = ranged_fast_random (5) + 2;
                    g = 1 + ranged_fast_random (gr);
                    py = cy * 360;
                    cr *= 360;
                    band ();
                }
                else {
                    a = (float) (5 + ranged_fast_random(10)) / 30;
                    cr = cr / 4 + 1;
                    wave ();
                }
            }
            r = 50 + ranged_fast_random (100);
            for (c=0; c<r; c++) {
                cr = ranged_fast_random (15) + 1;
                cy = ranged_fast_random (178 - 2*cr) + cr;
                cx = ((long)(60*secs) / (ranged_fast_random (8000) + 360)) % 360;
                gr = ranged_fast_random (2) + 1;
                if (ranged_fast_random(10))
                    cr = cr / 2 + 1;
                else
                    gr *= 3;
                storm ();
            }
            lssmooth (p_background);
            if (!ranged_fast_random(3)) negate ();
            break;
        case 7: r = 5 + ranged_fast_random (5);
            for (c=0; c<r; c++) ssmooth (p_background);
            r = 10 + ranged_fast_random (50);
            g = 5 + ranged_fast_random (20);
            b = ranged_fast_random (2) + 1;
            for (c=0; c<r; c++) {
                cx = ranged_fast_random (360);
                cy = ranged_fast_random (180);
                gr = ranged_fast_random (300);
                fracture (p_background, 180);
            }
            if (ranged_fast_random(2)) lssmooth (p_background);
            randoface (1 + ranged_fast_random(10), 1);
            if (ranged_fast_random(2)) negate ();
            break;
        case 8: r = ranged_fast_random (10) + 1;
            for (c=0; c<r; c++) lssmooth (p_background);
            r = 100 + ranged_fast_random (50);
            for (c=0; c<r; c++) {
                cr = ranged_fast_random (5) + 1;
                gr = ranged_fast_random (5) + 1;
                cx = ranged_fast_random (360);
                cy = ranged_fast_random (178 - 2*cr) + cr;
                permanent_storm ();
            }
            if (ranged_fast_random(2)) negate ();
            break;
        case 9: pclear (p_background, 0x1F);
            for (px = 0; px < 32400; px++) overlay[px] = 0x1F;
    }

    /* rinormalizzazione superficie a intervallo 00-1F:
       solo se l'atmosfera del pianeta non deve influire
       sull'aspetto della superficie sottostante, quindi
       per pianeti felisiani e per quelli simili a marte. */

    if (type==3||type==5) {
        for (px = 0; px < 64800; px++)
            p_background[px] >>= 1;
    }

    /* ritocchi specifici finali alla superficie - pianeti felisiani */

    if (type==3) {
        if (ranged_fast_random(2))
            lssmooth (p_background);
        else
            ssmooth (p_background);
    }

    /* fusione mappa terreno + overlay atmosfera,
       e rinormalizzazione della mappa del terreno
       in modo che si adatti al range da 0 a 1Fh. */

    for (px = 0, py = 0; px < 32400; py += 2, px++) {
        p_background[py] += overlay[px];
        if (p_background[py] > 0x3E) p_background[py] = 0x3E;
        p_background[py+1] += overlay[px];
        if (p_background[py+1] > 0x3E) p_background[py+1] = 0x3E;
    }

    /* ritocchi specifici finali alla superficie - pianeti venusiani */

    if (type==2) {
        if (!random(3)) {
            psmooth_grays(p_background);
            knot1 = 1;
        }
    }

    /* applicazione terminatore giorno-notte */

    nearstar_p_term_start[logical_id] = plwp + 35;
    if (nearstar_p_term_start[logical_id] >= 360) nearstar_p_term_start[logical_id] -= 360;
    nearstar_p_term_end[logical_id] = nearstar_p_term_start[logical_id] + 130;
    if (nearstar_p_term_end[logical_id] >= 360) nearstar_p_term_end[logical_id] -= 360;

        asm {   les di, dword ptr p_background
            add di, plwp
            add di, 35
            mov cx, 179 }
      darkside: asm {   push cx
            mov cx, 130 }
      darkline: asm {   shr byte ptr es:[di], 2
            inc di
            dec cx
            jnz darkline
            pop cx
            add di, 230
            dec cx
            jnz darkside }

    /* ritocchi specifici finali alla superficie - altri pianeti */

    if (type==2) {
        if (knot1)
            ssmooth (p_background);
        else {
            r = 3 + ranged_fast_random (5);
            for (c=0; c<r; c++)
                ssmooth (p_background);
        }
    }

    if (type==6) {
        for (c=0; c<3; c++)
            if (ranged_fast_random(2))
                ssmooth (p_background);
    }

    if (type==9) for (c=0; c<6; c++) ssmooth (p_background);

    /* Elaborazione tabella dei colori (ridefinisce da 192 a 255). */

    if (colorbase == 255) {
        QUADWORDS = QW;
        return;
    }

    type <<= 2;

    r = planet_rgb_and_var[type+0];
    g = planet_rgb_and_var[type+1];
    b = planet_rgb_and_var[type+2];
    c = planet_rgb_and_var[type+3];

    r <<= 1; r += nearstar_r; r >>= 1;
    g <<= 1; g += nearstar_g; g >>= 1;
    b <<= 1; b += nearstar_b; b >>= 1;

    r1 = r + random(c) - random(c);
    g1 = g + random(c) - random(c);
    b1 = b + random(c) - random(c);
    r2 = r + random(c) - random(c);
    g2 = g + random(c) - random(c);
    b2 = b + random(c) - random(c);
    r3 = r + random(c) - random(c);
    g3 = g + random(c) - random(c);
    b3 = b + random(c) - random(c);

    r1 *= 0.25; g1 *= 0.25; b1 *= 0.25;
    r2 *= 0.75; g2 *= 0.75; b2 *= 0.75;
    r3 *= 1.25; g3 *= 1.25; b3 *= 1.25;

    type >>= 2;

    shade (tmppal, colorbase + 00, 16, 00, 00, 00, r1, g1, b1);
    shade (tmppal, colorbase + 16, 16, r1, g1, b1, r2, g2, b2);
    shade (tmppal, colorbase + 32, 16, r2, g2, b2, r3, g3, b3);
    shade (tmppal, colorbase + 48, 16, r3, g3, b3, 64, 64, 64);

    brt = nearstar_p_owner[logical_id];
    if (brt == -1) brt = logical_id;

    if (brt <= 4)
        brt = 64;
    else
        brt = 64 - (4 * (brt - 4));

    tavola_colori (tmppal + 3*colorbase, colorbase, 64, brt, brt, brt);

    QUADWORDS = QW;
}

/* Tracciamento degli anelli (eventuali). */

void ring (int planet_id, double ox, double oy, double oz, int start, int layers)
{
    int     a, b, c, n, m, partn, partcls;
    double  sx, sy, sz;

    double  ringray = nearstar_p_ring[planet_id];
    double  ringtilt = 0.1 * ringray * nearstar_p_tilt[planet_id];
    double  step = 0.0075 * ringray;

    fast_srand (10000 * ringray + planet_id);
    b = 1 + fast_random (0x1F) - layers;
    partcls = 1 + fast_random (3);
    while (b > 0) {
        if (!fast_random(7)) {
            c = 1 + fast_random (3);
            pixel_spreads = 0;
        }
        else {
            c = 1 + fast_random (7);
            pixel_spreads = 1;
        }
        a = start - (start % c);
        pixilating_effect = fast_random(1) + fast_random(1);
        if (a < 0) a += 360;
        n = c; while (n + c < 180) {
            m = c + fast_random (1);
            n += m; a += m; if (a > 360) a -= 360;
            sy = oy - ringtilt * lft_sin[a];
            sx = ox + ringray  * lft_sin[a];
            sz = oz + ringray  * lft_cos[a];
            partn = partcls;
            while (partn) {
                sz += step - (fast_flandom() * step);
                sx += step - (fast_flandom() * step);
                far_pixel_at (sx, sy, sz, -0.042, 0);
                partn--;
            }
        }
        ringray += step;
        if (!fast_random(7)) ringray += 5 * step;
        ringtilt = 0.1 * ringray * nearstar_p_tilt[planet_id];
        b--;
    }

    pixilating_effect = LIGHT_EMITTING;
    pixel_spreads = 1;
}

/* Visualizza appopriatamente i pianeti, come punti, barlumi di luce
   o globi ben visibili, a seconda di distanza e raggio. C'ä un terzo
   modo in cui un corpo planetario puï rendersi visibile: con una falce.
   L'effetto falce viene realizzato da "glowinglobe". */

void planets ()
{
    char far *atmosphere = (char far *) objectschart;
    unsigned char far *surface_backup = (unsigned char far*)p_background;

    char is_moon;
    long poffs;
    long test;

    int  i1, i2, n1, n2, c1, c2, pnpcs;
    int  c, n, t, ts, te, ll, plwp, riwp;

    int  te_ll_distance, te_ll_distance_1, te_ll_distance_2;
    int  ts_ll_distance, ts_ll_distance_1, ts_ll_distance_2;

    double xx, yy, zz;
    double d3, d2, md2 = 1E9;

    unsigned char colorbase, showdisc, showrings, surfacemap;
    int ringlayers;

    if (ip_targetting) ip_targetted = -1;
    if (!nearstar_nop) return;

    for (n=0; n<nearstar_nob; n++) {
        planet_xyz (n);
        xx = plx - dzat_x;
        yy = ply - dzat_y;
        zz = plz - dzat_z;
        nearstar_p_qsortindex[n] = n;
        nearstar_p_qsortdist[n]  = sqrt (xx*xx+yy*yy+zz*zz);
    }

    QuickSort (nearstar_p_qsortindex,
           nearstar_p_qsortdist,
           0, nearstar_nob - 1);

    if (nearstar_nob == 1) {
        pnpcs = npcs;
        npcs  = 0;
        if (npcs != pnpcs) {
            resident_map1 = 0;
            resident_map2 = -1;
        }
    }
    else {
        pnpcs = npcs;
        n1 = nearstar_nob - 1;
        i1 = nearstar_p_qsortindex[n1];
        c1 = nearstar_p_owner[i1];
        n2 = nearstar_nob - 2;
        i2 = nearstar_p_qsortindex[n2];
        c2 = nearstar_p_owner[i2];
        if (c1 > -1) {
            while (c2 > -1) {
                n2 --;
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

    for (c=0; c<nearstar_nob; c++) {
        n  = nearstar_p_qsortindex[c];
        //
        d3 = nearstar_p_qsortdist[n];
        planet_xyz (n);
        if (nearstar_p_owner[n] > -1) {
            p_background = s_background;
            colorbase = 128;
            is_moon = 1;
        }
        else {
            p_background = surface_backup;
            colorbase = 192;
            is_moon = 0;
        }
        showdisc = 0;
        showrings = 0;
        surfacemap = 0;
        if (d3 < 250*nearstar_p_ray[n]) {
            showrings = 1;
            ringlayers = 0.05 * (d3 / nearstar_p_ray[n]);
            if (d3 < 100*nearstar_p_ray[n]) {
                showdisc = 1;
                if (d3 < 25*nearstar_p_ray[n])
                    surfacemap = 1;
            }
        }
        //
        if (ip_targetting || !showdisc) {
            far_pixel_at (plx, ply, plz, nearstar_p_ray[n], 0);
            if (ip_targetting) {
                pxx -= x_centro;
                pyy -= y_centro;
                d2 = pxx*pxx + pyy*pyy;
                if (d2<md2) {
                    md2 = d2;
                    ip_targetted = n;
                }
            }
        }
        //
        if (nearstar_p_type[n] == 10) goto notaplanet;
        //
        if (showrings) {
            if (surfacemap)
                multicolourmask = 0xC0;
            else
                multicolourmask = 0x40;
            plwp = 359 - planet_viewpoint (dzat_x, dzat_z);
            if (nearstar_p_ring[n]) {
                riwp = plwp + 180;
                if (riwp > 359) riwp -= 360;
                ring (n, plx, ply, plz, riwp, ringlayers);
            }
        }
        if (showdisc) {
            if (surfacemap) {
            if (n==resident_map1 || n==resident_map2) {
                if (is_moon) {
                    if (nearstar_p_type[n]) {
                        surface (n, nearstar_p_type[n],
                             1000000        *
                             nearstar_ray       *
                             nearstar_p_type[n]     *
                             nearstar_p_orb_orient[n],
                             128);
                    }
                    else {
                        surface (n, nearstar_p_type[n],
                             2000000 * n        *
                             nearstar_ray       *
                             nearstar_p_orb_orient[n],
                             128);
                    }
                }
                else {
                    if (nearstar_p_type[n]) {
                        surface (n, nearstar_p_type[n],
                             1000000        *
                             nearstar_p_type[n]     *
                             nearstar_p_orb_seed[n] *
                             nearstar_p_orb_tilt[n] *
                             nearstar_p_orb_ecc[n]  *
                             nearstar_p_orb_orient[n],
                             192);
                    }
                    else {
                        surface (n, nearstar_p_type[n],
                             2000000 * n        *
                             nearstar_p_orb_seed[n] *
                             nearstar_p_orb_tilt[n] *
                             nearstar_p_orb_ecc[n]  *
                             nearstar_p_orb_orient[n],
                             192);
                    }
                }
                if (n==resident_map1) resident_map1 = -1;
                if (n==resident_map2) resident_map2 = -1;
            }
            if (n == ip_targetted && landing_point) {
                nightzone = 0;
                //
                ts = nearstar_p_term_start[n];
                te = nearstar_p_term_end[n];
                ll = landing_pt_lon;
                //
                if (ts > te) {
                    if (ll >= ts
                        || ll < te)
                            nightzone = 1;
                }
                else {
                    if (ll >= ts
                        && ll < te)
                            nightzone = 1;
                }
                //
                te_ll_distance_1 = 0;
                ll = landing_pt_lon;
                while (ll != te) {
                    te_ll_distance_1++;
                    ll++; if (ll >= 360) ll = 0;
                }
                te_ll_distance_2 = 0;
                ll = landing_pt_lon;
                while (ll != te) {
                    te_ll_distance_2++;
                    ll--; if (ll <= -1) ll = 359;
                }
                if (te_ll_distance_1 < te_ll_distance_2)
                    te_ll_distance = te_ll_distance_1;
                else
                    te_ll_distance = te_ll_distance_2;
                ts_ll_distance_1 = 0;
                ll = landing_pt_lon;
                while (ll != ts) {
                    ts_ll_distance_1++;
                    ll++; if (ll >= 360) ll = 0;
                }
                ts_ll_distance_2 = 0;
                ll = landing_pt_lon;
                while (ll != ts) {
                    ts_ll_distance_2++;
                    ll--; if (ll <= -1) ll = 359;
                }
                if (ts_ll_distance_1 < ts_ll_distance_2)
                    ts_ll_distance = ts_ll_distance_1;
                else
                    ts_ll_distance = ts_ll_distance_2;
                if (ts_ll_distance <= te_ll_distance) {
                    sun_x_factor = +1;
                    crepzone = ts_ll_distance;
                }
                else {
                    sun_x_factor = -1;
                    crepzone = te_ll_distance;
                }
                //
                fast_srand (nearstar_p_orb_seed[n] * nearstar_p_orb_ecc[n] * 12345);
                ptr = 360 * landing_pt_lat + landing_pt_lon;
                sky_red_filter = fast_random (31) + 32;
                sky_grn_filter = fast_random (15) + 48;
                sky_blu_filter = fast_random (15) + 48;
                if (is_moon) {
                    gnd_red_filter = tmppal[(3 * p_background[ptr]) + 128*3 + 0];
                    gnd_grn_filter = tmppal[(3 * p_background[ptr]) + 128*3 + 1];
                    gnd_blu_filter = tmppal[(3 * p_background[ptr]) + 128*3 + 2];
                }
                else {
                    gnd_red_filter = tmppal[(3 * p_background[ptr]) + 192*3 + 0];
                    gnd_grn_filter = tmppal[(3 * p_background[ptr]) + 192*3 + 1];
                    gnd_blu_filter = tmppal[(3 * p_background[ptr]) + 192*3 + 2];
                }
                gnd_red_filter += fast_random (15);
                gnd_grn_filter += fast_random (15);
                gnd_blu_filter += fast_random (15);
                test = nearstar_p_type[n];
                if (nightzone) {
                    albedo = p_background[ptr];
                    albedo <<= 2;
                    if (test==3||test==5)
                        albedo -= atmosphere[ptr>>1];
                    albedo >>= 2;
                    albedo <<= 2;
                }
                else {
                    albedo = p_background[ptr];
                    if (test==3||test==5)
                        albedo -= atmosphere[ptr>>1];
                    albedo >>= 2;
                    albedo <<= 2;
                }
                if (test==3||test==5) albedo *= 2; // da 0 a 1F --> da 0 a 3F
                rainy = (float)atmosphere[ptr>>1] * 0.25;
                if (rainy > 5) rainy = 5;
                if (nightzone) {
                    sky_grn_filter /= 2;
                    sky_blu_filter /= 2;
                    if (crepzone > 5) {
                        sky_red_filter /= 2;
                        sky_brightness = 8;
                        horiz_brt = 10;
                    }
                    else {
                        sky_brightness = 32;
                        horiz_brt = 16;
                    }
                }
                else {
                    if (crepzone > 5) {
                        sky_brightness = 48;
                        horiz_brt = 20;
                    }
                    else {
                        sky_grn_filter /= 2;
                        sky_blu_filter /= 3;
                        sky_brightness = 40;
                        horiz_brt = 13;
                    }
                }
                for (poffs = -180; poffs < 180; poffs++) {
                    test = poffs + ptr;
                    if (test > 0 && test < 64800) {
                        _AL = p_background[test];
                        asm xor al, 0x1E;
                        p_background[test] = _AL;
                    }
                }
                for (poffs = -60; poffs < 60; poffs++) {
                    if (poffs) {
                        test = 360 * poffs + ptr;
                        if (test > 0 && test < 64800) {
                            _AL = p_background[test];
                            asm xor al, 0x1E;
                            p_background[test] = _AL;
                        }
                    }
                }
            }
            t = nearstar_p_type[n];
            if (t == 2 || t == 3 || t == 6 || t == 8 || t == 9)
                glass_bubble = 1;
            else
                glass_bubble = 0;
            globe (plwp + nearstar_p_rotation[n],
                   adapted, p_background, n_globes_map, gl_bytes,
                   plx, ply, plz, nearstar_p_ray[n], colorbase, 0);
            if (n == ip_targetted && landing_point) {
                for (poffs = -180; poffs < 180; poffs++) {
                    test = poffs + ptr;
                    if (test > 0 && test < 64800) {
                        _AL = p_background[test];
                        asm xor al, 0x1E;
                        p_background[test] = _AL;
                    }
                }
                for (poffs = -60; poffs < 60; poffs++) {
                    if (poffs) {
                        test = 360 * poffs + ptr;
                        if (test > 0 && test < 64800) {
                            _AL = p_background[test];
                            asm xor al, 0x1E;
                            p_background[test] = _AL;
                        }
                    }
                }
            }
            }
            else {
                ts = (89+35) - cplx_planet_viewpoint (n);
                if (ts < 0) ts += 360;
                if (ts > 359) ts -= 360;
                glowinglobe (plwp, adapted, n_globes_map, gl_bytes, plx,
                     ply, plz, nearstar_p_ray[n], ts, 130, 127);
            }
        }
        if (showrings) {
            if (nearstar_p_ring[n]) {
                ring (n, plx, ply, plz, plwp, ringlayers);
                if (!showdisc) far_pixel_at (plx, ply, plz, nearstar_p_ray[n], 0);
            }
        }
        notaplanet:
    }

    p_background = surface_backup;
}

// Necessaria all'inizializzazione (ottimizzazione caricamento segmenti).

void init_FP_segments ()
{
    asm {   les ax, dword ptr adapted
        mov seg_adapted, es }
}

/*

    Gestione cartografia galattica.

    Ad ogni stella ä assegnato un codice d'identificazione univoco,
    derivante dalle sue coordinate. A tale codice si fa riferimento
    per l'associazione dei nomi delle stelle. I codici identificativi
    dei pianeti vengono calcolati a partire da quello della loro stella,
    pió il numero (progressivo) del pianeta in ordine di distanza.

*/

double  laststar_x, laststar_y, laststar_z;

/* Determina se una certa stella, di cui si specifica il codice
   d'identificazione univoco, ä attualmente nel range dei sensori.
   Ritorna 1 quando ä visibile, 0 se non lo ä.
   Quando ä visibile, le coordinate della stella sono riportate
   nelle variabili "laststar_x", "laststar_y" e "laststar_z". */

char isthere (double star_id)
{
    char        visible_sectors = 9;

    long        sect_x, sect_y, sect_z;
    long        k, advance = 100000;

    double      sidlow = star_id - idscale;
    double      sidhigh = star_id + idscale;

    unsigned char   sx, sy, sz;
    double      laststar_id;

    sect_x = (dzat_x - visible_sectors*50000) / 100000; sect_x *= 100000;
    sect_y = (dzat_y - visible_sectors*50000) / 100000; sect_y *= 100000;
    sect_z = (dzat_z - visible_sectors*50000) / 100000; sect_z *= 100000;

    if (field_amplificator) visible_sectors = 14;
    k = 100000 * visible_sectors;

    asm {   les ax, dword ptr adapted
        mov al, visible_sectors
        mov sx, al }
e_while:asm {   mov al, visible_sectors
        mov sy, al }
m_while:asm {   mov al, visible_sectors
        mov sz, al }
i_while:asm {   db 0x66, 0xBB, 0x50, 0xC3, 0x00, 0x00 // mov ebx, 50000
        db 0x66; mov ax, word ptr sect_x
        db 0x66; mov dx, word ptr sect_z
        db 0x66; add ax, dx
        db 0x66; mov cx, ax
        db 0x66; mov dx, ax
        db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
        db 0x66; add dx, word ptr sect_x
        db 0x66; sub dx, bx
        db 0x66; mov word ptr laststar_x, dx
        db 0x66; imul dx
        db 0x66; add dx, ax
        db 0x66; add cx, dx
        db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
        db 0x66; add dx, word ptr sect_y
        db 0x66; sub dx, bx
        db 0x66; mov word ptr laststar_y, dx
        db 0x66; mov ax, cx
        db 0x66; imul dx
        db 0x66; add dx, ax
        db 0x66, 0x81, 0xE2, 0xFF, 0xFF, 0x01, 0x00 // and edx, 0x0001FFFF
        db 0x66; add dx, word ptr sect_z
        db 0x66; sub dx, bx
        db 0x66; mov word ptr laststar_z, dx
        fild dword ptr laststar_x
        fst  laststar_x
        fmul idscale
        fild dword ptr laststar_y
        fst  laststar_y
        fmul idscale
        fild dword ptr laststar_z
        fst  laststar_z
        fmul idscale
        fmulp
        fmulp
        fst laststar_id
        fcomp sidlow
        fstsw ax
        sahf
        jb i_next
        fld laststar_id
        fcomp sidhigh
        fstsw ax
        sahf
        jb y_end }
i_next: asm {   db 0x66; mov ax, word ptr advance
        db 0x66; add word ptr sect_z, ax
        dec sz
        jz i_end
        jmp i_while }
i_end:    asm { db 0x66; mov dx, word ptr k
        db 0x66; sub word ptr sect_z, dx
        db 0x66; add word ptr sect_y, ax
        dec sy
        jz m_end
        jmp m_while }
m_end:    asm { db 0x66; sub word ptr sect_y, dx
        db 0x66; add word ptr sect_x, ax
        dec sx
        jz e_end
        jmp e_while }
e_end:    return (0);
y_end:    return (1);
}

/* Ricerca tutte le stelle note visibili, fino a 50 contemporaneamente.
   Compila una tabella contenente l'ID di ogni stella e la sua
   posizione in coordinate Parsis. */

const int   tgt_bytes_per_scan = 5 * 32;
long        tgt_collect_lastpos = 0;

int         targets = 0;
int         topmost_target = 0;
int         target_line = 0;
char        update_targets = 0;
char        collecting_targets = 0;

double      targets_table_id[50];
double      targets_table_px[50];
double      targets_table_py[50];
double      targets_table_pz[50];

void collect_targets ()
{
    int     local_smh;
    unsigned    n, ptr, index, toread;

    char far    *buffer_ascii = (char far *)p_surfacemap;
    double far  *buffer_double = (double far *)p_surfacemap;

    local_smh = _rtl_open (starmap_file, 0);
    if (local_smh > -1) {
        toread = tgt_bytes_per_scan;
        while (toread) {
            lseek (local_smh, tgt_collect_lastpos, SEEK_SET);
            n = _rtl_read (local_smh, buffer_ascii, toread);
            if (!n) {
                collecting_targets = 0;
                goto stop;
            }
            ptr = 0;
            index = 0;
            toread = 0;
            while (ptr < n) {
                if (buffer_ascii[ptr + 29] == 'S') {
                    if (isthere (buffer_double[index])) {
                        targets_table_id[targets] = buffer_double[index];
                        targets_table_px[targets] = laststar_x;
                        targets_table_py[targets] = laststar_y;
                        targets_table_pz[targets] = laststar_z;
                        if (targets < 3)
                            target_line = targets;
                        else
                            target_line = 2;
                        if (targets > 2)
                            topmost_target = targets - 2;
                        update_targets = 1;
                        targets++;
                        if (targets == 50) {
                            collecting_targets = 0;
                            goto stop;
                        }
                    }
                }
                else
                    toread += 32;
                ptr += 32;
                index += 4;
                tgt_collect_lastpos += 32;
            }
        }
      stop: _rtl_close (local_smh);
    }
}

/* Cambia lo stato visualizzato dall'FCS sull'Head-Up-Display. */

void status (char *status_description, int message_delay)
{
    if (message_delay >= fcs_status_delay) {
        strcpy (fcs_status, status_description);
        fcs_status_delay = message_delay;
    }
}

/* Mappa caratteri per l'HUD:
   font iper-compatto (3 x 5 pixels). */

char digimap[65*5] = {
     0, 0, 0, 0, 0, // 32. spazio vuoto
     2, 2, 2, 0, 2, // 33. punto esclamativo
     5, 0, 0, 0, 0, // 34. virgolette
     0, 0, 3, 5, 5, // 35. cancelletto (rappresentato da una piccola n.)
     2, 2, 6, 2, 2, // 36. sistro
     1, 4, 2, 1, 4, // 37. percento
     0, 0, 2, 0, 0, // 38. e commericale (non ä possibile visualizzarla)
     0, 2, 2, 0, 0, // 39. apice
     4, 2, 2, 2, 4, // 40. parentesi tonda aperta
     1, 2, 2, 2, 1, // 41. parentesi tonda chiusa
     0, 0, 7, 2, 2, // 42. asterisco
     0, 2, 7, 2, 0, // 43. segno pió
     0, 0, 0, 2, 1, // 44. virgola
     0, 0, 7, 0, 0, // 45. segno meno
     0, 0, 0, 0, 2, // 46. punto
     0, 4, 2, 1, 0, // 47. barra destrorsa
     7, 5, 5, 5, 7, // 48. 0
     3, 2, 2, 2, 7, // 49. 1
     7, 4, 7, 1, 7, // 50. 2
     7, 4, 6, 4, 7, // 51. 3
     4, 6, 5, 7, 4, // 52. 4
     7, 1, 7, 4, 7, // 53. 5
     7, 1, 7, 5, 7, // 54. 6
     7, 4, 4, 4, 4, // 55. 7
     7, 5, 7, 5, 7, // 56. 8
     7, 5, 7, 4, 4, // 57. 9
     0, 2, 0, 2, 0, // 58. duepunti
     0, 2, 0, 2, 1, // 59. punto e virgola
     4, 2, 1, 2, 4, // 60. minore
     0, 7, 0, 7, 0, // 61. uguale
     1, 2, 4, 2, 1, // 62. maggiore
     7, 4, 6, 0, 2, // 63. punto interrogativo
     0, 2, 0, 0, 0, // 64. a commerciale (non visualizzabile)
     7, 5, 7, 5, 5, // 65. A
     7, 5, 3, 5, 7, // 66. B
     7, 1, 1, 1, 7, // 67. C
     3, 5, 5, 5, 3, // 68. D
     7, 1, 3, 1, 7, // 69. E
     7, 1, 3, 1, 1, // 70. F
     7, 1, 5, 5, 7, // 71. G
     5, 5, 7, 5, 5, // 72. H
     2, 2, 2, 2, 2, // 73. I
     4, 4, 4, 5, 7, // 74. J
     5, 5, 3, 5, 5, // 75. K
     1, 1, 1, 1, 7, // 76. L
     7, 7, 5, 5, 5, // 77. M
     5, 7, 7, 5, 5, // 78. N
     7, 5, 5, 5, 7, // 79. O
     7, 5, 7, 1, 1, // 80. P
     7, 5, 5, 1, 5, // 81. Q
     7, 5, 3, 5, 5, // 82. R
     7, 1, 7, 4, 7, // 83. S
     7, 2, 2, 2, 2, // 84. T
     5, 5, 5, 5, 7, // 85. U
     5, 5, 5, 5, 2, // 86. V
     5, 5, 7, 7, 5, // 87. W
     5, 5, 2, 5, 5, // 88. X
     5, 5, 7, 2, 2, // 89. Y
     7, 4, 2, 1, 7, // 90. Z
     0, 0, 6, 2, 2, // 91. parentesi quadra aperta
     1, 3, 7, 3, 1, // 92. barra sinistrorsa
     2, 2, 6, 0, 0, // 93. parentesi quadra chiusa
     2, 2, 2, 2, 2, // 94. ordinale femminile
     0, 0, 0, 0, 7, // 95. sottolinea
     1, 2, 0, 0, 0  // 96. accento
};

/* Mappa caratteri per il computer ed il sistema operativo:
   font a pió alta risoluzione (32 x 36 pixels).
   Viene caricato in n_globes_map + gl_bytes ed occupa 10800 bytes.
   Questi 10182 bytes (gl_brest) sono praticamente una minuscola estensione
   dell'area n_globes_map che di per sÇ, contenendo una semi-texture
   di 32Kb per la superficie dei mari, ä stata estesa da 22586 a 32768. */

unsigned long far *digimap2; // verrÖ assegnato a n_globes_map + gl_bytes

/* Cupola panoramica. */

const float cupsize = 1800;
const float cupheight = 1667;

void cupola (float y_or, float brk)
{
    float xx, yy, zz;
    float lat, lon, dlat, dlon, dlon_2, k, clon, slon, ck, sk;

    dlat = M_PI / 20;
    dlon = M_PI / 10;

    dlon_2 = dlon / 2;

    for (lon = 0; lon < 2*M_PI - dlon_2; lon += dlon) {
        k = lon + dlon;
        ck = cos (k); sk = sin (k);
        clon = cos (lon); slon = sin (lon);
        for (lat = dlat; lat < brk * dlat; lat += dlat) {
            xx = cupsize * sin(lat+dlat);
            yy = - cupheight * cos(lat) * y_or;
            zz = cupsize * sin(lat);
            stick3d (zz*clon, yy, zz*slon,
                 xx*clon, -cupheight*cos(lat+dlat)*y_or, xx*slon);
            stick3d (zz*clon, yy, zz*slon,
                 zz*ck, yy, zz*sk);
        }
        if (gburst > 1) {
            lat = (M_PI / 20) * 8 * ((float)gburst / 63);
            lens_flares_for (cam_x, cam_y, cam_z,
                     +cupsize * clon * sin(lat),
                     -cupheight *      cos(lat),
                     +cupsize * slon * sin(lat),
                     -50000, 10, 1, 0, 1, 1);
            flares = 0;
        }
    }
}

void polycupola (float y_or, char textured)
{
    float d1, d2, d3, dd;
    float x[4], y[4], z[4];
    float lat, lon, dlat, dlon, dlon_2, k, clon, slon, ck, sk;

    dlat = M_PI / 20;
    dlon = M_PI / 10;

    dlon_2 = dlon / 2;

    if (textured)
        setfx (4);
    else
        setfx (2);

    for (lon = 0; lon < 2*M_PI - dlon_2; lon += dlon) {
        k = lon + dlon;
        ck = cos (k); sk = sin (k);
        clon = cos (lon); slon = sin (lon);
        for (lat = dlat; lat < 8 * dlat; lat += dlat) {
            xx = cupsize * sin(lat+dlat);
            yy = - cupheight * cos(lat) * y_or;
            zz = cupsize * sin(lat);
            x[0] = zz * clon;
            y[0] = yy;
            z[0] = zz * slon;
            x[1] = zz * ck;
            y[1] = yy;
            z[1] = zz * sk;
            x[2] = xx * ck;
            y[2] = - cupheight * cos(lat+dlat) * y_or;
            z[2] = xx * sk;
            x[3] = xx * clon;
            y[3] = - cupheight * cos(lat+dlat) * y_or;
            z[3] = xx * slon;
            if (ontheroof && y_or == 1) {
                d1 = 0.5 * (x[0] + x[1]) - cam_x;
                d2 = 0.5 * (z[0] + z[1]) - cam_z;
                dd = 1000 - sqrt (d1*d1 + d2*d2);
                if (dd > 600) dd = 600;
                if (dd < 0) dd = 0;
                cam_y += dd;
                poly3d (x, y, z, 4, 64);
                cam_y -= dd;
            }
            else {
                if (textured) {
                    d1 = 0.5 * (x[0] + x[1]) - cam_x;
                    d2 = 0.5 * (y[0] + y[2]) - cam_y;
                    d3 = 0.5 * (z[0] + z[1]) - cam_z;
                    dd = 500 - sqrt (d1*d1 + d2*d2 + d3*d3);
                    if (dd > 500) dd = 500;
                    if (dd < 0) dd = 0;
                    cam_y += 4 * dd * y_or;
                    xx = x[3]; yy = y[3]; zz = z[3];
                    x[3] = x[2]; y[3] = y[2]; z[3] = z[2];
                    x[2] = x[1]; y[2] = y[1]; z[2] = z[1];
                    x[1] = x[0]; y[1] = y[0]; z[1] = z[0];
                    x[0] = xx; y[0] = yy; z[0] = zz;
                    polymap (x, y, z, 4, 0);
                    cam_y -= 4 * dd * y_or;
                }
                else
                    poly3d (x, y, z, 4, 64);
            }
        }
    }

    resetfx ();
}

/* Sincronizzatore: su qualsiasi PC un massimo di 18 fotogrammi al secondo. */

clock_t gtime;

void sync_start () { 
    gtime = clock(); 
}

void sync_stop () { 
    while (clock() == gtime); 
}

long   global_surface_seed;
float  ppos_x, ppos_y, ppos_z;
double dsd;         // per misurare distanze

/* Carica la bitmap per la superficie stellare. */

void load_starface ()
{
    unsigned seed = nearstar_identity * 12345;
    asm {   les di, dword ptr s_background
        mov cx, 64800
        mov ax, seed }
rndpat: asm {   add ax, cx
        xor dx, dx
        imul ax
        add ax, dx
        mov bl, al
        and bl, 0x3E
        mov es:[di], bl
        inc di
        dec cx
        jnz rndpat }

    int smoothcount;

    fast_srand (seed);
    smoothcount = fast_random(3);

    if (nearstar_class == 11 || nearstar_class == 7 || nearstar_class == 2)
        smoothcount += fast_random(3) + 2;

    while (smoothcount) {
        ssmooth (s_background);
        smoothcount--;
    }
}

void load_QVRmaps ()
{
    int fh;

    fh = sa_open (offsets_map);
    if (fh>-1) {
        _rtl_read (fh, n_offsets_map, om_bytes);
        _rtl_close (fh);
    }

    fh = sa_open (globes_map);
    if (fh>-1) {
        _rtl_read (fh, n_globes_map, gl_bytes);
        _rtl_close (fh);
    }
}

void load_digimap2 ()
{
    int fh;

    fh = sa_open (off_digimap2);
    if (fh>-1) {
        _rtl_read (fh, digimap2, dm2_bytes);
        _rtl_close (fh);
    }
}

char    outhudbuffer[81];
char    *compass = "N.........E.........S.........W.........N.........E.........S.......";

float   tp_gravity = 1, pp_gravity = 1;
float   tp_temp = 22, pp_temp = 22;
float   tp_pressure = 1, pp_pressure = 1;
float   tp_pulse = 118, pp_pulse = 118;

void wrouthud (unsigned x, unsigned y, unsigned l, char *text)
{
    int j, i, n;
    unsigned spot;

    n = 0; if (!l) l = 32767;
    spot = y * 320 + x;

    while (text[n] && n < l) {
        j = (text[n] - 32) * 5;
        for (i = 0; i < 5; i++) {
            if (digimap[j + i] & 1) adapted[spot+0] = 191 - adapted[spot+0];
            if (digimap[j + i] & 2) adapted[spot+1] = 191 - adapted[spot+1];
            if (digimap[j + i] & 4) adapted[spot+2] = 191 - adapted[spot+2];
            spot += 320;
        }
        spot -= 320 * 5;
        spot += 4;
        n++;
    }
}

void surrounding (char compass_on, int openhudcount)
{
    int cpos, crem;
    long    lsecs, lptr;
    float   pp_delta, ccom;

    for (lptr=0; lptr<04; lptr++) areaclear (adapted, 10, openhudcount + 9 - lptr, 0, 0, 300, 1, 54 + surlight + 3*lptr);
    for (lptr=0; lptr<10; lptr++) areaclear (adapted, 0, 9 - lptr, 0, 0, 320, 1, 64 + surlight - lptr);
    for (lptr=0; lptr<10; lptr++) areaclear (adapted, 0, 190 + lptr, 0, 0, 320, 1, 64 + surlight - lptr);
    for (lptr=0; lptr<10; lptr++) areaclear (adapted, 9 - lptr, 10, 0, 0, 1, 180, 64 + surlight - lptr);
    for (lptr=0; lptr<10; lptr++) areaclear (adapted, 310 + lptr, 10, 0, 0, 1, 180, 64 + surlight - lptr);

    lptr = 64 + 3 * surlight;
    if (lptr > 127) lptr = 127;

    areaclear (adapted, 9, 9, 0, 0, 4, 4, lptr);
    smootharound_64 (adapted, 9, 9, 5, 1);

    areaclear (adapted, 308, 9, 0, 0, 4, 4, lptr);
    smootharound_64 (adapted, 308, 9, 5, 1);

    areaclear (adapted, 9, 188, 0, 0, 4, 4, lptr);
    smootharound_64 (adapted, 9, 188, 5, 1);

    areaclear (adapted, 308, 188, 0, 0, 4, 4, lptr);
    smootharound_64 (adapted, 308, 188, 5, 1);

    sprintf (outhudbuffer, "EPOC %d & ", epoc);
    lsecs = secs; lsecs -= lsecs % 1000000L; lsecs /= 1000000L;
    strcat (outhudbuffer, alphavalue(lsecs)); strcat (outhudbuffer, ".");
    lsecs = secs; lsecs %= 1000000L; lsecs -= lsecs % 1000; lsecs /= 1000;
    strcat (outhudbuffer, alphavalue(lsecs)); strcat (outhudbuffer, ".");
    lsecs = secs; lsecs %= 1000;
    strcat (outhudbuffer, alphavalue(lsecs));
    if (compass_on) {
        strcat (outhudbuffer, " & SQC ");
        strcat (outhudbuffer, alphavalue(landing_pt_lon));
        strcat (outhudbuffer, ".");
        strcat (outhudbuffer, alphavalue(landing_pt_lat));
        strcat (outhudbuffer, ":");
        strcat (outhudbuffer, alphavalue((((long)(pos_x)) >> 14) - 100));
        strcat (outhudbuffer, ".");
        strcat (outhudbuffer, alphavalue((((long)(pos_z)) >> 14) - 100));
        areaclear (adapted, 254, 1, 0, 0, 5, 7, 64 + 0);
        areaclear (adapted, 256, 8, 0, 0, 1, 1, 64 + 63);
        ccom = 360 - user_beta;
        if (ccom > 359) ccom -= 360;
        cpos = ccom / 9; crem = ccom * 0.44444;
        wrouthud (200 - (crem % 4), 2, 28, compass + cpos);
    }
    else {
        if (!ontheroof) {
            strcat (outhudbuffer, " & ");
            if (sys==4)
                strcat (outhudbuffer, "5\\FLIGHTCTR R\\DEVICES    D\\PREFS      X\\SCREEN OFF");
            else {
                cpos = strlen (outhudbuffer);
                outhudbuffer[cpos + 00] = '6';
                outhudbuffer[cpos + 01] = '\\';
                memcpy (outhudbuffer + cpos + 02, ctb + 20 + 27 * 0, 10);
                outhudbuffer[cpos + 12] = ' ';
                outhudbuffer[cpos + 13] = '7';
                outhudbuffer[cpos + 14] = '\\';
                memcpy (outhudbuffer + cpos + 15, ctb + 20 + 27 * 1, 10);
                outhudbuffer[cpos + 25] = ' ';
                outhudbuffer[cpos + 26] = '8';
                outhudbuffer[cpos + 27] = '\\';
                memcpy (outhudbuffer + cpos + 28, ctb + 20 + 27 * 2, 10);
                outhudbuffer[cpos + 38] = ' ';
                outhudbuffer[cpos + 39] = '9';
                outhudbuffer[cpos + 40] = '\\';
                memcpy (outhudbuffer + cpos + 41, ctb + 20 + 27 * 3, 10);
                outhudbuffer[cpos + 51] = 0;
                strupr (outhudbuffer);
            }
        }
    }
    wrouthud (2, 2, NULL, outhudbuffer);

    pp_delta = (pp_gravity - tp_gravity) * 0.25; tp_gravity += pp_delta;
    pp_delta = (pp_temp - tp_temp) * 0.05; tp_temp += pp_delta;
    pp_delta = (pp_pressure - tp_pressure) * 0.02; tp_pressure += pp_delta;
    pp_delta = (pp_pulse - tp_pulse) * 0.01; tp_pulse += pp_delta;
    //unitÖ di debugging dell'albedo:
    //sprintf (outhudbuffer, "GRAVITY %2.3f FG & TEMPERATURE %+3.1f@C & PRESSURE %2.3f ATM & PULSE %3.0f PPS", tp_gravity, tp_temp, tp_pressure, (float)albedo);
    sprintf (outhudbuffer, "GRAVITY %2.3f FG & TEMPERATURE %+3.1f@C & PRESSURE %2.3f ATM & PULSE %3.0f PPS", tp_gravity, tp_temp, tp_pressure, tp_pulse);
    wrouthud (2, 192, NULL, outhudbuffer);
}

/* Salva una fotografia dello schermo sul file "SNAPXXXX.BMP":
   XXXX ä un numero progressivo di disambiguazione. */

extern long star_label_pos;
extern char star_label[25];
extern long planet_label_pos;
extern char planet_label[25];

char snapfilename[24];
void snapshot (int forcenumber, char showdata)
{
    int prog;
    unsigned pqw;
    double parsis_x, parsis_y, parsis_z;

    unsigned ptr, c;
    char a, b, t[54];

    int ih = sa_open (header_bmp);
    if (ih==-1) return;
    _rtl_read (ih, t, 54);
    _rtl_close (ih);

    pqw = QUADWORDS;
    QUADWORDS = 16000;
    pclear (adaptor, 0);
    QUADWORDS = pqw;

    if (!forcenumber) {
        prog = -1;
        do {
            prog++; if (prog == 9999) return;
            sprintf (snapfilename, "..\\GALLERY\\SNAP%04d.BMP", prog);
            ih = _rtl_open (snapfilename, 0);
            if (ih != -1) _rtl_close (ih);
        } while (ih != -1);
    }
    else
        sprintf (snapfilename, "..\\GALLERY\\SNAP%04d.BMP", forcenumber);

    if (showdata) {
    areaclear (adapted, 2, 191, 0, 0, 316, 7, 64 + 63);

    asm {   fld dzat_x
        frndint
        fstp parsis_x
        fld dzat_y
        frndint
        fstp parsis_y
        fld dzat_z
        frndint
        fstp parsis_z }

    strcpy (outhudbuffer, "LOCATION PARSIS: ");
    strcat (outhudbuffer, alphavalue(parsis_x));
    strcat (outhudbuffer, ";");
    strcat (outhudbuffer, alphavalue(-parsis_y));
    strcat (outhudbuffer, ";");
    strcat (outhudbuffer, alphavalue(parsis_z));
    if (ip_targetted > -1) {
        if (nearstar_p_owner[ip_targetted] > -1) {
            strcat (outhudbuffer, " & TGT: MOON N@");
            strcat (outhudbuffer, alphavalue(nearstar_p_moonid[ip_targetted]+1));
            strcat (outhudbuffer, " OF PLANET N@");
            strcat (outhudbuffer, alphavalue(nearstar_p_owner[ip_targetted]+1));
        }
        else {
            strcat (outhudbuffer, " & TGT: PLANET N@");
            strcat (outhudbuffer, alphavalue(ip_targetted+1));
        }
    }
    wrouthud (3, 192, NULL, outhudbuffer);

    if (ap_targetted == 1 && star_label_pos != -1) {
        areaclear (adapted, 14, 14, 0, 0, 102, 7, 64 + 63);
        wrouthud (15, 15, 20, star_label);
    }

    if (ip_targetted != -1 && planet_label_pos != -1) {
        areaclear (adapted, 14, 23, 0, 0, 102, 7, 64 + 63);
        wrouthud (15, 24, 20, planet_label);
    }
    }

    ih = _rtl_creat (snapfilename, 0);
    if (ih>-1) {
        a = 0;
        _rtl_write (ih, t, 54);
        for (c=0; c<768; c+=3) {
            b = tmppal[c+2]*4; _rtl_write (ih, &b, 1);
            b = tmppal[c+1]*4; _rtl_write (ih, &b, 1);
            b = tmppal[c+0]*4; _rtl_write (ih, &b, 1);
            _rtl_write (ih, &a, 1);
        }
        for (ptr=63680; ptr<64000; ptr-=320) _rtl_write (ih, adapted+ptr, 320);
        _rtl_close (ih);
    }
}

/*
    Consumi supplementari di litio, dal pió dispendioso al pió economico:
    - orbita vimana:            1 KD ogni 7 secondi.
    - inseguimento a punto lontano:     1 KD ogni 18 secondi.
    - inseguimento a punto fisso:       1 KD ogni 29 secondi.
    - inseguimento a punto vicino:      1 KD ogni 33 secondi.
    - amplificatore di campo stellare:  1 KD ogni 41 secondi.
    - orbita geosincrona:           1 KD ogni 58 secondi.
    - lampada interna:          1 KD ogni 84 secondi.
    - cercapianeti:             1 KD ogni 155 secondi.
*/

long iqsecs = 0;
void additional_consumes()
{
    if (iqsecs < (long)secs)
        iqsecs = secs;
    //
    if (ip_targetted > -1 && pwr > 15000) {
        if (ip_reached && sync) {
            if (sync==1) // fixed-point chase
                if (!(iqsecs % 29)) { pwr--; iqsecs++; }
            if (sync==2) // far chase
                if (!(iqsecs % 18)) { pwr--; iqsecs++; }
            if (sync==3) // syncrone orbit
                if (!(iqsecs % 58)) { pwr--; iqsecs++; }
            if (sync==4) // vimana orbit
                if (!(iqsecs %  7)) { pwr--; iqsecs++; }
            if (sync==5) // near chase
                if (!(iqsecs % 33)) { pwr--; iqsecs++; }
        }
    }
    //
    if (pl_search       && !(iqsecs % 155)) { pwr--; iqsecs++; }
    if (ilightv == 1    && !(iqsecs %  84)) { pwr--; iqsecs++; }
    if (field_amplificator  && !(iqsecs %  41)) { pwr--; iqsecs++; }
    //
    if (pwr <= 15000) {
        if (charge) {
            charge--;
            pwr = 20000;
            status ("FCS: READY", 100);
        }
        else {
            stspeed     = 0;
            ip_reaching     = 0;
            ip_reached  = 1;
            ip_targetted    = -1;
            if (pwr != 15000) {
                status ("POWER LOSS", 100);
                pwr = 15000;
            }
        }
    }
}
