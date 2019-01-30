//  //  Last modified on 1/30/19.
//  //  //  Copyright © 2019 Jada Berenguer and Benny Lin. All rights reserved.
//  //  // 
//
//  //  Chess
//  //
//  //  Created by Jada Berenguer and Benny Lin on 1/21/19.
//  //  Copyright © 2019 Jada Berenguer and Benny Lin. All rights reserved.
//  //  
#include "Pieces.h"
#include "Movegen.h"
#include "Evaluate.h"

MOVE *AI(board[8][8], PLAYER *AI, PLAYER *human){
	MOVELIST *list = NewMoveList(); 
	int i;
	int AI_tracker = 1; /*keep track of who's turn it is*/
	
	if ((AI -> color) = 'w'){
		list->board = CreateBoard(AI, human, board[8][8]);
	}else {
		list->board = CreateBoard(human, AI, board[8][8]);
	}
	getmoves(board[8][8], AI, human, list); /*first layer of list created*/
	
	MOVE *temp = NULL; 
	MOVE *bestmove = NULL;
	temp = list -> first;
	
	int bestscore = -INF;
	int alpha = -INF;
	int beta = INF;
	int depth = 9;
	
	while (temp != NULL) { 
		temp->score = NegaMax(depth, temp, alpha, beta, AI_tracker); /*Negamax (recursive func) will return the best score for that move*/
		if ((temp->score) > bestscore){
			bestscore = temp->score;
			bestmove = temp;
		}
		temp = temp->nextentry;
	} /*while end*/
	free((list->board));
	list->board = NULL;
	DeleteMoveList(list);
	return bestmove;
}/*EOF*/

/*Pass in the first layers possible moves*/
int NegaMax(int depth, MOVE *origmove, int alpha, int beta, int AI_tracker){ 
	int movescore = -INF;
	
	origmove->next_level = NewMovelist(); /*create a new Movelist for the next layer*/
	
	PLAYER *white = CreatePlayer((origmove->prevlevel->board->white->color), (origmove->prevlevel->board->white->type));
	PLAYER *black = CreatePlayer((origmove->prevlevel->board->black->color), (origmove->prevlevel->board->black->type));
	
	for (i = 0; i < 16; i++){
			white->piecelist[i]->player = white;
			white->piecelist[i]->piecetype = origmove->prevlevel->board->white->piecelist[i]->piecetype ;
			white->piecelist[i]->c = origmove->prevlevel->board->white->piecelist[i]->c;
			white->piecelist[i]->r = origmove->prevlevel->board->white->piecelist[i]->r;
			white->piecelist[i]->value = origmove->prevlevel->board->white->piecelist[i]->value;
			
			if (((white->piecelist[i]->r) == (origmove->src_row))&&((white->piecelist[i]->c) == origmove->src_col)){
				white->piecelist[i]->r = origmove->dst_row; 
				white->piecelist[i]->c = origmove->dst_col;
				/*Needs to check if it captures a piece and remove that piece from the list*/
			}/*Moves piece in data list*/
			
			black->piecelist[i]->player = black;
			black->piecelist[i]->piecetype = origmove->prevlevel->board->black->piecelist[i]->piecetype ;
			black->piecelist[i]->c = origmove->prevlevel->board->black->piecelist[i]->c;
			black->piecelist[i]->r = origmove->prevlevel->board->black->piecelist[i]->r;
			black->piecelist[i]->value = origmove->prevlevel->board->black->piecelist[i]->value;
			
			if (((black->piecelist[i]->r) == (origmove->src_row))&&((black->piecelist[i]->c) == origmove->src_col)){
				black->piecelist[i]->r = origmove->dst_row; 
				black->piecelist[i]->c = origmove->dst_col;
				/*Needs to check if it captures a piece and remove that piece from the list*/
			}/*Moves Piece in data list*/
	}
	
	origmove->next_level->board = CreateBoard(white, black,origmove->new_board[8][8]); /*set the board of the new layer's Movelist*/ 
	origmove->next_level->prevmove = origmove; /*set the new layer's movelist prevmove to point to the orig move*/
	
	if ((AI_tracker mod 2) == 1){ /*keep track of which player's turn it is down the list*/
		if(origmove->prev_level->board->white->type == 'a'){ 
			PLAYER *player = white;
			PLAYER *opponent = black;
		}
		else {
			PLAYER *player = black;
			PLAYER *opponent = white;
		}
	} else {
		if(origmove->prev_level->board->white->type == 'a'){ 
			PLAYER *opponent = white;
			PLAYER *player = black;
		}
		else {
			PLAYER *opponent = black;
			PLAYER *player = white;
		}		
	}
	
	
	if (depth < 1){
		return scoremove(origmove, player, opponent); /*return scorefromsidePOV*/ /*recursion happens*/
	} /*if end*/
	
	MOVE *temp = NULL; 
	MOVELIST *movelist = origmove->next_level;
	 /*newly created Movelist (line 59) is assigned to the next layer*/
	getmoves(origmove->newboard[8][8], player, opponent, movelist); /*get legal moves for the passed in origmove*/
	temp = movelist -> first; 


	while (temp) { 
		temp->score = -(NegaMax((depth-1), temp, -beta, -alpha, (AI_tracker + 1));
		if ((temp->score) >= beta)){

			DeleteBoard(temp->next_level->board);
			DeleteMoveList(temp->next_level);			
			return beta; /*alpha beta pruning: if temp->score >= beta then that branch will be deleted*/
		}
		if ((temp->score) > alpha){
			alpha = temp->score;
		}
		DeleteBoard(temp->next_level->board); /*delete the branches once we've figured out the highest score and best move*/
		DeleteMoveList(temp->next_level);
		temp = temp->nextentry;
	} /*while end*/
	
	return alpha;
	
} /*EOF*/
