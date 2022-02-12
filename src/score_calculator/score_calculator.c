#include "score_calculator.h"
#include "rosetta.h"
#include "math.h"
#include <string.h>

/* max double */
double max_double(double a, double b) {
    if (a >= b) {
        return a;
    }
    return b;
}

/* min double */
double min_double(double a, double b) {
    if (a <= b) {
        return a;
    }
    return b;
}

/* berekent de Haversine afstand */
double calculate_rosetta(entry* entry1, entry* entry2) {
    return d_geo(entry1->lengtelig, entry1->breedtelig, entry2->lengtelig, entry2->breedtelig);
}

/* brekent de extend van een rang */
double get_extend(int rang) {
    return extends[rang-1];
}

/* bepaald de entry met de hoogste rang en plaatst deze in de totale match */
void set_max_rang(entry_combination* entry_combination, enkele_totale_match* enkele_totale_match) {
    int max_rang = 0;
    for (int i = 0; i < entry_combination->amount_of_entries; ++i) {
        if (entry_combination->entries_of_combination[i]->rang > max_rang) {
            enkele_totale_match->match = entry_combination->entries_of_combination[i];
            max_rang = entry_combination->entries_of_combination[i]->rang;
        }
    }
}

/* formule voor locatie */
double calculate_locatie(entry* entry_max_rang, double lengte_lig, double breedte_lig) {
    //log(1000, a) = log(a)/log(1000)
    double teller = d_geo(entry_max_rang->lengtelig, entry_max_rang->breedtelig, lengte_lig, breedte_lig);
    double noemer = get_extend(entry_max_rang->rang);

    double teller_log = log(teller/noemer);
    double noemer_log = log(1000);

    return min_double(1,max_double(0, 1 - teller_log/noemer_log));
}

/* deelformule van synergie S1(vi, vj) */
double calculate_synergie_1(entry* entry1, entry* entry2) {
    double arg2 = pow(max_double(get_extend(entry1->rang), get_extend(entry2->rang))/calculate_rosetta(entry1, entry2), 2);
    return min_double(2, arg2);
}

/* formule voor synergie */
double calculate_synergie(entry_combination* entry_combination) {
    double synergie = 0;
    int n = entry_combination->amount_of_entries;
    if (n < 2) {
        return 1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i<j) {
                synergie += calculate_synergie_1(entry_combination->entries_of_combination[i], entry_combination->entries_of_combination[j]);
            }
        }
    }
    synergie = synergie/(n*(n-1));
    return synergie;
}

/* formule correctheid */
double calculate_correctheid(entry_combination* entry_combination) {
    double som_lengte = 0;
    double som_editeer_afstand = 0;
    for (int i = 0; i < entry_combination->amount_of_entries; ++i) {
        som_lengte += (double) strlen(entry_combination->entries_of_combination[i]->name);
        som_editeer_afstand += entry_combination->editeer_afstanden[i];
    }
    return (som_lengte-som_editeer_afstand)/som_lengte;
}

/* berekent score van 1 totale match */
enkele_totale_match* calculate_score(entry_combination* entry_combination, double lengte_lig, double breedte_lig) {
    enkele_totale_match* res = enkele_totale_match_alloc();
    // correctheid
    double correctheid_score = calculate_correctheid(entry_combination);

    // synergy
    double synergie_score = calculate_synergie(entry_combination);

    // update max rang + entry
    set_max_rang(entry_combination, res);

    // max rang score
    double max_rang_score = res->match->rang/30.00;

    // lengte/breedte ligging gegeven
    if (lengte_lig != -1) {
        // locatie score berekenen
        double locatie_score = calculate_locatie(res->match, lengte_lig, breedte_lig);
        res->totaal_score = 0.15 * correctheid_score + 0.55 * synergie_score + 0.15 * max_rang_score + 0.15 * locatie_score;
    } else {
        // geen lengte/breedte ligging gegeven
        res->totaal_score = 0.2 * correctheid_score + 0.7 * synergie_score + 0.1 * max_rang_score;
    }

    return res;
}

