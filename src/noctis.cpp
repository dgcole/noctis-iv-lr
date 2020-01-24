/*
    The main module of Noctis.
    Supervision functions for the base module.
*/

#include "scripting.h"
#include "brtl.h"
#include "noctis-0.h"
#include "noctis-d.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

const double deg = M_PI / 180;

extern int8_t exitflag;
extern int8_t entryflag;
extern void planetary_main();
extern float tiredness;

// Stuff imported from noctis-0.cpp to lighten it.

int8_t nsnp           = 1; // Nearstar-Not-Prepared
int8_t manual_target  = 0;
int8_t mt_string_char = 0;
int8_t mt_coord       = 0;
int8_t manual_x_string[11];
int8_t manual_y_string[11];
int8_t manual_z_string[11];

// Set the autopilot travel parameters.
void fix_remote_target() {
    double dxx, dyy, dzz;
    status("TGT FIXED", 105);
    dxx                          = dzat_x - ap_target_x;
    dyy                          = dzat_y - ap_target_y;
    dzz                          = dzat_z - ap_target_z;
    ap_target_initial_d          = sqrt(dxx * dxx + dyy * dyy + dzz * dzz);
    requested_vimana_coefficient = 1000 * ap_target_initial_d;
    current_vimana_coefficient   = 1000 * ap_target_initial_d;
    vimana_reaction_time         = 0.01;
    ap_reached                   = 0;
    dxx = sqrt(ap_target_x * ap_target_x + ap_target_z * ap_target_z);
    dxx += fabs(ap_target_y * 30);

    if (dxx > 2E9) {
        status("OUTOFRANGE", 105);
        ap_targetted = 0;
    } else {
        ap_targetted = 1;
    }
}

void fix_local_target() {
    double dxx, dyy, dzz;
    status("TGT FIXED", 105);
    planet_xyz(ip_targetted);
    dxx                            = dzat_x - plx;
    dyy                            = dzat_y - ply;
    dzz                            = dzat_z - plz;
    ip_target_initial_d            = sqrt(dxx * dxx + dyy * dyy + dzz * dzz);
    requested_approach_coefficient = 1000 * ip_target_initial_d;
    current_approach_coefficient   = 1000 * ip_target_initial_d;
    reaction_time                  = 0.01;
}

/* Lampada alogena (ovvero il laser a diffusione interno alle zattere).
 * Halogen lamp (i.e. the diffusion laser inside the rafts). */

void alogena() {
    float x[3], y[3], z[3];
    float lon, dlon, dlon_2;
    int16_t pcol;
    dlon = M_PI / 5;

    if (fabs(cam_z) > 1500) {
        dlon *= fabs(cam_z) / 1500;
    }

    dlon_2 = dlon / 2;
    pcol   = 72 + ilightv;

    if (pcol > 100) {
        pcol = 100;
    }

    x[2] = -10;
    y[2] = 10;
    z[2] = -10;

    for (lon = 0; lon < 2 * M_PI - dlon_2;) {
        x[0] = 15 * sin(lon);
        y[0] = 15 * cos(lon);
        z[0] = (y[0] - x[0]) / 2;
        lon += dlon;
        x[1] = 15 * sin(lon);
        y[1] = 15 * cos(lon);
        z[1] = (y[1] - x[1]) / 2;
        poly3d(x, y, z, 3, pcol);
        pcol += 2;
    }

    if (ilightv == 1 && !elight) {
        lens_flares_for(cam_x, cam_y, cam_z, -10, 10, -10, -50000, 2, 1, 0, 1,
                        1);
    }
}

/* Selection panels for the on-board computer */

void qsel(float *x, float *y, float *z, uint16_t n) {
    setfx(1);
    x[0] -= 10;
    y[0] -= 10;
    x[1] += 10;
    y[1] -= 10;
    x[2] += 10;
    y[2] += 10;
    x[3] -= 10;
    y[3] += 10;
    poly3d(x, y, z, n, 1);
    chgfx(0);
    x[0] += 10;
    y[0] += 10;
    x[1] -= 10;
    y[1] += 10;
    x[2] -= 10;
    y[2] -= 10;
    x[3] += 10;
    y[3] -= 10;
    poly3d(x, y, z, n, 68);
    resetfx();
}

// All reflections on reflective surfaces.

void reflexes() {
    float x[4], y[4], z[4];
    setfx(1);
    lbxf++;
    /*  if (depolarize) goto norefs;

        if (ilight) {
            x[0] = 3200; y[0] = -425; z[0] = -100;
            x[1] = 1000; y[1] = -415; z[1] = -100;
            x[2] = 3200; y[2] = -400; z[2] = -100;
            poly3d (x, y, z, 3, 1);
            x[0] = 3200; y[0] = -400; z[0] = -100;
            x[1] = 3175; y[1] = -425; z[1] = -100;
            x[2] = 3200; y[2] = +300; z[2] = -100;
            poly3d (x, y, z, 3, 5);
        }

        if (pos_z<-1750||beta<-45||beta>45) {
            x[0] = -1200; y[0] = -525; z[0] = -1800;
            x[1] = +1350; y[1] = -525; z[1] = -1800;
            x[2] = +1300; y[2] = -575; z[2] = -1850;
            poly3d (x, y, z, 3, 1);
            x[0] = +1350; y[0] = -525; z[0] = -1800;
            x[1] = +1350; y[1] = -525; z[1] = -4000;
            poly3d (x, y, z, 3, 1);
            x[0] = -1200; y[0] = +450; z[0] = -1800;
            x[1] = +1350; y[1] = +450; z[1] = -1800;
            x[2] = +1300; y[2] = +500; z[2] = -1850;
            poly3d (x, y, z, 3, 1);
            x[0] = +1350; y[0] = +450; z[0] = -1800;
            x[1] = +1350; y[1] = +450; z[1] = -4000;
            poly3d (x, y, z, 3, 1);
        } */
    if (ap_targetting || ip_targetting) {
        goto noevid;
    }

    if (ilight) {
        setfx(1);
    } else {
        setfx(0);
    }

    z[0] = 0;
    z[1] = 0;
    z[2] = 0;
    z[3] = 0;

    if (s_control) {
        x[0] = -66 * 30 - 10;
        y[0] = (float) (50 * (s_control - 3) - 30);
        x[1] = -46 * 30;
        y[1] = (float) (50 * (s_control - 3) - 30);
        x[2] = -46 * 30;
        y[2] = (float) (50 * (s_control - 2) - 25);
        x[3] = -66 * 30 - 10;
        y[3] = (float) (50 * (s_control - 2) - 25);
        qsel(x, y, z, 4);
    }

    if (sys != 4) {
        x[0] = -45.65 * 30;
        y[0] = -125;
        x[1] = -45.45 * 30;
        y[1] = -125;
        x[2] = -45.45 * 30;
        y[2] = 75;
        x[3] = -45.65 * 30;
        y[3] = 75;

        if (stspeed) {
            poly3d(x, y, z, 4, 32);
        } else {
            if (ilight) {
                poly3d(x, y, z, 4, 8);
            } else {
                poly3d(x, y, z, 4, 80);
            }
        }

        if (s_command) {
            x[0] = (float) (27 * 30 * s_command - 72 * 30 + 10);
            y[0] = -130;
            x[1] = x[0] + 26 * 30 + 10;
            y[1] = -130;
            x[2] = x[1];
            y[2] = -75;
            x[3] = x[0];
            y[3] = -75;
            qsel(x, y, z, 4);
        }
    }

noevid:
    lbxf--;
    setfx(0);
}

/* Schemi aggiuntivi per lo schermo del computer.
 * Additional schemes(layouts? borders?) for the computer screen. */

void frame(float x, float y, float l, float h, float borderwidth,
           uint8_t color) {
    // disegna una cornice rettangolare.
    // draw a rectangular frame.
    float vx[4], vy[4], vz[4] = {0, 0, 0, 0};
    float x0 = cam_x;
    float y0 = cam_y;
    setfx(4);
    vx[0] = -l - borderwidth;
    vy[0] = -borderwidth;
    vx[1] = +l + borderwidth;
    vy[1] = vy[0];
    vx[2] = +l + borderwidth;
    vy[2] = +borderwidth;
    vx[3] = -l - borderwidth;
    vy[3] = vy[2];
    cam_x = x0 - x;
    cam_y = y0 - y - h;
    poly3d(vx, vy, vz, 4, color);
    cam_y = y0 - y + h;
    poly3d(vx, vy, vz, 4, color);
    vx[0] = -borderwidth;
    vy[0] = -h - borderwidth;
    vx[1] = +borderwidth;
    vy[1] = vy[0];
    vx[2] = +borderwidth;
    vy[2] = +h + borderwidth;
    vx[3] = -borderwidth;
    vy[3] = vy[2];
    cam_y = y0 - y;
    cam_x = x0 - x - l;
    poly3d(vx, vy, vz, 4, color);
    cam_x = x0 - x + l;
    poly3d(vx, vy, vz, 4, color);
    cam_x = x0;
    cam_y = y0;
    resetfx();
}

// Draw star targeting cross.
void pointer_cross_for(double xlight, double ylight, double zlight) {
    double xx, yy, zz, z2, rx, ry, rz;
    xx = xlight - dzat_x;
    yy = ylight - dzat_y;
    zz = zlight - dzat_z;
    rx = xx * opt_pcosbeta + zz * opt_psinbeta;
    z2 = zz * opt_tcosbeta - xx * opt_tsinbeta;
    rz = z2 * opt_tcosalfa + yy * opt_tsinalfa;
    ry = yy * opt_pcosalfa - z2 * opt_psinalfa;

    if (rz > 1) {
        rx /= rz;
        rx += VIEW_X_CENTER;
        ry /= rz;
        ry += VIEW_Y_CENTER - 2;

        if (rx > 10 && ry > 10 && rx < 310 && ry < 190) {
            uint16_t offset = (320 * ((uint16_t) ry)) + ((uint16_t) rx);

            for (int16_t i = 0; i < 4; i++) {
                int16_t mod1 = (i == 1 || i == 3) ? 1 : -1;
                int16_t mod2 = (i == 1 || i == 2) ? 1 : -1;

                for (int16_t j = 7; j > 3; j--) {
                    adapted[offset + mod1 * 320 * j + mod2 * j] = 126;
                }
            }
        }
    }
}

// Write a line on the onboard computer screen.
void cline(int16_t line, const char *text) {
    // Multiply the line index by 128 b/c there are 128 characters per line.
    line *= 128;
    // The non-control section starts 20 characters into the line.
    uint16_t start = line + 20;
    strcpy(&ctb[start], text);
    // The current index, used for the other() function.
    point = start + strlen(text);
}

// Write text following what was just written with cline().
void other(const char *text) {
    strcpy(&ctb[point], text);
    // Increment the current character index by the length of what was just
    // added.
    point += strlen(text);
}

// Write the title of a system check (there are 4 in all).
void control(int16_t line, const char *text) {
    // Multiply the line index by 128 b/c there are 128 characters per line.
    uint16_t start = line * 128;
    strcpy(&ctb[start], text);
}

// Writes the title of a command on the main display.
// These are split up into 4 blocks of 27 characters.
void command(int16_t nr, const char *text) {
    uint16_t length = strlen(text);

    if (length > 27) {
        return;
    }

    int16_t index = 20 + 27 * nr;
    strcpy(&ctb[index], text);
}

// Clear the whole on-board computer screen.
void clear_onboard_screen() { memset(ctb, 0, 512); }

/* On-board operating system management group. */

uint8_t reset_signal         = 55;     // Reset signal (=55)
int8_t force_update          = 0;      // Force screen to refresh
int8_t active_screen         = -1;      // Screen currently active
int16_t osscreen_cursor_x[2] = {0, 0}; // Cursor position (x)
int16_t osscreen_cursor_y[2] = {0, 0}; // Cursor position (y)
char osscreen[2][7 * 21 + 1];       // Array of GOES screens

void mslocate(int16_t screen_id, int16_t cursor_x, int16_t cursor_y) {
    // Rilocazione cursore (multischermo).
    // Cursor relocation (multi-screen).
    osscreen_cursor_x[screen_id] = cursor_x;
    osscreen_cursor_y[screen_id] = cursor_y;
}

void mswrite(int16_t screen_id, const char *text) {
    // Scrittura caratteri (multischermo).
    // Character writing (multi-screen).
    int16_t i, j = 0;
    int8_t symbol;

    while ((symbol = text[j]) != 0) {
        if (symbol >= 32 && symbol <= 96) {
            i = 21 * osscreen_cursor_y[screen_id];
            i += osscreen_cursor_x[screen_id];
            osscreen[screen_id][i] = symbol;
            osscreen_cursor_x[screen_id]++;

            if (osscreen_cursor_x[screen_id] >= 21) {
                osscreen_cursor_x[screen_id] = 0;
                osscreen_cursor_y[screen_id]++;
            }
        } else if (symbol == 13) {
            osscreen_cursor_x[screen_id] = 0;
            osscreen_cursor_y[screen_id]++;
        } else if (symbol == 9) {
            osscreen_cursor_x[screen_id] /= (3 * 4);
            osscreen_cursor_x[screen_id]++;
            osscreen_cursor_x[screen_id] *= (3 * 4);

            if (osscreen_cursor_x[screen_id] >= 21) {
                osscreen_cursor_x[screen_id] = 0;
                osscreen_cursor_y[screen_id]++;
            }
        }

        j++;
    }
}

int8_t gnc_pos            = 0;      // Character number in command line.
int32_t goesfile_pos      = 0;      // Position of the GOES output file
char goesnet_command[120] = "_";    // GOES Net Command Line
const char *comm = "data/comm.bin"; // File di comunicazione dei moduli.

/* Freezes the situation (when exiting the program or running a module). */

void freeze() {
    FILE *fh = fopen(situation_file, "w");

    if (fh == nullptr) {
        return;
    }

    /* TODO: Should this be converted
     * to a struct to be written instead? */
    fwrite(&nsync, 1, 1, fh);
    fwrite(&anti_rad, 1, 1, fh);
    fwrite(&pl_search, 1, 1, fh);
    fwrite(&field_amplificator, 1, 1, fh);
    fwrite(&ilight, 1, 1, fh);
    fwrite(&ilightv, 1, 1, fh);
    fwrite(&charge, 1, 1, fh);
    fwrite(&revcontrols, 1, 1, fh);
    fwrite(&ap_targetting, 1, 1, fh);
    fwrite(&ap_targetted, 1, 1, fh);
    fwrite(&ip_targetting, 1, 1, fh);
    fwrite(&ip_targetted, 1, 1, fh);
    fwrite(&ip_reaching, 1, 1, fh);
    fwrite(&ip_reached, 1, 1, fh);
    fwrite(&ap_target_spin, 1, 1, fh);
    fwrite(&ap_target_r, 1, 1, fh);
    fwrite(&ap_target_g, 1, 1, fh);
    fwrite(&ap_target_b, 1, 1, fh);
    fwrite(&nearstar_spin, 1, 1, fh);
    fwrite(&nearstar_r, 1, 1, fh);
    fwrite(&nearstar_g, 1, 1, fh);
    fwrite(&nearstar_b, 1, 1, fh);
    fwrite(&gburst, 1, 1, fh);
    fwrite(&menusalwayson, 1, 1, fh);
    fwrite(&depolarize, 1, 1, fh);
    fwrite(&sys, 1, 2, fh);
    fwrite(&pwr, 1, 2, fh);
    fwrite(&dev_page, 1, 2, fh);
    fwrite(&ap_target_class, 1, 2, fh);
    fwrite(&f_ray_elapsed, 1, 2, fh);
    fwrite(&nearstar_class, 1, 2, fh);
    fwrite(&nearstar_nop, 1, 2, fh);
    fwrite(&pos_x, 1, 4, fh);
    fwrite(&pos_y, 1, 4, fh);
    fwrite(&pos_z, 1, 4, fh);
    fwrite(&user_alfa, 1, 4, fh);
    fwrite(&user_beta, 1, 4, fh);
    fwrite(&navigation_beta, 1, 4, fh);
    fwrite(&ap_target_ray, 1, 4, fh);
    fwrite(&nearstar_ray, 1, 4, fh);
    fwrite(&dzat_x, 1, 8, fh);
    fwrite(&dzat_y, 1, 8, fh);
    fwrite(&dzat_z, 1, 8, fh);
    fwrite(&ap_target_x, 1, 8, fh);
    fwrite(&ap_target_y, 1, 8, fh);
    fwrite(&ap_target_z, 1, 8, fh);
    fwrite(&nearstar_x, 1, 8, fh);
    fwrite(&nearstar_y, 1, 8, fh);
    fwrite(&nearstar_z, 1, 8, fh);
    fwrite(&helptime, 1, 8, fh);
    fwrite(&ip_target_initial_d, 1, 8, fh);
    fwrite(&requested_approach_coefficient, 1, 8, fh);
    fwrite(&current_approach_coefficient, 1, 8, fh);
    fwrite(&reaction_time, 1, 8, fh);
    fwrite(&fcs_status, 1, 11, fh);
    fwrite(&fcs_status_delay, 1, 2, fh);
    fwrite(&psys, 1, 2, fh);
    fwrite(&ap_target_initial_d, 1, 8, fh);
    fwrite(&requested_vimana_coefficient, 1, 8, fh);
    fwrite(&current_vimana_coefficient, 1, 8, fh);
    fwrite(&vimana_reaction_time, 1, 8, fh);
    fwrite(&lithium_collector, 1, 1, fh);
    fwrite(&autoscreenoff, 1, 1, fh);
    fwrite(&ap_reached, 1, 1, fh);
    fwrite(&lifter, 1, 2, fh);
    fwrite(&secs, 1, 8, fh);
    fwrite(&data, 1, 1, fh);
    fwrite(&surlight, 1, 1, fh);
    fwrite(&gnc_pos, 1, 1, fh);
    fwrite(&goesfile_pos, 1, 4, fh);
    fwrite(goesnet_command, 1, 120, fh);

    fclose(fh);
}

/* Get the Noctis executable's relative path
 * 	and strip the name to leave only the directory.
 */
char *argv0;
char *get_exe_dir() {
    char *directory;

    directory = (char *) malloc(strlen(argv0) + 1);
    strcpy(directory, argv0);

    /* Effectively cuts off the "nivlr"
     * 	part of the path */
    *(strrchr(directory, '/') + 1) = '\0';

    return directory;
}

