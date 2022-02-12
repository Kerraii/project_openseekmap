
#include "shiftand.h"
#include <string.h>
#include <stdlib.h>

#include <assert.h>

// bereken karakteristieke vectoren
unsigned long long* bereken_karakteristieke_vectoren(char* z, unsigned long amount_of_chars) {
    unsigned long long *res = malloc(amount_of_chars*sizeof(unsigned long long));
    assert(res);

    // init res to 0
    memset(res, 0, amount_of_chars*sizeof(unsigned long long));

    // get karakteristieke vectoren
    for (int i = (int) strlen(z)-1; i >= 0; i--) {
        res[(int) z[i]] = res[(int) z[i]] | (0x1u << (strlen(z) - i - 1));
    }

    return res;
}

/*
void quick_test_shift_and() {
    printf("d - bananas - 0? => %i\n", shiftAND("d", "bananas"));
    printf("a - bananas - 1? => %i\n", shiftAND("a", "bananas"));
    printf("ab - bananas - 0? => %i\n", shiftAND("ab", "bananas"));
    printf("ba - bananas - 1? => %i\n", shiftAND("ba", "bananas"));
    printf("ananana - bananas 0? => %i\n", shiftAND("ananana", "bananas"));
    printf("banana - bananas - 1? => %i\n", shiftAND("banana", "bananas"));
    printf("bananas - bananas - 1? => %i\n", shiftAND("bananas", "bananas"));
    printf("ab - zzbazz - 0? => %i\n", shiftAND("ab", "zzbazz"));
}
 */

// shiftAnd enkel voor ASCII
// deze functie wordt niet meer gebruikt in de werkelijke inplementatie van het opzoeken
int shiftAND(char *z, char *t) {
    unsigned long lengte_zoek = strlen(z);
    unsigned long lengte_tekst = strlen(t);
    unsigned long long kolom = 0;

    if (((int)lengte_tekst) - ((int) lengte_zoek) < 0){
        return 0;
    }

    // bereken karakteristieke vectoren
    // note: de bitvector is in 'andere' richting dan in de cursur
    unsigned long long* vectoren = bereken_karakteristieke_vectoren(z, AMOUNT_ASCII);
    if (z[0] == t[0]) {
        if (lengte_zoek == 1) {
            free(vectoren);
            return 1;
        }
        kolom = kolom | (0x1u << (lengte_zoek-1));
    }

    for(int j = 1; j < lengte_tekst; j++) {
        // shift 1 naar links en zet nieuwe bit op 1
        kolom = ((kolom >> 0x1u) | (0x1u << (lengte_zoek-1))) & vectoren[(int) t[j]];
        if ((kolom & 0x1u) > 0) {
            free(vectoren);
            return 1;
        }
    }

    // free vectors
    free(vectoren);
    return 0;
}



