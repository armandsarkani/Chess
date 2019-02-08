//  //  Last modified on 1/30/19.
//  //  //  Copyright © 2019 Jada Berenguer and Benny Lin. All rights reserved.
//  //  //
//
//  //  Chess
//  //
//  //  Created by Jada Berenguer and Benny Lin on 1/21/19.
//  //  Copyright © 2019 Jada Berenguer and Benny Lin. All rights reserved.
//  //
#include "AI.h"

MOVE *AI(BOARD *board, PLAYER *AI, PLAYER *human, int turn_counter){
    MOVELIST *list = NewMoveList();
    int AI_tracker = 1; /*keep track of who's turn it is*/
    
    if (AI -> color == 'w'){
        list->board = CreateAIBoard(AI, human, board->boardarray);
    }else {
        list->board = CreateAIBoard(human, AI, board->boardarray);
    }
    PLAYER *white = list->board->white;
    PLAYER *black = list->board->black;
    for (int i = 0; i < 16; i++){
        // trying to copy movelist with that move made
        white->piecelist[i]->player = white;
        white->piecelist[i]->piecetype = board->white->piecelist[i]->piecetype;
        white->piecelist[i]->c = board->white->piecelist[i]->c;
        white->piecelist[i]->r = board->white->piecelist[i]->r;
        white->piecelist[i]->value = board->white->piecelist[i]->value;
        black->piecelist[i]->player = black;
        black->piecelist[i]->piecetype = board->black->piecelist[i]->piecetype;
        black->piecelist[i]->c = board->black->piecelist[i]->c;
        black->piecelist[i]->r = board->black->piecelist[i]->r;
        black->piecelist[i]->value = board->black->piecelist[i]->value;
    }
    getsmartmoves(board->boardarray, board, AI, human, list, 1, turn_counter, 1); /*first layer of list created*/
    if(list->first == NULL){
        getsmartmoves(board->boardarray, board, AI, human, list, 0, turn_counter, 1);
    }
    if(list->first == NULL){
        getsmartmoves(board->boardarray, board, AI, human, list, 0, turn_counter, 0);
    }
    MOVE *temp = NULL;
    MOVE *bestmove = NULL;
    MOVE *blue = CreateMove();
    temp = list -> first;
    
    int bestscore = -999999999;
    int alpha = -900000000;
    int beta = 900000000;
    int depth = 1;
    
    if(turn_counter < 2){
        depth = 2;
    }else{
        depth = 5;
    }
    
    MOVE *next = NULL;
    int list_delete_tracker = 0;
    int ldt_guard = 0;
    while (temp != NULL) {
        temp->score = NegaMax(depth, temp, alpha, beta, AI_tracker, turn_counter+1, ldt_guard); /*Negamax (recursive func) will return the best score for that move*/
        next = temp->nextentry;
        if (temp->BadMove == 1){
            list_delete_tracker++;
        }
        temp = temp->nextentry;
    } /*while end*/
    if(list_delete_tracker == list->length){
        ldt_guard = 1;
    }
    else{
        ldt_guard = 2;
    }
    temp = list->first;
    while (temp != NULL) {
        next = temp->nextentry;
        if (ldt_guard == 0){
            if (temp->BadMove == 0){
                DeleteInsertedMove(temp);
                temp = next;
                next = temp->nextentry;
                if(next == NULL){
                    break;
                }
            }
        }
        temp->score = NegaMax(depth, temp, alpha, beta, AI_tracker, turn_counter+1, ldt_guard); /*Negamax (recursive func) will return the best score for that move*/
        if ((temp->score) > bestscore){
            bestscore = temp->score;
            bestmove = temp;
        }
        temp = temp->nextentry;
    } /*while end*/
    blue->src_row = bestmove->src_row;
    blue->src_col = bestmove->src_col;
    blue->dst_row = bestmove->dst_row;
    blue->dst_col = bestmove->dst_col;
    blue->IsCaptured = bestmove->IsCaptured;
    blue->opponentcapture = bestmove->opponentcapture;
    blue->next_level = NULL;
    blue->nextentry = NULL;
    
    
    DeleteMoveList(list);
    return blue;
}/*EOF*/
// Pass in the first layers possible moves
int NegaMax(int depth, MOVE *origmove, int alpha, int beta, int AI_tracker, int turn_counter, int ldt_guard){
    
    origmove->next_level = NewMoveList(); //create a new Movelist for the next layer
    PIECE *piece = origmove->opponentcapture;
    //int temppiece = 0;
    origmove->next_level->board = CreateAIBoard(origmove->board->white, origmove->board->black,origmove->new_board); /*set the board of the new layer's Movelist*/
    PLAYER *white = origmove->next_level->board->white;
    PLAYER *black = origmove->next_level->board->black;
    //int j = 0;
    for (int i = 0; i < 16; i++){
        // trying to copy movelist with that move made
        white->piecelist[i]->player = origmove->next_level->board->white;
        white->piecelist[i]->piecetype = origmove->prev_level->board->white->piecelist[i]->piecetype;
        white->piecelist[i]->c = origmove->prev_level->board->white->piecelist[i]->c;
        white->piecelist[i]->r = origmove->prev_level->board->white->piecelist[i]->r;
        white->piecelist[i]->value = origmove->prev_level->board->white->piecelist[i]->value;
        
        if (((white->piecelist[i]->r) == (origmove->src_row))&&((white->piecelist[i]->c) == origmove->src_col)){
            
            white->piecelist[i]->r = origmove->dst_row;
            white->piecelist[i]->c = origmove->dst_col;
            //Moves piece in data list
        }
        black->piecelist[i]->player = origmove->next_level->board->black;
        black->piecelist[i]->piecetype = origmove->prev_level->board->black->piecelist[i]->piecetype;
        black->piecelist[i]->c = origmove->prev_level->board->black->piecelist[i]->c;
        black->piecelist[i]->r = origmove->prev_level->board->black->piecelist[i]->r;
        black->piecelist[i]->value = origmove->prev_level->board->black->piecelist[i]->value;
        
        if (((black->piecelist[i]->r) == (origmove->src_row))&&((black->piecelist[i]->c) == origmove->src_col)){
            black->piecelist[i]->r = origmove->dst_row;
            black->piecelist[i]->c = origmove->dst_col;
        }//Moves Piece in data list
    }
    for(int i = 0; i < 16; i++)
    {
        if(piece != NULL)
        {
            if(piece->player == white)
            {
                if(white->piecelist[i]->r == origmove->dst_row && white->piecelist[i]->c == origmove->dst_col)
                {
                    white->piecelist[i]->r = 9;
                    white->piecelist[i]->c = 9;
                    white->piecelist[i]->value = 0;
                }
            }
            else if(piece->player == black)
            {
                if(black->piecelist[i]->r == origmove->dst_row && black->piecelist[i]->c == origmove->dst_col)
                {
                    black->piecelist[i]->r = 9;
                    black->piecelist[i]->c = 9;
                    black->piecelist[i]->value = 0;
                }
            }
        }
    }
    
    origmove->next_level->prevmove = origmove; /*set the new layer's movelist prevmove to point to the orig move*/
    PLAYER *player, *opponent;
    int ldt_2 = 2;
    if ((AI_tracker % 2) == 1){ /*keep track of which player's turn it is down the list*/
        if(origmove->prev_level->board->white->type == 'a'){
            player = white;
            opponent = black;
            ldt_2 = 0;
        }
        else {
            player = black;
            opponent = white;
            ldt_2 = 0;
        }
    } else {
        if(origmove->prev_level->board->white->type == 'a'){
            opponent = white;
            player = black;
        }
        else {
            opponent = black;
            player = white;
        }
    }
    
    
    if (depth < 1){
        return scoremove(origmove, player, opponent); /*return scorefromsidePOV*/ /*recursion happens*/
    } /*if end*/
    
    MOVE *temp = NULL;
    MOVELIST *movelist = origmove->next_level;
    /*newly created Movelist (line 59) is assigned to the next layer*/
    getsmartmoves(origmove->new_board, origmove->next_level->board, opponent, player, movelist, 1, turn_counter, 1); /*get legal moves for the passed in origmove*/
    if(movelist->first == NULL){
        getsmartmoves(origmove->new_board, origmove->next_level->board, opponent, player, movelist, 0, turn_counter, 1); /*get legal moves for the passed in origmove*/
    }
    if(movelist->first == NULL){
        getsmartmoves(origmove->new_board, origmove->next_level->board, opponent, player, movelist, 0, turn_counter, 0); /*get legal moves for the passed in origmove*/
    }
    temp = movelist -> first;
    MOVE *next = NULL;
    if(ldt_guard == 0){
        while(temp){
            next = temp->nextentry;
            if(AI_tracker == 1){
                if(temp->CheckMove == 1){
                    temp->BadMove = 1;
                    return 0;
                }
            }
            temp = next;
        }
    }
    
    while (temp) {
        temp->score = -(NegaMax((depth-1), temp, -beta, -alpha, (AI_tracker + 1), turn_counter + 1, ldt_2));
        
        if ((temp->score) >= beta){
            return beta; /*alpha beta pruning: if temp->score >= beta then that branch will be deleted*/
        }
        if ((temp->score) > alpha){
            alpha = temp->score;
        }
        if(temp->next_level != NULL){
            //DeleteBoard(temp->next_level->board); /*delete the branches once we've figured out the highest score and best move*/
            DeleteMoveList(temp->next_level);
            temp->next_level = NULL;
        }
        temp = temp->nextentry;
    } /*while
       end*/
    printf("Alpha %d \n", alpha);
    return alpha;
} /*EOF*/

