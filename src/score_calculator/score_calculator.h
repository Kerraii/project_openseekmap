#ifndef PROJECT_SCORE_CALCULATOR_H
#define PROJECT_SCORE_CALCULATOR_H

#include "../search/search.h"
#include "../combinator/match_combinator.h"
#include "../editeerafstand/editeerafstand.h"

// extends voor rang
const static double extends[] = {
        100000,
        50000,
        10000,
        1000,
        750,
        600,
        500,
        350,
        200,
        100,
        75,
        50,
        10,
        9,
        7.5,
        6,
        4.5,
        4,
        2,
        1,
        0.8,
        0.7,
        0.6,
        0.5,
        0.4,
        0.3,
        0.2,
        0.1,
        0.05,
        0.01
};

double get_extend(int rang);
double max_double(double a, double b);
double calculate_rosetta(entry *entry1, entry *entry2);
double calculate_synergie_1(entry *entry1, entry *entry2);

void set_max_rang(entry_combination *entry_combination, enkele_totale_match *enkele_totale_match);
double calculate_locatie(entry* entry_max_rang, double lengte_lig, double breedte_lig);
double calculate_synergie(entry_combination *entry_combination);
double calculate_correctheid(entry_combination *entry_combination);

enkele_totale_match *calculate_score(entry_combination *entry_combination, double lengte_lig, double breedte_lig);


#endif //PROJECT_SCORE_CALCULATOR_H
