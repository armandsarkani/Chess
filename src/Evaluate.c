#include "Evaluate.h"
/*Copyright Benny Lin*/
/* Last modified 1/30/2019*/
/* 
 * Things that need to be developed:
	
	Functions:
		int score_move();
		
		int CheckKillerMoves();
		int CheckCaptureMoves();
		int EvaluatePosition();
	
	Constants:
		Piece-SquareTable (needs some redefinition)
			*A PST is a 1-D array of 64 elements. Each element represents a position on the board. A position is given more weight if it 
			is better for the piece to be there. Higher values = better positions. The array encourages certain behaviors for the pieces.
			i.e. Pawns are enccouraged to move forward and stay in the center, knights are encouraged to stay in the center of the board, 
			kings are encouraged to stay out of corners of the board 
		Piece value (needs more discussion on how much a piece is worth vs. position)
		
	General formula for what is a good move
*/

/*PIECE SQUARE TABLE*/
const int PawnTable[64] = {
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,
10	,	10	,	0	,	-10	,	-10	,	0	,	10	,	10	,
5	,	0	,	0	,	5	,	5	,	0	,	0	,	5	,
0	,	0	,	10	,	20	,	20	,	10	,	0	,	0	,
5	,	5	,	5	,	10	,	10	,	5	,	5	,	5	,
10	,	10	,	10	,	20	,	20	,	10	,	10	,	10	,
20	,	20	,	20	,	30	,	30	,	20	,	20	,	20	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int KnightTable[64] = {
0	,	-10	,	0	,	0	,	0	,	0	,	-10	,	0	,
0	,	0	,	0	,	5	,	5	,	0	,	0	,	0	,
0	,	0	,	10	,	10	,	10	,	10	,	0	,	0	,
0	,	0	,	10	,	20	,	20	,	10	,	5	,	0	,
5	,	10	,	15	,	20	,	20	,	15	,	10	,	5	,
5	,	10	,	10	,	20	,	20	,	10	,	10	,	5	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0		
};

const int BishopTable[64] = {
0	,	0	,	-10	,	0	,	0	,	-10	,	0	,	0	,
0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
0	,	10	,	15	,	20	,	20	,	15	,	10	,	0	,
0	,	0	,	10	,	15	,	15	,	10	,	0	,	0	,
0	,	0	,	0	,	10	,	10	,	0	,	0	,	0	,
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	
};

const int RookTable[64] = {
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0	,
25	,	25	,	25	,	25	,	25	,	25	,	25	,	25	,
0	,	0	,	5	,	10	,	10	,	5	,	0	,	0		
};

const int KingE[64] = {	/*PLAYER KING*/
	-50	,	-10	,	0	,	0	,	0	,	0	,	-10	,	-50	,
	-10,	0	,	10	,	10	,	10	,	10	,	0	,	-10	,
	0	,	10	,	20	,	20	,	20	,	20	,	10	,	0	,
	0	,	10	,	20	,	40	,	40	,	20	,	10	,	0	,
	0	,	10	,	20	,	40	,	40	,	20	,	10	,	0	,
	0	,	10	,	20	,	20	,	20	,	20	,	10	,	0	,
	-10,	0	,	10	,	10	,	10	,	10	,	0	,	-10	,
	-50	,	-10	,	0	,	0	,	0	,	0	,	-10	,	-50	
};

const int KingO[64] = {	/*AI KING*/
	0	,	5	,	5	,	-10	,	-10	,	0	,	10	,	5	,
	-30	,	-30	,	-30	,	-30	,	-30	,	-30	,	-30	,	-30	,
	-50	,	-50	,	-50	,	-50	,	-50	,	-50	,	-50	,	-50	,
	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,
	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70	,	-70		
};

/*END TABLES*/
	/*Passes a move entry. Move entry is accessed. Data( row, col, new_board) is used to evaluate ce
  	Calls all other functions and sums the subscores for a final score
  	Returns final score */
int scoremove(MOVE *origmove, PLAYER *player, PLAYER *opponent){/* PArent function*/
	int i, score;
	int piece_tracker = 0;
    PLAYER *white, *black;
    BOARD *board;
	if (player->color == 'w'){/* WHo is white and who is black*/
		if(player->type == 'a'){
			white = CreatePlayer( 'w', 'a');
			black = CreatePlayer('b', 'h');
			
		}else {
			white = CreatePlayer('w', 'h');
			black = CreatePlayer('b', 'a');
		}
		board = CreateBoard(white, black, origmove->board->boardarray);
	}else{
		if(player->type == 'a'){
			black = CreatePlayer('b', 'a');
			white = CreatePlayer('w', 'h');
		}else{
			black = CreatePlayer('b', 'h');
			white = CreatePlayer('w', 'a');
		}
		board = CreateBoard(white, black, origmove->new_board);
	}
	
	for (i = 0; i < 16; i++){ /* copies old boARD TO NEW BOARD STRUCT*/
		white->piecelist[i]->player = white;
		white->piecelist[i]->piecetype = origmove->prev_level->board->white->piecelist[i]->piecetype ;
		white->piecelist[i]->c = origmove->prev_level->board->white->piecelist[i]->c;
		white->piecelist[i]->r = origmove->prev_level->board->white->piecelist[i]->r;
		white->piecelist[i]->value = origmove->prev_level->board->white->piecelist[i]->value;
		
		if (((white->piecelist[i]->r) == (origmove->src_row))&&((white->piecelist[i]->c) == origmove->src_col)){
			white->piecelist[i]->r = origmove->dst_row; 
			white->piecelist[i]->c = origmove->dst_col;
			/*Needs to check if it captures a piece and remove that piece from the list*/
			 piece_tracker = i;
		}
		
		black->piecelist[i]->player = black;
		black->piecelist[i]->piecetype = origmove->prev_level->board->black->piecelist[i]->piecetype ;
		black->piecelist[i]->c = origmove->prev_level->board->black->piecelist[i]->c;
		black->piecelist[i]->r = origmove->prev_level->board->black->piecelist[i]->r;
		black->piecelist[i]->value = origmove->prev_level->board->black->piecelist[i]->value;
		
		if (((black->piecelist[i]->r) == (origmove->src_row))&&((black->piecelist[i]->c) == origmove->src_col)){
			black->piecelist[i]->r = origmove->dst_row; 
			black->piecelist[i]->c = origmove->dst_col;
			/*Needs to check if it captures a piece and remove that piece from the list*/
			 piece_tracker = i;
		}
	}
	if(player->color == white->color){
		score = EvaluatePosition(origmove, white->piecelist[piece_tracker], board, white, black);
	}else {
		score = EvaluatePosition(origmove, black->piecelist[piece_tracker], board, black, white);
	}
	return score;
}

/*int CheckKillerMoves(MOVE *move, PLAYER *opponent){

}*/
int CheckCaptureMoves(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board){
	int x,y;
	int src_row = move -> src_row;
    int src_col = move -> src_col;
	int dst_row = move -> dst_row;
	int dst_col = move -> dst_col;
	int result;
	
	int new_temp_score = 0;
	int score = 0;
	
	int pos;
	
	BOARD *old_board = move->prev_level->board;
	
	PLAYER *prev_opponentpos = NULL;
	PLAYER *player = piece->player;
	
	switch (opponent->color){
		case 'w':
			prev_opponentpos = move->prev_level->board->white; 
			break;
		case 'b':
			prev_opponentpos = move->prev_level->board->black;
			break;
	}
	
	
	PIECE *piececaptured = NULL;
	
	/*make the move using CallPiece*/
	result = CallPiece(old_board, prev_opponentpos, piece, src_row, src_col, dst_row, dst_col, 0);
	if(result == 2) { /*see if the piece captures another piece*/
		piececaptured = CheckPiece(prev_opponentpos, dst_row, dst_col); /*find out what piece it captured*/
		score = 4*(piececaptured -> value); /*add the value to the score*/
	}/*if end*/
		/*TO LOOK AHEAD AFTER A PIECE CAPTURES:*/
		/*scan new_board in the passed in move*/
		/*once not null use checkpiece to find out which piece it is*/
		/*get legal moves of that piece (have to edit the for loops and stuff below)*/
    PIECE *new_piece;
    int i;
	for(i = Pawn1; i <= King; i++){
		new_piece = player->piecelist[i];
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++){
                piececaptured = CheckPiece(opponent, x+1, y+1);
				result = CallPiece(new_board, opponent, new_piece, (new_piece->r)+1, (new_piece->c)+1, x+1, y+1, 0);
				if (result == 2){ /*if player piece returns a capture*/
                    assert(piececaptured);
					piececaptured = CheckPiece(opponent, x+1, y+1);
					pos = BoardtoPSQTable(x , y);
					/*FInal formula needs more work*/
                    new_temp_score = ReturnPosScore(new_piece->piecetype, pos) + (piececaptured->value);
				}
			}	
		}	
		/*end for*/
	}/*end for*/
    score = score + new_temp_score;
	return score;
} /*EOF*/
	

