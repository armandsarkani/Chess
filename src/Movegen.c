//  Movegen.c
//  Chesster Team 3
#include "Movegen.h"


/*Last modified 1/24/19*/
/*Things that need to be added:
 *     DeleteMoveList
 *         DeleteMoveEntry
 *
 *                 accompanying header file movegen.h
 *                 */

void getsmartmoves(char *org_board[8][8], BOARD *board, PLAYER *player, PLAYER *opponent, MOVELIST *list, int t_guard, int turn_counter, int king){
    int success = 0; /*if success = 0*/
    int move;
    int exit = 0;
    int i,x,y,j,a;
    int guard = 0;
    PIECE *o_piece = NULL;
    PIECE *opponentcapture = NULL;
    int o_result = 1;
    char *piecetag = NULL;
    char *capturedpiece = NULL;
    int IsCaptured = 0;
    int opponent_r = 0, opponent_c = 0, opponent_value = 0;
    char *cpy_board[8][8];
    int CheckMove;
    int piecestart, pieceend;
    if(king != 0){
        if(turn_counter < 2){
            piecestart = 5;
            pieceend = 3;
        }
        else
        {
            piecestart = 14;
            pieceend = 0;
        }
    }
    else
    {
        piecestart = 15;
        pieceend = 15;
    }
    for (i = 0; i < 8; i++){/* copies board into a temp board*/
        for (j = 0; j < 8; j++){
            cpy_board[i][j] = org_board[i][j]; /*PLEASE DO NOT CHANGE THIS LINE*/
            /*end for*/
            /*end for*/
        }
    }
    int test = 0;
    for(i = piecestart; i >= pieceend; i--)
    {
        PIECE *piece = player->piecelist[i];
        if(piece->r == 9 || piece->c == 9)
        {
            continue;
        }
        int orig_pieceR = piece->r;
        int orig_pieceC = piece->c;
        int orig_piecevalue = piece->value;
        char *orig_piecetag = board->boardarray[orig_pieceR][orig_pieceC];
        for (x = 0; x < 8; x++)
        {
            for (y = 0; y < 8; y++)
            {
                success = CallPiece(board, opponent, piece, (piece->r)+1, (piece->c)+1, x+1, y+1, 0);
                if(success == 2)
                {
                    test = CallPiece(board, opponent, piece, (piece->r)+1, (piece->c)+1, x+1, y+1, 0);
                }
                if (success != 1) /*if CallPiece does not return a failure*/
                {
                    if(success == 2)
                    {
                        opponentcapture = CheckPiece(opponent, x+1, y+1);
                        opponent_r = opponentcapture->r;
                        opponent_c = opponentcapture->c;
                        opponent_value = opponentcapture->value;
                        piecetag = board->boardarray[opponent_r][opponent_c];
                        guard = 1;
                    }
                    char *originaldesttag = board->boardarray[x][y];
                    move = MovePiece(board, opponent, piece, x, y);/*makes move on cpyboard*/
                    if(move == 1) // if check
                    {
                        if(success == 2)
                        {
                            UndoCapture(board, opponentcapture, opponent_r, opponent_c, opponent_value, piecetag);
                        }
                        if(piece->value == 1 && orig_piecevalue == 2)
                        {
                            piece->value = 2;
                        }
                        success = 0;
                        move = 0;
                        continue;
                    }
                    else
                    {
                        if(success == 2)
                        {
                            IsCaptured = 1;
                            capturedpiece = cpy_board[opponentcapture->r][opponentcapture->c];
                        }
                        if(success != 2)
                        {
                            IsCaptured = 0;
                        }
                        if(CallPiece(board, opponent, piece, x+1, y+1, (opponent->piecelist[King]->r)+1,
                                     (opponent->piecelist[King]->c)+1, 0) == 2){
                            CheckMove = 1;
                        }
                        if(move == 0){
                            if (t_guard == 1){
                                for(a = 1; a < 16; a++){
                                    o_piece = opponent->piecelist[a];
                                    if(o_piece->r == 9){
                                        continue;
                                    }
                                    o_result = CallPiece(board, player, o_piece, o_piece->r+1, o_piece->c+1, x+1, y+1, 0);
                                    if(o_result == 0){
                                        if((o_piece->value) < (piece->value)){
                                            o_result = 1;
                                            exit = 1;
                                            break;
                                        }
                                        o_result = 0;
                                    }
                                }
                            }
                            if(exit == 0)
                            {
                                cpy_board[x][y] = orig_piecetag;
                                cpy_board[orig_pieceR][orig_pieceC] = "  ";
                                board->boardarray[x][y] = originaldesttag;
                                board->boardarray[orig_pieceR][orig_pieceC] = orig_piecetag;
                                piece->r = orig_pieceR;
                                piece->c = orig_pieceC;
                                AddLegalMoves(list, piece->r, piece->c, x, y, board, IsCaptured, piece, opponentcapture, cpy_board, guard);
                                guard = 0;
                                if(IsCaptured == 1)
                                {
                                    cpy_board[x][y] = capturedpiece;
                                    cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                                }
                                else
                                {
                                    cpy_board[x][y] = "  ";
                                    cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                                }
                            }
                            else
                            {
                                cpy_board[x][y] = orig_piecetag;
                                cpy_board[orig_pieceR][orig_pieceC] = "  ";
                                board->boardarray[x][y] = originaldesttag;
                                board->boardarray[orig_pieceR][orig_pieceC] = orig_piecetag;
                                piece->r = orig_pieceR;
                                piece->c = orig_pieceC;
                                if(IsCaptured == 1)
                                {
                                    cpy_board[x][y] = capturedpiece;
                                    cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                                }
                                else
                                {
                                    cpy_board[x][y] = "  ";
                                    cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                                }
                                exit = 0;
                            }
                        }
                    }
                    
                }
            }
            guard = 0;
            move = 0;
            success = 0;
            continue;
        }
    }
    /*end for*/
}/*end for*/

