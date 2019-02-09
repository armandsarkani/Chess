# Makefile for Chesster, EECS22L Winter 2019
# Author: Marvis Nguyen
# Modified by: Marvis Nguyen

GTKINC	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --cflags gtk+-2.0`
GTKLIBS	= `PKG_CONFIG_PATH=/usr/share/pkgconfig pkg-config --libs gtk+-2.0`

INC	= $(GTKINC)
LIBS	= $(GTKLIBS)

OPTS = -g
CC = gcc
DEBUG = -g -DDEBUG
CFLAGS = -ansi -Wall -c -std=c99
LFLAGS = -Wall

ASCII: bin/Chess clean

GUI: bin/GTK_chess


bin/Chess: bin/Board.o bin/Pieces.o bin/backupAI.o bin/Movegen.o bin/Conditions.o bin/AI.o bin/Evaluate.o
	$(CC) $(LFLAGS) bin/Board.o bin/Pieces.o bin/backupAI.o bin/Movegen.o bin/Conditions.o bin/AI.o bin/Evaluate.o -o bin/Chess

bin/Board.o: src/Board.c src/Board.h src/Pieces.h src/backupAI.h src/Movegen.h src/Conditions.h
	$(CC) $(CFLAGS) src/Board.c -o bin/Board.o

bin/Pieces.o: src/Pieces.c src/Pieces.h src/Board.h src/Conditions.h
	$(CC) $(CFLAGS) src/Pieces.c -o bin/Pieces.o

bin/backupAI.o: src/backupAI.c src/backupAI.h src/Pieces.h src/Board.h src/Movegen.h src/Conditions.h
	$(CC) $(CFLAGS) src/backupAI.c -o bin/backupAI.o

bin/AI.o: src/AI.c src/AI.h  src/Board.h src/Pieces.h src/Movegen.h src/Evaluate.h src/Conditions.h
	$(CC) $(CFLAGS) src/AI.c -o bin/AI.o

bin/Evaluate.o: src/Evaluate.c src/Evaluate.h src/Board.h src/Pieces.h src/Movegen.h
	$(CC) $(CFLAGS) src/Evaluate.c -o bin/Evaluate.o

bin/Movegen.o: src/Movegen.c src/Movegen.h src/Pieces.h src/Board.h src/Conditions.h
	$(CC) $(CFLAGS) src/Movegen.c -o bin/Movegen.o

bin/Conditions.o: src/Conditions.c src/Conditions.h src/Board.h src/Pieces.h
	$(CC) $(CFLAGS) src/Conditions.c -o bin/Conditions.o

bin/GTK_chess.o: src/GTK_chess.c src/GTK_chess.h
	$(CC) $(CFLAGS) src/GTK_chess.c $(INC) $(OPTS) -o bin/GTK_chess.o

bin/GTK_chess: bin/GTK_chess.o
	$(CC) $(LFLAGS) bin/GTK_chess.o $(LIBS) $(OPTS) -o bin/GTK_chess

clean:
	rm -f bin/*.o $(GUI)

