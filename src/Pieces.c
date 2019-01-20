//
//  Pieces.c
//  Chess
//
//  Created by Armand Sarkani on 1/17/19.
//  Copyright © 2019 Armand Sarkani. All rights reserved.
//

#include "Pieces.h"

int CallPiece(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    char piecetype = piece->piecetype;
    switch(piecetype)
    {
        case 'P':
            return(MovePawn(piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'R':
            return(MoveRook(piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'N':
            return(MoveKnight(piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'K':
            return(MoveKing(piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'Q':
            return(MoveQueen(piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'B':
            return(MoveBishop(piece, src_row, src_col, dest_row, dest_col));
            break;
    }
    return 1;
}

int MovePawn(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1) // moving pawn to empty space
    {
        printf("Condition 1");
        return 0;
    }
    else if(CheckPiece(piece->player, dest_row, dest_col) != NULL) // moving pawn to a space with your own piece
    {
        printf("You cannot move to a spot that currently contains your own piece. ");
        return 1;
        
    }
    else // otherwise must be moving to a space with a different player's piece
    {
        printf("Condition 3");
        return 0;
    }
}
int MoveRook(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1) // moving rook to empty space
    {
        printf("Condition 1");
        return 0;
    }
    else if(CheckPiece(piece->player, dest_row, dest_col) != NULL) // moving pawn to a space with your own piece
    {
        printf("You cannot move to a spot that currently contains your own piece. ");
        return 1;
        
    }
    else // otherwise must be moving to a space with a different player's piece
    {
        printf("Condition 3");
        return 0;
    }
}
int MoveKnight(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1) // moving knight to empty space
    {
        printf("Condition 1");
        return 0;
    }
    else if(CheckPiece(piece->player, dest_row, dest_col) != NULL) // moving pawn to a space with your own piece
    {
        printf("You cannot move to a spot that currently contains your own piece. ");
        return 1;
        
    }
    else // otherwise must be moving to a space with a different player's piece
    {
        printf("Condition 3");
        return 0;
    }
}
int MoveBishop(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1) // moving bishop to empty space
    {
        printf("Condition 1");
        return 0;
    }
    else if(CheckPiece(piece->player, dest_row, dest_col) != NULL) // moving pawn to a space with your own piece
    {
        printf("You cannot move to a spot that currently contains your own piece. ");
        return 1;
        
    }
    else // otherwise must be moving to a space with a different player's piece
    {
        printf("Condition 3");
        return 0;
    }
}
int MoveKing(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1) // moving king to empty space
    {
        printf("Condition 1");
        return 0;
    }
    else if(CheckPiece(piece->player, dest_row, dest_col) != NULL) // moving pawn to a space with your own piece
    {
        printf("You cannot move to a spot that currently contains your own piece. ");
        return 1;
        
    }
    else // otherwise must be moving to a space with a different player's piece
    {
        printf("Condition 3");
        return 0;
    }
}
int MoveQueen(PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1) // moving queen to empty space
    {
        printf("Condition 1 \n");
        return 0;
    }
    else if(CheckPiece(piece->player, dest_row, dest_col) != NULL) // moving pawn to a space with your own piece
    {
        printf("You cannot move to a spot that currently contains your own piece. ");
        return 1;
        
    }
    else // otherwise must be moving to a space with a different player's piece
    {
        printf("Condition 3 \n");
        return 0;
    }
}
