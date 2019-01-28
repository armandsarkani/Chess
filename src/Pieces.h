//  Pieces.h
//  Chess
//
//  First release was created by Armand Ahadi-Sarkani on 1/18/19.
//  Copyright © 2019 Armand Ahadi-Sarkani. All rights reserved.
//

#ifndef Pieces_h
#define Pieces_h

#include "Board.h"


int CallPiece(BOARD *board, PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MovePawn(BOARD *board, PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveRook(BOARD *board, PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveBishop(BOARD *board, PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveQueen(BOARD *board, PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveKnight(BOARD *board, PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);
int MoveKing(BOARD *board, PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col);

#endif /* Pieces_h */
