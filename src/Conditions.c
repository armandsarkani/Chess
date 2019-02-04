//  Conditions.c
//  Chesster Team 3

#include "Conditions.h"

int Check(BOARD *board, PLAYER *player, PLAYER *opponent, int king_row, int king_col)
{
    int piecereturn = 0;
    for(int i = Pawn1; i <= King; i++)
    {
        piecereturn = CallPiece(board, opponent, player->piecelist[i], (player->piecelist[i]->r)+1, (player->piecelist[i]->c)+1, king_row, king_col, 0);
        if(piecereturn == 2)
        {
            return 1; // king is in check automatically
        }
    }
    return 0;
}
int Checkmate(BOARD *board, PLAYER *player, PLAYER *opponent)
{
    for(int i = Pawn1; i <= King; i++)
    {
        PIECE *piece = opponent->piecelist[i];
        int originalR = piece->r;
        int originalC = piece->c;
        char *originalpiecetag = board->boardarray[piece->r][piece->c];
        int original_piece_value = piece->value;
        int movereturn = 0;
        PIECE *opponentcapture = NULL;
        int opponent_r = 0;
        int opponent_c = 0;
        int opponent_value = 0;
        char *piecetag = NULL;
        if(piece->value == 0) // captured piece cannot be moved to save the king
        {
            continue;
        }
        for(int j = 0; j < 8; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                int IsLegalMove = CallPiece(board, player, piece, (piece->r)+1, (piece->c)+1, j+1, k+1, 0); // can the opponent make a legal move?
                if(IsLegalMove == 1)
                {
                    continue;
                }
                else // if so, can that legal move get them out of check?
                {
                    char *originaldesttag = board->boardarray[j][k];
                    if(IsLegalMove == 2)
                    {
                        opponentcapture = CheckPiece(player, j+1, k+1);
                        opponent_r = opponentcapture->r;
                        opponent_c = opponentcapture->c;
                        opponent_value = opponentcapture->value;
                        piecetag = board->boardarray[opponent_r][opponent_c];
                    }
                    movereturn = MovePiece(board, player, piece, j, k);
                    if(movereturn == 1) // if the test move made puts/leaves the opponent in check
                    {
                        if(IsLegalMove == 2) // if move is a potential capture move, reset captures and value updates
                        {
                            UndoCapture(board, opponentcapture, opponent_r, opponent_c, opponent_value, piecetag);
                        }
                        if(piece->value == 1 && original_piece_value == 2)
                        {
                            piece->value = 2;
                        }
                    }
                    else
                    {
                        board->boardarray[j][k] = originaldesttag;
                        board->boardarray[originalR][originalC] = originalpiecetag;
                        piece->r = originalR;
                        piece->c = originalC;
                        return 0;
                    }
                    
                }
                
            }
        }
    }
    return 1;
}
int Promotion(BOARD *board, PIECE *piece)
{
    char choice = '\0';
    if(piece->player->type == 'a')
    {
        if(piece->player->color == 'w' &&  piece->r == 7)
        {
            piece->value = 9;
            piece->piecetype = 'Q';
            board->boardarray[piece->r][piece->c] = "wQ";
            return 1;
        }
        else if(piece->player->color == 'b' && piece->r == 0)
        {
            piece->value = 9;
            piece->piecetype = 'Q';
            board->boardarray[piece->r][piece->c] = "bQ";
            return 1;
        }
    }
    if(piece->player->color == 'w')
    {
        if(piece->r == 7)
        {
            printf("Pawn Promotion: Please select a piece to promote this pawn to. Enter Q for queen, N for knight, B for bishop, or R for rook.\n");
            scanf(" %c", &choice);
        }
    }
    else if(piece->player->color == 'b')
    {
        if(piece->r == 0)
        {
            printf("Pawn Promotion: Please select a piece to promote this pawn to. Enter Q for queen, N for knight, B for bishop, or R for rook.\n");
            scanf(" %c", &choice);
        }
    }
    if(choice == 'Q' || choice == 'q')
    {
        piece->value = 9;
        piece->piecetype = 'Q';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wQ";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bQ";
        }
        return 1;
    }
    else if(choice == 'N' || choice == 'n')
    {
        piece->value = 3;
        piece->piecetype = 'N';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wN";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bN";
        }
        return 1;
    }
    else if(choice == 'B' || choice == 'b')
    {
        piece->value = 3;
        piece->piecetype = 'B';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wB";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bB";
        }
        return 1;
    }
    else if(choice == 'R' || choice == 'r')
    {
        piece->value = 5;
        piece->piecetype = 'R';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wR";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bR";
        }
        return 1;
    }
    return 0;
}
void CapturePiece(BOARD *board, PIECE *piece)
{
    if(piece->piecetype != 'K')
    {
        board->boardarray[piece->r][piece->c] = "  ";
        piece->r = 9; // 9 = off board
        piece->c = 9; // 9 = off board
        piece->value = 0;
        piece = NULL;
    }
    
}
void UndoCapture(BOARD *board, PIECE *opponentcapture, int opponent_r, int opponent_c, int opponent_value, char *piecetag)
{
    board->boardarray[opponent_r][opponent_c] = piecetag;
    opponentcapture->r = opponent_r;
    opponentcapture->c = opponent_c;
    opponentcapture->value = opponent_value;
}
int CheckNumberofIllegalMoves(BOARD *board, PLAYER *opponent, PIECE *piece, int row_src, int col_src)
{
    int counter = 0;
    for(int i = 1; i <= 8; i++)
    {
        for(int j = 1; j <= 8; j++)
        {
            if(CallPiece(board, opponent, piece, row_src, col_src, i, j, 0) == 1)
            {
                counter++;
            }
        }
    }
    return counter;
}
int Stalemate(BOARD *board, PLAYER *player, PLAYER *opponent)
{
    if(Check(board, opponent, player, (player->piecelist[King]->r)+1, (player->piecelist[King]->c)+1)== 0)
    {
        if(Checkmate(board, opponent, player) == 1)
        {
            return 1;
        }
    }
    return 0;
}

int FiftyConsec (MOVELIST *movelist){
	MOVE CurrentMove = movelist -> last;
	for (int i = 0; i < 50 ; i++){

		if (CurrentMove -> IsCaptured == 1 || CurrentMove -> piece -> piecetype == 'P'){
			return 0;
		}		
		CurrentMove = CurrentMove -> preventry;
}
		return 1;

}
