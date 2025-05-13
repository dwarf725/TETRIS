#pragma once
#include <iostream>

class Coordinate {
private:
	int x;
	int y;
public: 
	Coordinate() {
		x = 0;
		y = 0;
	}

	void SetCoordinate(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int GetX() {
		return x;
	}

	int GetY() {
		return y;
	}
	
	~Coordinate() {

	}
};