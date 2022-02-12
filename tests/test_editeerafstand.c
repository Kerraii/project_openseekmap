#include "test_editeerafstand.h"

int test_editeerafstand() {
    int succesful_tests = 0;
    int total_tests = 0;

    // alle aanpassingen staan in commentaar en gebeuren in het 2de argument

    // exact match
    succesful_tests += bepaal_editeerafstand("de sterre gent", "de sterre gent") == 0;
    total_tests++;

    // exact match -> hoofdletters toevoegen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "De Sterre Gent") == 0;
    total_tests++;

    // 1 't' verwijderen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "De Sterre Gen") == 1;
    total_tests++;

    // 1 'n' toevoegen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "De Sterren Gent") == 1;
    total_tests++;

    // exact match -> accenten en hoofdletters toevoegen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "Dé Stêrrë Gént") == 0;
    total_tests++;

    // 1 letter omwisselen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "De Strere Gent") == 1;
    total_tests++;

    // 3 letters verwijderen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "D Sterr Gen") == 3;
    total_tests++;

    // 2 letters vervangen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "De Stelle Gent") == 2;
    total_tests++;

    // 1 vervangen en 1 verwijderen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "De Starre Gen") == 2;
    total_tests++;

    // 1 vervangen, 1 verwijderen en 1 toevoegen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "Da Stere Genat") == 3;
    total_tests++;

    // 1 wisselen en 1 toevoegen
    succesful_tests += bepaal_editeerafstand("de sterre gent", "ed Stearre Gent") == 2;
    total_tests++;

    /////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////// SPECIAL TESTS //////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////

    // 1 vervangen
    succesful_tests += bepaal_editeerafstand("a", "b") == 1;
    total_tests++;

    // 1 wissel
    succesful_tests += bepaal_editeerafstand("ab", "ba") == 1;
    total_tests++;

    // 1 wissel en 1 toevoegen
    succesful_tests += bepaal_editeerafstand("ab", "baa") == 2;
    total_tests++;

    // 1 wissel
    succesful_tests += bepaal_editeerafstand("abba", "abab") == 1;
    total_tests++;

    // 2 wissels
    succesful_tests += bepaal_editeerafstand("baba", "abab") == 2;
    total_tests++;

    // 1e letter verwijderen en 1 letter op einde toevoegen
    succesful_tests += bepaal_editeerafstand("babababa", "abababab") == 2;
    total_tests++;

    // 1 letter toevoegen
    succesful_tests += bepaal_editeerafstand("arra", "arara") == 1;
    total_tests++;

    // some tests failed
    if (total_tests - succesful_tests) {
        return 1;
    }
    return 0;
}