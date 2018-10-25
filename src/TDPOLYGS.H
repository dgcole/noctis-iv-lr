/*

    The Third Flare.
    ----------------
    Full-3D Graphic Engine.

    Funzioni a 32-bit per disegnare poligoni 3d riempiti di colore
    in grafica 320x200x256. Sul Pentium ä una cannonata: una media
    di 12000 poligoni al secondo, da workstation, con 75 MhZ.

    - Non si deve mai usare il colore nr. 255 per
      tracciare qualcosa nell'area di lavoro, quando si usa questa
      routine, perchÇ lo utilizza solo lei per delimitare i poligoni.
      Se si vuole usare un altro colore per delimitarli, bisogna
      cambiare tutti i valori 255 nelle funzioni "Segmento" e "poly3d".

    Chiamare initscanlines prima di tracciare alcunchä,
    sennï non traccia una bella sega.

    Nato (incredibile a dirsi) per Alpha Dream.
    Ultima revisione 21 Dicembre 1997.

    Aggiunte: ottimizzazione conversioni 3d-2d, 23.6.1997;
          ciclo di fast-load dei vertici quando sono tutti di fronte
          alla videocamera (cioä quasi sempre), 23.6.1997;
          clipping intelligente, ottobre '97;
          texture mapping, febbraio '98.

*/

#ifndef __FLOAT_H
#include <float.h>
#endif

#ifndef __ALLOC_H
#include <alloc.h>
#endif

#ifndef __MATH_H
#include <math.h>
#endif

#ifndef __IO_H
#include <io.h>
#endif

/* Dati sui poligoni (quanti vertici al massimo si pensa di fare). */

#ifndef VERTICI_PER_POLIGONO
#define VERTICI_PER_POLIGONO 4
#endif

/* Area di visualizzazione. */

#ifndef larghezza
#define larghezza 300
#endif

#ifndef altezza
#define altezza   180
#endif

#ifndef x_centro
#define x_centro  160
#endif

#ifndef y_centro
#define y_centro  100
#endif

/*

    Controllo visualizzazione.

                    */

float uneg = 100; /* Un fatto particolarmente curioso: uneg rappresenta
           la distanza minima alla quale un certo punto non viene
           considerato alle spalle dell'osservatore. Il bello ä
           che l'ideazione di questa sigla (ricordo che si
           pronuncia u-neg) risale a cosç tanto tempo fa
           (si parla della prima versione di Smallest, ovvero
           dell'aprile '92, attualmente pió di 5 anni fa)
           che non ricordo assolutamente che cosa significhi
           quest'acronimo (era un acronimo, ma chissÖ come mi
           venne in mente, forse da user-neg, negativo all'utente,
           in riferimento all'effetto di inversione del segno
           dato dalle funzioni prospettiche quando, per l'appunto,
           una tripletta di coordinate ha la distanza normale
           dallo schermo in negativo, ma non sono affatto sicuro. */

float alfa = 0, beta = 0, gamma = 0;
float cam_x = 0, cam_y = 0, cam_z = 0;

const double deg = M_PI / 180;

// Distanza dal piano di proiezione.

float dpp = 200;
float inv_dpp = 1 / dpp;

/* Costanti e variabili di controllo del texture mapping.
    H_MATRIXS e V_MATRIXS specificano le ripetizioni della stessa
    texture sui poligoni, ma per avere la possibilitÖ di dimezzare
    la texture o di disegnarne solo un quarto, sono state assunte
    come rappresentanti di "quarti di texture". Significa che
    per avere un texturing normale, senza ripetizioni nÇ
    dimezzamenti, bisogna assegnare le due variabili a 4,
    non a 1 (che rappresenterebbe un solo quarto).
    E cosç via... se si mette 8, si ottiene la ripetizione
    della texture per due volte sul corrispondente asse,
    se si mette a 12 si ottengono tre ripetizioni, eccetera...
    (ps ho cambiato la base a 16, sedicesimi di texture). */

const   MPIX          =                 319; // Massimo PIXEL su X.
const   MPIY          =                         199; // Massimo PIXEL su Y.
const   TEXTURE_XSIZE =                 256; // Larghezza delle BMP.
const   TEXTURE_YSIZE =                 256; // Altezza delle BMP.

float   EMU_K         =                      16; // Cost. di emulaz. FPU
long    H_MATRIXS     =                  16; // Nr. ripetizioni. 16-128
long    V_MATRIXS     =                  16; // Nr. ripetizioni. 16-128
long    XSIZE         =   TEXTURE_XSIZE * H_MATRIXS; // Calibraz. dimensioni.
long    YSIZE         =   TEXTURE_YSIZE * V_MATRIXS; // Calibraz. dimensioni.
float   XCOEFF        =                 EMU_K / dpp; // Coefficente di comodo.
float   YCOEFF        =                 EMU_K / dpp; // Coefficente di comodo.

// Inizializza indirizzi scanlines.

unsigned riga[200];

void initscanlines ()
{
    unsigned c;

    for (c=0; c<200; c++)
        riga[c] = 320 * c;

    _control87 (MCW_EM, MCW_EM); // disattiva i Floating Point Errors.
}

// Traccia un segmento senza effettuare controlli sui limiti. Pió veloce.
// Traccia con colore 255.
// Non effettua controlli, e quindi non va utilizzata per altre cose,
// o per lo meno bisogna stare attenti a far rientrare gli estremi del
// segmento nell'area video utilizzabile.
// Quella che effettua i controlli si trova nella funzione waveline di
// Liquid Player, ed ä sicura al 1000 per mille.

unsigned ptr;

unsigned long xp, yp, xa, ya;
unsigned long global_x, global_y;

void Segmento ()
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
       clu: asm {   mov byte ptr es:[si], 255
            add si, 320
            cmp si, pf
            jb clu }
        return;
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

trace:  asm les ax, dword ptr adapted;

    /*

        Nota importante:

            Tutte le operazioni precedute dal prefisso 0x66
            vanno considerate con operandi di dimensioni doppie.
            Difatti, poichÇ l'assemblatore in-line non supporta
            i registri a 32 bit, ä necessario aggiungere i
            prefissi d'estensione manualmente.
            Cosç facendo, i puntatori di tipo word (word ptr)
            vanno considerati come dword ptr, mentre i registri
            sono tutti estesi (per esempio, ax diventa eax).

    */

    asm {   db 0x66; mov ax, word ptr a    // passa in eax il delta_x (ovvero a).
        db 0x66; mov dx, word ptr b    // passa in edx il delta_y (ovvero b).
        db 0x66; mov cx, word ptr xa } // passa in ecx il limite superiore del ciclo (come coordinata x d'arrivo).

_do:    asm {   mov bx, word ptr global_y[2]
        mov di, word ptr global_x[2]
        add bx, bx
       db 0x66; add word ptr global_x, ax
        add di, word ptr riga[bx]
       db 0x66; add word ptr global_y, dx
        mov byte ptr es:[di+4], 255
       db 0x66; cmp word ptr global_x, cx
        jb  _do }
}

// La funzione di tracciamento viene principalmente usata da Noctis,
// ed una delle sue caratteristiche ä di poter fare poligoni semitrasparenti
// che simulano degli aloni luminosi: si attiva con il flag "flares".
// PerchÇ il disegno dei bordi (dei segmenti) non interferisca con tale
// operazione, serve una pagina sana, priva di bordi, diversa da quella su
// cui si va a tracciare.
// Per default, ä la seguente, posta a nulla perchÇ tdpolygs non si
// prepara subito a questa particolare funzione.

char flares = 0;

long mp[6*VERTICI_PER_POLIGONO];

unsigned max_x, max_y, min_x, min_y;

// Dati globali per conversioni, rototraslazioni e clipping.

char doflag;
int pvert, nvert, vvert;
int vr, vr2, vr3, vr4, vr5, vr6;

float zk;
float x2, y2, z2;
float xx, yy, zz;

/*

    Voglio annotarmi le sigle complicate, sennï finisce come per u-neg.

    doflag   = DO-(or-not)-for-each-polygon-FLAG.
           da quando c'ä il fast-load funge anche come contatore
           per i vertici da non ritagliare a livello 3d.
           infatti, se sono tutti in doflag, il poligono non
           interseca lo schermo e si puï lasciare com'ä, almeno
           a livello 3d.
    x2,y2,z2 = variabili di transito nelle rotazioni.
    pvert    = Previous-VERTex.
    nvert    = Next-VERTex.
    vvert    = bella domanda, mi sono scordato anche questa.
           venuto in mente: Visible VERTex, vertice visibile.
    zk       = Zeta-Constant... costante derivata dal calcolo della
           differenza tra coordinate zeta normalizzate allo schermo,
           viene usata nel clipping a livello 3d dalla funz. "poly3d".
           in realtÖ ä una costante solo per due equazioni,
           ma ä meglio calcolarla una volta sola che due.

    xx,yy,zz = in questa inclusione non sono mai usate, ma ci sono sempre
           state perchÇ una volta servivano a qualcosa (non ricordo
           per nulla a cosa). attualmente, devono rimanerci perchÇ
           molti programmi le usano come variabili temporanee.

    pun = PUNto, ä un contatore/non esiste pió dacchÇ ho tradotto in asm.
    rxf = Rototraslated-X-Floating-point-value.
    rwf = Rototraslated-vieW-(or-not)-Flag.
    mp  = Matrice Punti.
    lbx = LowerBound-X.
    ubx = UpperBound-X.

    opt_tsinalfa = OPTimized-Table-of-SINe-for-ALFA-angle.
    opt_psinalfa = OPTimized-Projected-table-of-SINe-for-ALFA-angle.

*/

char rwf[VERTICI_PER_POLIGONO];

float rxf[VERTICI_PER_POLIGONO];
float ryf[VERTICI_PER_POLIGONO];
float rzf[VERTICI_PER_POLIGONO];

// Limiti dell'area video rielaborati.

#define lbx -larghezza/2 + x_centro
#define ubx larghezza/2 + x_centro
#define lby -altezza/2 + y_centro
#define uby altezza/2 + y_centro

long lbxl = lbx;
long ubxl = ubx;
long lbyl = lby;
long ubyl = uby;

float lbxf = lbx;
float ubxf = ubx;
float lbyf = lby;
float ubyf = uby;

float x_centro_f = x_centro;
float y_centro_f = y_centro;

// Chiamare dopo aver cambiato l'angolo visuale.
// Aggiorna le seguenti variabili di ottimizzazione, usate da poly3d.

float opt_pcosbeta = dpp;
float opt_psinbeta = 0;
float opt_tcosbeta = 1;
float opt_tsinbeta = 0;
float opt_pcosalfa = dpp;
float opt_psinalfa = 0;
float opt_tcosalfa = 1;
float opt_tsinalfa = 0;

float opt_tcosgamma = 1;
float opt_tsingamma = 0;

void change_angle_of_view ()
{
    opt_pcosbeta = cos (beta*deg) * dpp;
    opt_psinbeta = sin (beta*deg) * dpp;
    opt_tcosbeta = cos (beta*deg);
    opt_tsinbeta = sin (beta*deg);
    opt_pcosalfa = cos (alfa*deg) * dpp; // 0.833
    opt_psinalfa = sin (alfa*deg) * dpp; // 0.833
    opt_tcosalfa = cos (alfa*deg);
    opt_tsinalfa = sin (alfa*deg);

    opt_tcosgamma = cos (gamma*deg);
    opt_tsingamma = sin (gamma*deg);
}

// Chiamare dopo aver cambiato dpp.
// Cambia l'obiettivo della videocamera.

void change_camera_lens ()
{
    inv_dpp = 1 / dpp;

    XCOEFF = EMU_K / dpp;
    YCOEFF = EMU_K / dpp;

    change_angle_of_view ();
}

// Chiamare dopo aver cambiato V_MATRIXS o H_MATRIXS.
// Aggiorna le variabili di lavoro per il texture mapping.

void change_txm_repeating_mode ()
{
    XSIZE = TEXTURE_XSIZE * H_MATRIXS;
    YSIZE = TEXTURE_YSIZE * V_MATRIXS;
}

/* Questa ä la funzione da invocare per ogni poligono da tracciare.

    E` un vero capolavoro: nessun problema, massima ottimizzazione,
    al 99% puro assembly per coprocessori da 387 in su e codice 32-bit,
    probabilmente la pió complessa e bella funzione ch'io abbia mai
    partorito.

    Chiunque tenterÖ di capirci qualcosa rimarrÖ molto scoraggiato.
    Lungo e complesso, ma provate ad eseguirlo ed a monitorarne il flusso:
    vi accorgerete della sua enorme agilitÖ. */

float uno = 1; // sempre uno: ä una costante di comodo.

unsigned char entity = 1; /* controlla quantitÖ generiche nel riempimento
                 dei poligoni con alcuni effetti speciali. */

