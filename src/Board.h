//
//  Board.h
//  Chess
//
//  Created by Armand Sarkani on 1/14/19.
//  Copyright © 2019 Armand Sarkani. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player PLAYER;
typedef struct Piece PIECE;

typedef enum PieceName {Pawn1, Pawn2, Pawn3, Pawn4, Pawn5, Pawn6, Pawn7, Pawn8, Rook1, Rook2, Bishop1, Bishop2, Knight1, Knight2, Queen, King} pieces;

struct Player {
    char color;
    int type;  //AI or human
    PIECE *piecelist[16];
};

struct Piece{
    char piece;
    int r;
    int c;
    int value; // AI
};
void DrawBoard(void);
void makeMove(PLAYER *p);
PIECE *CreatePiece(int r, int c, char piece, char color);
void movePiece(PIECE *piece, int newr, int newc);
int AlphatoNum(char alpha);
PIECE *findPiece(PLAYER *p, int r, int c);

#endif /* Board_h */
