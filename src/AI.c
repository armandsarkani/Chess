//  AI.c
//  //  Chess
//  //
//  //  Created by Jada Berenguer and Benny Lin
//  //  Last modified on 1/27/19.
//  //  Copyright © 2019 Jada Berenguer and Benny Lin. All rights reserved.
//  // 
#include "Pieces.h"
#include "Movegen.h"
#include "Evaluate.h"

void AI(board[8][8], PLAYER *player, PLAYER *opponent){
	MOVELIST *list = NewMoveList(); 
	int AI_tracker = 1; /*keep track of who's turn it is*/
	list->board = CreateBoard(player, opponent, board[8][8]);
	getmoves(board[8][8], player, opponent, list); /*first layer of list created*/
	MOVE *temp = NULL; 
	MOVE *bestmove = NULL;
	temp = list -> first; 
	int bestscore = -INF;
	int alpha = -INF;
	int beta = INF;
	while (temp != NULL) { 
		temp->score = NegaMax(depth, temp, alpha, beta, AI_tracker); /*Negamax (recursive func) will return the best score for that move*/
		if ((temp->score) > bestscore){
			bestscore = temp->score;
			bestmove = temp;
		}
		temp = temp->nextentry;
	} /*while end*/
	MakeMove(bestmove);
	DeleteBoard(list->board);
	DeleteMoveList(list);
}

/*Pass in the first layers possible moves*/
int NegaMax(int depth, MOVE *origmove, int alpha, int beta, int AI_tracker){ 
	int movescore = -INF;
	if ((AI_tracker mod 2) == 1){ /*keep track of which player's turn it is down the list*/
		if(origmove->prev_level->board->white->type == 'a'){ 
			PLAYER *player = origmove-> prev_level->board->white;
			PLAYER *opponent = origmove-> prev_level->board->black;
		}
		else {
			PLAYER *player = origmove-> prev_level->board->black;
			PLAYER *opponent = origmove-> prev_level->board->white;
		}
	} else {
		if(origmove->prev_level->board->white->type == 'a'){ 
			PLAYER *opponent = origmove-> prev_level->board->white;
			PLAYER *player = origmove-> prev_level->board->black;
		}
		else {
			PLAYER *opponent = origmove-> prev_level->board->black;
			PLAYER *player = origmove-> prev_level->board->white;
		}
	}
	
	origmove->next_level = NewMovelist(); /*create a new Movelist for the next layer*/
	origmove->next_level->board = CreateBoard(origmove->prevlevel->board->white, origmove->prevlevel->board->black,origmove->new_board[8][8]); /*set the board of the new layer's Movelist*/ 
	origmove -> next_level -> prevmove = origmove; /*set the new layer's movelist prevmove to point to the orig move*/

	if (depth < 1){
		return scoremove(origmove, opponent); /*return scorefromsidePOV*/ /*recursion happens*/
	} /*if end*/
	
	MOVE *temp = NULL; 
	MOVELIST *movelist = origmove->next_level; /*newly created Movelist (line 59) is assigned to the next layer*/
	getmoves(origmove->newboard[8][8], player, opponent, movelist); /*get legal moves for the passed in origmove*/
	temp = movelist -> first; 
	while (temp != NULL) { 
		temp->score = -(NegaMax((depth-1), temp, -beta, -alpha, (AI_tracker + 1));
		if ((temp->score) >= beta){
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
