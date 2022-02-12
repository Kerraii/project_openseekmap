#include "search.h"
#include "../editeerafstand/editeerafstand.h"
#include "../combinator/match_combinator.h"
#include "../sanitize/sanitize.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* allocate enkele totale match */
enkele_totale_match* enkele_totale_match_alloc() {
    enkele_totale_match* res = malloc(sizeof(enkele_totale_match));
    assert(res);
    return res;
}

/* free enkele totale match */
void enkele_totale_match_free(enkele_totale_match* enkele_totale_match) {
    free(enkele_totale_match);
}

/* allocate totale matches totale match */
totale_matches* totale_matches_alloc() {
    totale_matches* res = malloc(sizeof(totale_matches));
    assert(res);
    res->totaal_aantal = 0;
    res->lengte_lig = 0;
    res->breedte_lig = 0;
    res->totale_matches = malloc(MAX_TOTALE_MATCHES*sizeof(enkele_totale_match*));
    assert(res->totale_matches);
    return res;
}

/* free totale matches totale match */
void totale_matches_free(totale_matches* totale_matches) {
    for (int i = 0; i < totale_matches->totaal_aantal; ++i) {
        enkele_totale_match_free(totale_matches->totale_matches[i]);
    }
    free(totale_matches->totale_matches);
    free(totale_matches);
}

/* allocate 1 match_z */
match_z* match_z_alloc() {
    match_z* res = malloc(sizeof(match_z));
    assert(res);
    res->matches_size = 0;
    res->max_size = MAX_MATCHES;
    res->matched_entries = malloc(MAX_MATCHES*sizeof(entry*));
    assert(res->matched_entries);
    res->editeer_afstand = malloc(MAX_MATCHES*sizeof(int));
    assert(res->editeer_afstand);
    return res;
}

/* free match_z */
void match_z_free(match_z* match_z) {
    // entries itself are freed when data is freed
    free(match_z->zoek_string);
    free(match_z->matched_entries);
    free(match_z->editeer_afstand);

    free(match_z);
}

/* allocate 1 match_end */
match_end* match_end_alloc(int max_size) {
    match_end* res = malloc(sizeof(match_end));
    assert(res);
    res->max_end_index = max_size;
    res->match_zs = malloc(max_size*sizeof(match_z*));
    assert(res->match_zs);
    return res;
}

/* free 1 match_end */
void match_end_free(match_end* match_end, int start) {
    for (int i = 0; i < match_end->max_end_index; ++i) {
        if (start <= i) {
            match_z_free(match_end->match_zs[i]);
        }
    }
    free(match_end->match_zs);
    free(match_end);
}

/* allocate 1 match start to end */
match_start_to_end* match_start_to_end_alloc(int max_index) {
    match_start_to_end* res = malloc(sizeof(match_start_to_end));
    assert(res);
    res->max_start_index = max_index;
    res->match_matrix = malloc(max_index*sizeof(match_end*));
    assert(res->match_matrix);
    return res;
}

/* free 1 match start to end */
void match_start_to_end_free(match_start_to_end* match_start_to_end) {
    for (int i = 0; i < match_start_to_end->max_start_index; ++i) {
        match_end_free(match_start_to_end->match_matrix[i], i);
    }
    free(match_start_to_end->match_matrix);
    free(match_start_to_end);
}

/* increase max_size van match_z */
void double_size_match_z(match_z* match_z) {
    match_z->max_size = match_z->max_size*2;
    match_z->matched_entries = realloc(match_z->matched_entries, match_z->max_size*sizeof(entry*));
    match_z->editeer_afstand = realloc(match_z->editeer_afstand, match_z->max_size*sizeof(int));
    assert(match_z->matched_entries);
}

/* max voor long */
long max_long(long a, long b) {
    if (a >= b) {
        return a;
    }
    return b;
}

/* enkel editeerafstand gebruiken */
void match1_z(match_z* match_z, data* data, int correctie_index) {
    // zoek enkel op toepasselijke lengtes
    // van woord_len - 2 tot en met woord_len + 2
    char* sanitized = sanitize(match_z->zoek_string);
    long length = (long) strlen(sanitized);
    long start = data->index_list[max_long(0,length-3)];
    long stop;
    if (length < MAX_SORT_WORD_LENGTH - 1) {
        stop = data->index_list[length+2] - 1;
    } else {
        start = data->index_list[MAX_SORT_WORD_LENGTH-1];
        stop = data->size;
    }

    /* zoek op editeerafstand
     * correctie_index is 0 wanneer het totaal aantal woorden in de input <= 3 is
     * correctie_index is 1 wannner er 4 of meer woorden in de input zijn
     * zo zal de code sneller werken indien er meerdere woorden ingegeven werden
     */
    for (long i = start; i < stop; ++i) {
        int editeerafstand = bepaal_editeerafstand(sanitized, data->entries[i]->name);
        if (editeerafstand + correctie_index <= min_int(3, 1 + (int) strlen(data->entries[i]->name) / 3)) {
            match_z->matched_entries[match_z->matches_size] = data->entries[i];
            match_z->editeer_afstand[match_z->matches_size] = editeerafstand;
            match_z->matches_size++;
            if (match_z->matches_size == match_z->max_size) {
                double_size_match_z(match_z);
            }
        }
    }
    free(sanitized);
}

