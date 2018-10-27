/*

    Noctis galactic guide / CAT command.
    GOES Net Module.

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <io.h>

char msgbuffer[77];
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

double  object_id = 12345;
char    object_label[25];
double  s_object_id = 12345;
char    s_object_label[25];

double  subject_id = 12345;
double  idscale = 0.00001;

long    round;
int     i, fh, gh;
char*   file = "..\\DATA\\STARMAP.BIN";
char*   guide = "..\\DATA\\GUIDE.BIN";

char    outbuffer[40];
char    textbuffer[40];
char    parbuffer[160];
char    nullbuffer[128];
char    objectname[21];
char    subjectname[21];

double  mblock_subject;
char    mblock_message[77];

char find (char* starname) {
    int p, n, ctc, found;
    ctc = strlen (starname);

    if (ctc > 20 || ctc <= 0) {
        msg ("INVALID OBJECT NAME.");
        return (0);
    }

    n = 0;
    found = 0;
    lseek (fh, 4, SEEK_SET);

    while (_read (fh, &s_object_id, 8) && _read (fh, &s_object_label, 24) == 24) {
        if (memcmp (&s_object_id, "Removed:", 8)) {
            if (!memcmp (s_object_label, starname, ctc)) {
                n++;
                memcpy (object_label, s_object_label, 24);
                object_id = s_object_id;
                memcpy (subjectname, object_label, 20);
                subject_id = object_id;

                if (object_label[21] == 'S') {
                    found = 1;
                }

                if (object_label[21] == 'P') {
                    found = 2;
                }

                p = 20;

                while (p >= 0) {
                    if (s_object_label[p] != 32) {
                        if (s_object_label[p] == starname[p]) {
                            return (found);
                        } else {
                            break;
                        }
                    }

                    p--;
                }
            }
        }
    }

    if (!n) {
        msg ("OBJECT NOT FOUND.");
    }

    if (n > 1) {
        msg ("AMBIGUOUS SEARCH KEY:");
        msg ("PLEASE EXPAND NAME...");
        msg (divider);
        msg ("POSSIBLE RESULTS ARE:");
        msg (divider);
        lseek (fh, 4, SEEK_SET);

        while (_read (fh, &s_object_id, 8) && _read (fh, &s_object_label, 24) == 24) {
            if (memcmp (&s_object_id, "Removed:", 8)
                    && !memcmp (s_object_label, starname, ctc)) {
                s_object_label[21] = 0;
                msg (s_object_label);
            }
        }

        msg (divider);
        found = 0;
    }

    return (found);
}

void main () {
    char query;
    int j, col, pre;
    int is, rec, rec_start, rec_end;
    asm {   xor ax, ax
            mov es, ax
            cmp byte ptr es:[0x449], 0x13
            je  startup }
    printf ("\nGalactic Organization of Explorers and Stardrifters (G.O.E.S)\n");
    printf ("-------------------------------------------------------------\n");
    printf ("This is a GOES NET module and must be run from a stardrifter.\n");
    printf ("Please use the onboard computer console to run this module.\n");
    printf ("\n\t- GOES NET onboard microsystem, EPOC 6011 REVISION 2\n");
    return;
startup:

    if (_argc < 2) {
        msg ("________USAGE________");
        msg ("CAT OBJECTNAME");
        msg ("CAT OBJECTNAME:X..Y");
        msg ("^^^^^^^^^^^^^^^^^^^^^");
        msg ("PLEASE RUN AGAIN,");
        msg ("SPECIFYING PARAMETERS");
        return;
    } else {
        msg (" GOES GALACTIC GUIDE ");
        msg (divider);
    }

    fh = _open (file, 4);

    if (fh == -1) {
        msg ("STARMAP NOT AVAILABLE");
        return;
    }

    i = 2;
    strcpy (parbuffer, _argv[1]);

    while (i < _argc) {
        strcat (parbuffer, " ");
        strcat (parbuffer, _argv[i]);
        i++;
    }

    i = 0;

    while (parbuffer[i]) {
        if (parbuffer[i] == '_') {
            parbuffer[i] = 32;
        }

        i++;
    }

    i = 0;

    while (i < 21 && parbuffer[i] != ':' && parbuffer[i] != 0) {
        objectname[i] = parbuffer[i];
        i++;
    }

    if (i == 21) {
        msg ("INVALID SUBJECT NAME.");
        _close (fh);
    }

    if (parbuffer[i] == ':') {
        is = i + 1;
        i++;

        while (parbuffer[i] != '.' && parbuffer[i] != 0) {
            i++;
        }

        parbuffer[i] = 0;
        rec_start = atoi (parbuffer + is);

        if (parbuffer[i + 1] == '.') {
            rec_end = atoi (parbuffer + i + 2);
        } else {
            rec_end = 32767;
        }
    } else {
        rec_start = 1;
        rec_end = 32767;
    }

    objectname[i] = 0;
    query = find (objectname);

    if (query) {
        if (query == 1) {
            msg ("SUBJECT: STAR;");
        }

        if (query == 2) {
            msg ("SUBJECT: PLANET;");
        }

        msg (subjectname);
        msg (divider);
        gh = _open (guide, 4);

        if (gh == -1) {
            msg ("DATABASE ERROR.");
            msg ("(ERROR CODE 1003)");
        } else {
            rec = 0;
            col = 0;
            query = 0;
            lseek (gh, 4, SEEK_SET);

            while (_read (gh, &mblock_subject, 84) == 84) {
                if (mblock_subject > subject_id - idscale
                        && mblock_subject < subject_id + idscale) {
                    rec++;

                    if (rec >= rec_start && rec <= rec_end) {
                        if (col != 0) {
                            while (col < 21) {
                                printf (" ");
                                col++;
                            }

                            col = 0;
                        }

                        sprintf (textbuffer, "(%d)", rec);
                        msg (textbuffer);
                        query = 1;
                        i = 0;

                        while (i < 76 && mblock_message[i]) {
                            if (i == 0 || mblock_message[i] == 32) {
                                j = i + 1;
                                pre = col + 1;

                                while (j < 76 && mblock_message[j] != 32 && mblock_message[j] != 0) {
                                    if (pre >= 21) {
                                        while (col < 21) {
                                            printf (" ");
                                            col++;
                                        }

                                        col = 0;

                                        if (i != 0) {
                                            i++;
                                        }

                                        goto wordwrap;
                                    }

                                    pre++;
                                    j++;
                                }
                            }

wordwrap:

                            if (col == 0 && mblock_message[i] == 32) {
                                goto removeleadingspace;
                            }

                            printf ("%c", mblock_message[i]);
                            col++;

                            if (col > 20) {
                                col = 0;
                            }

removeleadingspace:
                            i++;
                        }
                    }
                }
            }

            if (!query) {
                msg ("THERE WERE NO RECORDS");
                msg ("IN THE GUIDE RELATING");
                msg ("SPECIFIED SUBJECT.");
            } else {
                msg ("");
            }

            _close (gh);
        }
    }

    _close (fh);
}