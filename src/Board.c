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
    while(IsGameOver == false)
    {
        MakeMove(global, white, black);
        DrawBoard(global);
        MakeMove(global, black, white);
        DrawBoard(global);
    }
    
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

void MakeMove(BOARD *board, PLAYER *p, PLAYER *opponent)
{
    assert(p);
    if(p->type == 'a')
    {
        printf("AI's turn. \n");
        // insert function call for AI module
    }
    if(p->type == 'h')
    {
        printf("Your turn. \n");
    }
    char cCol_src;
    int row_src;
    int col_src;
    char cCol_dest;
    int row_dest;
    int col_dest;
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
    printf("Enter the location to move the piece. \n");
    scanf(" %c%d", &cCol_dest, &row_dest);
    col_dest = AlphatoNum(cCol_dest);
    while((!(col_dest >= 1 && col_dest <= 8)) || !(row_dest >= 1 && row_dest <=8))
    {
        printf("You have entered an invalid input. Please enter a different location. \n");
        scanf(" %c%d", &cCol_dest, &row_dest);
        col_dest = AlphatoNum(cCol_dest);
    }
    int callreturn = CallPiece(board, opponent, piece, row_src, col_src, row_dest, col_dest);
    while(callreturn == 1)
    {
        printf("Invalid move. \n");
        printf("Please enter a different location. \n");
        scanf(" %c%d", &cCol_dest, &row_dest);
        col_dest = AlphatoNum(cCol_dest);
        piece = CheckPiece(p, row_src, col_src);
        callreturn = CallPiece(board, opponent, piece, row_src, col_src, row_dest, col_dest);
    }
    MovePiece(board, opponent, piece, row_dest-1, col_dest-1);
    
    
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
    char *temp = board->boardarray[piece->r][piece->c];
    board->boardarray[newr][newc] = temp;
    board->boardarray[piece->r][piece->c] = "  ";
    piece->r = newr;
    piece->c = newc;
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
    for(int i = 0; i < 16; i++)
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
    board->boardarray[piece->r][piece->c] = "  ";
    piece->r = 9; // 9 = off board
    piece->c = 9; // 9 = off board
    piece->value = 0;
    piece = NULL;

}
FILE *Log(char color, char piecetype, char destcol, int destrow, int isCaptured)
{
    FILE *log = fopen("Chess Move Log.txt", "a");
    char *color_string;
    if(color == 'w')
    {
       color_string = "White";
    }
    else
    {
        color_string = "Black";
    }
    if(isCaptured == 1)
    {
        if(piecetype == 'P')
        {
            fprintf(log, "%s: x%c%d\n", color_string, destcol, destrow);
        }
        else
        {
            fprintf(log, "%s: %cx%c%d\n", color_string, piecetype, destcol, destrow);
        }
    }
    else
    {
        if(piecetype == 'P')
        {
            fprintf(log, "%s: %c%d\n", color_string, destcol, destrow);
        }
        else
        {
            fprintf(log, "%s: %c%c%d\n", color_string, piecetype, destcol, destrow);
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
int Check(BOARD *board, PLAYER *player, PLAYER *opponent, int king_row, int king_col)
{
    int piecereturn = 0;
    for(int i = 0; i < 16; i++)
    {
        piecereturn = CallPiece(board, opponent, player->piecelist[i], player->piecelist[i]->r, player->piecelist[i]->c, king_row, king_col);
        if(piecereturn == 2)
        {
            return 1; // king is in check automatically
        }
    }
    return 0;
}