/* eerst shift and en dan op die matches editeerafstand gebruiken
 * niet gebruiken! oude versie
 */
/*
void match1_z_2(match_z* match_z, data* data) {
    for (int i = 0; i < data->size; ++i) {
        if (shiftAND(match_z->zoek_string, data->entries[i]->name)) {
            int editeerafstand = bepaal_editeerafstand(match_z->zoek_string, data->entries[i]->name);
            if (editeerafstand <= min_int(3, 1 + (int) strlen(data->entries[i]->name) / 3)) {
                match_z->matched_entries[match_z->matches_size] = data->entries[i];
                match_z->editeer_afstand[match_z->matches_size] = editeerafstand;
                match_z->matches_size++;
                if (match_z->matches_size == match_z->max_size) {
                    double_size_match_z(match_z);
                }
            }
        }
    }

}
 */

/* debug print alle gevonden matches */
void print_debug_matches(match_start_to_end* res, int start, int end) {
    printf("searching for: %s\n", res->match_matrix[start]->match_zs[end]->zoek_string);
    for (int i = 0; i < res->match_matrix[start]->match_zs[end]->matches_size; ++i) {
        printf("m: %s || %i\n", res->match_matrix[start]->match_zs[end]->matched_entries[i]->name, res->match_matrix[start]->match_zs[end]->editeer_afstand[i]);
    }
    printf("totale_matches: %i\n", res->match_matrix[start]->match_zs[end]->matches_size);
    printf("-------------------------------\n");
}

/* stel de match_end matrix op dit is een triangulaire matrix
 * deze bevat elke mogelijke opsplitsing van woorden en zoekt die exact 1 keer op
 * "De" "Sterre" "Gent" "De Sterre" "Sterre Gent" "De Sterre Gent"
 */
match_start_to_end* create_match_end(int max_size, all_combinaties* all_combinaties, data* data) {
    match_start_to_end* res = match_start_to_end_alloc(max_size);

    // gebruikt om te zoeken op editeerafstand
    int correctie_index = all_combinaties->words > 3 ? 1 : 0;

    for (int start = 0; start < max_size; ++start) {
        res->match_matrix[start] = match_end_alloc(max_size);
        // end start eigenlijk op 1 maar we slaan ze op in 0 om het kleine beetje plaats te besparen
        for (int end = 0; end < max_size; ++end) {
            // triangulair nu
            if (start <= end) {
                res->match_matrix[start]->match_zs[end] = match_z_alloc();

                // vul de match_z
                res->match_matrix[start]->match_zs[end]->zoek_string = get_string_from_combination(start, end+1, all_combinaties->word_list);
                match1_z(res->match_matrix[start]->match_zs[end], data, correctie_index);

                // print debug if broken
                // print_debug_matches(res, start, end);
            }
        }
    }
    return res;
}

/* get match_z object uit de matrix op een bepaalde plaats */
match_z* get_matches(int start_index, int end_index, match_start_to_end* match_start_to_end) {
    return match_start_to_end->match_matrix[start_index]->match_zs[end_index-1];
}

/* process 1 opsplitsing vb ["De" "Sterre Gent"]
 * neem voor elke woord de matches en kijk of er wel degelijk zijn (>0)
 * laat dan de totale matches berekenen.
 */
void process_combination(combinatie* combinatie, match_start_to_end* match_start_to_end, totale_matches* totale_matches) {
    match_z** match_list = malloc((combinatie->length-1)*sizeof(match_z*));
    for (int start_index = 0; start_index < combinatie->length-1; start_index++) {
            match_list[start_index] = get_matches(combinatie->combinatie[start_index], combinatie->combinatie[start_index+1], match_start_to_end);
            // geen totale matches
            if (match_list[start_index]->matches_size == 0) {
                free(match_list);
                return;
            }
    }
    // maak totale matches
    combinatie_matches(match_list, combinatie->length-1, totale_matches);
    free(match_list);
}

/* bereken alle totale matches van 1 input line */
totale_matches* matches_from_line(char* line, data* data, double lengte_lig, double breedte_lig) {
    // maak mogelijke combinaties vb ["De" "Sterre Gent"]
    all_combinaties* all_combinaties = combinate_from_line(line);

    // zoek in databank elke combinatie exact 1x op in de databank
    match_start_to_end* match_start_to_end = create_match_end(all_combinaties->max_words, all_combinaties, data);

    // create totale matches object
    totale_matches* res = totale_matches_alloc();
    res->lengte_lig = lengte_lig;
    res->breedte_lig = breedte_lig;

    // bepaal de totale_matches per combinatie
    // we loopen hier over de combinaties en vragen de huidige op
    // hierdoor slaan we ze niet allemaal tegelijk op
    while(all_combinaties->current_index < all_combinaties->max_size) {
        combinatie* current = get_combination_i(all_combinaties->current_index, all_combinaties);
        process_combination(current, match_start_to_end, res);
        combinatie_free(current);
        all_combinaties->current_index++;
    }

    match_start_to_end_free(match_start_to_end);
    all_combinaties_free(all_combinaties);
    return res;
}

