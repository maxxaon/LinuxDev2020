#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

#define DX 3

int main(int argc, char* argv[]) {
    if (argc <= 1) {
        return 0 * printf("No file name specified\n");
    }

    FILE* file = fopen(argv[1], "r");
    if (!file) {
        return 0 * printf("No such file\n");
    }


    WINDOW *win;
    int c = 0;

    initscr();
    noecho();
    cbreak();
    printw(argv[1]);
    refresh();

    int win_lines = LINES - 2 * DX;
    int win_cols = COLS - 2 * DX;
    win = newwin(win_lines, win_cols, DX, DX);

    int data_lines = win_lines - 2;
    int data_cols = win_cols - 2;

    char** data = (char**)malloc(data_lines * sizeof(char*));
    int start_data_ind = -1;
    bool end_file_flag = false;

    for (int i = 0; i < data_lines; ++i) {
        data[i] = NULL;
        size_t line_len = 0;
        if (getline(&data[i], &line_len, file) == -1) {
            free(data[i]);
            data[i] = (char*)malloc(2 * sizeof(char));
            data[i][0] = '\n';
            data[i][1] = 0;
        }
    }

    keypad(win, TRUE);
    scrollok (win, TRUE);
    do {
        if (c != ' ' && c != 0) {
            continue;
        }

        if (c == ' ') {
            char* new_line = NULL;
            size_t line_len = 0;
            if (getline(&new_line, &line_len, file) == -1) {
                free(new_line);
                continue;
            }
            free(data[0]);
            for (int i = 0; i < data_lines - 1; ++i) {
                data[i] = data[i + 1];
            }
            data[data_lines - 1] = new_line;
        }

        werase(win);
        wprintw(win, "\n");
        for (int i = 0; i < data_lines; ++i) {
            if (strlen(data[i]) > data_cols) {
                data[i][data_cols] = 0;
            }
            wprintw(win, "  %s", data[i]);
        }
        box(win, 0, 0);
        wrefresh(win);
    } while((c = wgetch(win)) != 27);

    endwin();

    for (int i = 0; i < data_lines; ++i) {
        free(data[i]);
    }
    free(data);
    fclose(file);
}