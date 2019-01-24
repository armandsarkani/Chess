#include "Board.h"
#include "Pieces.h"

char *tag[8][8];
int main()
{
    PLAYER *white = malloc(sizeof(PLAYER));
    white->color = 'w';
    PLAYER *black = malloc(sizeof(PLAYER));
    black->color = 'b';
    char human_color;
	int row; 
	char col;
    printf("Which color would you like to be? \n");
    printf("(w = white, b = black) \n");
    scanf(" %c", &human_color);
    if(human_color == 'w')
    {
        printf("You are the white player. \n");
        white->type = 'h';
        white->color = 'w';
        black->type = 'a';
    }
    else if(human_color == 'b')
    {
        printf("You are the black player. \n");
        black->type = 'h';
        white->type = 'a';
    }
	BOARDS *boards = CreateBoards();
    InitializeBoard(white, black, boards);
    bool IsGameOver = false; // replace with win condition checking functions in modules TBD
    DrawBoard();
    while(IsGameOver == false)
    {
        MakeMove(white, black, boards);
        DrawBoard();
		printf("Surveying the board. Enter row and column to find piece.\n");
		scanf(" %c%d", &col, &row);
        int Ncol = AlphatoNum(col);
		PieceInfo(FindPiece(boards, 8-row, Ncol-1));
        MakeMove(black, white, boards);
        DrawBoard();
    }
    
}

void InitializeBoard(PLAYER *white, PLAYER *black, BOARDS *boards)
{
    // White is by default the player that initially occupies first two rows, black is by default the player that initially occupies the top two rows
    // White and 2 initial pawns
    int pawncol = 0;
    for(int pawn = Pawn1; pawn <= Pawn8; pawn++)
    {
        white->piecelist[pawn] = CreatePiece(1, pawncol, 'P', 'w', white);
		boards->pieceboard[pawn][pawncol] = white->piecelist[pawn];
		
        black->piecelist[pawn] = CreatePiece(6, pawncol, 'P', 'b', black);
		boards->pieceboard[pawn][pawncol] = black->piecelist[pawn];
        pawncol++;
    }
    // White initial non-pawn pieces
    white->piecelist[Rook1] = CreatePiece(0, 0, 'R', 'w', white);
    white->piecelist[Rook2] = CreatePiece(0, 7, 'R', 'w', white);
    white->piecelist[Knight1] = CreatePiece(0, 1, 'N', 'w', white);
    white->piecelist[Knight2] = CreatePiece(0, 6, 'N', 'w', white);
    white->piecelist[Bishop1] = CreatePiece(0, 2, 'B', 'w', white);
    white->piecelist[Bishop2] = CreatePiece(0, 5, 'B', 'w', white);
    white->piecelist[Queen] = CreatePiece(0, 3, 'Q', 'w', white);
    white->piecelist[King] = CreatePiece(0, 4, 'K', 'w', white);
	
	boards->pieceboard[7][0] = white->piecelist[Rook1];
	boards->pieceboard[7][7] = white->piecelist[Rook1];
	boards->pieceboard[7][1] = white->piecelist[Knight1];
	boards->pieceboard[7][6] = white->piecelist[Knight2];
	boards->pieceboard[7][2] = white->piecelist[Bishop1];
	boards->pieceboard[7][5] = white->piecelist[Bishop2];
	boards->pieceboard[7][3] = white->piecelist[Queen];
	boards->pieceboard[7][4] = white->piecelist[King];
	
    // player 2 initial pieces
    black->piecelist[Rook1] = CreatePiece(7, 0, 'R', 'b', black);
    black->piecelist[Rook2] = CreatePiece(7, 7, 'R', 'b', black);
    black->piecelist[Knight1] = CreatePiece(7, 1, 'N', 'b', black);
    black->piecelist[Knight2] = CreatePiece(7, 6, 'N', 'b', black);
    black->piecelist[Bishop1] = CreatePiece(7, 2, 'B', 'b', black);
    black->piecelist[Bishop2] = CreatePiece(7, 5, 'B', 'b', black);
    black->piecelist[Queen] = CreatePiece(7, 3, 'Q', 'b', black);
    black->piecelist[King] = CreatePiece(7, 4, 'K', 'b', black);
	
	boards->pieceboard[0][0] = black->piecelist[Rook1];
	boards->pieceboard[0][7] = black->piecelist[Rook1];
	boards->pieceboard[0][1] = black->piecelist[Knight1];
	boards->pieceboard[0][6] = black->piecelist[Knight2];
	boards->pieceboard[0][2] = black->piecelist[Bishop1];
	boards->pieceboard[0][5] = black->piecelist[Bishop2];
	boards->pieceboard[0][3] = black->piecelist[Queen];
	boards->pieceboard[0][4] = black->piecelist[King];
	
    for(int i = 5; i >= 2; i--)
    {
        for(int j = 0; j < 8; j++)
        {
            tag[i][j] = "  ";
			boards->pieceboard[i][j] = NULL;
        }
    }
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

void MakeMove(PLAYER *p, PLAYER *opponent, BOARDS *boards)
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
    while((CallPiece(opponent, piece, row_src, col_src, row_dest, col_dest)) != 0)
    {
        printf("Please enter a different location. \n");
        scanf(" %c%d", &cCol_dest, &row_dest);
        col_dest = AlphatoNum(cCol_dest);
    }
    MovePiece(piece, row_dest-1, col_dest-1, boards);
    
}

