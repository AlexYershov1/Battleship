#include "submarine.h"
const int amount_of_subs = 5;
const int table_size = 10;

class empty_board {
protected:
	t_cell _board[table_size][table_size] = { nothing };
public:
	/// <summary>
	/// Draw the board
	/// </summary>
	/// <param name="is_enemy">toggle between drawing the board as an enemy
	/// board or as the players' own board</param>
	void draw();

	/// <summary>
	/// Assist drawing the info inside the cells. For example,
	/// in a cell containing a ship, the character '&' is printed.
	/// </summary>
	/// <param name="box">a single cell in the board</param>
	/// <param name="index">index of the cell</param>
	void draw_info(t_cell box, int index);

	/// <summary>
	/// Draw the horizontal lines of the board
	/// </summary>
	void draw_roof_and_bottom();

	void mark_status(int point, bool is_hit);

	bool was_targeted_before(int point);
};
