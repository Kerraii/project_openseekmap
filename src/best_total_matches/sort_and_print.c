#include "sort_and_print.h"
#include <stdlib.h>
#include <stdio.h>

/* compare functie voor 1 totale match */
int compare_totale_match_by_score(const void* a, const void* b) {
    enkele_totale_match* totale_match1 = *(enkele_totale_match**) a;
    enkele_totale_match* totale_match2 = *(enkele_totale_match**) b;

    if (totale_match1->totaal_score < totale_match2->totaal_score) {
        return 1;   // a < b -> 1 want b moet eerder
    } else if (totale_match1->totaal_score > totale_match2->totaal_score) {
        return -1;  // a > b -> -1 want a moet eerder
    } else {
        return 0;   // gelijk
    }
}

/* sorteer de totale matches op beste score */
void sort_by_score(totale_matches* totale_matches) {
    qsort(totale_matches->totale_matches, totale_matches->totaal_aantal, sizeof(enkele_totale_match*), compare_totale_match_by_score);
}

/* print 1 totale match */
void print_one_match(enkele_totale_match* enkele_totale_match) {
    printf("\n%s (%ld)\ngeo:%f,%f\n~\n", enkele_totale_match->match->name, enkele_totale_match->match->identifier, enkele_totale_match->match->lengtelig, enkele_totale_match->match->breedtelig);
}

/* print beste amount (5) matches */
void print_best_matches(totale_matches* totale_matches,int amount) {
    // amount is groter dan aantal matches
    if (totale_matches->totaal_aantal < amount) {
        amount = totale_matches->totaal_aantal;
    }

    // geen matches
    if (amount == 0) {
        printf("\nGeen totale matches gevonden!\n");
    }

    // print elke match
    for (int i = 0; i < amount; i++) {
        print_one_match(totale_matches->totale_matches[i]);
    }
}
