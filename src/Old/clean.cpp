/*

    Noctis database / CLEAN command.
    GOES Net Module.

*/

#include <string.h>
#include <stdio.h>
#include <io.h>

char msgbuffer[40];
char* divider = "&&&&&&&&&&&&&&&&&&&&&";

void msg (char* string) {
    int x;
    strcpy (msgbuffer, string);
    msgbuffer[21] = 0;
    printf (msgbuffer);
    x = strlen(msgbuffer);

    while (x < 21) {
        printf (" ");
        x++;
    }
}

double  object_id;
char    object_label[25];
double  mblock_subject;
char    mblock_message[77];

long    starmap_consolidated;
long    cleaned_starmap_consolidated;
long    guide_consolidated;
long    cleaned_guide_consolidated;

long    round, sm_pos, gg_pos;
int     fh, gh, fh2, gh2;

char*   starmap = "..\\DATA\\STARMAP.BIN";
char*   starmap_swp = "..\\DATA\\STARMAP.SWP";
char*   guide = "..\\DATA\\GUIDE.BIN";
char*   guide_swp = "..\\DATA\\GUIDE.SWP";

long    tmessages;
long    rmessages;

char    outbuffer[40];

void main () {
    asm {   xor ax, ax
            mov es, ax
            cmp byte ptr es:[0x449], 0x13
            je  startup }
    printf ("\nGalactic Organization of Explorers and Stardrifters (G.O.E.S)\n");
    printf ("-------------------------------------------------------------\n");
    printf ("This is a GOES NET module and must be run from a stardrifter.\n");
    printf ("Please use the onboard computer console to run this module.\n");
    printf ("\n\t- GOES NET onboard microsystem, EPOC 6011 REVISION 3\n");
    return;
startup:
    msg ("CLEANING STARMAP...");
    msg (divider);
    fh = _open (starmap, 0);

    if (fh == -1) {
        msg ("STARMAP NOT AVAILABLE");
        return;
    }

    fh2 = _creat (starmap_swp, 0);

    if (fh2 == -1) {
        msg ("CAN'T SETUP SWAP FILE");
        _close (fh);
        return;
    }

    _read (fh, &starmap_consolidated, 4);
    _write (fh2, &starmap_consolidated, 4);
    cleaned_starmap_consolidated = starmap_consolidated;

    if (starmap_consolidated > filelength (fh)) {
        msg ("STARMAP FILE CORRUPT:");
        msg ("PLEASE RE-DOWNLOAD");
        msg ("WHOLE NOCTIS PACKAGE");
        msg ("AND RE-UPDATE IN FULL");
        msg (divider);
        msg ("VERY SORRY.");
        _close (fh);
        _close (fh2);
        remove (starmap_swp);
        return;
    }

    tmessages = 0;
    rmessages = 0;

    while (_read (fh, &object_id, 8) && _read (fh, object_label, 24) == 24) {
        tmessages++;

        if (memcmp(&object_id, "Removed:", 8)) {
            _write (fh2, &object_id, 8);
            round = _write (fh2, object_label, 24);

            if (round != 24) {
                msg ("ERROR: DISK FULL?");
                _close (fh);
                _close (fh2);
                remove (starmap_swp);
                return;
            }
        } else {
            rmessages++;
            sm_pos = tell (fh);
            sm_pos -= 32;

            if (sm_pos < starmap_consolidated) {
                cleaned_starmap_consolidated -= 32;
            }
        }
    }

    lseek (fh2, 0, SEEK_SET);
    _write (fh2, &cleaned_starmap_consolidated, 4);
    _close (fh);
    _close (fh2);
    remove (starmap);
    rename (starmap_swp, starmap);
    sprintf (outbuffer, "RECORDS: %ld", tmessages);
    msg (outbuffer);
    sprintf (outbuffer, "REMOVED: %ld", rmessages);
    msg (outbuffer);
    ////////////////////////////////////////////////////////////////////
    msg (divider);
    msg ("CLEANING GUIDE...");
    msg (divider);
    gh = _open (guide, 0);

    if (gh == -1) {
        msg ("GUIDE NOT AVAILABLE");
        return;
    }

    gh2 = _creat (guide_swp, 0);

    if (gh2 == -1) {
        msg ("CAN'T SETUP SWAP FILE");
        _close (gh);
        return;
    }

    _read (gh, &guide_consolidated, 4);
    _write (gh2, &guide_consolidated, 4);
    cleaned_guide_consolidated = guide_consolidated;

    if (guide_consolidated > filelength (gh)) {
        msg ("GUIDE FILE CORRUPT:");
        msg ("PLEASE RE-DOWNLOAD");
        msg ("WHOLE NOCTIS PACKAGE");
        msg ("AND RE-UPDATE IN FULL");
        msg (divider);
        msg ("VERY SORRY.");
        _close (gh);
        _close (gh2);
        remove (guide_swp);
        return;
    }

    tmessages = 0;
    rmessages = 0;

    while (_read (gh, &mblock_subject, 8) && _read (gh, mblock_message, 76) == 76) {
        tmessages++;

        if (memcmp(&mblock_subject, "Removed:", 8)) {
            _write (gh2, &mblock_subject, 8);
            round = _write (gh2, mblock_message, 76);

            if (round != 76) {
                msg ("ERROR: DISK FULL?");
                _close (gh);
                _close (gh2);
                remove (guide_swp);
                return;
            }
        } else {
            rmessages++;
            gg_pos = tell (gh);
            gg_pos -= 84;

            if (gg_pos < guide_consolidated) {
                cleaned_guide_consolidated -= 84;
            }
        }
    }

    lseek (gh2, 0, SEEK_SET);
    _write (gh2, &cleaned_guide_consolidated, 4);
    _close (gh);
    _close (gh2);
    remove (guide);
    rename (guide_swp, guide);
    sprintf (outbuffer, "RECORDS: %ld", tmessages);
    msg (outbuffer);
    sprintf (outbuffer, "REMOVED: %ld", rmessages);
    msg (outbuffer);
    ////////////////////////////////////////////////////////////////////
    msg (divider);
    msg ("END");
}