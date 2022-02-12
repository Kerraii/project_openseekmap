#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "editeerafstand.h"
#include "../sanitize/sanitize.h"

/* min int van 3 getallen */
int min_int_3(int a, int b, int c) {
    return min_int(min_int(a, b), c);
}

/* min int */
int min_int(int a, int b) {
    if (a <= b) {
        return a;
    }
    return b;
}

/* geheugen efficiente versie uit oefeningenles
 * NOTE: t1 is al gesanitized
 */
int bepaal_editeerafstand(char* t1, char* t2_) {

    // sanitize t2
    char* t2 = sanitize(t2_);

    long lengte_t1 = (long) strlen(t1);
    long lengte_t2 = (long) strlen(t2);

    // als woorden te veel in lengte verschillen return early
    // niet meer nodig sinds dat databank sorted is op lengte!
    /*
    if(lengte_t2 - lengte_t1 > 2 || lengte_t2 - lengte_t1 < -2) {
        free(t2);
        return 4;
    }
     */

    int vorige[lengte_t2+1];
    int nieuwe[lengte_t2+1];

    for (int i = 0; i <= lengte_t2; ++i) {
        vorige[i] = i;
        nieuwe[i] = 0;
    }

    for (int i = 1; i <= lengte_t1; ++i) {
        nieuwe[0] = i;
        for (int j = 1; j <= lengte_t2; ++j) {
            if (t1[i-1] == t2[j-1]) {
                nieuwe[j] = vorige[j-1];
            }
            // swap 2 letters die naast elkaar staan + prevent foute dubbel swap
            // foute dubbel swap: "aba" en "bab" != editeeraftand 1
            else if (i != lengte_t1 && j != lengte_t2 && t1[i-1] == t2[j] && t1[i] == t2[j-1]) {
                if (i > 1 && j > 1 &&t1[i-2] == t2[j-1] && t1[i-1] == t2[j-2]) {
                    nieuwe[j] = min_int_3(vorige[j - 1] + 1, vorige[j] + 1, nieuwe[j - 1] + 1);
                } else {
                    nieuwe[j] = vorige[j-1];
                }
            } else {
                nieuwe[j] = min_int_3(vorige[j - 1] + 1, vorige[j] + 1, nieuwe[j - 1] + 1);
            }
        }
        for (int j = 0; j <= lengte_t2; ++j) {
            vorige[j] = nieuwe[j];
        }
    }
    free(t2);
    return nieuwe[lengte_t2];
}

/* geheugen inefficiente versie uit cursus
 * deze wordt niet meer gebruikt
 * deze houdt geen rekening met verwijderen van accenten en hoofdletters
 */
/*
int bepaal_editeerafstand_(char* t1, char* t2) {
    // niet leeg
    assert(strcmp(t1, "") != 0);
    assert(strcmp(t2, "") != 0);

    unsigned long lengte_t1 = strlen(t1);
    unsigned long lengte_t2 = strlen(t2);

    if(lengte_t2 - lengte_t1 > 2 || lengte_t2 - lengte_t1 < -2) {
        return 4;
    }

    int d[lengte_t1+1][lengte_t2+1];

    for (int i = 0; i <= lengte_t1; i++) {
        for (int j = 0; j <= lengte_t2; j++) {
            d[i][j] = 0;
        }
    }

    for (int i = 0; i <= lengte_t1; i++) {
        d[i][0] = i;
    }

    for (int i = 0; i <= lengte_t2; i++) {
        d[0][i] = i;
    }

    for (int i = 1; i <= lengte_t1; i++) {
        for (int j = 1; j <= lengte_t2; j++) {
            int wissel_kost = 1;
            if (t1[i-1] == t2[j-1]) {
                wissel_kost = 0;
            }
            d[i][j] = min_int_3(d[i-1][j-1] + wissel_kost, d[i-1][j]+1, d[i][j-1]+1);
            if (i > 1 && j > 1 && t1[i-1] == t2[j-2] && t1[i-2] == t2[j-1]) {
                d[i][j] = min_int(d[i][j], d[i-2][j-2] + 1);
            }
        }
    }
    return d[lengte_t1][lengte_t2];
}
 */