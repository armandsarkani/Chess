
/*Last modified 1/24/19*/
/*Things that need to be added:
	DeleteMoveList
	DeleteMoveEntry
	
	accompanying header file movegen.h
*/

#include "Pieces.h"
#include "Board.h"

void getmoves(char *org_board[8][8],PLAYER *player, PLAYER *oppenent, MOVELIST *list){
	char *cpy_board;
	char piece;
	int success; /*if success = 0*/
		
	for loop{/* copies board into a temp board*/
		for loop{
			cpy_board[i][j] = org_board[i][j]; //i = r, j = c
		/*end for*/
	/*end for*/
		}
	}
	for loop{/* scans board of pieces, once it reaches a piece, checks if piece is AI controlled, then makes move on temp board 
		i: dummy variable for coordinate tracking on chess board*/
		for loop{ /*j: dummy variable for coordinate tracking on chess board*/
			if(board!= NULL){	
				piece = CheckPiece(player, i, j);
				if(piece != NULL){

					for loop {/*x: dummy variable for coordinate tracking on chess board*/
						for loop{/*y: dummy variable for coordinate tracking on chess board*/
						success = CallPiece(player, piece, i, j, x, y);
						if (success != 1){ /*if AI_piece does not return a failure*/
							MovePiece(cpy_board[8][8], piece, x, y);/*makes move on cpyboard*/
							AddLegalMoves(list, i, j, x, y, cpy_board[8][8]);
							for loop{/*a: dummy variable for coordinate tracking on chess board*/
								for loop{ /*b: : dummy variable for coordinate tracking on chess board*/
								cpy_board[a][b] = org_board[8][8]; /*resets copyboard for next move*/ 
								}
							}
						}
					}
				}
				}
			
			}
				
			}
		}
	}
					}*/
		/*end for*/
	/*end for*/
}



void AddLegalMoves(MOVELIST *list, src_row, src_col, dest_row, dest_col, board[8][8]){
/*Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move*/	
	
	MOVE *new_entry = malloc(sizeof(MOVE));
	assert(new_entry);

	if( list->first = NULL){
		list->first = new_entry;
		new_entry->preventry = NULL;
		new_entry->nextentry = NULL;
		
		new_entry->src_row = src_row;
		new_entry->src_col = src_col;
		new_entry->dst_row = dest_row;
		new_entry->dst_col = dest_col;
		
		list->last = new_entry;
	
		for loop{
			for loop{
				new_entry -> newboard[i][j] = board[i][j];
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
	
		for loop{
			for loop{
				new_entry -> newboard[i][j] = board[i][j];
			}
		}
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

////Deletes list of all possible legal moves: frees memory
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
////Deletes a single move entry within the movelist
void DeleteMoveEntry(MOVE *entry){
	assert(entry);
	if (entry->next_level != NULL){
		DeleteMoveList(next_level);
	}else {
		free(entry);
	}
}



