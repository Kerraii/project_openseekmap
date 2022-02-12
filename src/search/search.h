#ifndef PROJECT_SEARCH_H
#define PROJECT_SEARCH_H

#include "../databank/databank.h"
#include "../combinator/combinator.h"
#include "../shiftAnd/shiftand.h"

#define MAX_MATCHES 64
#define MAX_TOTALE_MATCHES 5

// 1 match van een deel zoals "Sterre" of "De Sterre"
typedef struct {
    // "Sterre"
    char* zoek_string;

    // alle matches voor "Sterre"
    int matches_size;
    int max_size;
    entry** matched_entries;

    // overeenkomstige editeerafstand
    int* editeer_afstand;
} match_z;

// 1 lijn van de matrix
typedef struct {
    int max_end_index;
    match_z** match_zs;
} match_end;

// 'volledige' triangulaire matrix van matches voor een bepaald woord
typedef struct {
    int max_start_index;
    match_end** match_matrix;
} match_start_to_end;

// 1 enkele totale match
typedef struct {
    // match met hoogste rang
    entry* match;
    double totaal_score;
} enkele_totale_match;

// top 5 totale matches + de breedte- en lengteligging van de input
typedef struct {
    int totaal_aantal;
    double lengte_lig;
    double breedte_lig;
    enkele_totale_match** totale_matches;
} totale_matches;

totale_matches* totale_matches_alloc();
void totale_matches_free(totale_matches* totale_matches);

// niet meer nodig want we slaan niet meer alle totale matches
// nu maximum 5 (voor top 5)
// void double_size_totale_matches(totale_matches* totale_matches);

enkele_totale_match* enkele_totale_match_alloc();
void enkele_totale_match_free(enkele_totale_match* enkele_totale_match);

match_z* match_z_alloc();
void match_z_free(match_z* match_z);
void double_size_match_z(match_z* match_z);

match_end* match_end_alloc(int max_size);
void match_end_free(match_end* match_end, int start);

match_start_to_end* match_start_to_end_alloc(int max_index);
void match_start_to_end_free(match_start_to_end* match_start_to_end);

void match1_z(match_z* match_z, data* data, int correctie_index);
match_z* get_matches(int start_index, int end_index, match_start_to_end* match_start_to_end);
match_start_to_end* create_match_end(int max_size, all_combinaties* all_combinaties, data* data);

totale_matches* matches_from_line(char* line, data* data, double lengte_lig, double breedte_lig);
void process_combination(combinatie*, match_start_to_end*, totale_matches*);

//void print_debug_matches(match_start_to_end* res, int start, int end);

#endif //PROJECT_SEARCH_H