void poly3d (float *x, float *y, float *z,
         unsigned nrv, unsigned char colore)
{
    unsigned _8n;
        unsigned char ent = entity;

    // Matrici 3d: tutto sullo stack.

    float ultima_x[2*VERTICI_PER_POLIGONO];
    float ultima_y[2*VERTICI_PER_POLIGONO];
    float ultima_z[2*VERTICI_PER_POLIGONO];

    // Matrici 2d: idem come sopra.

    float video_x0[2*VERTICI_PER_POLIGONO], video_y0[2*VERTICI_PER_POLIGONO];
    float video_x1[3*VERTICI_PER_POLIGONO], video_y1[3*VERTICI_PER_POLIGONO];
    float video_x2[4*VERTICI_PER_POLIGONO], video_y2[4*VERTICI_PER_POLIGONO];
    float video_x3[6*VERTICI_PER_POLIGONO], video_y3[6*VERTICI_PER_POLIGONO];

    // Rototraslazione dei vertici; i dati rimangono ancora 3d.

                    doflag = 0;

                asm {   xor di, di
                    xor si, si }
               vertex:  asm {   les bx, dword ptr z
                    fld dword ptr es:[bx+si]
                    fsub cam_z
                    fst zz
                    fmul opt_psinbeta
                    les bx, dword ptr x
                    fld dword ptr es:[bx+si]
                    fsub cam_x
                    fst xx
                    fmul opt_pcosbeta
                    faddp
                    fstp dword ptr rxf[si]
                    fld zz
                    fmul opt_tcosbeta
                    fld xx
                    fmul opt_tsinbeta
                    fsubp
                    fst z2
                    fmul opt_tcosalfa
                    les bx, dword ptr y
                    fld dword ptr es:[bx+si]
                    fsub cam_y
                    fst yy
                    fmul opt_tsinalfa
                    faddp
                    fst dword ptr rzf[si]
                    fcomp uneg
                    fstsw ax
                    fld yy
                    fmul opt_pcosalfa
                    fld z2
                    fmul opt_psinalfa
                    fsubp
                    fstp dword ptr ryf[si]
                    sahf
                    jb rzf_min_uneg
                    inc doflag
                    mov byte ptr rwf[di], 1
                    jmp convert }
            rzf_min_uneg: asm   mov byte ptr rwf[di], 0
            convert:      asm { add si, 4
                    inc di
                    cmp di, nrv
                    je end_convert
                    jmp vertex }

            end_convert:        if (!doflag) return;

    // Fast-load per poligoni completamente visibili.

                    if (doflag==nrv) {
                        asm {   xor si, si
                            mov cx, nrv
                            mov vr2, cx }
                    load:   asm {   db 0x66; mov ax, word ptr rxf[si]
                            db 0x66; mov bx, word ptr ryf[si]
                            db 0x66; mov dx, word ptr rzf[si]
                            db 0x66; mov word ptr ultima_x[si], ax
                            db 0x66; mov word ptr ultima_y[si], bx
                            db 0x66; mov word ptr ultima_z[si], dx
                            add si, 4
                            dec cx
                            jnz load }
                        goto to_2d;
                    }

    /* Conversione punti alle spalle dell'osservatore
       rispetto al piano dello schermo. */

                    asm {   mov vr, 0
                        xor di, di
                        mov dx, nrv
                        dec dx }
                 the_for_1: asm {   mov si, vr
                        cmp byte ptr rwf[si], 0
                        je CONT1
                        jmp bypass }
                  CONT1:    asm {   mov ax, vr
                        sub ax, 1
                        jnc pvert1ok
                        mov pvert, dx
                        jmp pvert1no }
                  pvert1ok: asm     mov pvert, ax
                  pvert1no: asm {   mov ax, vr
                        inc ax
                        cmp ax, dx
                        jbe nvert1ok
                        mov nvert, 0
                        jmp nvert1no }
                  nvert1ok: asm     mov nvert, ax
                  nvert1no: asm {   mov si, pvert
                        cmp byte ptr rwf[si], 0
                        je ctrl1
                        jmp JMPR11 }
                  ctrl1:    asm {   mov si, nvert
                        cmp byte ptr rwf[si], 0
                        jne JMPR11
                        jmp STOP1 }
                  JMPR11:   asm {   mov bx, vr
                        shl bx, 2
                        mov si, pvert
                        mov al, byte ptr rwf[si]
                        mov si, nvert
                        add al, byte ptr rwf[si]
                        cmp al, 2
                        je if11
                        jmp else11 }
                  if11:     asm {   shl pvert, 2
                        shl nvert, 2
                        mov si, bx
                        fld dword ptr rzf[si]
                        mov si, pvert
                        fcomp dword ptr rzf[si]
                        fstsw ax
                        sahf
                        jne if12
                        jmp else12 }
                  if12:     asm {   fld dword ptr uneg
                        fsub dword ptr rzf[si]
                        fld dword ptr rzf[si]
                        mov si, bx
                        fsubr dword ptr rzf[si]
                        fdivp
                        fst zk
                        fld dword ptr rxf[si]
                        mov si, pvert
                        fsub dword ptr rxf[si]
                        fmulp
                        fadd dword ptr rxf[si]
                        fstp dword ptr ultima_x[di]
                        fld zk
                        mov si, bx
                        fld dword ptr ryf[si]
                        mov si, pvert
                        fsub dword ptr ryf[si]
                        fmulp
                        fadd dword ptr ryf[si]
                        fstp dword ptr ultima_y[di]
                        jmp JMPR12 }
                  else12:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr rxf[si]
                        db 0x66; mov word ptr ultima_x[di], ax
                        db 0x66; mov ax, word ptr ryf[si]
                        db 0x66; mov word ptr ultima_y[di], ax }
                  JMPR12:   asm {   db 0x66; mov ax, word ptr uneg
                        db 0x66; mov word ptr ultima_z[di], ax
                        mov si, bx
                        fld dword ptr rzf[si]
                        mov si, nvert
                        fcomp dword ptr rzf[si]
                        fstsw ax
                        sahf
                        jne neq1
                        jmp eq1 }
                  neq1:     asm {   fld dword ptr uneg
                        fsub dword ptr rzf[si]
                        fld dword ptr rzf[si]
                        mov si, bx
                        fsubr dword ptr rzf[si]
                        fdivp
                        fst zk
                        fld dword ptr rxf[si]
                        mov si, nvert
                        fsub dword ptr rxf[si]
                        fmulp
                        fadd dword ptr rxf[si]
                        fstp dword ptr ultima_x[di+4]
                        fld zk
                        mov si, bx
                        fld dword ptr ryf[si]
                        mov si, nvert
                        fsub dword ptr ryf[si]
                        fmulp
                        fadd dword ptr ryf[si]
                        fstp dword ptr ultima_y[di+4]
                        jmp JMPR13 }
                  eq1:      asm {   mov si, bx
                        db 0x66; mov ax, word ptr rxf[si]
                        db 0x66; mov word ptr ultima_x[di+4], ax
                        db 0x66; mov ax, word ptr ryf[si]
                        db 0x66; mov word ptr ultima_y[di+4], ax }
                  JMPR13:   asm {   db 0x66; mov ax, word ptr uneg
                        db 0x66; mov word ptr ultima_z[di+4], ax
                        add di, 8
                        jmp STOP1 }
                  else11:   asm {   mov si, pvert
                        cmp byte ptr rwf[si], 0
                        jne vpvert1
                        mov ax, nvert
                        mov vvert, ax
                        jmp vnvert1 }
                  vpvert1:  asm {   mov ax, pvert
                        mov vvert, ax }
                  vnvert1:  asm {   shl vvert, 2
                        mov si, bx
                        fld dword ptr rzf[si]
                        mov si, vvert
                        fcomp dword ptr rzf[si]
                        fstsw ax
                        sahf
                        jne neq2
                        jmp eq2 }
                  neq2:     asm {   fld dword ptr uneg
                        fsub dword ptr rzf[si]
                        fld dword ptr rzf[si]
                        mov si, bx
                        fsubr dword ptr rzf[si]
                        fdivp
                        fst zk
                        fld dword ptr rxf[si]
                        mov si, vvert
                        fsub dword ptr rxf[si]
                        fmulp
                        fadd dword ptr rxf[si]
                        fstp dword ptr ultima_x[di]
                        fld zk
                        mov si, bx
                        fld dword ptr ryf[si]
                        mov si, vvert
                        fsub dword ptr ryf[si]
                        fmulp
                        fadd dword ptr ryf[si]
                        fstp dword ptr ultima_y[di]
                        jmp JMPR14 }
                  eq2:      asm {   mov si, bx
                        db 0x66; mov ax, word ptr rxf[si]
                        db 0x66; mov word ptr ultima_x[di], ax
                        db 0x66; mov ax, word ptr ryf[si]
                        db 0x66; mov word ptr ultima_y[di], ax }
                  JMPR14:   asm {   db 0x66; mov ax, word ptr uneg
                        db 0x66; mov word ptr ultima_z[di], ax
                        add di, 4
                        jmp STOP1 }
                  bypass:   asm {   shl si, 2
                        db 0x66; mov ax, word ptr rxf[si]
                        db 0x66; mov word ptr ultima_x[di], ax
                        db 0x66; mov ax, word ptr ryf[si]
                        db 0x66; mov word ptr ultima_y[di], ax
                        db 0x66; mov ax, word ptr rzf[si]
                        db 0x66; mov word ptr ultima_z[di], ax
                        add di, 4 }
                  STOP1:    asm {   inc vr
                        mov ax, vr
                        cmp ax, nrv
                        jnb cutting_end_1
                        jmp the_for_1 }

             cutting_end_1: asm {   mov ax, di
                        shr ax, 2
                        mov vr2, ax }

                if (vr2<3) return;

       // Queste sono le proiezioni prospettiche da 3d a 2d.
       // E` stato incluso in data 6.12.97 anche un piccolo esame
       // dei minimi e massimi grafici. Questo fa sç che i poligoni
       // che rientrano nei limiti del video non vengano esaminati
       // dalle funzioni di clipping 2-d. E` pió intelligente.
       // Prima d'ora, il ciclo di ricerca minimi-massimi era in fondo,
       // e veniva eseguito dopo il clipping 2d, che perï ä lungo
       // e complicato: non ä quindi una cosa da fare sempre.

                 to_2d: asm {   db 0x66; mov ax, word ptr lbxl
                        db 0x66; mov bx, word ptr lbyl
                        db 0x66; mov cx, word ptr ubxl
                        db 0x66; mov dx, word ptr ubyl
                        mov si, vr2
                        dec si
                        shl si, 2
                        mov di, si
                        add di, si
                        mov _8n, di }
                 projector: asm {   fld uno
                        fdiv dword ptr ultima_z[si]
                        fld st(0)
                        fmul dword ptr ultima_x[si]
                        fadd dword ptr x_centro_f
                        fst dword ptr video_x0[si]
                        fistp dword ptr mp[di]
                        db 0x66; cmp word ptr mp[di], cx
                        jnl outr_1
                        db 0x66; mov cx, word ptr mp[di] }
                 outr_1:    asm {   db 0x66; cmp word ptr mp[di], ax
                        jle outr_2
                        db 0x66; mov ax, word ptr mp[di] }
                 outr_2:    asm {   fmul dword ptr ultima_y[si]
                        fadd dword ptr y_centro_f
                        fst dword ptr video_y0[si]
                        fistp dword ptr mp[di+4]
                        db 0x66; cmp word ptr mp[di+4], dx
                        jnl outr_3
                        db 0x66; mov dx, word ptr mp[di+4] }
                 outr_3:    asm {   db 0x66; cmp word ptr mp[di+4], bx
                        jle outr_4
                        db 0x66; mov bx, word ptr mp[di+4] }
                 outr_4:    asm {   sub di, 8
                        sub si, 4
                        jnc projector
                        mov max_x, ax
                        mov max_y, bx
                        mov min_x, cx
                        mov min_y, dx
                        xor si, si
                        db 0x66; cmp ax, word ptr ubxl
                        jl ranged1
                        inc si
                        mov max_x, ubx }
                 ranged1:   asm {   db 0x66; cmp bx, word ptr ubyl
                        jl ranged2
                        inc si
                        mov max_y, uby }
                 ranged2:   asm {   db 0x66; cmp cx, word ptr lbxl
                        jnl ranged3
                        inc si
                        mov min_x, lbx }
                 ranged3:   asm {   db 0x66; cmp dx, word ptr lbyl
                        jnl ranged4
                        inc si
                        mov min_y, lby }
                 ranged4:   asm {   test si, si
                        jnz yes_clip
                        jmp drawb }

       /* Conversione dei punti che risiedono al di fuori dell'area
          visibile. Questi punti devono essere ridimensionati per
          rientrare in tale area per evitare poligoni troppo grandi,
          che oltre a rallentare notevolmente il tracciamento provocano
          il blocco di sistema invadendo aree di memoria non-video.
          In questa sezione i dati sui vertici del poligono da tracciare
          vengono rimaneggiati a livello bidimensionale, aggiungendo
          eventuali vertici per "ritagliare" solo la parte di poligono
          visibile. */

       // Lato superiore del video.

                  yes_clip: asm {   mov vr, 0
                        xor di, di
                        mov dx, vr2
                        dec dx }
                  the_for_2:asm {   mov si, vr
                        shl si, 2
                        fld dword ptr video_y0[si]
                        fcomp dword ptr lbyf
                        fstsw ax
                        sahf
                        jb if21
                        jmp else21 }
                  if21:     asm {   mov bx, si
                        mov ax, vr
                        sub ax, 1
                        jnc pvert2ok
                        mov pvert, dx
                        jmp pvert2no }
                  pvert2ok: asm     mov pvert, ax
                  pvert2no: asm {   mov ax, vr
                        inc ax
                        cmp ax, dx
                        jbe nvert2ok
                        mov nvert, 0
                        jmp nvert2no }
                  nvert2ok: asm     mov nvert, ax
                  nvert2no: asm {   shl pvert, 2
                        shl nvert, 2
                        mov si, pvert
                        fld dword ptr video_y0[si]
                        fcomp dword ptr lbyf
                        fstsw ax
                        sahf
                        jae CONT2
                        mov si, nvert
                        fld dword ptr video_y0[si]
                        fcomp dword ptr lbyf
                        fstsw ax
                        sahf
                        jae CONT2
                        jmp STOP2 }
                  CONT2:    asm {   mov si, pvert
                        fld dword ptr video_y0[si]
                        fcomp dword ptr lbyf
                        fstsw ax
                        sahf
                        jae ctrl22
                        jmp else22 }
                  ctrl22:   asm {   mov si, nvert
                        fld dword ptr video_y0[si]
                        fcomp dword ptr lbyf
                        fstsw ax
                        sahf
                        jae if22
                        jmp else22 }
                  if22:     asm {   mov si, bx
                        fld dword ptr video_y0[si]
                        mov si, pvert
                        fcomp dword ptr video_y0[si]
                        fstsw ax
                        sahf
                        jne if23
                        jmp else23 }
                  if23:     asm {   fld dword ptr lbyf
                        fsub dword ptr video_y0[si]
                        fld dword ptr video_y0[si]
                        mov si, bx
                        fsubr dword ptr video_y0[si]
                        fdivp
                        fld dword ptr video_x0[si]
                        mov si, pvert
                        fsub dword ptr video_x0[si]
                        fmulp
                        fadd dword ptr video_x0[si]
                        fstp dword ptr video_x1[di]
                        jmp JMPR23 }
                  else23:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_x0[si]
                        db 0x66; mov word ptr video_x1[di], ax }
                  JMPR23:   asm {   db 0x66; mov ax, word ptr lbyf
                        db 0x66; mov word ptr video_y1[di], ax
                        mov si, bx
                        fld dword ptr video_y0[si]
                        mov si, nvert
                        fcomp dword ptr video_y0[si]
                        fstsw ax
                        sahf
                        jne if24
                        jmp else24 }
                  if24:     asm {   fld dword ptr lbyf
                        fsub dword ptr video_y0[si]
                        fld dword ptr video_y0[si]
                        mov si, bx
                        fsubr dword ptr video_y0[si]
                        fdivp
                        fld dword ptr video_x0[si]
                        mov si, nvert
                        fsub dword ptr video_x0[si]
                        fmulp
                        fadd dword ptr video_x0[si]
                        fstp dword ptr video_x1[di+4]
                        jmp JMPR22 }
                  else24:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_x0[si]
                        db 0x66; mov word ptr video_x1[di+4], ax }
                  JMPR22:   asm {   db 0x66; mov ax, word ptr lbyf
                        db 0x66; mov word ptr video_y1[di+4], ax
                        add di, 8
                        jmp STOP2 }
                  else22:   asm {   mov si, pvert
                        fld dword ptr video_y0[si]
                        fcomp dword ptr lbyf
                        fstsw ax
                        sahf
                        jb vnvert2
                        mov ax, pvert
                        mov vvert, ax
                        jmp vpvert2 }
                  vnvert2:  asm {   mov ax, nvert
                        mov vvert, ax }
                  vpvert2:  asm {   mov si, bx
                        fld dword ptr video_y0[si]
                        mov si, vvert
                        fcomp dword ptr video_y0[si]
                        fstsw ax
                        sahf
                        jne if25
                        jmp else35 }
                  if25:     asm {   fld dword ptr lbyf
                        fsub dword ptr video_y0[si]
                        fld dword ptr video_y0[si]
                        mov si, bx
                        fsubr dword ptr video_y0[si]
                        fdivp
                        fld dword ptr video_x0[si]
                        mov si, vvert
                        fsub dword ptr video_x0[si]
                        fmulp
                        fadd dword ptr video_x0[si]
                        fstp dword ptr video_x1[di]
                        jmp JMPR21 }
                  else25:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_x0[si]
                        db 0x66; mov word ptr video_x1[di], ax }
                  JMPR21:   asm {   db 0x66; mov ax, word ptr lbyf
                        db 0x66; mov word ptr video_y1[di], ax
                        add di, 4
                        jmp STOP2 }
                  else21:   asm {   db 0x66; mov ax, word ptr video_y0[si]
                        db 0x66; mov word ptr video_y1[di], ax
                        db 0x66; mov ax, word ptr video_x0[si]
                        db 0x66; mov word ptr video_x1[di], ax
                        add di, 4 }
                  STOP2:    asm {   inc vr
                        mov ax, vr
                        cmp ax, vr2
                        jnb cutting_end_2
                        jmp the_for_2 }

             cutting_end_2: asm {   mov ax, di
                        shr ax, 2
                        mov vr3, ax }

                    if (vr3<3) return;

       // Lato inferiore del video.

                    asm {   mov vr, 0
                        xor di, di
                        mov dx, vr3
                        dec dx }
                  the_for_3:asm {   mov si, vr
                        shl si, 2
                        fld dword ptr video_y1[si]
                        fcomp dword ptr ubyf
                        fstsw ax
                        sahf
                        ja if31
                        jmp else31 }
                  if31:     asm {   mov bx, si
                        mov ax, vr
                        sub ax, 1
                        jnc pvert3ok
                        mov pvert, dx
                        jmp pvert3no }
                  pvert3ok: asm     mov pvert, ax
                  pvert3no: asm {   mov ax, vr
                        inc ax
                        cmp ax, dx
                        jbe nvert3ok
                        mov nvert, 0
                        jmp nvert3no }
                  nvert3ok: asm     mov nvert, ax
                  nvert3no: asm {   shl pvert, 2
                        shl nvert, 2
                        mov si, pvert
                        fld dword ptr video_y1[si]
                        fcomp dword ptr ubyf
                        fstsw ax
                        sahf
                        jbe CONT3
                        mov si, nvert
                        fld dword ptr video_y1[si]
                        fcomp dword ptr ubyf
                        fstsw ax
                        sahf
                        jbe CONT3
                        jmp STOP3 }
                  CONT3:    asm {   mov si, pvert
                        fld dword ptr video_y1[si]
                        fcomp dword ptr ubyf
                        fstsw ax
                        sahf
                        jbe ctrl32
                        jmp else32 }
                  ctrl32:   asm {   mov si, nvert
                        fld dword ptr video_y1[si]
                        fcomp dword ptr ubyf
                        fstsw ax
                        sahf
                        jbe if32
                        jmp else32 }
                  if32:     asm {   mov si, bx
                        fld dword ptr video_y1[si]
                        mov si, pvert
                        fcomp dword ptr video_y1[si]
                        fstsw ax
                        sahf
                        jne if33
                        jmp else33 }
                  if33:     asm {   fld dword ptr ubyf
                        fsub dword ptr video_y1[si]
                        fld dword ptr video_y1[si]
                        mov si, bx
                        fsubr dword ptr video_y1[si]
                        fdivp
                        fld dword ptr video_x1[si]
                        mov si, pvert
                        fsub dword ptr video_x1[si]
                        fmulp
                        fadd dword ptr video_x1[si]
                        fstp dword ptr video_x2[di]
                        jmp JMPR33 }
                  else33:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_x1[si]
                        db 0x66; mov word ptr video_x2[di], ax }
                  JMPR33:   asm {   db 0x66; mov ax, word ptr ubyf
                        db 0x66; mov word ptr video_y2[di], ax
                        mov si, bx
                        fld dword ptr video_y1[si]
                        mov si, nvert
                        fcomp dword ptr video_y1[si]
                        fstsw ax
                        sahf
                        jne if34
                        jmp else34 }
                  if34:     asm {   fld dword ptr ubyf
                        fsub dword ptr video_y1[si]
                        fld dword ptr video_y1[si]
                        mov si, bx
                        fsubr dword ptr video_y1[si]
                        fdivp
                        fld dword ptr video_x1[si]
                        mov si, nvert
                        fsub dword ptr video_x1[si]
                        fmulp
                        fadd dword ptr video_x1[si]
                        fstp dword ptr video_x2[di+4]
                        jmp JMPR32 }
                  else34:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_x1[si]
                        db 0x66; mov word ptr video_x2[di+4], ax }
                  JMPR32:   asm {   db 0x66; mov ax, word ptr ubyf
                        db 0x66; mov word ptr video_y2[di+4], ax
                        add di, 8
                        jmp STOP3 }
                  else32:   asm {   mov si, pvert
                        fld dword ptr video_y1[si]
                        fcomp dword ptr ubyf
                        fstsw ax
                        sahf
                        ja vnvert3
                        mov ax, pvert
                        mov vvert, ax
                        jmp vpvert3 }
                  vnvert3:  asm {   mov ax, nvert
                        mov vvert, ax }
                  vpvert3:  asm {   mov si, bx
                        fld dword ptr video_y1[si]
                        mov si, vvert
                        fcomp dword ptr video_y1[si]
                        fstsw ax
                        sahf
                        jne if35
                        jmp else35 }
                  if35:     asm {   fld dword ptr ubyf
                        fsub dword ptr video_y1[si]
                        fld dword ptr video_y1[si]
                        mov si, bx
                        fsubr dword ptr video_y1[si]
                        fdivp
                        fld dword ptr video_x1[si]
                        mov si, vvert
                        fsub dword ptr video_x1[si]
                        fmulp
                        fadd dword ptr video_x1[si]
                        fstp dword ptr video_x2[di]
                        jmp JMPR31 }
                  else35:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_x1[si]
                        db 0x66; mov word ptr video_x2[di], ax }
                  JMPR31:   asm {   db 0x66; mov ax, word ptr ubyf
                        db 0x66; mov word ptr video_y2[di], ax
                        add di, 4
                        jmp STOP3 }
                  else31:   asm {   db 0x66; mov ax, word ptr video_y1[si]
                        db 0x66; mov word ptr video_y2[di], ax
                        db 0x66; mov ax, word ptr video_x1[si]
                        db 0x66; mov word ptr video_x2[di], ax
                        add di, 4 }
                  STOP3:    asm {   inc vr
                        mov ax, vr
                        cmp ax, vr3
                        jnb cutting_end_3
                        jmp the_for_3 }

             cutting_end_3: asm {   mov ax, di
                        shr ax, 2
                        mov vr4, ax }

                    if (vr4<3) return;

       // Lato sinistro del video.

                    asm {   mov vr, 0
                        xor di, di
                        mov dx, vr4
                        dec dx }
                  the_for_4:asm {   mov si, vr
                        shl si, 2
                        fld dword ptr video_x2[si]
                        fcomp dword ptr lbxf
                        fstsw ax
                        sahf
                        jb if41
                        jmp else41 }
                  if41:     asm {   mov bx, si
                        mov ax, vr
                        sub ax, 1
                        jnc pvert4ok
                        mov pvert, dx
                        jmp pvert4no }
                  pvert4ok: asm     mov pvert, ax
                  pvert4no: asm {   mov ax, vr
                        inc ax
                        cmp ax, dx
                        jbe nvert4ok
                        mov nvert, 0
                        jmp nvert4no }
                  nvert4ok: asm     mov nvert, ax
                  nvert4no: asm {   shl pvert, 2
                        shl nvert, 2
                        mov si, pvert
                        fld dword ptr video_x2[si]
                        fcomp dword ptr lbxf
                        fstsw ax
                        sahf
                        jae CONT4
                        mov si, nvert
                        fld dword ptr video_x2[si]
                        fcomp dword ptr lbxf
                        fstsw ax
                        sahf
                        jae CONT4
                        jmp STOP4 }
                  CONT4:    asm {   mov si, pvert
                        fld dword ptr video_x2[si]
                        fcomp dword ptr lbxf
                        fstsw ax
                        sahf
                        jae ctrl42
                        jmp else42 }
                  ctrl42:   asm {   mov si, nvert
                        fld dword ptr video_x2[si]
                        fcomp dword ptr lbxf
                        fstsw ax
                        sahf
                        jae if42
                        jmp else42 }
                  if42:     asm {   mov si, bx
                        fld dword ptr video_x2[si]
                        mov si, pvert
                        fcomp dword ptr video_x2[si]
                        fstsw ax
                        sahf
                        jne if43
                        jmp else43 }
                  if43:     asm {   fld dword ptr lbxf
                        fsub dword ptr video_x2[si]
                        fld dword ptr video_x2[si]
                        mov si, bx
                        fsubr dword ptr video_x2[si]
                        fdivp
                        fld dword ptr video_y2[si]
                        mov si, pvert
                        fsub dword ptr video_y2[si]
                        fmulp
                        fadd dword ptr video_y2[si]
                        fstp dword ptr video_y3[di]
                        jmp JMPR43 }
                  else43:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_y2[si]
                        db 0x66; mov word ptr video_y3[di], ax }
                  JMPR43:   asm {   db 0x66; mov ax, word ptr lbxf
                        db 0x66; mov word ptr video_x3[di], ax
                        mov si, bx
                        fld dword ptr video_x2[si]
                        mov si, nvert
                        fcomp dword ptr video_x2[si]
                        fstsw ax
                        sahf
                        jne if44
                        jmp else44 }
                  if44:     asm {   fld dword ptr lbxf
                        fsub dword ptr video_x2[si]
                        fld dword ptr video_x2[si]
                        mov si, bx
                        fsubr dword ptr video_x2[si]
                        fdivp
                        fld dword ptr video_y2[si]
                        mov si, nvert
                        fsub dword ptr video_y2[si]
                        fmulp
                        fadd dword ptr video_y2[si]
                        fstp dword ptr video_y3[di+4]
                        jmp JMPR42 }
                  else44:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_y2[si]
                        db 0x66; mov word ptr video_y3[di+4], ax }
                  JMPR42:   asm {   db 0x66; mov ax, word ptr lbxf
                        db 0x66; mov word ptr video_x3[di+4], ax
                        add di, 8
                        jmp STOP4 }
                  else42:   asm {   mov si, pvert
                        fld dword ptr video_x2[si]
                        fcomp dword ptr lbxf
                        fstsw ax
                        sahf
                        jb vnvert4
                        mov ax, pvert
                        mov vvert, ax
                        jmp vpvert4 }
                  vnvert4:  asm {   mov ax, nvert
                        mov vvert, ax }
                  vpvert4:  asm {   mov si, bx
                        fld dword ptr video_x2[si]
                        mov si, vvert
                        fcomp dword ptr video_x2[si]
                        fstsw ax
                        sahf
                        jne if45
                        jmp else45 }
                  if45:     asm {   fld dword ptr lbxf
                        fsub dword ptr video_x2[si]
                        fld dword ptr video_x2[si]
                        mov si, bx
                        fsubr dword ptr video_x2[si]
                        fdivp
                        fld dword ptr video_y2[si]
                        mov si, vvert
                        fsub dword ptr video_y2[si]
                        fmulp
                        fadd dword ptr video_y2[si]
                        fstp dword ptr video_y3[di]
                        jmp JMPR41 }
                  else45:   asm {   mov si, bx
                        db 0x66; mov ax, word ptr video_y2[si]
                        db 0x66; mov word ptr video_y3[di], ax }
                  JMPR41:   asm {   db 0x66; mov ax, word ptr lbxf
                        db 0x66; mov word ptr video_x3[di], ax
                        add di, 4
                        jmp STOP4 }
                  else41:   asm {   db 0x66; mov ax, word ptr video_x2[si]
                        db 0x66; mov word ptr video_x3[di], ax
                        db 0x66; mov ax, word ptr video_y2[si]
                        db 0x66; mov word ptr video_y3[di], ax
                        add di, 4 }
                  STOP4:    asm {   inc vr
                        mov ax, vr
                        cmp ax, vr4
                        jnb cutting_end_4
                        jmp the_for_4 }

             cutting_end_4: asm {   mov ax, di
                        shr ax, 2
                        mov vr5, ax }

                    if (vr5<3) return;

       // Lato destro del video.

                    asm {   mov vr, 0
                        xor di, di // vr6 * 4
                        mov dx, vr5
                        dec dx } // vr5 - 1
                  the_for_5:asm {   mov si, vr
                        shl si, 2
                        fld dword ptr video_x3[si]
                        fcomp dword ptr ubxf
                        fstsw ax
                        sahf
                        ja if51
                        jmp else51 }
                  if51:     asm {   mov bx, si // costante vr * 4
                        mov ax, vr
                        sub ax, 1
                        jnc pvert5ok
                        mov pvert, dx
                        jmp pvert5no }
                  pvert5ok: asm     mov pvert, ax
                  pvert5no: asm {   mov ax, vr
                        inc ax
                        cmp ax, dx
                        jbe nvert5ok
                        mov nvert, 0
                        jmp nvert5no }
                  nvert5ok: asm     mov nvert, ax
                  nvert5no: asm {   shl pvert, 2
                        shl nvert, 2
                        mov si, pvert
                        fld dword ptr video_x3[si]
                        fcomp dword ptr ubxf
                        fstsw ax
                        sahf
                        jbe CONT5
                        mov si, nvert
                        fld dword ptr video_x3[si]
                        fcomp dword ptr ubxf
                        fstsw ax
                        sahf
                        jbe CONT5
                        jmp STOP5 }
                  CONT5:    asm {   mov si, pvert
                        fld dword ptr video_x3[si]
                        fcomp dword ptr ubxf
                        fstsw ax
                        sahf
                        jbe ctrl52
                        jmp else52 }
                  ctrl52:   asm {   mov si, nvert
                        fld dword ptr video_x3[si]
                        fcomp dword ptr ubxf
                        fstsw ax
                        sahf
                        jbe if52
                        jmp else52 }
                  if52:     asm {   mov si, bx
                        fld dword ptr video_x3[si]
                        mov si, pvert
                        fcomp dword ptr video_x3[si]
                        fstsw ax
                        sahf
                        jne if53
                        jmp else53 }
                  if53:     asm {   fld dword ptr ubxf
                        fsub dword ptr video_x3[si]
                        fld dword ptr video_x3[si]
                        mov si, bx
                        fsubr dword ptr video_x3[si]
                        fdivp
                        fld dword ptr video_y3[si]
                        mov si, pvert
                        fsub dword ptr video_y3[si]
                        fmulp
                        fadd dword ptr video_y3[si]
                        fistp dword ptr mp[di+4]
                        jmp JMPR53 }
                  else53:   asm {   mov si, bx
                        fld dword ptr video_y3[si]
                        fistp dword ptr mp[di+4] }
                  JMPR53:   asm {   mov word ptr mp[di], ubx
                        mov word ptr mp[di+2], 0
                        mov si, bx
                        fld dword ptr video_x3[si]
                        mov si, nvert
                        fcomp dword ptr video_x3[si]
                        fstsw ax
                        sahf
                        jne if54
                        jmp else54 }
                  if54:     asm {   fld dword ptr ubxf
                        fsub dword ptr video_x3[si]
                        fld dword ptr video_x3[si]
                        mov si, bx
                        fsubr dword ptr video_x3[si]
                        fdivp
                        fld dword ptr video_y3[si]
                        mov si, nvert
                        fsub dword ptr video_y3[si]
                        fmulp
                        fadd dword ptr video_y3[si]
                        fistp dword ptr mp[di+12]
                        jmp JMPR52 }
                  else54:   asm {   mov si, bx
                        fld dword ptr video_y3[si]
                        fistp dword ptr mp[di+12] }
                  JMPR52:   asm {   mov word ptr mp[di+8], ubx
                        mov word ptr mp[di+10], 0
                        add di, 16
                        jmp STOP5 }
                  else52:   asm {   mov si, pvert
                        fld dword ptr video_x3[si]
                        fcomp dword ptr ubxf
                        fstsw ax
                        sahf
                        ja vnvert5
                        mov ax, pvert
                        mov vvert, ax
                        jmp vpvert5 }
                  vnvert5:  asm {   mov ax, nvert
                        mov vvert, ax }
                  vpvert5:  asm {   mov si, bx
                        fld dword ptr video_x3[si]
                        mov si, vvert
                        fcomp dword ptr video_x3[si]
                        fstsw ax
                        sahf
                        jne if55
                        jmp else55 }
                  if55:     asm {   fld dword ptr ubxf
                        fsub dword ptr video_x3[si]
                        fld dword ptr video_x3[si]
                        mov si, bx
                        fsubr dword ptr video_x3[si]
                        fdivp
                        fld dword ptr video_y3[si]
                        mov si, vvert
                        fsub dword ptr video_y3[si]
                        fmulp
                        fadd dword ptr video_y3[si]
                        fistp dword ptr mp[di+4]
                        jmp JMPR51 }
                  else55:   asm {   mov si, bx
                        fld dword ptr video_y3[si]
                        fistp dword ptr mp[di+4] }
                  JMPR51:   asm {   mov word ptr mp[di], ubx
                        mov word ptr mp[di+2], 0
                        add di, 8
                        jmp STOP5 }
                  else51:   asm {   fld dword ptr video_x3[si]
                        fistp dword ptr mp[di]
                        fld dword ptr video_y3[si]
                        fistp dword ptr mp[di+4]
                        add di, 8 }
                  STOP5:    asm {   inc vr
                        mov ax, vr
                        cmp ax, vr5
                        jnb cutting_end_5
                        jmp the_for_5 }

             cutting_end_5: asm {   mov _8n, di
                        sub _8n, 8
                        shr di, 3
                        mov vr6, di }

                    if (vr6<3) return;

    /* Riempimento del poligono risultante. */

    // Tracciamento rapido (nr. 3 balletti & via, per i poligoni piccoli)

