#pragma once
#include<iostream>
#include<iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::swap;
using std::cerr;


enum t_cell { nothing, ship, hit, miss };

class submarine {
private:
	int _size;
	int* _points;
	bool Is_empty;

public:
	submarine();

	/// <summary>
	/// New ship is added to the game pieces
	/// </summary>
	/// <param name="points"> the newly created array of points </param>
	/// <param name="size"> size of ship </param>
	void new_submarine(int* points, int size);

	/// <summary>
	/// Adding a new index to a ship
	/// </summary>
	/// <param name="point"> index in the board </param>
	/// <param name="index"> index in the ship </param>
	void add_point_to_sub(int point, int index);

	/// <summary>
	/// Check if ship has't sunk yet
	/// </summary>
	bool is_alive();

	/// <summary>
	/// Marking a hit on the ship in case of a hit
	/// </summary>
	/// <param name="point"> target to hit </param>
	bool hit(int point);

	/// <summary>
	/// draw the ship
	/// </summary>
	void draw();
};
