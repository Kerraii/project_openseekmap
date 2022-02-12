#include <stdio.h>
#include "test_editeerafstand.h"
#include "test_sanitize.h"
#include "test_combinator.h"

// return 0 if all tests passed
int main() {
    int test_failed = 0;

    // do every test
    test_failed += test_editeerafstand();
    test_failed += test_sanitize();
    test_failed += test_combinator();


    if (!test_failed) {
        printf("All basic tests passed!\n");
    }

    return test_failed;
}
