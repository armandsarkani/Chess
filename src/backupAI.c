//  AI.c
//  //  //  Chess
//  //  //
//  //  //  Created by Jada Berenguer
//  //  //  Last modified on 1/28/19.
//  //  //  Copyright © 2019 Jada Berenguer. All rights reserved.
//  //  //  
/*AI function for now will just move based on capture pieces*/
/*AI function will pass in: a board, a player, and an opponent)*/
/*it will scan the board until it hits a piece*/
/*once it hits a piece, it will get list of all possible moves for that piece*/
/*once it gets all possible moves, use callpiece and see if it returns a 2 (capture)*/
/*see which piece it captures, assign a score, keep score and move in variables*/
/*if no captures possible, move first piece it sees in array*/
/*random function: choose a random number, loop through that random number x times
 *  * and choose that move from getmoves*/
#include "backupAI.h"
MOVE *AI(BOARD *new_board, PLAYER *player, PLAYER *opponent){
	
	PIECE *piece;
	PIECE *piececaptured;
	MOVELIST *movelist; 
    MOVE *capturemove = NULL;
    movelist = NewMoveList(); /*allocate mem*/
    movelist->length = 0;
	int value = 0;
	int score = 0;
    //int success = 0;
	int bestscore = 0;
	MOVE *tempmove;
    MOVE *blue = CreateMove();
    getmoves(new_board, player, opponent, movelist);
    /*for(int i = Pawn1; i <= King; i++)
    {
        piece = player->piecelist[i];
        for (int x = 0; x < 8; x++) { //dummy variable for coordinate tracking on chess board
            for (int y = 0; y < 8; y++){ //y: dummy variable for coordinate tracking on chess board
                success = CallPiece(movelist->board, opponent, piece, piece->r, piece->c, x, y, 0);
                if (success != 1){ //if CallPiece does not return a failure
                    MovePiece(movelist->board, opponent, piece, x, y); //makes move on cpyboard
                    AddLegalMoves(movelist, piece->r, piece->c, x, y, movelist->board->boardarray);
                }
            }
        }
    }*/
    tempmove = movelist->first;
    while (tempmove != NULL) {
        piece = tempmove->piece;
        value = tempmove->IsCaptured;
        if(value == 1) {
            piececaptured = tempmove->opponentcapture;
            score = piececaptured -> value;
            CapturePiece(new_board, piececaptured);
            if(score > bestscore){
                bestscore = score;
                capturemove = tempmove;
            }/*if end*/
        }/*if end*/
        tempmove = tempmove->nextentry;
	}/*while end*/
    if(capturemove == NULL) { /*if no pieces can capture*/
		/*generate a random move*/
		srand((unsigned)time(0));
		/*generate a random move or other type of move*/
        capturemove = movelist->first;
        int randnum = rand() % (movelist->length + 1);
        for(int a = 0; a < randnum; a++){
            capturemove = capturemove->nextentry;
        } /*for end*/
    } /*if end*/
    blue->src_row = capturemove->src_row;
    blue->src_col = capturemove->src_col;
    blue->dst_row = capturemove->dst_row;
    blue->dst_col = capturemove->dst_col;
    //DeleteMoveList(movelist);
	return blue; /*at the end of the while loop it will return the highest valued capture move*/
}
