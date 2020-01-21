/*

    The Third Flare.
    ----------------
    Full-3D Graphic Engine.

    32-bit functions to draw 3D polygons filled with color
    in 320x200x256 graphics. On the Pentium is a cannon shot:
    an average of 12,000 polygons per second, from workstations, with 75MHz

    - You should never use the color 255 to trace something
    in the work area, when using this routine, because only
    you use it to delimit the polygons. If you want to use another
    color to delimit them, you need to change all the 255 values in
    the "segment" and "poly3d" functions.


    Call initscanlines() before tracing anything, otherwise things will break.

    Born (incredible to say) for Alpha Dream
    Last revised December 21st 1997.

    Additions:
        3d-2d conversion optimization, 23.6.1997;

        fast-load cycle of the vertices when they
        are all in front of the camera
        (that is almost always), 23.6.1997;

        intelligent clipping, October '97;

        texture mapping, February '98.
*/

#include <cmath>
#include <cstdio>

#include <memory.h>

#include "noctis-d.h"

/*

    Display control.

*/

float uneg = 100;
/* A particularly curious fact: uneg represents the minimum distance
 * at which a certain point is not considered behind the observer.
 *
 * The nice thing is that the conception of this acronym (recalling u-neg)
 * goes back to so long ago (we talk about the first version of Smallest,
 * that is April '92, currently more than 5 years ago) that I don't remember
 * at all what this acronym means (it was an acronym, but who knows
 * how it came to find, perhaps from user-neg, negative to the user,
 * with reference to the reversal effect of the sign given by the
 * perspective functions when, precisely, a triplet of coordinates
 * has the normal distance from the screen in negative,
 * but I'm not sure at all. */

float alfa = 0, beta = 0, ngamma = 0;
float cam_x = 0, cam_y = 0, cam_z = 0;

const double deg = M_PI / 180;

// Distance from the projection plane.

float dpp = 200;

/* Texture mapping constants and control variables.
 * H_MATRIXS and V_MATRIXS specify the repetitions of the same
 * texture on the polygons, but in order to have the possibility
 * of halving the texture or drawing only a quarter, they have
 * been assumed as representing "quarters of texture". It means
 * that to have a normal texturing, without repeitions halved,
 * it is necessary to assign the two variables to 4, not to 1
 * (which would represent a single quarter). And so on...
 * if you put 8, you get the repetition of the texture twice
 * on the corresponding axis, if you set to 12, you get three
 * repetitions, etc.
 * (ps, I changed the base to 16, texture sixteenths). */

const uint16_t MPIY = 199; // Maximum PIXEL on Y.

float EMU_K       = 16;                         // Cost of FPU emulation
int32_t H_MATRIXS = 16;                         // Number of repetitions. 16-128
int32_t V_MATRIXS = 16;                         // Number of repetitions. 16-128
int32_t XSIZE     = TEXTURE_X_SIZE * H_MATRIXS; // Calibrate dimensions.
int32_t YSIZE     = TEXTURE_Y_SIZE * V_MATRIXS; // Calibrate dimensions.
float XCOEFF      = EMU_K / dpp;                // Coefficient of convenience.
float YCOEFF      = EMU_K / dpp;                // Coefficient of convenience.

// Draw a segment without checking limits. Faster.
// Trace with color 255.
// It does not carry out checks, so it should not be used for other things,
// or at least you have to be careful to include the extremes of the
// segment in the usable video area.
// The one doing the checks is in the waveline function of
// Liquid Player, and it is safe at 1000 per thousand.

uint16_t ptr;

void segment(int32_t xp, int32_t yp, int32_t xa, int32_t ya) {
    int32_t a, b, L;
    uint32_t pi, pf;
    bool flip = false;

    if (xp == xa) {
        if (ya >= yp) {
            pi = 320 * yp + xp;
            pf = 320 * (ya + 1);
        } else {
            pi = 320 * ya + xp;
            pf = 320 * (yp + 1);
        }

        while (pi < pf) {
            adapted[pi] = 255;
            pi += 320;
        }

        return;
    }

    pi = abs(xa - xp);
    if (xa < xp) {
        uint32_t swap;

        swap = xp;
        xp   = xa;
        xa   = swap;

        swap = yp;
        yp   = ya;
        ya   = swap;
    }

    a = pi;
    L = pi;

    // Account for steep lines.
    b = abs(ya - yp);
    if (ya < yp) {
        flip = true;
    }

    if (b >= L) {
        L = b;
    }

    L++;
    xa = ((uint32_t) xa) << 16u;

    uint32_t global_x = ((uint32_t) xp) << 16u;
    uint32_t global_y = ((uint32_t) yp) << 16u;

    a = ((uint32_t) a) << 16u;
    b = ((uint32_t) b) << 16u;

    a /= L;
    b /= L;

    if (flip)
        b = -b;

    while (global_x < xa) {
        uint16_t line = (global_y >> 16u);
        uint16_t col  = (global_x >> 16u);

        global_x += a;
        global_y += b;

        adapted[320 * line + col] = 255;
    }
}

// La funzione di tracciamento viene principalmente usata da Noctis,
// ed una delle sue caratteristiche � di poter fare poligoni semitrasparenti
// che simulano degli aloni luminosi: si attiva con il flag "flares".
// Perch� il disegno dei bordi (dei segmenti) non interferisca con tale
// operazione, serve una pagina sana, priva di bordi, diversa da quella su
// cui si va a tracciare.
// Per default, � la seguente, posta a nulla perch� tdpolygs non si
// prepara subito a questa particolare funzione.

int8_t flares = 0;

int32_t mp[6 * VERTEXES_PER_POLYGON];

// Dati globali per conversioni, rototraslazioni e clipping.

int8_t doflag;
int16_t pvert, nvert, vvert;
int16_t vr2, vr3, vr4, vr5, vr6;

float zk;

/*

    Voglio annotarmi le sigle complicate, senn� finisce come per u-neg.

    doflag   = DO-(or-not)-for-each-polygon-FLAG.
           da quando c'� il fast-load funge anche come contatore
           per i vertici da non ritagliare a livello 3d.
           infatti, se sono tutti in doflag, il poligono non
           interseca lo schermo e si pu� lasciare com'�, almeno
           a livello 3d.
    x2,y2,z2 = variabili di transito nelle rotazioni.
    pvert    = Previous-VERTex.
    nvert    = Next-VERTex.
    vvert    = bella domanda, mi sono scordato anche questa.
           venuto in mente: Visible VERTex, vertice visibile.
    zk       = Zeta-Constant... costante derivata dal calcolo della
           differenza tra coordinate zeta normalizzate allo schermo,
           viene usata nel clipping a livello 3d dalla funz. "poly3d".
           in realt� � una costante solo per due equazioni,
           ma � meglio calcolarla una volta sola che due.

    xx,yy,zz = in questa inclusione non sono mai usate, ma ci sono sempre
           state perch� una volta servivano a qualcosa (non ricordo
           per nulla a cosa). attualmente, devono rimanerci perch�
           molti programmi le usano come variabili temporanee.

    pun = PUNto, � un contatore/non esiste pi� dacch� ho tradotto in asm.
    rxf = Rototraslated-X-Floating-point-value.
    rwf = Rototraslated-vieW-(or-not)-Flag.
    mp  = Matrice Punti.
    lbx = LowerBound-X.
    ubx = UpperBound-X.

    opt_tsinalfa = OPTimized-Table-of-SINe-for-ALFA-angle.
    opt_psinalfa = OPTimized-Projected-table-of-SINe-for-ALFA-angle.

*/

int8_t rwf[VERTEXES_PER_POLYGON];

