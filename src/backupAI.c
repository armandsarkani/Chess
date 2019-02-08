//  backupAI.c
//  Chesster Team 3
#include "backupAI.h"

/*AI function for now will just move based on capture pieces*/
/*AI function will pass in: a board, a player, and an opponent)*/
/*it will scan the board until it hits a piece*/
/*once it hits a piece, it will get list of all possible moves for that piece*/
/*once it gets all possible moves, use callpiece and see if it returns a 2 (capture)*/
/*see which piece it captures, assign a score, keep score and move in variables*/
/*if no captures possible, move first piece it sees in array*/
/*random function: choose a random number, loop through that random number x times
 *  * and choose that move from getmoves*/
MOVE *backupAI(BOARD *board, PLAYER *player, PLAYER *opponent){
    
    PIECE *piece;
    PIECE *piececaptured;
    MOVELIST *movelist;
    MOVE *bestmove = NULL;
    PIECE *tempcapture = NULL;
    movelist = NewMoveList(); /*allocate mem*/
    movelist->length = 0;
    movelist->board = NULL;
    int value = 0;
    int score = 0;
    int bestscore = 0;
    int checkvalue = 0;
    MOVE *tempmove;
    MOVE *blue = CreateMove();
    getmoves(board->boardarray, board, player, opponent, movelist);
    tempmove = movelist->first;
    while (tempmove != NULL) {
        piece = tempmove->piece;
        value = tempmove->IsCaptured;
        checkvalue = tempmove->CheckMove;
        if(value == 1) {
            piececaptured = tempmove->opponentcapture;
            score = piececaptured -> value;
            if(checkvalue == 1)
            {
                score += 9;
            }
            if(score > bestscore){
                bestscore = score;
                bestmove = tempmove;
            }/*if end*/
        }/*if end*/
        tempmove = tempmove->nextentry;
    }/*while end*/
    if(bestmove != NULL)
    {
        tempcapture = bestmove->opponentcapture;
        CapturePiece(board, bestmove->opponentcapture);
    }
    if(bestmove == NULL) { /*if no pieces can capture*/
        /*generate a random move*/
        srand((unsigned)time(0));
        /*generate a random move or other type of move*/
        bestmove = movelist->first;
        int randnum = rand() % (movelist->length);
        for(int a = 0; a < randnum; a++){
            bestmove = bestmove->nextentry;
        } /*for end*/
    } /*if end*/
    blue->src_row = bestmove->src_row;
    blue->src_col = bestmove->src_col;
    blue->dst_row = bestmove->dst_row;
    blue->dst_col = bestmove->dst_col;
    blue->opponentcapture = tempcapture;
    blue->IsCaptured = bestmove->IsCaptured;
    blue->next_level = NULL;
    DeleteMoveList(movelist);
    return blue; /*at the end of the while loop it will return the highest valued capture move*/
}
