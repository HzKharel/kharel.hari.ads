/*
* Author: Hari Kharel - 40312824
* Module: Algorithims and Data structures 
*
* This application is a console based tic tac toe with various game modes and features
* Everything was implemented using the standard libraries included in C99.
*/



#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<stdlib.h> 
#include <string.h>
#include "Header.h"


//global variables
char player1[25], player2[25], board[10];
struct Leaderboard leaderboard_array[100];
struct Match match_replays[100];



//main entry point for the game
void  main(void)
{
	//clearing stream
	fseek(stdin, 0, SEEK_END);
	int selection = 0;

	//populating the main menu

	printf("Tic Tac Toe - ADS Coursework - Hari Kharel - 40312824. Edinburgh Napier University\n\n\n");
	printf("====== MAIN MENU ======\n\n");
	printf(" 1) Plaver v Player \n");
	printf(" 2) Plaver v Computer \n");
	printf(" 3) Match Replays \n");
	printf(" 4) Scoreboard \n");
	printf(" 5) Exit \n\n\n\n");
	printf(" Make A slection:  ");

	scanf("%d", &selection);
	char name[25] = "zasszz";

	//detecting user selection
	//switching ints and performing the correct action
	switch (selection)
	{
	case 1:
		pvp_mode();
		break;
	case 2:
		pve_mode();
		break;
	case 3:
		match_replays_selection();
		break;
	case 4:
		print_leaderboard();
		break;
	case 5:
		printf("Press Any Key to Exit.\n");
		getch();
		exit(0);
		break;
	default:
		printf("Invalid Selection.");

		break;
	}
	//recursive function
	getch();
	system("cls\n\n");
	main();
}


//function to display the game board and the moves on the command line
void draw_board()
{
	//clear previous draws
	system("cls");

	//printing the board
	printf("\n\n\tTic Tac Toe - ADS\n\n");
	printf("\t%s (X)  - %s (O)\n\n\n", player1, player2);
	printf("\t        |       |  \n");
	printf("\t    %c   |   %c   |   %c\n", board[1], board[2], board[3]);
	printf("\t        |       |  \n");
	printf("\t -----------------------\n");
	printf("\t        |       |  \n");
	printf("\t    %c   |   %c   |   %c\n", board[4], board[5], board[6]);
	printf("\t        |       |  \n");
	printf("\t -----------------------\n");
	printf("\t        |       |  \n");
	printf("\t    %c   |   %c   |   %c\n", board[7], board[8], board[9]);
	printf("\t        |       |  \n");

}

//function to create a new, empty board
void new_board()
{
	//loops 10 times and either creates a new array of chars or clears the one from previous game
	for (int i = 1; i < 10; i++) {
		board[i] = i + '0';
	}
}

//function to get the player names
void get_player_names()
{
	//using scanf to get the player names
	system("cls");
	printf("Player 1 Name: ");
	scanf("%s", &player1);
	

	printf("Player 2 Name: ");
	scanf("%s", &player2);

	//clearing stream
	fseek(stdin, 0, SEEK_END);
}

//this method checks if the user input is valid or not. Checks if board index is free, or if its undo or redo and returns an appropriate response
int valid_move_checker(int choice)
{
	/*
		1 = Valid Move
		0 = Undo
		11 = Redo
		-1 = Invalid move
	*/

	//valid move
	if (choice == 1 && board[1] == '1' || choice == 2 && board[2] == '2' || choice == 3 && board[3] == '3' || choice == 4 && board[4] == '4' || choice == 5 && board[5] == '5' ||
		choice == 6 && board[6] == '6' || choice == 7 && board[7] == '7' || choice == 8 && board[8] == '8' || choice == 9 && board[9] == '9')
	{
		return 1;
	}

	//undo is called
	else if (choice == 0)
	{
		return 0;
	}

	//redo is called
	else if (choice == 11)
	{
		return  11;
	}

	//invalid input
	else
	{
		return -1;
	}
}

//function that checks if the game is won. Called after every player move
int check_win()
{
	/*  * 1 = Game Won
		* 2 = Game draw
		* 0 = Game Still in Progress
		*
	*/

	//game won
	if (board[1] == board[2] && board[2] == board[3] || board[4] == board[5] && board[5] == board[6] || board[7] == board[8] && board[8] == board[9] ||
		board[1] == board[4] && board[4] == board[7] || board[2] == board[5] && board[5] == board[8] || board[2] == board[5] && board[5] == board[8] ||
		board[3] == board[6] && board[6] == board[9] || board[1] == board[5] && board[5] == board[9] || board[3] == board[5] && board[5] == board[7])
	{

		return 1;

	}

	//ganme draw
	else if (board[1] != '1' && board[2] != '2' && board[3] != '3' &&
		board[4] != '4' && board[5] != '5' && board[6] != '6' && board[7]
		!= '7' && board[8] != '8' && board[9] != '9')
	{
		return 2;
	}
	//game is still in progress
	else
	{
		return  0;
	}


}

