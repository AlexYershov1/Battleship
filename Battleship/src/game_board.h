#include "empty_board.h"
#include "submarine.h"
#include "network.h"

class game_board: public empty_board {
private:
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
	/// a target, by reference</param>
	/// <returns>TRUE if another turn is deserved, otherwise FALSE</returns>
	bool shoot(int point);

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
	/// draws ships on board
	/// </summary>
	void draw_ships();

	/// <summary>
	/// Check if memory could be allocated for the dynamic array.
	/// in case the memory is insufficient, the program is tarminated.
	/// </summary>
	/// <param name="index"></param>
	void check_allocation(int* points);
};
