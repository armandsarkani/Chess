#include "Evaluate.h"
/*Copyright Benny Lin*/
/* Last modified 2/6/2019*/

/*Passes a move entry. Move entry is accessed. Data( row, col, new_board) is used to evaluate ce
 Calls all other functions and sums the subscores for a final score
 Returns final score */

/*PIECE SQUARE TABLE*/

const int PawnTable[64] = {
    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,
    10    ,    10    ,    0    ,    -10    ,    -10    ,    0    ,    10    ,    10    ,
    5    ,    0    ,    0    ,    5    ,    5    ,    0    ,    0    ,    5    ,
    0    ,    0    ,    10    ,    20    ,    20    ,    10    ,    0    ,    0    ,
    50    ,    5    ,    5    ,    20    ,    20    ,    5    ,    5    ,    50    ,
    10    ,    30    ,    10    ,    50    ,    50    ,    15    ,    15    ,    15   ,
    10    ,    10    ,    20    ,    20    ,    20    ,    20    ,    10    ,    10    ,
    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0
};

const int KnightTable[64] = {
    0    ,    -10    ,    0    ,    0    ,    0    ,    0    ,    -10    ,    0    ,
    0    ,    0    ,    0    ,    5    ,    5    ,    0    ,    0    ,    0    ,
    0    ,    0    ,    10    ,    10    ,    10    ,    10    ,    0    ,    0    ,
    0    ,    0    ,    10    ,    20    ,    20    ,    10    ,    5    ,    0    ,
    5    ,    10    ,    15    ,    20    ,    20    ,    15    ,    10    ,    5    ,
    5    ,    10    ,    10    ,    20    ,    20    ,    10    ,    10    ,    5    ,
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0    ,
    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0
};

const int BishopTable[64] = {
    0    ,    0    ,    -10    ,    0    ,    0    ,    -10    ,    0    ,    0    ,
    0    ,    0    ,    0    ,    10    ,    10    ,    0    ,    0    ,    0    ,
    0    ,    0    ,    10    ,    15    ,    15    ,    10    ,    0    ,    0    ,
    0    ,    10    ,   15    ,    20    ,    20    ,    15    ,    10    ,    0    ,
    0    ,    10    ,   15    ,    20    ,    20    ,    15    ,    10    ,    0    ,
    0    ,    0    ,    10    ,    15    ,    15    ,    10    ,    0    ,    0    ,
    0    ,    0    ,    0    ,    10    ,    10    ,    0    ,    0    ,    0    ,
    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0
};

const int Bishop1Table[64] = {
    0    ,    0    ,    -10   ,    0    ,    0    ,    -10   ,    0    ,    0    ,
    0    ,    0    ,    0    ,    10    ,    10    ,    0    ,    0    ,    0    ,
    0    ,    0    ,    10   ,    15    ,    15    ,    10   ,    0    ,    0    ,
    0    ,    10   ,    15   ,    20    ,    20    ,    15   ,    10    ,    0    ,
    0    ,    10   ,    15   ,    20    ,    20    ,    15   ,    10    ,    0    ,
    0    ,    0    ,    10   ,    15    ,    15    ,    10   ,    0    ,    0    ,
    0    ,    0    ,    0    ,    10    ,    10    ,    0    ,    0    ,    0    ,
    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0    ,    0
};

const int RookTable[64] = {
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0    ,
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0    ,
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0    ,
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0    ,
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0    ,
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0    ,
    25    ,    25    ,    25    ,    25    ,    25    ,    25    ,    25    ,    25    ,
    0    ,    0    ,    5    ,    10    ,    10    ,    5    ,    0    ,    0
};

const int KingE[64] = {    /*PLAYER KING*/
    -50    ,    -10    ,    0    ,    0    ,    0    ,    0    ,    -10    ,    -50    ,
    -10,    0    ,    10    ,    10    ,    10    ,    10    ,    0    ,    -10    ,
    0    ,    10    ,    20    ,    20    ,    20    ,    20    ,    10    ,    0    ,
    0    ,    10    ,    20    ,    40    ,    40    ,    20    ,    10    ,    0    ,
    0    ,    10    ,    20    ,    40    ,    40    ,    20    ,    10    ,    0    ,
    0    ,    10    ,    20    ,    20    ,    20    ,    20    ,    10    ,    0    ,
    -10,    0    ,    10    ,    10    ,    10    ,    10    ,    0    ,    -10    ,
    -50    ,    -10    ,    0    ,    0    ,    0    ,    0    ,    -10    ,    -50
};

