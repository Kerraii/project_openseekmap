#include <memory.h>
#include <malloc.h>
#include "test_sanitize.h"

int test_sanitize() {
    int succesful_tests = 0;
    int total_tests = 0;
    char* woord;

    // simple test
    woord = sanitize("abc");
    succesful_tests += strcmp(woord, "abc") == 0;
    free(woord);
    total_tests++;

    // check hoofdletters
    woord = sanitize("ABC");
    succesful_tests += strcmp(woord, "abc") == 0;
    free(woord);
    total_tests++;

    // check accenten
    woord = sanitize("éënd");
    succesful_tests += strcmp(woord, "eend") == 0;
    free(woord);
    total_tests++;

    // check accenten
    woord = sanitize("köê");
    succesful_tests += strcmp(woord, "koe") == 0;
    free(woord);
    total_tests++;

    // check accenten
    woord = sanitize("áàp");
    succesful_tests += strcmp(woord, "aap") == 0;
    free(woord);
    total_tests++;

    // check accenten op een hoofdletter
    woord = sanitize("WÄLVÍS");
    succesful_tests += strcmp(woord, "walvis") == 0;
    free(woord);
    total_tests++;

    // check accenten op een hoofdletter
    woord = sanitize("PÄÁRD");
    succesful_tests += strcmp(woord, "paard") == 0;
    free(woord);
    total_tests++;

    // check hoopje accenten
    woord = sanitize("âäáàçôöõóòñûüúù");
    succesful_tests += strcmp(woord, "aaaacooooonuuuu") == 0;
    free(woord);
    total_tests++;

    // some tests failed
    if (total_tests - succesful_tests) {
        return 1;
    }
    return 0;
}

