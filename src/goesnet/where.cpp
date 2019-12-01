/*

    Noctis galactic guide / WHERE command.
    GOES Net Module.

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


char msgbuffer[77];
char* divider = (char*)"&&&&&&&&&&&&&&&&&&&&&";

void msg (char* string) {
    int x;
    strcpy (msgbuffer, string);
    msgbuffer[21] = 0;
    printf("%s", msgbuffer);
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

int     i;
FILE* 	fh;
char*   file = (char*)"data/STARMAP.BIN";

char    outbuffer[40];
char    textbuffer[40];
char    parbuffer[160];
char    nullbuffer[128];
char    objectname[21];
char    subjectname[21];
char    parentname[21];

char find (char* starname) {
    int p, n, ctc, found;
    ctc = strlen(starname);

    if (ctc > 20 || ctc <= 0) {
        msg ((char*)"INVALID OBJECT NAME.");
        return (0);
    }

    n = 0;
    found = 0;
    fseek(fh, 4, SEEK_SET);

    while (fread(&s_object_id, 1, 8, fh) && fread(&s_object_label, 1, 24, fh) == 24) {
        if (memcmp(&s_object_id, "Removed:", 8)) {
            if (!memcmp(s_object_label, starname, ctc)) {
                n++;
                memcpy(object_label, s_object_label, 24);
                object_id = s_object_id;
                memcpy(subjectname, object_label, 20);
                subject_id = object_id;

                //
                if (object_label[21] == 'P') {
                    subject_id -= (object_label[22] - '0') * 10;
                    subject_id -= (object_label[23] - '0');
                }

                //
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
        msg ((char*)"OBJECT NOT FOUND.");
    }

    if (n > 1) {
        msg ((char*)"AMBIGUOUS SEARCH KEY:");
        msg ((char*)"PLEASE EXPAND NAME...");
        msg (divider);
        msg ((char*)"POSSIBLE RESULTS ARE:");
        msg (divider);
        fseek (fh, 4, SEEK_SET);

        while (fread(&s_object_id, 1, 8, fh) && fread(&s_object_label, 1, 24, fh) == 24) {
            if (memcmp (&s_object_id, "Removed:", 8)
                    && !memcmp (s_object_label, starname, ctc)) {
                s_object_label[21] = 0;
                msg (s_object_label);
            }
        }

        msg (divider);
        found = 0;
    }

    return found;
}

int main (int argc, char** argv) {
    char query;

    /* Printed if not run from Noctis
    printf ("\nGalactic Organization of Explorers and Stardrifters (G.O.E.S)\n");
    printf ("-------------------------------------------------------------\n");
    printf ("This is a GOES NET module and must be run from a stardrifter.\n");
    printf ("Please use the onboard computer console to run this module.\n");
    printf ("\n\t- GOES NET onboard microsystem, EPOC 6011 REVISION 2\n");
    return; */

    if (argc < 2) {
        msg ((char*)"________USAGE________");
        msg ((char*)"WHERE PLANETNAME");
        msg ((char*)"^^^^^^^^^^^^^^^^^^^^^");
        msg ((char*)"PLEASE RUN AGAIN,");
        msg ((char*)"SPECIFYING PARAMETERS");
        return 0;
    } else {
        msg ((char*)"  GOES GALACTIC MAP  ");
        msg (divider);
    }

    fh = fopen(file, "r");

    if (fh == nullptr) {
        msg ((char*)"STARMAP NOT AVAILABLE");
        return 2;
    }

    i = 2;
    strcpy(parbuffer, argv[1]);

    while (i < argc) {
        strcat(parbuffer, " ");
        strcat(parbuffer, argv[i]);
        i++;
    }

    strcpy(objectname, parbuffer);
    query = find (objectname);

    if (query) {
        if (query == 1) {
            msg ((char*)"THIS OBJECT IS A STAR");
            msg ((char*)"AND ITS POSITION CAN");
            msg ((char*)"BE DETERMINED USING");
            msg ((char*)"THE 'PAR' MODULE.");
        } else {
            fseek(fh, 4, SEEK_SET);

            while (fread(&s_object_id, 1, 8, fh) && fread(&s_object_label, 1, 24, fh) == 24) {
                if (memcmp (&s_object_id, "Removed:", 8)) {
                    if (s_object_id >= subject_id - idscale
                            && s_object_id <= subject_id + idscale) {
                        s_object_label[20] = 0;
                        msg (subjectname);
                        msg ((char*)"IS PART OF THE");
                        msg (s_object_label);
                        msg ((char*)"SYSTEM.");
                        
			fclose(fh);
			return 0;
                    }
                }
            }

            msg ((char*)"UNABLE  TO  DETERMINE");
            msg ((char*)"THIS PLANET'S  PARENT");
            msg ((char*)"STAR;  PROBABLY, THAT");
            msg ((char*)"STAR ISN'T CATALOGUED");
        }
    }

    fclose(fh);

    return 0;
}
