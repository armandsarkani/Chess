#ifndef Board_h
#define Board_h

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


typedef struct Player PLAYER;
typedef struct Piece PIECE;
typedef struct Boards BOARDS;

typedef enum PieceName {Pawn1, Pawn2, Pawn3, Pawn4, Pawn5, Pawn6, Pawn7, Pawn8, Rook1, Rook2, Bishop1, Bishop2, Knight1, Knight2, Queen, King} pieces;

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
    int value; // AI
};

struct Boards{
	PLAYER *player;
	PIECE *pieceboard[8][8];
};

void InitializeBoard(PLAYER *p1, PLAYER *p2, BOARDS *boards);
void DrawBoard(void);
void MakeMove(PLAYER *p, PLAYER *opponent, BOARDS *boards);
PIECE *CreatePiece(int r, int c, char piece, char color, PLAYER *player);
void MovePiece(PIECE *piece, int newr, int newc, BOARDS *boards);
int AlphatoNum(char alpha);
char NumtoAlpha(int num);
PIECE *CheckPiece(PLAYER *p, int r, int c);
int FindEmptySpace(int r, int c);
BOARDS *CreateBoards(void);
PIECE *FindPiece(BOARDS *boards, int r, int c);
void PieceInfo(PIECE *piece);
void CapturePiece(PIECE *piece);

#endif /* Board_h */
