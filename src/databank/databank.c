#include "databank.h"
#include "../sanitize/sanitize.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

/* allocate 1 entry uit de database */
entry* entry_alloc() {
    entry* res = malloc(sizeof(entry));
    assert(res);
    res->identifier = 0;
    res->name = NULL;
    res->rang = 0;
    res->lengtelig = 0;
    res->breedtelig = 0;
    res->sanitized_length = 0;
    return res;
}

/* free 1 entry uit de database */
void entry_free(entry* entry) {
    //free de naam
    free(entry->name);

    //free de entry
    free(entry);
}

/* allocate 1 data object voor alle entries op te slaan */
data* data_alloc() {
    data* res = malloc(sizeof(data));
    assert(res);
    res->size = 0;
    memset(res->index_list, 0, MAX_SORT_WORD_LENGTH*sizeof(int));
    res->max_size = MAX_SIZE;
    res->entries = malloc(sizeof(entry*)*MAX_SIZE);
    assert(res->entries);
    return res;
}

/* free het data object */
void data_free(data* data) {
    //free entries
    for (int i = 0; i < data->size; i++) {
        entry_free(data->entries[i]);
    }

    //free entry list
    free(data->entries);

    //free data
    free(data);
}

/* verdubbel het aantal entries indien nodig */
void double_size_data(data* data) {
    data->max_size = data->max_size * 2;
    data->entries = realloc(data->entries, data->max_size * sizeof(entry*));
    assert(data->entries);
}

/* na het inlezen van de databank kunnen we het aantal entries exact reallocen */
void exact_realloc_data(data* data) {
    data->max_size = data->size;
    data->entries = realloc(data->entries, data->max_size * sizeof(entry*));
    assert(data->entries);
}

/* process 1 lijn uit de databank en steek het in een entry */
entry* read_entry(char* line) {
    entry* res = entry_alloc();

    // identifier
    res->identifier = strtol(line, &line, 10);

    // skip de tab
    line += sizeof(char);

    //  name
    int size_of_name = 0;
    while (line[size_of_name] != '\t') {
        size_of_name++;
    }
    res->name = malloc((size_of_name+1)*sizeof(char));
    assert(res->name && "Invalid name!");
    res->name[size_of_name] = '\0';
    strncpy(res->name, line, size_of_name);

    // zet sanitized length
    char* sanitized = sanitize(res->name);
    res->sanitized_length = strlen(sanitized);
    free(sanitized);

    // skip de naam + de tab
    line += (size_of_name+1)*sizeof(char);

    // rang
    res->rang = (uint8_t) strtol(line, &line, 10);

    // skip de tab
    line += sizeof(char);

    //  breedtelig
    res->breedtelig = strtod(line, &line);

    // skip de tab
    line += sizeof(char);

    // lengtelig
    res->lengtelig = strtod(line, &line);

    return res;
}

/* lees het databestand in */
data* read_data(const char* filename) {
    FILE *file_ptr = fopen(filename, "r");
    assert(file_ptr != NULL && "Invalid file!");

    data* res = data_alloc();

    char* buffer = malloc(MAX_COUNT*sizeof(char));

    assert(buffer != NULL);

    // less lijn per lijn
    res->size = 0;
    while (fgets(buffer, MAX_COUNT, file_ptr) != NULL) {
        entry* e = read_entry(buffer);
        assert(e);
        res->entries[res->size] = e;
        res->size++;
        // check for max size
        if(res->size == res->max_size) {
            double_size_data(res);
        }
    }

    // realloc res zijn entries
    exact_realloc_data(res);

    //close file and free buffer
    fclose(file_ptr);
    free(buffer);

    return res;
}
