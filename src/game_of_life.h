#include <stdio.h>
#include <stdbool.h>
#include <ncurses.h>
#include <unistd.h>
#include <ctype.h>

#define HEIGTH 25
#define WIDTH 80

void init_ncurses();
void set_colors();
void init_game_field(int game_field[HEIGTH][WIDTH]);
void evolution(int game_field[HEIGTH][WIDTH], int tmp_game_field[HEIGTH][WIDTH]);
int count_neighbors(int game_field[HEIGTH][WIDTH], int i, int j);
int status_of_cell(int neighbors, int prev_status);
void upd_game_field(int game_field[HEIGTH][WIDTH], int tmp_game_field[HEIGTH][WIDTH]);
void game_loop(int game_field[HEIGTH][WIDTH], int tmp_game_field[HEIGTH][WIDTH]);
int comp_fields(int game_field[HEIGTH][WIDTH], int tmp_game_field[HEIGTH][WIDTH]);
int change_game_speed(char button, int time_mili_sec, bool *endgame);