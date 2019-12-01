/*

    Noctis galactic guide / CAT command.
    GOES Net Module.

*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char msgbuffer[77];
char* divider = (char*)"&&&&&&&&&&&&&&&&&&&&&";

void msg (char* string)
{
    int x;
    strcpy (msgbuffer, string);
    msgbuffer[21] = 0;
    printf ("%s", msgbuffer);
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
int     i;
FILE* 	fh;
FILE* 	gh;
const char*   file = "data/STARMAP.BIN";
const char*   guide = "data/GUIDE.BIN";

char    outbuffer[40];
char    textbuffer[40];
char    parbuffer[160];
char    nullbuffer[128];
char    objectname[21];
char    subjectname[21];

double  mblock_subject;
char    mblock_message[77];

char find (char* starname)
{
    int p, n, ctc, found;
    ctc = strlen (starname);

    if (ctc > 20 || ctc <= 0) {
        msg ((char*)"INVALID OBJECT NAME.");
        return (0);
    }

    n = 0;
    found = 0;
    fseek (fh, 4, SEEK_SET);

    while (fread(&s_object_id, 1, 8, fh) && fread(&s_object_label, 1, 24, fh) == 24) {
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
        msg ((char*)"OBJECT NOT FOUND.");
    }

    if (n > 1) {
        msg ((char*)"AMBIGUOUS SEARCH KEY:");
        msg ((char*)"PLEASE EXPAND NAME...");
        msg (divider);
        msg ((char*)"POSSIBLE RESULTS ARE:");
        msg (divider);
        fseek (fh, 4, SEEK_SET);

        while (fread (&s_object_id, 1, 8, fh) && fread(&s_object_label, 1, 24, fh) == 24) {
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

int main (int argc, char** argv)
{
    char query;
    int j, col, pre;
    int is, rec, rec_start, rec_end;

    /* This is printed if this is not run by Noctis,
     * 	but the check for this still needs to be implemented */
    goto startup;

    /*
	printf ("\nGalactic Organization of Explorers and Stardrifters (G.O.E.S)\n");
    	printf ("-------------------------------------------------------------\n");
    	printf ("This is a GOES NET module and must be run from a stardrifter.\n");
    	printf ("Please use the onboard computer console to run this module.\n");
    	printf ("\n\t- GOES NET onboard microsystem, EPOC 6011 REVISION 2\n");
    	return; */
startup:

    if (argc < 2) {
        msg ((char*)"________USAGE________");
        msg ((char*)"CAT OBJECTNAME");
        msg ((char*)"CAT OBJECTNAME:X..Y");
        msg ((char*)"^^^^^^^^^^^^^^^^^^^^^");
        msg ((char*)"PLEASE RUN AGAIN,");
        msg ((char*)"SPECIFYING PARAMETERS");
        return 0; //Not sure if should return 0
    } else {
        msg ((char*)" GOES GALACTIC GUIDE ");
        msg (divider);
    }

    fh = fopen(file, "r"); //Not sure if it should be binary mode or normal

    if (fh == NULL) {
        msg ((char*)"STARMAP NOT AVAILABLE");
        return 0; //Not sure if should return 0
    }

    i = 2;
    strcpy (parbuffer, argv[1]);

    while (i < argc) {
        strcat (parbuffer, " ");
        strcat (parbuffer, argv[i]);
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
        msg ((char*)"INVALID SUBJECT NAME.");
        fclose(fh);
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
            msg ((char*)"SUBJECT: STAR;");
        }

        if (query == 2) {
            msg ((char*)"SUBJECT: PLANET;");
        }

        msg (subjectname);
        msg (divider);
        gh = fopen(guide, "r");

        if (gh == NULL) {
            msg ((char*)"DATABASE ERROR.");
            msg ((char*)"(ERROR CODE 1003)");
        } else {
            rec = 0;
            col = 0;
            query = 0;
            fseek (gh, 4, SEEK_SET);

            while (fread(&mblock_subject, 1, 84, gh) == 84) { //Should size be 1 byte?
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
                msg ((char*)"THERE WERE NO RECORDS");
                msg ((char*)"IN THE GUIDE RELATING");
                msg ((char*)"SPECIFIED SUBJECT.");
            } else {
                msg ((char*)"");
            }

            fclose(gh);
        }
    }

    fclose(fh);
}
