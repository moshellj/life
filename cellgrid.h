#ifndef CELLGRID_H
#define CELLGRID_H

#include "cell.h"
#include <vector>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <set>
#include <stdexcept>

using std::vector;

class CellGrid{
	public:
	int xSize, ySize;
	//graphics
	char on, off;
	vector<vector<Cell*> > cells;//all cells, in 2d
	std::set<Cell*> toCheck; //Live cells and their neighbors
	
	int maxAge;
	//which states make cells come alive or stay alive
	vector<bool> born, stayLive;
	std::set<Cell*> liveCells;//only living cells
	
	CellGrid(int x, int y, vector<bool> born, vector<bool> stayLive, int maxAge);
	//simulate one generation. returns if any cells are alive at the end.
	bool simulate();
	//get neighbors
	vector<Cell*> getNeighbors(int x, int y);
	vector<Cell*> getNeighbors(Cell* c);
	
	//initialize randomly
    void randomInit();
    //initialize based on a vector of bools. returns nonzero on error.
    int vectorInit(vector<bool>& newState);
	//set on and off state graphics
	void setGraphics(char on, char off);
	
	//print out the board state
	void draw();
};

#endif
