#include <glib.h>
#include <stdio.h>

typedef struct WordWithCount {
    gchar* word;
    gint count;
} WordWithCount;

void add_to_list(gpointer key, gpointer value, gpointer words_with_count_ptr)
{
    WordWithCount* word_with_count = malloc(sizeof(WordWithCount));
    word_with_count->word = key;
    word_with_count->count = GPOINTER_TO_INT(value);
    *(GList**)words_with_count_ptr = g_list_append(*(GList**)words_with_count_ptr, word_with_count);
}

int compare_words(gpointer lhs, gpointer rhs) {
    WordWithCount* lhs_word_with_count = lhs;
    WordWithCount* rhs_word_with_count = rhs;
    return rhs_word_with_count->count - lhs_word_with_count->count;
}

void printer(gpointer g_word_with_count, gpointer user_data) {
    WordWithCount* word_with_count = g_word_with_count;
    printf("%s %d\n", word_with_count->word, word_with_count->count);
}

int main() {
    GHashTable* hash_table = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);

    int max_line_length = 80;
    char buffer[max_line_length + 1];
    while (fgets(buffer, max_line_length + 1, stdin) != NULL) {
        gchar** tokens = g_strsplit_set(buffer, " \t\n\v\f\r", max_line_length + 1);
        gchar** cur_token_ptr = tokens;
        while (*cur_token_ptr) {
            gchar* cur_token = *cur_token_ptr;
            if (strcmp(cur_token, "") != 0) {
                g_hash_table_insert(hash_table, cur_token, GINT_TO_POINTER(g_hash_table_lookup(hash_table, cur_token) + 1));
            }
            ++cur_token_ptr;
        }
        g_free(tokens);
    }

    gint word_cnt = g_hash_table_size(hash_table);
    GList* words_with_count;

    g_hash_table_foreach(hash_table, add_to_list, &words_with_count);
    words_with_count = g_list_sort(words_with_count, (GCompareFunc)compare_words);

    g_list_foreach(words_with_count, printer, NULL);

    g_list_free_full(words_with_count, g_free);
    g_hash_table_destroy(hash_table);
}