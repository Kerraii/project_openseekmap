#include "../search/search.h"

#ifndef PROJECT_MATCH_COMBINATOR_H
#define PROJECT_MATCH_COMBINATOR_H

/* de combinatie van entries van een totale match */
typedef struct {
    int amount_of_entries;
    entry** entries_of_combination;
    int* editeer_afstanden;
} entry_combination;

entry_combination* entry_combination_alloc(int size);
void entry_combination_free(entry_combination* entryCombination);

void next_combination(int* current_combination, const int* max_matches_sizes, int size);

void combinatie_matches(match_z** match_list, int size, totale_matches* totale_matches);

#endif //PROJECT_MATCH_COMBINATOR_H
