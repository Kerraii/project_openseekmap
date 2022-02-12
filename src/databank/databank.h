#ifndef PROJECT_DATABANK_H
#define PROJECT_DATABANK_H

#include <stdint.h>

#define MAX_COUNT 512
#define MAX_SIZE 50000
#define MAX_SORT_WORD_LENGTH 30

typedef struct {
    // 1 enkele entry
    long identifier;
    char* name;
    uint8_t rang;
    // lengte zonder accenten (en hoofdletters)
    unsigned long sanitized_length;
    double lengtelig;
    double breedtelig;
} entry;

typedef struct {
    // de entries
    int size;
    int max_size;
    entry** entries;

    // lengte 1 tem 30 (index 0 tem 29)
    // start index vanwaar het eerste voorkomen van een woord met deze lengte
    long index_list[MAX_SORT_WORD_LENGTH];
} data;

entry* entry_alloc();
void entry_free(entry* entry);

data* data_alloc();
void data_free(data* data);
void double_size_data(data* data);
void exact_realloc_data(data* data);

entry* read_entry(char* line);

data* read_data(const char* filename);


#endif //PROJECT_DATABANK_H
