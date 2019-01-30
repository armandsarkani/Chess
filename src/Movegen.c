nclude "Pieces.h" 
#include "Board.h"
#include "movegen.h"

void getmoves(char *org_board[8][8],PLAYER *player, PLAYER *oppenent, MOVELIST *list){
	char *cpy_board;
	char piece;
	int success; /*if success = 0*/
	int i,j,x,y,a,b;
	for (i = 0; i < 8; i++){/*copies board into a temp board*/
		for (j = 0; j < 8; j++{
			cpy_board[i][j] = org_board[i][j]; //i = r, j = c
		/*end for*/
	/*end for*/ 
	
		}
	}
	for (int i = 0; i < 8; i++) {/* scans board of pieces, once it reaches a piece, checks if piece is AI controlled, then makes move on temp board 
							 i: dummy variable for coordinate tracking on chess board*/
		for (int j = 0; j < 8; j++){ /*j: dummy variable for coordinate tracking on chess board*/
			if(cpy_board != NULL){
					if(list->board->white->type == 'a'){
						piece = CheckPiece(list->board->white, i, j);
					}/*if end*/
					else {
						piece = CheckPiece(list->board->black, i, j);
					}/*if end*/
				if(piece != NULL){
					for (int x = 0; x < 8; x++) {/*x: dummy variable for coordinate tracking on chess board*/
						for (int y = 0; y < 8; y++){/*y: dummy variable for coordinate tracking on chess board*/
						success = CallPiece(boardplayer, piece, i, j, x, y);
						if (success != 1){ /*if AI_piece does not return a failure*/
							MovePiece(cpy_board[8][8] , piece, x, y);/*makes move on cpyboard*/
							AddLegalMoves(list, i, j, x, y, cpy_board[8][8]);
							for (int a = 0; a < 8; a++){/*a: dummy variable for coordinate tracking on chess board*/
								for (int b = 0; b < 8; b++){ /*b: : dummy variable for coordinate tracking on chess board*/
								cpy_board[a][b] = org_board[a][b]; /*resets copyboard for next move*/ 
								}
							}
						}
					}
				}
			
			}
			}
		}
	}

		/*end for*/
	/*end for*/
}



void AddLegalMoves(MOVELIST *list, src_row, src_col, dest_row, dest_col, board[8][8], PLAYER *player, PLAYER *opponent){
/*Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move*/	
	
	MOVE *new_entry = malloc(sizeof(MOVE));
	assert(new_entry);

	if(list->first = NULL){
		list->first = new_entry;
		new_entry->preventry = NULL;
		new_entry->nextentry = NULL;
		
		new_entry->src_row = src_row;
		new_entry->src_col = src_col;
		new_entry->dst_row = dest_row;
		new_entry->dst_col = dest_col;
		
		list->last = new_entry;
		new_entry -> prev_level = list;
	
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				new_entry -> new_board[i][j] = board[i][j];
			}
		}
		
		new_entry -> newboard = CreateBoard(player, opponent, new_entry -> new_board[8][8]);
		
	
	}/*if end*/
	else {
		list->last->nextentry = new_entry;
		new_entry->preventry = list->last;
		list->last= new_entry;

		new_entry->src_row = src_row;
		new_entry->src_col = src_col;
		new_entry->dst_row = dest_row;
		new_entry->dst_col = dest_col;
		
		new_entry -> prev_level = list;
	
		for (i = 0; i < 8; i++){
			for (j = 0; j < 8; j++){
				new_entry -> new_board[i][j] = board[i][j];
			}
		}
		
		new_entry -> newboard = CreateBoard(player, opponent, new_entry -> new_board[8][8]);

	}
}

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

void DeleteBoard(BOARD *board){
	assert(board);
	DeletePlayer(white);
	DeletePlayer(black);
	free(board);
}

void DeletePlayer(PLAYER *entry){
	assert(entry);
	for(int i = 0; i < 16; i++){
		DeletePiece(entry->piecelist[i]);
	} /*for end*/
	free(entry);
}

void DeletePiece(PIECE *piece){
	assert(piece);
	free(piece);
}
 	
