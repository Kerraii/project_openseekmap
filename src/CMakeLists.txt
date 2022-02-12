cmake_minimum_required(VERSION 3.15)
project(project C)

set(CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Werror -lm)

add_executable(openseekmap
        main.c
        main.h
        shiftAnd/shiftand.c
        shiftAnd/shiftand.h
        databank/databank.c
        databank/databank.h
        combinator/combinator.c
        combinator/combinator.h
        search/search.c
        search/search.h
        editeerafstand/editeerafstand.c
        editeerafstand/editeerafstand.h
        combinator/match_combinator.c
        combinator/match_combinator.h
        score_calculator/score_calculator.c
        score_calculator/score_calculator.h
        score_calculator/rosetta.c
        score_calculator/rosetta.h
        best_total_matches/sort_and_print.c
        best_total_matches/sort_and_print.h
        sanitize/accents.h
        sanitize/accents.c
        sanitize/sanitize.c
        sanitize/sanitize.h
        sanitize/utf8.h
        sanitize/utf8.c
        preprocess/preprocess.c
        preprocess/preprocess.h)

target_link_libraries(openseekmap m)