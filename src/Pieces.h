//
//  Pieces.h
//  Chess
//
//  Created by Armand Sarkani on 1/17/19.
//  Copyright © 2019 Armand Sarkani. All rights reserved.
//

#ifndef Pieces_h
#define Pieces_h

#include "Board.h"

int CallPiece(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MovePawn(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveRook(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveBishop(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveQueen(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveKnight(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveKing(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);

#endif /* Pieces_h */
