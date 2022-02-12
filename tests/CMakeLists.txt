cmake_minimum_required(VERSION 3.15)
project(project C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Werror -lm)

add_executable(openseekmap_test
        main_test.c
        ../src/shiftAnd/shiftand.c
        ../src/shiftAnd/shiftand.h
        ../src/databank/databank.c
        ../src/databank/databank.h
        ../src/combinator/combinator.c
        ../src/combinator/combinator.h
        ../src/search/search.c
        ../src/search/search.h
        ../src/editeerafstand/editeerafstand.c
        ../src/editeerafstand/editeerafstand.h
        ../src/combinator/match_combinator.c
        ../src/combinator/match_combinator.h
        ../src/score_calculator/score_calculator.c
        ../src/score_calculator/score_calculator.h
        ../src/score_calculator/rosetta.c
        ../src/score_calculator/rosetta.h
        ../src/best_total_matches/sort_and_print.c
        ../src/best_total_matches/sort_and_print.h
        ../src/sanitize/accents.h
        ../src/sanitize/accents.c
        ../src/sanitize/sanitize.c
        ../src/sanitize/sanitize.h
        ../src/sanitize/utf8.h
        ../src/sanitize/utf8.c
        ../src/preprocess/preprocess.c
        ../src/preprocess/preprocess.h
        test_editeerafstand.c
        test_editeerafstand.h
        test_sanitize.c
        test_sanitize.h
        test_combinator.c
        test_combinator.h)

target_link_libraries(openseekmap_test m)