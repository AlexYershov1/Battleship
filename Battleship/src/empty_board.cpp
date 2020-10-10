#include "empty_board.h"

//--------------------------------------------//
void empty_board::draw() {
	// write the entire table
	for (int row = 0; row < table_size; row++) {
		this->draw_roof_and_bottom();
		for (int col = 0; col < table_size; col++) {
			cout << '|';
			cout << std::setfill(' ') << std::setw(3);
			// send cell and cells' index as parameters
			draw_info(_board[row][col], row * 10 + col);
		}
		cout << '|' << endl;
	}
	this->draw_roof_and_bottom();
}
//--------------------------------------------//
void empty_board::draw_info(t_cell box, int index) {
	switch (box)
	{
	case ship:
		cout << '&';
		break;
	case hit:
		cout << 'x';
		break;
	case miss:
		cout << '*';
		break;
	default:
		cout << index; // print location of cell
	}
}
//--------------------------------------------//
void empty_board::draw_roof_and_bottom() {
	// write the bottom and roof of the table: ----------------
	for (int i = 0; i < table_size; i++)
		cout << "----";
	cout << endl;
}
//--------------------------------------------//
void empty_board::mark_status(int point, bool is_hit) {
	t_cell* box = &this->_board[point / 10][point % 10]; // get target cell
	if (is_hit) 
		*box = hit;
	else 
		*box = miss;
}
//--------------------------------------------//
bool empty_board::was_targeted_before(int point) {
	t_cell* box = &this->_board[point / 10][point % 10]; // get target cell
	if (*box == miss || *box == hit)
		return true;
	return false;
}