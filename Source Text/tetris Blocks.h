#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>;
#include "coordinate.h"
using namespace std; 
using namespace sf;

class Tetrino {
protected: 
	char id;
	int rotationstate;
	Coordinate* coords;
	Coordinate Center;
	bool isactive;
	RectangleShape blocks[4];
public: 
	Tetrino() {
		id = ' ';
		rotationstate = 0; 
		coords = nullptr;
		isactive = true;
	}

	Tetrino ( Tetrino &obj ){
		id = obj.id;
		rotationstate = obj.rotationstate;
		delete coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i] = obj.coords[i];
		}
		Center = obj.Center;
		isactive = obj.isactive;
		for (int i = 0; i < 4; i++) {
			blocks[i] = obj.blocks[i];
		}
	}


	void virtual rotate(char**& grid)  = 0;

	void Move(int X, int Y, char**& grid) {
		bool valid = true;
		for (int i = 0; i < 4; i++) {
			int newX = coords[i].GetX() + X;
			int newY = coords[i].GetY() + Y;


			if (newX < 0 || newX >= 20 || newY < 0 || newY >= 10) {
				valid = false;
				break;
			}

			
			if (grid[newX][newY] != id && grid[newX][newY] != '*') {
				valid = false;
				break;
			}
		}
		if (valid == true) {
			for (int i = 0; i < 4; i++) {
				grid[coords[i].GetX()][coords[i].GetY()] = '*';
			}

			for (int i = 0; i < 4; i++) {
				coords[i].SetCoordinate(coords[i].GetX() + X, coords[i].GetY() + Y);
				grid[coords[i].GetX()][coords[i].GetY()] = id;
			}
		}
	}

	void collision(char**& grid, char**& dgrid) {
		for (int i = 0; i < 4; i++) {
			int x = coords[i].GetX();
			int y = coords[i].GetY();
			if ((x + 1 < 20 && grid[x + 1][y] == 'A') || x == 19) {
				isactive = false;
				for (int j = 0; j < 4; j++) {
					dgrid[coords[j].GetX()][coords[j].GetY()] = id;
					grid[coords[j].GetX()][coords[j].GetY()] = 'A';
				}
			}
		}
	}
	/*void draw(RectangleShape**& grid,RenderWindow& win) {
		for (int i = 0; i < 4; i++) {
			blocks[i].setPosition(grid[coords[i].GetX()][coords[i].GetY()].getPosition());
			win.draw(blocks[i]);
		}
	}*/
	void Create(char**& grid, bool &gameended) {
		for (int i = 0; i < 4; i++) {
			if (grid[coords[i].GetX()][coords[i].GetY()] != '*' && grid[coords[i].GetX()][coords[i].GetY()] != id) {
				gameended = true;
			}
			grid[coords[i].GetX()][coords[i].GetY()] = id;
		}
	}

	char getId() const { return id; }
	int getRotationState() const { return rotationstate; }
	Coordinate getCoord(int i) const { return coords[i]; }
	Coordinate getCenter() const { return Center; }
	bool getIsActive() const { return isactive; }


	bool Getstatus() {
		return isactive;
	}

	void SetCoord(int i, int j, int k) { coords[i].SetCoordinate(j, k); }

	void virtual assign(Tetrino* obj) = 0;
};

class TBlock :public Tetrino {
public: 
	TBlock() {
		id = 'T';
		rotationstate = 0;
		coords = new Coordinate[4];
		Center.SetCoordinate(0, 5);
		coords[0] = Center;
		coords[1].SetCoordinate(0, 4);
		coords[2].SetCoordinate(0, 6);
		coords[3].SetCoordinate(1, 5);
		for (int i = 0; i < 4; i++) {
			blocks[i].setSize(Vector2f(30.f, 30.f));
			blocks[i].setFillColor(Color::Magenta);
		}
	}

	void assign(Tetrino* obj) override {
		id = obj->getId();
		rotationstate = obj->getRotationState();
		delete[] coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i].SetCoordinate(obj->getCoord(i).GetX(), obj->getCoord(i).GetY());
		}
		Center = obj->getCenter();
		isactive = obj->getIsActive();
	}

	void rotate(char**& grid) override {
		Center = coords[0];
		rotationstate++;
		if (rotationstate == 4) {
			rotationstate = 0;
		}

		if (Center.GetX() + 1 < 20 && Center.GetX() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX() + 1][Center.GetY()] == '*'|| grid[Center.GetX() + 1][Center.GetY()] == id) && (grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id) && (grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id)) {
				if (rotationstate == 1) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					coords[3].SetCoordinate(Center.GetX() + 1, Center.GetY());
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id) && (grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id) && (grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 2) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}
	
		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id) && (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id) && (grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 3) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetY() + 1 < 10 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id) && (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id) && (grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 0) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() , Center.GetY() + 1);
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}
		
	}

	



};

