#ifndef CELLLIFE_H
#define CELLLIFE_H

#include <vector>
#include <stdlib.h>

using std::vector;

class CellGrid;

class Cell{
	private:
	CellGrid* parent;
	int age, maxAge;
	//vector<Cell*> neighbors;
	//bool alreadyChecked;//if nextState has been changed since the last time update ran
	bool nextState;
	
	public:
	int xpos, ypos;
	bool state;
	
	Cell(CellGrid* myParent, int maxAge, int x, int y);
	//change state to nextState
	void update();
	//populate list of neighbors
	//void addNeighbors(vector<Cell*> newNeigh);
	//return number of live neighbors
	int numNeighbors();
	//determine if i will be alive next generation
	void getNextState();
	//return if alive
	explicit operator bool() const;
	
	//set manually
	void set(bool what);
	//set position
	void setPosition(int x, int y);
};

#endif
