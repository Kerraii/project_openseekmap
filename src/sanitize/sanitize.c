#include <stdio.h>      /* printf */
#include "utf8.h"       /* u8_ functions */
#include "accents.h"
#include <stddef.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "sanitize.h"

/* return een copy zonder hoofdletters en accenten.
 * NOTE: return value moet nog gefreed worden
 */
char* sanitize(char* ii) {
    unsigned long len_input = strlen(ii);
    // + 5 zodat er genoeg '\0' achter kan
    char* output = malloc((len_input+5)*sizeof(char));
    assert(output);
    memset(output, '\0', (len_input+5));
    char input[len_input + 5];
    memset(input, '\0', len_input + 5);
    strcpy(input, ii);
    char buf2[10] = "";
    int i = 0;
    wchar_t c;
    while((c = u8_nextchar(input,&i))){
        uint32_t norm = tolower(remove_accent(c));
        u8_wc_toutf8(buf2, norm);
        strcat(output, buf2);
        memset(buf2, '\0', 10);
    }
    return output;
}