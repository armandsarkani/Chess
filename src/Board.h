//  Board.h
//  Chess
//
//  First release was created by Armand Ahadi-Sarkani on 1/16/19.
//  Copyright © 2019 Armand Ahadi-Sarkani. All rights reserved.
//

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>


typedef struct Player PLAYER;
typedef struct Piece PIECE;
typedef struct Board BOARD;

typedef enum PieceName {Pawn1, Pawn2, Pawn3, Pawn4, Pawn5, Pawn6, Pawn7, Pawn8, Rook1, Rook2, Bishop1, Bishop2, Knight1, Knight2, Queen, King} pieces;

struct Board {
    PLAYER *white;
    PLAYER *black;
    char *boardarray[8][8];
};

struct Player {
    char type;  //type of player: human ('h') or AI ('a')
    char color;
    PIECE *piecelist[16];
};


struct Piece{
    PLAYER *player;
    char piecetype;
    int r;
    int c;
    int value; 
};

void InitializeBoard(BOARD *global);
void DrawBoard(BOARD *board);
void MakeMove(BOARD *board, PLAYER *p, PLAYER *opponent);
PIECE *CreatePiece(BOARD *board, int r, int c, char piece, char color, PLAYER *player);
int MovePiece(BOARD *board, PLAYER *opponent, PIECE *piece, int newr, int newc);
int AlphatoNum(char alpha);
PIECE *CheckPiece(PLAYER *p, int r, int c);
int FindEmptySpace(BOARD *board, int r, int c);
int Check(BOARD *board, PLAYER *player, PLAYER *opponent, int king_row, int king_col);
void CapturePiece(BOARD *board, PIECE *piece);
BOARD *CreateBoard(PLAYER *human, PLAYER *AI, char *boardarray[8][8]);
FILE *Log(char color, char piecetype, char destcol, int destrow, int isCaptured);


#endif /* Board_h */
