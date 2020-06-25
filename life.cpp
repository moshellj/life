#include "cellgrid.h"
#include "cell.h"
#include <stdio.h>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <string.h>

#define XSIZE 20
#define YSIZE 20
#define DONT_AGE 0

using namespace std;

int main(int argc, char** argv){
	vector<bool>      bornRule{0,0,0,1,0,0,0,0,0};
	vector<bool> stayAliveRule{0,0,1,1,0,0,0,0,0};
	CellGrid board(XSIZE, YSIZE, bornRule, stayAliveRule, 10);
	board.setGraphics('X', '-');
	
	//initialization
	if(argc == 1){//random init
		board.randomInit();
	}else if(argc == 3 && strcmp(argv[1], "-f") == 0){
		//file init
		ifstream text;
		vector<bool> state(XSIZE*YSIZE, 0);
		text.open(argv[2]);
		if(text.is_open()){
			//reading
			char next;
			int i = 0;
			while(text >> next){
				state[i++] = (next != '0');
			}
			if(board.vectorInit(state)){//format error
				printf("Input file is wrong size.\n");
				return 3;
			}
			text.close();
		}else{//file error
			printf("Could not open file \"%s\".\n", argv[2]);
			return 2;
		}
	}else{//error
		printf("Bad command line arguments. %d, '%s'\n", argc, argv[1]);
		return 1;
	}
	
	/*debug for(int x = 0; x < XSIZE; x++){
		for(int y = 0; y < YSIZE; y++){
			printf("%d, %d: %d\n", x, y, board.cells[y][x] -> numNeighbors());
		}
	}*/
	
	//get time to simulate
	printf("How many generations would you like to simulate?   ");
	
	int maxGen;
	scanf("%d", &maxGen);
	
	//simulate
	int usleeptime = 250000;
	bool boardLive;
	for(int gen = 0; gen <= maxGen; gen++){
		printf("Generation %d:\n", gen);
		board.draw();
		printf("\n");
		if(!board.simulate()){//end if empty
			if(usleeptime) usleep(usleeptime);
			printf("Generation %d: Empty. Ending early.\n", gen+1);
			board.draw();
			printf("\n");
			break;
		}
		
		//debug
		/*printf("Checked:\n");
		for(Cell* c : board.toCheck){
			printf("%d, %d\n", c -> xpos, c -> ypos);
		}*/
		
		if(usleeptime) usleep(usleeptime);//sleep if thou must
	}
	//board.draw();
}