void getmoves(char *org_board[8][8], BOARD *board, PLAYER *player, PLAYER *opponent, MOVELIST *list){
    int success = 0; /*if success = 0*/
    int move;
    int i,x,y,j;
    PIECE *opponentcapture = NULL;
    char *piecetag = NULL;
    char *capturedpiece = NULL;
    int CheckMove = 0;
    int IsCaptured = 0;
    int opponent_r = 0, opponent_c = 0, opponent_value = 0;
    char *cpy_board[8][8];
    for (i = 0; i < 8; i++){/* copies board into a temp board*/
        for (j = 0; j < 8; j++){
            cpy_board[i][j] = org_board[i][j]; /*PLEASE DO NOT CHANGE THIS LINE*/
            /*end for*/
            /*end for*/
        }
    }
    int test = 0;
    for(i = Pawn1; i <= King; i++)
    {
        PIECE *piece = player->piecelist[i];
        if(piece->r == 9 || piece->c == 9)
        {
            continue;
        }
        int orig_pieceR = piece->r;
        int orig_pieceC = piece->c;
        int orig_piecevalue = piece->value;
        char *orig_piecetag = board->boardarray[orig_pieceR][orig_pieceC];
        for (x = 0; x < 8; x++)
        {
            for (y = 0; y < 8; y++)
            {
                success = CallPiece(board, opponent, piece, (piece->r)+1, (piece->c)+1, x+1, y+1, 0);
                if(success == 2)
                {
                    test = CallPiece(board, opponent, piece, (piece->r)+1, (piece->c)+1, x+1, y+1, 0);
                }
                if (success != 1) /*if CallPiece does not return a failure*/
                {
                    if(success == 2)
                    {
                        opponentcapture = CheckPiece(opponent, x+1, y+1);
                        opponent_r = opponentcapture->r;
                        opponent_c = opponentcapture->c;
                        piecetag = board->boardarray[opponent_r][opponent_c];
                        opponent_value = opponentcapture->value;
                        opponentcapture->r = 9;
                        opponentcapture->c = 9;
                        opponentcapture->value = 0;
                    }
                    char *originaldesttag = board->boardarray[x][y];
                    move = MovePiece(board, opponent, piece, x, y);/*makes move on cpyboard*/
                    if(move == 1) // if check
                    {
                        if(success == 2)
                        {
                            UndoCapture(board, opponentcapture, opponent_r, opponent_c, opponent_value, piecetag);
                        }
                        if(piece->value == 1 && orig_piecevalue == 2)
                        {
                            piece->value = 2;
                        }
                        success = 0;
                        move = 0;
                        continue;
                    }
                    else
                    {
                        if(success == 2)
                        {
                            IsCaptured = 1;
                            capturedpiece = cpy_board[opponentcapture->r][opponentcapture->c];
                        }
                        if(success != 2)
                        {
                            IsCaptured = 0;
                        }
                        if(CallPiece(board, opponent, piece, x+1, y+1, (opponent->piecelist[King]->r)+1, (opponent->piecelist[King]->c)+1, 0) == 2)
                        {
                            CheckMove = 1;
                        }
                        if(move == 0){
                            if(opponentcapture != NULL)
                            {
                                opponentcapture->r = opponent_r;
                                opponentcapture->c = opponent_c;
                                opponentcapture->value = opponent_value;
                                board->boardarray[opponent_r][opponent_c] = piecetag;
                            }
                            cpy_board[x][y] = orig_piecetag;
                            cpy_board[orig_pieceR][orig_pieceC] = "  ";
                            board->boardarray[x][y] = originaldesttag;
                            board->boardarray[orig_pieceR][orig_pieceC] = orig_piecetag;
                            piece->r = orig_pieceR;
                            piece->c = orig_pieceC;
                            AddLegalMoves(list, piece->r, piece->c, x, y, board, IsCaptured, piece, opponentcapture, cpy_board, CheckMove);
                            if(IsCaptured == 1)
                            {
                                cpy_board[x][y] = capturedpiece;
                                cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                            }
                            else
                            {
                                cpy_board[x][y] = "  ";
                                cpy_board[orig_pieceR][orig_pieceC] = orig_piecetag;
                            }
                        }
                        
                    }
                }
                move = 0;
                success = 0;
                continue;
            }
        }
        /*end for*/
    }/*end for*/
}