// Execution of an executable module of the GOES Net.
void run_goesnet_module() {
    as::script_output.clear();

    try {
        // Remove '_' from the command
        goesnet_command[gnc_pos] = 0;

        printf("Loading script...\n");
        as::load_script(goesnet_command);

        printf("Grabbing module...\n");
        asIScriptModule *module = as::engine->GetModule(goesnet_command, asGM_ONLY_IF_EXISTS);

        printf("Creating context...\n");
        asIScriptContext *context = as::get_main_context(module);

        printf("Executing...\n");
        context->Execute();

        context->Release();
    }
    catch (std::exception e) {
        printf("%s\n", e.what());
    }

    /* FILE *ch;

     * Allows for prepending './' to the command,
     * 	so that a bash shell can run the proper module file.
     * TODO: Find a better solution that doesn't involve
     * 	this wasteful malloc call. *
    char *command_prepended = (char *) malloc(200);

    // Reading the path to the Noctis binary
    char *dir = get_exe_dir();

    // Save the situation because some modules need it.
    freeze();

    // Check resident commands.
    if (memcmp(goesnet_command, "CLR", 3) != 0) {
        ch = fopen(goesoutputfile, "w");

        if (ch != nullptr) {
            fwrite("(UNKNOWN MODULE)", 1, 16, ch);
            fclose(ch);
        }

         * Delete the last character (which is the '_' cursor) from the command
         * line, then add the redirection to the "goesfile.txt" file.
         *
        goesnet_command[gnc_pos] = 0;
        strcat(goesnet_command, " >");
        strcat(goesnet_command, goesoutputfile);
        // strcpy(command_prepended, (char*)".");
        strcpy(command_prepended, dir);
        strcat(command_prepended, goesnet_command);
        system(command_prepended);
    } else {
        remove(goesoutputfile);
    }

    // Free space allocated for command.
    free(command_prepended);

    // Free space allocated for exe path
    free(dir); */

    /*
    if (!adapted) {
        printf("Sorry, GOES Net crashed.\n");
        printf("System integrity compromised: any key to quit.\n\n");
        get_key();
        exit(0xFF);
    } else {
        // It reacts to the presence of data in the communication file.
        ch = fopen(comm, "w");

        if (ch != nullptr) {
            uint32_t len = fseek(ch, 0, SEEK_END);
            fseek(ch, 0, SEEK_SET);
            if (len == 2) {
                if (ap_reached) {
                    if (pwr > 15000) {
                        if (fread(&ip_targetted, 1, 2, ch) == 2) {
                            ip_targetted--;
                            fix_local_target();
                            ip_targetting = 0;
                            ip_reached    = 0;
                            ip_reaching   = 1; // Automatic start
                        }
                    }
                } else {
                    status("NEED RECAL", 75);
                }
            }

            if (len == 24) {
                fread(&ap_target_x, 1, 8, ch);
                fread(&ap_target_y, 1, 8, ch);

                if (fread(&ap_target_z, 1, 8, ch) == 8) {
                    ap_targetting = 0;
                    extract_ap_target_infos();
                    fix_remote_target();

                    if (lithium_collector || manual_target) {
                        status("CONFLICT", 50);
                    } else {
                        if (pwr > 15000) {
                            stspeed      = 1; // Automatic start
                            nsnp         = 1;
                            ip_reached   = 0;
                            ip_targetted = -1;
                        }
                    }
                }
            }
            fclose(ch);
            remove(comm);
        }
    } */

    force_update = 1;
    goesfile_pos = 0;
}

/* On-board computer screen tracking group */

uint32_t pp[32] = {0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010,
                   0x00000020, 0x00000040, 0x00000080, 0x00000100, 0x00000200,
                   0x00000400, 0x00000800, 0x00001000, 0x00002000, 0x00004000,
                   0x00008000, 0x00010000, 0x00020000, 0x00040000, 0x00080000,
                   0x00100000, 0x00200000, 0x00400000, 0x00800000, 0x01000000,
                   0x02000000, 0x04000000, 0x08000000, 0x10000000, 0x20000000,
                   0x40000000, 0x80000000};

void digit_at(int8_t digit, float x, float y, float size, uint8_t color,
              int8_t shader) {
    // This is an alphanumeric character.
    uint8_t *prev_txtr = txtr;
    float vx[4], vy[4], vz[4] = {0, 0, 0, 0};
    float size_x_left  = size * - 1.5f;
    float size_y_left  = size * - 2.0f;
    float size_x_right = size * + 4.0f;
    float size_y_right = size * + 8.0f;
    int32_t prev_xs    = XSIZE;
    int32_t prev_ys    = YSIZE;
    int16_t n, m, d, i;
    int8_t pixel_color = color % 64;
    int8_t map_base    = ((uint8_t)(color >> 6u)) << 6u;

    if (reset_signal > 100) {
        pixel_color -= (reset_signal - 100);

        if (pixel_color < 0) {
            pixel_color = 0;
        }
    }

    if (digit > 32 && digit <= 96) {
        txtr = p_surfacemap;
        d    = (digit - 32) * 36;

        // TODO; Valgrind said there was a big bad invalid write happening here,
        //  so I just blindly changed this loop to start at one. It probably
        //  breaks things...
        for (n = 1; n < 36; n++) {

            i           = 256 * n - 5;
            txtr[i - 1] = 0; // Avoid aliasing at the end of the scanline.

            for (m = 0; m < 32; m++) {
                if (digimap2[n + d] & pp[m]) {
                    txtr[i] = pixel_color;
                } else {
                    txtr[i] = 0;
                }

                i++;
            }

            if (shader) {
                pixel_color--;
            }
        }

        txtr[256 * 36 - 6] = 0; // Avoids aliasing at the end of the matrix.
        vx[3]              = x + size_x_left;
        vx[0]              = x + size_x_right;
        vx[1]              = x + size_x_right;
        vx[2]              = x + size_x_left;
        vy[3]              = y + size_y_left;
        vy[0]              = y + size_y_left;
        vy[1]              = y + size_y_right;
        vy[2]              = y + size_y_right;
        setfx(2);
        XSIZE = 512;
        YSIZE = 576;
        polymap(vx, vy, vz, 4, map_base);
        XSIZE = prev_xs;
        YSIZE = prev_ys;
        txtr  = prev_txtr;
        resetfx();
    }
}

void screen() {
    float x, y;
    int16_t c, p, t = 0;
#define blinkscolor 127
#define screencolor 127

    if (ap_targetting) {
        return;
    }

    if (pwr <= 15000 && !charge) {
        fast_srand((int32_t) secs);
        c = fast_random(3) + 2;

        if (clock() % c) {
            return;
        }
    }

    x = cam_x;
    y = cam_y;

    for (p = -2; p < 2; p++)
        for (c = -64; c < 64; c++) {
            cam_x = x - ((float) (c * 30));

            if (c < -44) {
                if (s_control || menusalwayson) {
                    cam_x += 50;
                    cam_y = y - ((float) (p * 50));
                } else {
                    t += 19;
                    c += 19;
                    goto passby;
                }
            }

            if (c == -44) {
                if (s_command || menusalwayson) {
                    if (p == -2 || menusalwayson) {
                        cam_y = y - ((float) (p * 50));
                    } else {
                        t += 108;
                        break;
                    }
                } else {
                    if (!infoarea || p == -2) {
                        t += 108;
                        break;
                    } else {
                        cam_y = y - ((float) (p * 46)) - 12;
                    }
                }
            }

            if (ctb[t] >= 'A' && ctb[t] <= 'Z') {
                digit_at(ctb[t], -6, -16, 4, blinkscolor - 12 * (clock() % 6),
                         1);
            } else {
                if (ctb[t] >= 'a' && ctb[t] <= 'z') {
                    digit_at(ctb[t] - 32, -6, -16, 4, screencolor, 1);
                } else {
                    digit_at(ctb[t], -6, -16, 4, screencolor, 1);
                }
            }

        passby:
            t++;
        }

    cam_x = x;
    cam_y = y;
}

// Draw the surface map at the time you want to land.

void show_planetary_map() {
    int8_t is_moon;
    int16_t lat, lon, i, j, p;

    if (nearstar_p_owner[ip_targetted] > -1) {
        is_moon = 1;
    } else {
        is_moon = 0;
    }

    lon = landing_pt_lon - 22;

    for (i = 0; i < 48; i++) {
        while (lon > 359) {
            lon -= 360;
        }

        while (lon < 0) {
            lon += 360;
        }

        lat = landing_pt_lat - 14;

        for (j = 0; j < 32; j++) {
            p = ((uint16_t)(j + 9) << 8u) + i + 14;

            if (lat > 0 && lat < 120) {
                ptr = lat * 360 + lon;

                if (is_moon) {
                    p_surfacemap[p] = s_background[ptr] + 128;
                } else {
                    p_surfacemap[p] = p_background[ptr] + 192;
                }
            } else {
                p_surfacemap[p] = 4;
            }

            lat++;
        }

        lon++;
    }
}

/*  Draw the stardrifter. (The one you are using, seen from the inside.)
    It also assumes the task of deciphering keyboard commands for GOESnet. */

// What do these variables do?
int16_t goesk_a = -1;
int16_t goesk_e = -1;

