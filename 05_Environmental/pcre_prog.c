#ifndef PCRE2_CODE_UNIT_WIDTH
#define PCRE2_CODE_UNIT_WIDTH 8
#endif

#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif

#include "pcre_prog.h"

#include <string.h>
#include <pcre2.h>
#include <stdio.h>

struct MatchResult match(char* pattern, char* subject) {
    pcre2_code *re;
    PCRE2_SPTR pcre_pattern = (PCRE2_SPTR)pattern;     /* PCRE2_SPTR is a pointer to unsigned code units of */
    PCRE2_SPTR pcre_subject = (PCRE2_SPTR)subject;     /* the appropriate width (in this case, 8 bits). */

    int errnum;
    int i, rc;

    PCRE2_SIZE erroffs;
    PCRE2_SIZE *ovector;
    PCRE2_SIZE subject_length;

    pcre2_match_data *match_data;

    subject_length = (PCRE2_SIZE)strlen((char *)pcre_subject);

#ifndef WITHOUT_UTF
    uint32_t options = PCRE2_UCP;
#else
    uint32_t options = 0;
#endif
    re = pcre2_compile(pcre_pattern, PCRE2_ZERO_TERMINATED, options, &errnum, &erroffs, NULL);
    struct MatchResult match_result;

    if (re == NULL) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errnum, buffer, sizeof(buffer));

        asprintf(&match_result.output, "  PCRE2 compilation failed at offset %d: %s\n", (int)erroffs, buffer);
        return match_result;
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    rc = pcre2_match(re, pcre_subject, subject_length, 0, 0, match_data, NULL);

    if (rc < 0) {
        switch(rc) {
        case PCRE2_ERROR_NOMATCH:
            asprintf(&match_result.output, "  No match\n");
            break;
        default:
            asprintf(&match_result.output, "  Matching error %d\n", rc);
            break;
        }
        pcre2_match_data_free(match_data);   /* Release memory used for the match */
        pcre2_code_free(re);                 /*   data and the compiled pattern. */
        return match_result;
    }

    ovector = pcre2_get_ovector_pointer(match_data);

    int output_len = 0;
    for (int i = 0; i < rc; ++i) {
        output_len += 2 + 4 + (int)(ovector[2*i+1] - ovector[2*i]) + 1;
    }
    match_result.output = malloc(sizeof(char) * (output_len + 1));
    char* output_ptr = match_result.output;

    for (i = 0; i < rc; i++)
        output_ptr += snprintf(output_ptr, output_len + 1, "  %2ld: %.*s\n", ovector[2*i], 
			                  (int)(ovector[2*i+1] - ovector[2*i]),
			                  pcre_subject + ovector[2*i]);

    pcre2_match_data_free(match_data);  /* Release the memory that was used */
    pcre2_code_free(re);                /* for the match data and the pattern. */

    return match_result;
}