class ZBlock :public Tetrino {
public:
	ZBlock() {
		id = 'Z';
		rotationstate = 0;
		coords = new Coordinate[4];
		Center.SetCoordinate(0, 6);
		coords[0] = Center;
		coords[1].SetCoordinate(0, 7);
		coords[2].SetCoordinate(1, 6);
		coords[3].SetCoordinate(1, 5);
		for (int i = 0; i < 4; i++) {
			blocks[i].setSize(Vector2f(30.f, 30.f));
			blocks[i].setFillColor(Color::Green);
		}
	}

	void assign(Tetrino* obj) override {
		id = obj->getId();
		rotationstate = obj->getRotationState();
		delete[] coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i].SetCoordinate(obj->getCoord(i).GetX(), obj->getCoord(i).GetY());
		}
		Center = obj->getCenter();
		isactive = obj->getIsActive();
	}


	void rotate(char**& grid) override {
		Center = coords[0];
		rotationstate++;
		if (rotationstate == 4) {
			rotationstate = 0;
		}

		if ((Center.GetX() + 1 < 20) && Center.GetX() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX() + 1][Center.GetY() + 1] == '*' || grid[Center.GetX() + 1][Center.GetY() + 1] == id) && (grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id) && (grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id)) {
				if (rotationstate == 1) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					coords[3].SetCoordinate(Center.GetX() + 1, Center.GetY() + 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id) && (grid[Center.GetX() - 1][Center.GetY() + 1] == '*' || grid[Center.GetX() - 1][Center.GetY() + 1] == id) && (grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 2) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX() - 1, Center.GetY() + 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() - 1][Center.GetY() - 1] == '*' || grid[Center.GetX() - 1][Center.GetY() - 1] == id) && (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id) && (grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 3) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY() - 1);
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetY() + 1 < 10 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() + 1][Center.GetY() + 1] == '*' || grid[Center.GetX() + 1][Center.GetY() + 1] == id) && (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id) && (grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 0) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() + 1, Center.GetY() + 1);
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

	}
};


class SBlock :public Tetrino {
public:
	SBlock() {
		id = 'S';
		rotationstate = 0;
		coords = new Coordinate[4];
		Center.SetCoordinate(0, 5);
		coords[0] = Center;
		coords[1].SetCoordinate(0, 4);
		coords[2].SetCoordinate(1, 5);
		coords[3].SetCoordinate(1, 6);
		for (int i = 0; i < 4; i++) {
			blocks[i].setSize(Vector2f(30.f, 30.f));
			blocks[i].setFillColor(Color::Green);
		}
	}

	void assign(Tetrino* obj) override {
		id = obj->getId();
		rotationstate = obj->getRotationState();
		delete[] coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i].SetCoordinate(obj->getCoord(i).GetX(), obj->getCoord(i).GetY());
		}
		Center = obj->getCenter();
		isactive = obj->getIsActive();
	}


	void rotate(char**& grid) override {
		Center = coords[0];
		rotationstate++;
		if (rotationstate == 4) {
			rotationstate = 0;
		}

		if ((Center.GetX() + 1 < 20) && Center.GetX() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX() + 1][Center.GetY() - 1] == '*' || grid[Center.GetX() + 1][Center.GetY() - 1] == id)
				&& (grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id)
				&& (grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 1) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					coords[3].SetCoordinate(Center.GetX() + 1, Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id)
				&& (grid[Center.GetX() - 1][Center.GetY() - 1] == '*' || grid[Center.GetX() - 1][Center.GetY() - 1] == id)
				&& (grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id)) {
				if (rotationstate == 2) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX() - 1, Center.GetY() - 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() + 1 < 10 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() - 1][Center.GetY() + 1] == '*' || grid[Center.GetX() - 1][Center.GetY() + 1] == id)
				&& (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id)
				&& (grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id)) {
				if (rotationstate == 3) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY() + 1);
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetY() + 1 < 10 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() + 1][Center.GetY() + 1] == '*' || grid[Center.GetX() + 1][Center.GetY() + 1] == id) &&
				(grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id) &&
				(grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 0) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() + 1, Center.GetY() + 1);
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

	}





};