int EvaluatePosition(MOVE *move, PIECE *piece, BOARD *board, PLAYER *player, PLAYER *opponent){
	int x,y, pos, base_score, final_score;
	x = move->dst_row;
	y = move->dst_col;
	
	pos = BoardtoPSQTable(x, y);
	
	char piecetype = piece->piecetype;
	base_score = ReturnPosScore(piecetype, pos);
	
	final_score = base_score /*- CheckKillerMoves()*/ + CheckCaptureMoves(move, piece, opponent, board) /*+ CheckBeyondPiece()*/;
	return final_score;
}

//int CheckBeyondPiece(){
/* IF WE HAVE TIME*/	
//}

int ReturnPosScore(char piecetype, int pos){
	int score = 0;
	switch(piecetype){
		case 'P':
			score = PawnTable[pos];
			break;
		case 'R':
			score = RookTable[pos];
			break;
		case 'N':
			score = KnightTable[pos];
			break;
		case 'K':
			//if(/*CHECKS WHOSE KING IT IS*/){
				score = KingE[pos];
			//}else{
				//score = KingO[pos];
			//}
			break;
		case 'Q':
            score = /*QueenTable[pos];*/ BishopTable[pos];
			break;
		case 'B':
			score = BishopTable[pos];
			break;
	}	
	return score;
}

int BoardtoPSQTable(int row, int col){
	int pos;
	pos = (row - 1) * 8 + (col - 1);
	return pos;
}

