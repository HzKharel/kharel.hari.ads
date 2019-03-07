#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "Header.h"


void get_player_names();
char board[10];
char player1_name[15];
char player2_name[15];

void draw_board() {
	//clear previous draws
	system("cls");
	printf("\n\n\t\tTic Tac Toe - ADS\n\n");
	printf("\t\t%s (X)  - %s (O)\n\n\n", player1_name, player2_name);
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



void play_game()
{
	int player_turn = 0;
	char player_name[25];
	char mark = 'X';
	int choice = 0;
	int game_won = 0;

	do
	{
		if (player_turn == 0)
		{
			strcpy(player_name, player1_name);
			mark = 'X';
			player_turn = 1;

		}
		else
		{
			strcpy(player_name, player2_name);
			mark = 'O';
			player_turn = 0;
		}

		printf("%s Enter grid number, or 0 to undo the last move: ", player_name);
		scanf("%d", &choice);

		if (choice == 1 && board[1] == '1') { board[1] = mark; }
		else if (choice == 2 && board[2] == '2') { board[2] = mark; }
		else if (choice == 3 && board[3] == '3') { board[3] = mark; }
		else if (choice == 4 && board[4] == '4') { board[4] = mark; }
		else if (choice == 5 && board[5] == '5') { board[5] = mark; }
		else if (choice == 6 && board[6] == '6') { board[6] = mark; }
		else if (choice == 7 && board[7] == '7') { board[7] = mark; }
		else if (choice == 8 && board[8] == '8') { board[8] = mark; }
		else if (choice == 9 && board[9] == '9') { board[9] = mark; }
		else
		{
			printf("Invalid move!");
			if (player_turn == 0)
			{
				player_turn = 1;
			}
			else
			{
				player_turn = 0;
			}
			getch();

			choice = 0;

		}

		game_won = check_win();
		draw_board();

	} while (game_won == 0);

	if (game_won == 1)
	{
		printf("\t\t%s, game is Won!", player_name);
	}


	getch();

	return 0;

}

void new_name()
{
	for (int i = 0; i < 10; i++)
	{

		board[i] = i + '0';
	}
	get_player_names();
	draw_board();
	play_game();
}


void get_player_names()
{

	printf("Enter Player 1 Name: ");
	fgets(player1_name, 25, stdin);
	strtok(player1_name, "\n");
	printf("Enter Player 2 Name: ");
	fgets(player2_name, 25, stdin);
	strtok(player2_name, "\n");

}

int check_win()
{

	/*  CONDITIONS:
	*   1 = Game Won
	*   2 = Game draw
	*   0 = Game Still in Progress
	*
	*/
	if (board[1] == board[2] && board[2] == board[3])
		return 1;

	else if (board[4] == board[5] && board[5] == board[6])
		return 1;

	else if (board[7] == board[8] && board[8] == board[9])
		return 1;

	else if (board[1] == board[4] && board[4] == board[7])
		return 1;

	else if (board[2] == board[5] && board[5] == board[8])
		return 1;

	else if (board[3] == board[6] && board[6] == board[9])
		return 1;

	else if (board[1] == board[5] && board[5] == board[9])
		return 1;

	else if (board[3] == board[5] && board[5] == board[7])
		return 1;

	else if (board[1] != '1' && board[2] != '2' && board[3] != '3' &&
		board[4] != '4' && board[5] != '5' && board[6] != '6' && board[7]
		!= '7' && board[8] != '8' && board[9] != '9')

		return 2;
	else
		return  0;

}

void main()
{
	int play_again = 0;
	do
	{
		new_name();
		printf("Enter 1 to play again.");
		scanf("%d", play_again);

	} while (play_again == 0);


}