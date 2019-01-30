//  Board.c
//  Chess
//
//  First release was created by Armand Ahadi-Sarkani on 1/16/19.
//  Copyright © 2019 Armand Ahadi-Sarkani. All rights reserved.
//

#include "Board.h"
#include "Pieces.h"

int main()
{
    char *mainboard[8][8];
    PLAYER *white = malloc(sizeof(PLAYER));
    white->color = 'w';
    PLAYER *black = malloc(sizeof(PLAYER));
    black->color = 'b';
    char human_color;
    printf("Which color would you like to be? \n");
    printf("(w = white, b = black) \n");
    scanf(" %c", &human_color);
    BOARD *global;
    if(human_color == 'w' || human_color == 'W')
    {
        printf("You are the white player. \n");
        white->type = 'h';
        white->color = 'w';
        black->type = 'a';
        global = CreateBoard(white, black, mainboard);
        
    }
    else
    {
        printf("You are the black player. \n");
        black->type = 'h';
        white->type = 'a';
        global = CreateBoard(white, black, mainboard);
        
    }
    InitializeBoard(global);
    bool IsGameOver = false; // replace with win condition checking functions in modules TBD
    DrawBoard(global);
    int move = 0;
    while(IsGameOver == false)
    {
        if(white->type == 'h')
        {
            printf("Your turn!\n");
        }
        move = MakeMove(global, white, black);
        DrawBoard(global);
        //if(Check(global, white, black, (black->piecelist[King]->r)+1, (black->piecelist[King]->c)+1) == 1)
        if(move == 1 || move == 2)
        {
            //if(Checkmate(global, white, black) == 1) // if black is in checkmate
            if(move == 2)
            {
                printf("Game over! White wins by checkmate!\n");
                return 0;
            }
            else
            {
                printf("You are in check!\n");
                
            }
        }
        if(black->type == 'h')
        {
            printf("Your turn!\n");
        }
        move = MakeMove(global, black, white);
        DrawBoard(global);
        //if(Check(global, black, white, (white->piecelist[King]->r)+1, (white->piecelist[King]->c)+1) == 1)
        if(move == 1 || move == 2)
        {
            //if(Checkmate(global, black, white) == 1) // if white is in checkmate
            if(move == 2)
            {
                printf("Game over! Black wins by checkmate!\n");
                return 0;
            }
            else
            {
                printf("You are in check!\n");
                
            }
        }
    }
    return 0;
    
}

void InitializeBoard(BOARD *board)
{
    // White is by default the player that initially occupies first two rows, black is by default the player that initially occupies the top two rows
    // White and 2 initial pawns
    int pawncol = 0;
    for(int pawn = Pawn1; pawn <= Pawn8; pawn++)
    {
        board->white->piecelist[pawn] = CreatePiece(board, 1, pawncol, 'P', 'w', board->white);
        board->black->piecelist[pawn] = CreatePiece(board, 6, pawncol, 'P', 'b', board->black);
        pawncol++;
    }
    // White initial non-pawn pieces
    board->white->piecelist[Rook1] = CreatePiece(board, 0, 0, 'R', 'w', board->white);
    board->white->piecelist[Rook2] = CreatePiece(board, 0, 7, 'R', 'w', board->white);
    board->white->piecelist[Knight1] = CreatePiece(board, 0, 1, 'N', 'w', board->white);
    board->white->piecelist[Knight2] = CreatePiece(board, 0, 6, 'N', 'w', board->white);
    board->white->piecelist[Bishop1] = CreatePiece(board, 0, 2, 'B', 'w', board->white);
    board->white->piecelist[Bishop2] = CreatePiece(board, 0, 5, 'B', 'w', board->white);
    board->white->piecelist[Queen] = CreatePiece(board, 0, 3, 'Q', 'w', board->white);
    board->white->piecelist[King] = CreatePiece(board, 0, 4, 'K', 'w', board->white);
    // player 2 initial pieces
    board->black->piecelist[Rook1] = CreatePiece(board, 7, 0, 'R', 'b', board->black);
    board->black->piecelist[Rook2] = CreatePiece(board, 7, 7, 'R', 'b', board->black);
    board->black->piecelist[Knight1] = CreatePiece(board, 7, 1, 'N', 'b', board->black);
    board->black->piecelist[Knight2] = CreatePiece(board, 7, 6, 'N', 'b', board->black);
    board->black->piecelist[Bishop1] = CreatePiece(board, 7, 2, 'B', 'b', board->black);
    board->black->piecelist[Bishop2] = CreatePiece(board, 7, 5, 'B', 'b', board->black);
    board->black->piecelist[Queen] = CreatePiece(board, 7, 3, 'Q', 'b', board->black);
    board->black->piecelist[King] = CreatePiece(board, 7, 4, 'K', 'b', board->black);
    for(int i = 5; i >= 2; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            board->boardarray[i][j] = "  ";
        }
    }
}