float rxf[VERTEXES_PER_POLYGON];
float ryf[VERTEXES_PER_POLYGON];
float rzf[VERTEXES_PER_POLYGON];

// Video area limits reworked.

int32_t lbxl = lbx;
int32_t ubxl = ubx;
int32_t lbyl = lby;
int32_t ubyl = uby;

float lbxf = (float) ((int32_t) lbx);
float ubxf = (float) ((int32_t) ubx);
float lbyf = (float) ((int32_t) lby);
float ubyf = (float) ((int32_t) uby);

float x_centro_f = VIEW_X_CENTER;
float y_centro_f = VIEW_Y_CENTER;

// Call after changing the visual angle.
// Update the following optimization variables, used by poly3d.

float opt_pcosbeta = dpp;
float opt_psinbeta = 0;
float opt_tcosbeta = 1;
float opt_tsinbeta = 0;
float opt_pcosalfa = dpp;
float opt_psinalfa = 0;
float opt_tcosalfa = 1;
float opt_tsinalfa = 0;

float opt_tcosngamma = 1;
float opt_tsinngamma = 0;

void change_angle_of_view() {
    opt_pcosbeta   = (float) cos(beta * deg) * dpp;
    opt_psinbeta   = (float) sin(beta * deg) * dpp;
    opt_tcosbeta   = (float) cos(beta * deg);
    opt_tsinbeta   = (float) sin(beta * deg);
    opt_pcosalfa   = (float) cos(alfa * deg) * dpp; // 0.833
    opt_psinalfa   = (float) sin(alfa * deg) * dpp; // 0.833
    opt_tcosalfa   = (float) cos(alfa * deg);
    opt_tsinalfa   = (float) sin(alfa * deg);
    opt_tcosngamma = (float) cos(ngamma * deg);
    opt_tsinngamma = (float) sin(ngamma * deg);
}

// Call after changing dpp.
// Change the camera lens.

void change_camera_lens() {
    XCOEFF = EMU_K / dpp;
    YCOEFF = EMU_K / dpp;
    change_angle_of_view();
}

// Call after changing V_MATRIXS or H_MATRIXS.
// Update the job variables for texture mapping.

void change_txm_repeating_mode() {
    XSIZE = TEXTURE_X_SIZE * H_MATRIXS;
    YSIZE = TEXTURE_Y_SIZE * V_MATRIXS;
}

/*  Questa � la funzione da invocare per ogni poligono da tracciare.

    E` un vero capolavoro: nessun problema, massima ottimizzazione,
    al 99% puro assembly per coprocessori da 387 in su e codice 32-bit,
    probabilmente la pi� complessa e bella funzione ch'io abbia mai
    partorito.

    Chiunque tenter� di capirci qualcosa rimarr� molto scoraggiato.
    Lungo e complesso, ma provate ad eseguirlo ed a monitorarne il flusso:
    vi accorgerete della sua enorme agilit�. */

float uno =
    1; // Always one: it is a constant of convenience. (Very cool, italy man)

uint8_t entity = 1; /* check generic quantities in polygon filling with some
                       special effects */

