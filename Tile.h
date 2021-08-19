#pragma once
#include "State.h"

class Tile
{
private:
	State state;
	char graphic;
	int label;
	bool hidden;
	int x;
	int y;
	bool flagged;
public:
	Tile();
	Tile(State, char);

	void setState(State);
	void setGraphic(char);
	void setLabel(int);
	void setX(int);
	void setY(int);

	State getState()const { return state; }
	char getGraphic()const { return graphic; }
	int getLabel()const { return label; }
	int getX()const { return x; }
	int getY()const { return y; }

	void hide();
	void reveal();
	bool isHidden()const { return hidden; }

	void flag();
	bool isFlagged()const { return flagged; }
};

