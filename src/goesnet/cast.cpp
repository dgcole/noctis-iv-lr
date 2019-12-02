/*

    Noctis galactic guide / CAST command.
    GOES Net Module.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char msgbuffer[40];
char *divider = "&&&&&&&&&&&&&&&&&&&&&";

void strupr(char *str) {
    while (*str) {
        *str = toupper(*str);
        str++;
    }
}

void msg(char *string) {
    int x;
    strcpy(msgbuffer, string);
    msgbuffer[21] = 0;
    printf(msgbuffer);
    x = strlen(msgbuffer);

    while (x < 21) {
        printf(" ");
        x++;
    }
}

double object_id = 12345;
char object_label[25];
double s_object_id = 12345;
char s_object_label[25];

double subject_id = 12345;

long round;
int i, mlen;
FILE *fh, *gh;
char *file  = "data/STARMAP.BIN";
char *guide = "data/GUIDE.BIN";

char outbuffer[40];
char textbuffer[40];
char parbuffer[160];
char nullbuffer[128];
char objectname[21];
char subjectname[21];

char find(char *starname) {
    int p, n, ctc, found;
    ctc = strlen(starname);

    if (ctc > 20 || ctc <= 0) {
        msg("INVALID OBJECT NAME.");
        return (0);
    }

    n     = 0;
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
        msg("OBJECT NOT FOUND.");
    }

    if (n > 1) {
        msg("AMBIGUOUS SEARCH KEY:");
        msg("PLEASE EXPAND NAME...");
        msg(divider);
        msg("POSSIBLE RESULTS ARE:");
        msg(divider);
        fseek(fh, 4, SEEK_SET);

        while (fread(&s_object_id, 1, 8, fh) &&
            fread(&s_object_label, 1, 24, fh) == 24) {
            if (memcmp(&s_object_id, "Removed:", 8) &&
                !memcmp(s_object_label, starname, ctc)) {
                s_object_label[21] = 0;
                msg(s_object_label);
            }
        }

        msg(divider);
        found = 0;
    }

    return (found);
}

int main(int argc, char** argv) {
    char query;

    /*printf ("\nGalactic Organization of Explorers and Stardrifters
    (G.O.E.S)\n"); printf
    ("-------------------------------------------------------------\n"); printf
    ("This is a GOES NET module and must be run from a stardrifter.\n"); printf
    ("Please use the onboard computer console to run this module.\n"); printf
    ("\n\t- GOES NET onboard microsystem, EPOC 6011 REVISION 2\n"); return;*/

    if (argc < 2) {
        msg("________USAGE________");
        msg("CAST OBJECTNAME:NOTES");
        msg("^^^^^^^^^^^^^^^^^^^^^");
        msg("PLEASE RUN AGAIN,");
        msg("SPECIFYING PARAMETERS");
        return 1;
    } else {
        msg(" GOES GALACTIC GUIDE ");
        msg(divider);
    }

    fh = fopen(file, "r+");

    if (fh == nullptr) {
        msg("STARMAP NOT AVAILABLE");
        return 1;
    }

    i = 2;
    strcpy(parbuffer, argv[1]);

    while (i < argc) {
        strcat(parbuffer, " ");
        strcat(parbuffer, argv[i]);
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

    if (parbuffer[i] != ':') {
        msg("SYNTAX ERROR:");
        msg("MISSING COLON BETWEEN");
        msg("OBJECT NAME AND NOTES");
    } else {
        strupr(parbuffer);
        strupr(objectname);

        if (parbuffer[i + 1] == 0) {
            msg("VOID MESSAGE:");
            msg("WAS NOT SENT.");
        } else {
            objectname[i] = 0;
            query         = find(objectname);

            if (query) {
                msg("TRANSFER SUCCEDED:");
                msg(divider);

                if (query == 1) {
                    msg("SUBJECT: STAR;");
                }

                if (query == 2) {
                    msg("SUBJECT: PLANET;");
                }

                sprintf(outbuffer, "NAME: %s", subjectname);
                msg(outbuffer);
                msg("MESSAGE SENT;");
                gh = fopen(guide, "r+");

                if (gh == nullptr) {
                    msg("DATABASE ERROR;");
                    msg("MESSAGE REJECTED.");
                    msg("(ERROR CODE 1001)");
                } else {
                    mlen = strlen(parbuffer + i + 1);
                    fseek(gh, 0, SEEK_END);
                    fwrite(&subject_id, 1, 8, gh);
                    fwrite(&parbuffer[i + 1], 1, mlen, gh);
                    long fpos = ftell(gh);
                    fseek(gh, 0, SEEK_END);
                    round = ftell(gh);
                    fseek(gh, fpos, SEEK_SET);

                    if (round >= 0) {
                        round %= 84;

                        if (round) {
                            round = 84 - round;
                            fwrite(nullbuffer, 1, round, gh);
                        }

                        msg("MESSAGE ACCEPTED.");
                    } else {
                        msg("DATABASE ERROR;");
                        msg("MESSAGE REJECTED.");
                        msg("(ERROR CODE 1002)");
                    }

                    fclose(gh);
                }
            }
        }
    }

    fclose(fh);
}