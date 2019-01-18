#include "Board.h"

char *tag[8][8];
int main()
{
    PLAYER *p1 = malloc(sizeof(PLAYER));
    PLAYER *p2 = malloc(sizeof(PLAYER));
    p1->color = 'w';
    p2->color = 'b';
    int pawncol = 0;
    // player 1 and 2 initial pawns
    for(int pawn = Pawn1; pawn <= Pawn8; pawn++)
    {
        p1->piecelist[pawn] = CreatePiece(1, pawncol, 'P', p1->color);
        p2->piecelist[pawn] = CreatePiece(6, pawncol, 'P', p2->color);
        pawncol++;
    }
    // player 1 initial pieces
    p1->piecelist[Rook1] = CreatePiece(0, 0, 'R', p1->color);
    p1->piecelist[Rook2] = CreatePiece(0, 7, 'R', p1->color);
    p1->piecelist[Knight1] = CreatePiece(0, 1, 'N', p1->color);
    p1->piecelist[Knight2] = CreatePiece(0, 6, 'N', p1->color);
    p1->piecelist[Bishop1] = CreatePiece(0, 2, 'B', p1->color);
    p1->piecelist[Bishop2] = CreatePiece(0, 5, 'B', p1->color);
    p1->piecelist[Queen] = CreatePiece(0, 3, 'Q', p1->color);
    p1->piecelist[King] = CreatePiece(0, 4, 'K', p1->color);
    // player 2 initial pieces
    p2->piecelist[Rook1] = CreatePiece(7, 0, 'R', p2->color);
    p2->piecelist[Rook2] = CreatePiece(7, 7, 'R', p2->color);
    p2->piecelist[Knight1] = CreatePiece(7, 1, 'N', p2->color);
    p2->piecelist[Knight2] = CreatePiece(7, 6, 'N', p2->color);
    p2->piecelist[Bishop1] = CreatePiece(7, 2, 'B', p2->color);
    p2->piecelist[Bishop2] = CreatePiece(7, 5, 'B', p2->color);
    p2->piecelist[Queen] = CreatePiece(7, 3, 'Q', p2->color);
    p2->piecelist[King] = CreatePiece(7, 4, 'K', p2->color);
    for(int i = 5; i >= 2; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            tag[i][j] = "  ";
        }
    }

    // draw initial board
    DrawBoard();
    makeMove(p1);
    DrawBoard();
    makeMove(p2);
    DrawBoard();
}
void DrawBoard()
{
    int cols = 0;
    for(int i = 8; i >= 1; i--)
    {
        printf("  +------+------+------+------+------+------+------+------+\n");
        printf("%d |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |  %s  |\n", i, tag[i-1][0], tag[i-1][1], tag[i-1][2], tag[i-1][3], tag[i-1][4], tag[i-1][5], tag[i-1][6], tag[i-1][7]);
        cols++;
    }
    printf("  +------+------+------+------+------+------+------+------+\n");
    printf("      a      b      c      d      e      f      g      h   \n");

    
}

void makeMove(PLAYER *p)
{
    assert(p);
    char cCol_src;
    int row_src;
    int col_src;
    char cCol_dest;
    int row_dest;
    int col_dest;
    printf("Enter the location of the piece you wish to move. \n");
    scanf(" %c%d", &cCol_src, &row_src);
    col_src = AlphatoNum(cCol_src);
    while((!(col_src >= 1 && col_src <= 8)) || !(row_src >= 1 && row_src <= 7))
    {
        printf("You have entered an invalid input. Please enter a different location \n");
        scanf(" %c%d", &cCol_src, &row_src);
        col_src = AlphatoNum(cCol_src);
        
    }
    while(findPiece(p, row_src, col_src) == NULL)
    {
        printf("You have made an invalid move. Please enter a different location \n");
        scanf(" %c%d", &cCol_src, &row_src);
        col_src = AlphatoNum(cCol_src);
    }
    PIECE *piece = findPiece(p, row_src, col_src);
    printf("Enter the location to move the piece. \n");
    scanf(" %c%d", &cCol_dest, &row_dest);
    col_dest = AlphatoNum(cCol_dest);
    movePiece(piece, row_dest-1, col_dest-1);
}

PIECE *CreatePiece(int r, int c, char piece, char color)
{
    PIECE *p = malloc(sizeof(PIECE));
    p->piece = piece;
    p->r = r;
    p->c = c;
    if(color == 'w')
    {
        if(piece == 'P') {tag[r][c] = "wP";}
        if(piece == 'R') {tag[r][c] = "wR";}
        if(piece == 'K') {tag[r][c] = "wK";}
        if(piece == 'Q') {tag[r][c] = "wQ";}
        if(piece == 'N') {tag[r][c] = "wN";}
        if(piece == 'B') {tag[r][c] = "wB";}
    }
    if(color == 'b')
    {
        if(piece == 'P') {tag[r][c] = "bP";}
        if(piece == 'R') {tag[r][c] = "bR";}
        if(piece == 'K') {tag[r][c] = "bK";}
        if(piece == 'Q') {tag[r][c] = "bQ";}
        if(piece == 'N') {tag[r][c] = "bN";}
        if(piece == 'B') {tag[r][c] = "bB";}
    }
    switch(piece)
    {
        case 'P':
            p->value = 1;
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
            p->value = 10; //should really be infinity
            break;
        default:
            break;
    }
    return p;
}
void movePiece(PIECE *piece, int newr, int newc)
{
    assert(piece);
    char *temp = tag[piece->r][piece->c];
    tag[newr][newc] = temp;
    tag[piece->r][piece->c] = "  ";
    piece->r = newc;
    piece->c = newr;
}
int AlphatoNum(char alpha)
{
    int num = 0;
    switch(alpha)
    {
        case 'a':
            num = 1;
            break;
        case 'b':
            num = 2;
            break;
        case 'c':
            num = 3;
            break;
        case 'd':
            num = 4;
            break;
        case 'e':
            num = 5;
            break;
        case 'f':
            num = 6;
            break;
        case 'g':
            num = 7;
            break;
        case 'h':
            num = 8;
            break;
        default:
            num = 9;
            break;
    }
    return num;
}

PIECE *findPiece(PLAYER *p, int r, int c)
{
    assert(p);
    PIECE *piece = malloc(sizeof(PIECE));
    for(int i = 0; i < 16; i++)
    {
        int rx = p->piecelist[i]->r;
        int cx = p->piecelist[i]->c;
        if((rx == r-1) && (cx == c-1))
        {
            piece = p->piecelist[i];
            return piece;
        }
    }
    return NULL;
}
