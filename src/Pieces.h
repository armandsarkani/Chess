//  Pieces.h
//  Chess
//
//  First release was created by Armand Ahadi-Sarkani on 1/18/19.
//  Copyright © 2019 Armand Ahadi-Sarkani. All rights reserved.
//

#ifndef Pieces_h
#define Pieces_h

#include "Board.h"


int CallPiece(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MovePawn(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveRook(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveBishop(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveQueen(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveKnight(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveKing(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);

#endif /* Pieces_h */
