#Makefile for Chesster, EECS22L Winter 2019
#Author: Marvis Nguyen
#Modified by: Marvis Nguyen

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

OPTS = -g
CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -ansi -Wall -c -std=c99
LFLAGS = -Wall

all: Board

GUI: GTK_chess

Board: Board.o Pieces.o
	$(CC) $(LFLAGS) Board.o Pieces.o -o Board
	
Board.o: Board.c Board.h Pieces.h
	$(CC) $(CFLAGS) Board.c -o Board.o

Pieces.o: Pieces.c Pieces.h
	$(CC) $(CFLAGS) Pieces.c -o Pieces.o

GTK_chess.o: GTK_chess.c GTK_chess.h
	$(CC) $(CFLAGS) GTK_chess.c $(INC) $(OPTS) -o GTK_chess.o

GTK_chess: GTK_chess.o
	$(CC) $(LFLAGS) GTK_chess.o $(LIBS) $(OPTS) -o GTK_chess

clean:
	rm -f *.o $(GUI)



