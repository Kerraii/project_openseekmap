#ifndef PROJECT_COMBINATOR_H
#define PROJECT_COMBINATOR_H

#define MAX_WORDS 32

typedef struct {
    int length;
    // combinatie 0 is dan woord[combinatie[0]] tot woord[combinatie[1]]
    // stel 3 woorden
    // 0 1 2 3
    // 0 1 3
    // 0 2 3
    // 0 3
    int* combinatie;
} combinatie;

typedef struct {
    // aantal combinaties
    long long int max_size;
    long current_index;

    //aantal woorden
    int max_words;
    int words;
    char** word_list;
} all_combinaties;

int calculate_max_size(int aantal_woorden);

int power_int(int base, int exponent);

combinatie* combinatie_alloc(int max_length);
void combinatie_free(combinatie* combinatie);

all_combinaties* all_combinaties_alloc();
void all_combinaties_free(all_combinaties* all_combinaties);
void double_size_words(all_combinaties* all_combinaties);
void exact_realloc_words(all_combinaties* all_combinaties);

// worden niet mee gebruikt
// void print_all_combinaties(all_combinaties* allcombinaties);
// void combinate_integers(all_combinaties* all_combinaties);

combinatie* get_combination_i(unsigned long long int combination_index, all_combinaties* all_combinaties);
all_combinaties* combinate_from_line(char* line);

char* get_string_from_combination(int start, int end, char** word_list);

#endif //PROJECT_COMBINATOR_H