void DrawBoard(BOARD *board)
{
    int cols = 0;
    for(int i = 8; i >= 1; i--)
    {
        printf("  +------+------+------+------+------+------+------+------+\n");
        printf("%d |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", i, board->boardarray[i-1][0], board->boardarray[i-1][1], board->boardarray[i-1][2], board->boardarray[i-1][3], board->boardarray[i-1][4], board->boardarray[i-1][5], board->boardarray[i-1][6], board->boardarray[i-1][7]);
        cols++;
    }
    printf("  +------+------+------+------+------+------+------+------+\n");
    printf("      a      b      c      d      e      f      g      h   \n");
}

int MakeMove(BOARD *board, PLAYER *p, PLAYER *opponent)
{
    int EXIT = 0;
    while(EXIT == 0)
    {
        assert(p);
        char cCol_src;
        int row_src;
        int col_src;
        char cCol_dest;
        int row_dest;
        int col_dest;
        char *piecetag = NULL;
        PIECE *opponentcapture = NULL;
        int opponent_r = 0;
        int opponent_c = 0;
        int opponent_value = 0;
        printf("Enter the location of the piece you wish to move. \n");
        scanf(" %c%d", &cCol_src, &row_src);
        col_src = AlphatoNum(cCol_src);
        while((!(col_src >= 1 && col_src <= 8)) || !(row_src >= 1 && row_src <=8))
        {
            printf("You have entered an invalid input. Please enter a different location. \n");
            scanf(" %c%d", &cCol_src, &row_src);
            col_src = AlphatoNum(cCol_src);
        }
        while(CheckPiece(p, row_src, col_src) == NULL)
        {
            printf("You have made an invalid move. Please enter a different location. \n");
            scanf(" %c%d", &cCol_src, &row_src);
            col_src = AlphatoNum(cCol_src);
        }
        PIECE *piece = CheckPiece(p, row_src, col_src);
        int original_piece_value = piece->value;
        int illegalmoves = CheckNumberofIllegalMoves(board, opponent, piece, row_src, col_src);
        if(illegalmoves == 64)
        {
            printf("You have selected a piece that currently has no legal moves to make. Please try again.\n");
            continue;
        }
        printf("Enter the location to move the piece. \n");
        scanf(" %c%d", &cCol_dest, &row_dest);
        col_dest = AlphatoNum(cCol_dest);
        while((!(col_dest >= 1 && col_dest <= 8)) || !(row_dest >= 1 && row_dest <=8))
        {
            printf("You have entered an invalid input. Please enter a different location. \n");
            scanf(" %c%d", &cCol_dest, &row_dest);
            col_dest = AlphatoNum(cCol_dest);
        }
        if(CheckPiece(opponent, row_dest, col_dest) != NULL)
        {
            opponentcapture = CheckPiece(opponent, row_dest, col_dest);
            piecetag = board->boardarray[opponentcapture->r][opponentcapture->c];
            opponent_r = opponentcapture->r;
            opponent_c = opponentcapture->c;
            opponent_value = opponentcapture->value;
        }
        int callreturn = CallPiece(board, opponent, piece, row_src, col_src, row_dest, col_dest, 1);
        while(callreturn == 1)
        {
            printf("Invalid move. \n");
            printf("Please enter a different location. \n");
            scanf(" %c%d", &cCol_dest, &row_dest);
            col_dest = AlphatoNum(cCol_dest);
            piece = CheckPiece(p, row_src, col_src);
            callreturn = CallPiece(board, opponent, piece, row_src, col_src, row_dest, col_dest, 1);
        }
        char *originalpiecetag = board->boardarray[piece->r][piece->c];
        int movereturn = MovePiece(board, opponent, piece, row_dest-1, col_dest-1);
        if(movereturn == 1)
        {
            printf("You cannot make a move that will leave you in check. Please try again. \n");
            if(callreturn == 2)
            {
                UndoCapture(board, opponentcapture, opponent_r, opponent_c, opponent_value, piecetag);
            }
            if(piece->value == 1 && original_piece_value == 2)
            {
                piece->value = 2;
            }
            continue;
        }
        EXIT = 1;
        FILE *log;
        int CheckReturn = 0;
        if(Checkmate(board, p, opponent) == 1)
        {
            CheckReturn = 2;
        }
        else if(Check(board, p, opponent, (opponent->piecelist[King]->r)+1, (opponent->piecelist[King]->c)+1) == 1)
        {
            CheckReturn = 1;
        }
        board->boardarray[piece->r][piece->c] = originalpiecetag;
        if(callreturn == 2) // a piece has been captured
        {
            log = Log(p->color, piece->piecetype, cCol_dest, row_dest, 1, CheckReturn);
        }
        else
        {
            log = Log(p->color, piece->piecetype, cCol_dest, row_dest, 0, CheckReturn);
        }
        if(CheckReturn == 2)
        {
            return 2;
        }
        else if(CheckReturn == 1)
        {
            return 1;
        }
        return 0;
    }
    return 0;
    
}