//main gamemode, 2 players playing against each other
void pvp_mode()
{
	//setting up some vaiables, calling some methods to set up the game
	fseek(stdin, 0, SEEK_END);
	new_board();
	get_player_names();
	draw_board();

	//function variables
	int game_won = 0;
	int player_indx = 1;
	char mark = 'X';
	char player[25];
	struct game_moves moves[9];
	int moves_index = 0;

	strcpy(player, player1);

	//loop that runs until the game is won or draw or ends naturally
	while (game_won == 0)
	{
		fseek(stdin, 0, SEEK_END);
		system("cls");
		draw_board();
		printf("%s, Enter board index, 0 to undo, 11 to redo: ", player);
		int choice;
		scanf("%d", &choice);
		int valid_move = valid_move_checker(choice);

		//if the player makes a valid move on the board
		if (valid_move == 1)
		{
			//storing the player name, move and the mark as it enables undo, redo and replays features
			moves[moves_index].board_move = choice;
			moves[moves_index].mark = mark;
			strcpy(moves[moves_index].player_name, &player);

			moves_index++;
			board[choice] = mark;
			draw_board();
			int win = check_win();
			//checking if the game is won or not
			if (win == 1)
			{

				system("cls");
				draw_board();
				printf("%s won the game!", &player);
				if (strcmp(player, player1) == 0) {
					add_to_leaderboard(player1, 1, 0);
					add_to_leaderboard(player2, 0, 1);
				}
				else
				{
					add_to_leaderboard(player2, 1, 0);
					add_to_leaderboard(player1, 0, 1);
				}
				break;

			}
			if (win == 2)
			{
				system("cls");
				draw_board();
				printf("Draw!");
				add_to_leaderboard(player2, 0, 0);
				add_to_leaderboard(player2, 0, 0);
				break;

			}
			else
			{
				//switching between players and their mark
				if (player_indx == 1)
				{
					mark = 'O';
					strcpy(player, player2);
					player_indx = 2;
				}
				else
				{
					mark = 'X';
					strcpy(player, player1);
					player_indx = 1;
				}
			}
		}

		//if the user undo's the last move
		else if (valid_move == 0)
		{
			if (moves_index > 0)
			{
				//moves index acts like a pointer that moves up and down depending on undo or redo or natual game progeression
				moves_index--;
				board[moves[moves_index].board_move] = moves[moves_index].board_move + '0';
				draw_board();
			}
			else
			{
				printf("\nNo moves left to undo!\n");
			}
		}
		//redoing the moves
		else if (valid_move == 11)
		{
			char temp_mark = moves[moves_index].mark;
			//checking the mark before redoing the last move
			if (temp_mark == 'X' || temp_mark == 'O')
			{
				board[moves[moves_index].board_move] = temp_mark;
				moves_index++;
				draw_board();
			}
			else
			{
				printf("\nNo moves Left to redo!\n");
			}
		}
		else {
			printf("Invalid Move!");
			getch();
		}

	}
	//once the game is finshed, add it to an struct array to replay it at a later stage
	add_to_replay(moves);
}

//used to get a free slot in the replay index to store the replay
int get_free_replay_index()
{
	for (int i = 0; i < 100; i++)
	{
		if (strcmp(match_replays[i].match_moves[1].player_name, "") == 0)
		{
			return i;
		}
	}

	return NULL;

}
//a method that adds the game to the replay array, takes in a game struct
void add_to_replay(struct game_moves moves[9])
{
	int match_index = get_free_replay_index();

	//looping thhrough each game move and adding it to the replay
	for (int i = 0; i < 9; i++)
	{
		match_replays[match_index].match_moves[i].board_move = moves[i].board_move;
		match_replays[match_index].match_moves[i].mark = moves[i].mark;
		strcpy(match_replays[match_index].match_moves[i].player_name, moves[i].player_name);
	}
}
//player vs computer mode
void pve_mode()
{
	//setting up the game
	fseek(stdin, 0, SEEK_END);
	new_board();
	printf("Enter your name: ");
	scanf("%s", &player1);
	strcpy(player2, "Computer");
	char current_player[25];
	draw_board();
	strtok(player1, "/n");

	int gamewon = 0;
	int turn = 1;

	//looping until the game is finished
	while (gamewon == 0)
	{
		fseek(stdin, 0, SEEK_END);
		system("cls");
		draw_board();
		int choice;
		printf("Enter board Index: ");

		//if its users turn, get the board index from them
		if (turn == 1)
		{
			scanf("%d", &choice);
		}
		//if computers move, call a method that returns a valid move for the computer to play
		else
		{
			choice = computer_move();
		}

		//checking user move validity
		int valid_move = valid_move_checker(choice);
		if (valid_move == 1)
		{

			if (turn == 1)
			{
				board[choice] = 'X';
				turn = 2;
				draw_board();

				//checking to see if the game is won 
				int win = check_win();
				if (win == 1)
				{
					printf("%s won the game!", player1);
					gamewon = 1;
					break;
				}
				else if (win == 2)
				{
					printf("Draw!");
					break;
					getch();
				}
			}
			//checking the computers turn
			else if (turn == 2)
			{
				board[choice] = 'O';
				turn = 1;
				draw_board();
				int win = check_win();
				if (win == 1)
				{
					printf("Computer won the game!");
					gamewon = 1;
					break;
				}
				else if (win == 2)
				{
					printf("Draw!");
					break;
					getch();
				}
			}

		}
		else
		{
			printf("Invalid move!");
			getch();
		}

	}


}

