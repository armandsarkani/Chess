#include "Pieces.h"

int CallPiece(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    char piecetype = piece->piecetype;
    switch(piecetype)
    {
        case 'P':
            return(MovePawn(opponent, piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'R':
            return(MoveRook(opponent, piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'N':
            return(MoveKnight(opponent, piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'K':
            return(MoveKing(opponent, piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'Q':
            return(MoveQueen(opponent, piece, src_row, src_col, dest_row, dest_col));
            break;
        case 'B':
            return(MoveBishop(opponent, piece, src_row, src_col, dest_row, dest_col));
            break;
    }
    return 1;
}

int MovePawn(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1) // moving pawn to empty space
    {
        if(piece->player->color == 'w')
        {
            if((piece->value == 2) && (src_col == dest_col) && ((dest_row == src_row + 1) || (dest_row == src_row + 2)))
            {
                if(dest_row == src_row + 2 && (CheckPiece(piece->player, src_row+1, src_col) == NULL) && (CheckPiece(opponent, src_row+1, src_col) == NULL))
                {
                    piece->value = 1;
                    return 0;
                }
                else if(dest_row == src_row + 1)
                {
                    piece->value = 1;
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else if((piece->value == 1) && (src_col == dest_col) && (dest_row == src_row + 1))
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            if((piece->value == 2) && (src_col == dest_col) && ((src_row == dest_row + 1) || (src_row == dest_row + 2)))
            {
                if(src_row == dest_row + 2 && (CheckPiece(piece->player, src_row -1, src_col) == NULL) && (CheckPiece(opponent, src_row -1, src_col) == NULL))
                {
                    piece->value = 1;
                    return 0;
                }
                else if(src_row == dest_row + 1)
                {
                    piece->value = 1;
                    return 0;
                }
                else
                {
                    return 1;
                }
            }
            else if((piece->value == 1) && (src_col == dest_col) && (src_row == dest_row + 1))
            {
                return 0;
            }
            else
            {
                return 1;
            }
               
        }
    }
    else if(CheckPiece(piece->player, dest_row, dest_col) != NULL) // moving pawn to a space with your own piece
    {
        return 1;
        
    }
    else // otherwise must be moving to a space with a different player's piece (a capture)
    {
        if(piece->player->color == 'w')
        {
            if(((dest_col == src_col + 1) || (dest_col == src_col - 1)) && (dest_row = src_row + 1))
            {
                PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                CapturePiece(opponentpiece);
                return 2;
            }
            else
            {
                return 1;
            }
        }
        else
        {
            if(((dest_col == src_col - 1) || (dest_col == src_col + 1)) && (dest_row = src_row - 1))
            {
                PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                CapturePiece(opponentpiece);
                return 2;
            }
            else
            {
                return 1;
            }
        }
    }
}
int MoveRook(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1 || CheckPiece(opponent, dest_row, dest_col) != NULL) // moving rook to empty space or a capture space
    {
        if(src_row == dest_row && src_col != dest_col) // horizontal
        {
            if(src_col < dest_col)
            {
                for(int i = src_col + 1; i < dest_col; i++)
                {
                    if(FindEmptySpace(src_row, i) == 0)
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
            if(src_col > dest_col)
            {
                for(int i = src_col - 1; i > dest_col; i--)
                {
                    if(FindEmptySpace(src_row, i) == 0)
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
        }
        else if(src_row != dest_row && src_col == dest_col) // vertical
        {
            if(src_row < dest_row)
            {
                for(int i = src_row + 1; i < dest_row; i++)
                {
                    if(FindEmptySpace(i, src_col) == 0)
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
            if(src_row > dest_row)
            {
                for(int i = src_row - 1; i > dest_row; i--)
                {
                    if(FindEmptySpace(i, src_col) == 0)
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
        }
        else
        {
            return 1;
        }
        return 0;
    }
    else // moving pawn to a space with your own piece
    {
        return 1;
        
    }
}
int MoveKnight(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1 || CheckPiece(opponent, dest_row, dest_col) != NULL) // moving knight to empty space or a capture space
    {
        if(((dest_row == src_row+1) && (dest_col == src_col+2)) || ((dest_row == src_row+2) && (dest_col == src_col+1)) || ((dest_row == src_row+2) && (dest_col == src_col-1)) || ((dest_row == src_row+1) && (dest_col == src_col-2)) || ((dest_row == src_row-1) && (dest_col == src_col-2)) || ((dest_row == src_row-2) && (dest_col == src_col-1)) || ((dest_row == src_row-2) && (dest_col == src_col+1)) || ((dest_row == src_row-1) && (dest_col == src_col+2)))
        {
            return 0;
        }
        return 1;
    }
    else // moving pawn to a space with your own piece
    {
        return 1;
        
    }
}
int MoveBishop(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1 || CheckPiece(opponent, dest_row, dest_col) != NULL) // moving bishop to empty space or a capture space
    {
        int dRow = 0; // change in row value
        int dCol = 0; // change in column value
        if((dest_row < src_row) && (dest_col < src_col)) // moving to bottom left
        {
            dRow = src_row - dest_row;
            dCol = src_col - dest_col;
            if(dRow == dCol)
            {
                for(int i = 1; i < dRow; i++)
                {
                    if(FindEmptySpace(src_row-i, src_col-i) == 0) // if there is a piece in the way
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
            return 1;
        }
        else if((dest_row < src_row) && (dest_col > src_col)) // moving to bottom right
        {
            dRow = src_row - dest_row;
            dCol = dest_col - src_col;
            if(dRow == dCol)
            {
                for(int i = 1; i < dRow; i++)
                {
                    if(FindEmptySpace(src_row-i, src_col+i) == 0) // if there is a piece in the way
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
            return 1;
        }
        else if((dest_row > src_row) && (dest_col < src_col)) // moving to top left
        {
            dRow = dest_row - src_row;
            dCol = src_col - dest_col;
            if(dRow == dCol)
            {
                for(int i = 1; i < dRow; i++)
                {
                    if(FindEmptySpace(src_row+i, src_col-i) == 0) // if there is a piece in the way
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
            return 1;
        }
        else if((dest_row > src_row) && (dest_col > src_col)) // moving to top right
        {
            dRow = dest_row - src_row;
            dCol = dest_col - src_col;
            if(dRow == dCol)
            {
                for(int i = 1; i < dRow; i++)
                {
                    if(FindEmptySpace(src_row+i, src_col+i) == 0) // if there is a piece in the way
                    {
                        return 1;
                    }
                }
                if(CheckPiece(opponent, dest_row, dest_col) != NULL)
                {
                    PIECE *opponentpiece = CheckPiece(opponent, dest_row, dest_col);
                    CapturePiece(opponentpiece);
                    return 2;
                }
                return 0;
            }
            return 1;
        }
        else
        {
            return 1;
        }
    }
    else // moving pawn to a space with your own piece
    {
        return 1;
        
    }
}
int MoveKing(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if(FindEmptySpace(dest_row, dest_col) == 1 || CheckPiece(opponent, dest_row, dest_col) != NULL) // moving king to empty space or a capture space
    {
        if(((dest_row == src_row+1) && (dest_col == src_col-1)) || ((dest_row == src_row+1) && (dest_col == src_col)) || ((dest_row == src_row+1) && (dest_col == src_col+1)) || ((dest_row == src_row) && (dest_col == src_col-1)) || ((dest_row == src_row) && (dest_col == src_col+1)) || ((dest_row == src_row-1) && (dest_col == src_col-1)) || ((dest_row == src_row-1) && (dest_col == src_col)) || ((dest_row == src_row-1) && (dest_col == src_col+1)))

        {
               return 0;
        }
        return 1;
    }
    else  // moving pawn to a space with your own piece
    {
        return 1;
        
    }
}
int MoveQueen(PLAYER *opponent, PIECE *piece, int src_row, int src_col, int dest_row, int dest_col)
{
    if((MoveRook(opponent, piece, src_row, src_col, dest_row, dest_col) == 0) || (MoveBishop(opponent, piece, src_row, src_col, dest_row, dest_col) == 0))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