PIECE *CreatePiece(BOARD *board, int r, int c, char piece, char color, PLAYER *player)
{
    PIECE *p = malloc(sizeof(PIECE));
    p->piecetype = piece;
    p->player = player;
    p->r = r;
    p->c = c;
    if(color == 'w')
    {
        if(piece == 'P') {board->boardarray[r][c] = "wP";}
        if(piece == 'R') {board->boardarray[r][c] = "wR";}
        if(piece == 'K') {board->boardarray[r][c] = "wK";}
        if(piece == 'Q') {board->boardarray[r][c] = "wQ";}
        if(piece == 'N') {board->boardarray[r][c] = "wN";}
        if(piece == 'B') {board->boardarray[r][c] = "wB";}
    }
    if(color == 'b')
    {
        if(piece == 'P') {board->boardarray[r][c] = "bP";}
        if(piece == 'R') {board->boardarray[r][c] = "bR";}
        if(piece == 'K') {board->boardarray[r][c] = "bK";}
        if(piece == 'Q') {board->boardarray[r][c] = "bQ";}
        if(piece == 'N') {board->boardarray[r][c] = "bN";}
        if(piece == 'B') {board->boardarray[r][c] = "bB";}
    }
    switch(piece)
    {
        case 'P':
            p->value = 2; // initial value 2, then goes down to 1 after first move of a pawn to up to 2 spaces
            break;
        case 'N':
            p->value = 3;
            break;
        case 'B':
            p->value = 3;
            break;
        case 'R':
            p->value = 5;
            break;
        case 'Q':
            p->value = 9;
            break;
        case 'K':
            p->value = 90; //should really be infinity
            break;
        default:
            break;
    }
    return p;
}
int MovePiece(BOARD *board, PLAYER *opponent, PIECE *piece, int newr, int newc) // only called when the move is legal
{
    assert(piece);
    int tempR = piece->r;
    int tempC = piece->c;
    char *temp = board->boardarray[piece->r][piece->c];
    board->boardarray[newr][newc] = temp;
    board->boardarray[piece->r][piece->c] = "  ";
    piece->r = newr;
    piece->c = newc;
    if(Check(board, opponent, piece->player, (piece->player->piecelist[King]->r)+1, (piece->player->piecelist[King]->c)+1) == 1)
    {
        board->boardarray[newr][newc] = "  ";
        board->boardarray[tempR][tempC] = temp;
        piece->r = tempR;
        piece->c = tempC;
        return 1;
    }
    return 0;
}
int AlphatoNum(char alpha)
{
    int num = 0;
    switch(alpha)
    {
        case 'a':
            num = 1;
            break;
        case 'A':
            num = 1;
            break;
        case 'b':
            num = 2;
            break;
        case 'B':
            num = 2;
            break;
        case 'c':
            num = 3;
            break;
        case 'C':
            num = 3;
            break;
        case 'd':
            num = 4;
            break;
        case 'D':
            num = 4;
            break;
        case 'e':
            num = 5;
            break;
        case 'E':
            num = 5;
            break;
        case 'f':
            num = 6;
            break;
        case 'F':
            num = 6;
            break;
        case 'g':
            num = 7;
            break;
        case 'G':
            num = 7;
            break;
        case 'h':
            num = 8;
            break;
        case 'H':
            num = 8;
            break;
        default:
            num = 9;
            break;
    }
    return num;
}

PIECE *CheckPiece(PLAYER *p, int r, int c) // check if its your piece in a particular location
{
    assert(p);
    for(int i = Pawn1; i <= King; i++)
    {
        int rx = p->piecelist[i]->r;
        int cx = p->piecelist[i]->c;
        if((rx == r-1) && (cx == c-1))
        {
            PIECE *piece = p->piecelist[i];
            return piece;
        }
    }
    return NULL;
}

