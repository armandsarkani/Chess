#include "Movegen.h"


/*Last modified 1/24/19*/
/*Things that need to be added:
 * 	DeleteMoveList
 * 		DeleteMoveEntry
 * 			
 * 				accompanying header file movegen.h
 * 				*/


void getmoves(char *org_board[8][8], BOARD *board, PLAYER *player, PLAYER *opponent, MOVELIST *list){
	int success; /*if success = 0*/
    int move;
	int i,x,y,j;
    PIECE *opponentcapture = NULL;
    char *piecetag = NULL;
    char *capturedpiece = NULL;
    int IsCaptured = 0;
    int opponent_r = 0, opponent_c = 0, opponent_value = 0;
    char *cpy_board[8][8];
    for (i = 0; i < 8; i++){/* copies board into a temp board*/
        for (j = 0; j < 8; j++){
            cpy_board[i][j] = org_board[i][j]; /*PLEASE DO NOT CHANGE THIS LINE*/
            /*end for*/
            /*end for*/
        }
    }
	for(i = Pawn1; i <= King; i++)
    {
		PIECE *piece = player->piecelist[i];
        if(piece->r == 9 || piece->c == 9)
        {
            continue;
        }
        int orig_pieceR = piece->r;
        int orig_pieceC = piece->c;
        int orig_piecevalue = piece->value;
        char *orig_piecetag = board->boardarray[orig_pieceR][orig_pieceC];
        for (x = 0; x < 8; x++)
        {
			for (y = 0; y < 8; y++)
            {
                success = CallPiece(board, opponent, piece, (piece->r)+1, (piece->c)+1, x+1, y+1, 0);
				if (success != 1) /*if CallPiece does not return a failure*/
                {
                    if(success == 2)
                    {
                        opponentcapture = CheckPiece(opponent, x+1, y+1);
                        opponent_r = opponentcapture->r;
                        opponent_c = opponentcapture->c;
                        opponent_value = opponentcapture->value;
                        piecetag = board->boardarray[opponent_r][opponent_c];
                     }
                    char *originaldesttag = board->boardarray[x][y];
					move = MovePiece(board, opponent, piece, x, y);/*makes move on cpyboard*/
                    if(move == 1) // if check
                    {
                        if(success == 2)
                        {
                            UndoCapture(board, opponentcapture, opponent_r, opponent_c, opponent_value, piecetag);
                        }
                        if(piece->value == 1 && orig_piecevalue == 2)
                        {
                            piece->value = 2;
                        }
                        continue;
                    }
                    else
                    {
                        if(success == 2)
                        {
                            IsCaptured = 1;
                            capturedpiece = cpy_board[opponentcapture->r][opponentcapture->c];
                        }
                        cpy_board[x][y] = orig_piecetag;
                        cpy_board[orig_pieceR][orig_pieceC] = "  ";
                        board->boardarray[x][y] = originaldesttag;
                        board->boardarray[orig_pieceR][orig_pieceC] = orig_piecetag;
                        piece->r = orig_pieceR;
                        piece->c = orig_pieceC;
                        AddLegalMoves(list, piece->r, piece->c, x, y, board, IsCaptured, piece, opponentcapture, cpy_board);
                        if(IsCaptured == 1)
                        {
                            cpy_board[x][y] = capturedpiece;
                            cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                        }
                        else
                        {
                            cpy_board[x][y] = "  ";
                            cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                        }
                        
                    }
				}
                continue;
			}
		}	
		/*end for*/
	}/*end for*/
}

void AddLegalMoves(MOVELIST *list, int src_row, int src_col, int dest_row, int dest_col, BOARD *board, int IsCaptured, PIECE *piece, PIECE *opponentcapture, char *cpy_board[8][8]){
/*Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move*/	
	
	MOVE *new_entry = malloc(sizeof(MOVE));
	assert(new_entry);
	if(list->first == NULL){
		list->first = new_entry;
		new_entry->preventry = NULL;
		new_entry->nextentry = NULL;
		new_entry->src_row = src_row;
		new_entry->src_col = src_col;
		new_entry->dst_row = dest_row;
		new_entry->dst_col = dest_col;
        new_entry->IsCaptured = IsCaptured;
        new_entry->piece = piece;
        new_entry->opponentcapture = opponentcapture;
		new_entry->score = 0;
        new_entry->board = board;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                new_entry->new_board[i][j] = cpy_board[i][j];
            }
        }
		list->last = new_entry;
		new_entry -> prev_level = list;
        new_entry->next_level = NULL;
	
	}else{
		list->last->nextentry = new_entry;
		new_entry->preventry = list->last;
        new_entry->nextentry = NULL;
		list->last= new_entry;

		new_entry->src_row = src_row;
		new_entry->src_col = src_col;
		new_entry->dst_row = dest_row;
		new_entry->dst_col = dest_col;
        new_entry->IsCaptured = IsCaptured;
        new_entry->piece = piece;
        new_entry->opponentcapture = opponentcapture;
		new_entry->score = 0;
        new_entry->board = board;
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                new_entry->new_board[i][j] = cpy_board[i][j];
            }
        }
		new_entry->prev_level = list;
        new_entry->next_level = NULL;

	
	}
    list->length++;
}

/*Cretes a move*/
MOVE *CreateMove(void){
	MOVE *move = malloc(sizeof(MOVE));
	return move;
}

/*Creates a movelist*/
MOVELIST *NewMoveList(void){
	MOVELIST *l;
	l = malloc(sizeof(MOVELIST));
	if (!l)
	{
		perror("\n Out of Memory! Aborting...");
		exit(10);
	}
	l->first = NULL;
	l->last = NULL;
	return l;
}

/*Deletes list of all possible legal moves: frees memory*/
void DeleteMoveList(MOVELIST *list){
	assert(list);
	MOVE *next;
	MOVE *temp;
	temp = list->first;
	while(temp) {
		next = temp->nextentry;
		DeleteMoveEntry(temp);
		temp = next;
	}
	free(list);
}

/*Deletes a single move entry within the movelist*/
void DeleteMoveEntry(MOVE *entry){
	assert(entry);
	if (entry->next_level != NULL){
		DeleteMoveList(entry->next_level);
	}else {
		free(entry);
	}
}

/*Deletes a board*/
void DeleteBoard(BOARD *board){
	assert(board);
	DeletePlayer(board->white);
	DeletePlayer(board->black);
	free(board);
}

/*Deletes a player*/
void DeletePlayer(PLAYER *entry){
	assert(entry);
	for(int i = 0; i < 16; i++){
		DeletePiece(entry->piecelist[i]);
	} /*for end*/
	free(entry);
}

/*Deletes a piece*/
void DeletePiece(PIECE *piece){
	assert(piece);
	free(piece);
}





