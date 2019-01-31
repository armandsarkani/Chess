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

ASCII: Chess

GUI: GTK_chess

Chess: Board.o Pieces.o backupAI.o Movegen.o
	$(CC) $(LFLAGS) Board.o Pieces.o backupAI.o Movegen.o -o Chess
	
Board.o: Board.c Board.h Pieces.h backupAI.h Movegen.h
	$(CC) $(CFLAGS) Board.c -o Board.o

Pieces.o: Pieces.c Pieces.h Board.h
	$(CC) $(CFLAGS) Pieces.c -o Pieces.o

backupAI.o: backupAI.c backupAI.h Pieces.h Board.h Movegen.h
	$(CC) $(CFLAGS) backupAI.c -o backupAI.o

Movegen.o: Movegen.c Movegen.h Pieces.h Board.h
	$(CC) $(CFLAGS) Movegen.c -o Movegen.o

GTK_chess.o: GTK_chess.c GTK_chess.h
	$(CC) $(CFLAGS) GTK_chess.c $(INC) $(OPTS) -o GTK_chess.o

GTK_chess: GTK_chess.o
	$(CC) $(LFLAGS) GTK_chess.o $(LIBS) $(OPTS) -o GTK_chess

clean:
	rm -f *.o $(GUI)