const int KingO[64] = {    /*AI KING*/
    0    ,    5    ,    5    ,    -10    ,    -10    ,    0    ,    10    ,    5    ,
    -30    ,    -30    ,    -30    ,    -30    ,    -30    ,    -30    ,    -30    ,    -30    ,
    -50    ,    -50    ,    -50    ,    -50    ,    -50    ,    -50    ,    -50    ,    -50    ,
    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,
    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,
    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,
    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,
    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70    ,    -70
};


/*END TABLES*/

int scoremove(MOVE *origmove, PLAYER *player, PLAYER *opponent) {/* PArent function*/
    int i;
    int score = 0;
    int piece_tracker = 0;
    PIECE *piece = NULL;
    PLAYER *white, *black;
    BOARD *board;
    if (player->color == 'w') {/* WHo is white and who is black*/
        board = CreateAIBoard(player, opponent, origmove->new_board);
    }
    else {
        board = CreateAIBoard(opponent, player, origmove->new_board);
    }
    
    white = board->white;
    black = board->black;
    
    for (i = 0; i < 16; i++) {
        // trying to copy movelist with that move made
        white->piecelist[i]->player = origmove->next_level->board->white;
        white->piecelist[i]->piecetype = origmove->prev_level->board->white->piecelist[i]->piecetype;
        white->piecelist[i]->c = origmove->prev_level->board->white->piecelist[i]->c;
        white->piecelist[i]->r = origmove->prev_level->board->white->piecelist[i]->r;
        white->piecelist[i]->value = origmove->prev_level->board->white->piecelist[i]->value;
        
        if (((white->piecelist[i]->r) == (origmove->src_row)) && ((white->piecelist[i]->c) == origmove->src_col)) {
            
            white->piecelist[i]->r = origmove->dst_row;
            white->piecelist[i]->c = origmove->dst_col;
            //Moves piece in data list
        }
        black->piecelist[i]->player = origmove->next_level->board->black;
        black->piecelist[i]->piecetype = origmove->prev_level->board->black->piecelist[i]->piecetype;
        black->piecelist[i]->c = origmove->prev_level->board->black->piecelist[i]->c;
        black->piecelist[i]->r = origmove->prev_level->board->black->piecelist[i]->r;
        black->piecelist[i]->value = origmove->prev_level->board->black->piecelist[i]->value;
        
        if (((black->piecelist[i]->r) == (origmove->src_row)) && ((black->piecelist[i]->c) == origmove->src_col)) {
            black->piecelist[i]->r = origmove->dst_row;
            black->piecelist[i]->c = origmove->dst_col;
        }//Moves Piece in data list
    }
    for (i = 0; i < 16; i++)
    {
        if (piece != NULL)
        {
            if (piece->player == white)
            {
                if (white->piecelist[i]->r == origmove->dst_row && white->piecelist[i]->c == origmove->dst_col)
                {
                    white->piecelist[i]->r = 9;
                    white->piecelist[i]->c = 9;
                    white->piecelist[i]->value = 0;
                    
                }
            }
            else if (piece->player == black)
            {
                if (black->piecelist[i]->r == origmove->dst_row && black->piecelist[i]->c == origmove->dst_col)
                {
                    black->piecelist[i]->r = 9;
                    black->piecelist[i]->c = 9;
                    black->piecelist[i]->value = 0;
                }
            }
        }
    }
    
    if (player->color == white->color) {
        score = EvaluatePosition(origmove, white->piecelist[piece_tracker], board, white, black);
    }
    else {
        score = EvaluatePosition(origmove, black->piecelist[piece_tracker], board, black, white);
    }
    DeleteBoard(board);
    return score;
}