int FindEmptySpace(BOARD *board, int r, int c)
{
    if(strcmp(board->boardarray[r-1][c-1], "  ") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void CapturePiece(BOARD *board, PIECE *piece)
{
    if(piece->piecetype != 'K')
    {
        board->boardarray[piece->r][piece->c] = "  ";
        piece->r = 9; // 9 = off board
        piece->c = 9; // 9 = off board
        piece->value = 0;
        piece = NULL;
    }
    
}
void UndoCapture(BOARD *board, PIECE *opponentcapture, int opponent_r, int opponent_c, int opponent_value, char *piecetag)
{
    board->boardarray[opponent_r][opponent_c] = piecetag;
    opponentcapture->r = opponent_r;
    opponentcapture->c = opponent_c;
    opponentcapture->value = opponent_value;
}
FILE *Log(char color, char piecetype, char destcol, int destrow, int isCaptured, int CheckReturn)
{
    FILE *log = fopen("Chess Move Log.txt", "a");
    char *color_string;
    char check_char = '\0';
    if(color == 'w')
    {
        color_string = "White";
    }
    else
    {
        color_string = "Black";
    }
    if(CheckReturn == 1)
    {
        check_char = '+';
    }
    else if(CheckReturn == 2)
    {
        check_char = '#';
    }
    if(isCaptured == 1)
    {
        if(piecetype == 'P')
        {
            fprintf(log, "%s: x%c%d%c\n", color_string, destcol, destrow, check_char);
        }
        else
        {
            fprintf(log, "%s: %cx%c%d%c\n", color_string, piecetype, destcol, destrow, check_char);
        }
    }
    else
    {
        if(piecetype == 'P')
        {
            fprintf(log, "%s: %c%d%c\n", color_string, destcol, destrow, check_char);
        }
        else
        {
            fprintf(log, "%s: %c%c%d%c\n", color_string, piecetype, destcol, destrow, check_char);
        }
    }
    fclose(log);
    return log;
}

BOARD *CreateBoard(PLAYER *white, PLAYER *black, char *boardarray[8][8])
{
    BOARD *board = malloc(sizeof(BOARD));
    board->white = white;
    board->black = black;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board->boardarray[i][j] = boardarray[i][j];
        }
    }
    return board;
}
PLAYER *CreatePlayer(char color, char type)
{
    PLAYER *newplayer = malloc(sizeof(PLAYER));
    newplayer->color = color;
    newplayer->type = type;
    for(int i = Pawn1; i < King; i++)
    {
        newplayer->piecelist[i] = malloc(sizeof(PIECE));
    }
    return newplayer;
}
int Check(BOARD *board, PLAYER *player, PLAYER *opponent, int king_row, int king_col)
{
    int piecereturn = 0;
    for(int i = Pawn1; i <= King; i++)
    {
        piecereturn = CallPiece(board, opponent, player->piecelist[i], (player->piecelist[i]->r)+1, (player->piecelist[i]->c)+1, king_row, king_col, 0);
        if(piecereturn == 2)
        {
            return 1; // king is in check automatically
        }
    }
    return 0;
}
int CheckNumberofIllegalMoves(BOARD *board, PLAYER *opponent, PIECE *piece, int row_src, int col_src)
{
    int counter = 0;
    for(int i = 1; i <= 8; i++)
    {
        for(int j = 1; j <= 8; j++)
        {
            if(CallPiece(board, opponent, piece, row_src, col_src, i, j, 0) == 1)
            {
                counter++;
            }
        }
    }
    return counter;
}
int Checkmate(BOARD *board, PLAYER *player, PLAYER *opponent)
{
    for(int i = Pawn1; i <= King; i++)
    {
        PIECE *piece = opponent->piecelist[i];
        int originalR = piece->r;
        int originalC = piece->c;
        char *originalpiecetag = board->boardarray[piece->r][piece->c];
        int original_piece_value = piece->value;
        int movereturn = 0;
        if(piece->value == 0) // captured piece cannot be moved to save the king
        {
            continue;
        }
        for(int j = 0; j < 8; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                int IsLegalMove = CallPiece(board, player, piece, (piece->r)+1, (piece->c)+1, j+1, k+1, 0); // can the opponent make a legal move?
                if(IsLegalMove == 1)
                {
                    continue;
                }
                else // if so, can that legal move get them out of check?
                {
                    char *originaldesttag = board->boardarray[j][k];
                    movereturn = MovePiece(board, player, piece, j, k);
                    if(movereturn == 1)
                    {
                        if(IsLegalMove == 2) // resetting captures and value updates
                        {
                            PIECE *opponentcapture = CheckPiece(player, j+1, k+1);
                            char *piecetag = board->boardarray[opponentcapture->r][opponentcapture->c];
                            int opponent_r = opponentcapture->r;
                            int opponent_c = opponentcapture->c;
                            int opponent_value = opponentcapture->value;
                            UndoCapture(board, opponentcapture, opponent_r, opponent_c, opponent_value, piecetag);
                        }
                        if(piece->value == 1 && original_piece_value == 2)
                        {
                            piece->value = 2;
                        }
                    }
                    else
                    {
                        board->boardarray[j][k] = originaldesttag;
                        board->boardarray[originalR][originalC] = originalpiecetag;
                        piece->r = originalR;
                        piece->c = originalC;
                        return 0;
                    }
                    
                }
                
            }
        }
    }
    return 1;
}