class LBlock :public Tetrino {
public:
	LBlock() {
		id = 'L';
		rotationstate = 0;
		coords = new Coordinate[4];
		Center.SetCoordinate(0, 5);
		coords[0] = Center;
		coords[1].SetCoordinate(0, 4);
		coords[2].SetCoordinate(1, 4);
		coords[3].SetCoordinate(0, 6);
	}

	void assign(Tetrino* obj) override {
		id = obj->getId();
		rotationstate = obj->getRotationState();
		delete[] coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i].SetCoordinate(obj->getCoord(i).GetX(), obj->getCoord(i).GetY());
		}
		Center = obj->getCenter();
		isactive = obj->getIsActive();
	}


	void rotate(char**& grid) override {
		Center = coords[0];
		rotationstate++;
		if (rotationstate == 4) {
			rotationstate = 0;
		}

		if ((Center.GetX() + 1 < 20) && Center.GetX() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX() + 1][Center.GetY() + 1] == '*' || grid[Center.GetX() + 1][Center.GetY() + 1] == id)
				&& (grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id)
				&& (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id)) {
				if (rotationstate == 1) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX() + 1, Center.GetY() + 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)
				&& (grid[Center.GetX() - 1][Center.GetY() + 1] == '*' || grid[Center.GetX() - 1][Center.GetY() + 1] == id)
				&& (grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id)) {
				if (rotationstate == 2) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					coords[2].SetCoordinate(Center.GetX() - 1, Center.GetY() + 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() - 1][Center.GetY() - 1] == '*' || grid[Center.GetX() - 1][Center.GetY() - 1] == id)
				&& (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id)
				&& (grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id)) {
				if (rotationstate == 3) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY() - 1);
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX() - 1, Center.GetY());
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetY() + 1 < 10 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() + 1][Center.GetY() - 1] == '*' || grid[Center.GetX() + 1][Center.GetY() - 1] == id) &&
				(grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX() ][Center.GetY() + 1] == id) &&
				(grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 0) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() + 1, Center.GetY() - 1);
					coords[2].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}
	}
};

class JBlock :public Tetrino {
public:
	JBlock() {
		id = 'J';
		rotationstate = 0;
		coords = new Coordinate[4];
		Center.SetCoordinate(0, 5);
		coords[0] = Center;
		coords[1].SetCoordinate(0, 4);
		coords[2].SetCoordinate(1, 6);
		coords[3].SetCoordinate(0, 6);
	}

	void assign(Tetrino* obj) override {
		id = obj->getId();
		rotationstate = obj->getRotationState();
		delete[] coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i].SetCoordinate(obj->getCoord(i).GetX(), obj->getCoord(i).GetY());
		}
		Center = obj->getCenter();
		isactive = obj->getIsActive();
	}


	void rotate(char**& grid) override {
		Center = coords[0];
		rotationstate++;
		if (rotationstate == 4) {
			rotationstate = 0;
		}

		if ((Center.GetX() + 1 < 20) && Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0) {
			if ((grid[Center.GetX() + 1][Center.GetY() - 1] == '*' || grid[Center.GetX() + 1][Center.GetY() - 1] == id)
				&& (grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id)
				&& (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id)) {
				if (rotationstate == 1) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY());
					coords[2].SetCoordinate(Center.GetX() + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX() + 1, Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetY() + 1 < 10) {
			if ((grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)
				&& (grid[Center.GetX() - 1][Center.GetY() - 1] == '*' || grid[Center.GetX() - 1][Center.GetY() - 1] == id)
				&& (grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id)) {
				if (rotationstate == 2) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					coords[2].SetCoordinate(Center.GetX() - 1, Center.GetY() - 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetX() - 1 >= 0 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() - 1][Center.GetY() + 1] == '*' || grid[Center.GetX() - 1][Center.GetY() + 1] == id)
				&& (grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id)
				&& (grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == id)) {
				if (rotationstate == 3) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() - 1, Center.GetY() + 1);
					coords[2].SetCoordinate(Center.GetX()  + 1, Center.GetY());
					coords[3].SetCoordinate(Center.GetX()  - 1, Center.GetY());
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}

		if (Center.GetY() + 1 < 10 && Center.GetY() - 1 >= 0 && Center.GetX() + 1 < 20) {
			if ((grid[Center.GetX() + 1][Center.GetY() + 1] == '*' || grid[Center.GetX() + 1][Center.GetY() + 1] == id) &&
				(grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id) &&
				(grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == id)) {
				if (rotationstate == 0) {
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX() + 1, Center.GetY() + 1);
					coords[2].SetCoordinate(Center.GetX(), Center.GetY() + 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}
				}
			}
		}
	}
};

