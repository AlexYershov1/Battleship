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
#include "network.h"
 //---------------prototype-------------------//
void log_in_page();
void enter_ships_page(game_board& b);
void draw_screen(game_board board_ply_1, empty_board enemy_status);
bool offence(game_board& board, empty_board& status, void* socket);
bool defence(game_board& board, void* socket);
void write_result(bool another_turn, bool toggle);
int end(bool ply_1_won);
//--------------------------------------------//
void log_in_page() {
	cout << "Welcome to Battleship ! " << endl;
	system("pause");
	system("CLS");
}
//--------------------------------------------//
void enter_ships_page(game_board& board) {
	// Insert Submarines
	cout << "Please choose the locations of your 5 ships, use the numbers on the filled board to do so." << endl
		<< "Please note that for each ship, two numbers are required - a start and an end index." << endl
		<< "Finally, press enter to accept." << endl;
	board.draw(); // draw empty board
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
			else {
				board.draw();
				board.draw_ships();
			}
		}
	}
}
//--------------------------------------------//
/// <summary>
/// draw suitable board and ships on screen
/// </summary>
/// <param name="board_ply"> the board to be printed </param>
/// <param name="Is_enemy"> determinantes whether a board needs to be printed as a board
/// for the eyes of the enemy or as a board with the ships pictured in it,
/// like in the insertion level </param>
void draw_screen(game_board board_ply, empty_board enemy_status) {
	cout << "my board:" << endl;
	board_ply.draw();
	board_ply.draw_ships();

	cout << endl << "enemy board status:" << endl;
	enemy_status.draw();
}
//--------------------------------------------//
int end(bool ply_won) {
	if (ply_won)
		cout << "You won the game! Congratulations!" << endl;
	else
		cout << "You lost the game! Better luck next time!" << endl;
	cout << endl << "Thank you for playing !" << endl
		<< "Credit: Alex Yershov, GitHub account: AlexYershov1" << endl;
	system("pause");
	return EXIT_SUCCESS;
}
//--------------------------------------------//
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
//--------------------------------------------//
// main
int main(int argc, char* argv[]) {
//	------------initialize_connection------------------
	if (argc != 2) {
		cout << "Enter: main.exe server/client" << endl;
		return 0;
	}

	void* socket = NULL;
	bool is_server,
		 toggle; // start - true for server false for client
	if (strcmp(argv[1], "server") == 0) {
		is_server = toggle = true;
		init_socket_library();
		socket = server_wait_for_client();
	}
	else if (strcmp(argv[1], "client") == 0) {
		is_server = toggle = false;
		init_socket_library();
		socket = client_connect_to_server();
	}
	else {
		cout << "Enter: main.exe server/client" << endl;
		return 0;
	}
//	------------------THE GAME-------------------------
	game_board board;
	empty_board status;
	log_in_page();
	enter_ships_page(board); // enter player ships
	system("CLS");
	draw_screen(board, status);

	bool another_turn; // if player hit the target, it deserves another turn
	bool ply_won = false; // which player won the game

	while (!ply_won) {
		bool start_toggle = toggle; // state of defence/offence at the beginning of the round
		if (toggle) {
			another_turn = defence(board, socket);
			if (!another_turn)
				toggle = false;
		}
		else {
			//draw_screen(board, status);
			another_turn = offence(board, status, socket);
			if (!another_turn)
				toggle = true;
		}

		system("CLS"); // clear for new round
		write_result(another_turn, start_toggle);
		draw_screen(board, status);
		// check if game was won
		ply_won = board.is_win();
	}
	return end(ply_won);
}
//--------------------------------------------//
bool offence(game_board& board, empty_board& status, void* socket) {
	int point, // point to hit
		res;   // result of hit: hit/miss
	do {
		cout << "Enter a valid point to hit:" << endl;
		cin >> point;
		cout << endl;
	} while (!board.Is_point_on_board(point) || status.was_targeted_before(point));

	socket_send(socket, point);

	// analyzing the result
	res = socket_recv(socket);
	if (res == -1) { // a hit was made
		status.mark_status(point, true);
		return true;
	}
	else		   // a miss was made
		status.mark_status(point, false);
	return false;
}
//--------------------------------------------//
bool defence(game_board& board, void* socket) {
	cout << "waiting for the enemy to attack...";
	int target = socket_recv(socket);
	system("CLS");
	bool another_turn = board.shoot(target); // mark on board
	socket_send(socket, another_turn); // send result of attack
	return another_turn;
}

void write_result(bool another_turn, bool toggle) {
	if (toggle) {
		if (another_turn)
			cout << "The enemy hit!" << endl;
		else
			cout << "The enemy missed!" << endl;
	}
	else {
		if (another_turn)
			cout << "You hit the enemy ships! You get to attack again!" << endl;
		else
			cout << "You missed the enemy ships! We'll get them next time!" << endl;
	}
}
/*
previous main

	//while (!ply_won) {
	//	int point; // target to shoot
	//	int target; // enemys' target

	//	draw_screen(board, status);

	//	if (is_server) {
	//		target = socket_recv(socket);
	//		cout << "we use server" << endl << target;
	//	}
	//
	//	do {
	//		cout << "Enter a valid point to hit:" << endl;
	//		cin >> point;
	//		cout << endl;
	//	} while (!board.Is_point_on_board(point) || status.was_targeted_before(point));
	//	system("CLS"); // clear for new round

	//	socket_send(socket, point, another_turn);

	//	if (!is_server)
	//		target = socket_recv(socket);

	//	if (target == -1) { // in case player deserves another turn
	//		status.mark_status(point, true); // a hit was made
	//		continue;
	//	}
	//	else
	//		status.mark_status(point, false); // a miss was made

	//	another_turn = board.shoot(target);

	//	// check if game was won
	//	ply_won = board.is_win();
	//}
	//return end(ply_won);


*/