/* Battleship (game)
   * =========================================
   * Written by: Alex Yershov, GitHub account = AlexYershov1
   *
   * This program simulates the a two player game battleship. Each
   * player inserts 5 ships into a 10x10 board using the keyboard.
   * Afterwards, each player, in its' turn, tries to sink all the battleships
   * of the other player.
   * Ground rules:
   *	a. Each player receives the same amount of battleships - 5.
   *	   The sizes of the ships are 2, 3, 4, 5 , 6 (by cells).
   *	b. A battleship can be placed horizontally or vertically only.
   *	c. Whenever a hit is made, the player gets another turn.
   *	d. First player to sink all his enemies ships is declared the winner!
   *	e. Have Fun!
   * input:
   *     5 ships using a start index and an end index, based on the board
		 that is presented on the screen.
 */

#include <iostream>
#include <stdlib.h>
#include "game_board.h"

void log_in_page();
void enter_ships_page(game_board& b);
void draw_screen(game_board board_ply_1, bool is_enemy);
int end(bool ply_1_won);

void log_in_page() {
	cout << "Welcome to Battleship ! " << endl;
	system("pause");
	system("CLS");
}

void enter_ships_page(game_board& board) {
	// Insert Submarines
	cout << "Please choose the locations of your 5 ships, use the numbers on the filled board to do so." << endl
		 << "Please note that for each ship, two numbers are required - a start and an end index." << endl
		 << "Finally, press enter to accept." << endl;
	board.draw(false); // draw empty board
	for (int counter = 1; counter <= amount_of_subs; counter++) {
		bool inserted = false; // has the ship been inserted ?
		while (!inserted) {
			int start, end; // start and end indexes for ship
			board.pre_text(counter);
			cin >> start >> end;
			
			inserted = board.insert(start, end, counter + 1);
			if (!inserted) {
				cout << "Failed to insert, try again" << endl;
			}
			else
				draw_screen(board, false);
		}
	}
}

/// <summary>
/// draw suitable board and ships on screen
/// </summary>
/// <param name="board_ply"> the board to be printed </param>
/// <param name="Is_enemy"> determinantes whether a board needs to be printed as a board
/// for the eyes of the enemy or as a board with the ships pictured in it,
/// like in the insertion level </param>
void draw_screen(game_board board_ply, bool is_enemy) {
	board_ply.draw(is_enemy);
	board_ply.draw_ships();
}

int end(bool ply_1_won) {
	if (ply_1_won)
		cout << "Player 1 won the game! Congratulations!" << endl;
	else
		cout << "Player 2 won the game! Congratulations!" << endl;
	cout << endl << "Thank you for playing !" << endl
		 << "Credit: Alex Yershov, GitHub account: AlexYershov1" << endl;
	system("pause");
	return EXIT_SUCCESS;
}

// testing
int main0() {
	game_board board;

	bool inserted = board.insert(0, 3, 3);
	if (inserted) {
		cout << "TEST FAILED!" << endl;
	}

	inserted = board.insert(0, 2, 3);
	if (!inserted) {
		cout << "TEST FAILED!" << endl;
	}
	return 0;
}

// main
int main() {
	game_board board_ply_1, board_ply_2;
	log_in_page();
	enter_ships_page(board_ply_1); // enter player 1 ships
	system("CLS");
	enter_ships_page(board_ply_2); // enter player 2 ships
	system("CLS");

	bool player1 = true,	  // toggle between players turns
		another_turn = false, // if player hit the target, it deserves another turn
		ply_1_won = false, ply_2_won = false; // which player won the game

	while (!ply_1_won && !ply_2_won) {
		int point; // target to shoot

		cout << "Enter point to hit" << endl;
		cin >> point;

		system("CLS"); // clear for new round

		bool hit = player1 ? 
			board_ply_2.shoot(point, another_turn) : board_ply_1.shoot(point, another_turn);

		if (!hit) { // was the shot valid or not
			cout << "wrong coordinate entered, please try again." << endl;
			continue;
		}

		if (player1) // draw board of player 2
			draw_screen(board_ply_2, true); 
		else         // draw board of player 1
			draw_screen(board_ply_1, true);

		// check if game was won
		ply_1_won = board_ply_1.is_win();
		ply_2_won = board_ply_2.is_win();

		if (another_turn) { // in case of a hit
			another_turn = false;
			continue;
		}

		player1 = !player1; // switch turn
	}
	return end(ply_1_won);
}