int CheckKillerMoves(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board) {
    int i, x, y;
    
    int dst_row = move->dst_row;
    int dst_col = move->dst_col;
    int result;
    
    int new_temp_score = 0;
    int temp_score = 0;
    int score = 0;
    
    int pos;
    int pos_score;
    
    
    PLAYER *prev_playerpos = NULL;
    PLAYER *player = piece->player;
    
    switch (opponent->color) {
        case 'w':
            prev_playerpos = move->prev_level->board->white;
            break;
        case 'b':
            prev_playerpos = move->prev_level->board->black;
            break;
    }
    
    
    PIECE *piececaptured = NULL;
    PIECE *opponent_p = NULL;
    /*make the move using CallPiece*/
    for (i = 0; i < 16; i++) {
        opponent_p = opponent->piecelist[i];
        if (opponent_p->r == 9) {
            continue;
        }
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                result = CallPiece(new_board, player, opponent_p, x + 1, y + 1, dst_row + 1, dst_col + 1, 0);
                if (result == 2) { /*see if the piece captures another piece*/
                    score = score + (piece->value) + 3 * (opponent_p->value); /*add the value to the score*/
                    if (piece->piecetype == 'K') {
                        score = score + (piececaptured->value);
                    }
                    
                }/*if end*/
            }
        }
    }
    /*TO LOOK AHEAD AFTER A PIECE CAPTURES:*/
    /*scan new_board in the passed in move*/
    /*once not null use checkpiece to find out which piece it is*/
    /*get legal moves of that piece (have to edit the for loops and stuff below)*/
    PIECE *new_piece;
    for (i = 0; i <= 15; i++) {
        new_piece = opponent->piecelist[i];
        if (new_piece->r == 9) {
            continue;
        }
        
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                piececaptured = CheckPiece(player, x + 1, y + 1);
                result = CallPiece(new_board, player, new_piece, (new_piece->r) + 1, (new_piece->c) + 1, x + 1, y + 1, 0);
                if (result == 2) { /*if player piece returns a capture*/
                    piececaptured = CheckPiece(player, x + 1, y + 1);
                    pos = BoardtoPSQTable(x, y);
                    pos_score = ReturnPosScore(new_piece->piecetype, pos, new_piece);
                    /*FInal formula needs more work*/
                    temp_score = pos_score + (piececaptured->value) + (new_piece->value);
                    temp_score = temp_score / 4;
                    new_temp_score = new_temp_score + temp_score;
                }
            }
        }
        /*end for*/
    }/*end for*/
    score = score + new_temp_score;
    return score;
} /*EOF*/

int CheckCaptureMoves(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board) {
    int x, y;
    int src_row = move->src_row;
    int src_col = move->src_col;
    int dst_row = move->dst_row;
    int dst_col = move->dst_col;
    int result;
    
    int new_temp_score = 0;
    int temp_score;
    int score = 0;
    
    int pos;
    int pos_score;
    
    BOARD *old_board = move->prev_level->board;
    
    PLAYER *prev_opponentpos = NULL;
    PLAYER *player = piece->player;
    
    switch (opponent->color) {
        case 'w':
            prev_opponentpos = move->prev_level->board->white;
            break;
        case 'b':
            prev_opponentpos = move->prev_level->board->black;
            break;
    }
    
    
    PIECE *piececaptured = NULL;
    
    /*make the move using CallPiece*/
    result = CallPiece(old_board, prev_opponentpos, piece, src_row + 1, src_col + 1, dst_row + 1, dst_col + 1, 0);
    if (result == 2) { /*see if the piece captures another piece*/
        piececaptured = CheckPiece(prev_opponentpos, dst_row + 1, dst_col + 1); /*find out what piece it captured*/
        score = 40 * (piececaptured->value) + 10 * (piece->value); /*add the value to the score*/
        if (piece->piecetype == 'K') {
            score = 40 * (piececaptured->value) + (piece->value);
        }
    }/*if end*/
    /*TO LOOK AHEAD AFTER A PIECE CAPTURES:*/
    /*scan new_board in the passed in move*/
    /*once not null use checkpiece to find out which piece it is*/
    /*get legal moves of that piece (have to edit the for loops and stuff below)*/
    PIECE *new_piece;
    int i;
    for (i = 8; i <= 14; i++) {
        new_piece = player->piecelist[i];
        if (new_piece->r == 9) {
            continue;
        }
        for (x = 0; x < 8; x++) {
            for (y = 0; y < 8; y++) {
                piececaptured = CheckPiece(opponent, x + 1, y + 1);
                result = CallPiece(new_board, opponent, new_piece, (new_piece->r) + 1, (new_piece->c) + 1, x + 1, y + 1, 0);
                if (result == 2) { /*if player piece returns a capture*/
                    piececaptured = CheckPiece(opponent, x + 1, y + 1);
                    pos = BoardtoPSQTable(x, y);
                    pos_score = ReturnPosScore(new_piece->piecetype, pos, new_piece);
                    temp_score = pos_score + (piececaptured->value) + 8 * (new_piece->value);
                    temp_score = temp_score / 4;
                    new_temp_score = new_temp_score + temp_score;
                }
            }
        }
        /*end for*/
    }/*end for*/
    score = score + new_temp_score;
    return score;
} /*EOF*/


