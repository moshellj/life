life: life.o cell.o cellgrid.o
	g++ -o life life.o cell.o cellgrid.o

life.o: life.cpp cell.h cellgrid.h
	g++ -c life.cpp

cell.o: cell.h cellgrid.h

cellGrid.o: cell.h cellgrid.h