void AddLegalMoves(MOVELIST *list, int src_row, int src_col, int dest_row, int dest_col, BOARD *board, int IsCaptured, PIECE *piece, PIECE *opponentcapture, char *cpy_board[8][8], int CheckMove){
    /*Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move*/
    
    MOVE *new_entry = malloc(sizeof(MOVE));
    PIECE *temppiece = NULL;
    assert(new_entry);
    if(list->first == NULL){
        list->first = new_entry;
        new_entry->preventry = NULL;
        new_entry->nextentry = NULL;
        new_entry->src_row = src_row;
        new_entry->src_col = src_col;
        new_entry->dst_row = dest_row;
        new_entry->dst_col = dest_col;
        new_entry->IsCaptured = IsCaptured;
        new_entry->piece = piece;
        if(opponentcapture == NULL)
        {
            new_entry->opponentcapture = NULL;
        }
        else
        {
            new_entry->opponentcapture = opponentcapture;
        }
        new_entry->score = 0;
        new_entry->board = board;
        if(opponentcapture == NULL)
        {
            if(piece->player->color == 'w')
            {
                temppiece = CheckPiece(board->black, dest_row, dest_col);
            }
            if(piece->player->color == 'b')
            {
                temppiece = CheckPiece(board->white, dest_row, dest_col);
            }
            if(temppiece != NULL)
            {
                new_entry->EnPassantStatus = temppiece->EnPassant;
            }
        }
        if(CheckMove == 1)
        {
            new_entry->CheckMove = 1;
        }
        else
        {
            new_entry->CheckMove = 0;
        }
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                new_entry->new_board[i][j] = cpy_board[i][j];
            }
        }
        list->last = new_entry;
        new_entry -> prev_level = list;
        new_entry->next_level = NULL;
        
    }else{
        list->last->nextentry = new_entry;
        new_entry->preventry = list->last;
        new_entry->nextentry = NULL;
        list->last= new_entry;
        
        new_entry->src_row = src_row;
        new_entry->src_col = src_col;
        new_entry->dst_row = dest_row;
        new_entry->dst_col = dest_col;
        new_entry->IsCaptured = IsCaptured;
        new_entry->piece = piece;
        if(opponentcapture == NULL)
        {
            new_entry->opponentcapture = NULL;
        }
        else
        {
            new_entry->opponentcapture = opponentcapture;
        }
        new_entry->score = 0;
        new_entry->board = board;
        if(opponentcapture == NULL)
        {
            temppiece = CheckPiece(piece->player, dest_row, dest_col);
            if(temppiece != NULL)
            {
                new_entry->EnPassantStatus = temppiece->EnPassant;
            }
        }
        if(CheckMove == 1)
        {
            new_entry->CheckMove = 1;
        }
        else
        {
            new_entry->CheckMove = 0;
        }
        for(int i = 0; i < 8; i++)
        {
            for(int j = 0; j < 8; j++)
            {
                new_entry->new_board[i][j] = cpy_board[i][j];
            }
        }
        new_entry->prev_level = list;
        new_entry->next_level = NULL;
        
        
    }
    list->length++;
}