drawb:  if (!flares) {
        if (min_y==max_y) {
            if (min_x==max_x)
                adapted[min_x + riga[min_y]] = colore;
            else {
                ptr = max_x + riga[min_y];
                while (max_x>=min_x) {
                    adapted[ptr] = colore;
                    max_x--;
                    ptr--;
                }
            }
            return;
        }
    }

    // Tracciamento complesso.

    // Disegna i bordi del poligono, con la funzione Segmento.

    asm     xor si, si
bordo:  asm {   db 0x66; mov ax, word ptr mp[si]
        db 0x66; mov word ptr xp, ax
        db 0x66; mov ax, word ptr mp[si+4]
        db 0x66; mov word ptr yp, ax
        db 0x66; mov ax, word ptr mp[si+8]
        db 0x66; mov word ptr xa, ax
        db 0x66; mov ax, word ptr mp[si+12]
        db 0x66; mov word ptr ya, ax
        push si }
        Segmento ();
    asm {   pop si
        add si, 8
        cmp si, _8n
        jb bordo
        db 0x66; mov ax, word ptr mp[si]
        db 0x66; mov word ptr xp, ax
        db 0x66; mov ax, word ptr mp[si+4]
        db 0x66; mov word ptr yp, ax
        db 0x66; mov ax, word ptr mp[0]
        db 0x66; mov word ptr xa, ax
        db 0x66; mov ax, word ptr mp[4]
        db 0x66; mov word ptr ya, ax }
        Segmento ();

    // Pixel di Partenza.

    unsigned segmptr; //= riga[min_y] + min_x;

    // Pixel d'Arrivo.

    unsigned lim_y; // = riga[max_y] + min_x;
    unsigned lim_x; // = segmptr + max_x - min_x;
    unsigned bytes; // = lim_x - segmptr + 2;

    asm {   mov si, min_y
        mov ax, min_x
        add si, si
        mov di, max_y
        add ax, word ptr riga[si]
        mov bx, min_x
        add di, di
        mov segmptr, ax
        add bx, word ptr riga[di]
        mov lim_y, bx
        add ax, max_x
        sub ax, min_x
        mov lim_x, ax
        sub ax, segmptr
        add ax, 2
        mov bytes, ax }

    // Riempimento (direction flag dev'essere 0)
    asm cld;

    switch (flares) {
        case 0:
            asm {   pusha
                les di, dword ptr adapted
                add lim_y, di
                add di, segmptr
                mov al, colore
                mov ah, colore
                db 0x66 // macro: shl eax, 16
                db 0xc1
                db 0xe0
                db 0x10
                mov ah, colore }
        linea:  asm {   push di
                mov cx, bytes
                mov al, 255
              repne scasb
                jne pross
                mov si, di
               repe scasb
                mov bx, di
              repne scasb
                jne fb1
               repe scasb
                dec di
                dec si
                mov al, colore
                mov dx, di
                sub dx, si
                mov di, si
                mov cx, dx
                shr cx, 2
                jz no_store }
    store_stringdw: asm {   db 0x26, 0x66, 0x89, 0x05 // mov es:[di], eax
                add di, 4
                dec cx
                jnz store_stringdw }
       no_store:    asm {   mov cl, dl
                and cl, 3
                rep stosb
                jmp pross }
        fb1:    asm {   dec si
                dec bx
                mov cx, bx
                mov al, colore
                sub cx, si
                mov di, si
                rep stosb }
        pross:  asm {   pop di
                add di, 320
                cmp di, lim_y
                jbe linea
                popa }
            break;
        case 1:
            asm {   les di, dword ptr adapted
                add lim_y, di
                add di, segmptr
                mov al, colore
                and al, 0x3F
                mov colore, al }
        l2:     asm {   push di
                mov cx, bytes
                mov al, 255
              repne scasb
                jne pross2
                mov si, di
               repe scasb
                mov bx, di
              repne scasb
                jne fb2
               repe scasb
                dec di
                dec si
                mov cx, di
                sub cx, si
                mov di, si }
        fill2:  asm {   mov al, es:[di-1]
                and al, 0x3F
                add al, colore
                cmp al, 62
                jb flow
                mov al, 62 }
        flow:   asm {   mov es:[di], al
                inc di
                dec cx
                jnz fill2
                jmp pross2 }
        fb2:    asm {   dec si
                dec bx
                mov cx, bx
                sub cx, si
                mov di, si
                mov dl, colore
                shr dl, 1 }
        fb2a:   asm {   mov al, es:[di-1]
                and al, 0x3F
                add al, dl
                cmp al, 62
                jb flow4
                mov al, 62 }
        flow4:  asm {   mov es:[di], al
                inc di
                dec cx
                jnz fb2a }
        pross2: asm {   pop di
                add di, 320
                cmp di, lim_y
                jbe l2 }
            break;
        case 2:
            asm {   push ds
                les ax, dword ptr adapted
                lds di, dword ptr adapted
                add lim_y, di
                add di, segmptr }
        l3: asm {   mov al, 0xFF
                push di
                mov cx, bytes
              repne scasb
                jne pross3
                mov si, di
               repe scasb
                mov bx, di
              repne scasb
                jne fb3
               repe scasb
                dec di
                dec si
                mov cx, di
                sub cx, si
                mov di, si }
        fill3:  asm {   cmp byte ptr [di], 0xFF
                jne tsnob
                mov ah, [di-321]
                and ah, 0x3F
                or ah, 0x40
                mov [di], ah
                jmp under }
        tsnob:  asm {   mov al, [di]
                and ax, 0x3F
                or  al, 0x40
                add ax, cx
                cmp ax, 128
                jb dnorm
                mov al, 127 }
        dnorm:  asm mov [di], al
        under:  asm {   inc di
                dec cx
                jnz fill3
                jmp pross3 }
        fb3:    asm {   dec si
                dec bx
                mov cx, bx
                sub cx, si
                mov di, si }
        fb3a:   asm {   mov ah, [di-321]
                cmp ah, 0xFF
                jne tsnoby
                mov ah, [di-642] }
        tsnoby: asm {   and ah, 0x3F
                or ah, 0x40
                mov [di], ah
                inc di
                dec cx
                jnz fb3a }
        pross3: asm {   pop di
                add di, 320
                cmp di, lim_y
                ja l3end
                jmp l3 }
        l3end:  asm pop ds
            break;
        // effetto flares = 3 spostato a "polymap"
        case 4:
            asm {   pusha
                les di, dword ptr adapted
                add lim_y, di
                add di, segmptr }
         fil4a: asm {   mov al, colore
                mov ah, colore
                db 0x66 // macro: shl eax, 16
                db 0xc1
                db 0xe0
                db 0x10
                mov ah, colore
                push di
                mov cx, bytes
                mov al, 255
              repne scasb
                jne fil4d
                mov si, di
               repe scasb
                mov bx, di
              repne scasb
                jne fil4e
               repe scasb
                dec di
                dec si
                mov al, colore
                mov dx, di
                sub dx, si
                mov di, si
                mov cx, dx
                shr cx, 2
                jz fil4c }
         fil4b: asm {   db 0x26, 0x66, 0x89, 0x05 // mov es:[di], eax
                add di, 4
                dec cx
                jnz fil4b }
         fil4c: asm {   mov cl, dl
                and cl, 3
                rep stosb
                jmp fil4d }
         fil4e: asm {   dec si
                dec bx
                mov cx, bx
                mov al, colore
                sub cx, si
                mov di, si
                rep stosb }
         fil4d: asm {   mov al, colore
                mov ah, colore
                and al, 0x3F
                and ah, 0xC0
                add al, ent
                cmp al, 0x3F
                jbe fil4f
                mov al, 0x3F
                test ent, 0x80
                jz  fil4f
                xor al, al }
         fil4f: asm {   or  al, ah
                mov colore, al
                pop di
                add di, 320
                cmp di, lim_y
                jbe fil4a
                popa }
    }
}

