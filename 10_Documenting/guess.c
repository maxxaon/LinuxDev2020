/** @file guess.c
 * Guesser program main file.
 * Thus utility knows your number!
 */

#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <libintl.h>
#include <locale.h>
#include <string.h>
#include <config.h>
#include <stdbool.h>

/** Macro for string autotranslating */
#define _(STRING) gettext(STRING)

/** Localisations path */
#define LOCALE_PATH "."

/** String repr of Roman numbers from 0 to 100 */
char* roman_numbers[] = {"N","I","II","III","IV","V","VI","VII","VIII","IX","X","XI","XII","XIII","XIV","XV","XVI","XVII","XVIII","XIX","XX","XXI","XXII","XXIII","XXIV","XXV","XXVI","XXVII","XXVIII","XXIX","XXX","XXXI","XXXII","XXXIII","XXXIV","XXXV","XXXVI","XXXVII","XXXVIII","XXXIX","XL","XLI","XLII","XLIII","XLIV","XLV","XLVI","XLVII","XLVIII","XLIX","L","LI","LII","LIII","LIV","LV","LVI","LVII","LVIII","LIX","LX","LXI","LXII","LXIII","LXIV","LXV","LXVI","LXVII","LXVIII","LXIX","LXX","LXXI","LXXII","LXXIII","LXXIV","LXXV","LXXVI","LXXVII","LXXVIII","LXXIX","LXXX","LXXXI","LXXXII","LXXXIII","LXXXIV","LXXXV","LXXXVI","LXXXVII","LXXXVIII","LXXXIX","XC","XCI","XCII","XCIII","XCIV","XCV","XCVI","XCVII","XCVIII","XCIX","C"};

/**
 * Converts Roman string to integer
 * 
 * @param s Roman string to convert.
 */
int romanToInteger(char* s) {
    for (int i = 0; i <= 100; ++i) {
        if (strcmp(s, roman_numbers[i]) == 0) {
            return i; 
        }
    }
    return -1;
}

/**
 * Converts integer to Roman string
 * 
 * @param n Integer to convert.
 */
char* integerToRoman(int n) {
    return roman_numbers[n];
}

/** Help message for --help flag */
#define HELP_MSG _("It's program, that can guess your number from 1 to 100\n\
Usage: ./guess [OPTIONS]\n\
    --help      just prints this help\n\
    --version   prints prgram version\n\
    -r          uses roman numbers instead of integers\n\
")

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
	bindtextdomain ("guess", LOCALE_PATH);
	textdomain ("guess");

    bool roman_flag = false;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-r") == 0) {
            roman_flag = true;
        } else if (strcmp(argv[i], "--help") == 0) {
            printf(HELP_MSG);
            return 0;
        } else if (strcmp(argv[i], "--version") == 0) {
            puts(VERSION);
            return 0;
        }
    }

    int lower_bound = 0;
    int upper_bound = 100;

    while (upper_bound > lower_bound + 1) {
        int middle_number = (lower_bound + upper_bound) / 2;
        printf(_("Is number greater than"));
        if (roman_flag) {
            printf(" %s?\n", integerToRoman(middle_number));
        } else {
            printf(" %d?\n", middle_number);
        }
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
    if (roman_flag) {
        printf(" %s!\n", integerToRoman(upper_bound));
    } else {
        printf(" %d!\n", upper_bound);
    }
}

