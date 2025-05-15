#include "game_of_life.h"

int main() {
    int game_field[HEIGTH][WIDTH];
    int tmp_game_field[HEIGTH][WIDTH];

    init_game_field(game_field);

    if (freopen("/dev/tty", "r", stdin)) {
        init_ncurses();
        game_loop(game_field, tmp_game_field);
        endwin();
    }

    return 0;
}

void init_ncurses() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    curs_set(false);
    set_colors();
}

void set_colors() {
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_BLACK, COLOR_BLACK);
}

void init_game_field(int game_field[HEIGTH][WIDTH]) {
    for (int i = 0; i < HEIGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf("%d", &game_field[i][j]);
        }
    }
}

void evolution(int game_field[HEIGTH][WIDTH], int temp_game_field[HEIGTH][WIDTH]) {
    for (int i = 0; i < HEIGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            temp_game_field[i][j] = status_of_cell(count_neighbors(game_field, i, j), game_field[i][j]);
            if (temp_game_field[i][j]) {
                attron(COLOR_PAIR(1));
                printw(" ");
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                printw(" ");
                attroff(COLOR_PAIR(2));
            }
        }
        printw("\n");
    }
}

int count_neighbors(int game_field[HEIGTH][WIDTH], int i, int j) {
    int neighbors = 0;

    int i_minus = (i - 1 + HEIGTH) % HEIGTH;
    int i_plus = (i + 1) % HEIGTH;
    int j_minus = (j - 1 + WIDTH) % WIDTH;
    int j_plus = (j + 1) % WIDTH;

    neighbors += game_field[i_minus][j_minus];
    neighbors += game_field[i_minus][j];
    neighbors += game_field[i_minus][j_plus];
    neighbors += game_field[i][j_plus];
    neighbors += game_field[i_plus][j_plus];
    neighbors += game_field[i_plus][j];
    neighbors += game_field[i_plus][j_minus];
    neighbors += game_field[i][j_minus];

    return neighbors;
}

int status_of_cell(int neighbors, int prev_status) {
    int next_status = -1;
    if (neighbors == 3 || (neighbors == 2 && prev_status == 1))
        next_status = 1;
    else
        next_status = 0;

    return next_status;
}

void upd_game_field(int game_field[HEIGTH][WIDTH], int tmp_game_field[HEIGTH][WIDTH]) {
    for (int i = 0; i < HEIGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            game_field[i][j] = tmp_game_field[i][j];
        }
    }
}

int comp_fields(int game_field[HEIGTH][WIDTH], int tmp_game_field[HEIGTH][WIDTH]) {
    int res = 0;
    for (int i = 0; i < HEIGTH; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (game_field[i][j] == tmp_game_field[i][j]) res++;
        }
    }
    return res;
}

void game_loop(int game_field[HEIGTH][WIDTH], int tmp_game_field[HEIGTH][WIDTH]) {
    bool endgame = false;
    int time_ms = 500;

    while (!endgame) {
        char c = getch();
        time_ms = change_game_speed(c, time_ms, &endgame);
        usleep(time_ms * 1000);
        clear();

        evolution(game_field, tmp_game_field);
        if (comp_fields(game_field, tmp_game_field) == HEIGTH * WIDTH) {
            endgame = true;
        }
        upd_game_field(game_field, tmp_game_field);
    }
}

int change_game_speed(char c, int time_ms, bool *endgame) {
    c = tolower(c);

    if (c == 'z') time_ms += 100;
    else if (c == 'a') time_ms -= 100;
    else if (c == 'q') *endgame = 1;

    if (time_ms <= 100) time_ms = 100;
    if (time_ms >= 1000) time_ms = 1000;

    return time_ms;
}