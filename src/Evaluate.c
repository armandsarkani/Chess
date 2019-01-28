nclude "evaluate.h"

int score_move(MOVE *move, PLAYER *opponent){
	
}

int CheckKillerMoves(MOVE *move, PLAYER* opponent){
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
						if (success == 2){ /*if AI_piece does not return a failure*/
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
}
}

void CheckCaptureMoves(MOVE *move, PIECE *piece, PLAYER* opponent){
	int src_row = move -> src_row;
	int src_col = move -> src_col
	int dst_row = move -> dst_row;
	int dst_col = move -> dst_col;
	int result;
	
	BOARD *old_board = move->prev_level->board;
	BOARD *new_board = move->new_board;
	
	PIECE *piececaptured; 
	
	/*make the move using CallPiece*/
	result = CallPiece(piece, src_row, src_col, dst_row, dst_col);
		if(result == 2) { /*see if the piece captures another piece*/
			piececaptured = CheckPiece(opponent, dst_row, dst_col); /*find out what piece it captured*/
			move -> score = score + (piececaptured -> value); /*add the value to the score*/
		}/*if end*/
		/*TO LOOK AHEAD AFTER A PIECE CAPTURES:*/
		/*scan new_board in the passed in move*/
		/*once not null use checkpiece to find out which piece it is*/
		/*get legal moves of that piece (have to edit the for loops and stuff below)*/
		for (int i = 0; i < 8; i++){/* scans board of pieces, once it reaches a piece, checks if piece is AI controlled, then makes move on temp board 
		i: dummy variable for coordinate tracking on chess board*/
			for (int j = 0; j < 8; j++){ /*j: dummy variable for coordinate tracking on chess board*/
				if(move -> new_board[i][j] != NULL){
					if(list->board->white->type == 'a'){
						piece = CheckPiece(list->board->white, i, j);
					} else{
						piece = CheckPiece(list->board->black, i, j);
					}
				if(piece != NULL){
					for (x = 0; x < 8; x++) {/*x: dummy variable for coordinate tracking on chess board*/
						for (y = 0; y < 8; y++){/*y: dummy variable for coordinate tracking on chess board*/
						success = CallPiece(boardplayer, piece, i, j, x, y);
						if (success == 2){ /*if AI_piece can capture*/
								piececaptured = CheckPiece(opponent, j, x);
								move -> score = score + (piececaptured -> value);
							for (a = 0; a < 8; a++){/*a: dummy variable for coordinate tracking on chess board*/
								for (b = 0; b < 8; b++){ /*b: : dummy variable for coordinate tracking on chess board*/
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
		/*use call piece to see if it returns a 2*/
		/*add to score*/
		for (int i = 0; i < 16; i++){
			for (int j = 0; j < 8; j++){
				for (int x = 0; x< 8; x++){
					result = CallPiece(piece, new_board->piecelist[i]->r, piecelist[i]->c, j, x);
					if(result == 2) {
						piececaptured = CheckPiece(opponent, j, x);
						move -> score = score + (piececaptured -> value);
					} /*if end*/
				} /*for end*/
			}/*for end*/
		}/*for end*/
} /*EOF*/
	

int EvaluatePositon(MOVE *move, PIECE *piece){
	
}
