# Makefile for plagiarismCatcher
# Ben Belov and Matt Yu
# Last edited 12/7/18
unitTest: main.o Node.o Neighbor.o
	gcc -o unitTest main.o Node.o Neighbor.o
main.o: main.c Node.h Neighbor.h
	gcc -c main.c
# Mouse.o: Mouse.c Structs.h Node.h
# 	gcc -c Mouse.c
Node.o: Node.c Structs.h Neighbor.h
	gcc -c Node.c
Neighbor.o: Neighbor.c Neighbor.h
	gcc -c Neighbor.c
