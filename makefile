all: bqb

bqb: bqb.cpp ball.hpp
	g++ bqb.cpp -o bqb -lsfml-graphics -lsfml-window -lsfml-system

main: main.cpp
	g++ -c main.cpp
	g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

