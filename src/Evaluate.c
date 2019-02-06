<<<<<<< HEAD
nclude "Evaluate.h"
=======
#include "Evaluate.h"
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
/*Copyright Benny Lin*/
/* Last modified 2/6/2019*/

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

/*Passes a move entry. Move entry is accessed. Data(row, col, new_board) is used to evaluate
 *  Calls all other functions and sums the subscores for a final score
 *   Returns final score*/
int scoremove(MOVE *origmove, PLAYER *player, PLAYER *opponent){ /*Parent function*/
	int i, score;
	int piece_tracker = 0;
    PIECE *piece = NULL;
    PLAYER *white, *black;
    BOARD *board;
<<<<<<< HEAD
	if (player->color == 'w'){/* Who is white and who is black*/
=======
	if (player->color == 'w'){/* WHo is white and who is black*/
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
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
	
    for ( i = 0; i < 16; i++){
<<<<<<< HEAD
        /*trying to copy movelist with that move made*/
=======
        // trying to copy movelist with that move made
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
        white->piecelist[i]->player = white;
        white->piecelist[i]->piecetype = origmove->prev_level->board->white->piecelist[i]->piecetype;
        white->piecelist[i]->c = origmove->prev_level->board->white->piecelist[i]->c;
        white->piecelist[i]->r = origmove->prev_level->board->white->piecelist[i]->r;
        white->piecelist[i]->value = origmove->prev_level->board->white->piecelist[i]->value;
        
        if (((white->piecelist[i]->r) == (origmove->src_row))&&((white->piecelist[i]->c) == origmove->src_col)){
            
            white->piecelist[i]->r = origmove->dst_row;
            white->piecelist[i]->c = origmove->dst_col;
            if (origmove->IsCaptured == 1){
                piece = CheckPiece(black, (origmove->dst_row)+1, (origmove->dst_col)+1);
            }
            
        }
        white->piecelist[i]->r = origmove->prev_level->board->white->piecelist[i]->r;
        white->piecelist[i]->c = origmove->prev_level->board->white->piecelist[i]->c;
<<<<<<< HEAD
        /*Moves piece in piece list*/
=======
        //Moves piece in data list
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
        
        black->piecelist[i]->player = black;
        black->piecelist[i]->piecetype = origmove->prev_level->board->black->piecelist[i]->piecetype;
        black->piecelist[i]->c = origmove->prev_level->board->black->piecelist[i]->c;
        black->piecelist[i]->r = origmove->prev_level->board->black->piecelist[i]->r;
        black->piecelist[i]->value = origmove->prev_level->board->black->piecelist[i]->value;
        
        if (((black->piecelist[i]->r) == (origmove->src_row))&&((black->piecelist[i]->c) == origmove->src_col)){
            black->piecelist[i]->r = origmove->dst_row;
            black->piecelist[i]->c = origmove->dst_col;
            
            if (origmove->IsCaptured == 1){
                piece = CheckPiece(white, (origmove->dst_row)+1, (origmove->dst_col)+1);
            }
<<<<<<< HEAD
        }/*Moves Piece in piece list*/
		
		/*indicate piece if offboard if it is captured*/
=======
        }//Moves Piece in data list
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
        if (origmove->IsCaptured == 1 && piece != NULL){
            if(piece->piecetype != 'K'){

            piece->r = 9;
            piece->c = 9;
            piece->value = 0;
            if(piece->player->color == 'w')
            {
                origmove->prev_level->board->white->piecelist[i] = piece;
                
            }
            else
            {
                origmove->prev_level->board->black->piecelist[i] = piece;
            }
            }
        }
    }
    
<<<<<<< HEAD
	/*final scoring of move*/
=======
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
	if(player->color == white->color){
		score = EvaluatePosition(origmove, white->piecelist[piece_tracker], board, white, black);
	}else {
		score = EvaluatePosition(origmove, black->piecelist[piece_tracker], board, black, white);
	}
	return score;
}

<<<<<<< HEAD
/*Checks if the opponent can make a future capture on the player's piece*/
=======
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
int CheckKillerMoves(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board){
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
    
<<<<<<< HEAD
    PLAYER *prev_playerpos = NULL; /*obtaining the player's previous board state data*/
    PLAYER *player = piece->player;
    
    switch (player->color){ /*establish the white or black player of the game*/
        case 'w':
            prev_playerpos = move->prev_level->board->white;
            break;
        case 'b':
            prev_playerpos = move->prev_level->board->black;
=======
    PLAYER *prev_opponentpos = NULL;
    PLAYER *player = piece->player;
    
    switch (opponent->color){
        case 'w':
            prev_opponentpos = move->prev_level->board->white;
            break;
        case 'b':
            prev_opponentpos = move->prev_level->board->black;
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
            break;
    }
    
    
    PIECE *piececaptured = NULL;
    
    /*make the move using CallPiece*/
<<<<<<< HEAD
    result = CallPiece(old_board, prev_playerpos, piece, src_row+1, src_col+1, dst_row+1, dst_col+1, 0);
    if(result == 2) { /*see if the piece captures another piece*/
        piececaptured = CheckPiece(prev_playerpos, dst_row + 1, dst_col + 1 ); /*find out what piece it captured*/
        score = (piececaptured -> value); /*add the value to the score*/
    }/*if end*/
    
    PIECE *new_piece;
    int i;
    for(i = Pawn1; i <= King; i++){
        new_piece = opponent->piecelist[i];
        if (new_piece->r == 9){
            continue;
        } 
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++){ /*loop through piecelist to establish the captured piece*/
                piececaptured = CheckPiece(player, x+1, y+1);
                result = CallPiece(new_board, player, new_piece, (new_piece->r)+1, (new_piece->c)+1, x+1, y+1, 0);
                if (result == 2){ /*if player piece returns a capture (Call piece func passes in opponent)*/
                    piececaptured = CheckPiece(player, x+1, y+1);
                    pos = BoardtoPSQTable(x, y);
					/*Final Formula*/
=======
    result = CallPiece(old_board, prev_opponentpos, piece, src_row+1, src_col+1, dst_row+1, dst_col+1, 0);
    if(result == 2) { /*see if the piece captures another piece*/
        piececaptured = CheckPiece(prev_opponentpos, dst_row + 1, dst_col + 1 ); /*find out what piece it captured*/
        score = (piececaptured -> value); /*add the value to the score*/
    }/*if end*/
    /*TO LOOK AHEAD AFTER A PIECE CAPTURES:*/
    /*scan new_board in the passed in move*/
    /*once not null use checkpiece to find out which piece it is*/
    /*get legal moves of that piece (have to edit the for loops and stuff below)*/
    PIECE *new_piece;
    int i;
    for(i = Pawn1; i <= King; i++){
        new_piece = player->piecelist[i];
        if (new_piece->r == 9){
            continue;
        }
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++){
                piececaptured = CheckPiece(opponent, x+1, y+1);
                result = CallPiece(new_board, opponent, new_piece, (new_piece->r)+1, (new_piece->c)+1, x+1, y+1, 0);
                if (result == 2){ /*if player piece returns a capture*/
                    piececaptured = CheckPiece(opponent, x+1, y+1);
                    pos = BoardtoPSQTable(x , y);
                    /*FInal formula needs more work*/
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
                    new_temp_score = 0*ReturnPosScore(new_piece->piecetype, pos) + 3*(piececaptured->value);
                }
            }
        }
        /*end for*/
    }/*end for*/
    score = score + new_temp_score;
    return score;
}

/*Checks if the player can make a future capture on the opponent based on board state*/
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
	
<<<<<<< HEAD
	PLAYER *prev_opponentpos = NULL; /*obtaining the opponent's previous board state data*/
=======
	PLAYER *prev_opponentpos = NULL;
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
	PLAYER *player = piece->player;
	
	switch (opponent->color){ /*establish the white or black player of the game*/
		case 'w':
			prev_opponentpos = move->prev_level->board->white; 
			break;
		case 'b':
			prev_opponentpos = move->prev_level->board->black;
			break;
	}
	
	
	PIECE *piececaptured = NULL;
	
	/*make the move using CallPiece*/
	result = CallPiece(old_board, prev_opponentpos, piece, src_row+1, src_col+1, dst_row+1, dst_col+1, 0);
	if(result == 2) { /*see if the piece captures another piece*/
		piececaptured = CheckPiece(prev_opponentpos, dst_row + 1, dst_col + 1 ); /*find out what piece it captured*/
		score = (piececaptured -> value); /*add the value to the score*/
	}/*if end*/
<<<<<<< HEAD

    PIECE *new_piece;
    int i;
	for(i = Pawn1; i <= King; i++){ /*loop through piecelist to establish the captured piece*/
=======
		/*TO LOOK AHEAD AFTER A PIECE CAPTURES:*/
		/*scan new_board in the passed in move*/
		/*once not null use checkpiece to find out which piece it is*/
		/*get legal moves of that piece (have to edit the for loops and stuff below)*/
    PIECE *new_piece;
    int i;
	for(i = Pawn1; i <= King; i++){
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
		new_piece = player->piecelist[i];
        if (new_piece->r == 9){
            continue;
        }
		for (x = 0; x < 8; x++) {
			for (y = 0; y < 8; y++){
                piececaptured = CheckPiece(opponent, x+1, y+1);
				result = CallPiece(new_board, opponent, new_piece, (new_piece->r)+1, (new_piece->c)+1, x+1, y+1, 0);
<<<<<<< HEAD
				if (result == 2){ /*if player piece returns a capture (Call piece func passes in opponent)*/
					piececaptured = CheckPiece(opponent, x+1, y+1);
					pos = BoardtoPSQTable(x, y);
					/*Final Formula*/
=======
				if (result == 2){ /*if player piece returns a capture*/
					piececaptured = CheckPiece(opponent, x+1, y+1);
					pos = BoardtoPSQTable(x , y);
					/*FInal formula needs more work*/
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
                    new_temp_score = ReturnPosScore(new_piece->piecetype, pos) + (piececaptured->value);
				}
			}	
		}	
		/*end for*/
	}/*end for*/
    score = score + new_temp_score;
	return score;
} /*EOF*/
	
<<<<<<< HEAD
/*Gives a score for the move being evaluated based on CheckKillerMoves, CheckCaptureMoves, and ReturnPosScore funcs*/
=======

>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
int EvaluatePosition(MOVE *move, PIECE *piece, BOARD *board, PLAYER *player, PLAYER *opponent){
	int x,y, pos, base_score, final_score;
	x = move->dst_row;
	y = move->dst_col;
	
	pos = BoardtoPSQTable(x, y);
	
	char piecetype = piece->piecetype;
	base_score = ReturnPosScore(piecetype, pos);
	
<<<<<<< HEAD
	final_score = base_score + CheckKillerMoves(move, piece, opponent, board) + CheckCaptureMoves(move, piece, opponent, board) /*+ CheckBeyondPiece()*/;
	return final_score;
}

/*returns a base score for a piece based on it's position on the board*/
=======
	final_score = base_score /*- CheckKillerMoves()*/ + CheckCaptureMoves(move, piece, opponent, board) /*+ CheckBeyondPiece()*/;
	return final_score;
}

//int CheckBeyondPiece(){
/* IF WE HAVE TIME*/	
//}

>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
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
<<<<<<< HEAD
			/*if(*CHECKS WHOSE KING IT IS){*/
				score = KingE[pos];
			/*}else{
 * 				//score = KingO[pos];
 * 							}*/
=======
			//if(/*CHECKS WHOSE KING IT IS*/){
				score = KingE[pos];
			//}else{
				//score = KingO[pos];
			//}
>>>>>>> 7d09c4cc79d652f4be7a88c7b370dc9830468cc3
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

/*Converting board position to the PSQ table position */
int BoardtoPSQTable(int row, int col){
	int pos;
	pos = (row - 1) * 8 + (col - 1);
	return pos;
}