void poly3d(const float *x, const float *y, const float *z, uint16_t nrv,
            uint8_t colore) {
    uint16_t _8n;
    uint8_t ent = entity;
    // 3D Matrices: Everything on the stack
    float ultima_x[2 * VERTEXES_PER_POLYGON];
    float ultima_y[2 * VERTEXES_PER_POLYGON];
    float ultima_z[2 * VERTEXES_PER_POLYGON];

    // 2D Matrices: Same as above.
    float video_x0[2 * VERTEXES_PER_POLYGON],
        video_y0[2 * VERTEXES_PER_POLYGON];
    float video_x1[3 * VERTEXES_PER_POLYGON],
        video_y1[3 * VERTEXES_PER_POLYGON];
    float video_x2[4 * VERTEXES_PER_POLYGON],
        video_y2[4 * VERTEXES_PER_POLYGON];
    float video_x3[6 * VERTEXES_PER_POLYGON],
        video_y3[6 * VERTEXES_PER_POLYGON];
    // Rototranslations of the vertices; the data still remains 3D.

    doflag = 0;
    for (uint16_t i = 0; i < nrv; i++) {
        float zz = z[i] - cam_z;
        float xx = x[i] - cam_x;
        float yy = y[i] - cam_y;

        float z2 = (zz * opt_tcosbeta) - (xx * opt_tsinbeta);

        rxf[i] = (zz * opt_psinbeta) + (xx * opt_pcosbeta);
        rzf[i] = (z2 * opt_tcosalfa) + (yy * opt_tsinalfa);
        ryf[i] = (yy * opt_pcosalfa) - (z2 * opt_psinalfa);

        if (rzf[i] >= uneg) {
            doflag++;
            rwf[i] = 1;
        } else {
            rwf[i] = 0;
        }
    }

    if (!doflag) {
        return;
    }

    // Fast-load for completely visible polygons.
    if (doflag == nrv) {
        vr2 = nrv;
        memcpy(ultima_x, rxf, nrv * sizeof(float));
        memcpy(ultima_y, ryf, nrv * sizeof(float));
        memcpy(ultima_z, rzf, nrv * sizeof(float));
    } else {
        // Convert points behind the observer compared to the screen plane
        uint16_t fakedi = 0;
        for (uint16_t vr = 0; vr < nrv; vr++) {
            if (rwf[vr] != 0) {
                ultima_x[fakedi / 4] = rxf[vr];
                ultima_y[fakedi / 4] = ryf[vr];
                ultima_z[fakedi / 4] = rzf[vr];
                fakedi += 4;
                continue;
            }

            if (vr >= 1) {
                pvert = vr - 1;
            } else {
                pvert = nrv - 1;
            }

            if ((vr + 1) <= (nrv - 1)) {
                nvert = vr + 1;
            } else {
                nvert = 0;
            }

            if (rwf[pvert] == 0 && rwf[nvert] == 0)
                continue;

            if (rwf[pvert] + rwf[nvert] == 2) {
                if (rzf[vr] == rzf[pvert]) {
                    ultima_x[fakedi / 4] = rxf[vr];
                    ultima_y[fakedi / 4] = ryf[vr];
                } else {
                    zk = (uneg - rzf[pvert]) / (rzf[vr] - rzf[pvert]);

                    ultima_x[fakedi / 4] =
                        zk * (rxf[vr] - rxf[pvert]) + rxf[pvert];
                    ultima_y[fakedi / 4] =
                        zk * (ryf[vr] - ryf[pvert]) + ryf[pvert];
                }
                ultima_z[fakedi / 4] = uneg;

                if (rzf[vr] == rzf[nvert]) {
                    ultima_x[(fakedi / 4) + 1] = rxf[vr];
                    ultima_y[(fakedi / 4) + 1] = ryf[vr];
                } else {
                    zk = (uneg - rzf[nvert]) / (rzf[vr] - rzf[nvert]);

                    ultima_x[(fakedi / 4) + 1] =
                        zk * (rxf[vr] - rxf[nvert]) + rxf[nvert];
                    ultima_y[(fakedi / 4) + 1] =
                        zk * (ryf[vr] - ryf[nvert]) + ryf[nvert];
                }
                ultima_z[(fakedi / 4) + 1] = uneg;
                fakedi += 8;
            } else {
                if (rwf[pvert] == 0) {
                    vvert = nvert;
                } else {
                    vvert = pvert;
                }

                if (rzf[vvert] == rzf[vr]) {
                    ultima_x[fakedi / 4] = rxf[vr];
                    ultima_y[fakedi / 4] = ryf[vr];
                } else {
                    zk = (uneg - rzf[vvert]) / (rzf[vr] - rzf[vvert]);

                    ultima_x[fakedi / 4] =
                        zk * (rxf[vr] - rxf[vvert]) + rxf[vvert];
                    ultima_y[fakedi / 4] =
                        zk * (ryf[vr] - ryf[vvert]) + ryf[vvert];
                }

                ultima_z[fakedi / 4] = uneg;
                fakedi += 4;
            }
        }

        vr2 = fakedi / 4;

        if (vr2 < 3) {
            return;
        }
    }

    // These are the perspective projections from 3D to 2D.
    // A small check was included on 6/12/97 of the minimum and
    // maximum graphs. This makes sure that the polygons which
    // fall within the limits of the screen are not checked by
    // the 2D clipping functions. Is it more intelligent? Before
    // now, the minimum-maximum search cycle was at the bottom
    // and it was executed after clipping 2D. What for? Long
    // and complicated: therefore one thing to not always do.
    _8n = (vr2 - 1) * 8;

    int32_t temp_max_x = lbxl;
    int32_t temp_max_y = lbyl;
    int32_t temp_min_x = ubxl;
    int32_t temp_min_y = ubyl;

    for (int32_t i = vr2 - 1; i >= 0; i--) {
        float base = uno / ultima_z[i];

        float xtest = base * ultima_x[i] + x_centro_f;
        video_x0[i] = xtest;
        mp[i * 2]   = round(xtest);
        if (mp[i * 2] > temp_max_x)
            temp_max_x = mp[i * 2];
        if (mp[i * 2] < temp_min_x)
            temp_min_x = mp[i * 2];

        float ytest   = base * ultima_y[i] + y_centro_f;
        video_y0[i]   = ytest;
        mp[i * 2 + 1] = round(ytest);
        if (mp[i * 2 + 1] > temp_max_y)
            temp_max_y = mp[i * 2 + 1];
        if (mp[i * 2 + 1] < temp_min_y)
            temp_min_y = mp[i * 2 + 1];
    }

    uint16_t max_x = temp_max_x;
    uint16_t max_y = temp_max_y;
    uint16_t min_x = temp_min_x;
    uint16_t min_y = temp_min_y;

    bool oob = false;
    if (temp_max_x >= ubxl) {
        oob   = true;
        max_x = ubx;
    }
    if (temp_max_y >= ubyl) {
        oob   = true;
        max_y = uby;
    }
    if (temp_min_x < lbxl) {
        oob   = true;
        min_x = lbx;
    }
    if (temp_min_y < lbyl) {
        oob   = true;
        min_y = lby;
    }

    uint16_t fakedi = 0;

    if (!oob)
        goto drawb;

    /* Conversion of points outside of the visible area. These points must be
     * resized to be within the visible area to avoid polygons that are too
     * large, which would lead to both buffer overruns and slow rendering.
     * In this section the vertices of the polygon are reworked on a 2d level
     * to retriangulate them and generate only visible polygons. */

    // Top side of the video

    for (uint16_t vr = 0; vr < vr2; vr++) {
        if (video_y0[vr] >= lbyf) {
            video_y1[fakedi] = video_y0[vr];
            video_x1[fakedi] = video_x0[vr];

            fakedi += 1;
            continue;
        }

        if (vr >= 1) {
            pvert = vr - 1;
        } else {
            pvert = vr2 - 1;
        }

        if ((vr + 1) > (vr2 - 1)) {
            nvert = 0;
        } else {
            nvert = vr + 1;
        }

        if ((video_y0[pvert] < lbyf) && (video_y0[nvert] < lbyf)) {
            continue;
        }

        if ((video_y0[pvert] < lbyf) || (video_y0[nvert] < lbyf)) {
            if (video_y0[pvert] < lbyf) {
                vvert = nvert;
            } else {
                vvert = pvert;
            }

            if (video_y0[vr] == video_y0[vvert]) {
                video_x1[fakedi] = video_x0[vr];
            } else {
                video_x1[fakedi] = ((lbyf - video_y0[vvert]) /
                                    (video_y0[vr] - video_y0[vvert])) *
                                       (video_x0[vr] - video_x0[vvert]) +
                                   video_x0[vvert];
            }

            video_y1[fakedi] = lbyf;

            fakedi += 1;
        } else {
            if (video_y0[vr] == video_y0[pvert]) {
                video_x1[fakedi] = video_x0[vr];
            } else {
                video_x1[fakedi] = (((lbyf - video_y0[pvert]) /
                                     (video_y0[vr] - video_y0[pvert])) *
                                    (video_x0[vr] - video_x0[pvert])) +
                                   video_x0[pvert];
            }

            video_y1[fakedi] = lbyf;

            if (video_y0[vr] == video_y0[nvert]) {
                video_x1[fakedi + 1] = video_x0[vr];
            } else {
                video_x1[fakedi + 1] = ((lbyf - video_y0[nvert]) /
                                        (video_y0[vr] - video_y0[nvert])) *
                                           (video_x0[vr] - video_x0[nvert]) +
                                       video_x0[nvert];
            }

            video_y1[fakedi + 1] = lbyf;

            fakedi += 2;
        }
    }

    vr3 = fakedi;

    if (vr3 < 3) {
        return;
    }

    // Bottom side of the video.

    fakedi = 0;
    for (uint16_t vr = 0; vr < vr3; vr++) {
        if (video_y1[vr] <= ubyf) {
            video_y2[fakedi] = video_y1[vr];
            video_x2[fakedi] = video_x1[vr];

            fakedi += 1;
            continue;
        }

        if (vr >= 1) {
            pvert = vr - 1;
        } else {
            pvert = vr3 - 1;
        }

        if ((vr + 1) > (vr3 - 1)) {
            nvert = 0;
        } else {
            nvert = vr + 1;
        }

        if ((video_y1[pvert] > ubyf) && (video_y1[nvert] > ubyf)) {
            continue;
        }

        if ((video_y1[pvert] > ubyf) || (video_y1[nvert] > ubyf)) {
            if (video_y1[pvert] > ubyf) {
                vvert = nvert;
            } else {
                vvert = pvert;
            }

            if (video_y1[vr] == video_y1[vvert]) {
                video_x2[fakedi] = video_x1[vr];
            } else {
                video_x2[fakedi] = ((ubyf - video_y1[vvert]) /
                                    (video_y1[vr] - video_y1[vvert])) *
                                       (video_x1[vr] - video_x1[vvert]) +
                                   video_x1[vvert];
            }

            video_y2[fakedi] = ubyf;

            fakedi += 1;
        } else {
            if (video_y1[vr] == video_y1[pvert]) {
                video_x2[fakedi] = video_x1[vr];
            } else {
                video_x2[fakedi] = (((ubyf - video_y1[pvert]) /
                                     (video_y1[vr] - video_y1[pvert])) *
                                    (video_x1[vr] - video_x1[pvert])) +
                                   video_x1[pvert];
            }

            video_y2[fakedi] = ubyf;

            if (video_y1[vr] == video_y1[nvert]) {
                video_x2[fakedi + 1] = video_x1[vr];
            } else {
                video_x2[fakedi + 1] = ((ubyf - video_y1[nvert]) /
                                        (video_y1[vr] - video_y1[nvert])) *
                                           (video_x1[vr] - video_x1[nvert]) +
                                       video_x1[nvert];
            }

            video_y2[fakedi + 1] = ubyf;

            fakedi += 2;
        }
    }
    vr4 = fakedi;

    if (vr4 < 3) {
        return;
    }

    // Left side of the video.
    fakedi = 0;
    for (uint16_t vr = 0; vr < vr4; vr++) {
        if (video_x2[vr] >= lbxf) {
            video_x3[fakedi] = video_x2[vr];
            video_y3[fakedi] = video_y2[vr];

            fakedi += 1;
            continue;
        }

        if (vr >= 1) {
            pvert = vr - 1;
        } else {
            pvert = vr4 - 1;
        }

        if ((vr + 1) > (vr4 - 1)) {
            nvert = 0;
        } else {
            nvert = vr + 1;
        }

        if ((video_x2[pvert] < lbxf) && (video_x2[nvert] < lbxf)) {
            continue;
        }

        if ((video_x2[pvert] < lbxf) || (video_x2[nvert] < lbxf)) {
            if (video_x2[pvert] < lbxf) {
                vvert = nvert;
            } else {
                vvert = pvert;
            }

            if (video_x2[vr] == video_x2[vvert]) {
                video_y3[fakedi] = video_y2[vr];
            } else {
                video_y3[fakedi] = ((lbxf - video_x2[vvert]) /
                                    (video_x2[vr] - video_x2[vvert])) *
                                       (video_y2[vr] - video_y2[vvert]) +
                                   video_y2[vvert];
            }

            video_x3[fakedi] = lbxf;

            fakedi += 1;
        } else {
            if (video_x2[vr] == video_x2[pvert]) {
                video_y3[fakedi] = video_y2[vr];
            } else {
                video_y3[fakedi] = (((lbxf - video_x2[pvert]) /
                                     (video_x2[vr] - video_x2[pvert])) *
                                    (video_y2[vr] - video_y2[pvert])) +
                                   video_y2[pvert];
            }

            video_x3[fakedi] = lbxf;

            if (video_x2[vr] == video_x2[nvert]) {
                video_y3[fakedi + 1] = video_y2[vr];
            } else {
                video_y3[fakedi + 1] = ((lbxf - video_x2[nvert]) /
                                        (video_x2[vr] - video_x2[nvert])) *
                                           (video_y2[vr] - video_y2[nvert]) +
                                       video_y2[nvert];
            }

            video_x3[fakedi + 1] = lbxf;

            fakedi += 2;
        }
    }
    vr5 = fakedi;

    if (vr5 < 3) {
        return;
    }

    // Right side of the video.
    fakedi = 0;
    for (uint16_t vr = 0; vr < vr5; vr++) {
        if (video_x3[vr] <= ubxf) {
            mp[fakedi]     = round(video_x3[vr]);
            mp[fakedi + 1] = round(video_y3[vr]);

            fakedi += 2;

            continue;
        }

        if (vr >= 1) {
            pvert = vr - 1;
        } else {
            pvert = vr5 - 1;
        }

        if ((vr + 1) > (vr5 - 1)) {
            nvert = 0;
        } else {
            nvert = vr + 1;
        }

        if ((video_x3[pvert] > ubxf) && (video_x3[nvert] > ubxf)) {
            continue;
        }

        if (video_x3[pvert] > ubxf || video_x3[nvert] > ubxf) {
            if (video_x3[pvert] > ubxf) {
                vvert = nvert;
            } else {
                vvert = pvert;
            }

            if (video_x3[vr] == video_x3[vvert]) {
                mp[fakedi + 1] = round(video_y3[vr]);
            } else {
                mp[fakedi + 1] = round(((ubxf - video_x3[vvert]) /
                                        (video_x3[vr] - video_x3[vvert])) *
                                           (video_y3[vr] - video_y3[vvert]) +
                                       video_y3[vvert]);
            }

            mp[fakedi] = (uint32_t) ubx & 0x0000FFFFu; // y tho

            fakedi += 2;
            continue;
        } else {
            if (video_x3[vr] == video_x3[pvert]) {
                mp[fakedi + 1] = round(video_y3[vr]);
            } else {
                mp[fakedi + 1] = round(((ubxf - video_x3[pvert]) /
                                        (video_x3[vr] - video_x3[pvert])) *
                                           (video_y3[vr] - video_y3[pvert]) +
                                       video_y3[pvert]);
            }

            mp[fakedi] = (uint32_t) ubx & 0x0000FFFFu;

            if (video_x3[vr] == video_x3[nvert]) {
                mp[fakedi + 3] = round(video_y3[vr]);
            } else {
                mp[fakedi + 3] = round(((ubxf - video_x3[nvert]) /
                                        (video_x3[vr] - video_x3[nvert])) *
                                           (video_y3[vr] - video_y3[nvert]) +
                                       video_y3[nvert]);
            }

            mp[fakedi + 2] = (uint32_t) ubx & 0x0000FFFFu;

            fakedi += 4;
            continue;
        }
    }

    _8n = (fakedi - 2) * 4;
    vr6 = fakedi;

    if (vr6 < 3) {
        return;
    }

/* Filling of the resulting polygon. */
// Quick tracing (3 ballets (Translation error..?) & away, for small polys).
drawb:

    if (!flares) {
        if (min_y == max_y) {
            if (min_x == max_x) {
                adapted[min_x + 320 * min_y] = colore;
            } else {
                ptr = max_x + 320 * min_y;

                while (max_x >= min_x) {
                    adapted[ptr] = colore;
                    max_x--;
                    ptr--;
                }
            }

            return;
        }
    }

    // Complete tracing.
    // Draw the edges of the polygon, with the segment function.
    for (fakedi = 0; fakedi < (_8n / 4); fakedi += 2) {
        segment(mp[fakedi], mp[fakedi + 1], mp[fakedi + 2], mp[fakedi + 3]);
    }

    segment(mp[fakedi], mp[fakedi + 1], mp[0], mp[1]);
    // Starting Pixels
    uint16_t segmptr = 320 * min_y + min_x;
    // Arrival pixels
    uint16_t lim_y = 320 * max_y + min_x;
    uint16_t lim_x = segmptr + max_x - min_x;
    uint16_t bytes = lim_x - segmptr + 2;

    uint16_t loc0, loc1, tempBytes, tinkywinky, laalaa;
    uint32_t tempfakedi;
    uint8_t dipsy, po;

    switch (flares) {
    case 0:
        for (fakedi = segmptr; fakedi <= lim_y; fakedi += 320) {
            tempBytes  = bytes;
            tempfakedi = fakedi;

            if (adapted[tempfakedi] != 255) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes == 0)
                continue;
            loc0 = tempfakedi;

            while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                ;
            loc1 = tempfakedi;

            if (adapted[tempfakedi] != 255 && tempBytes > 0) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes > 0) {
                while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                    ;

                tempfakedi--;
                tempfakedi = tempfakedi > 64000 ? 64000 : tempfakedi;
                memset(&adapted[loc0], colore, tempfakedi - loc0);
            } else {
                loc1--;
                memset(&adapted[loc0], colore, loc1 - loc0);
            }
        }
        break;

    case 1:
        colore &= 0x3Fu;
        for (fakedi = segmptr; fakedi <= lim_y; fakedi += 320) {
            tempBytes  = bytes;
            tempfakedi = fakedi;

            if (adapted[tempfakedi] != 255) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes == 0)
                continue;
            loc0 = tempfakedi;

            while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                ;
            loc1 = tempfakedi;

            if (adapted[tempfakedi] != 255 && tempBytes > 0) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes > 0) {
                while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                    ;
                tempfakedi--;

                tinkywinky = tempfakedi - loc0;
                tempfakedi = loc0;

                for (; tinkywinky > 0; tempfakedi++, tinkywinky--) {
                    dipsy = adapted[tempfakedi - 1];
                    dipsy &= 0x3Fu;
                    dipsy += colore;

                    if (dipsy > 62)
                        dipsy = 62;

                    adapted[tempfakedi] = dipsy;
                }
            } else {
                loc1--;

                tinkywinky = loc1 - loc0;
                tempfakedi = loc0;

                dipsy = colore >> 1u;

                for (; tinkywinky > 0; tempfakedi++, tinkywinky--) {
                    po = adapted[tempfakedi - 1];
                    po &= 0x3Fu;
                    po += dipsy;

                    if (po > 62)
                        po = 62;

                    adapted[tempfakedi] = po;
                }
            }
        }
        break;
    case 2:
        for (fakedi = segmptr; fakedi <= lim_y; fakedi += 320) {
            tempBytes  = bytes;
            tempfakedi = fakedi;

            if (adapted[tempfakedi] != 255) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes == 0)
                continue;
            loc0 = tempfakedi;

            while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                ;
            loc1 = tempfakedi;

            if (adapted[tempfakedi] != 255 && tempBytes > 0) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes > 0) {
                while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                    ;
                tempfakedi--;

                tinkywinky = tempfakedi - loc0;
                tempfakedi = loc0;

                for (; tinkywinky > 0; tempfakedi++, tinkywinky--) {
                    tempfakedi = tempfakedi > 64000 ? 64000 : tempfakedi;
                    if (adapted[tempfakedi] == 0xFF) {
                        dipsy = adapted[tempfakedi - 321];
                        dipsy &= 0x3Fu;
                        dipsy |= 0x40u;
                        adapted[tempfakedi] = dipsy;
                    } else {
                        laalaa = adapted[tempfakedi];
                        laalaa &= 0x3Fu;
                        laalaa |= 0x40u;
                        laalaa += tinkywinky;
                        if (laalaa >= 128)
                            laalaa = 127;
                        adapted[tempfakedi] = laalaa;
                    }
                }
            } else {
                loc1--;
                for (tempfakedi = loc0; tempfakedi < loc1; tempfakedi++) {
                    dipsy = adapted[tempfakedi - 321];
                    if (dipsy == 0xFF) {
                        dipsy = adapted[tempfakedi - 642];
                    }

                    dipsy &= 0x3Fu;
                    dipsy |= 0x40u;
                    adapted[tempfakedi] = dipsy;
                }
            }
        }
        break;
        // effetto flares = 3 spostato a "polymap"
    case 4:
        for (fakedi = segmptr; fakedi <= lim_y; fakedi += 320) {
            tempBytes  = bytes;
            tempfakedi = fakedi;

            if (adapted[tempfakedi] != 255) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes == 0)
                continue;
            loc0 = tempfakedi;

            while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                ;
            loc1 = tempfakedi;

            if (adapted[tempfakedi] != 255 && tempBytes > 0) {
                while (--tempBytes > 0 && adapted[++tempfakedi] != 255)
                    ;
            }

            if (tempBytes > 0) {
                while (tempBytes-- > 0 && adapted[tempfakedi++] == 255)
                    ;

                tempfakedi--;
                memset(&adapted[loc0], colore, tempfakedi - loc0);
            } else {
                loc1--;
                memset(&adapted[loc0], colore, loc1 - loc0);
            }

            dipsy = (colore & 0x3Fu) + ent;
            po    = colore & 0xC0u;

            if (dipsy > 0x3F) {
                dipsy = 0x3F;
                if (ent & 0x80u) {
                    dipsy = 0;
                }
            }

            dipsy |= po;
            colore = dipsy;
        }
        break;
    default:
        return;
    }
}

