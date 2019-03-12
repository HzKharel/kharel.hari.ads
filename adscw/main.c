#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "Header.h"


//global variables
char player1[25], player2[25], board[9];


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
	switch (selection)
	{
	case 1:
		pvp_mode();
		break;
	case 2:
		pve_mode();
		break;
	case 3:
		printf("Launch Replays");
		break;
	case 4:
		printf("Launch scoreboard");
		break;
	case 5:
		leaderboard(name);
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
	printf("\t\t%s (X)  - %s (O)\n\n\n", player1, player2);
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
	for (int i = 1; i < 10; i++) {
		board[i] = i + '0';
	}
	return board;
}

//function to get the player names
void get_player_names()
{
	static char players[2][25];


	printf("Player 1 Name: ");
	scanf("%s", &player1);
	strtok(players[0], "/n");

	printf("Player 2 Name: ");
	scanf("%s", &player2);
	strtok(players[1], "/n");

	//clearing stream
	fseek(stdin, 0, SEEK_END);
}

int valid_move_checker(int choice)
{
	/*
		1 = Valid Move
		0 = Undo
		11 = Redo
		-1 = Invalid move
	*/
	if (choice == 1 && board[1] == '1' || choice == 2 && board[2] == '2' || choice == 3 && board[3] == '3' || choice == 4 && board[4] == '4' || choice == 5 && board[5] == '5' || 
		choice == 6 && board[6] == '6' || choice == 7 && board[7] == '7' || choice == 8 && board[8] == '8' || choice == 9 && board[9] == '9')
	{
		return 1;
	}

	else if (choice == 0)
	{
		return 0;
	}
	else if (choice == 11)
	{
		return  11;
	}
	else
	{
		return -1;
	}
}

int check_win()
{
	/*  * 1 = Game Won
		* 2 = Game draw
		* 0 = Game Still in Progress
		*
	*/
	if (board[1] == board[2] && board[2] == board[3] || board[4] == board[5] && board[5] == board[6] || board[7] == board[8] && board[8] == board[9] ||
		board[1] == board[4] && board[4] == board[7] || board[2] == board[5] && board[5] == board[8] || board[2] == board[5] && board[5] == board[8] ||
		board[3] == board[6] && board[6] == board[9] || board[1] == board[5] && board[5] == board[9] || board[3] == board[5] && board[5] == board[7])
	{

		return 1;

	}

	else if (board[1] != '1' && board[2] != '2' && board[3] != '3' &&
		board[4] != '4' && board[5] != '5' && board[6] != '6' && board[7]
		!= '7' && board[8] != '8' && board[9] != '9')
	{
		return 2;
	}
	else
	{
		return  0;
	}
			

}


void pvp_mode()
{
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

	while (game_won == 0)
	{
		system("cls");
		printf("%s, Enter board index, 0 to undo, 11 to redo: ", player);
		int choice;
		scanf("%d", &choice);
		int valid_move  = valid_move_checker(choice);

		//if the player makes a valid move on the board
		if (valid_move == 1) 
		{
			moves[moves_index].board_move = choice;
			moves[moves_index].mark = mark;
			strcpy(moves[moves_index].player_name, &player);
			
			moves_index++;
			board[choice] = mark;
			draw_board();
			int win = check_win();
			if (win == 1)
			{
				system("cls");
				draw_board();
				printf("%s won the game!", &player);
				break;

			}
			if (win == 2)
			{
				system("cls");
				draw_board();
				printf("Draw!");
				break;

			}
			else
			{
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
		if (valid_move == 0)
		{
			if (moves_index > 0)
			{
				moves_index--;
				board[moves[moves_index].board_move] = moves[moves_index].board_move + '0';
				draw_board();
			}
			else
			{
				printf("\nNo moves left to redo!\n");
			}
		}
		if (valid_move == 11)
		{
			char temp_mark = moves[moves_index].mark;
			if(temp_mark == 'X' || temp_mark == 'O')
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



	}
}


void pve_mode()
{
	fseek(stdin, 0, SEEK_END);
	new_board();
	printf("Enter your name: ");
	scanf("%s", &player1);
	strcpy(player2, "Computer");
	draw_board();
	strtok(player1, "/n");

	int gamewon = 0;
	int turn = 1;

	while (gamewon == 0)
	{
		fseek(stdin, 0, SEEK_END);
		system("cls");
		draw_board();
		int choice;
		printf("Enter board Index: ");
		

		if (turn == 1)
		{
			scanf("%d", &choice);
		}
		else
		{
			choice = computer_move();
		}
		int valid_move = valid_move_checker(choice);
		if(valid_move == 1)
		{

			if (turn == 1)
			{
				board[choice] = 'X';
				turn = 2;
				draw_board();
			}
			else if(turn == 2)
			{
				board[choice] = 'O';
				turn = 1;
				draw_board();
			}
			
		}
		else
		{
			printf("Invalid move!");
			getch();
		}


		int win = check_win();

		if (win == 1)
		{
			printf("%s won the game!", player1);
			gamewon = 1;
			break;
		}
		else if (win == 2)
		{
			printf("Draw!", player2);
			break;
			getch();
		}

		
	}
	

}

int computer_move()
{
	int computer_choice;
	int valid_move = 0;
	while (valid_move == 0)
	{
		computer_choice = (rand() % 8) + 1;
		if (board[computer_choice] == computer_choice +'0')
		{
			return computer_choice;
		}
	}
}
void leaderboard(char name[25]) 
{
	FILE* File_Editor;
	File_Editor = fopen("leaderboard.txt", "r");
	char line[100];
	if (!File_Editor == NULL) 
	{
		while (fgets(line, sizeof(line), File_Editor)) {
			
		}
	}



}