/*

    Sezione per il texture mapping.

*/

#define OK                     1 // Ritorno positivo.
#define NOT_OK                     0 // Ritorno negativo.

unsigned char huge *txtr; /* Area della texture (FLS a livelli di intensitÖ,
                 64 livelli per pixel, senza header).*/

char init_texture_mapping ()
{
    _control87 (MCW_EM, MCW_EM); // disattiva i Floating Point Errors.

    txtr = (unsigned char huge *)
           farmalloc ((long)TEXTURE_YSIZE * 256 + 16);

    if (txtr)
        return (OK);
    else
        return (NOT_OK);
}

char load_texture (char *fname, long offset)
                /* Carica una bitmap:
                   formato FLS a livelli di luminanza,
                   64 livelli per pixel, senza header. */
{
    int fh, sl;
    unsigned long p;

    fh = _rtl_open (fname, 0);

    if (fh>-1) {
        if (offset>=0)
            lseek (fh, offset, SEEK_SET);
        else
            lseek (fh, offset, SEEK_END);
        sl = 0;
        p  = 12;
        while (sl<TEXTURE_YSIZE&&!eof(fh)) {
            _rtl_read (fh, &txtr[p], TEXTURE_XSIZE);
            p += 256;
            sl++;
        }
        _rtl_close (fh);
        if (sl==TEXTURE_YSIZE)
            return (OK);
        else
            return (NOT_OK);
    }
    else
        return (NOT_OK);
}