/*

    Sezione per il texture mapping.

*/

uint8_t *txtr; /* Area della texture (FLS a livelli di intensit�,
                 64 livelli per pixel, senza header).*/

float pnx, pny, pnz; // valori di ritorno della funzione successiva. */

void pnorm(const float *x, const float *y, const float *z)
// Calcola i coefficenti x/y/z della normale ad un poligono.
// Valori calcolati in pnx, pny, pnz.
// Richiesti almeno tre vertici.
// N.B. I vertici sono scanditi in senso orario,
//      il vettore risultante rispetta la regola della mano destra.
{
    float x1, y1, z1;
    float x2, y2, z2;
    float xr, yr, zr;
    float ln;
    x1 = x[0] - x[2];
    y1 = y[0] - y[2];
    z1 = z[0] - z[2];
    x2 = x[1] - x[2];
    y2 = y[1] - y[2];
    z2 = z[1] - z[2];
    xr = y1 * z2 - y2 * z1;
    yr = z1 * x2 - z2 * x1;
    zr = x1 * y2 - x2 * y1;
    ln = sqrt(xr * xr + yr * yr + zr * zr);

    if (ln > 0) {
        ln  = 1 / ln;
        pnx = xr * ln;
        pny = yr * ln;
        pnz = zr * ln;
    } else {
        pnx = 0;
        pny = 0;
        pnz = 0;
    }
}