PIECE *CreatePiece(int r, int c, char piece, char color, PLAYER *player)
{
    PIECE *p = malloc(sizeof(PIECE));
    p->piecetype = piece;
    p->player = player;
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
            p->value = 10; //should really be infinity
            break;
        default:
            break;
    }
    return p;
}
void MovePiece(PIECE *piece, int newr, int newc, BOARDS *boards)
{
    assert(piece);
	assert(boards);
    char *temp = tag[piece->r][piece->c];
	PIECE *tempPiece = malloc(sizeof(PIECE));
	tempPiece = boards->pieceboard[piece->r][piece->c];
	
    tag[newr][newc] = temp;
	boards->pieceboard[newr][newc] = tempPiece;

    tag[piece->r][piece->c] = "  ";
	boards->pieceboard[piece->r][piece->c] = NULL;
    piece->r = newr;
    piece->c = newc;

    free(tempPiece);
    tempPiece = NULL;
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

char NumtoAlpha(int num){
	char alpha;
    switch(num)
    {
        case 0:
            alpha = 'A';
            break;
        case 1:
            alpha = 'B';
            break;
        case 2:
            alpha = 'C';
            break;
        case 3:
            alpha = 'D';
            break;
        case 4:
            alpha = 'E';
            break;
        case 5:
            alpha = 'F';
            break;
        case 6:
            alpha = 'G';
            break;
        case 7:
            alpha = 'H';
            break;
        default:
            alpha = 'N';
            break;
    }
    return alpha;
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

int FindEmptySpace(int r, int c)
{
    if(strcmp(tag[r-1][c-1], "  ") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

BOARDS *CreateBoards(){
	BOARDS *boards = malloc(sizeof(BOARDS));
	
	return boards;
}
PIECE *FindPiece(BOARDS *boards, int r, int c){
	assert(boards);
	return boards->pieceboard[r][c];
	
}

void PieceInfo(PIECE *piece){
	if(piece != NULL){
	    printf("Piece color: %c\n", piece->player->color);
	    printf("Piece type: %c\n", piece->piecetype);
	    printf("Piece location: %c%d\n", NumtoAlpha(piece->c), piece->r+1);
	}
	else
	    printf("No piece there\n");
}

void CapturePiece(PIECE *piece)
{
    tag[piece->r][piece->c] = "  ";
    free(piece);
    piece->r = 9; // 9 = off board
    piece->c = 9; // 9 = off board
    piece->value = 0;
    piece = NULL;

}
