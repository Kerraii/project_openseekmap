#include <malloc.h>
#include <memory.h>
#include "test_combinator.h"

int test_combinator() {
    int succesful_tests = 0;
    int total_tests = 0;

    all_combinaties* de_sterre_gent = combinate_from_line("De Sterre Gent");

    // De Sterre Gent
    combinatie* c = get_combination_i(de_sterre_gent->current_index, de_sterre_gent);

    char* s = get_string_from_combination(c->combinatie[0], c->combinatie[1], de_sterre_gent->word_list);
    succesful_tests += strcmp("De Sterre Gent", s) == 0;
    total_tests++;
    free(s);

    combinatie_free(c);
    de_sterre_gent->current_index++;

    // De | Sterre Gent
    c = get_combination_i(de_sterre_gent->current_index, de_sterre_gent);

    s = get_string_from_combination(c->combinatie[0], c->combinatie[1], de_sterre_gent->word_list);
    succesful_tests += strcmp("De", s) == 0;
    total_tests++;
    free(s);

    s = get_string_from_combination(c->combinatie[1], c->combinatie[2], de_sterre_gent->word_list);
    succesful_tests += strcmp("Sterre Gent", s) == 0;
    total_tests++;
    free(s);

    combinatie_free(c);
    de_sterre_gent->current_index++;

    // De Sterre | Gent
    c = get_combination_i(de_sterre_gent->current_index, de_sterre_gent);

    s = get_string_from_combination(c->combinatie[0], c->combinatie[1], de_sterre_gent->word_list);
    succesful_tests += strcmp("De Sterre", s) == 0;
    total_tests++;
    free(s);

    s = get_string_from_combination(c->combinatie[1], c->combinatie[2], de_sterre_gent->word_list);
    succesful_tests += strcmp("Gent", s) == 0;
    total_tests++;
    free(s);

    combinatie_free(c);
    de_sterre_gent->current_index++;

    // De | Sterre | Gent
    c = get_combination_i(de_sterre_gent->current_index, de_sterre_gent);

    s = get_string_from_combination(c->combinatie[0], c->combinatie[1], de_sterre_gent->word_list);
    succesful_tests += strcmp("De", s) == 0;
    total_tests++;
    free(s);

    s = get_string_from_combination(c->combinatie[1], c->combinatie[2], de_sterre_gent->word_list);
    succesful_tests += strcmp("Sterre", s) == 0;
    total_tests++;
    free(s);

    s = get_string_from_combination(c->combinatie[2], c->combinatie[3], de_sterre_gent->word_list);
    succesful_tests += strcmp("Gent", s) == 0;
    total_tests++;
    free(s);

    combinatie_free(c);
    de_sterre_gent->current_index++;


    // some tests failed
    if (total_tests - succesful_tests) {
        return 1;
    }
    return 0;
}

/*
 * words:
De
Sterre
Gent


combinatie:
De Sterre Gent

combinatie:
De
Sterre Gent

combinatie:
De Sterre
Gent

combinatie:
De
Sterre
Gent
 */
