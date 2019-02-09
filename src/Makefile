# changed
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


Chess: Board.o Pieces.o backupAI.o Movegen.o Conditions.o AI.o Evaluate.o
	$(CC) $(LFLAGS) Board.o Pieces.o backupAI.o Movegen.o Conditions.o AI.o Evaluate.o -o Chess

Board.o: Board.c Board.h Pieces.h backupAI.h Movegen.h Conditions.h
	$(CC) $(CFLAGS) Board.c -o Board.o

Pieces.o: Pieces.c Pieces.h Board.h Conditions.h
	$(CC) $(CFLAGS) Pieces.c -o Pieces.o

backupAI.o: backupAI.c backupAI.h Pieces.h Board.h Movegen.h Conditions.h
	$(CC) $(CFLAGS) backupAI.c -o backupAI.o

AI.o: AI.c AI.h Board.h Pieces.h Movegen.h Evaluate.h Conditions.h
	$(CC) $(CFLAGS) AI.c -o AI.o

Evaluate.o: Evaluate.c Evaluate.h Board.h Pieces.h Movegen.h
	$(CC) $(CFLAGS) Evaluate.c -o Evaluate.o

Movegen.o: Movegen.c Movegen.h Pieces.h Board.h Conditions.h
	$(CC) $(CFLAGS) Movegen.c -o Movegen.o
Conditions.o: Conditions.c Conditions.h Board.h Pieces.h
	$(CC) $(CFLAGS) Conditions.c -o Conditions.o
GTK_chess.o: GTK_chess.c GTK_chess.h
	$(CC) $(CFLAGS) GTK_chess.c $(INC) $(OPTS) -o GTK_chess.o

GTK_chess: GTK_chess.o
	$(CC) $(LFLAGS) GTK_chess.o $(LIBS) $(OPTS) -o GTK_chess

clean:
	rm -f *.o $(GUI)