//method that returns a valid move for the computer
int computer_move()
{
	int computer_choice;
	int valid_move = 0;
	while (valid_move == 0)
	{
		//generates a random number between 1-9 and checks if its valid or not until its valid
		computer_choice = (rand() % 8) + 1;
		if (board[computer_choice] == computer_choice + '0')
		{
			return computer_choice;
		}
	}
	return NULL;
}

//called after each game, adds the results from the game to the leaderboard. Tracks wins, losses and total games
void add_to_leaderboard(char name[25], int win, int loss)
{
	int exists = 0;
	//if the player is already in the leaderboard, just increase their win or loss and total game
	for (int idx = 0; idx < 100; idx++)
	{
		if ((strcmp(leaderboard_array[idx].name, name) == 0))
		{
			if (win == 1)
			{
				leaderboard_array[idx].wins++;
			}
			if (loss == 1)
			{
				leaderboard_array[idx].losses++;
			}

			leaderboard_array[idx].total++;
			exists = 1;
		}
	}
	//if not in the leaderboard, find the next empty slot and add the user to the leaderboard
	if (exists == 0)
	{
		for (int idx = 0; idx < 100; idx++)
		{
			if ((strcmp(leaderboard_array[idx].name, "") == 0))
			{
				strcpy(leaderboard_array[idx].name, name);
				leaderboard_array[idx].wins = 0;
				leaderboard_array[idx].losses = 0;
				leaderboard_array[idx].total = 0;

				if (win == 1)
				{
					leaderboard_array[idx].wins++;
				}
				if (loss == 1)
				{
					leaderboard_array[idx].losses++;
				}
				leaderboard_array[idx].total++;
				break;

			}
		}

	}

}
//method that prints the leaderboad 
void print_leaderboard()
{
	system("cls");
	printf("Name \t\t\t Wins \t Losses \t Total\n\n");
	for (int i = 0; i < 100; i++) {
		//checking to see of the leaderboard entry is populated
		if (strcmp(leaderboard_array[i].name, "") == 1) {
			printf("%s \t\t %d \t %d \t\t %d\n", leaderboard_array[i].name, leaderboard_array[i].wins, leaderboard_array[i].losses, leaderboard_array[i].total);
		}
	}
	getch();
}

//match replay menu, sub menu of the main game
void match_replays_selection()
{
	system("cls");
	printf("Match Replays  \n");
	printf("Invalid input will simulate an empty board or the first game. \n\n");

	//goes through the match replay data and prints all the valid replays the user can watch
	for (int i = 0; i < 100; i++)
	{
		if ((strcmp(match_replays[i].match_moves[0].player_name, "") == 1) && (strcmp(match_replays[i].match_moves[1].player_name, "") == 1))
		{
			printf("%d ) Match between %s and %s\n", i, match_replays[i].match_moves[0].player_name, match_replays[i].match_moves[1].player_name);
		}
	}
	int match_idx = -1;

	//takes in user choice of game and replays that
	scanf("%d", &match_idx);;
	if (-1 < match_idx < 100)
	{
		fseek(stdin, 0, SEEK_END);
		launch_replay(match_idx);
	}

}
//method that actually replays the match
void launch_replay(int game_index)
{
	//setting the player names to match the replay names
	strcpy(player1, match_replays[game_index].match_moves[0].player_name);
	strcpy(player2, match_replays[game_index].match_moves[1].player_name);
	system("cls");
	new_board();
	draw_board();
	//looping through the 9 moves
	for (int i = 0; i < 9; i++)
	{

		int temp_move = match_replays[game_index].match_moves[i].board_move;
		char temp_mark = match_replays[game_index].match_moves[i].mark;
		char dummydata = '0';

		//if the mark is valid, show it on the board
		if (temp_mark == 'X' || temp_mark == 'O')
		{
			//takes in user input to simulate the next move 
			printf("Press Any Key To Simulate Next Move.");
			scanf("%d", &dummydata);
			board[temp_move] = temp_mark;
			draw_board();
			fseek(stdin, 0, SEEK_END);

		}

	}
	printf("\n\nReplay Finished. Press Any Key to go back.\n");
	getch();

}