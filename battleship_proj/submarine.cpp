#include "submarine.h"


submarine::submarine() {
	this->_size = 0;
	this->_points = NULL;
	this->Is_empty = true;
}
//--------------------------------------------//
void submarine::new_submarine(int* points, int size) {
	this->_points = points;
	this->_size = size;
}
//--------------------------------------------//
void submarine::add_point_to_sub(int point, int index) {
	this->_points[index] = point;
	this->Is_empty = false;
}
//--------------------------------------------//
bool submarine::hit(int point) {
	for (int count = 0; count < this->_size; count++) {
		if (this->_points[count] == point) {
			this->_points[count] = -1; // point destroyed
			return true;
		}
	}
	return false;
}
//--------------------------------------------//
bool submarine::is_alive() {
	for (int count = 0; count < this->_size; count++) {
		if (this->_points[count] != -1)
			return true;	// ship survived
	}
	return false;
}
//--------------------------------------------//
void submarine::draw() {
	if (this->Is_empty == false) {
		for (int count = 0; count < this->_size; count++) {
			switch (this->_points[count])
			{
			case -1: // ship is hit
				cout << 'x';
				break;
			default: // ship is not hit
				cout << '*';
				break;
			}
		}
		cout << endl;
	}
}