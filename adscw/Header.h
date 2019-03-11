#pragma once

struct winCount
{
	char name[15];
	int win_count;
};

struct player_moves
{
	char letter;
	int board_index;
};

void draw_board();
void play_game();
void new_game();
void get_player_names();
