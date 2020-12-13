#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>

#define _(STRING) gettext(STRING)

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
	bindtextdomain ("guess", LOCALEDIR);
	textdomain ("guess");

    int lower_bound = 0;
    int upper_bound = 100;

    while (upper_bound > lower_bound + 1) {
        int middle_number = (lower_bound + upper_bound) / 2;
        printf(_("Is number greater than"));
        printf(" %d?\n", middle_number);
        char *answer;
        int scanf_ret = scanf("%ms", &answer);
        (void)scanf_ret;

        if (strcmp(answer, gettext("yes")) == 0 || strcmp(answer, gettext("Yes")) == 0) {
            lower_bound = middle_number;
        } else {
            upper_bound = middle_number;
        }
        free(answer);
    }

    printf(_("Your number is"));
    printf(" %d!\n", upper_bound);
}

