#pragma once
#include <iostream>
#include "Tile.h"

using namespace std;

class Board
{
private:
	int rows;
	int cols;
	int mineCnt;
	Tile** grid;
public:
	Board();
	Board(int r, int c, int mines);
	//~Board();

	void setRows(int);
	void setCols(int);
	void setMineCnt(int);
	void setGrid(Tile**);

	int getRows()const { return rows; }
	int getCols()const { return cols; }
	int getMineCnt()const { return mineCnt; }
	Tile** getGrid()const { return grid; }

	Tile** getAjacent(int, int);
	void chainReveal(int, int);
};

char digitToChar(int i);