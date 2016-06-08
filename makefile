all: gravilex.o gamestate.o grid.o library.o
	g++ -o Gravilex gravilex.o gamestate.o grid.o library.o
	rm *.o

gravilex.o: gravilex.cpp
	g++ -c gravilex.cpp
	
gamestate.o: gamestate.cpp gamestate.h
	g++ -c gamestate.cpp
	
grid.o: grid.cpp grid.h
	g++ -c grid.cpp
	
library.o: library.cpp library.h
	g++ -c library.cpp
	

