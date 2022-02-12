#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "databank/databank.h"
#include "search/search.h"
#include "best_total_matches/sort_and_print.h"
#include "main.h"

// #include <sys/resource.h>
#include <assert.h>
// #include <time.h>
#include "preprocess/preprocess.h"

/*
void print_max_memuse() {
    struct rusage r_usage;
    getrusage(RUSAGE_SELF,&r_usage);
    // Print the maximum resident set size used (in kilobytes).
    printf("Memory usage: %ld kilobytes\n",r_usage.ru_maxrss);
}
 */

int main(int argc, char *argv[]) {
    // clock_t begin = clock();
    data* data;
    double lengtelig_rond = -1;
    double breedtelig_rond = -1;
    // name + database
    if (argc == 2) {
        data = read_data(argv[1]);
    }
    // name + coordinates + database
    else if (argc == 4) {
        lengtelig_rond = strtod(argv[2], NULL);
        breedtelig_rond = strtod(argv[3], NULL);
        data = read_data(argv[1]);
    }
    // invalid
    else {
        printf("Syntax: openseekmap database.data | openseekmap database.data lengteligging breedteligging\n");
        return 0;
    }

    // preprocessing van de data
    preprocess(data);

    int buffer_size = BUFFER_SIZE;
    char* buffer = malloc(buffer_size*sizeof(char));
    assert(buffer);

    while (fgets(buffer, buffer_size, stdin) != NULL) {
        //print ?
        printf("?");
        
        //filter out '\n' and '\r' indien nodig
        size_t ln = strlen(buffer);
        if (buffer[ln-1] == '\n') {
            buffer[ln-1] = '\0';
            if (ln-2 >= 0 && buffer[ln-2] == '\r') {
                buffer[ln-2] = '\0';
            }
        // else if buffer was vol en woord was niet compleet
        // verdubbel grootte van de buffer zolang dat het nodig is
        } else if (strlen(buffer) == buffer_size - 1) {
            while(strlen(buffer) == buffer_size - 1) {
                char *buffer_2 = malloc(buffer_size*sizeof(char));
                if (fgets(buffer_2, buffer_size, stdin)) {
                    buffer_size = buffer_size*2 - 1;
                    buffer = realloc(buffer, buffer_size);
                    buffer = strcat(buffer, buffer_2);
                } else {
                    free(buffer_2);
                    break;
                }
                free(buffer_2);
            }
        }
        // empty line == EOF
        if (strlen(buffer) == 0){
            break;
        }

        // get the totale_matches from the current line
        totale_matches* totale_matches = matches_from_line(buffer, data, lengtelig_rond, breedtelig_rond);

        // beste totale_matches
        sort_by_score(totale_matches);

        // print output
        print_best_matches(totale_matches, 5);

        // free the totale_matches
        totale_matches_free(totale_matches);

    }

    // free dingen
    free(buffer);
    data_free(data);

    /* print time
    printf("\n------------------------\n");
    // check time
    clock_t end = clock();
    double time_spent_total = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\nRuntime total: %f seconds\n", time_spent_total);

    // print max memery use
    // print_max_memuse();
     */

    return 0;
}