int EvaluatePosition(MOVE *move, PIECE *piece, BOARD *board, PLAYER *player, PLAYER *opponent) {
    int x, y, pos;
    int base_score, final_score;
    x = move->dst_row;
    y = move->dst_col;
    
    pos = BoardtoPSQTable(x, y);
    
    char piecetype = piece->piecetype;
    base_score = ReturnPosScore(piecetype, pos, piece);
    if (move->opponentcapture != NULL) {
        final_score = base_score - CheckKillerMoves(move, piece, opponent, board) + CheckCaptureMoves(move, piece, opponent, board) +
        CheckBeyondPiece(move, piece, opponent, board) + (move->opponentcapture->value) + 300*CheckPawnOutPost(move) +
        100*CheckCapturePosition(move);
        /*if( piece->piecetype == 'K'){
         //final_score = 0*base_score - 0*CheckKillerMoves(move, piece, opponent, board) + 0*CheckCaptureMoves(move, piece, opponent, board) + CheckBeyondPiece(move, piece, opponent, board) + 0*(move->opponentcapture->value);
         final_score = -final_score;
         
         }*/
    }
    else {
        final_score = base_score - CheckKillerMoves(move, piece, opponent, board) +
        CheckCaptureMoves(move, piece, opponent, board) + CheckBeyondPiece(move, piece, opponent, board) + 300*CheckPawnOutPost(move);
        /*if( piece->piecetype == 'K'){
         //final_score = 0*base_score - 0*CheckKillerMoves(move, piece, opponent, board) + 0*CheckCaptureMoves(move, piece, opponent, board) + CheckBeyondPiece(move, piece, opponent, board);
         final_score = -final_score;
         }*/
    }
    return final_score;
}

int CheckBeyondPiece(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board) {
    /* IF WE HAVE TIME*/
    return 0;
}


int ReturnPosScore(char piecetype, int pos, PIECE *piece) {
    int score = 0;
    switch (piecetype) {
        case 'P':
            //score = 1;
            score = PawnTable[pos];
            break;
        case 'R':
            //score = 3;
            score = RookTable[pos];
            break;
        case 'N':
            //score = 3;
            score = KnightTable[pos];
            break;
        case 'K':
            if (piece->player->type == 'h') {
                score = KingE[pos];
            }
            else {
                score = KingO[pos];
            }
            break;
        case 'B':
            //score = 1;
            score = Bishop1Table[pos];
            break;
        case 'Q':
            //score = 2;
            score =  BishopTable[pos];
            break;
    }
    return score;
}

int BoardtoPSQTable(int row, int col) {
    int pos;
    pos = (row - 1) * 8 + (col - 1);
    return pos;
}

int CheckCapturePosition(MOVE *move) {
    PLAYER *player, *opponent;
    player = move->piece->player;
    opponent = move->opponentcapture->player;
    PIECE *opiece;
    int result;
    int success = 0;
    
    for (int i = 0; i < 15; i++) {
        opiece = opponent->piecelist[i];
        if (opiece->r == 9) {
            continue;
        }
        result = CallPiece(move->board, player, opiece, move->src_row + 1, move->src_col + 1, move->dst_row + 1, move->dst_col + 1, 0);
        if (result == 1) {
            if(opiece->piecetype == 'P'){
                return 0;
            }
            if (move->opponentcapture->value >= move->piece->value) {
                if (move->piece->piecetype == 'P') {
                    if (move->opponentcapture->value == 1) {
                        success = 0;
                    }
                    else {
                        success = 1;
                    }
                }
                else {
                    success = 1;
                }
            }
            else {
                success = 0;
            }
        }
    }
    return success;
}

int CheckPawnOutPost(MOVE *move) {
    PLAYER *player;
    player = move->piece->player;
    PIECE *pawn = NULL;
    int i;
    for (i = 0; i < 8; i++) {
        pawn = player->piecelist[i];
        if (pawn->r == 9) {
            continue;
        }
        if (player->color == 'w') {
            if ((move->dst_row == pawn->r + 1) && ((move->dst_col == pawn->c - 1) || (move->dst_col == pawn->c + 1))) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            if ((move->dst_row == pawn->r - 1) && ((move->dst_col == pawn->c - 1) || (move->dst_col == pawn->c + 1))) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}

int CheckOppPawnCapture(MOVE *move) {
    if (move->piece->piecetype == 'P') {
        return 0;
    }
    PLAYER *player, *opponent;
    player = move->piece->player;
    if (player->color == 'w') {
        opponent = move->board->black;
    }
    else {
        opponent = move->board->white;
    }
    PIECE *pawn = NULL;
    int i;
    for (i = 0; i < 8; i++) {
        pawn = opponent->piecelist[i];
        if (pawn->r == 9) {
            continue;
        }
        if (player->color == 'w') {
            if ((move->dst_row == pawn->r - 1) && ((move->dst_col == pawn->c - 1) || (move->dst_col == pawn->c + 1))) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            if ((move->dst_row == pawn->r + 1) && ((move->dst_col == pawn->c - 1) || (move->dst_col == pawn->c + 1))) {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    return 0;
}
