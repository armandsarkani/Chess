nclude "Pieces.h" 
#include "Board.h"
#include "movegen.h"


/*Last modified 1/24/19*/
/*Things that need to be added:
 * 	DeleteMoveList
 * 		DeleteMoveEntry
 * 			
 * 				accompanying header file movegen.h
 * 				*/

#include "Pieces.h"
#include "Board.h"

void getmoves(char *org_board[8][8],PLAYER *player, PLAYER *oppenent, MOVELIST *list){
	char *cpy_board;
	PIECE *piece;
	int success; /*if success = 0*/
	int i,j,x,y,a,b;
	for (i = 0; i < 8; i++){/* copies board into a temp board*/
		for (j = 0; j < 8; j++{
			cpy_board[i][j] = org_board[i][j]; /*PLEASE DO NOT CHANGE THIS LINE*/
		/*end for*/
	/*end for*/ 
		}
	}

	for(i = 0; i < 16; i++){
		piece = player->piecelist[i];
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++){
				success = CallPiece(list->board, opponent, piece, piece->r, piece->c, x, y, 0);
				if (success != 1){ /*if CallPiece does not return a failure*/
					MovePiece( list->board,opponent, piece, x, y);/*makes move on cpyboard*/
					AddLegalMoves(list, piece->r, piece->c, x, y, list->board->boardarray);
					for (a = 0; a < 8; a++){
						for (b = 0; b < 8; b++){
							list->board->boardarray[a][b] = cpy_board[a][b]; /*PLEASE DO NOT CHANGE THIS LINE*/
						}
					}
				}
			}	
		}	
		/*end for*/
	}/*end for*/
}

void AddLegalMoves(MOVELIST *list, src_row, src_col, dest_row, dest_col, board[8][8]){
/*Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move*/	
	
	MOVE *new_entry = malloc(sizeof(MOVE));
	assert(new_entry);
	int i,j; 
	if( list->first = NULL){
		list->first = new_entry;
		new_entry->preventry = NULL;
		new_entry->nextentry = NULL;
		
		new_entry->src_row = src_row;
		new_entry->src_col = src_col;
		new_entry->dst_row = dest_row;
		new_entry->dst_col = dest_col;
		new_entry->score = 0;
		
		list->last = new_entry;
		new_entry -> prev_level = list;
	
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				new_entry -> new_board[i][j] = board[i][j];
			}
		}	
	}else{
		list->last->nextentry = new_entry;
		new_entry->preventry = list->last;
		list->last= new_entry;

		new_entry->src_row = src_row;
		new_entry->src_col = src_col;
		new_entry->dst_row = dest_row;
		new_entry->dst_col = dest_col;
		new_entry->score = 0;
		
		new_entry -> prev_level = list;
	
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				new_entry -> new_board[i][j] = board[i][j];
			}
		}
	}
}

/*Cretes a move*/
MOVE *CreateMove(void){
	move = malloc(sizeof(MOVE));
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
		DeleteMoveList(next_level);
	}else {
		free(entry);
	}
}

/*Deletes a board*/
void DeleteBoard(BOARD *board){
	assert(board);
	DeletePlayer(white);
	DeletePlayer(black);
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