/*  Se si desidera una texture sui poligoni, invocare quest'altra funzione.
    Il parametro "tinta" permette di specificare il colore meno luminoso
    di una sequenza di sue copie pi� intense: il numero di queste
    gradazioni non � importante per polymap.

    E` leggermente pi� lenta nel riempimento, ma non � grave.
    N.B. Il poligono deve avere sempre 4 vertici, anche se specificare il
    numero di vertici effettivi con il parametro "nv" aggiusta la
    texture in modo che i bordi coincidano.

    P.S. Sulla pagina nascosta, bisogna prevedere un byte in pi� (64001),
    perch� vi viene conservato il numero del primo colore della texture,
    dato che i parametri sullo stack non sono raggiungibili nel ciclo
    di tracciamento principale, per ragioni di ottimizzazione. */

float x_antialias = 1.125;
float y_antialias = 1.125;
float z_antialias = 1.125;

int8_t culling_needed  = 0; // flag: traccia due punti per volta.
int8_t halfscan_needed = 0; // flag: traccia due linee per volta.

uint8_t escrescenze = 0xE0; // primo colore dei bumps (escrescenze)

void polymap(float *x, float *y, float *z, int8_t nv, uint8_t tinta) {
    float ultima_x[2 * VERTEXES_PER_POLYGON];
    float ultima_y[2 * VERTEXES_PER_POLYGON];
    float ultima_z[2 * VERTEXES_PER_POLYGON];
    int16_t fpart[MPIY];
    int16_t ipart[MPIY];
    float tempXsize = XSIZE;
    float tempYsize = YSIZE;
    int8_t _flares  = flares;
    int8_t culling  = culling_needed;
    int8_t halfscan = halfscan_needed;
    int16_t vr22;
    int32_t bndx;
    int16_t sections;
    int32_t i_low_lim = -10000;
    int32_t i_hig_lim = +10000;
    int32_t u, v, min_y, max_y;
    int32_t x1, y1, x2, y2, ity, jty, h;
    float k1, k2, k3, k4;
    float hx, vx, ox, hy, vy, oy, hz, vz, oz, _x, _y, _z;
    float kx, rx, ry, rz, mx, my, mz, nx, ny, nz, xx, yy, zz, z2;
    float midx, midy, midz;
    float trxf[4], tryf[4], trzf[4];

    // Polymap is made to draw quads.
    // If drawing a triangle, the last vertex must be duplicated.

    if (nv == 3) {
        x[3] = x[2];
        y[3] = y[2];
        z[3] = z[2];
    }

    // Rototranslations of the vertices; the data still remains 3D.
    doflag = 0;

    for (uint32_t i = 0; i < 4; i++) {
        xx = x[i] - cam_x;
        yy = y[i] - cam_y;
        zz = z[i] - cam_z;

        z2 = (zz * opt_tcosbeta) - (xx * opt_tsinbeta);

        rxf[i] = (xx * opt_tcosbeta) + (zz * opt_tsinbeta);
        rzf[i] = (yy * opt_tsinalfa) + (z2 * opt_tcosalfa);

        if (ngamma == 0) {
            ryf[i] = (yy * opt_tcosalfa) - (z2 * opt_tsinalfa);
        } else {
            // TODO; Untested.
            my = (yy * opt_tcosalfa) - (z2 * opt_tsinalfa);

            ryf[i] = (my * opt_tcosngamma) - (rxf[i] * opt_tsinngamma);
            rxf[i] = (rxf[i] * opt_tcosngamma) + (my * opt_tsinngamma);
        }

        if (rzf[i] < uneg) {
            rwf[i] = 0;
        } else {
            rwf[i] = 1;
            doflag++;
        }
    }

    if (!doflag)
        return;

    // Calculation of texture mapping tracking vectors.
    uint16_t target = 0;
    if (nv == 3) {
        midx = (rxf[0] + rxf[1] + rxf[2]) * 0.3333333f;
        midy = (ryf[0] + ryf[1] + ryf[2]) * 0.3333333f;
        midz = (rzf[0] + rzf[1] + rzf[2]) * 0.3333333f;

        for (uint16_t vr = 0; vr < 3; vr++) {
            trxf[vr] = (rxf[vr] - midx) * x_antialias + midx;
            tryf[vr] = (ryf[vr] - midy) * y_antialias + midy;
            trzf[vr] = (rzf[vr] - midz) * z_antialias + midz;
        }

        target = 2;
    } else {
        midx = (rxf[0] + rxf[1] + rxf[2] + rxf[3]) * 0.25f;
        midy = (ryf[0] + ryf[1] + ryf[2] + ryf[3]) * 0.25f;
        midz = (rzf[0] + rzf[1] + rzf[2] + rzf[3]) * 0.25f;

        for (uint16_t vr = 0; vr < 4; vr++) {
            trxf[vr] = (rxf[vr] - midx) * x_antialias + midx;
            tryf[vr] = (ryf[vr] - midy) * y_antialias + midy;
            trzf[vr] = (rzf[vr] - midz) * z_antialias + midz;
        }

        target = 3;
    }

    rx = trxf[0];
    mx = trxf[1] - rx;
    nx = rx - trxf[target];

    ry = tryf[0];
    my = tryf[1] - ry;
    ny = ry - tryf[target];

    rz = trzf[0];
    mz = trzf[1] - rz;
    nz = rz - trzf[target];

    hx = (rx * mz - rz * mx) * YCOEFF;
    hy = (rx * nz - rz * nx) * YCOEFF;
    hz = (nx * mz - nz * mx) / dpp;

    vx = (rz * my - ry * mz) * XCOEFF;
    vy = (rz * ny - ry * nz) * XCOEFF;
    vz = (nz * my - ny * mz) / dpp;

    ox = (ry * mx - rx * my) * EMU_K;
    oy = (ry * nx - rx * ny) * EMU_K;
    oz = ny * mx - nx * my;

    // Fast-load for fully visible polygons.
    if (doflag == 4) {
        vr2  = 4;
        vr22 = 8;
        for (uint32_t i = 0; i < 4; i++) {
            ultima_x[i] = rxf[i];
            ultima_y[i] = ryf[i];
            ultima_z[i] = rzf[i];
        }
    } else {
        // Clip points behind the observer compared to the screen plane.
        uint16_t fakedi = 0;
        for (uint16_t vr = 0; vr < 4; vr++) {
            if (rwf[vr] != 0) {
                ultima_x[fakedi / 4] = rxf[vr];
                ultima_y[fakedi / 4] = ryf[vr];
                ultima_z[fakedi / 4] = rzf[vr];
                fakedi += 4;
                continue;
            }

            if (vr >= 1) {
                pvert = vr - 1;
            } else {
                pvert = 3;
            }

            if ((vr + 1) <= 3) {
                nvert = vr + 1;
            } else {
                nvert = 0;
            }

            if (rwf[pvert] == 0 && rwf[nvert] == 0)
                continue;

            if (rwf[pvert] + rwf[nvert] == 2) {
                if (rzf[vr] == rzf[pvert]) {
                    ultima_x[fakedi / 4] = rxf[vr];
                    ultima_y[fakedi / 4] = ryf[vr];
                } else {
                    zk = (uneg - rzf[pvert]) / (rzf[vr] - rzf[pvert]);

                    ultima_x[fakedi / 4] =
                        zk * (rxf[vr] - rxf[pvert]) + rxf[pvert];
                    ultima_y[fakedi / 4] =
                        zk * (ryf[vr] - ryf[pvert]) + ryf[pvert];
                }
                ultima_z[fakedi / 4] = uneg;

                if (rzf[vr] == rzf[nvert]) {
                    ultima_x[(fakedi / 4) + 1] = rxf[vr];
                    ultima_y[(fakedi / 4) + 1] = ryf[vr];
                } else {
                    zk = (uneg - rzf[nvert]) / (rzf[vr] - rzf[nvert]);

                    ultima_x[(fakedi / 4) + 1] =
                        zk * (rxf[vr] - rxf[nvert]) + rxf[nvert];
                    ultima_y[(fakedi / 4) + 1] =
                        zk * (ryf[vr] - ryf[nvert]) + ryf[nvert];
                }
                ultima_z[(fakedi / 4) + 1] = uneg;
                fakedi += 8;
            } else {
                if (rwf[pvert] == 0) {
                    vvert = nvert;
                } else {
                    vvert = pvert;
                }

                if (rzf[vvert] == rzf[vr]) {
                    ultima_x[fakedi / 4] = rxf[vr];
                    ultima_y[fakedi / 4] = ryf[vr];
                } else {
                    zk = (uneg - rzf[vvert]) / (rzf[vr] - rzf[vvert]);

                    ultima_x[fakedi / 4] =
                        zk * (rxf[vr] - rxf[vvert]) + rxf[vvert];
                    ultima_y[fakedi / 4] =
                        zk * (ryf[vr] - ryf[vvert]) + ryf[vvert];
                }

                ultima_z[fakedi / 4] = uneg;
                fakedi += 4;
            }
        }

        vr2  = fakedi / 4;
        vr22 = fakedi / 2;

        if (vr2 < 3) {
            return;
        }
    }

    // These are the perspective projections from 3D to 2D.
    // The cycle simultaneously searches for the min and max vertical
    // polygon extension on the screen.
    int32_t temp_min_y = ubyl;
    int32_t temp_max_y = lbyl;

    for (int16_t i = (vr2 - 1); i >= 0; i--) {
        float base = dpp / ultima_z[i];

        float xtest = base * ultima_x[i] + x_centro_f;
        float ytest = base * ultima_y[i] + y_centro_f;

        mp[i * 2]     = round(xtest);
        mp[i * 2 + 1] = round(ytest);

        temp_min_y = (mp[i * 2 + 1] < temp_min_y) ? mp[i * 2 + 1] : temp_min_y;
        temp_max_y = (mp[i * 2 + 1] > temp_max_y) ? mp[i * 2 + 1] : temp_max_y;
    }

    min_y = temp_min_y;
    max_y = temp_max_y;

    // Possible exclusion of non-visible polygons.
    if (min_y > uby || max_y < lby)
        return;

    // Normalization of limits.
    min_y = (min_y < lby) ? lby : min_y;
    max_y = (max_y > uby) ? uby : max_y;

    if (min_y > max_y)
        return;

    // Initialization of optimization constants.
    k1 = vx * 16;
    k2 = vy * 16;
    k3 = vz * 16;

    if (culling) {
        k1 *= 2;
        k2 *= 2;
        k3 *= 2;
    }

    // Initialization of the horizontal border matrices.
    for (uint32_t i = min_y; i <= max_y; i++) {
        fpart[i] = lbxl;
        ipart[i] = ubxl;
    }

    // Calculation of horizontal borders.
    mp[vr22]     = mp[0];
    mp[vr22 + 1] = mp[1];

    for (uint32_t i = 0; i < vr22; i += 2) {
        if (mp[i + 3] < mp[i + 1]) {
            x1 = mp[i + 2];
            x2 = mp[i];

            y1 = mp[i + 3];
            y2 = mp[i + 1];
        } else {
            x1 = mp[i];
            x2 = mp[i + 2];

            y1 = mp[i + 1];
            y2 = mp[i + 3];
        }

        if (y1 != y2) {
            kx = ((float) (x2 - x1)) / ((float) (y2 - y1));

            if (y1 < lbyl) {
                ity = lbyl;

                x1 += round(((float) (lbyl - y1)) * kx);
            } else {
                ity = y1;
            }

            if (y2 > ubyl) {
                jty = ubyl;
            } else {
                jty = y2;
            }

            if (ity < jty) {
                float tinkywinky = x1;
                for (h = ity; h <= jty; h++) {
                    bndx = tinkywinky;

                    if (bndx < i_low_lim)
                        bndx = i_low_lim;
                    if (bndx > i_hig_lim)
                        bndx = i_hig_lim;

                    if (bndx > fpart[h] && bndx < ubxl) {
                        fpart[h] = bndx;
                    } else if (bndx >= ubxl) {
                        fpart[h] = ubxl;
                    }

                    if (bndx < ipart[h] && bndx > lbxl) {
                        ipart[h] = bndx;
                    } else if (bndx <= lbxl) {
                        ipart[h] = lbxl;
                    }

                    tinkywinky += kx;
                }
            }
        }
    }

    // Pre-work assignments.
    int32_t tempu = 0, tempv = 0;
    uint16_t tax = 0, tbx = 0, tdx = 0, tbp = 0, fakedi = 0, fakesi = 0,
             tempfakedi = 0, reallytempfakedi = 0;
    uint8_t tcl = 0, tch = 0, tbl = 0, tbh = 0, tah = 0, tal = 0, tdh = 0,
            tdl = 0, tempch = 0;
    adapted[0xFA00] = tinta;
    adapted[0xFA01] = escrescenze;

    // Tracking cycle. (NOTE: This makes no sense.)
    for (uint32_t i = min_y; i <= max_y;) {
        _x = ox + (hx * (i - y_centro_f)) +
             (vx * ((float) ipart[i] - x_centro_f + 1));
        _y = oy + (hy * (i - y_centro_f)) +
             (vy * ((float) ipart[i] - x_centro_f + 1));
        _z = oz + (hz * (i - y_centro_f)) +
             (vz * ((float) ipart[i] - x_centro_f + 1));

        k4 = 1.0f / _z;

        u = round((_x * tempXsize) * k4);
        v = round((_y * tempYsize) * k4);

        sections = fpart[i] - ipart[i];
        fakedi   = 320 * i + ipart[i] -
                 4; // i * 320 + ipart[i] - 4; // NOTE: Fudge factor to account
                    // for loss of offset on adapted.

        if (culling) {
            goto c_row;
        }

    //  High detail scanline tracing.
    row:
        if (sections <= 0) {
            goto row_end;
        }

        if (sections > 16) {
            goto complete;
        } else {
            tax = sections;
            tal = (tax & 0xFFu);
            tcl = tal;
            goto unfinished;
        }

    complete:
        tcl = 16;

    unfinished:
        sections -= 16;
        if (tcl == 0) {
            goto row;
        }
        _x += k1;
        _y += k2;
        _z += k3;

        k4 = 1 / _z;

        tempu = u;
        tempv = v;

        u = round((_x * tempXsize) * k4);
        v = round((_y * tempYsize) * k4);

        tax    = tempu;
        tdx    = tempv;
        fakesi = ((uint32_t)(v - tempv)) >> 4u;
        tbp    = ((uint32_t)(u - tempu)) >> 4u;

        tch = _flares;
        if (tch & 1u) {
            goto transp;
        } else if (tch & 2u) {
            goto bright;
        } else if (tch & 4u) {
            goto merger;
        } else if (tch & 8u) {
            goto bumper;
        } else {
            goto internal;
        }

    internal:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tbh = tdh;
        fakedi++;
        tbl = tah;
        tch = adapted[0xFA00];
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)]; // NOTE; Fudge factor to account for
                                          // loss of offset on txtr.
        tax += tbp;
        adapted[fakedi + 3] = tch;
        tdx += fakesi;
        tcl--;
        if (tcl != 0)
            goto internal;
        goto common;

    transp:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tbh = tdh;
        fakedi++;
        tbl = tah;
        tch = adapted[fakedi + 3];
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)];
        tax += tbp;
        adapted[fakedi + 3] = tch;
        tdx += fakesi;
        tcl--;
        if (tcl != 0)
            goto transp;
        goto common;

    bright: // NOTE: This is for the text rendering.
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tch = adapted[fakedi + 4];
        tbh = tdh;
        fakedi++;
        tbl = tah;
        tch &= 0x3Fu;
        tax += tbp;
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        /* NOTE: This frequently runs over the intended end of the txtr (40k),
         * but we have allocated additional space to bring it up to 65k and
         * prevent it from running over. It happens in the original source too.
         */
        tch += txtr[(uint16_t)(tbx - 4)];
        tdx += fakesi;
        if (tch <= 0x3E)
            goto antibloom;
        tch = 0x3E;

    antibloom:
        adapted[fakedi + 3] &= 0xC0u;
        adapted[fakedi + 3] |= tch;
        tcl--;
        if (tcl != 0)
            goto bright;
        goto common;

    merger:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tch = adapted[fakedi + 4];
        tbh = tdh;
        fakedi++;
        tbl = tah;
        tch &= 0x3Fu;
        tax += tbp;
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)];
        tch += adapted[0xFA00];
        tdx += fakesi;
        tch >>= 1u;
        adapted[fakedi + 3] &= 0xC0u;
        adapted[fakedi + 3] |= tch;
        tcl--;
        if (tcl != 0)
            goto merger;
        goto common;

    bumper:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tbh = tdh;
        fakedi++;
        tbl = tah;
        tch = adapted[0xFA00];
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)];
        tax += tbp;
        adapted[fakedi + 3] = tch;
        tempfakedi          = fakedi;
        tempch              = tch;
        tch &= 0x07u;

    bmpm320:
        fakedi -= 320;
        tch--;
        if (!(((uint8_t)(tch >> 7u)) & 1u))
            goto bmpm320;
        tch = tempch;
        tch -= adapted[0xFA00];
        tch += adapted[0xFA01];
        tch += txtr[(uint16_t)(tbx - 4)];
        adapted[fakedi + 640 + 3] = tch;
        fakedi                    = tempfakedi;
        tdx += fakesi;
        tcl--;
        if (tcl != 0)
            goto bumper;

    common:
        goto row;

    // Low detail scanline tracing.
    c_row:
        if (sections <= 0) {
            goto row_end;
        }

        if (sections > 32) {
            goto c_complete;
        } else {
            tax = sections;
            tax += 2;
            tal = (tax & 0xFFu);
            tcl = tal;
            goto c_unfinished;
        }

    c_complete:
        tcl = 32;

    c_unfinished:
        sections -= 32;
        if (tcl < 2) {
            goto c_row;
        }

        _x += k1;
        _y += k2;
        _z += k3;

        k4 = 1 / _z;

        tempu = u;
        tempv = v;

        reallytempfakedi = tempfakedi;

        u = round((_x * tempXsize) * k4);
        v = round((_y * tempYsize) * k4);

        tax    = tempu;
        tdx    = tempv;
        fakesi = ((uint32_t)(v - tempv)) >> 4u;
        tbp    = ((uint32_t)(u - tempu)) >> 4u;

        tcl >>= 1u;
        tch = _flares;
        if (tch & 1u) {
            goto c_transp;
        } else if (tch & 2u) {
            goto c_bright;
        } else if (tch & 4u) {
            goto c_merger;
        } else if (tch & 8u) {
            goto c_bumper;
        } else {
            goto c_internal;
        }

    c_internal:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tbh = tdh;
        fakedi += 2;
        tbl = tah;
        tch = adapted[0xFA00];
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)]; // NOTE; Fudge factor to account for
                                          // loss of offset on txtr.
        tax += tbp;
        adapted[fakedi + 2] = tch;
        adapted[fakedi + 3] = tch;
        tdx += fakesi;
        tcl--;
        if (tcl != 0)
            goto c_internal;
        goto c_common;

    c_transp:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tbh = tdh;
        fakedi += 2;
        tbl = tah;
        tch = adapted[fakedi + 3];
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)];
        tax += tbp;
        adapted[fakedi + 2] = tch;
        adapted[fakedi + 3] = tch;
        tdx += fakesi;
        tcl--;
        if (tcl != 0)
            goto c_transp;
        goto c_common;

    c_bright:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tch = adapted[fakedi + 4];
        tbh = tdh;
        fakedi += 2;
        tbl = tah;
        tch &= 0x3Fu;
        tax += tbp;
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)];
        tdx += fakesi;
        if (tch <= 0x3E)
            goto c_antibloom;
        tch = 0x3E;

    c_antibloom:
        adapted[fakedi + 2] &= 0xC0u;
        tch |= adapted[fakedi + 2];
        adapted[fakedi + 2] = tch;
        adapted[fakedi + 3] = tch;
        tcl--;
        if (tcl != 0)
            goto c_bright;
        goto c_common;

    c_merger:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tch = adapted[fakedi + 4];
        tbh = tdh;
        fakedi += 2;
        tbl = tah;
        tch &= 0x3Fu;
        tax += tbp;
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)];
        tch += adapted[0xFA00];
        tdx += fakesi;
        tch >>= 1u;
        adapted[fakedi + 2] &= 0xC0u;
        tch |= adapted[fakedi + 2];
        adapted[fakedi + 2] = tch;
        adapted[fakedi + 3] = tch;
        tcl--;
        if (tcl != 0)
            goto c_merger;
        goto c_common;

    c_bumper:
        tdh = ((uint16_t)(tdx >> 8u)) & 0xFFu;
        tah = ((uint16_t)(tax >> 8u)) & 0xFFu;

        tbh = tdh;
        fakedi += 2;
        tbl = tah;
        tch = adapted[0xFA00];
        tbx = (((uint16_t) tbh) << 8u) + tbl;
        tch += txtr[(uint16_t)(tbx - 4)];
        tax += tbp;
        adapted[fakedi + 2] = tch;
        adapted[fakedi + 3] = tch;
        tempfakedi          = fakedi;
        tempch              = tch;
        tch &= 0x07u;

    c_bmpm320:
        fakedi -= 320;
        tch--;
        if (!(((uint8_t)(tch >> 7u)) & 1u))
            goto c_bmpm320;
        tch = tempch;
        tch -= adapted[0xFA00];
        tch += adapted[0xFA01];
        tch += txtr[(uint16_t)(tbx - 4)];
        adapted[fakedi + 640 + 2] = tch;
        adapted[fakedi + 640 + 3] = tch;
        fakedi                    = tempfakedi;
        tdx += fakesi;
        tcl--;
        if (tcl != 0)
            goto c_bumper;

    c_common:
        fakedi = reallytempfakedi;
        fakedi += 32;
        goto c_row;

    // Inter-scanline code: between one scanline and the next.
    row_end:
        if (!(((uint8_t) halfscan) & 0x01u))
            goto do_singlescan;
        i++;
        if (i > max_y)
            return;
        tdx    = ipart[i - 2];
        tax    = fpart[i - 2];
        fakedi = 320 * i;
        if (tax <= tdx) {
            goto do_singlescan;
        }
        tax -= tdx;
        fakedi += tdx;

    duplicate:
        tdl                   = adapted[fakedi - 316];
        adapted[fakedi + 4]   = tdl;
        adapted[fakedi + 324] = tdl;
        fakedi++;
        tax--;
        if (tax != 0)
            goto duplicate;

    do_singlescan:
        i++;
    }
}