void vehicle(float opencapcount) {
    int16_t n, c, i, j, k;
    int8_t short_text[11];
    uint8_t chcol;
    float backup_cam_x, backup_cam_z;
    float backup_beta = beta;
    float chry;
    float vx[4], vy[4], vz[4];
    float osscreen_x[4], osscreen_z[4];
    float osscreen_y[4] = {-20 * 15, 14 * 15, 14 * 15, -20 * 15};

    if (elight) {
        memset(osscreen[0], 0, 7 * 21);
        memset(osscreen[1], 0, 7 * 21);
    }

    // Tracking of panoramic domes when not closing to form capsule.
    if (opencapcount == 0.0) {
        cam_z += 3100;
        cam_y -= 550;
        polycupola(0, 0);
        setfx(0);
        cupola(0, 8);
        resetfx();
        cam_y += 550;

        if (!ontheroof) {
            polycupola(+1, 0);
            setfx(0);
            cupola(+1, 8);
            resetfx();
        }

        cam_z -= 3100;
    }

    /* Rest of the hull. If you are on the terrace, stop here after drawing the
     * upper dome, which must be superimposed on the hull.
     */
    if (depolarize) {
        setfx(2);
        drawpv(vehicle_handle, 2, 3, 0.0, 0.0, 0.0, 0);
        resetfx();
    } else {
        drawpv(vehicle_handle, 2, 2, 0.0, 0.0, 0.0, 0);
    }

    if (ontheroof) {
        cam_z += 3100;
        polycupola(+1, 0);
        setfx(0);
        cupola(+1, 8);
        resetfx();
        cam_z -= 3100;
        return;
    }

    // Key interception (priority) for GOESnet.

    if (force_update || (active_screen == 0 && is_key())) {
        if (!force_update) {
            goesk_a = -1;
            c       = get_key();

            if (!c) {
                c       = get_key();
                goesk_e = c;

                if (c == 0x47) {
                    goesnet_command[0] = '_';
                    goesnet_command[1] = 0;
                    gnc_pos            = 0;
                    goesk_e            = -1;
                }
            } else {
                if (c == 27) {
                    goesk_a = c; // Pass the keystroke
                } else if (c == 8 && gnc_pos > 0) {
                    goesnet_command[gnc_pos - 1] = '_';
                    goesnet_command[gnc_pos]     = 0;
                    gnc_pos--;
                } else if (c == 13) {
                    run_goesnet_module();
                    n = 0;

                    if (!memcmp(goesnet_command, "CAST", 4)) {
                        i = 0;

                        while (i < gnc_pos) {
                            if (goesnet_command[i] == ':') {
                                n = i + 1;
                                break;
                            }

                            i++;
                        }
                    }
                    goesnet_command[n]     = '_';
                    goesnet_command[n + 1] = 0;
                    gnc_pos                = n;
                }

                // Transform quotation marks.
                if (c == 34) {
                    c = 39;
                }

                // Uppercase letters.
                if (c >= 'a' && c <= 'z') {
                    c -= 32;
                }

                // Check for invalid characters.
                if (c != 36 && c != 38 && c != 60 && c != 62) {
                    // Enter valid characters.
                    if ((c >= 32 && c <= 90 && gnc_pos < 83) || (c == 95)) {
                        goesnet_command[gnc_pos]     = c;
                        goesnet_command[gnc_pos + 1] = '_';
                        goesnet_command[gnc_pos + 2] = 0;
                        gnc_pos++;
                    }
                }
            }
        }

        memset(osscreen[0] + 3 * 21, 0, 4 * 21);
        mslocate(0, 0, 3);
        mswrite(0, (char *) goesnet_command);
    }

    /* Key interception (priority) for the "STARMAP TREE". */
    // Starmap Tree???
    if (force_update || (active_screen == 1 && is_key())) {
        if (!force_update) {
            while (is_key()) {
                c       = get_key();
                goesk_a = c;

                if (!c) {
                    goesk_a = -1;
                    c       = get_key();
                    goesk_e = c;

                    //TODO: Replace DOS hex keycodes with SDL2 scancodes
                    switch (c) {
                    case 0x4F: // End key
                    case 0x76: // Pg-Down
                    case 0x91: { // CTRL-Down
                        FILE *screenfile = fopen(goesoutputfile, "r");

                        if (screenfile != nullptr) {
                            uint32_t len = fseek(screenfile, 0, SEEK_END);
                            fseek(screenfile, 0, SEEK_SET);
                            goesfile_pos = len - 7 * 21;

                            if (goesfile_pos < 0) {
                                goesfile_pos = 0;
                            }

                            fclose(screenfile);
                        }

                        goesk_e = -1;
                        break;
                    }
                    case 0x47: // Home Button
                    case 0x84: // CTRL-PgUp
                    case 0x8D: // CTRL-Up
                        goesfile_pos = 0;
                        goesk_e      = -1;
                        break;

                    case 80: // Down arrow key
                        goesfile_pos += 21;
                        goesk_e = -1;
                        break;

                    case 72: // Up arrow key
                        goesfile_pos -= 21;

                        if (goesfile_pos < 0) {
                            goesfile_pos = 0;
                        }

                        goesk_e = -1;
                        break;

                    case 0x51: // Page Down
                        goesfile_pos += 21 * 7;
                        goesk_e = -1;
                        break;

                    case 0x49: // Page Up
                        goesfile_pos -= 21 * 7;

                        if (goesfile_pos < 0) {
                            goesfile_pos = 0;
                        }

                        goesk_e = -1;
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        memset(osscreen[1], 0, 21 * 7);

        //Convert all character to uppercase,
        // since only uppercase chars can be displayed.
        for (auto ich = as::script_output.begin(); ich < as::script_output.end(); ++ich) {
            *ich = toupper(*ich);
        }

        // TODO: Length checking so we don't overflow the screen buffer
        memcpy(osscreen[1], as::script_output.c_str(), as::script_output.size());
    }

    // Intercettazione tasti (prioritaria) per la planetary map.

    if (active_screen == 2 && is_key()) {
    krep2:
        c       = get_key();
        goesk_a = c;

        if (!c) {
            goesk_a = -1;
            c       = get_key();
            goesk_e = c;

            if (landing_point) {
                switch (c) {
                case 77:
                    landing_pt_lon++;

                    if (landing_pt_lon >= 360) {
                        landing_pt_lon -= 360;
                    }

                    goesk_e = -1;
                    break;

                case 75:
                    landing_pt_lon--;

                    if (landing_pt_lon < 0) {
                        landing_pt_lon += 360;
                    }

                    goesk_e = -1;
                    break;

                case 80:
                    landing_pt_lat++;

                    if (landing_pt_lat > 119) {
                        landing_pt_lat = 119;
                    }

                    goesk_e = -1;
                    break;

                case 72:
                    landing_pt_lat--;

                    if (landing_pt_lat < 1) {
                        landing_pt_lat = 1;
                    }

                    goesk_e = -1;
                    break;

                case 0x74:
                    landing_pt_lon += 3;

                    if (landing_pt_lon >= 360) {
                        landing_pt_lon -= 360;
                    }

                    goesk_e = -1;
                    break;

                case 0x73:
                    landing_pt_lon -= 3;

                    if (landing_pt_lon < 0) {
                        landing_pt_lon += 360;
                    }

                    goesk_e = -1;
                    break;

                case 0x91:
                    landing_pt_lat += 3;

                    if (landing_pt_lat > 119) {
                        landing_pt_lat = 119;
                    }

                    goesk_e = -1;
                    break;

                case 0x8D:
                    landing_pt_lat -= 3;

                    if (landing_pt_lat < 1) {
                        landing_pt_lat = 1;
                    }

                    goesk_e = -1;
                default:
                    break;
                }
            }
        } else {
            if (landing_point) {
                if (c == 13) {
                    land_now = 1;
                    goesk_a  = -1;
                }

                if (c == 27) {
                    landing_point = 0;
                    status("CANCELLED", 50);
                    goesk_a = -1;
                }

                /*  Unit� di debugging dell'albedo
                    uint8_t far *ov=(uint8_t far*)objectschart;
                    if (c == 'b') {
                    ov[(18 + 60*360) / 2] += 4;
                    p_background[18 + 60*360] ++;
                    }
                    if (c == 'd') {
                    ov[(18 + 60*360) / 2] -= 4;
                    p_background[18 + 60*360] --;
                    }*/
            }
        }

        if (is_key()) {
            goto krep2;
        }
    }

    // Tracciamento degli schermi di GOESNet.
    // Si tratta dei primi due schermi sulla paratia destra.
    // Tracking GOESNet screens.
    // These are the first two screens on the right bulkhead.
    H_MATRIXS = 6;
    V_MATRIXS = 3;
    change_txm_repeating_mode();
    txtr          = p_surfacemap + 256 * 8 + 16;
    osscreen_z[0] = -104 * 15;
    osscreen_z[1] = -104 * 15;
    osscreen_z[2] = -154 * 15;
    osscreen_z[3] = -154 * 15;
    osscreen_x[0] = +236 * 15;
    osscreen_x[1] = +236 * 15;
    osscreen_x[2] = +236 * 15;
    osscreen_x[3] = +236 * 15;
    vx[0]         = 236 * 15;
    vx[1]         = 236 * 15;
    vx[2]         = 236 * 15;
    vx[3]         = 236 * 15;
    vy[0]         = -22 * 15;
    vy[1]         = -23 * 15;
    vy[2]         = -23 * 15;
    vy[3]         = -22 * 15;
    vz[0]         = -104 * 15;
    vz[1]         = -104 * 15;
    vz[2]         = -108 * 15;
    vz[3]         = -108 * 15;
    n             = 0;

    while (n < 2) {
        poly3d(osscreen_x, osscreen_y, osscreen_z, 4, 68);
        beta += 90;

        if (beta > 359) {
            beta -= 360;
        }

        change_angle_of_view();
        backup_cam_x = cam_x;
        backup_cam_z = cam_z;
        cam_z        = backup_cam_x - 236 * 15;
        chry         = -18 * 15;
        chcol        = 152;
        k            = 0;

        for (j = 0; j < 7; j++) {
            cam_x = -backup_cam_z - 105 * 15;

            for (i = 0; i < 21; i++) {
                c = osscreen[n][k + i];

                if (c > 48 && c < 91) {
                    digit_at(c, 0, chry, 5.5, chcol, 0);
                } else {
                    if (c == '(') {
                        chcol = 191;
                    }

                    if (c != '$' && c != '[' && c != ']' && c != '*' &&
                        c != '&' && c != '_') {
                        digit_at(c, 0, chry, 5.5, chcol, 0);
                    } else {
                        digit_at(c, 0, chry, 6.5, 138, 0);
                    }

                    if (c == ')') {
                        chcol = 152;
                    }
                }

                cam_x -= 2.35 * 15;
            }

            k += 21;
            chry += 4.5 * 15;
        }

        cam_x = backup_cam_x;
        cam_z = backup_cam_z;
        beta  = backup_beta;
        change_angle_of_view();

        if (n == active_screen) {
            poly3d(vx, vy, vz, 4, 63);
        } else {
            poly3d(vx, vy, vz, 4, 00);
        }

        cam_z += 54 * 15;
        n++;
    }

    // Tracing the planetary map.
    // After the GOES screen.
    H_MATRIXS = 3;
    V_MATRIXS = 2;
    change_txm_repeating_mode();

    if (landing_point) {
        show_planetary_map();
        polymap(osscreen_x, osscreen_y, osscreen_z, 4, 0);
        sprintf((char *) short_text, "LQ %03d:%03d", landing_pt_lon,
                landing_pt_lat);
        status((char *) short_text, 10);
    } else {
        poly3d(osscreen_x, osscreen_y, osscreen_z, 4, 4);
    }

#define surface_crosshair_x_shift +25
#define surface_crosshair_y_shift -10
#define surface_crosshair_x_spacing +11
#define surface_crosshair_y_spacing +10
    setfx(2);
    stick3d(osscreen_x[0], osscreen_y[0],
            osscreen_z[0] - 27 * 15 - surface_crosshair_x_spacing +
                surface_crosshair_x_shift,
            osscreen_x[0], osscreen_y[1],
            osscreen_z[0] - 27 * 15 - surface_crosshair_x_spacing +
                surface_crosshair_x_shift);
    stick3d(osscreen_x[0], osscreen_y[0],
            osscreen_z[0] - 27 * 15 + surface_crosshair_x_spacing +
                surface_crosshair_x_shift,
            osscreen_x[0], osscreen_y[1],
            osscreen_z[0] - 27 * 15 + surface_crosshair_x_spacing +
                surface_crosshair_x_shift);
    stick3d(osscreen_x[0],
            osscreen_y[0] + 17 * 15 - surface_crosshair_y_spacing +
                surface_crosshair_y_shift,
            osscreen_z[0], osscreen_x[0],
            osscreen_y[0] + 17 * 15 - surface_crosshair_y_spacing +
                surface_crosshair_y_shift,
            osscreen_z[2]);
    stick3d(osscreen_x[0],
            osscreen_y[0] + 17 * 15 + surface_crosshair_y_spacing +
                surface_crosshair_y_shift,
            osscreen_z[0], osscreen_x[0],
            osscreen_y[0] + 17 * 15 + surface_crosshair_y_spacing +
                surface_crosshair_y_shift,
            osscreen_z[2]);
    resetfx();

    if (active_screen == 2) {
        poly3d(vx, vy, vz, 4, 63);
    } else {
        poly3d(vx, vy, vz, 4, 00);
    }

    // Finish screen tracking.
    cam_z -= 2 * 54 * 15;
    txtr = p_background;

    if (force_update) {
        force_update = 0;
    }

    // Tracing of the internal lamp.
    cam_x -= 3395;
    cam_y += 480;
    cam_z += 200;
    alogena();
    cam_x += 3395;
    cam_y -= 480;
    cam_z -= 200;

    // Tracing of panoramic domes when closing to form capsule.
    if (opencapcount != 0.0) {
        chry = cam_y;
        cam_z += 3100;
        cam_y = chry + opencapcount * 9.55f - 550;
        polycupola(-opencapcount / 85, 0);
        setfx(0);
        cupola(-opencapcount / 85, 8);
        resetfx();
        cam_y = chry - opencapcount * 9.55f;

        if (!ontheroof) {
            polycupola(+1, 0);
            setfx(0);
            cupola(+1, 8);
            resetfx();
        }

        cam_z -= 3100;
        cam_y = chry;
    }
}

/* Draw a starlight, seen from the outside */

void other_vehicle_at(double ovhx, double ovhy, double ovhz) {
    cam_x = (float) -ovhx;
    cam_y = (float) -ovhy;
    cam_z = (float) -ovhz;
    cam_z += 3100;
    setfx(2);

    if (ovhy > -375) {
        cupola(+1, 8);
    }

    if (ovhy < +375) {
        cupola(-1, 8);
    }

    resetfx();
    cam_z -= 3100;
    cam_x = 0;
    cam_y = 0;
    cam_z = 0;
    drawpv(vehicle_handle, 0, 0, (float) ovhx, (float) ovhy, (float) ovhz, 1);
    cam_x = (float) -ovhx;
    cam_y = (float) -ovhy;
    cam_z = (float) -ovhz;
    cam_z += 3100;
    setfx(2);

    if (ovhy > +375) {
        cupola(+1, 8);
    }

    if (ovhy < -375) {
        cupola(-1, 8);
    }

    resetfx();
    cam_z -= 3100;
    lens_flares_for(cam_x, cam_y, cam_z, 3225, 0, 0, -5e5, 3, 1, 1, 1, 1);
    lens_flares_for(cam_x, cam_y, cam_z, -3225, 0, 0, -5e5, 3, 1, 1, 1, 1);
    lens_flares_for(cam_x, cam_y, cam_z, 3225, 0, -6150, -5e5, 3, 1, 1, 1, 1);
    lens_flares_for(cam_x, cam_y, cam_z, -3225, 0, -6150, -5e5, 3, 1, 1, 1, 1);
}

/* Fine roba importata da noctis-0.cpp */

/* Global variables for general use. */

int8_t aso_countdown  = 100; // counter for the function "autoscreenoff"
int32_t tgt_label_pos = -1;  // selected target label position
int16_t tgts_in_show  = 0;   // targets currently displayed

/* Cartography management data. */

int8_t targets_in_range = 0;
int32_t sm_consolidated = 0;

int8_t target_name[4][24];

int8_t iptargetstring[11];
int8_t iptargetchar = 0;
int8_t iptargetplanet;
int8_t iptargetmoon;

double ap_target_id = 12345, ap_target_previd = 54321;
double current_planet_id = 12345, prev_planet_id = 54321;
int8_t labstar = 0, labplanet = 0, labstar_char = 0, labplanet_char = 0;
int32_t star_label_pos = -1, planet_label_pos = -1;

double star_id           = 12345;
int8_t star_label[25]    = "UNKNOWN STAR / CLASS ...";
int8_t star_no_label[25] = "UNKNOWN STAR / CLASS ...";

double planet_id           = 12345;
int8_t planet_label[25]    = "NAMELESS PLANET / N. ...";
int8_t planet_no_label[25] = "NAMELESS PLANET / N. ...";
int8_t moon_no_label[25]   = "NAMELESS MOON #../../...";

const char *sr_message = "SYSTEM RESET";

void update_star_label() {
    if (ap_targetted == -1) {
        strcpy((char *) star_label, "- DIRECT PARSIS TARGET -");
    } else {
        ap_target_id =
            ap_target_x / 100000 * ap_target_y / 100000 * ap_target_z / 100000;

        if (ap_target_id != ap_target_previd) {
            ap_target_previd = ap_target_id;
            star_label_pos   = search_id_code(ap_target_id, 'S');

            if (star_label_pos != -1) {
                FILE* smh = fopen(starmap_file, "r");
                fseek(smh, star_label_pos, SEEK_SET);
                fread(&star_id, 8, 1, smh);
                fread(&star_label, 24, 1, smh);
                fclose(smh);
            } else {
                memcpy(star_label, star_no_label, 24);
            }

            brtl_srand((uint16_t) ap_target_id);
            sprintf((char *) (star_label + 21), "S%02d",
                    brtl_random(star_classes));
        }
    }
}

void update_planet_label() {
    current_planet_id = nearstar_identity + ip_targetted + 1;

    if (current_planet_id != prev_planet_id) {
        prev_planet_id   = current_planet_id;
        planet_label_pos = search_id_code(current_planet_id, 'P');

        if (planet_label_pos != -1) {
            FILE* smh = fopen(starmap_file, "r");
            fseek(smh, planet_label_pos, SEEK_SET);
            fread(&planet_id, 8, 1, smh);
            fread(&planet_label, 24, 1, smh);
            fclose(smh);
        } else {
            if (nearstar_p_owner[ip_targetted] == -1) {
                memcpy(planet_label, planet_no_label, 24);
            } else {
                memcpy(planet_label, moon_no_label, 24);
                sprintf((char *) (planet_label + 15), "%02d",
                        nearstar_p_moonid[ip_targetted] + 1);
                sprintf((char *) (planet_label + 18), "%02d",
                        nearstar_p_owner[ip_targetted] + 1);
                planet_label[17] = '/';
                planet_label[20] = '&';
            }
        }

        sprintf((char *) (planet_label + 21), "P%02d", ip_targetted + 1);
    }
}

// Control the flight (Flight Control System).
void fcs() {
    int16_t n;

    if (ip_targetted != -1) {
        cline(1, "local target: ");

        if (nearstar_p_owner[ip_targetted] > -1) {
            other("moon #");
            other(alphavalue(nearstar_p_moonid[ip_targetted] + 1));
            other(" of ");
            n = nearstar_p_owner[ip_targetted];
        } else {
            n = ip_targetted;
        }

        other((char *) ord[n + 1]);
        other(" planet. ");
        other((char *) planet_description[nearstar_p_type[ip_targetted]]);
    }

    if (ap_targetted) {
        if (ap_targetted == 1) {
            cline(2, "remote target: class ");
            other(alphavalue(ap_target_class));
            other(" star; ");
            other((char *) star_description[ap_target_class]);
        } else {
            cline(2, "direct parsis target: non-star type.");
        }
    } else {
        cline(2, "no remote target selected");
    }

    cline(3, "current range: elapsed ");
    float xx = (float) pwr - 15000;

    if (xx < 0) {
        xx = 0;
    }

    other(alphavalue(xx));
    other(" kilodyams, remaining lithium: ");
    other(alphavalue(charge));
    other(" grams.");
    command(0, "set remote target");

    if (stspeed) {
        command(1, "stop vimana flight");
    } else {
        command(1, "start vimana flight");
    }

    if (landing_point) {
        command(3, "cancel landing request");
    } else {
        command(3, "deploy surface capsule");
    }

    if (ip_targetted == -1 || ip_reached) {
        command(2, "set local target");
    } else {
        if (ip_reaching) {
            command(2, "stop fine approach");
        } else {
            command(2, "start fine approach");
            command(3, "clear local target");
        }
    }
}

/* FCS Commands. */

void fcs_commands() {
    switch (s_command) {
    case 1:
        if (stspeed || manual_target) {
            status("CONFLICT", 50);
            break;
        }

        status("TGT-REMOTE", 50);
        ap_targetting = 1;
        ap_targetted  = 0;
        break;

    case 2:
        if (stspeed) {
            stspeed = 0;
            status("IDLE", 50);
        } else {
            if (lithium_collector || manual_target) {
                status("CONFLICT", 50);
                break;
            }

            if (pwr > 15000) {
                stspeed = 1;

                if (ap_targetted) {
                    nsnp         = 1;
                    ap_reached   = 0;
                    ip_reached   = 0;
                    ip_targetted = -1;
                }
            }
        }

        break;

    case 3:
        if (ip_reached || ip_targetted == -1) {
            if (ap_reached) {
                status("TGT-LOCAL", 50);
                ip_targetted  = -1;
                ip_targetting = 1;
                ip_reaching   = 0;
                ip_reached    = 0;
                iptargetchar  = 0;
            } else {
                status("NEED RECAL", 75);
            }
        } else {
            if (ip_reaching) {
                status("IDLE", 50);
                ip_targetted = -1;
                ip_reaching  = 0;
                ip_reached   = 1;
            } else {
                if (pwr > 15000) {
                    ip_reaching = 1;
                    status("CONFIRM", 50);
                }
            }
        }

        break;

    case 4:
        if (!ip_reaching && ip_targetted != -1) {
            if (!ip_reached) {
                ip_targetted = -1;
                status("TGT REJECT", 50);
            } else {
                landing_point = 1 - landing_point;

                if (landing_point) {
                    if (nearstar_p_type[ip_targetted] == 0 ||
                        nearstar_p_type[ip_targetted] == 6 ||
                        nearstar_p_type[ip_targetted] >= 9) {
                        status("IMPOSSIBLE", 50);
                        landing_point = 0;
                    } else {
                        status("SURFACE", 50);
                        landing_pt_lon = 0;
                        landing_pt_lat = 60;
                    }
                } else {
                    status("IDLE", 50);
                }
            }
        } else {
            status("ERROR", 50);
        }
        break;
    default:
        break;
    }
}

/* Onboard devices: main menu and four submenus */

void devices() {
    double parsis_x, parsis_y, parsis_z;
    int16_t n, sp;
    int32_t lsecs;

    switch (dev_page) {
    case 0: // sub menu
        command(0, "navigation instruments");
        command(1, "miscellaneous");
        command(2, "galactic cartography");
        command(3, "emergency functions");
        cline(3, "SELECT ARGUMENT");
        break;

    case 1: // navigation status
        if (field_amplificator) {
            command(0, "STARFIELD AMPLIFICATOR");
            cline(1, "starfield amplification active, ");
        } else {
            command(0, "starfield amplificator");
            cline(1, "starfield amplification disabled, ");
        }

        if (anti_rad) {
            command(3, "FORCE RADIATIONS LIMIT");
            other("high-radiation fields are avoided.");
        } else {
            command(3, "force radiations limit");
            other("high-radiation fields are ignored.");
        }

        if (nsync) {
            if (ip_targetted != -1 && ip_reached) {
                sp = 0;

                for (n = 0; n < ip_targetted; n++) {
                    if (nearstar_p_type[n] != -1) {
                        sp++;
                    }
                }

                cline(1, "tracking status: performing ");

                if (nsync == 1) {
                    other("fixed-point chase.");
                    command(2, "fixed-point chase");
                }

                if (nsync == 2) {
                    other("far chase.");
                    command(2, "far chase");
                }

                if (nsync == 3) {
                    other("syncrone orbit.");
                    command(2, "syncrone orbit");
                }

                if (nsync == 4) {
                    other("high-speed orbit.");
                    command(2, "high-speed orbit");
                }

                if (nsync == 5) {
                    other("near chase.");
                    command(2, "near chase");
                }
            } else {
                cline(2, "tracking status: disconnected.");

                if (nsync == 1) {
                    command(2, "fixed-point chase");
                }

                if (nsync == 2) {
                    command(2, "far chase");
                }

                if (nsync == 3) {
                    command(2, "syncrone orbit");
                }

                if (nsync == 4) {
                    command(2, "high-speed orbit");
                }

                if (nsync == 5) {
                    command(2, "near chase");
                }
            }
        } else {
            cline(2, "tracking status: inactive.");
            command(2, "drive tracking mode");
        }

        if (pl_search) {
            command(1, "LOCAL PLANETS FINDER");
            float xx = (float) (nearstar_x - dzat_x);
            float yy = (float) (nearstar_y - dzat_y);
            float zz = (float) (nearstar_z - dzat_z);
            xx       = sqrt(xx * xx + yy * yy + zz * zz);

            if (xx < 20000) {
                if (nearstar_nop) {
                    cline(3, "planet finder report: system has ");
                    other(alphavalue(nearstar_nop));
                    other(" ");

                    if (nearstar_class == 9) {
                        other("proto");
                    }

                    if (nearstar_nop == 1) {
                        other("planet, and ");
                    } else {
                        other("planets, and ");
                    }

                    other(alphavalue(nearstar_nob - nearstar_nop));
                    other(" minor bodies. ");
                    other(alphavalue(nearstar_labeled));
                    other(" labeled out of ");
                    other(alphavalue(nearstar_nob));
                    other(".");
                } else {
                    cline(3, "planet finder report: there are no major bodies "
                             "in this system.");
                }
            } else {
                cline(3, "planet finder report: no stellar systems within "
                         "remote sensors range.");
            }
        } else {
            command(1, "local planets finder");
        }

        break;

    case 2: // miscellaneous devices status
        if (ilightv == 1) {
            command(0, "internal light on");
        } else {
            command(0, "internal light off");
        }

        command(1, "remote target data");
        command(2, "local target data");
        command(3, "environment data");

        if (data == 1) {
            command(1, "REMOTE TARGET DATA");
        }

        if (data == 2) {
            command(2, "LOCAL TARGET DATA");
        }

        if (data == 3) {
            command(3, "ENVIRONMENT DATA");
        }

        break;

    case 3: // galactic cartography status
        if (labstar) {
            command(0, "assign star label");
        } else {
            if (star_label_pos > -1) {
                command(0, "remove star label");
            } else {
                command(0, "label star as...");
            }
        }

        if (labplanet) {
            command(1, "assign planet label");
        } else {
            if (planet_label_pos > -1) {
                command(1, "remove planet label");
            } else {
                command(1, "label planet as...");
            }
        }

        if (targets_in_range) {
            command(2, "quit targets in range");
        } else {
            command(2, "show targets in range");
        }

        if (manual_target) {
            command(3, "(enter coordinates)");
        } else {
            command(3, "set target to parsis");
        }

        cline(1, "epoc ");
        other(alphavalue((int32_t) epoc));
        other(" triads ");
        lsecs = (int32_t) secs;
        lsecs -= lsecs % 1000000L;
        lsecs /= 1000000L;
        other(alphavalue(lsecs));
        other(",");
        lsecs = (int32_t) secs;
        lsecs %= 1000000L;
        lsecs -= lsecs % 1000;
        lsecs /= 1000;
        other(alphavalue(lsecs));
        other(",");
        lsecs = (int32_t) secs;
        lsecs %= 1000;
        other(alphavalue(lsecs));
        cline(2, "parsis universal coordinates: ");
        parsis_x = round(dzat_x);
        parsis_y = round(dzat_y);
        parsis_z = round(dzat_z);
        other(alphavalue(parsis_x));
        other(";");
        other(alphavalue(-parsis_y));
        other(";");
        other(alphavalue(parsis_z));
        cline(3, "heading pitch: ");
        other(alphavalue((int16_t)(sin(deg * navigation_beta) * +100)));
        other(";");
        other(alphavalue((int16_t)(cos(deg * navigation_beta) * -100)));
        break;

    case 4: // emergency functions status
        command(0, "reset onboard system");
        command(1, "send help request");

        if (lithium_collector) {
            command(2, "stop scoping lithium");
        } else {
            command(2, "scope for lithium");
        }

        command(3, "clear status");

        if (gburst == -1) {
            cline(1, "NOTE: there are no emergencies at the moment.");
            cline(2, "help request not sent.");
        }
        break;
    default:
        break;
    }
}

/* On-board device controls. */

int8_t dummy_identity[9] = "Removed:";
int8_t comp_data[32];

void dev_commands() {
    int16_t n;
    float dist;

    switch (dev_page) {
    case 0:
        dev_page = s_command;

        switch (s_command) {
        case 1:
            status("NAVIGATION", 50);
            break;
        case 2:
            status("SUPPORTS", 50);
            break;
        case 3:
            status("CARTOGRAFY", 50);
            break;
        case 4:
            status("EMERGENCY", 50);
            break;
        default:
            break;
        }

        break;

    case 1:
        switch (s_command) {
        case 1:
            field_amplificator = 1 - field_amplificator;

            if (field_amplificator) {
                status("ACTIVE", 50);
            } else {
                status("INACTIVE", 50);
            }

            break;

        case 2:
            pl_search = 1 - pl_search;

            if (pl_search) {
                status("ACTIVE", 50);
            } else {
                status("INACTIVE", 50);
            }

            break;

        case 3:
            nsync++;
            nsync %= 6;

            if (!nsync) {
                status("IDLE", 50);
                ip_reaching = 0;
                ip_reached  = 1;
            } else {
                status("ACQUIRED", 50);

                if (ip_reached) {
                    ip_reaching = 1;
                    ip_reached  = 0;
                }
            }

            break;

        case 4:
            anti_rad = 1 - anti_rad;

            if (anti_rad) {
                status("ACTIVE", 50);
            } else {
                status("INACTIVE", 50);
            }
            break;
        default:
            break;
        }
        break;

    case 2:
        switch (s_command) {
        case 1:
            ilightv = -ilightv;

            if (ilightv > 0) {
                status("ON", 50);
            } else {
                status("OFF", 50);
            }

            break;

        case 2:
            if (data == 1) {
                datasheetdelta = -2;
            } else {
                data           = 1;
                datasheetdelta = +2;
            }

            break;

        case 3:
            if (data == 2) {
                datasheetdelta = -2;
            } else {
                data           = 2;
                datasheetdelta = +2;
            }

            break;

        case 4:
            if (data == 3) {
                datasheetdelta = -2;
            } else {
                data           = 3;
                datasheetdelta = +2;
            }

            break;
        default:
            break;
        }

        break;

    case 3: // galactic cartography commands
        switch (s_command) {
        case 1:
            if (ap_targetted == 1 && !ap_targetting && !labplanet) {
                labstar = 1 - labstar;

                if (labstar) {
                    if (star_label_pos > -1) {
                        labstar = 0;

                        if (star_label_pos >= sm_consolidated) {
                            FILE* smh = fopen(starmap_file, "w");

                            if (smh != nullptr) {
                                fseek(smh, star_label_pos, SEEK_SET);
                                fwrite(&dummy_identity[0], 8, 1, smh);
                                fclose(smh);
                                ap_target_previd = 12345;
                                status("REMOVED", 50);
                                star_label_pos = -1;
                                nearstar_labeled--;
                            } else {
                                status("INT. ERROR", 50);
                            }
                        } else {
                            status("DENIED", 50);
                        }
                    } else {
                        status("PROMPT", 50);
                        labstar_char = 0;
                        star_id      = ap_target_id;

                        for (n = 0; n < 21; n++) {
                            star_label[n] = 32;
                        }
                    }
                } else {
                    FILE* smh = fopen(starmap_file, "r+");

                    if (smh == nullptr) {
                        smh             = fopen(starmap_file, "w+");
                        sm_consolidated = 4;
                        fwrite(&sm_consolidated, 4, 1, smh);
                    }

                    if (smh != nullptr) {
                        fseek(smh, 4, SEEK_SET);
                        while (fread(comp_data, 1, 32, smh) == 32)
                            if (memcmp(comp_data, dummy_identity, 8)) {
                                if (!strcasecmp((char *) (comp_data + 8),
                                                (char *) star_label)) {
                                    status("EXTANT", 50);
                                    ap_target_previd = 12345;
                                    star_label_pos   = -1;
                                    fclose(smh);
                                    return;
                                }
                            }

                        fseek(smh, 0, SEEK_END);
                        star_label_pos = fseek(smh, 0, SEEK_CUR);
                        fwrite(&star_id, 1, 32, smh);
                        fclose(smh);
                        status("ASSIGNED", 50);
                        nearstar_labeled++;
                    } else {
                        status("INT. ERROR", 50);
                    }
                }
            } else {
                status("CONFLICT", 50);
            }

            break;

        case 2:
            if (ip_targetted != -1 && !labstar) {
                labplanet = 1 - labplanet;

                if (labplanet) {
                    if (planet_label_pos > -1) {
                        labplanet = 0;

                        if (planet_label_pos >= sm_consolidated) {
                            FILE* smh = fopen(starmap_file, "w");

                            if (smh != nullptr) {
                                fseek(smh, planet_label_pos, SEEK_SET);
                                fwrite(&dummy_identity[0], 1, 8, smh);
                                fclose(smh);
                                prev_planet_id = 12345;
                                status("REMOVED", 50);
                                planet_label_pos = -1;
                                nearstar_labeled--;
                            } else {
                                status("INT. ERROR", 50);
                            }
                        } else {
                            status("DENIED", 50);
                        }
                    } else {
                        status("PROMPT", 50);
                        labplanet_char = 0;
                        planet_id      = nearstar_identity + ip_targetted + 1;

                        for (n = 0; n < 21; n++) {
                            planet_label[n] = 32;
                        }
                    }
                } else {
                    FILE* smh = fopen(starmap_file, "r+");

                    if (smh == nullptr) {
                        smh             = fopen(starmap_file, "w+");
                        sm_consolidated = 4;
                        fwrite(&sm_consolidated, 4, 1, smh);
                    }

                    if (smh != nullptr) {
                        fseek(smh, 4, SEEK_SET);

                        while (fread(comp_data, 1, 32, smh) == 32)
                            if (memcmp(comp_data, dummy_identity, 8)) {
                                if (!strcasecmp((char *) (comp_data + 8),
                                                (char *) planet_label)) {
                                    status("EXTANT", 50);
                                    prev_planet_id   = 12345;
                                    planet_label_pos = -1;
                                    fclose(smh);
                                    return;
                                }
                            }

                        fseek(smh, 0, SEEK_END);
                        planet_label_pos = fseek(smh, 0, SEEK_CUR);
                        fwrite(&planet_id, 1, 32, smh);
                        fclose(smh);
                        status("ASSIGNED", 50);
                        nearstar_labeled++;
                    } else {
                        status("INT. ERROR", 50);
                    }
                }
            } else {
                status("CONFLICT", 50);
            }

            break;

        case 3:
            targets_in_range = 1 - targets_in_range;

            if (targets_in_range) {
                targets             = 0;
                target_line         = 0;
                topmost_target      = 0;
                tgt_collect_lastpos = 4;
                collecting_targets  = 1;
                memset(&target_name[0], 32, 4 * 24);
                collect_targets();
                tgts_in_show = 0;
            }

            break;

        case 4: // target parsis
            manual_target = 1 - manual_target;

            if (manual_target) {
                mt_coord           = 0;
                mt_string_char     = 0;
                manual_x_string[0] = 0;
                status("TGT MANUAL", 100);
                ap_targetted = 0;
                stspeed      = 0;
            } else {
                status("TGT REJECT", 100);
            }

            break;

        default:
            break;
        }

        break;

    case 4:
        switch (s_command) {
        case 1: // reset onboard system
            reset_signal = 150;
            break;

        case 2: // help request
            if (pwr <= 15000 && !charge) {
                dist = fabs(dzat_x + dzat_y + dzat_z) * 0.0001;

                if (dist > 1800) {
                    dist = 1800;
                }

                fast_srand(clock());
                helptime = (flandom() * dist) + secs + 60;
                status("HELP REQ.", 50);
                gburst = 63;
            } else {
                status("ERROR", 50);
                gburst = -1;
            }

            break;

        case 3: // collect lithium
            if (!lithium_collector) {
                if (ap_reached && ap_targetted == 1) {
                    if (nearstar_class == 5 ||
                        (nearstar_class == 6 && nearstar_ray > 4)) {
                        lithium_collector = 1;
                    } else {
                        status("UNSUITABLE", 50);
                    }
                } else {
                    status("NEED RECAL", 75);
                }
            } else {
                lithium_collector = 0;
                status("IDLE", 50);
            }

            break;

        case 4: // clear status
            status("READY", 50);
            gburst = 0;
            break;
        default:
            break;
        }
    default:
        break;
    }
}

/* Preferences. */

void prefs() {
    if (autoscreenoff) {
        command(0, "auto screen sleep on");
    } else {
        command(0, "auto screen sleep off");
    }

    if (revcontrols) {
        command(1, "reverse pitch controls");
    } else {
        command(1, "normal pitch controls");
    }

    if (menusalwayson) {
        command(2, "menus always onscreen");
    } else {
        command(2, "auto-hidden menus");
    }

    if (depolarize) {
        command(3, "polarize");
    } else {
        command(3, "depolarize");
    }
}

/* Controls for setting preferential options. */

void toggle_option(int8_t *option_flag) {
    *option_flag = 1 - *option_flag;

    if (*option_flag) {
        status("ACQUIRED", 50);
    } else {
        status("DISABLED", 50);
    }
}

void pfs_commands() {
    switch (s_command) {
    case 1:
        toggle_option(&autoscreenoff);
        break;

    case 2:
        toggle_option(&revcontrols);
        break;

    case 3:
        toggle_option(&menusalwayson);
        break;

    case 4:
        toggle_option(&depolarize);
        break;
    default:
        break;
    }
}

/*  Commands given to the on-board computer.
 *  All except "disable screen". */

void commands() {
    switch (sys) {
    case 1:
        fcs_commands();
        break;

    case 2:
        dev_commands();
        break;

    case 3:
        pfs_commands();
        break;

    default:
        break;
    }
}

/*  Undo the situation, reproducing it in all respects,
     and making it evolve at the current time.
 *  Note: Garbage translation above
 *
 *  This loads the situation saved by freeze() */

void unfreeze() {
    double elapsed, dpwr;
    // Reading the consolidated starmap.
    FILE* smh = fopen(starmap_file, "r+");

    if (smh != nullptr) {
        fread(&sm_consolidated, 4, 1, smh);

        if (!sm_consolidated) {
            sm_consolidated = fseek(smh, 0, SEEK_END);
            fseek(smh, 0, SEEK_SET);
            fwrite(&sm_consolidated, 4, 1, smh);
        }

        fclose(smh);
    } else {
        sm_consolidated = 0;
    }

    /* Reading the previous situation */
    FILE *fh = fopen(situation_file, "r");

    if (fh == nullptr) {
        return;
    }

    fread(&nsync, 1, 1, fh);
    fread(&anti_rad, 1, 1, fh);
    fread(&pl_search, 1, 1, fh);
    fread(&field_amplificator, 1, 1, fh);
    fread(&ilight, 1, 1, fh);
    fread(&ilightv, 1, 1, fh);
    fread(&charge, 1, 1, fh);
    fread(&revcontrols, 1, 1, fh);
    fread(&ap_targetting, 1, 1, fh);
    fread(&ap_targetted, 1, 1, fh);
    fread(&ip_targetting, 1, 1, fh);
    fread(&ip_targetted, 1, 1, fh);
    fread(&ip_reaching, 1, 1, fh);
    fread(&ip_reached, 1, 1, fh);
    fread(&ap_target_spin, 1, 1, fh);
    fread(&ap_target_r, 1, 1, fh);
    fread(&ap_target_g, 1, 1, fh);
    fread(&ap_target_b, 1, 1, fh);
    fread(&nearstar_spin, 1, 1, fh);
    fread(&nearstar_r, 1, 1, fh);
    fread(&nearstar_g, 1, 1, fh);
    fread(&nearstar_b, 1, 1, fh);
    fread(&gburst, 1, 1, fh);
    fread(&menusalwayson, 1, 1, fh);
    fread(&depolarize, 1, 1, fh);
    fread(&sys, 1, 2, fh);
    fread(&pwr, 1, 2, fh);
    fread(&dev_page, 1, 2, fh);
    fread(&ap_target_class, 1, 2, fh);
    fread(&f_ray_elapsed, 1, 2, fh);
    fread(&nearstar_class, 1, 2, fh);
    fread(&nearstar_nop, 1, 2, fh);
    fread(&pos_x, 1, 4, fh);
    fread(&pos_y, 1, 4, fh);
    fread(&pos_z, 1, 4, fh);
    fread(&user_alfa, 1, 4, fh);
    fread(&user_beta, 1, 4, fh);
    fread(&navigation_beta, 1, 4, fh);
    fread(&ap_target_ray, 1, 4, fh);
    fread(&nearstar_ray, 1, 4, fh);
    fread(&dzat_x, 1, 8, fh);
    fread(&dzat_y, 1, 8, fh);
    fread(&dzat_z, 1, 8, fh);
    fread(&ap_target_x, 1, 8, fh);
    fread(&ap_target_y, 1, 8, fh);
    fread(&ap_target_z, 1, 8, fh);
    fread(&nearstar_x, 1, 8, fh);
    fread(&nearstar_y, 1, 8, fh);
    fread(&nearstar_z, 1, 8, fh);
    fread(&helptime, 1, 8, fh);
    fread(&ip_target_initial_d, 1, 8, fh);
    fread(&requested_approach_coefficient, 1, 8, fh);
    fread(&current_approach_coefficient, 1, 8, fh);
    fread(&reaction_time, 1, 8, fh);
    fread(&fcs_status, 1, 11, fh);
    fread(&fcs_status_delay, 1, 2, fh);
    fread(&psys, 1, 2, fh);
    fread(&ap_target_initial_d, 1, 8, fh);
    fread(&requested_vimana_coefficient, 1, 8, fh);
    fread(&current_vimana_coefficient, 1, 8, fh);
    fread(&vimana_reaction_time, 1, 8, fh);
    fread(&lithium_collector, 1, 1, fh);
    fread(&autoscreenoff, 1, 1, fh);
    fread(&ap_reached, 1, 1, fh);
    fread(&lifter, 1, 2, fh);
    fread(&secs, 1, 8, fh);
    fread(&data, 1, 1, fh);
    fread(&surlight, 1, 1, fh);
    fread(&gnc_pos, 1, 1, fh);
    fread(&goesfile_pos, 1, 4, fh);
    fread(goesnet_command, 1, 120, fh);

    fclose(fh);

    /* Resynchronization of the situation
     * 	in relation to previous events
     * 	(hidden evolution of the situation). */
    elapsed = secs;
    getsecs();
    elapsed = secs - elapsed;

    if ((helptime != 0.0) && (secs > (helptime + 20))) {
        helptime = 0;
        charge   = 4;
        gburst   = 0;
    }

    /* Reconstruction of the current star system. */
    npcs = -12345;
    prepare_nearstar();

    if (lithium_collector) {
        while (elapsed >= 30 && charge < 120) {
            elapsed -= 30;
            charge++;
        }

        if (charge == 120) {
            pwr = 20000;
        } else {
            brtl_srand((uint32_t)(secs));
            pwr = (int16_t)(brtl_random(5000) + 15000);
        }
    }

    /* Update on additional consumption. */
    dpwr = pwr;

    if (ilightv == 1) {
        dpwr -= elapsed / 84;
    }

    if (pl_search) {
        dpwr -= elapsed / 155;
    }

    if (field_amplificator) {
        dpwr -= elapsed / 41;
    }

    if (ip_targetted != -1 && ip_reached) {
        if (nsync == 1) { // fixed-point chase
            dpwr -= elapsed / 29;
        }

        if (nsync == 2) { // far chase
            dpwr -= elapsed / 18;
        }

        if (nsync == 3) { // syncrone orbit
            dpwr -= elapsed / 58;
        }

        if (nsync == 4) { // vimana orbit
            dpwr -= elapsed / 7;
        }

        if (nsync == 5) { // near chase
            dpwr -= elapsed / 33;
        }
    }

    while (dpwr < 15000) {
        if (charge) {
            dpwr += 5000;
            charge--;
        } else {
            dpwr = 15000;
        }
    }

    pwr = (int16_t) dpwr;
}

/* Main program. */

float starmass_correction[star_classes] = {
    1.886,   // Class 0
    1.50,    // Class 1
    8000.40, // Class 2
    0.05,    // Class 3
    2.44,    // Class 4
    3.10,    // Class 5
    9.30,    // Class 6
    48.00,   // Class 7
    1.00,    // Class 8
    1.00,    // Class 9
    0.07,    // Class 10
    15000.00 // Class 11
};

SDL_Surface *sdl_surface;
SDL_Window *window;
SDL_Renderer *renderer;

// Actual noctis stuff starts here.
float satur, DfCoS;

// float user_drawing_range;
int32_t ir, ig, ib, ire = 0, ige = 0, ibe = 0;
int32_t ir2, ig2, ib2, ir2e = 0, ig2e = 0, ib2e = 0;
int32_t ir3, ig3, ib3, ir3e = 0, ig3e = 0, ib3e = 0;
int16_t mc            = 0;
uint8_t p_mpul        = 0;
int8_t sky_palette_ok = 0;
int8_t lselect, rselect, lrv;
bool right_dblclick = false;
float right_dblclick_dir;
double dpz, ras, rap, dasp, eclipse;
double dxx, dyy, dzz, l_dsd, p_dsd, stz, ang;
static int16_t opencapcount = 0;
int16_t opencapdelta        = 0;
int16_t holdtomiddle        = 0;
int8_t leftturn, rightturn, arrowcolor, farstar = 0;
char temp_distance_buffer[16];
uint16_t pqw;
float hold_z;
float tmp_float;
int32_t p1, p2, p3, p4;

clock_t right_dblclick_timing = 0;

int16_t resolve = 64;

void loop();

int main(int argc, char **argv) {
    // Set up AngelScript
    as::init();
    as::register_functions();

    //This doesn't get check, but callback still exists for errors
    /*as_errorcode = testmod->Build();

    asIScriptFunction *as_func = testmod->GetFunctionByDecl("void main()");

    if (as_func == 0) {
        printf("The script is missing void main()\n");

        return 0;
    }

    asIScriptContext *as_context = as_engine->CreateContext();
    as_context->Prepare(as_func);

    as_errorcode = as_context->Execute();
    if (as_errorcode != asEXECUTION_FINISHED) {
        // The execution didn't complete as expected. Determine what happened.
        if(as_errorcode == asEXECUTION_EXCEPTION)
        {
            // An exception occurred, let the script writer know what happened so it can be corrected.
            printf("An AngelScript exception '%s' occurred. Please correct the code and try again.\n", as_context->GetExceptionString());
        }
    }*/

    // Initialize SDL.
    sdl_surface = SDL_CreateRGBSurface(0, 320, 200, 32, 0xFF000000, 0xFF0000,
                                       0xFF00, 0xFF);
    window = SDL_CreateWindow(
        "Noctis IV LR", SDL_WINDOWPOS_CENTERED, // NOLINT(hicpp-signed-bitwise)
        SDL_WINDOWPOS_CENTERED, 1280, 800,      // NOLINT(hicpp-signed-bitwise)
        SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

    // What does this do?
    for (ir = 0; ir < 200; ir++) {
        m200[ir] = ir * 200;
    }

    n_offsets_map = (uint8_t *) malloc(om_bytes);
    n_globes_map = (int8_t *) malloc((uint16_t) gl_bytes + (uint16_t) gl_brest);
    s_background = (uint8_t *) malloc(st_bytes);
    p_background = (uint8_t *) malloc(pl_bytes);
    /* NOTE: This is set to at least 65k because polymap keeps running over the
     * end. It happens in the original source too, and somehow isn't a problem
     * there, but we can't have it running over into random memory. The bug is
     * present in the original source.
     */
    p_surfacemap = (uint8_t *) malloc(ps_bytes | 65536);
    objectschart = (quadrant *) malloc(oc_bytes);
    ruinschart   = (uint8_t *) objectschart; // oc alias
    pvfile       = (uint8_t *) malloc(pv_bytes);
    adapted      = (uint8_t *) malloc(sc_bytes);
    txtr         = (uint8_t *) p_background;             // txtr alias
    digimap2     = (uint32_t *) &n_globes_map[gl_bytes]; // font alias

    argv0 = argv[0];

    if (pvfile && adapted && n_offsets_map && n_globes_map && p_background &&
        s_background && p_surfacemap && objectschart && lens_flares_init()) {
        lrv = loadpv(vehicle_handle, vehicle_ncc, 15, 15, 15, 0, 0, 0, 0, 1);

        if (lrv < 1) {
            printf("\nLoad error.\n");
            return 1;
        }

        load_QVRmaps();
        load_starface();
        load_digimap2();
    } else {
        /* NOTE: The 2nd line is not helpful on modern systems */
        printf("\nNot enough free conventional memory to run.");
        printf("\nType MEM and hit ENTER to check it out.");
        printf("\n550 KB are needed to run Noctis!\n");
        return 1;
    }


    unfreeze();
    memset(adapted, 0, QUADWORDS * 4);
    QUADWORDS -= 1440;
    pqw = QUADWORDS;
    handle_input();
    mpul = 0;
    dpp  = 210;
    change_camera_lens();
    //   0..64  Vehicle, computer selections, artifacts. Cobalt Blue, depending
    //   on the color from the star.
    //  64..128 cosmos, galactic background, clear skies and "suplucsi effect".
    //  from the white electric blue.
    // 128..192 Stars (Continuous cyclic shaders) or moons (non-constant)
    // 192..256 Planets (Non constant)
    tavola_colori(range8088, 0, 64, 16, 32, 63);
    tavola_colori(tmppal, 0, 256, 64, 64, 64);
    // causa il recupero dell'eventuale contenuto dello schermo
    // di output della GOES command net
    // causes the recovery of any screen content
    // GOES command net output
    force_update = 1;
    // recupero della situazione di superficie
    // recovery of the surface situation
    FILE* sfh = fopen(surface_file, "r");

    if (sfh != NULL) {
        // lettura precedenti coordinate di sbarco
        fread(&landing_pt_lon, 2, 1, sfh);
        fread(&landing_pt_lat, 2, 1, sfh);
        fclose(sfh);
        // recupero labels del pianeta e della stella-bersaglio
        update_star_label();
        update_planet_label();
        // risincronizzazione istantanea della posizione della navicella
        getsecs();
        planet_xyz(ip_targetted);
        dzat_x = plx;
        dzat_y = ply;
        dzat_z = plz;
        // calcolo della distanza dalla stella primaria
        dxx = dzat_x - nearstar_x;
        dyy = dzat_y - nearstar_y;
        dzz = dzat_z - nearstar_z;
        dsd = sqrt(dxx * dxx + dyy * dyy + dzz * dzz) + 1;
        // rielaborazione superficie planetaria
        from_vehicle();
        landing_point = 1;
        planets();
        landing_point = 0;
        // ripresa del ciclo di esplorazione planetaria
        entryflag = 1;
        planetary_main();
        // termine esplorazione
        opencapcount = 86;
        opencapdelta = -2;
        holdtomiddle = 1;
        pp_gravity   = 1;
        QUADWORDS    = 16000;
        memset(adapted, 0, QUADWORDS * 4);
        QUADWORDS = pqw;

        if (exitflag) {
            as::engine->ShutDownAndRelease();
            freeze();
        }
    }

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 24, 1);
#else
    do {
        loop();
    } while ((mc != 27) || stspeed || ip_reaching || lifter);
#endif
    remove(surface_file);

    freeze();
    as::engine->ShutDownAndRelease();
}

void swapBuffers() {
    SDL_RenderClear(renderer);
    auto dest = static_cast<uint32_t *>(sdl_surface->pixels);
    for (int i = 0; i < 64000; i++) {
        uint8_t color_index = adapted[i];
        uint32_t color_r    = currpal[color_index * 3] * 4;
        uint32_t color_g    = currpal[color_index * 3 + 1] * 4;
        uint32_t color_b    = currpal[color_index * 3 + 2] * 4;

        uint32_t color =
            (color_r << 24u) + (color_g << 16u) + (color_b << 8u) + 255;
        dest[i] = color;
    }
    // Palette display.
    /*for (int i = 0; i < 256; i++) {
        uint32_t color_r    = currpal[i * 3] * 4;
        uint32_t color_g    = currpal[i * 3 + 1] * 4;
        uint32_t color_b    = currpal[i * 3 + 2] * 4;

        uint32_t color = (color_r << 24u) + (color_g << 16u) + (color_b << 8u) +
    255;

        uint32_t line = 10 * (i / 32);
        uint32_t col = (i * 10) % 320;

        uint32_t base = line * 320 + col;
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                dest[base + j * 320 + k] = color;
            }
        }
    }*/

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, sdl_surface);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(texture);

    // Frame limiter (18 FPS)
    static const auto goal = std::chrono::milliseconds(FRAME_TIME_MILLIS);
    static auto last       = std::chrono::high_resolution_clock::now();

    auto now = std::chrono::high_resolution_clock::now();

    if ((now - last) < goal) {
        std::this_thread::sleep_for(goal - (now - last));
    }

    last = now;
}

void loop() {
    sync_start();
    //
    // Controllo del flag che indica quando ci si trova
    // sulla "terrazza panoramica", il tetto dello stardrifter.
    //
    pos_y += lifter;

    if (lifter > 0) {
        lifter--;

        if (lifter > 65) {
            user_alfa += 0.11 * (40 - user_alfa);
        } else {
            user_alfa -= 0.25 * user_alfa;
        }

        step = 0.5 * lifter;
    }

    if (lifter < 0) {
        lifter++;

        if (pos_y > -325) {
            user_alfa += 0.12 * (user_alfa - 40);
        }

        if (pos_y < -325 && pos_y > -715) {
            step = -pos_y;
        }
    }

    if (pos_y > 0) {
        lifter = 0;
        pos_y  = 0;
    }

    if (pos_y < -750) {
        lifter = 0;
        pos_y  = -750;
    }

    if (pos_y < -500) {
        ontheroof = 1;
    } else {
        ontheroof = 0;
    }

    if (!lifter && ontheroof) {
        DfCoS = pos_z + 3100;
        DfCoS = sqrt(pos_x * pos_x + DfCoS * DfCoS);

        if (DfCoS + step < 1100) {
            lifter = +75;
        }
    }

    //
    // Risposta al reset del sistema operativo di bordo.
    // La variabile "reset_signal" controlla la procedura
    // di reset, che reimposta tutti i parametri operativi
    // allo stato originario.
    //
    // Impostanto reset_signal a 150 si resetta tutto il sistema.
    // Impostanto reset_signal a 60 si resetta la rete GOES.
    //
    if (reset_signal) {
        switch (reset_signal) {
        case 150:
            elight  = 1;
            ilight  = 0;
            ilightv = 0;
            status("----------", 100);
            break;

        case 140:
            ip_targetted = -1;
            ip_reaching  = 0;
            break;

        case 130:
            ap_targetted = 0;
            stspeed      = 0;
            break;

        case 120:
            gburst             = 0;
            nsync              = 1;
            anti_rad           = 1;
            pl_search          = 0;
            field_amplificator = 0;
            break;

        case 115:
            sys  = 4;
            psys = 4;
            break;

        case 110:
            lithium_collector = 0;
            autoscreenoff     = 0;
            break;

        case 101:
            status("_^*^-!_$[]", 100);
            ap_reached    = 0;
            ip_reached    = 0;
            landing_point = 0;
            break;

        case 75:
            elight  = 0;
            ilightv = 1;
            break;

        case 55:
            mslocate(0, 0, 0);
            mswrite(0, "G.O.E.S. COMMAND NET:");
            break;

        case 35:
            mslocate(0, 0, 1);
            mswrite(0, "REVISION ID 6011/0200");
            break;

        case 25:
            mslocate(0, 0, 2);
            mswrite(0, "SESSION ID ");
            fast_srand((int32_t)(secs * 18));
            sprintf(temp_distance_buffer, "%05lu%05lu", fast_random(0x7FFF),
                    fast_random(0x7FFF));
            mswrite(0, temp_distance_buffer);
            break;

        case 10:
            status("STANDBY", 100);
            break;
        default:
            break;
        }

        reset_signal--;
    }

    //
    // Controlla il timer di sistema.
    //
    getsecs();

    //
    // Accensione luci d'emergenza.
    // Comportamento dell'astrozattera in mancanza di litio.
    //
    if (pwr <= 15000 && !charge) {
        elight             = 1;
        nsync              = 0;
        anti_rad           = 0;
        pl_search          = 0;
        field_amplificator = 0;
        ip_targetted       = -1;
        ap_reached         = 0;
        datasheetdelta     = -100;
    } else {
        if (elight && !reset_signal) {
            elight       = 0;
            ilight       = 0;
            ilightv      = 1;
            reset_signal = 200;
        }
    }

    // Mouse input for user movements.
    p_mpul = mpul;
    handle_input();

    // Dev Bryce: Mouse Currently only rotates camera
    /*if (mpul & 2u) {
        //shift += 3 * mdltx;
    //shift = mdlty;
        dlt_alfa -= (float)mdlty / 8;
    } else {
        //step -= 3 * mdlty;

        if (abs(mdlty) > 7) {
            dlt_alfa = -user_alfa / 6;
        }

        dlt_beta -= (float)mdltx / 3;
    }*/

    dlt_beta -= (float) mdltx / 3;
    dlt_alfa = (float) mdlty / 3;

    // Left-right Movement
    // shift = ;

    // Left-right Camera Rotation
    // dlt_beta;

    // Up-Down Camera Rotation (Does that make sense?)
    // dlt_alfa

    const int WASD_speed = 20;

    if ((active_screen != 0) && ((labstar == 0) && (labplanet == 0))) {
        // +X / -X Direction
        int8_t x_dir = ((int8_t) key_move_dir.right) - ((int8_t) key_move_dir.left);
        // +Z / -Z Direction
        int8_t z_dir = ((int8_t) key_move_dir.forward) - ((int8_t) key_move_dir.backward);

        if (x_dir || z_dir) {
            step += z_dir * WASD_speed;
            shift += x_dir * WASD_speed;
        }
    }

    // Mouse input for double left and right click.
    if (ontheroof) {
        goto nop;
    }

    if ((mpul & 1u) && !(p_mpul & 1u)) {
        lselect = 1;
    } else {
        lselect = 0;
    }

    if ((mpul & 2u) && !(p_mpul & 2u) && !right_dblclick) {
        if (!right_dblclick_timing) {
            right_dblclick_timing = clock();
            rselect = 1;
        } else {
            if (clock() - right_dblclick_timing < DBL_CLICK_CUTOFF) {
                right_dblclick     = true;
                right_dblclick_dir = user_beta;
            } else {
                right_dblclick_timing = clock();
                rselect = 1;
            }
        }
    } else {
        rselect = 0;
    }

    // Disable double clicking while a screen is selected to fix a few weird
    // quirks.
    right_dblclick = (right_dblclick && (active_screen == -1));

    if (right_dblclick) {
        if (ap_targetting) {
            ap_targetting  = 0;
            right_dblclick = false;
            extract_ap_target_infos();
            fix_remote_target();
            goto nop;
        }

        if (ip_targetting) {
            ip_targetting  = 0;
            right_dblclick = false;

            if (ip_targetted != -1) {
                fix_local_target();
            } else {
                status("NO TARGET", 50);
            }

            goto nop;
        }

        if (!holdtomiddle) {
            float xx, zz;
            if (right_dblclick_dir > -135 && right_dblclick_dir < -45) {
                user_beta += 90;
                user_beta /= 1.5;
                xx = pos_x - 2900;
                pos_x -= xx * 0.25;

                if (landing_point) {
                    zz = pos_z + 104 * 15 + 1980;
                } else {
                    zz = pos_z + 1940;
                }

                pos_z -= zz * 0.25;

                if (fabs(xx) < 25 && fabs(zz) < 25 && fabs(user_beta) < 1) {
                    right_dblclick_timing = 0;
                    right_dblclick        = false;
                }

                user_beta -= 90;
            } else {
                user_beta /= 1.5;
                zz = pos_z + 500;
                pos_z -= zz * 0.25;

                if (sys != 4) {
                    if (fabs(zz) < 25 && fabs(user_beta) < 1) {
                        right_dblclick_timing = 0;
                        right_dblclick        = false;
                    }
                } else {
                    xx = pos_x + 1700;
                    pos_x -= xx * 0.25;

                    if (fabs(zz) < 25 && fabs(xx) < 25 && fabs(user_beta) < 1) {
                        right_dblclick_timing = 0;
                        right_dblclick        = false;
                    }
                }
            }
        }
    }

//
// Variazione angoli visivi.
// (Visual angle variation)
//
nop:
    user_alfa += dlt_alfa;
    dlt_alfa /= 1.5;

    if (fabs(dlt_alfa) < 0.25) {
        dlt_alfa = 0;
    }

    if (user_alfa < -44.9) {
        user_alfa = -44.9;
        dlt_alfa  = 0;
    }

    if (user_alfa > 44.9) {
        user_alfa = 44.9;
        dlt_alfa  = 0;
    }

    user_beta += dlt_beta;
    dlt_beta /= 1.5;

    if (fabs(dlt_beta) < 0.25) {
        dlt_beta = 0;
    }

    if (user_beta > 180) {
        user_beta -= 360;
    }

    if (user_beta < -180) {
        user_beta += 360;
    }

    // Variation of the user's position in the spacecraft.
    alfa = user_alfa;
    beta = user_beta - 90;
    change_angle_of_view();
    p_forward(shift);
    beta = user_beta;
    change_angle_of_view();
    p_forward(step);
    shift /= 1.5;

    if (fabs(shift) < 0.5) {
        shift = 0;
    }

    step /= 1.25;

    if (fabs(step) < 0.5) {
        step = 0;
    }

    if (pos_x < -3100) {
        pos_x = -3100;
    }

    if (pos_x > +3100) {
        pos_x = +3100;
    }

    if (pos_z > -300) {
        pos_z = -300;
    }

    if (pos_z < -5800) {
        pos_z = -5800;
    }

    // Black background, which will be made hazy.
    if (!stspeed) {
        memset(adapted + 2880, 0, QUADWORDS * 4);
    } else {
        pfade(adapted, 180, 8);
    }

    // Close star management
    from_vehicle();
    dxx   = dzat_x - nearstar_x;
    dyy   = dzat_y - nearstar_y;
    dzz   = dzat_z - nearstar_z;
    l_dsd = sqrt(dxx * dxx + dyy * dyy + dzz * dzz) + 1;
    satur = (12 * dsd) / nearstar_ray;
    fast_srand((int32_t) nearstar_z);
    ir = fast_random(31) + 29;

    if (satur < ir) {
        satur = ir;
    }

    if (satur > 63) {
        satur = 63;
    }

    //
    if (l_dsd < 100 * nearstar_ray)
        white_globe(adapted, nearstar_x, nearstar_y, nearstar_z,
                    3 * nearstar_ray, 0.3);

    for (ir = 0; ir < nearstar_nop; ir++) {
        if (nearstar_p_type[ir] == 10) {
            planet_xyz(ir);
            p_dsd = nearstar_p_qsortdist[ir];
            fast_srand((int32_t)(ir + nearstar_x));
            white_globe(adapted, plx, ply, plz, 3 * nearstar_p_ray[ir],
                        0.15 - fast_flandom() * 0.3);

            if (p_dsd > 5 * nearstar_p_ray[ir] &&
                p_dsd < 1000 * nearstar_p_ray[ir])
                lens_flares_for(dzat_x, dzat_y, dzat_z, plx, ply, plz,
                                (10 * nearstar_p_ray[ir]) / p_dsd,
                                (int16_t)(1 + (0.001 * p_dsd)), 1, 0, 3, 0);
        }
    }

    if (l_dsd > 6 * nearstar_ray) {
        if (nearstar_class != 5 && nearstar_class != 6 &&
            nearstar_class != 10) {
            if (nearstar_class != 11 || gl_start < 90) {
                if (l_dsd > 5 * nearstar_ray && l_dsd < 1000 * nearstar_ray) {
                    lens_flares_for(dzat_x, dzat_y, dzat_z, nearstar_x,
                                    nearstar_y, nearstar_z,
                                    (10 * nearstar_ray) / l_dsd,
                                    (int16_t)(1 + (0.001 * l_dsd)), 1, 0, 3, 0);
                }
            }
        }

        psmooth_grays(adapted + 2880);
    }

    mask_pixels(adapted + 2880, 64);

    if (l_dsd < 8 * nearstar_ray) {
        if (farstar) {
            farstar = 0;
            load_starface();
        }

        glass_bubble = 0;

        if (nearstar_spin) {
            gl_start += nearstar_spin;
            gl_start %= 360;
            globe(gl_start, adapted, s_background, (uint8_t *) n_globes_map,
                  gl_bytes, nearstar_x, nearstar_y, nearstar_z, nearstar_ray,
                  64, (int8_t) satur);
        } else {
            globe((clock() / 360) % 360, adapted, s_background,
                  (uint8_t *) n_globes_map, gl_bytes, nearstar_x, nearstar_y,
                  nearstar_z, nearstar_ray, 64, (int8_t) satur);
        }
    } else {
        farstar = 1;
    }

    //
    if (l_dsd > 100 * nearstar_ray && l_dsd < 1550 * nearstar_ray) {
        ir = (int32_t)(((1600 * nearstar_ray) - l_dsd) / (100 * nearstar_ray));

        if (ir < 0) {
            ir = 0;
        }

        ir += 0x30;
        far_pixel_at(nearstar_x, nearstar_y, nearstar_z, 0, ir);
        far_pixel_at(nearstar_x, nearstar_y, nearstar_z, 0, ir);
        far_pixel_at(nearstar_x, nearstar_y, nearstar_z, 0, ir);
    }

    //
    // Riflessi del protagonista sulla vetrata (rimossi).
    /*
        if (!stspeed) {
        if (ilight) {
            from_user ();
            if (cam_z>-1000) {
                if (alfa>-10&&alfa<10)
                    user_drawing_range = 55;
                else
                    user_drawing_range = 70;
            }
            else
                user_drawing_range = 40;
            if (beta>-user_drawing_range&&beta<user_drawing_range) {
                cam_x = -4*beta;
                cam_y = 10*alfa;
                cam_z = 0;
                Forward (2*pos_z);
                alfa *= 2; beta *= 2;
                change_angle_of_view ();
                flares = 2;
                user ();
                flares = 0;
            }
        }
        }
    */
    // Controllo gestore (indicando i comandi con lo sguardo).
    //
    from_user();
    leftturn  = 0;
    rightturn = 0;
    infoarea  = 0;
    s_control = 0;
    s_command = 0;

    if (ontheroof) {
        goto jpr;
    }

    float xx, zz;
    do {
        zz = fabs(cam_z);
        xx = fabs(cam_x);
        forward(zz / 2);
    } while (zz > 25 && xx < 3000);

    if (zz < 25) {
        if (cam_x < -44 * 30) {
            if (cam_x > -68 * 30) {
                s_control = (int16_t)((cam_y + 25) / 50 + 3);

                if (s_control < 1) {
                    s_control = 1;
                }

                if (s_control > 4) {
                    s_control = 4;
                }

                if (lselect) {
                    if (!ap_targetting && !ip_targetting) {
                        aso_countdown = 100;
                        sys           = s_control;
                        dev_page      = 0;
                    }
                }
            }
        } else {
            if (cam_y < -50) {
                if (cam_x < 68 * 30) {
                    s_command = (int16_t)((cam_x + 44 * 30) / (27 * 30) + 1);

                    if (s_command < 1) {
                        s_command = 1;
                    }

                    if (s_command > 4) {
                        s_command = 4;
                    }

                    if (lselect) {
                        if (!ap_targetting && !ip_targetting) {
                            aso_countdown = 100;
                            commands();
                            goto jpr;
                        }
                    }
                }
            } else {
                infoarea = 1;
            }
        }
    }

    if (lselect && pwr > 15000) {
        if (revcontrols) {
            if (cam_x > 2500) {
                dlt_nav_beta += 1.5;
                status("PITCH - R", 25);
            }

            if (cam_x < -2500) {
                dlt_nav_beta -= 1.5;
                status("PITCH - L", 25);
            }
        } else {
            if (cam_x > 2500) {
                dlt_nav_beta -= 1.5;
                status("PITCH - L", 25);
            }

            if (cam_x < -2500) {
                dlt_nav_beta += 1.5;
                status("PITCH - R", 25);
            }
        }
    }

    if (cam_x > 2500) {
        rightturn = 1;
    }

    if (cam_x < -2500) {
        leftturn = 1;
    }

//
// Rotazione della navicella.
// Attivazione schermi.
//
jpr:

    if (!elight) {
        // Paratia destra:
        if (user_beta > -135 && user_beta < -45 && pos_z < -104 * 15 &&
            pos_z > -262 * 15 && pos_x > 172 * 15) {
            if (rselect) {
                if (active_screen == -1) {
                    active_screen = (int8_t)((pos_z + 104 * 15) / (-54 * 15));
                    status("SELECTED", 50);
                } else {
                    active_screen = -1;
                    status("DESELECTED", 50);
                }
            }
        } else {
            active_screen = -1;
        }

        // Paratia sinistra:
        // if (user_beta > +45 && user_beta < +135 && pos_z < -104*15 &&
        // pos_z > -154*15 && pos_x < -172*15) active_screen = (pos_z +
        // 104*15) / (-54*15) + 2;
    }

    navigation_beta += dlt_nav_beta;
    dlt_nav_beta /= 1.1;

    if (fabs(dlt_nav_beta) < 0.5) {
        dlt_nav_beta = 0;
    }

    if (navigation_beta >= 360) {
        navigation_beta -= 360;
    }

    if (navigation_beta < 0) {
        navigation_beta += 360;
    }

    // Planet tracking
    from_vehicle();
    planets();

    // Controlling help requests.
    if ((helptime != 0) && secs > helptime) {
        if (gburst) {
            status("HELP CAME!", 50);
            gburst = 0;
        }

        if (secs < helptime + 120) {
            stz = 0;

            if (secs < helptime + 20) {
                stz = pow(helptime + 20 - secs, 2) * 2000;
            }

            if (secs > helptime + 100) {
                stz = pow(helptime + 100 - secs, 2) * 2000;
            }

            if ((stz == 0) && charge < 3) {
                charge = 3;
            }

            other_vehicle_at((stz + 16000) * cos(secs / 10),
                             4000 * sin(secs / 100),
                             (stz + 16000) * sin(secs / 10));
        } else {
            helptime = 0;
        }
    }

    //
    // Tracciamento della navicella.
    //
    from_user();
    vehicle(opencapcount);

    //
    // Tracciamento riflessi, aggiornamento dello schermo
    // del gestore, tracciamento dello schermo del gestore,
    // reazione visiva agli eventi interni alla navicella.
    //
    if (ontheroof) {
        goto ext_1;
    }

    from_user();

    if (!opencapcount) {
        reflexes();
    }

    if (!(clock() % 10)) {
        clear_onboard_screen();
        control(0, "flight control drive");
        control(1, "onboard devices");
        control(2, "preferences");
        control(3, "disable display");

        switch (sys) {
        case 1:
            control(0, "FLIGHT CONTROL DRIVE");

            if (sys != psys) {
                status("FCS MENU", 50);
            }

            fcs();
            break;

        case 2:
            control(1, "ONBOARD DEVICES");

            if (sys != psys) {
                status("SELECT SUB", 50);
            }

            devices();
            break;

        case 3:
            control(2, "PREFERENCES");

            if (sys != psys) {
                status("PREFS MENU", 50);
            }

            prefs();
            break;

        case 4:
            control(3, "DISABLE DISPLAY");

            if (sys != psys) {
                status("SCREEN OFF", 50);
            }
            break;
        default:
            break;
        }

        psys = sys;
    }

    if (!ap_targetting && !ip_targetting) {
        setfx(4);
        dxx = pos_z / 88;

        if (dxx < -16) {
            dxx = -16;
        }

        entity = (uint8_t) dxx;
        screen();
        setfx(0);
    }

    if (leftturn) {
        arrowcolor = 127 - 16 * (clock() % 4);
        digit_at('-', -2900, -50, 12, arrowcolor, 0);

        if (revcontrols) {
            digit_at('>', -3000, -50, 12, arrowcolor, 0);
        } else {
            digit_at('<', -3000, -50, 12, arrowcolor, 0);
        }
    }

    if (rightturn) {
        arrowcolor = 127 - 16 * (clock() % 4);
        digit_at('-', +2900, -50, 12, arrowcolor, 0);

        if (revcontrols) {
            digit_at('<', +3000, -50, 12, arrowcolor, 0);
        } else {
            digit_at('>', +3000, -50, 12, arrowcolor, 0);
        }
    }

    //
    // ***** H.U.D. OUTER LAYER *****
    // Fornisce informazioni sullo strato esterno dell'H.U.D.
    // Qualsiasi glifo verr� in seguito trattato con dithering.
    //
    if (active_screen != -1) {
        goto nohud_1;
    }

    /* Additional information and diagrams on the H.U.D. , label tracking of
     * selected star, and distance tracking from selected star.
     */
    if (ap_targetting || ap_targetted) {
        alfa = 0;
        beta = 0;
        change_angle_of_view();
        cam_x = 450;
        cam_y = 250;
        cam_z = -750;

        for (mc = 0; mc < 24; mc++) {
            if (labstar && mc == labstar_char) {
                digit_at('_', -6, -15, 5, 127 - 2 * (clock() % 32), 0);
            }

            digit_at(star_label[mc], -6, -15, 5, 127, 1);
            cam_x -= 40;
        }

        dxx   = dzat_x - ap_target_x;
        dyy   = dzat_y - ap_target_y;
        dzz   = dzat_z - ap_target_z;
        l_dsd = sqrt(dxx * dxx + dyy * dyy + dzz * dzz) * 5E-5;

        if (ap_reached && ap_target_id == nearstar_identity) {
            l_dsd *= 0.01;
        }

        sprintf(temp_distance_buffer, "%01.2f", l_dsd);
        cam_x = 450;
        cam_y = -180;
        cam_z = -750;
        mc    = 0;

        while (temp_distance_buffer[mc] != 0) {
            digit_at(temp_distance_buffer[mc], -6, -15, 5, 127, 1);
            cam_x -= 40;
            mc++;
        }

        cam_x -= 40;
        digit_at('L', -6, -15, 5, 112, 1);
        cam_x -= 40;
        digit_at('.', -6, -15, 5, 112, 1);
        cam_x -= 40;
        digit_at('Y', -6, -15, 5, 112, 1);
        cam_x -= 40;
        digit_at('.', -6, -15, 5, 112, 1);
    }

    //
    // Tracciamento label del pianeta selezionato,
    // tracciamento distanza dal pianeta selezionato,
    // aggiornamento nome del pianeta-bersaglio.
    //
    if (ip_targetted != -1) {
        update_planet_label();
        alfa = 0;
        beta = 0;
        change_angle_of_view();
        cam_x = 450;
        cam_y = 180;
        cam_z = -750;

        for (mc = 0; mc < 24; mc++) {
            if (labplanet && mc == labplanet_char) {
                digit_at('_', -6, -15, 5, 127 - 2 * (clock() % 32), 0);
            }

            digit_at(planet_label[mc], -6, -15, 5, 112, 1);
            cam_x -= 40;
        }

        planet_xyz(ip_targetted);
        dxx   = dzat_x - plx;
        dyy   = dzat_y - ply;
        dzz   = dzat_z - plz;
        l_dsd = sqrt(dxx * dxx + dyy * dyy + dzz * dzz) * 1E-2;
        sprintf(temp_distance_buffer, "%01.2f", l_dsd);
        cam_x = 450;
        cam_y = -250;
        cam_z = -750;
        mc    = 0;

        while (temp_distance_buffer[mc] != 0) {
            digit_at(temp_distance_buffer[mc], -6, -15, 5, 120, 1);
            cam_x -= 40;
            mc++;
        }

        cam_x -= 40;
        digit_at('D', -6, -15, 5, 105, 1);
        cam_x -= 40;
        digit_at('Y', -6, -15, 5, 105, 1);
        cam_x -= 40;
        digit_at('A', -6, -15, 5, 105, 1);
        cam_x -= 40;
        digit_at('M', -6, -15, 5, 105, 1);
        cam_x -= 40;
        digit_at('S', -6, -15, 5, 105, 1);
    }

    //
    // Messaggio di reset, lampeggiante.
    //
    if (reset_signal && (reset_signal % 10) < 5) {
        alfa = 0;
        beta = 0;
        change_angle_of_view();
        cam_x = 300;
        cam_y = 0;
        cam_z = -750;
        mc    = 0;

        while (sr_message[mc] != 0) {
            digit_at(sr_message[mc], -6, -15, 8, 127, 1);
            cam_x -= 60;
            mc++;
        }
    }

//
// Tracing the current FCS status.
//
nohud_1:
    alfa = 0;
    beta = 0;
    change_angle_of_view();
    cam_x = -512;
    cam_y = -275;
    cam_z = -750;
    mc    = strlen(fcs_status) - 1;

    while (mc >= 0) {
        digit_at(fcs_status[mc], -6, -15, 6, 120, 1);
        cam_x += 45;
        mc--;
    }

    //
    // Link alla funzione di ricerca dei targets in real-time.
    //
    if (collecting_targets) {
        status("SCANNING..", 100);
        collect_targets();

        if (!collecting_targets) {
            if (targets) {
                status("DONE!", 100);
            } else {
                status("NO TARGETS", 100);
            }
        }
    }

    //
    // Display / update table "targets in range".
    //
    if (targets_in_range) {
        if (update_targets) {
            tgts_in_show = 0;
            mc           = topmost_target;

            while (targets && mc < targets && tgts_in_show < 3) {
                tgt_label_pos = search_id_code(targets_table_id[mc], 'S');

                if (tgt_label_pos > -1) {
                    FILE* smh = fopen(starmap_file, "r");

                    if (smh != nullptr) {
                        fseek(smh, tgt_label_pos + 8, SEEK_SET);
                        fread(&target_name[tgts_in_show], 1, 24, smh);
                        fclose(smh);
                        tgts_in_show++;
                    }
                }

                mc++;
            }

            update_targets = 0;
        }

        cam_x = 175;
        cam_y = 40;
        cam_z = -500;
        frame(225, 48, 285, 96, 2, 90);
        cam_y = 8 + 40;
        mc    = 0;

        while (mc < tgts_in_show) {
            cam_x = 35 + 175;

            if (mc == target_line) {
                frame(226 + 35, 0, 277, 30, 1, 120);
            }

            for (ir = 0; ir < 24; ir++) {
                digit_at(target_name[mc][ir], -5, -10, 3.5, 174, 1);
                cam_x -= 23;
            }

            cam_y -= 55;
            mc++;
        }
    }

ext_1: //
    // Anti-aliasing e dithering (error-diffusion).
    // E` un procedimento molto peculiare, che fornisce effetti
    // straordinariamente belli su uno schermo che, di per s�,
    // � poco risolutivo, sia fisicamente che cromaticamente.
    //
    QUADWORDS -= 240;
    psmooth_64(adapted, 200);
    psmooth_64(adapted, 200);
    QUADWORDS += 240;
    //
    // Tracking of all visible stars.
    //
    from_vehicle();
    sky(0x405C);

    //
    // ***** H.U.D. INNER LAYER *****
    // Provides information on the inner layer of the HUD.
    // Any glyph will not be treated with dithering.
    //
    if (datasheetscroll) {
        area_clear(adapted, 11, 85, 0, 0, 1 + datasheetscroll, 9, 72);
        area_clear(adapted, 11, 95, 0, 0, 1 + datasheetscroll, 40, 112);
        mc = (datasheetscroll / 4) - 1;

        if (mc > 0) {
            switch (data) {
            case 1: // remote target data
                if (ap_targetted) {
                    if (ap_targetted == 1) {
                        wrouthud(14, 87, mc, (char *) star_label);
                        tmp_float = 1e-3 * qt_M_PI * ap_target_ray *
                                    ap_target_ray * ap_target_ray;
                        tmp_float *= starmass_correction[ap_target_class];

                        if (nearstar_class == 8 || nearstar_class == 9) {
                            fast_srand((int32_t) ap_target_x % 32000);

                            switch (fast_random(5)) {
                            case 0:
                                tmp_float /= 1 + 5 * fast_flandom();
                                break;

                            case 1:
                                tmp_float /= 1 + fast_flandom();
                                break;

                            case 2:
                                tmp_float *= 1 + fast_flandom();
                                break;

                            case 3:
                                tmp_float *= 1 + 20 * fast_flandom();
                                break;

                            case 4:
                                tmp_float *= 1 + 50 * fast_flandom();
                            }
                        }

                        wrouthud(14, 97, mc, "PRIMARY MASS:");
                        sprintf((char *) outhudbuffer, "%1.8f BAL. M.",
                                tmp_float);
                        wrouthud(14, 103, mc, (char *) outhudbuffer);
                        tmp_float /= 0.38e-4 * ap_target_ray;

                        if (ap_target_class == 6) {
                            tmp_float *= 0.0022;
                        }

                        wrouthud(14, 113, mc, "SURFACE TEMPERATURE:");
                        sprintf((char *) outhudbuffer,
                                "%1.0f@K&%1.0f@C&%1.0f@F", tmp_float + 273.15,
                                tmp_float, tmp_float * 1.8 + 32);
                        wrouthud(14, 119, mc, (char *) outhudbuffer);
                        sprintf((char *) outhudbuffer, "MAJOR BODIES: %d EST.",
                                starnop(ap_target_x, ap_target_y, ap_target_z));
                        wrouthud(14, 129, mc, (char *) outhudbuffer);
                    } else {
                        wrouthud(14, 87, mc, "DIRECT PARSIS TARGET");
                    }
                } else {
                    wrouthud(14, 87, mc, "REMOTE TARGET NOT SET");
                }

                break;

            case 2: // local intarget data
                if (ip_targetted != -1) {
                    wrouthud(14, 87, mc, (char *) planet_label);
                    wrouthud(14, 97, mc, "PERIOD OF ROTATION:");

                    if (nearstar_p_qsortindex[nearstar_nob - 1] ==
                        ip_targetted) {
                        if (nearstar_p_rtperiod[ip_targetted] > 0) {
                            p1 = nearstar_p_rtperiod[ip_targetted];
                            p1 *= 360;
                            p2 = p1 / 1000;
                            p2 /= 1000;
                            p3 = p1 / 1000;
                            p3 %= 1000;
                            p4 = p1 % 1000;
                            sprintf((char *) outhudbuffer,
                                    "TRIADS %03d:%03d:%03d", p2, p3, p4);
                            wrouthud(14, 103, mc, (char *) outhudbuffer);
                        } else {
                            if (ip_reaching || ip_reached) {
                                if (nearstar_p_type[ip_targetted] != 10) {
                                    wrouthud(14, 103, mc, "COMPUTING...");
                                } else {
                                    wrouthud(14, 103, mc, "NOT RESOLVABLE");
                                }
                            } else {
                                wrouthud(14, 103, mc, "TOO FAR TO ESTIMATE");
                            }
                        }
                    } else {
                        wrouthud(14, 103, mc, "TOO FAR TO ESTIMATE");
                    }

                    wrouthud(14, 113, mc, "PERIOD OF REVOLUTION:");
                    tmp_float = rtp(ip_targetted);
                    p1        = (int32_t)(tmp_float * 1e-9);
                    p2        = (int32_t)(tmp_float * 1e-6);
                    p2 %= 1000;
                    p3 = (int32_t)(tmp_float * 1e-3);
                    p3 %= 1000;
                    p4 = (int32_t)(tmp_float) % 1000;

                    if (p1 < 2) {
                        sprintf((char *) outhudbuffer,
                                "%d EPOCS, %03d:%03d:%03d", p1, p2, p3, p4);
                    } else {
                        if (p1 < 2047) {
                            sprintf((char *) outhudbuffer,
                                    "%d EPOCS, %03d:%03d:???", p1, p2, p3);
                        } else {
                            sprintf((char *) outhudbuffer,
                                    "%d EPOCS, %03d:???:???", p1, p2);
                        }
                    }

                    wrouthud(14, 119, mc, (char *) outhudbuffer);
                } else {
                    wrouthud(14, 87, 21, "LOCAL TARGET NOT SET");
                }

                break;

            case 3: // environment data
                wrouthud(14, 87, mc, "EXTERNAL ENVIRONMENT");
                fast_srand((int32_t)(secs / 2));
                tmp_float = 16 - dsd * 0.044;
                tmp_float *= fabs(tmp_float);
                tmp_float -= (tmp_float + 273.15) * eclipse;

                if (tmp_float < -269) {
                    tmp_float = fast_flandom() - 269;
                }

                sprintf((char *) outhudbuffer, "TEMP. %1.2f@K",
                        tmp_float + 273.15);
                wrouthud(14, 97, mc, (char *) outhudbuffer);
                sprintf((char *) outhudbuffer, "      %1.2f@C", tmp_float);
                wrouthud(14, 103, mc, (char *) outhudbuffer);
                sprintf((char *) outhudbuffer, "      %1.2f@F",
                        tmp_float * 1.8 + 32);
                wrouthud(14, 109, mc, (char *) outhudbuffer);
                brtl_srand((uint16_t) nearstar_identity);

                if (nearstar_class == 6 || nearstar_class == 5) {
                    ir = brtl_random(50);
                    if (nearstar_class == 5) {
                        ir -= (int32_t)(125 / dsd);

                        if (ir <= 0) {
                            ir = 1;
                        }
                    } else {
                        ir -= (int32_t)(25 / dsd);
                    }
                } else {
                    ir = 0;
                }

                sprintf((char *) outhudbuffer, "LI+ IONS: %d MTPD EST.", ir);
                wrouthud(14, 119, mc, (char *) outhudbuffer);

                tmp_float = 50 + (brtl_random(10)) - (brtl_random(10));

                tmp_float *= (1 - eclipse);
                tmp_float *= 100 / dsd;

                if (nearstar_class == 11) {
                    if (gl_start < 90) {
                        tmp_float *= 75 + brtl_random(50);
                    } else {
                        tmp_float *= 50;
                    }
                }

                if (nearstar_class == 10) {
                    tmp_float *= 0.25;
                }

                if (nearstar_class == 9) {
                    tmp_float *= 3;
                }

                if (nearstar_class == 8) {
                    tmp_float *= 1.5;
                }

                if (nearstar_class == 7) {
                    tmp_float *= 25;
                }

                if (nearstar_class == 6) {
                    tmp_float *= 0.01;
                }

                if (nearstar_class == 5) {
                    tmp_float *= 0.1;
                }

                if (nearstar_class == 4) {
                    tmp_float *= 10;
                }

                if (nearstar_class == 3) {
                    tmp_float *= 0.5;
                }

                if (nearstar_class == 2) {
                    tmp_float *= 18;
                }

                if (nearstar_class == 1) {
                    tmp_float *= 5;
                }

                brtl_srand((uint16_t) secs);
                tmp_float *= 1 + (float) (brtl_random(100)) * 0.001 -
                             (float) (brtl_random(100)) * 0.001;
                sprintf((char *) outhudbuffer, "RADIATION: %1.1f KR",
                        tmp_float);
                wrouthud(14, 126, mc, (char *) outhudbuffer);
                break;
            default:
                break;
            }
        }
    }

    datasheetscroll += datasheetdelta;

    if (datasheetscroll > 100) {
        datasheetscroll = 100;
    }

    if (datasheetscroll < 0) {
        datasheetscroll = 0;
        data            = 0;
    }

    // Draw planetary targeting cross.
    if ((ip_targetted != -1 && !ip_reached) || ip_targetting) {
        planet_xyz(ip_targetted);

        if (far_pixel_at(plx, ply, plz, 0, 1)) {
            uint16_t index = vptr - 640;

            for (int16_t i = 0; i < 4; i++) {
                int16_t voffset = (i > 1) ? 320 : 1;
                int16_t signmod = (i % 2 == 0) ? -1 : 1;

                for (int16_t j = 4; j < 8; j++) {
                    adapted[index + signmod * voffset * j] = 126;
                }
            }
        }
    }

    //
    // Star-Target pointing cross, update star-target name, shift interstellar
    // (suplucsi?)
    //
    dxx   = dzat_x - ap_target_x;
    dyy   = dzat_y - ap_target_y;
    dzz   = dzat_z - ap_target_z;
    l_dsd = sqrt(dxx * dxx + dyy * dyy + dzz * dzz);

    if (ap_targetting || l_dsd > 10000) {
        pointer_cross_for(ap_target_x, ap_target_y, ap_target_z);
    }

    if (ap_targetting || ap_targetted) {
        update_star_label();

        if (stspeed == 1) {
            if (ap_targetted == -1) {
                ras = 25000;
            } else {
                if (anti_rad) {
                    ras = 44 * ap_target_ray;
                } else {
                    ras = 1.5 * ap_target_ray;
                }

                if (l_dsd < 20000 && nsnp) {
                    prepare_nearstar();
                    nsnp = 0;
                }
            }

            if (l_dsd < ras) {
                status("CALIBRATED", 50);
                ap_reached = 1;
                stspeed    = 0;
            } else {
                if (l_dsd > 0.9999 * ap_target_initial_d) {
                    requested_vimana_coefficient = 0.001 * l_dsd;
                    status("CHARGING", 0);
                    vimana_reaction_time = 0.1;
                    goto ap_drive_mode;
                }

                if (l_dsd < 7500 + ras) {
                    requested_vimana_coefficient = 0.005 * l_dsd;
                    status("PARKING", 0);
                    vimana_reaction_time = 0.01;
                    goto ap_drive_mode;
                }

                if (l_dsd < 15000 + ras) {
                    requested_vimana_coefficient = 0.005 * l_dsd;
                    status("LINKING", 0);
                    vimana_reaction_time = 0.0025;
                    goto ap_drive_mode;
                }

                if (l_dsd < 0.9990 * ap_target_initial_d) {
                    requested_vimana_coefficient = 0.00001 * l_dsd;
                    status("DRIVING", 0);
                    vimana_reaction_time = 0.05;
                    goto ap_drive_mode;
                }

                requested_vimana_coefficient = 0.0002 * l_dsd;
                status("IGNITION", 0);

                if (vimana_reaction_time != 0.08) {
                    vimana_reaction_time = 0.08;
                }

            ap_drive_mode:
                current_vimana_coefficient += (requested_vimana_coefficient -
                                               current_vimana_coefficient) *
                                              vimana_reaction_time;

                if (current_vimana_coefficient < 10) {
                    current_vimana_coefficient = 10;
                }

                dzat_x -= dxx / current_vimana_coefficient;
                dzat_y -= dyy / current_vimana_coefficient;
                dzat_z -= dzz / current_vimana_coefficient;
                pwr -= (int16_t)(l_dsd * 1E-5);
            }
        }
    }

//
// Sincronizzazione della navicella con i moti planetari,
// spostamenti interplanetari suplucsi.
//
resynctoplanet:

    if (ip_targetted != -1 && pwr > 15000) {
        planet_xyz(ip_targetted);
        dxx = dzat_x - plx;
        dyy = dzat_y - ply;
        dzz = dzat_z - plz;

        if (ip_reached && nsync) {
            status("TRACKING", 0);

            if (nsync == 1) { // fixed-point chase
                ang    = (double) deg * (double) navigation_beta;
                hold_z = 1.8;
            }

            if (nsync == 2) { // far chase
                ang    = (double) deg * (double) navigation_beta;
                hold_z = 5.4;
            }

            if (nsync == 3) { // syncrone orbit
                ang = (double) nearstar_p_rotation[ip_targetted] * (double) deg;
                hold_z = 1.8 + 0.1 * nearstar_p_ray[ip_targetted];
            }

            if (nsync == 4) { // vimana orbit
                ang    = 7 * secs * (double) deg;
                hold_z = 3.6;
            }

            if (nsync == 5) { // near chase
                ang    = (double) deg * (double) navigation_beta;
                hold_z = 1.2;
            }

            dxx += hold_z * nearstar_p_ray[ip_targetted] * sin(ang);
            dzz -= hold_z * nearstar_p_ray[ip_targetted] * cos(ang);

            if (_delay < 5) {
                dzat_x -= dxx * 0.05;
                dzat_y -= dyy * 0.05;
                dzat_z -= dzz * 0.05;
            } else {
                dzat_x -= dxx;
                dzat_y -= dyy;
                dzat_z -= dzz;
            }
        }

        if (ip_reaching) {
            l_dsd = sqrt(dxx * dxx + dyy * dyy + dzz * dzz);

            if (l_dsd > 0.99999 * ip_target_initial_d) {
                requested_approach_coefficient = 25 * l_dsd;
                status("WARMING UP", 0);
                reaction_time = 0.001;
                goto ip_drive_mode;
            }

            if (l_dsd < 25 && ip_target_initial_d > 500) {
                requested_approach_coefficient = 50 * l_dsd;
                status("REFINING", 0);
                reaction_time = 0.0002;
                goto ip_drive_mode;
            }

            if (l_dsd < 100 && ip_target_initial_d > 500) {
                requested_approach_coefficient = 15 * l_dsd;
                status("BREAKING", 0);
                reaction_time = 0.0003;
                goto ip_drive_mode;
            }

            if (l_dsd < 0.99500 * ip_target_initial_d) {
                requested_approach_coefficient = 0.05 * l_dsd;
                status("APPROACH", 0);
                reaction_time = 0.025;
                goto ip_drive_mode;
            }

            requested_approach_coefficient = 1.5 * l_dsd;
            status("IGNITION", 0);
            reaction_time = 0.05;
        ip_drive_mode:
            current_approach_coefficient += (requested_approach_coefficient -
                                             current_approach_coefficient) *
                                            reaction_time;

            if (current_approach_coefficient < 10) {
                current_approach_coefficient = 10;
            }

            dzat_x -= dxx / current_approach_coefficient;
            dzat_z -= dzz / current_approach_coefficient;
            dzat_y -= dyy / (0.5 * current_approach_coefficient);
            pwr -= (int16_t)(l_dsd * 0.5E-5);

            if (l_dsd < 2 * nearstar_p_ray[ip_targetted]) {
                status("STANDBY", 0);
                ip_reaching = 0;
                ip_reached  = 1;
            }
        }
    }

    //
    // Gestione del consumo di litio.
    // Consumi supplementari, gestione ricariche.
    //
    additional_consumes();
    //
    // Calcolo della distanza dalla stella pi� vicina,
    // per il controllo su radiazioni, eclissi, temperatura.
    //
    dxx = dzat_x - nearstar_x;
    dyy = dzat_y - nearstar_y;
    dzz = dzat_z - nearstar_z;
    dsd = sqrt(dxx * dxx + dyy * dyy + dzz * dzz) + 1;

    //
    // Allontanamento d'emergenza della navicella dalla stella.
    //
    if (dsd < (0.44 + (double) (2 * anti_rad)) * nearstar_ray) {
        status("CORRECTION", 100);
        dzat_x += (dxx / dsd) * 0.1;
        dzat_y += (dyy / dsd) * 0.1;
        dzat_z += (dzz / dsd) * 0.1;
    }

    //
    // Manovre di approvvigionamento litio dallo spazio
    // attorno alle stelle di classe 5 o a certe di classe 6.
    // Le stelle di classe 6 sono pi� difficili da sfruttare,
    // ma danno i migliori risultati. Quelle di classe 5 sono
    // sempre adatte, ma con scarsi risultati.
    //
    if (lithium_collector) {
        brtl_srand((uint16_t) nearstar_identity);
        ir = brtl_random(50);

        if (nearstar_class == 5) {
            ir -= (int32_t)(125 / dsd);

            if (ir <= 0) {
                ir = 1;
            }
        } else {
            ir -= (int32_t)(25 / dsd);
        }

        if (ir > 0) {
            if (pwr >= 20000 && charge >= 120) {
                status("! FULL !", 100);
                lithium_collector = 0;
            } else {
                pwr += ir;

                if (pwr >= 20000) {
                    if (charge < 120) {
                        pwr = 15001;
                        charge++;
                    } else {
                        pwr = 20000;
                    }
                }

                status("SCOPING...", 25);
            }
        } else {
            status("GET CLOSER", 100);

            if (!reset_signal) {
                lithium_collector = 0;
            }
        }
    }

    // Eclipse control.
    stz = dzz * cos(deg * navigation_beta) - dxx * sin(deg * navigation_beta) -
          fabs(dyy) / 2;

    if (stz > dsd) {
        stz = dsd;
    }

    if (stz < 0) {
        stz = 0;
    }

    stz /= 1.25;
    ras = (105 * nearstar_ray) / dsd;

    if (ras > 66) {
        ras = 66;
    }

    if (ras < 1) {
        ras = 1;
    }

    eclipse = 0;

    for (mc = 0; mc < nearstar_nob; mc++) {
        if (nearstar_p_type[mc] != -1) {
            planet_xyz(mc);
            dxx = dzat_x - plx;
            dyy = dzat_y - ply;
            dzz = dzat_z - plz;
            dpz = sqrt(dxx * dxx + dyy * dyy + dzz * dzz) + 0.001;

            if (dpz < 10 * nearstar_p_ray[mc]) {
                watch(dzat_x, dzat_y, dzat_z, nearstar_x, nearstar_y,
                      nearstar_z);
                change_angle_of_view();

                if (xy(dzat_x, dzat_y, dzat_z, plx, ply, plz)) {
                    dasp = sqrt(delta_x * delta_x + delta_y * delta_y);
                    rap  = (105 * nearstar_p_ray[mc]) / dpz;

                    if (rap > 66) {
                        rap = 66;
                    }

                    eclipse = (dasp + ras - rap) / (2 * ras);

                    if (eclipse > 1) {
                        eclipse = 1;
                    }

                    if (eclipse < 0) {
                        eclipse = 0;
                    }

                    eclipse = 1 - eclipse;
                }
            }
        }
    }

    //
    // Reactions to eclipses (obscure the color of the spacecraft).
    // Also lower the internal temperature by a little, but not
    // too much because it is contrasted by air conditioning.
    //
    fast_srand((int32_t)(secs / 2));
    pp_temp = 90 - dsd * 0.33;
    pp_temp -= 44;
    pp_temp *= fabs(pp_temp * 0.44);
    pp_temp -= (pp_temp + 273.15) * eclipse;

    if (pp_temp < -269) {
        pp_temp = fast_flandom() - 269;
    }

    if (!ontheroof) {
        if (pp_temp < 0) {
            pp_temp = 0;
        }

        if (pp_temp > 40) {
            pp_temp = 40;
        }

        while (pp_temp < 14) {
            pp_temp += fast_flandom() * 2.5;
        }

        while (pp_temp > 32) {
            pp_temp -= fast_flandom() * 2.5;
        }

        l_dsd = (24 * nearstar_ray) / (dsd - stz);
        l_dsd -= l_dsd * eclipse;
        pp_temp += l_dsd;

        if (pp_temp > 40) {
            pp_temp = 40;
        }

        while (pp_temp > 38) {
            pp_temp -= fast_flandom() * 2.5;
        }

        pp_pressure = 1;
    } else {
        pp_pressure = 0;
    }

    //
    ilight += ilightv;

    if (ilight < 0) {
        ilight = 0;
    }

    if (ilight > 63) {
        ilight = 63;
    }

    l_dsd = (15 * nearstar_ray * nearstar_r) / (dsd - stz);
    l_dsd -= l_dsd * eclipse;

    if (elight) {
        ir3 = (int32_t)(ilight + 30 - clock() % 30 + l_dsd);
    } else {
        ir3 = (int32_t)(ilight / 4.0 + l_dsd);
    }

    if (ir3 > nearstar_r + 16) {
        ir3 = nearstar_r + 16;
    }

    if (nearstar_class == 11 && gl_start < 90) {
        ir = 5 * ir3;
    }

    if (ir3 > 63) {
        ir3 = 63;
    }

    l_dsd = (7 * nearstar_ray * nearstar_g) / (dsd - stz);
    l_dsd -= l_dsd * eclipse;

    if (elight) {
        ig3 = (int32_t)((ilight + 30 - clock() % 30) / 2.0 + l_dsd);
    } else {
        ig3 = (int32_t)(ilight / 2.0 + l_dsd);
    }

    if (ig3 > nearstar_g + 32) {
        ig3 = nearstar_g + 32;
    }

    if (nearstar_class == 11 && gl_start < 90) {
        ig3 = 5 * ig3;
    }

    if (ig3 > 63) {
        ig3 = 63;
    }

    l_dsd = (7 * nearstar_ray * nearstar_b) / (dsd - stz);
    l_dsd -= l_dsd * eclipse;

    if (elight) {
        ib3 = (int32_t)((ilight + 30 - clock() % 30) / 4.0 + l_dsd);
    } else {
        ib3 = (int32_t)(ilight + l_dsd);
    }

    if (nearstar_class == 11 && gl_start < 90) {
        ib3 = 5 * ib3;
    }

    if (ib3 > 63) {
        ib3 = 63;
    }

    if (gburst > 0 && gburst < 5) {
        ir3 += 8 * gburst;
        ig3 += 8 * gburst;
        ib3 += 8 * gburst;
    }

    if (ir3 != ir3e || ig3 != ig3e || ib3 != ib3e) {
        tavola_colori(range8088, 0, 64, ir3, ig3, ib3);
        ir3e = ir3;
        ig3e = ig3;
        ib3e = ib3;
    }

    //
    // Controllo del flag di richiesta di atterraggio.
    //
    if (land_now) {
        land_now       = 0;
        landing_point  = 0;
        holdtomiddle   = 1;
        opencapdelta   = 2;
        right_dblclick = false;
        status("UNLOCKING", 50);
    }

    //
    // Avanzamento contatore per le richieste d'aiuto.
    //
    if (gburst > 0) {
        gburst--;

        if (!gburst) {
            gburst = 63;
            status("SIGNAL", 50);
        }
    }

    //
    // Countdown per il delay dei messaggi di stato dell'FCS.
    //
    if (fcs_status_delay) {
        fcs_status_delay--;
    }

    //
    // Countdown per il delay della funzione auto-sleep.
    //
    if (autoscreenoff) {
        aso_countdown--;

        if (aso_countdown <= 0) {
            aso_countdown = 100;
            sys           = 4;
        }
    }

    //
    // Il protagonista sta sempre in una tutina... � normale.
    // Vede le cose attraverso uno scafandro, non ingombrante
    // ma pur sempre uno scafandro. La funzione "surrounding"
    // disegna i bordi dello scafandro, illuminati in relazione
    // all'ambiente circostante.
    //
    surrounding(0, 180);
    // riduzione stanchezza (continua, eventualmente
    // dall'ultima volta che si � scesi in superficie)
    // e variazioni nelle pulsazioni, pi� verosimili...
    fast_srand((int32_t)(secs / 2));
    tiredness *= 0.9977;
    pp_pulse = (1 + tiredness) * 118;
    pp_pulse += fast_flandom() * 8;
    pp_pulse -= fast_flandom() * 8;

    // se si sta per scendere o si � appena risaliti,
    // si deve trattenere il player nel mezzo della navicella,
    // in quanto si suppone che sia bloccato nella capsula.
    if (holdtomiddle || lifter) {
        pos_x *= 0.75;
        hold_z = pos_z + 3100;
        pos_z -= hold_z * 0.25;
    }

    // effetto di apertura della capsula:
    // quando � totalmente aperta, si pu� scendere.
    // LQ significa Last Quadrant (ultimo quadrante visitato)
    if (opencapdelta < 0) {
        opencapcount += opencapdelta;

        if (opencapcount <= 0) {
            opencapdelta = 0;
            holdtomiddle = 0;
            sprintf(temp_distance_buffer, "LQ %03d:%03d", landing_pt_lon,
                    landing_pt_lat);
            status(temp_distance_buffer, 100);
        }
    }

    // effetto di chiusura della capsula:
    // quando � totalmente sigillata, scotty beam me down.
    // al ritorno, comincia a riaprire la capsula...
    if (opencapdelta > 0) {
        opencapcount += opencapdelta;

        if (opencapcount >= 85) {
            entryflag = 0;
            planetary_main();

            if (exitflag) {
                exit(0);
            }

            opencapdelta = -2;
            holdtomiddle = 1;
            pp_gravity   = 1;
            resolve      = 0;
            _delay       = 13; // solo al ritorno da superficie
            goto resynctoplanet;
        }
    }

    // Page swap.
    QUADWORDS = 16000;

    if (_delay == 13) {
        _delay = 0;
    }

    if (!_delay) {
        swapBuffers();
    } else if (_delay > 0 && _delay < 10) {
        _delay--;
    }

    QUADWORDS = pqw;

    if (resolve == 1) {
        while (resolve <= 63) {
            tavola_colori((uint8_t *) return_palette, 0, 256, resolve, resolve,
                          resolve);
            ir = clock();

            while (ir == clock())
                ;

            resolve += 4;
        }
    }

    if (resolve == 0) {
        resolve = 1;
    }

    //
    // This section controls the pixels in a continuous loop
    // depicting the convective currents inside the stars,
    // but goes into action only if the star is close enough,
    // otherwise you can not see a white globe: The colors
    // of the stars are not really colors, but only soft
    // nuances; in practice, being almost all well beyond the
    // saturation level of the eye, the stars appear generally
    // all white, unless you approach them really very much.
    //
    if (dsd < 1000 * nearstar_ray) {
        ir = nearstar_r;
        ig = nearstar_g;
        ib = nearstar_b;
        mc = nearstar_class;

        if (mc == 8) {
            fast_srand((int32_t) nearstar_identity);
            brtl_srand(fast_random(0x7FFF));
            mc = brtl_random(star_classes);
            ir = class_rgb[mc * 3 + 0];
            ig = class_rgb[mc * 3 + 1];
            ib = class_rgb[mc * 3 + 2];
        }

        switch (mc) {
        case 0:
            ir2 = 64;
            ig2 = 54;
            ib2 = 28;
            break;

        case 1:
            ir2 = 36;
            ig2 = 50;
            ib2 = 64;
            break;

        case 2:
            ir2 = 24;
            ig2 = 32;
            ib2 = 48;
            break;

        case 3:
            ir2 = 64;
            ig2 = 24;
            ib2 = 12;
            break;

        case 4:
            ir2 = 64;
            ig2 = 40;
            ib2 = 32;
            break;

        case 5:
            ir2 = 28;
            ig2 = 20;
            ib2 = 12;
            break;

        case 6:
            ir2 = 32;
            ig2 = 32;
            ib2 = 32;
            break;

        case 7:
            ir2 = 32;
            ig2 = 44;
            ib2 = 64;
            break;

        case 8:
            ir2 = 64;
            ig2 = 60;
            ib2 = 32;
            break;

        case 9:
            fast_srand((int32_t) nearstar_identity);
            ir2 = 32 + fast_random(31);
            ig2 = 32 + fast_random(31);
            ib2 = 16 + fast_random(31);
            break;

        case 10:
            ir2 = 32;
            ig2 = 26;
            ib2 = 22;
            break;

        case 11:
            ir2 = 36;
            ig2 = 48;
            ib2 = 64;
            break;
        default:
            break;
        }

        satur = (6.4 * dsd) / nearstar_ray;

        if (satur > 44) {
            satur = 44;
        }

        if (ir < satur) {
            ir = (int32_t) satur;
        }

        if (ig < satur) {
            ig = (int32_t) satur;
        }

        if (ib < satur) {
            ib = (int32_t) satur;
        }

        if (ir2 < satur) {
            ir2 = (int32_t) satur;
        }

        if (ig2 < satur) {
            ig2 = (int32_t) satur;
        }

        if (ib2 < satur) {
            ib2 = (int32_t) satur;
        }
    } else {
        ir  = 48;
        ig  = 56;
        ib  = 64;
        ir2 = 24;
        ig2 = 32;
        ib2 = 40;
    }

    if (ire == ir && ige == ig && ibe == ib && ir2e == ir2 && ig2e == ig2 &&
        ib2e == ib2) {
        if (!sky_palette_ok) {
            sky_palette_ok = 1;
            goto last_sky_palette_redefinition;
        }
    } else {
        sky_palette_ok = 0;
    last_sky_palette_redefinition:

        if (ire < ir) {
            ire++;
        }

        if (ire > ir) {
            ire--;
        }

        if (ige < ig) {
            ige++;
        }

        if (ige > ig) {
            ige--;
        }

        if (ibe < ib) {
            ibe++;
        }

        if (ibe > ib) {
            ibe--;
        }

        if (ir2e < ir2) {
            ir2e++;
        }

        if (ir2e > ir2) {
            ir2e--;
        }

        if (ig2e < ig2) {
            ig2e++;
        }

        if (ig2e > ig2) {
            ig2e--;
        }

        if (ib2e < ib2) {
            ib2e++;
        }

        if (ib2e > ib2) {
            ib2e--;
        }

        shade(tmppal, 64 + 00, 24, 0, 0, 0, ir2e, ig2e, ib2e);
        shade(tmppal, 64 + 24, 16, ir2e, ig2e, ib2e, ire, ige, ibe);
        shade(tmppal, 64 + 40, 24, ire, ige, ibe, 64, 70, 76);
        tavola_colori(tmppal + 3 * 64, 64, 64, 63, 63, 63);
    }

    if (!farstar) {
        for (ir = 0; ir < 64800; ir++) {
            ig               = (s_background[ir] + 1) % 64;
            ib               = ((uint8_t)(s_background[ir] >> 6u)) << 6u;
            s_background[ir] = ig + ib;
        }
    }

    //
    sync_stop();

    /* Hook for managing the motion characteristics of planet surface features
     *
     */
    if (ip_targetted != -1 && ip_reached) {
        if ((int32_t) secs % 300 == 0) {
            npcs = -12345;
        }
    }

    /* Keyboard input: Taking snapshots, ending the game session, selecting
     * targets, attributing labels, etc.
     */
    if (ontheroof) {
        if (is_key()) {
            mc = get_key();

            if (mc == '*') {
                snapshot(0, 1);
            }
        } else {
            mc = 0;
        }

        goto endmain;
    }

    if (goesk_e != -1) {
        mc      = goesk_e;
        goesk_e = -1;
        goto goesk_e_reentry;
    }

    if (goesk_a != -1) {
        mc      = goesk_a;
        goesk_a = -1;
        goto goesk_a_reentry;
    }

    if (active_screen == -1 && is_key()) {
        while (is_key()) {
            mc = get_key();

            if (!mc) {
                mc = get_key();
            goesk_e_reentry:

                if (targets_in_range) {
                    if (mc == 80) {
                        if (target_line < 2) {
                            if (topmost_target + target_line < targets - 1) {
                                target_line++;
                            }
                        } else {
                            if (topmost_target < targets - 3) {
                                topmost_target++;
                                update_targets = 1;
                            }
                        }
                    }

                    if (mc == 72) {
                        if (target_line > 0) {
                            target_line--;
                        } else {
                            if (topmost_target > 0) {
                                topmost_target--;
                                update_targets = 1;
                            }
                        }
                    }

                    goto endmain;
                }

                if (mc == 75) {
                    dlt_nav_beta += 1.5;
                    status("PITCH - R", 25);
                }

                if (mc == 77) {
                    dlt_nav_beta -= 1.5;
                    status("PITCH - L", 25);
                }

                if (mc == 72) {
                    lifter = -100;
                }
            } else {
            goesk_a_reentry:

                if (mc == '*') {
                    snapshot(0, 1);
                    goto endmain;
                }

                if (data) {
                    if (mc == 27) {
                        mc             = 0;
                        datasheetdelta = -2;
                        goto endmain;
                    }
                }

                if (ap_targetting) {
                    if (mc == 27) {
                        mc            = 0;
                        ap_targetting = 0;
                        ap_targetted  = 0;
                        status("CANCELLED", 50);
                        goto endmain;
                    }
                }

                if (labstar) {
                    if (mc == 27) {
                        mc               = 0;
                        labstar          = 0;
                        ap_target_previd = -1;
                        goto endmain;
                    }

                    if (mc >= 32 && mc <= 126 && labstar_char < 20) {
                        if (mc >= 'a' && mc <= 'z') {
                            mc -= 32;
                        }

                        star_label[labstar_char] = mc;
                        labstar_char++;
                    }

                    if (mc == 8 && labstar_char > 0) {
                        labstar_char--;
                        star_label[labstar_char] = 32;
                    }

                    if (mc == 13) {
                        dev_page  = 3;
                        s_command = 1;
                        dev_commands();
                    }

                    goto endmain;
                }

                if (labplanet) {
                    if (mc == 27) {
                        mc             = 0;
                        labplanet      = 0;
                        prev_planet_id = -1;
                        goto endmain;
                    }

                    if (mc >= 32 && mc <= 126 && labplanet_char < 20) {
                        if (mc >= 'a' && mc <= 'z') {
                            mc -= 32;
                        }

                        planet_label[labplanet_char] = mc;
                        labplanet_char++;
                    }

                    if (mc == 8 && labplanet_char > 0) {
                        labplanet_char--;
                        planet_label[labplanet_char] = 32;
                    }

                    if (mc == 13) {
                        dev_page  = 3;
                        s_command = 2;
                        dev_commands();
                    }

                    goto endmain;
                }

                if (targets_in_range) {
                    if (mc == 27) {
                        mc               = 0;
                        targets_in_range = 0;
                        goto endmain;
                    }

                    if (mc == 13) {
                        if (!collecting_targets &&
                            topmost_target + target_line < targets) {
                            ap_target_x =
                                targets_table_px[topmost_target + target_line];
                            ap_target_y =
                                targets_table_py[topmost_target + target_line];
                            ap_target_z =
                                targets_table_pz[topmost_target + target_line];
                            extract_ap_target_infos();
                            fix_remote_target();
                        }

                        goto endmain;
                    }
                }

                if (ip_targetting) {
                    if (mc == 27) {
                        mc            = 0;
                        ip_targetted  = -1;
                        ip_targetting = 0;
                        status("CANCELLED", 50);
                        goto endmain;
                    }

                    if (mc == 8 && iptargetchar > 0) {
                        iptargetchar--;
                        iptargetstring[iptargetchar] = 0;
                        status((char *) iptargetstring, 100);
                    }

                    if (((mc >= '0' && mc <= '9') || mc == '/') &&
                        iptargetchar < 10) {
                        if (mc == '/') {
                            if (iptargetchar == 0) {
                                goto endmain;
                            }

                            ir = 0;

                            while (ir < iptargetchar) {
                                if (iptargetstring[ir] == '/') {
                                    goto endmain;
                                }

                                ir++;
                            }
                        }

                        iptargetstring[iptargetchar]     = mc;
                        iptargetstring[iptargetchar + 1] = 0;
                        iptargetchar++;
                        status((char *) iptargetstring, 100);
                    }

                    if (mc == 13) {
                        if (iptargetchar == 0) {
                            goto endmain;
                        }

                        ir = 0;

                        while (ir < iptargetchar) {
                            if (iptargetstring[ir] == '/') {
                                iptargetstring[ir] = 0;
                                iptargetmoon = atoi((char *) iptargetstring);
                                iptargetstring[ir] = '/';

                                if (iptargetstring[ir + 1] != 0) {
                                    iptargetplanet =
                                        atoi((char *) iptargetstring + ir + 1);
                                    goto searchmoon;
                                }

                                status("NOT EXTANT", 100);
                                goto endmain;
                            }

                            ir++;
                        }

                        iptargetplanet = atoi((char *) iptargetstring);

                        if (iptargetplanet != 0 &&
                            iptargetplanet <= nearstar_nop) {
                            ip_targetted = iptargetplanet - 1;
                            fix_local_target();
                            ip_targetting = 0;
                        }

                        status("NOT EXTANT", 100);
                        goto endmain;
                    searchmoon:
                        ir = 0;

                        while (ir < nearstar_nob) {
                            if (nearstar_p_owner[ir] == iptargetplanet - 1 &&
                                nearstar_p_moonid[ir] == iptargetmoon - 1) {
                                ip_targetted = ir;
                                fix_local_target();
                                ip_targetting = 0;
                                goto endmain;
                            }

                            ir++;
                        }

                        status("NOT EXTANT", 100);
                    }

                    goto endmain;
                }

                if (manual_target) {
                    if (mc == 27) {
                        mc            = 0;
                        manual_target = 0;
                        ap_targetted  = 0;
                        status("CANCELLED", 50);
                        goto endmain;
                    }

                    if (mc == 8 && mt_string_char > 0) {
                        mt_string_char--;

                        switch (mt_coord) {
                        case 0:
                            manual_x_string[mt_string_char] = 0;
                            break;

                        case 1:
                            manual_y_string[mt_string_char] = 0;
                            break;

                        case 2:
                            manual_z_string[mt_string_char] = 0;
                            break;
                        default:
                            break;
                        }
                    }

                    if ((mc >= '0' && mc <= '9' && mt_string_char < 10) ||
                        (mc == '-' && mt_string_char == 0)) {
                        switch (mt_coord) {
                        case 0:
                            manual_x_string[mt_string_char]     = mc;
                            manual_x_string[mt_string_char + 1] = 0;
                            break;

                        case 1:
                            manual_y_string[mt_string_char]     = mc;
                            manual_y_string[mt_string_char + 1] = 0;
                            break;

                        case 2:
                            manual_z_string[mt_string_char]     = mc;
                            manual_z_string[mt_string_char + 1] = 0;
                            break;
                        default:
                            break;
                        }

                        mt_string_char++;
                    }

                    if (mc == 13) {
                        switch (mt_coord) {
                        case 0:
                            ap_target_x        = atol((char *) manual_x_string);
                            manual_y_string[0] = 0;
                            break;

                        case 1:
                            ap_target_y = -atol((char *) manual_y_string);
                            manual_z_string[0] = 0;
                            break;

                        case 2:
                            ap_target_z = atol((char *) manual_z_string);
                            break;
                        default:
                            break;
                        }

                        mt_string_char = 0;
                        mt_coord++;

                        if (mt_coord > 2) {
                            manual_target = 0;
                            fix_remote_target();
                            ap_targetted = -1;
                        }
                    }

                    switch (mt_coord) {
                    case 0:
                        sprintf(temp_distance_buffer, "%s", manual_x_string);
                        break;

                    case 1:
                        sprintf(temp_distance_buffer, "%s", manual_y_string);
                        break;

                    case 2:
                        sprintf(temp_distance_buffer, "%s", manual_z_string);
                        break;
                    default:
                        break;
                    }

                    if (mt_coord <= 2) {
                        status(temp_distance_buffer, 100);
                    }

                    goto endmain;
                }

                if (!ap_targetting && !ip_targetting) {
                    aso_countdown = 100;

                    switch (mc) {
                    case '5':
                        sys      = 1;
                        dev_page = 0;
                        break;

                    case 'r':
                        sys      = 2;
                        dev_page = 0;
                        break;

                    case 'p':
                        sys      = 3;
                        dev_page = 0;
                        break;

                    case 'x':
                        sys      = 4;
                        dev_page = 0;
                        break;

                    case '6':
                        s_command = 1;
                        commands();
                        break;

                    case '7':
                        s_command = 2;
                        commands();
                        break;

                    case '8':
                        s_command = 3;
                        commands();
                        break;

                    case '9':
                        s_command = 4;
                        commands();
                        break;
                    default:
                        break;
                    }
                }

                if (mc == '+' && surlight < 63) {
                    surlight++;
                }

                if (mc == '-' && surlight > 10) {
                    surlight--;
                }
            }

        endmain:
            uint8_t argblarg = 5;
        }
    } else {
        mc = 0;
    }
}