char fast_load_texture (char *fname) /* Solo per bitmaps 256 x 256. */
{
    int fh;
    unsigned long p;

    fh = _rtl_open (fname, 0);

    if (fh>-1) {
        p  = 12;
        _rtl_read (fh, &txtr[p], 32768);
        p += 32768;
        _rtl_read (fh, &txtr[p], 32768);
        _rtl_close (fh);
        return (OK);
    }
    else
        return (NOT_OK);
}

/* Variabili e funzioni per i procedimenti di shading.
   Possono essere cambiate per conferire un aspetto diverso
   ad ogni poligono.

char    shade = 0;        // in che modo i poligoni intercettano la luce

#define NORMAL       0x00 // luminositÖ non curata

              /* sezione spotlight */
#define SPOTLIGHT    0x10 // torcia elettrica o faro, con centro su <xl, yl>
int     xl = x_centro;    // coordinate video del centro di luce
int yl = y_centro;    // coordinata y
int     aspect = 8;       // aspetto d. proiezione: + alto = + schiacciato
int     fallout = 20;     // evidenza della zona centrale: + alto = + diffuso
int     lt_range = 30;    // ampiezza zona illumin.: 0 = infinita
int     absorption = 45;  // assorbimento della superficie, da 0 a 63

              /* sezione radiosity semplificata */
#define RADIOSITY    0x20 // luminositÖ regolabile orizzontalmente o vertic.
char    shadymask = 1;
int shady_aux = 0;

int     xsh, ysh, ksh; // variabili di lavoro che devono rientrare in DS.

float   pnx, pny, pnz; // valori di ritorno della funzione successiva. */

void pnorm (float *x, float *y, float *z)
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

    ln = sqrt (xr * xr + yr * yr + zr * zr);
    if (ln>0) {
        ln  =  1 / ln;
        pnx = xr * ln;
        pny = yr * ln;
        pnz = zr * ln;
    }
    else {
        pnx = 0;
        pny = 0;
        pnz = 0;
    }
}

/* Se si desidera una texture sui poligoni, invocare quest'altra funzione.
   Il parametro "tinta" permette di specificare il colore meno luminoso
   di una sequenza di sue copie pió intense: il numero di queste
   gradazioni non ä importante per polymap.

   E` leggermente pió lenta nel riempimento, ma non ä grave.
   N.B. Il poligono deve avere sempre 4 vertici, anche se specificare il
    numero di vertici effettivi con il parametro "nv" aggiusta la
    texture in modo che i bordi coincidano.

   P.S. Sulla pagina nascosta, bisogna prevedere un byte in pió (64001),
    perchÇ vi viene conservato il numero del primo colore della texture,
    dato che i parametri sullo stack non sono raggiungibili nel ciclo
    di tracciamento principale, per ragioni di ottimizzazione. */

float   _0 = 0.0;
float   _16 = 16.0;

float   x_antialias = 1.125;
float   y_antialias = 1.125;
float   z_antialias = 1.125;

char    culling_needed = 0;  // flag: traccia due punti per volta.
char    halfscan_needed = 0; // flag: traccia due linee per volta.

unsigned char escrescenze = 0xE0; // primo colore dei bumps (escrescenze)

