#include "combinator.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* power int */
int power_int(int base, int exponent) {
    int result = 1;
    for(; exponent > 0 ; exponent--) {
        result *= base;
    }
    return result;
}

/* allocate 1 combinatie
 * max length = max woorden */
combinatie* combinatie_alloc(int max_length) {
    combinatie* res = malloc(sizeof(combinatie));
    assert(res);
    res->length = 0;
    res->combinatie = malloc(max_length*sizeof(int));
    assert(res->combinatie);
    return res;
}

/* free 1 combinatie */
void combinatie_free(combinatie* combinatie) {
    free(combinatie->combinatie);
    free(combinatie);
}

/* berekent het maximum size 2^(n-1) */
int calculate_max_size(int aantal_woorden) {
    return power_int(2, aantal_woorden-1);
}

/* stel de string op van de combinatie van ints van start tot end */
char* get_string_from_combination(int start, int end, char** word_list) {
    unsigned int size = 0;
    for (int i = start; i < end; ++i) {
        size += strlen(word_list[i]);
        size++; //voor de spatie
    }

    //de laatste spatie zal te veel zijn, maar daar zetten we \0
    char* res = malloc(size*sizeof(char));
    strcpy(res, word_list[start]);
    for (int i = start+1; i < end; ++i) {
        strcat(res, " ");
        strcat(res, word_list[i]);
    }
    res[size-1] = '\0';
    return res;
}

/* allocate alle combinaties object */
all_combinaties* all_combinaties_alloc() {
    all_combinaties* res = malloc(sizeof(all_combinaties));
    assert(res);
    res->max_size = 0;
    res->current_index = 0;
    res->max_words = MAX_WORDS;
    res->words = 0;
    res->word_list = malloc(MAX_WORDS* sizeof(char*));
    assert(res->word_list);
    return res;
}

/* free alle combinaties object */
void all_combinaties_free(all_combinaties* all_combinaties) {
    for (int i = 0; i < all_combinaties->words; ++i) {
        free(all_combinaties->word_list[i]);
    }

    free(all_combinaties->word_list);

    free(all_combinaties);
}

/* double het aantal woorden indien nodig */
void double_size_words(all_combinaties* all_combinaties) {
    all_combinaties->max_words = all_combinaties->max_words * 2;
    all_combinaties->word_list = realloc(all_combinaties->word_list, all_combinaties->max_words * sizeof(char*));
    assert(all_combinaties->word_list);
}

/* zet de max size juist */
void set_max_size_all_combinaties(all_combinaties* all_combinaties) {
    all_combinaties->max_size = calculate_max_size(all_combinaties->words);
}

/* eens we weten hoeveel er exact zijn kunnen we dit exact reallocen */
void exact_realloc_words(all_combinaties* all_combinaties) {
    all_combinaties->max_words = all_combinaties->words;
    all_combinaties->word_list = realloc(all_combinaties->word_list, all_combinaties->max_words * sizeof(char*));
    assert(all_combinaties->word_list);
}

/* vraag combinatie i op */
combinatie* get_combination_i(unsigned long long int combination_index, all_combinaties* all_combinaties) {
    combinatie* res = combinatie_alloc(all_combinaties->words + 1);
    res->combinatie[0] = 0;
    res->length = 1;
    int i = 1;
    // stel de combinatie van getallen op
    for(unsigned long long int bit = 1; bit < all_combinaties->max_size; bit*=2) {
        if ((bit & combination_index) != 0) {
            res->combinatie[res->length] = i;
            res->length++;
        }
        i++;
    }
    res->combinatie[res->length] = all_combinaties->words;
    res->length++;
    return res;
}

/* debug combinatie
void print_all_combinaties(all_combinaties* all_combinaties) {
    for (int i = 0; i < all_combinaties->size; ++i) {
        for (int j = 0; j < all_combinaties->combinaties[i]->length; ++j) {
            printf("%i ", all_combinaties->combinaties[i]->combinatie[j]);
        }
        printf("\n");
    }
}
 */

/* stel het combinatie object op */
all_combinaties* combinate_from_line(char* line) {
    all_combinaties* res = all_combinaties_alloc();

    // copy line omdat we deze aanpassen
    char* copy = malloc((strlen(line) + 1)*sizeof(char));
    strcpy(copy, line);

    // split line into words and save them into res
    char* word = strtok(copy, " ");
    res->words = 0;
    while(word != NULL) {
        res->word_list[res->words] = malloc((strlen(word) + 1)* sizeof(char));
        strcpy(res->word_list[res->words], word);
        word = strtok(NULL, " ");
        res->words++;
        if (res->words == res->max_words) {
            double_size_words(res);
        }
    }

    // we weten we het exact aantal woorden dus kunnen we exact reallocen
    exact_realloc_words(res);

    // nu weten we het aantal combinaties: 2^n-1 met n het aantal woorden
    set_max_size_all_combinaties(res);

    // maak de combinaties met ints om ze da
    // wordt niet meer gebruikt, nu slaan we ze niet op maar vragen we ze 1 voor 1 op
    // combinate_integers(res);

    free(copy);
    return res;
}
