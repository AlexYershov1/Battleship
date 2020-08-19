#include "game_board.h"


game_board::game_board() {
	this->_current_sub = 0;
	// create the game pieces in the board
	for (int count = 1; count <= amount_of_subs; count++) {
		int* points = new (std::nothrow) int[count+1];
		check_allocation(points);
		this->_subs[count-1].new_submarine(points, count + 1);
	}
}
//--------------------------------------------//
bool game_board::is_win() {
	bool status = true;
	for (int count = 0; count < amount_of_subs; count++) {
		if (this->_subs[count].is_alive())
			status = false; // found a ship that still survived
	}
	return status;
}
//--------------------------------------------//
bool game_board::shoot(int point, bool& another_turn) {
	if (Is_point_on_board(point)) {
		t_cell* box = &this->_board[point / 10][point % 10]; // get target cell
		if (*box == miss || *box == hit) // in case the cell has been targeted before
			return false;
		if (*box == ship) {	// check if ship is located at this cell
			*box = hit;		// it's a hit
			mark_submarine(point); // pass the info to the submarine data
			cout << "It was a hit!" << endl;
			another_turn = true; // player deserves to continue its' turn
		}
		else {
			*box = miss;    // it's a miss
			cout << "It was a miss!" << endl;
		}
		return true; // target was valid
	}
	return false;
}
//--------------------------------------------//
void game_board::mark_submarine(int point) {
	for (int count = 0; count < amount_of_subs; count++) {
		if (this->_subs[count].hit(point))
			break;
	}
}
//--------------------------------------------//
void game_board::pre_text(int size) {
	cout << "pick a spot for submarine number " << size
		<< ", the size of the submarine in cells is: " << size + 1 << endl;
}
//--------------------------------------------//
bool game_board::insert(int start, int end, int size) {
	bool is_horizontal;
	if (start > end) // swap so that start is the starting index of the route
		swap(start, end);

	if (this->check_user_pick(start, end, size - 1, is_horizontal) &&
		!this->Is_spot_taken(start, end, is_horizontal)) {
		// pick is valid
		this->add_to_board(start, end, is_horizontal);
		return true;
	}
	return false; // pick is not valid, need to pick again
}
//--------------------------------------------//
bool game_board::check_user_pick(int start, int end, int size, bool& is_horizontal) {
	bool valid = false; // Did the user enter a valid location for the submarines
	// check if pick is valid
	// are start and end between 0 and 99
	if (!(Is_point_on_board(start) && Is_point_on_board(end)))
		return valid;
	// horizontal route
	if (end - start == size && // check route size is valid
		start / 10 == end / 10) { // check that route doesn't change line midway
		is_horizontal = true;
		valid = true;
	}
	// vertical route
	else if (end - start == size * 10) { // check route size is valid
		is_horizontal = false;
		valid = true;
	}
	return valid;
}
//--------------------------------------------//
bool game_board::Is_spot_taken(int start, int end, bool is_horizontal) {
	while (start != end) {
		if (this->_board[start / 10][start % 10] == ship)
			return true;
		// advance to checking next cell
		if (is_horizontal)
			start++;
		else
			start += 10;
	}
	// check last cell
	if (this->_board[start / 10][start % 10] == ship)
		return true;
	return false; // route not taken
}
//--------------------------------------------//
void game_board::add_to_board(int start, int end, bool is_horizontal) {
	int i = 0;
	while (start != end) {
		this->_subs[this->_current_sub].add_point_to_sub(start, i); // add the point to submarine info
		this->_board[start / 10][start % 10] = ship; // add the point to board info
		// change index according to route
		if (is_horizontal)
			start++;
		else
			start += 10;
		i++; // next
	}
	this->_subs[this->_current_sub].add_point_to_sub(start, i);   // add the point to submarine info
	this->_board[start / 10][start % 10] = ship; // add the point to board info
	system("CLS");
	cout << "submarine added" << endl; // conclusion
	this->_current_sub++;
}
//--------------------------------------------//
bool game_board::Is_point_on_board(int point) {
	if (point < 0 || point > 99)
		return false;
	return true;
}
//--------------------------------------------//
void game_board::draw(bool is_enemy) {
	// write the entire table
	for (int row = 0; row < table_size; row++) {
		this->draw_roof_and_bottom();
		for (int col = 0; col < table_size; col++) {
			cout << '|';
			cout << std::setfill(' ') << std::setw(3);
			// send cell and cells' index as parameters
			if (is_enemy)
				draw_enemy_board(_board[row][col], row * 10 + col);
			else
				draw_own_board(_board[row][col], row * 10 + col);
		}
		cout << '|' << endl;
	}
	this->draw_roof_and_bottom();
}
//--------------------------------------------//
void game_board::draw_own_board(t_cell box, int index) {
	switch (box)
	{
	case ship:
		cout << 'x';
		break;
	default:
		cout << index; // print location of cell
	}
}
//--------------------------------------------//
void game_board::draw_enemy_board(t_cell box, int index) {
	switch (box)
	{
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
void game_board::draw_roof_and_bottom() {
	// write the bottom and roof of the table: ----------------
	for (int i = 0; i < table_size; i++)
		cout << "----";
	cout << endl;
}
//--------------------------------------------//
void game_board::draw_ships() {
	cout << "Ships:" << endl;
	for (int count = 0; count < amount_of_subs; count++) {
		this->_subs[count].draw();
	}
}
//--------------------------------------------//
void game_board::check_allocation(int* points) {
	if (points == NULL) {
		cerr << "cannot allocate memory \n";
		exit(EXIT_FAILURE);
	}
}