void polymap (float *x, float *y, float *z, char nv, unsigned char tinta)
{

    float ultima_x[2*VERTICI_PER_POLIGONO];
    float ultima_y[2*VERTICI_PER_POLIGONO];
    float ultima_z[2*VERTICI_PER_POLIGONO];

    int   fpart[MPIY];
    int   ipart[MPIY];

    float tempXsize = XSIZE;
    float tempYsize = YSIZE;

    char  _flares = flares;
    float _uno = 1;

    char  culling = culling_needed;
    char  halfscan = halfscan_needed;

    int   vr22;
    long  bndx;

    int   i, sections;

    long  i_low_lim = -10000;
    long  i_hig_lim = +10000;

    long  u, v, min_y, max_y;
    long  x1, y1, x2, y2, ity, jty;

    float k1, k2, k3, k4;
    float hx, vx, ox, hy, vy, oy, hz, vz, oz, _x, _y, _z;
    float kx, rx, ry, rz, mx, my, mz, nx, ny, nz, xx, yy, zz;

    float midx, midy, midz;
    float trxf[4], tryf[4], trzf[4];

    // Polymap ha routines fatte per 4 vertici.
    // Se sono 3, l'ultimo va duplicato.

    if (nv==3) {
        x[3] = x[2];
        y[3] = y[2];
        z[3] = z[2];
    }

    // Rototraslazione dei vertici; i dati rimangono ancora 3d.

        asm mov doflag, 0
        asm {// if (gamma)
           db 0x66; mov ax, word ptr _0
           db 0x66; cmp ax, word ptr gamma
            jne t_axis
            jmp no_t_axis }
    t_axis: asm {   xor di, di
            xor si, si }
       _vertex: asm {   les bx, dword ptr z
            fld dword ptr es:[bx+si]
            fsub cam_z
            fst zz
            fmul opt_tsinbeta
            les bx, dword ptr x
            fld dword ptr es:[bx+si]
            fsub cam_x
            fst xx
            fmul opt_tcosbeta
            faddp
            fstp dword ptr rxf[si]
            fld zz
            fmul opt_tcosbeta
            fld xx
            fmul opt_tsinbeta
            fsubp
            fst z2
            fmul opt_tcosalfa
            les bx, dword ptr y
            fld dword ptr es:[bx+si]
            fsub cam_y
            fst yy
            fmul opt_tsinalfa
            faddp
            fst dword ptr rzf[si]
            fcomp uneg
            fstsw ax
            fld yy
            fmul opt_tcosalfa
            fld z2
            fmul opt_tsinalfa
            fsubp
            fst my
            fmul opt_tcosgamma
            fld dword ptr rxf[si]
            fmul opt_tsingamma
            fsubp
            fstp dword ptr ryf[si]
            fld my
            fmul opt_tsingamma
            fld dword ptr rxf[si]
            fmul opt_tcosgamma
            faddp
            fstp dword ptr rxf[si]
            sahf
            jb _rzf_min_uneg
            inc doflag
            mov byte ptr rwf[di], 1
            jmp _convert }
 _rzf_min_uneg: asm     mov byte ptr rwf[di], 0
      _convert: asm {   add si, 4
            inc di
            cmp di, 4
            je _end_convert
            jmp _vertex }
  _end_convert: asm jmp end_convert
     no_t_axis: asm {   xor di, di
            xor si, si }
    vertex: asm {   les bx, dword ptr z
            fld dword ptr es:[bx+si]
            fsub cam_z
            fst zz
            fmul opt_tsinbeta
            les bx, dword ptr x
            fld dword ptr es:[bx+si]
            fsub cam_x
            fst xx
            fmul opt_tcosbeta
            faddp
            fstp dword ptr rxf[si]
            fld zz
            fmul opt_tcosbeta
            fld xx
            fmul opt_tsinbeta
            fsubp
            fst z2
            fmul opt_tcosalfa
            les bx, dword ptr y
            fld dword ptr es:[bx+si]
            fsub cam_y
            fst yy
            fmul opt_tsinalfa
            faddp
            fst dword ptr rzf[si]
            fcomp uneg
            fstsw ax
            fld yy
            fmul opt_tcosalfa
            fld z2
            fmul opt_tsinalfa
            fsubp
            fstp dword ptr ryf[si]
            sahf
            jb rzf_min_uneg
            inc doflag
            mov byte ptr rwf[di], 1
            jmp convert }
  rzf_min_uneg: asm     mov byte ptr rwf[di], 0
       convert: asm {   add si, 4
            inc di
            cmp di, 4
            je end_convert
            jmp vertex }

   end_convert: asm {// if (!doflag) return;
            cmp doflag, 0
            jne vectors }

        return;

    // Calcolo dei vettori di tracciamento del texture mapping.

       vectors: if (nv == 3) {
            midx = (rxf[0] + rxf[1] + rxf[2]) * 0.3333333;
            midy = (ryf[0] + ryf[1] + ryf[2]) * 0.3333333;
            midz = (rzf[0] + rzf[1] + rzf[2]) * 0.3333333;
            for (vr = 0; vr < 3; vr++) {
                trxf[vr] = (rxf[vr] - midx) * x_antialias + midx;
                tryf[vr] = (ryf[vr] - midy) * y_antialias + midy;
                trzf[vr] = (rzf[vr] - midz) * z_antialias + midz;
            }
            _SI = 8;
        }
        else {
            midx = (rxf[0] + rxf[1] + rxf[2] + rxf[3]) * 0.25;
            midy = (ryf[0] + ryf[1] + ryf[2] + ryf[3]) * 0.25;
            midz = (rzf[0] + rzf[1] + rzf[2] + rzf[3]) * 0.25;
            for (vr = 0; vr < 4; vr++) {
                trxf[vr] = (rxf[vr] - midx) * x_antialias + midx;
                tryf[vr] = (ryf[vr] - midy) * y_antialias + midy;
                trzf[vr] = (rzf[vr] - midz) * z_antialias + midz;
            }
            _SI = 12;
        }

        asm {// rx = rxf[0];
            fld dword ptr trxf[0]
            fstp rx
             // mx = rxf[1] - rx;
            fld dword ptr trxf[4]
            fsub rx
            fstp mx
             // nx = rx - rxf[3];
            fld rx
            fsub dword ptr trxf[si]
            fstp nx
             // ry = ryf[0];
            fld dword ptr tryf[0]
            fstp ry
             // my = ryf[1] - ry;
            fld dword ptr tryf[4]
            fsub ry
            fstp my
             // ny = ry - ryf[3];
            fld ry
            fsub dword ptr tryf[si]
            fstp ny
             // rz = rzf[0];
            fld dword ptr trzf[0]
            fstp rz
             // mz = rzf[1] - rz;
            fld dword ptr trzf[4]
            fsub rz
            fstp mz
             // nz = rz - rzf[3];
            fld rz
            fsub dword ptr trzf[si]
            fstp nz }

        asm {// hx = (rx * mz - rz * mx) * YCOEFF;
            fld rx
            fmul mz
            fld rz
            fmul mx
            fsubp
            fmul YCOEFF
            fstp hx
             // hy = (rx * nz - rz * nx) * YCOEFF;
            fld rx
            fmul nz
            fld rz
            fmul nx
            fsubp
            fmul YCOEFF
            fstp hy
             // hz = (nx * mz - nz * mx) / dpp;
            fld nx
            fmul mz
            fld nz
            fmul mx
            fsubp
            fmul inv_dpp
            fstp hz
             // vx = (rz * my - ry * mz) * XCOEFF;
            fld rz
            fmul my
            fld ry
            fmul mz
            fsubp
            fmul XCOEFF
            fstp vx
             // vy = (rz * ny - ry * nz) * XCOEFF;
            fld rz
            fmul ny
            fld ry
            fmul nz
            fsubp
            fmul XCOEFF
            fstp vy
             // vz = (nz * my - ny * mz) / dpp;
            fld nz
            fmul my
            fld ny
            fmul mz
            fsubp
            fmul inv_dpp
            fstp vz
             // ox = (ry * mx - rx * my) * EMU_K;
            fld ry
            fmul mx
            fld rx
            fmul my
            fsubp
            fmul EMU_K
            fstp ox
             // oy = (ry * nx - rx * ny) * EMU_K;
            fld ry
            fmul nx
            fld rx
            fmul ny
            fsubp
            fmul EMU_K
            fstp oy
             // oz =  ny * mx - nx * my;
            fld ny
            fmul mx
            fld nx
            fmul my
            fsubp
            fstp oz }

    // Fast-load per poligoni completamente visibili.

        asm {// if (doflag==4) {
            cmp doflag, 4
            jne z_clipping
            xor si, si
            mov cx, 4
            mov vr2, 4
            mov vr22, 8 }
    load:   asm {   db 0x66; mov ax, word ptr rxf[si]
            db 0x66; mov bx, word ptr ryf[si]
            db 0x66; mov dx, word ptr rzf[si]
            db 0x66; mov word ptr ultima_x[si], ax
            db 0x66; mov word ptr ultima_y[si], bx
            db 0x66; mov word ptr ultima_z[si], dx
            add si, 4
            dec cx
            jnz load
            jmp to_2d }

    /* Conversione punti alle spalle dell'osservatore
       rispetto al piano dello schermo. */

    z_clipping: asm {   mov vr, 0
            xor di, di
            mov dx, 4
            dec dx }
     the_for_1: asm {   mov si, vr
            cmp byte ptr rwf[si], 0
            je CONT1
            jmp bypass }
      CONT1:    asm {   mov ax, vr
            sub ax, 1
            jnc pvert1ok
            mov pvert, dx
            jmp pvert1no }
      pvert1ok: asm     mov pvert, ax
      pvert1no: asm {   mov ax, vr
            inc ax
            cmp ax, dx
            jbe nvert1ok
            mov nvert, 0
            jmp nvert1no }
      nvert1ok: asm     mov nvert, ax
      nvert1no: asm {   mov si, pvert
            cmp byte ptr rwf[si], 0
            je ctrl1
            jmp JMPR11 }
      ctrl1:    asm {   mov si, nvert
            cmp byte ptr rwf[si], 0
            jne JMPR11
            jmp STOP1 }
      JMPR11:   asm {   mov bx, vr
            shl bx, 2
            mov si, pvert
            mov al, byte ptr rwf[si]
            mov si, nvert
            add al, byte ptr rwf[si]
            cmp al, 2
            je if11
            jmp else11 }
      if11:     asm {   shl pvert, 2
            shl nvert, 2
            mov si, bx
            fld dword ptr rzf[si]
            mov si, pvert
            fcomp dword ptr rzf[si]
            fstsw ax
            sahf
            jne if12
            jmp else12 }
      if12:     asm {   fld dword ptr uneg
            fsub dword ptr rzf[si]
            fld dword ptr rzf[si]
            mov si, bx
            fsubr dword ptr rzf[si]
            fdivp
            fst zk
            fld dword ptr rxf[si]
            mov si, pvert
            fsub dword ptr rxf[si]
            fmulp
            fadd dword ptr rxf[si]
            fstp dword ptr ultima_x[di]
            fld zk
            mov si, bx
            fld dword ptr ryf[si]
            mov si, pvert
            fsub dword ptr ryf[si]
            fmulp
            fadd dword ptr ryf[si]
            fstp dword ptr ultima_y[di]
            jmp JMPR12 }
      else12:   asm {   mov si, bx
            db 0x66; mov ax, word ptr rxf[si]
            db 0x66; mov word ptr ultima_x[di], ax
            db 0x66; mov ax, word ptr ryf[si]
            db 0x66; mov word ptr ultima_y[di], ax }
      JMPR12:   asm {   db 0x66; mov ax, word ptr uneg
            db 0x66; mov word ptr ultima_z[di], ax
            mov si, bx
            fld dword ptr rzf[si]
            mov si, nvert
            fcomp dword ptr rzf[si]
            fstsw ax
            sahf
            jne neq1
            jmp eq1 }
      neq1:     asm {   fld dword ptr uneg
            fsub dword ptr rzf[si]
            fld dword ptr rzf[si]
            mov si, bx
            fsubr dword ptr rzf[si]
            fdivp
            fst zk
            fld dword ptr rxf[si]
            mov si, nvert
            fsub dword ptr rxf[si]
            fmulp
            fadd dword ptr rxf[si]
            fstp dword ptr ultima_x[di+4]
            fld zk
            mov si, bx
            fld dword ptr ryf[si]
            mov si, nvert
            fsub dword ptr ryf[si]
            fmulp
            fadd dword ptr ryf[si]
            fstp dword ptr ultima_y[di+4]
            jmp JMPR13 }
      eq1:      asm {   mov si, bx
            db 0x66; mov ax, word ptr rxf[si]
            db 0x66; mov word ptr ultima_x[di+4], ax
            db 0x66; mov ax, word ptr ryf[si]
            db 0x66; mov word ptr ultima_y[di+4], ax }
      JMPR13:   asm {   db 0x66; mov ax, word ptr uneg
            db 0x66; mov word ptr ultima_z[di+4], ax
            add di, 8
            jmp STOP1 }
      else11:   asm {   mov si, pvert
            cmp byte ptr rwf[si], 0
            jne vpvert1
            mov ax, nvert
            mov vvert, ax
            jmp vnvert1 }
      vpvert1:  asm {   mov ax, pvert
            mov vvert, ax }
      vnvert1:  asm {   shl vvert, 2
            mov si, bx
            fld dword ptr rzf[si]
            mov si, vvert
            fcomp dword ptr rzf[si]
            fstsw ax
            sahf
            jne neq2
            jmp eq2 }
      neq2:     asm {   fld dword ptr uneg
            fsub dword ptr rzf[si]
            fld dword ptr rzf[si]
            mov si, bx
            fsubr dword ptr rzf[si]
            fdivp
            fst zk
            fld dword ptr rxf[si]
            mov si, vvert
            fsub dword ptr rxf[si]
            fmulp
            fadd dword ptr rxf[si]
            fstp dword ptr ultima_x[di]
            fld zk
            mov si, bx
            fld dword ptr ryf[si]
            mov si, vvert
            fsub dword ptr ryf[si]
            fmulp
            fadd dword ptr ryf[si]
            fstp dword ptr ultima_y[di]
            jmp JMPR14 }
      eq2:      asm {   mov si, bx
            db 0x66; mov ax, word ptr rxf[si]
            db 0x66; mov word ptr ultima_x[di], ax
            db 0x66; mov ax, word ptr ryf[si]
            db 0x66; mov word ptr ultima_y[di], ax }
      JMPR14:   asm {   db 0x66; mov ax, word ptr uneg
            db 0x66; mov word ptr ultima_z[di], ax
            add di, 4
            jmp STOP1 }
      bypass:   asm {   shl si, 2
            db 0x66; mov ax, word ptr rxf[si]
            db 0x66; mov word ptr ultima_x[di], ax
            db 0x66; mov ax, word ptr ryf[si]
            db 0x66; mov word ptr ultima_y[di], ax
            db 0x66; mov ax, word ptr rzf[si]
            db 0x66; mov word ptr ultima_z[di], ax
            add di, 4 }
      STOP1:    asm {   inc vr
            mov ax, vr
            cmp ax, 4
            jnb cutting_end_1
            jmp the_for_1 }

 cutting_end_1: asm {   mov ax, di
            shr ax, 1
            mov vr22, ax
            shr ax, 1
            mov vr2, ax }

            if (vr2<3) return;

       // Queste sono le proiezioni prospettiche da 3d a 2d.
       // Contemporaneamente, il ciclo ricerca il minimo ed il massimo
       // verticale dell'estensione del poligono sullo schermo.

     to_2d: asm {   db 0x66; mov dx, word ptr ubyl
            db 0x66; mov bx, word ptr lbyl
            mov si, vr2
            dec si
            shl si, 2
            mov di, si
            add di, si }
     projector: asm {   fld dpp
            fdiv dword ptr ultima_z[si]
            fld st(0)
            fmul dword ptr ultima_x[si]
            fadd dword ptr x_centro_f
            fistp dword ptr mp[di]
            fmul dword ptr ultima_y[si]
            fadd dword ptr y_centro_f
            fistp dword ptr mp[di+4]
            db 0x66; cmp word ptr mp[di+4], dx
            jnl outr_3
            db 0x66; mov dx, word ptr mp[di+4] }
     outr_3:    asm {   db 0x66; cmp word ptr mp[di+4], bx
            jle outr_4
            db 0x66; mov bx, word ptr mp[di+4] }
     outr_4:    asm {   sub di, 8
            sub si, 4
            jnc projector
            db 0x66; mov word ptr max_y, bx
            db 0x66; mov word ptr min_y, dx }

    // Eventuale esclusione di poligoni non visibili.

    asm {// if (min_y>uby) return;
       db 0x66; mov ax, word ptr min_y
       db 0x66; cmp ax, word ptr ubyl
        jle ct1ok
         // if (max_y<lby) return;
       db 0x66; mov ax, word ptr max_y
       db 0x66; cmp ax, word ptr lbyl
        jnl ct1ok }

       return;

    // Normalizzazione dei limiti.

ct1ok:  asm {// if (min_y<lby) min_y = lby;
       db 0x66; mov ax, word ptr min_y
       db 0x66; cmp ax, word ptr lbyl
        jnl step_1
       db 0x66; mov ax, word ptr lbyl
       db 0x66; mov word ptr min_y, ax }

step_1: asm {// if (max_y>uby) max_y = uby;
       db 0x66; mov ax, word ptr max_y
       db 0x66; cmp ax, word ptr ubyl
        jle step_2
       db 0x66; mov ax, word ptr ubyl
       db 0x66; mov word ptr max_y, ax }

step_2: asm {// if (min_y>max_y) return;
       db 0x66; mov ax, word ptr min_y
       db 0x66; cmp ax, word ptr max_y
        jle ct2ok }

    return;

    // Inizializzazione costanti di ottimizzazione.

ct2ok:  asm {// k1 = vx * 16;
        fld  vx
        fmul _16
        fstp k1
         // k2 = vy * 16;
        fld  vy
        fmul _16
        fstp k2
         // k3 = vz * 16;
        fld  vz
        fmul _16
        fstp k3 }

    if (culling) {
        k1 *= 2;
        k2 *= 2;
        k3 *= 2;
    }

    // Inizializzazione delle matrici dei confini orizzontali.

    asm {// for (i=min_y; i<=max_y; i++)
        mov di, word ptr min_y
        mov cx, word ptr max_y
        db 0x66; mov ax, word ptr lbxl
        db 0x66; mov bx, word ptr ubxl
        sub cx, di
        shl di, 1
        inc cx }
ol_init:asm {// fpart[i] = lbxl;
        mov word ptr fpart[di], ax
         // ipart[i] = ubxl;
        mov word ptr ipart[di], bx
        add di, 2
        dec cx
        jnz ol_init }

    // Calcolo confini orizzontali.

    asm {// mp[vr22]   = mp[0];
         // mp[vr22+1] = mp[1];
        mov di, vr22
        shl di, 2
       db 0x66; mov ax, word ptr mp[0]
       db 0x66; mov bx, word ptr mp[4]
       db 0x66; mov word ptr mp[di], ax
       db 0x66; mov word ptr mp[di+4], bx
         // for (i = 0; i < vr22; i += 2)
        xor si, si
        shr vr22, 1 }
extfor: asm {// y1 = mp[i+1];
         // y2 = mp[i+3];
         // x1 = mp[i];
         // x2 = mp[i+2];
       db 0x66; mov bx, word ptr mp[si+4]
       db 0x66; mov dx, word ptr mp[si+12]
       db 0x66; mov ax, word ptr mp[si]
       db 0x66; mov cx, word ptr mp[si+8]
         // if (y2<y1)
       db 0x66; cmp dx, bx
        jnl noex
       db 0x66; mov word ptr x1, cx
       db 0x66; mov word ptr y1, dx
       db 0x66; mov word ptr x2, ax
       db 0x66; mov word ptr y2, bx
        jmp exch }
  noex: asm {// niente scambio
       db 0x66; mov word ptr x1, ax
       db 0x66; mov word ptr y1, bx
       db 0x66; mov word ptr x2, cx
       db 0x66; mov word ptr y2, dx }
  exch: asm {// scambio effettuato
         // if (y2!=y1) [nessuno ha alterato i flags]
        jne ol
        jmp nool } // niente calcolo del bordo: il segmento non si sviluppa in altezza
    ol: asm {// kx = (float)(x2 - x1) / (float)(y2 - y1);
        fild x2
        fisub x1
        fild y2
        fisub y1
        fdivp
        fstp kx
         // if (y1<lbyl)
       db 0x66; mov ax, word ptr y1
       db 0x66; cmp ax, word ptr lbyl
        jnl nocr
         // ity = lbyl;
       db 0x66; mov ax, word ptr lbyl
       db 0x66; mov word ptr ity, ax
         // x1 += (float)(lbyl-y1) * kx;
        fild x1
        fild lbyl
        fisub y1
        fmul kx
        faddp
        fistp x1
        jmp crct }
  nocr: asm {// ity = y1;
       db 0x66; mov ax, word ptr y1
       db 0x66; mov word ptr ity, ax }
  crct: asm {// if (y2>ubyl)
       db 0x66; mov ax, word ptr y2
       db 0x66; cmp ax, word ptr ubyl
        jng _nocr
         // jty = ubyl;
       db 0x66; mov ax, word ptr ubyl
       db 0x66; mov word ptr jty, ax
        jmp _crct }
 _nocr: asm {// jty = y2;
       db 0x66; mov ax, word ptr y2
       db 0x66; mov word ptr jty, ax }
 _crct: asm {// bndx = x1;
        fild x1
         // for (h=ity; h<=jty; h++)
       db 0x66; mov di, word ptr ity
       db 0x66; mov cx, word ptr jty
       db 0x66; cmp di, cx
        jnl noifor
       db 0x66; sub cx, di
        shl di, 1
        inc cx }
intfor: asm {// _EAX = bndx;
        fist bndx
        db 0x66; mov ax, word ptr bndx
        db 0x66; cmp ax, word ptr i_low_lim
        jnl ct01
        db 0x66; mov ax, word ptr i_low_lim }
ct01:   asm {   db 0x66; cmp ax, word ptr i_hig_lim
        jng ct02
        db 0x66; mov ax, word ptr i_hig_lim }
ct02:   asm {// if (bndx > fpart[h])
        cmp ax, word ptr fpart[di]
        jng ct1n
         // if (bndx < ubx)
        cmp ax, word ptr ubxl
        jnl ct2n
         // fpart[h] = bndx;
        mov word ptr fpart[di], ax
        jmp ct1n }
  ct2n: asm {// fpart[h] = ubx;
        mov dx, word ptr ubxl
        mov word ptr fpart[di], dx }
  ct1n: asm {// if (bndx < ipart[h])
        cmp ax, word ptr ipart[di]
        jnl ct3n
         // if (bndx > lbx)
        cmp ax, word ptr lbxl
        jng ct4n
         // ipart[h] = bndx;
        mov word ptr ipart[di], ax
        jmp ct3n }
  ct4n: asm {// ipart[h] = lbx;
        mov dx, word ptr lbxl
        mov word ptr ipart[di], dx }
  ct3n: asm {// bndx += kx;
        fadd kx
        add di, 2
        dec cx
        jnz intfor }
noifor: asm fstp st
  nool: asm {   add si, 8
        dec vr22
        jz  ol_end
        jmp extfor }

    // Pre-assegnamenti di lavoro.

ol_end: asm les dx, dword ptr txtr  // caricamento del segmento-texture
    asm mov ax, es          // .
    asm shr dx, 4           // .
    asm add ax, dx          // .
    asm db 0x8e, 0xe0       // mov fs, ax

    asm les ax, dword ptr adapted   // caricamento indirizzo area video
    asm mov al, tinta       // caricamento del primo colore
    asm mov es:[0xFA00], al     // .
    asm mov al, escrescenze     // caricamento primo colore bumps
    asm mov es:[0xFA01], al     // .

    // Ciclo di tracciamento.

             // for (i=min_y; i<=max_y; i++)
        asm     mov ax, word ptr min_y
        asm mov i, ax
     trace: asm {// _z = oz + (hz * (i - y_centro)) + (vz * (ipart[i] - x_centro + 1));
            mov si, i
            shl si, 1
            fild word ptr ipart[si]
            fsub x_centro_f
            fadd uno
            fld st(0) // duplica (ipart[i] - x_centro + 1)
            fld st(0) // due volte, ä lo stesso per tre calcoli
            fmul vz
            fild i
            fsub y_centro_f
            fmul hz
            faddp
            fadd oz
            fst _z
             // k4 = 1 / _z;
            fdivr uno
            fstp k4
             // _x = ox + (hx * (i - y_centro)) + (vx * (ipart[i] - x_centro + 1));
            fmul vx
            fild i
            fsub y_centro_f
            fmul hx
            faddp
            fadd ox
            fstp _x
             // _y = oy + (hy * (i - y_centro)) + (vy * (ipart[i] - x_centro + 1));
            fmul vy
            fild i
            fsub y_centro_f
            fmul hy
            faddp
            fadd oy
            fstp _y
             // u  = (_x * tempXsize) * k4; // Seq. stabile
             // v  = (_y * tempYsize) * k4; // Ma usare _control87
            fld _y
            fmul tempYsize
            fmul k4
            fld _x
            fmul tempXsize
            fmul k4
            fxch
            fistp v
            fistp u
             // sections = fpart[i] - ipart[i]; // Sequenza stabile.
             // _DI = i * 320 + ipart[i];       // Moltiplicazione per 320 in tabella.
             // SI ä giÖ caricato con I * 2.
            mov dx, word ptr ipart[si]
            mov ax, word ptr fpart[si]
            mov di, word ptr riga[si]
            sub ax, dx
            add di, dx
            mov sections, ax
            push ds
            push es
            pop  ds
            test culling, 1
            jz row
            jmp c_row }
     // tracciamento di una scanline: versione ad alto dettaglio
       row: asm {   cmp sections, 0
            jg  again
            jmp row_end }
     again: asm {   cmp sections, 16
            jg  complete
            mov ax, sections
            mov cl, al
            jmp unfinished }
      complete: asm     mov cl, 16
    unfinished: asm {   sub sections, 16
            cmp cl, 0
            je  row
             // x += k1;               // Sequenza stabile.
             // y += k2;           // Traduzione ASM ok.
             // z += k3;               // Nessun ritardo grazie a FXCH.
             // if (z) {               // !! Sequenza instabile.
             // k4 = 1 / z;        // correzione da parte di "_control87"
             // u2 = (x * XSIZE) * k4; // Problema: le FISTP possono provocare
             // v2 = (y * YSIZE) * k4; // errori di dominio in virgola mobile.
            fld   _z           // 1 cycle   stack: z
            fadd  k3               // 1 cycle   stack: z+k3
            fld   _x           // 1 cycle   stack: x, z+k3
            fadd  k1               // 1 cycle   stack: x+k1, z+k3
            fxch                   // no time   stack: z+k3, x+k1
            fst   _z               // 2 cycles  stack: z+k3, x+k1
            fxch                   // no time   stack: x+k1, z+k3
            fst   _x               // 2 cycles  stack: x+k1, z+k3
            fxch                   // no time   stack: z+k3, x+k1
            fdivr _uno             // 39 cycles stack: k4, x+k1
           db 0x66; mov ax, word ptr u     // while FPU is working,
           db 0x66; mov dx, word ptr v     // this group takes 0 cycles.
            mov ch, _flares        //
            push bp                //
            fxch                   // no time   stack: x+k1, k4
            fmul  tempXsize        // 1 cycle   stack: x..., k4
            fld   _y               // 1 cycle   stack: y, x..., k4
            fadd  k2           // 1 cycle   stack: y+k2, x..., k4
            fst   _y               // 3 cycles  stack: y+k2, x..., k4
            fmul  tempYsize        // 1 cycle   stack: y..., x..., k4
            fxch                   // no time   stack: x..., y..., k4
            fmul  st, st(2)        // 1 cycle   stack: u, y..., k4
            fxch                   // no time   stack: y..., u, k4
            fmul  st, st(2)        // 1 cycle   stack: v, u, k4
            fxch                   // no time   stack: u, v, k4
            fistp u                // 6 cycles  stack: v, k4
            fistp v                // 6 cycles  stack: k4
            fstp st
           db 0x66; mov si, word ptr v
           db 0x66; mov bp, word ptr u
           db 0x66; sub si, dx
           db 0x66; sub bp, ax
           db 0x66; sar si, 4
           db 0x66; sar bp, 4
            test ch, 15     // NORMALE = 0
            jz internal
            test ch, 1      // LUCIDO = 1
            jnz transp
            test ch, 2      // BRILLANTE = 2
            jnz bright
            test ch, 4      // TRASLUCIDO = 4
            jnz merger
            jmp bumper }        // BUMP MAPPING = 8
      internal: asm {   mov bh, dh      // 1 (riempimento normale)
            inc di          // *
            mov bl, ah      // 1
            mov ch, ds:[0xFA00] // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            add ax, bp      // *
            mov [di+3], ch      // 1
            add dx, si      // *
            dec cl          // 1
            jnz internal        // 7 cicli.
            jmp common }
      transp:   asm {   mov bh, dh      // 1 (riempimento lucido)
            inc di          // *
            mov bl, ah      // 1
            mov ch, [di+3]      // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            add ax, bp      // *
            mov [di+3], ch      // 1
            add dx, si      // *
            dec cl          // 1
            jnz transp      // 7 cicli.
            jmp common }
      bright:   asm {   mov ch, [di+4]      // 1 (riempimento brillante)
            mov bh, dh      // *
            inc di          // 1
            mov bl, ah      // *
            and ch, 0x3F        // 1
            add ax, bp      // *
            db 0x64, 0x02, 0x2F     // 1+PFX (add ch, fs:[bx])
            add dx, si      // *
            cmp ch, 0x3E        // 1
            jbe antibloom       // * (antiblooming)
            mov ch, 0x3E }      // 1
      antibloom:asm {   and byte ptr [di+3],0xC0// 1
            or  [di+3], ch      // 1
            dec cl          // *
            jnz bright      // 1/0 (9-10 cicli.)
            jmp common }
      merger:   asm {   mov ch, [di+4]      // 1 (traslucido)
            mov bh, dh      // *
            inc di          // 1
            mov bl, ah      // *
            and ch, 0x3F        // 1
            add ax, bp      // *
            db 0x64, 0x02, 0x2F     // 1+PFX (add ch, fs:[bx])
            add ch, ds:[0xFA00]
            add dx, si      // *
            shr ch, 1       // 1
            and byte ptr [di+3],0xC0// 1
            or  [di+3], ch      // 1
            dec cl          // *
            jnz merger      // 1 (9 cicli.)
            jmp common }
      bumper:   asm {   mov bh, dh      // 1 (bump mapping)
            inc di          // *
            mov bl, ah      // 1
            mov ch, ds:[0xFA00] // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            add ax, bp      // *
            mov [di+3], ch      // 1
            push di
            push cx
            and ch, 0x7 }
      bmpm320:  asm {   sub di, 320
            dec ch
            jns bmpm320
            pop cx
            sub ch, ds:[0xFA00]
            add ch, ds:[0xFA01] // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            mov byte ptr [di+640+3], ch
            pop di
            add dx, si      // *
            dec cl          // 1
            jnz bumper }        // ? cicli.
    common: asm {   pop bp
            jmp row }
     // tracciamento di una scanline: versione a basso dettaglio
     c_row: asm {   cmp sections, 0
            jg  c_again
            jmp row_end }
       c_again: asm {   cmp sections, 32
            jg  c_complete
            mov ax, sections
            add ax, 2
            mov cl, al
            jmp c_unfinished }
    c_complete: asm     mov cl, 32
  c_unfinished: asm {   sub sections, 32
            cmp cl, 2
            jl  c_row
            fld   _z           // 1 cycle   stack: z
            fadd  k3               // 1 cycle   stack: z+k3
            fld   _x           // 1 cycle   stack: x, z+k3
            fadd  k1               // 1 cycle   stack: x+k1, z+k3
            fxch                   // no time   stack: z+k3, x+k1
            fst   _z               // 2 cycles  stack: z+k3, x+k1
            fxch                   // no time   stack: x+k1, z+k3
            fst   _x               // 2 cycles  stack: x+k1, z+k3
            fxch                   // no time   stack: z+k3, x+k1
            fdivr _uno             // 39 cycles stack: k4, x+k1
           db 0x66; mov ax, word ptr u     // while FPU is working,
           db 0x66; mov dx, word ptr v     // this group takes 0 cycles.
            shr cl, 1          //
            push bp                //
            mov ch, _flares        //
            push di            //
            fxch                   // no time   stack: x+k1, k4
            fmul  tempXsize        // 1 cycle   stack: x..., k4
            fld   _y               // 1 cycle   stack: y, x..., k4
            fadd  k2           // 1 cycle   stack: y+k2, x..., k4
            fst   _y               // 3 cycles  stack: y+k2, x..., k4
            fmul  tempYsize        // 1 cycle   stack: y..., x..., k4
            fxch                   // no time   stack: x..., y..., k4
            fmul  st, st(2)        // 1 cycle   stack: u, y..., k4
            fxch                   // no time   stack: y..., u, k4
            fmul  st, st(2)        // 1 cycle   stack: v, u, k4
            fxch                   // no time   stack: u, v, k4
            fistp u                // 6 cycles  stack: v, k4
            fistp v                // 6 cycles  stack: k4
            fstp st
           db 0x66; mov si, word ptr v
           db 0x66; mov bp, word ptr u
           db 0x66; sub si, dx
           db 0x66; sub bp, ax
           db 0x66; sar si, 4
           db 0x66; sar bp, 4
            test ch, 15         // NORMALE = 0
            jz c_internal
            test ch, 1      // LUCIDO = 1
            jnz c_transp
            test ch, 2      // BRILLANTE = 2
            jnz c_bright
            test ch, 4      // TRASLUCIDO = 4
            jnz c_merger
            jmp c_bumper }      // BUMP MAPPING = 8
    c_internal: asm {   mov bh, dh      // 1 (riempimento normale)
            add di, 2       // *
            mov bl, ah      // 1
            mov ch, ds:[0xFA00] // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            add ax, bp      // *
            mov [di+2], ch      // 1
            mov [di+3], ch      // *
            add dx, si      // 1
            dec cl          // *
            jnz c_internal      // 1 (8 cicli).
            jmp c_common }
    c_transp:   asm {   mov bh, dh      // 1 (riempimento lucido)
            add di, 2       // *
            mov bl, ah      // 1
            mov ch, [di+3]      // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            add ax, bp      // *
            mov [di+2], ch      // 1
            mov [di+3], ch      // *
            add dx, si      // 1
            dec cl          // *
            jnz c_transp        // 1 (8 cicli).
            jmp c_common }
    c_bright:   asm {   mov ch, [di+4]      // 1 (riempimento brillante)
            mov bh, dh      // *
            add di, 2       // 1
            mov bl, ah      // *
            and ch, 0x3F        // 1
            add ax, bp      // *
            db 0x64, 0x02, 0x2F     // 1+PFX (add ch, fs:[bx])
            add dx, si      // *
            cmp ch, 0x3E        // 1
            jbe c_antibloom     // * (antiblooming)
            mov ch, 0x3E }      // 1
    c_antibloom:asm {   and byte ptr [di+2],0xC0// 1
            or  ch, [di+2]      // 1
            dec cl          // 1
            mov [di+2], ch      // *
            mov [di+3], ch      // 1
            jnz c_bright        // 0 (11 cicli.)
            jmp c_common }
    c_merger:   asm {   mov ch, [di+4]      // 1 (traslucido)
            mov bh, dh      // *
            add di, 2       // 1
            mov bl, ah      // *
            and ch, 0x3F        // 1
            add ax, bp      // *
            db 0x64, 0x02, 0x2F     // 1+PFX (add ch, fs:[bx])
            add ch, ds:[0xFA00]
            add dx, si      // *
            shr ch, 1       // 1
            and byte ptr [di+2],0xC0// *
            or  ch, [di+2]      // 1
            dec cl          // *
            mov [di+2], ch      // 1
            mov [di+3], ch      // *
            jnz c_merger        // 1 (9 cicli.)
            jmp c_common }
      c_bumper: asm {   mov bh, dh      // 1 (bump mapping)
            add di, 2       // *
            mov bl, ah      // 1
            mov ch, ds:[0xFA00] // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            add ax, bp      // *
            mov [di+2], ch      // 1
            mov [di+3], ch      // 1
            push di
            push cx
            and ch, 0x7 }
      c_bmpm320:asm {   sub di, 320
            dec ch
            jns c_bmpm320
            pop cx
            sub ch, ds:[0xFA00]
            add ch, ds:[0xFA01] // *
            db 0x64, 0x02, 0x2F     // 1+PFX+AGI (add ch, fs:[bx])
            mov byte ptr [di+640+2], ch
            mov byte ptr [di+640+3], ch
            pop di
            add dx, si      // *
            dec cl          // 1
            jnz c_bumper }      // ? cicli.
      c_common: asm {   pop di
            pop bp
            add di, 32
            jmp c_row }
    // codice inter-scanline: fra una scanline e la successiva...
       row_end: asm {   test halfscan, 1
            jz do_singlescan
            inc i
            mov ax, word ptr max_y
            cmp ax, i
            pop ds
            jb trace_end
            mov si, i
            shl si, 1
            mov dx, word ptr ipart[si-2]
            mov ax, word ptr fpart[si-2]
            mov di, word ptr riga[si]
            push ds
            push es
            pop  ds
            sub ax, dx
            jc do_singlescan
            jz do_singlescan
            add di, dx }
     duplicate: asm {   mov dl, [di-316]
            mov [di+4], dl
            mov [di+324], dl
            inc di
            dec ax
            jnz duplicate }
 do_singlescan: asm {   inc i
            mov ax, word ptr max_y
            cmp ax, i
            pop ds
            jb trace_end
            jmp trace }
     trace_end:      // Fine tracciamento.
}