class OBlock :public Tetrino {
public:
	OBlock() {
		id = 'O';
		rotationstate = 0;
		coords = new Coordinate[4];
		Center.SetCoordinate(0, 5);
		coords[0] = Center;
		coords[1].SetCoordinate(0, 4);
		coords[2].SetCoordinate(1, 4);
		coords[3].SetCoordinate(1, 5);
	}

	void assign(Tetrino* obj) override {
		id = obj->getId();
		rotationstate = obj->getRotationState();
		delete[] coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i].SetCoordinate(obj->getCoord(i).GetX(), obj->getCoord(i).GetY());
		}
		Center = obj->getCenter();
		isactive = obj->getIsActive();
	}

	void rotate(char**&) override {};
};

class IBlock :public Tetrino {
public:
	IBlock() {
		id = 'I';
		rotationstate = 0;
		coords = new Coordinate[4];
		Center.SetCoordinate(0, 4);
		coords[0] = Center;
		coords[1].SetCoordinate(0, 3);
		coords[2].SetCoordinate(0, 5);
		coords[3].SetCoordinate(0, 6);
	}

	void assign(Tetrino* obj) override {
		id = obj->getId();
		rotationstate = obj->getRotationState();
		delete[] coords;
		coords = new Coordinate[4];
		for (int i = 0; i < 4; i++) {
			coords[i].SetCoordinate(obj->getCoord(i).GetX(), obj->getCoord(i).GetY());
		}
		Center = obj->getCenter();
		isactive = obj->getIsActive();
	}

	void rotate(char**& grid) override {
		Center = coords[0];  // The center block
		rotationstate++;

		if (rotationstate == 2) {
			rotationstate = 0;
		}
		if (Center.GetX() + 1 < 20 && Center.GetX() - 1 >= 0 && Center.GetX() + 2 < 20) {
			if ((grid[Center.GetX() + 1][Center.GetY()] == '*' || grid[Center.GetX() + 1][Center.GetY()] == id) &&
				(grid[Center.GetX() - 1][Center.GetY()] == '*' || grid[Center.GetX() - 1][Center.GetY()] == '*') &&
				(grid[Center.GetX() + 2][Center.GetY()] == '*' || grid[Center.GetX() + 2][Center.GetY()] == '*')) {
				if(rotationstate == 1){

					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
				coords[1].SetCoordinate(Center.GetX() + 1, Center.GetY());
				coords[2].SetCoordinate(Center.GetX() - 1, Center.GetY());
				coords[3].SetCoordinate(Center.GetX() + 2, Center.GetY());
				for (int i = 0; i < 4; i++) {
					grid[coords[i].GetX()][coords[i].GetY()] = id;
				}

				}
			}
		}

		if (Center.GetY() + 1 < 10 && Center.GetY() - 1 >= 0 && Center.GetY() + 2 < 10) {
			if ((grid[Center.GetX()][Center.GetY() + 1] == '*' || grid[Center.GetX()][Center.GetY() + 1] == id) &&
				(grid[Center.GetX()][Center.GetY() - 1] == '*' || grid[Center.GetX()][Center.GetY() - 1] == '*') &&
				(grid[Center.GetX()][Center.GetY() + 2] == '*' || grid[Center.GetX()][Center.GetY() + 2] == '*')) {
				if (rotationstate == 0) {

					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = '*';
					}
					coords[1].SetCoordinate(Center.GetX(), Center.GetY() + 1) ;
					coords[2].SetCoordinate(Center.GetX(), Center.GetY() - 1);
					coords[3].SetCoordinate(Center.GetX(), Center.GetY() + 2);
					for (int i = 0; i < 4; i++) {
						grid[coords[i].GetX()][coords[i].GetY()] = id;
					}

				}
			}
		}




	}
};