/*Cretes a move*/
MOVE *CreateMove(void){
    MOVE *move = malloc(sizeof(MOVE));
    
    return move;
}

/*Creates a movelist*/
MOVELIST *NewMoveList(void){
    MOVELIST *l;
    l = malloc(sizeof(MOVELIST));
    if (!l)
    {
        perror("\n Out of Memory! Aborting...");
        exit(10);
    }
    l->first = NULL;
    l->last = NULL;
    l->prevmove = NULL;
    l->length = 0;
    return l;
}

/*Deletes list of all possible legal moves: frees memory*/
void DeleteMoveList(MOVELIST *list){
    assert(list);
    MOVE *next;
    MOVE *temp;
    if(list->board){
        DeleteBoard(list->board);
        list->board = NULL;
    }
    if(list->first == NULL)
    {
        free(list);
        list = NULL;
    }else{
        temp = list->first;
        while(temp != NULL) {
            next = temp->nextentry;
            DeleteMoveEntry(temp);
            list->length--;
            temp = next;
        }
        free(list);
        list = NULL;
    }
}

/*Deletes a single move entry within the movelist*/
void DeleteMoveEntry(MOVE *entry){
    assert(entry);
    if (entry->next_level != NULL){
        DeleteMoveList(entry->next_level);
        entry->next_level = NULL;
    }else {
        free(entry);
        entry = NULL;
    }
}

/*Deletes a board*/
void DeleteBoard(BOARD *board){
    assert(board);
    if(board != NULL){
        DeletePlayer(board->white);
        DeletePlayer(board->black);
        board->white = NULL;
        board->black = NULL;
        free(board);
        board = NULL;
    }
    
}

/*Creates a player*/
PLAYER *CreatePlayer(char color, char type)
{
    PLAYER *newplayer = malloc(sizeof(PLAYER));
    newplayer->color = color;
    newplayer->type = type;
    for(int i = Pawn1; i <= King; i++)
    {
        newplayer->piecelist[i] = malloc(sizeof(PIECE));
    }
    return newplayer;
}

/*Deletes a player*/
void DeletePlayer(PLAYER *entry){
    assert(entry);
    for(int i = 0; i < 16; i++){
        DeletePiece(entry->piecelist[i]);
        entry->piecelist[i] = NULL;
    } /*for end*/
    free(entry);
    entry = NULL;
}

/*Deletes a piece*/
void DeletePiece(PIECE *piece){
    assert(piece);
    free(piece);
    piece = NULL;
}

void DeleteInsertedMove(MOVE *entry){
    assert(entry);
    if(entry->preventry == NULL){
        entry->nextentry->preventry = NULL;
        entry->prev_level->first = entry->nextentry;
        entry->prev_level->length--;
        entry->prev_level = NULL;
        entry->next_level = NULL;
        free(entry);
    }else if(entry->nextentry == NULL){
        entry->preventry->nextentry = NULL;
        entry->prev_level->last = entry->preventry;
        entry->prev_level->length--;
        entry->prev_level = NULL;
        entry->next_level = NULL;
        free(entry);
    }else{
        entry->preventry->nextentry = entry->nextentry;
        entry->nextentry->preventry = entry->preventry;
        entry->prev_level->length--;
        entry->prev_level = NULL;
        entry->next_level = NULL;
        free(entry);
    }
}