void Forward (float delta) /* Provoca l'avanzamento dell'osservatore
                  nella direzione di volo di <delta>
                  unitÖ virtuali. */
{
    cam_x -= delta * opt_tsinbeta * opt_tcosalfa;
    cam_z += delta * opt_tcosbeta * opt_tcosalfa;
    cam_y += delta * opt_tsinalfa;
}

long _x_, _y_;

char getcoords (float x, float y, float z)
{ // calcola le coordinate sullo schermo di un punto nello spazio,
  // usando lo stesso nucleo di calcolo di poly3d e di polymap,
  // se il punto rientra nello schermo ritorna 1, altrimenti ritorna 0.
  // le coordinate sono poi trasferite nelle variabili _x_ e _y_.
  // il punto non andrebbe tracciato se non ä visibile, perchÇ
  // le coordinate risulterebbero, in tal caso, indeterminabili.

    float rx, ry, rz, my;

        asm {// if (gamma != 0) goto t_axis;
           db 0x66; mov ax, word ptr _0
           db 0x66; cmp ax, word ptr gamma
            jne t_axis
            jmp no_t_axis }
    t_axis: asm {   fld z
            fsub cam_z
            fst zz
            fmul opt_tsinbeta
            fld x
            fsub cam_x
            fst xx
            fmul opt_tcosbeta
            faddp
            fstp rx
            fld zz
            fmul opt_tcosbeta
            fld xx
            fmul opt_tsinbeta
            fsubp
            fst z2
            fmul opt_tcosalfa
            fld y
            fsub cam_y
            fst yy
            fmul opt_tsinalfa
            faddp
            fst rz
            fcomp uneg
            fstsw ax
            fld yy
            fmul opt_tcosalfa
            fld z2
            fmul opt_tsinalfa
            fsubp
            fst my
            fmul opt_tcosgamma
            fld rx
            fmul opt_tsingamma
            fsubp
            fstp ry
            fld my
            fmul opt_tsingamma
            fld rx
            fmul opt_tcosgamma
            faddp
            fstp rx
            sahf
            jb _rzf_min_uneg
            jmp convert }
 _rzf_min_uneg:     return (0);

     no_t_axis: asm {   fld z
            fsub cam_z
            fst zz
            fmul opt_tsinbeta
            fld x
            fsub cam_x
            fst xx
            fmul opt_tcosbeta
            faddp
            fstp rx
            fld zz
            fmul opt_tcosbeta
            fld xx
            fmul opt_tsinbeta
            fsubp
            fst z2
            fmul opt_tcosalfa
            fld y
            fsub cam_y
            fst yy
            fmul opt_tsinalfa
            faddp
            fst rz
            fcomp uneg
            fstsw ax
            fld yy
            fmul opt_tcosalfa
            fld z2
            fmul opt_tsinalfa
            fsubp
            fstp ry
            sahf
            jb rzf_min_uneg
            jmp convert }
  rzf_min_uneg:     return (0);

       convert: //my  = dpp / rz;
        //_x_ = my * rx + x_centro_f;
        //_y_ = my * ry + y_centro_f;

        asm {
            fld dpp
            fdiv rz
            fld st(0)
            fmul rx
            fadd x_centro_f
            fistp _x_
            fmul ry
            fadd y_centro_f
            fistp _y_
        }

        if (_x_ > lbxl && _x_ < ubxl && _y_ > lbyl && _y_ < ubyl)
            return (1);
        else
            return (0);
}

