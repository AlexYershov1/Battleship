#pragma once

#include "submarine.h"

const int amount_of_subs = 5;
const int table_size = 10;


class game_board {
private:
	t_cell _board[table_size][table_size] = { nothing };
	int _items_count = amount_of_subs;

	submarine _subs[amount_of_subs];
	int _current_sub;

public:
	game_board();

	/// <summary>
	/// text that explains which ship is added to the board
	/// and the size of the ship
	/// </summary>
	/// <param name="size">
	/// size used both as ships' serial number
	/// and the size of the ship in cells </param>
	void pre_text(int size);

	/// <summary>
	/// Insert Player Submarine by start and end point
	/// </summary>
	/// <param name="start">start index of ships' route</param>
	/// <param name="end">end index of ships' route</param>
	/// <returns>TRUE if inserted successfully, otherwise FALSE</returns>
	bool insert(int start, int end, int size);

	/// <summary>
	/// Checks if the user entered valid indexes for the ships' location.
	/// Function is called from the 'insert' function.
	/// </summary>
	/// <param name="start">start index of ships' route</param>
	/// <param name="end">end index of ships' route</param>
	/// <param name="size">required size of ship</param>
	/// <param name="is_horizontal">direction of ship, by reference</param>
	/// <returns>TRUE if pick is valid, otherwise FALSE</returns>
	bool check_user_pick(int start, int end, int size, bool& is_horizontal);

	/// <summary>
	/// Checks if the spot the user chose had already been occupied by another ship.
	/// </summary>
	/// <param name="start">start index of ships' route</param>
	/// <param name="end">end index of ships' route</param>
	/// <param name="is_horizontal">direction of ship</param>
	/// <returns>TRUE if spot is occupied, otherwise FALSE</returns>
	bool Is_spot_taken(int start, int end, bool is_horizontal);

	/// <summary>
	/// Adding a ship both to board and submarine information. Ultimately,
	/// adding a new game piece to the game.
	/// </summary>
	/// <param name="start">start index of ships' route</param>
	/// <param name="end">end index of ships' route</param>
	/// <param name="is_horizontal">direction of ship</param>
	void add_to_board(int start, int end, bool direction);

	/// <summary>
	/// Player is trying to shoot down other Players' submarine on the board
	/// </summary>
	/// <param name="point">target index</param>
	/// <param name="end">check if player deserves another turn after hitting
	/// a target, by reference</param>
	/// <returns>TRUE if there was a hit, otherwise FALSE</returns>
	bool shoot(int point, bool& another_turn);

	/// <summary>
	/// Upon a hit, marking the index that was hit on the ship info
	/// </summary>
	/// <param name="point">the target that was hit</param>
	void mark_submarine(int point);

	/// <summary>
	/// Check if Player x won the game
	/// </summary>
	/// <returns>TRUE if wins, otherwise FALSE</returns>
	bool is_win();

	/// <summary>
	/// Check if point is an index on the board
	/// </summary>
	/// <param name="point">an index</param>
	/// <returns>TRUE if on board, otherwise FALSE</returns>
	bool Is_point_on_board(int point);

	/// <summary>
	/// Draw the board
	/// </summary>
	/// <param name="is_enemy">toggle between drawing the board as an enemy
	/// board or as the players' own board</param>
	void draw(bool is_enemy);

	/// <summary>
	/// Draw the horizontal lines of the board
	/// </summary>
	void draw_roof_and_bottom();

	/// <summary>
	/// Assist drawing own board during the insert stage
	/// </summary>
	/// <param name="box">a single cell in the board</param>
	/// <param name="index">index of the cell</param>
	void draw_own_board(t_cell box, int index);

	/// <summary>
	/// Assist drawing enemiems board during the insert stage
	/// </summary>
	/// <param name="box">a single cell in the board</param>
	/// <param name="index">index of the cell</param>
	void draw_enemy_board(t_cell box, int index);

	void draw_ships();

	/// <summary>
	/// Check if memory could be allocated for the dynamic array.
	/// in case the memory is insufficient, the program is tarminated.
	/// </summary>
	/// <param name="index"></param>
	void check_allocation(int* points);
};
