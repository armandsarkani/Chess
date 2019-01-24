#Makefile for Chesster, EECS22L Winter 2019
#Author: Marvis Nguyen
#Modified by: Marvis Nguyen


CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -ansi -Wall -c -std=c99
LFLAGS = -Wall

all: Board

Board: Board.o Pieces.o
	$(CC) $(LFLAGS) Board.o Pieces.o -o Board
	
Board.o: Board.c Board.h Pieces.h
	$(CC) $(CFLAGS) Board.c -o Board.o

Pieces.o: Pieces.c Pieces.h
	$(CC) $(CFLAGS) Pieces.c -o Pieces.o
clean:
	rm -f *.o Board



