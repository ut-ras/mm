# Project: Micromouse Maze Simulator
# Makefile created by Matthew Yu

mmsim: Main.o Simulator.o Maze.o Mouse.o Algorithm.o
	g++ -o mmsim Main.o Simulator.o Maze.o Mouse.o Algorithm.o
Main.o: Main.cpp Simulator.h
	g++ -c Main.cpp
Simulator.o: Simulator.cpp Simulator.h Maze.h Mouse.h Algorithm.h
	g++ -c Simulator.cpp
Mouse.o: Mouse.cpp Mouse.h Maze.h
	g++ -c Mouse.cpp
Maze.o: Maze.cpp Maze.h Params.h
	g++ -c Maze.cpp
Algorithm.o: Algorithm.cpp Algorithm.h
	g++ -c Algorithm.cpp