/* Causes the observer to advance
 * in the direction of flight of <delta> virtual units */
void forward(float delta) {
    cam_x -= delta * opt_tsinbeta * opt_tcosalfa;
    cam_z += delta * opt_tcosbeta * opt_tcosalfa;
    cam_y += delta * opt_tsinalfa;
}

int32_t _x_, _y_;

/* Calculate the coordinates on the screen of a point in space,
 * using the same calculation nucleus(unit? group?) of poly3d and polymap,
 * if the point re-enters the screen it returns 1, otherwise it returns 0.
 * The coordinates are then transferred in the variables _x_ and _y_.
 * The point should not be traced(drawn?) so it is not visible,
 * because the coordinates would be, in this(that?) case, indeterminable. */
int8_t get_coords(float x, float y, float z) {
    float rx, ry, rz, my, xx, yy, zz, z2;

    zz = z - cam_z;
    xx = x - cam_x;

    rx = (xx * opt_tcosbeta) + (zz * opt_tsinbeta);
    z2 = (zz * opt_tcosbeta) - (xx * opt_tsinbeta);

    yy = y - cam_y;

    rz = (yy * opt_tsinalfa) + (z2 * opt_tcosalfa);

    if (ngamma != 0) {
        my = (yy * opt_tcosalfa) - (z2 * opt_tsinalfa);
        ry = (my * opt_tcosngamma) - (rx * opt_tsinngamma);
        rx = (rx * opt_tcosngamma) + (my * opt_tsinngamma);
    } else {
        ry = (yy * opt_tcosalfa) - (z2 * opt_tsinalfa);
    }

    if (rz < uneg) {
        return 0;
    }

    my  = dpp / rz;
    _x_ = round(my * rx + x_centro_f);
    _y_ = round(my * ry + y_centro_f);

    if (_x_ > lbxl && _x_ < ubxl && _y_ > lbyl && _y_ < ubyl) {
        return 1;
    } else {
        return 0;
    }
}

// TODO; Fix.
bool facing(float *x, float *y, float *z) {
    /* Controls whether a single-sided polygon is visible or not.
     * Of course, as a procedure it is not so simple:
     * the surface normal must be calculated, even approximately;
     * however, always better than calculating the entire polygon. */

    /*float x1, y1, z1, x2, y2, z2, xr, yr, zr;

    x1 = *x - x[8];
    y1 = *y - y[8];
    z1 = *z - z[8];
    x2 = x[4] - x[8];
    y2 = y[4] - y[8];
    z2 = z[4] - z[8];

    xr = (z2 * y1) - (y2 *z1);
    yr = (z1 * x2) - (z2 * x1);
    zr = (x1 * y2) - (x2 * y1);

    if (((cam_x - x[8]) * xr) + ((cam_y - y[8]) * yr) + ((cam_z - z[8]) * zr) <
    0) { return 0;
    }*/

    return true;
}
