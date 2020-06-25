#include "cell.h"
#include "cellgrid.h"

using namespace std;

Cell::Cell(CellGrid* myParent, int maxAge, int x, int y){
	parent = myParent;
	this -> maxAge = maxAge;
	age = 0;
	xpos = x;
	ypos = y;
	nextState = false;
	state = false;
}

void Cell::update(){
	set(nextState);
}

int Cell::numNeighbors(){
	int count = 0;
	vector<Cell*> neighbors = parent -> getNeighbors(this);
	for(Cell* c : neighbors){
		if(*c) count++;
	}
	return count;
}

void Cell::getNextState(){
	age++;
	if(state){//alive
		nextState = parent -> stayLive[numNeighbors()];
		if(maxAge && (age == maxAge)){//age if maxAge > 0
			nextState = false;
		}
	}else{//dead
		nextState = parent -> born[numNeighbors()];
	}
}

Cell::operator bool() const{
	return state;
}

void Cell::set(bool what){
	if(state && !what){//die
		age = 0;
		state = false;
		parent -> liveCells.erase(this);
	}else if(!state && what){//born
		age = 0;
		state = true;
		parent -> liveCells.insert(this);
	}//else do nothing
}

void Cell::setPosition(int x, int y){
	xpos = x; ypos = y;
}
