#pragma once

void pvp_mode();
void draw_board();
void get_player_names();
void new_board();
int valid_move_checker(int choice);
int computer_move();
void pve_mode();
void add_to_leaderboard(char name[25], int win, int loss);
void print_leaderboard();
int get_free_replay_index();
void add_to_replay(struct game_moves moves[9]);
void match_replays_selection();
void launch_replay(int game_index);

struct game_moves {
	int board_move;
	char player_name[25];
	char mark;
};

struct Leaderboard {
	int wins;
	int losses;
	int total;
	char name[25];
};

struct Match
{
	struct game_moves match_moves[9];
};