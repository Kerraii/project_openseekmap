#include "match_combinator.h"
#include "../score_calculator/score_calculator.h"

#include <stdlib.h>
#include <assert.h>

/* allocate de combinatie van entries van een totale match */
entry_combination* entry_combination_alloc(int size) {
    entry_combination* res = malloc(sizeof(entry_combination));
    assert(res);
    res->amount_of_entries = size;
    res->entries_of_combination = malloc(size*sizeof(entry*));
    assert(res->entries_of_combination);
    res->editeer_afstanden = malloc(size*sizeof(int));
    assert(res->editeer_afstanden);
    for (int i = 0; i < size; ++i) {
        res->editeer_afstanden[i] = 0;
    }
    return res;
}

/* free de combinatie van entries van een totale match */
void entry_combination_free(entry_combination* entry_combination) {
    free(entry_combination->entries_of_combination);
    free(entry_combination->editeer_afstanden);
    free(entry_combination);
}

/* vraag de volgende combinatie op */
void next_combination(int* current_combination, const int* max_matches_sizes, int size) {
    for (int i = size-1; i >= 0; i--) {
        if(current_combination[i] == max_matches_sizes[i]-1) {
            current_combination[i] = 0;
        } else {
            current_combination[i]++;
            return;
        }
    }
}

/* kijk of we de enkele totale match (op basis van score) in de top 5 kunnen plaatsen
 * Indien dit zo is zullen we hem daar plaatsen en de laagste verwijderen (niet gesorteerd)
 * en anders zullen we hem vrijgeven
 */
void place_in_top_5(totale_matches* totale_matches, enkele_totale_match* enkele_totale_match) {
    if (totale_matches->totaal_aantal != MAX_TOTALE_MATCHES) {
        totale_matches->totale_matches[totale_matches->totaal_aantal] = enkele_totale_match;
        totale_matches->totaal_aantal++;
    } else {
        int min_index = 0;
        double min_score = totale_matches->totale_matches[0]->totaal_score;
        for (int i = 1; i < MAX_TOTALE_MATCHES; ++i) {
            // nieuw minimum
            if (min_score > totale_matches->totale_matches[i]->totaal_score) {
                min_index = i;
                min_score = totale_matches->totale_matches[i]->totaal_score;
            }
        }
        if (totale_matches->totale_matches[min_index]->totaal_score < enkele_totale_match->totaal_score) {
            enkele_totale_match_free(totale_matches->totale_matches[min_index]);
            totale_matches->totale_matches[min_index] = enkele_totale_match;
        } else {
            enkele_totale_match_free(enkele_totale_match);
        }
    }
}

/* bepaal de totale matches van 1 combinatie en plaats deze in de totale matches top 5 indien nodig */
void combinatie_matches(match_z** match_list, int size, totale_matches* totale_matches) {
    // init
    int matched_entries_lengths[size];
    int current_combination[size];
    for (int i = 0; i < size; ++i) {
        matched_entries_lengths[i] = 0;
        current_combination[i] = 0;
    }

    // zet de lengtes van aantal matches juist & bereken het totaal aantal totale matches
    long aantal_combinaties = 1;
    for (int i = 0; i < size; i++) {
        aantal_combinaties *= match_list[i]->matches_size;
        matched_entries_lengths[i] = match_list[i]->matches_size;
    }

    int index = 0;
    while (index < aantal_combinaties) {
        // zet de entries juist met de huidige combinatie & editeerafstand
        entry_combination* combination = entry_combination_alloc(size);
        for (int i = 0; i < size; ++i) {
            combination->entries_of_combination[i] = match_list[i]->matched_entries[current_combination[i]];
            combination->editeer_afstanden[i] = match_list[i]->editeer_afstand[current_combination[i]];
        }

        // bereken scores van huidige combinatie & update de struct
        enkele_totale_match* current_match = calculate_score(combination, totale_matches->lengte_lig, totale_matches->breedte_lig);
        place_in_top_5(totale_matches, current_match);

        // bereken volgende combinatie
        next_combination(current_combination, matched_entries_lengths, size);

        // free de huidige combinatie
        entry_combination_free(combination);

        // update index
        index++;
    }
}