char facing (float *x, float *y, float *z)
{ /* Controlla se un poligono a una sola faccia ä visibile o meno.
     Certo che come procedimento non ä poi tanto semplice: va calcolata,
     anche approssimativamente, la normale alla superficie; comunque,
     sempre meglio che calcolare tutto il poligono... */
    float x1, y1, z1, x2, y2, z2, xr, yr, zr;

    asm {   les   bx, dword ptr x
        mov   si, word ptr  y
        mov   di, word ptr  z
        fld   dword ptr es:[bx]
        fsub  dword ptr es:[bx+8]
        fstp  x1
        fld   dword ptr es:[si]
        fsub  dword ptr es:[si+8]
        fstp  y1
        fld   dword ptr es:[di]
        fsub  dword ptr es:[di+8]
        fstp  z1
        fld   dword ptr es:[bx+4]
        fsub  dword ptr es:[bx+8]
        fstp  x2
        fld   dword ptr es:[si+4]
        fsub  dword ptr es:[si+8]
        fstp  y2
        fld   dword ptr es:[di+4]
        fsub  dword ptr es:[di+8]
        fst   z2
        fmul  y1
        fld   y2
        fmul  z1
        fsubp
        fstp  xr
        fld   z1
        fmul  x2
        fld   z2
        fmul  x1
        fsubp
        fstp  yr
        fld   x1
        fmul  y2
        fld   x2
        fmul  y1
        fsubp
        fstp  zr
        fld   cam_x
        fsub  dword ptr es:[bx+8]
        fmul  xr
        fld   cam_y
        fsub  dword ptr es:[si+8]
        fmul  yr
        faddp
        fld   cam_z
        fsub  dword ptr es:[di+8]
        fmul  zr
        faddp
        ftst
        ffree st(0)
        fstsw ax
        xor dl, dl
        sahf
        jb _zero
        not dl }
_zero:      return (_DL);
}
