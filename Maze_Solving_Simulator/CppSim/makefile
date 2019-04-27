# Project: Micromouse Maze Simulator
# Makefile created by Matthew Yu

mmsim: Main.o Simulator.o Maze.o Mouse.o Algo.o
	g++ -o mmsim Main.o Simulator.o Maze.o Mouse.o Algo.o
Main.o: Main.cpp Simulator.h
	g++ -c Main.cpp
Simulator.o: Simulator.cpp Simulator.h Maze.h Mouse.h
	g++ -c Simulator.cpp
Maze.o:	Maze.cpp Maze.h Params.h
	g++ -c Maze.cpp
Algo.o: Algo.cpp Algo.h
	g++ -c Algo.cpp
Mouse.o: Mouse.cpp Mouse.h
	g++ -c Mouse.cpp
