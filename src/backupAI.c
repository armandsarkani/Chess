//  AI.c
//  //  Chess
//  //
//  //  Created by Jada Berenguer
//  //  Last modified on 1/28/19.
//  //  Copyright © 2019 Jada Berenguer. All rights reserved.
//  //  

#include "Pieces.h"
#include "Movegen.h"
#include "Evaluate.h"

/*AI function for now will just move based on capture pieces*/
/*AI function will pass in: a board, a player, and an opponent)*/
/*it will scan the board until it hits a piece*/
/*once it hits a piece, it will get list of all possible moves for that piece*/
/*once it gets all possible moves, use callpiece and see if it returns a 2 (capture)*/
/*see which piece it captures, assign a score, keep score and move in variables*/
/*if no captures possible, move first piece it sees in array*/
/*random function: choose a random number, loop through that random number x times
 * and choose that move from getmoves*/

void AI(board[8][8], PLAYER *player, PLAYER *opponent){
	
	PIECE *piece;
	PIECE *piececaptured;
	MOVELIST *movelist; 
	MOVE *capturemove;
	list = NewMoveList(); /*allocate mem*/
	int value; 
	int score = 0;
	MOVE *tempmove;
	for (int x = 0; x < 8; x++) {/*x: dummy variable for coordinate tracking on chess board*/
		for (int y = 0; y < 8; y++){/*y: dummy variable for coordinate tracking on chess board*/
			piece = CheckPiece(player, x, y);
			if(piece != NULL){
				getmoves(board, player, oppenent, movelist); 
				tempmove = movelist -> first;
				while (tempmove != NULL) {
					for(int i = 0; i < 8; i++){
						for (int j = 0; j < 8; j++){
							value = CallPiece(board, opponent, piece, x, y, i, j, 1);
							if(value == 2) {
								piececaptured = CheckPiece(opponent, i, j);
								score = score + (piececaptured -> value);
								capturemove = tempmove; 
							}/*if end*/
							tempmove = tempmove->nextentry;
						}/*for end*/
					}/*for end*/
					if(value != 2) { /*if no pieces can capture*/
						/*generate a random move*/
						srand(time(0));
						/*generate a random move or other type of move*/
						capturemove = movelist->first;
						int randnum = rand();
						for(int a = 0; a < randnum; a++){
							capturemove = capturemove->nextentry;
						} /*for end*/
					} /*if end*/
				}/*while end*/
				return capturemove; /*at the end of the while loop it will return the highest valued capture move*/
			}/*if end*/ 
		}/*for end*/
	}/*for end*/
}/*EOF*/
