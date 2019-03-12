#pragma once

void pvp_mode();
void draw_board();
void get_player_names();
void new_board();
int valid_move_checker(int choice);
void leaderboard(char name[25]);
int computer_move();
void pve_mode();

struct game_moves {
	int board_move;
	char player_name[25];
	char mark;
};

struct Leaderboard {
	int wins;
	int losses;
	char name[25];
};