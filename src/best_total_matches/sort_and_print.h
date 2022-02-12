#ifndef PROJECT_SORT_AND_PRINT_H
#define PROJECT_SORT_AND_PRINT_H

#include "../search/search.h"

void print_one_match(enkele_totale_match* enkele_totale_match);
void print_best_matches(totale_matches* totale_matches,int amount);

int compare_totale_match_by_score(const void* a, const void* b);
void sort_by_score(totale_matches* totale_matches);

#endif //PROJECT_SORT_AND_PRINT_H
