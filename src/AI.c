//  AI.c
//  Chess
//
//  Created by Jada Berenguer and Benny Lin on 1/21/19.
//  Copyright © 2019 Jada Berenguer and Benny Lin. All rights reserved.
//  

void AI(board[8][8]){
	MOVELIST *list = malloc;
	list = getmoves(board[8][8], player, opponent);
	MOVE *temp = NULL; 
	MOVE *bestmove = NULL;
	temp = list -> first;
	int bestscore = -10000000000000;
	int alpha = -INF;
	int beta = INF;
	/*create getmoves function*/
	while (temp != NULL) { 
		temp->score = NegaMax((depth), temp, alpha, beta);
		if ((temp->score) > bestscore){
			bestscore = temp->score;
			bestmove = temp;
		}
		temp = temp->nextentry;
	} /*while end*/
	MakeMove(bestmove);
}
int NegaMax(int depth, MOVE *origmove, int alpha, int beta){ 
	int movescore = -100000000;
	MOVELIST *movelist;
	/*createmovelist function malloc*/
	if (depth < 1){
		return scoremove(origmove->newboard[8][8]); /*return scorefromsidePOV*/ /*recursion happens*/
	} /*if end*/
	
	MOVE *temp = NULL; 
	movelist = getmoves(origmove->newboard[8][8], PLAYER *player, PLAYER *opponent); 
	temp = movelist -> first;
	/*create getmoves function*/
	while (temp != NULL) { 
		temp->score = -(NegaMax((depth-1), temp, -beta, -alpha);
		if ((temp->score) >= beta){
			return beta;
		}
		if ((temp->score) > alpha){
			alpha = temp->score;
		}
		temp = temp->nextentry;
	} /*while end*/
	return alpha;
	
} /*EOF*/
