#include "cellgrid.h"

using namespace std;

CellGrid::CellGrid(int xs, int ys, vector<bool> born, vector<bool> stayLive, int maxAge){
	xSize = xs;
	ySize = ys;
	this -> born = born;
	this -> stayLive = stayLive;
	//initialize size
	cells = vector<vector<Cell*> >(ySize, vector<Cell*>(xSize, NULL));
	for(int y = 0; y < ySize; y++){
		for(int x = 0; x < xSize; x++){
			cells[y][x] = new Cell(this, maxAge, x, y);//create cell objects
		}
	}
	//connect neighbors, after all cells created
	/*for(vector<Cell*> row : cells){
		for(Cell* c : row){
			c -> addNeighbors(getNeighbors(c));
		}
	}*/
	on = '1';
	off = '0';
	srand(time(NULL));
}

bool CellGrid::simulate(){
	//change toCheck
	toCheck.clear();
	for(Cell* c : liveCells){
		vector<Cell*> next = getNeighbors(c);
		for(Cell* n : next){
			toCheck.insert(n);
		}
		toCheck.insert(c);
	}
	//calculate changes
	for(Cell* c : toCheck){
        c -> getNextState();
    }//apply changes
    for(Cell* c : toCheck){
        c -> update();
    }
	return !liveCells.empty();
}

vector<Cell*> CellGrid::getNeighbors(int x, int y){
	vector<Cell*> give;
	for(int xo = -1; xo <= 1; xo++){
		for(int yo = -1; yo <= 1; yo++){
			if(x + xo >= 0 && x + xo < xSize &&
			y + yo >= 0 && y + yo < ySize &&
			!(xo == 0 && yo == 0)){
				give.push_back(cells[y+yo][x+xo]);
			}
		}
	}
	return give;
}

vector<Cell*> CellGrid::getNeighbors(Cell* c){
	return getNeighbors(c -> xpos, c -> ypos);
}

void CellGrid::randomInit(){
	for(vector<Cell*> row : cells){
		for(Cell* c : row){
			c -> set(rand()%2);
		}
	}
}

int CellGrid::vectorInit(vector<bool>& newState){
	int i = 0;
	//printf("initvecsize = %d\n", newState.size());
	try{
		for(vector<Cell*> row : cells){
			for(Cell* c : row){
				c -> set(newState.at(i++));
			}
		}
	}catch(const std::exception &exc){
		printf("%s\n", exc.what());
		return 1;
	}
	if(i != newState.size()) return 2;
	return 0;
}

void CellGrid::setGraphics(char on, char off){
	this -> on = on;
	this -> off = off;
}

void CellGrid::draw(){
	for(vector<Cell*> row : cells){
		for(Cell* c : row){
			if(*c){
				printf("%c ", on);
			}else{
				printf("%c ", off);
			}
		}
		printf("\n");
	}
}
