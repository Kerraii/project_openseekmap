#include <stdlib.h>
#include "preprocess.h"

/* compare functie voor 2 entries based of sanitzied length */
int compare_entry_by_sanitized_length(const void* a, const void* b) {
    entry* entry1 = *(entry**) a;
    entry* entry2 = *(entry**) b;
    unsigned long len1 = entry1->sanitized_length;
    unsigned long len2 = entry2->sanitized_length;

    if (len1 < len2) {
        return -1;
    } else if (len1 > len2) {
        return 1;
    } else {
        return 0;
    }
}

/* sorteer op sanitized length */
void sort_by_length(data* data) {
    qsort(data->entries, data->size, sizeof(entry*), compare_entry_by_sanitized_length);
}

/* zet de index goed.
 * op indexlist[i] staat de index van de eerste entry die start met
 * lengte i + 1
 */
void set_index_list(data* data) {
    int current_length = 1;
    // zet voor elke lengte de start goed
    for (int i = 0; i < data->size; ++i) {
        // achter MAX_SORT_WORD_LENGTH houden we geen indexen meer bij want er zullen
        // toch niet veel woorden meer zijn
        while (current_length <= data->entries[i]->sanitized_length && current_length <= MAX_SORT_WORD_LENGTH) {
            data->index_list[current_length - 1] = i;
            current_length++;
        }
    }

    // indien we niet alle lengtes overlopen hebben vullen we de array
    // met het einde van de database
    while(current_length <= MAX_SORT_WORD_LENGTH) {
        data->index_list[current_length - 1] = data->size - 1;
        current_length++;
    }


    /* debug prints
    printf("indexlist: \n");
    for (int i = 0; i < MAX_SORT_WORD_LENGTH; ++i) {
        printf("%li\n", data->index_list[i]);
    }

    printf("\n");
    printf("s1: %s\n", data->entries[data->index_list[5]]->name);
    printf("s2: %s\n", data->entries[data->index_list[5] - 1]->name);
     */
}

/* preprocess de data */
void preprocess(data* data) {
    sort_by_length(data);
    set_index_list(data);
}