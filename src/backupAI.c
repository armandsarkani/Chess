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
    MOVE *capturemove = NULL;
    movelist = NewMoveList(); /*allocate mem*/
    movelist->length = 0;
    int value = 0;
    int score = 0;
    //int success = 0;
    int bestscore = 0;
    MOVE *tempmove;
    MOVE *blue = CreateMove();
    getmoves(board->boardarray, board, player, opponent, movelist);
    tempmove = movelist->first;
    while (tempmove != NULL) {
        piece = tempmove->piece;
        value = tempmove->IsCaptured;
        if(value == 1) {
            piececaptured = tempmove->opponentcapture;
            score = piececaptured -> value;
            if(score > bestscore){
                bestscore = score;
                capturemove = tempmove;
            }/*if end*/
        }/*if end*/
        tempmove = tempmove->nextentry;
    }/*while end*/
    if(capturemove != NULL)
    {
        CapturePiece(board, capturemove->opponentcapture);
    }
    if(capturemove == NULL) { /*if no pieces can capture*/
        /*generate a random move*/
        srand((unsigned)time(0));
        /*generate a random move or other type of move*/
        capturemove = movelist->first;
        int randnum = rand() % (movelist->length);
        for(int a = 0; a < randnum; a++){
            capturemove = capturemove->nextentry;
        } /*for end*/
    } /*if end*/
    blue->src_row = capturemove->src_row;
    blue->src_col = capturemove->src_col;
    blue->dst_row = capturemove->dst_row;
    blue->dst_col = capturemove->dst_col;
    blue->IsCaptured = capturemove->IsCaptured;
    blue->next_level = NULL;
    DeleteMoveList(movelist);
    return blue; /*at the end of the while loop it will return the highest valued capture move*/
}
