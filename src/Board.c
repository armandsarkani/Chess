//  Board.c
//  Chesster Team 3

#include "Board.h"
#include "Pieces.h"
#include "backupAI.h"
#include "Movegen.h"
#include "Evaluate.h"

int main()
{
    char *mainboard[8][8];
    PLAYER *white = malloc(sizeof(PLAYER));
    white->color = 'w';
    PLAYER *black = malloc(sizeof(PLAYER));
    black->color = 'b';
    int game_mode;
    printf("Please press 1 for human vs. human, 2 for human vs. AI:\n");
    scanf("%d", &game_mode);
    char human_color;
    printf("Which color would you like to be? \n");
    printf("(w = white, b = black) \n");
    scanf(" %c", &human_color);
    BOARD *global;
    if(human_color == 'w' || human_color == 'W')
    {
        printf("You are the white player. \n");
        white->color = 'w';
        black->color = 'b';
        if(game_mode == 1)
        {
            white->type = 'h';
            black->type = 'h';
        }
        if(game_mode == 2)
        {
            white->type = 'h';
            black->type = 'a';
        }
        global = CreateBoard(white, black, mainboard);
        
    }
    else
    {
        printf("You are the black player. \n");
        black->color = 'b';
        white->color = 'w';
        if(game_mode == 1)
        {
            white->type = 'h';
            black->type = 'h';
        }
        if(game_mode == 2)
        {
            white->type = 'a';
            black->type = 'h';
        }
        global = CreateBoard(white, black, mainboard);
        
    }
    InitializeBoard(global);
    bool IsGameOver = false; // replace with win condition checking functions in modules TBD
    if(white->type == 'h')
    {
        DrawBoard(global);
    }
    int move = 0;
    while(IsGameOver == false)
    {
        move = MakeMove(global, white, black);
        DrawBoard(global);
        if(move == 1 || move == 2)
        {
            if(move == 2)
            {
                printf("Game over! White wins by checkmate!\n");
                IsGameOver = true;
                break;
            }
            else
            {
                printf("Black is in check!\n");
                
            }
        }
        move = MakeMove(global, black, white);
        DrawBoard(global);
        if(move == 1 || move == 2)
        {
            if(move == 2)
            {
                printf("Game over! Black wins by checkmate!\n");
                IsGameOver = true;
                break;
            }
            else
            {
                printf("White is in check!\n");
                
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
        char cCol_src = '\0';
        int row_src = 0;
        int col_src = 0;
        char cCol_dest = '\0';
        int row_dest = 0;
        int col_dest = 0;
        char *piecetag = NULL;
        char initial_piecetype = '\0';
        char *originalpiecetag = NULL;
        PIECE *opponentcapture = NULL;
        int opponent_r = 0;
        int opponent_c = 0;
        int opponent_value = 0;
        int callreturn = 0;
        int promotion = 0;
        PIECE *piece = NULL;
        if (p->type == 'a') {
            sleep(1);
            printf("AI's move: \n");
            MOVE *AImove = AI(board, p, opponent);
            row_src = AImove->src_row;
            col_src = AImove->src_col;
            row_dest = AImove->dst_row;
            col_dest = AImove->dst_col;
            if(AImove->IsCaptured == 1)
            {
                callreturn = 2;
            }
            piece = CheckPiece(p, row_src+1, col_src+1);
            originalpiecetag = board->boardarray[piece->r][piece->c];
            row_src += 1;
            col_src += 1;
            row_dest += 1;
            col_dest += 1;
            cCol_dest = NumtoAlpha(col_dest);
            cCol_src = NumtoAlpha(col_src);
            char *piecename = PieceName(piece->piecetype);
            printf("%s moved from %c%d to %c%d\n", piecename, cCol_src, row_src, cCol_dest, row_dest);
            MovePiece(board, opponent, piece, row_dest-1, col_dest-1);
            DeleteMoveEntry(AImove);
        }
        else
        {
            printf("Your move: \n");
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
                printf("You cannot move an opponent's piece or an empty square. Please enter a different location. \n");
                scanf(" %c%d", &cCol_src, &row_src);
                col_src = AlphatoNum(cCol_src);
            }
            piece = CheckPiece(p, row_src, col_src);
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
            callreturn = CallPiece(board, opponent, piece, row_src, col_src, row_dest, col_dest, 1);
            while(callreturn == 1)
            {
                printf("Invalid move. \n");
                printf("Please enter a different location. \n");
                scanf(" %c%d", &cCol_dest, &row_dest);
                col_dest = AlphatoNum(cCol_dest);
                piece = CheckPiece(p, row_src, col_src);
                callreturn = CallPiece(board, opponent, piece, row_src, col_src, row_dest, col_dest, 1);
            }
            originalpiecetag = board->boardarray[piece->r][piece->c];
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
        }
        initial_piecetype = piece->piecetype;
        // Move is legal and does not place the player in check
        if(piece->piecetype == 'P')
        {
            promotion = Promotion(board, piece);
        }
        EXIT = 1;
        FILE *log;
        char info = '\0';
        int CheckReturn = 0;
        if(Checkmate(board, p, opponent) == 1)
        {
            CheckReturn = 2;
        }
        else if(Check(board, p, opponent, (opponent->piecelist[King]->r)+1, (opponent->piecelist[King]->c)+1) == 1)
        {
            CheckReturn = 1;
        }
        if(promotion == 0)
        {
            board->boardarray[piece->r][piece->c] = originalpiecetag;
        }
        else if(promotion == 1)
        {
            info = piece->piecetype;
        }
        if(callreturn == 2) // a piece has been captured
        {
            log = Log(p->color, initial_piecetype, cCol_dest, row_dest, 1, CheckReturn, info);
        }
        else
        {
            log = Log(p->color, initial_piecetype, cCol_dest, row_dest, 0, CheckReturn, info);
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
    if(Check(board, opponent, piece->player, (piece->player->piecelist[King]->r)+1, (piece->player->piecelist[King]->c)+1) == 1) // undo a move if in check
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
char NumtoAlpha(int num)
{
    char alpha = 0;
    switch(num)
    {
        case 1:
            alpha = 'a';
            break;
        case 2:
            alpha = 'b';
            break;
        case 3:
            alpha = 'c';
            break;
        case 4:
            alpha = 'd';
            break;
        case 5:
            alpha = 'e';
            break;
        case 6:
            alpha = 'f';
            break;
        case 7:
            alpha = 'g';
            break;
        case 8:
            alpha = 'h';
            break;
        default:
            alpha = 'q';
            break;
    }
    return alpha;
}

char *PieceName(char piecename)
{
    char *piecestring = NULL;
    switch(piecename)
    {
        case 'P':
            piecestring = "Pawn";
            break;
        case 'R':
            piecestring = "Rook";
            break;
        case 'N':
            piecestring = "Knight";
            break;
        case 'B':
            piecestring = "Bishop";
            break;
        case 'Q':
            piecestring = "Queen";
            break;
        case 'K':
            piecestring = "King";
            break;
        default:
            piecestring = NULL;
            break;
    }
    return piecestring;
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
FILE *Log(char color, char piecetype, char destcol, int destrow, int isCaptured, int CheckReturn, char info)
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
            fprintf(log, "%s: x%c%d%c%c\n", color_string, destcol, destrow, check_char, info);
        }
        else
        {
            fprintf(log, "%s: %cx%c%d%c%c\n", color_string, piecetype, destcol, destrow, check_char, info);
        }
    }
    else
    {
        if(piecetype == 'P')
        {
            fprintf(log, "%s: %c%d%c%c\n", color_string, destcol, destrow, check_char, info);
        }
        else
        {
            fprintf(log, "%s: %c%c%d%c%c\n", color_string, piecetype, destcol, destrow, check_char, info);
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
        PIECE *opponentcapture = NULL;
        int opponent_r = 0;
        int opponent_c = 0;
        int opponent_value = 0;
        char *piecetag = NULL;
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
                    if(IsLegalMove == 2)
                    {
                        opponentcapture = CheckPiece(player, j+1, k+1);
                        opponent_r = opponentcapture->r;
                        opponent_c = opponentcapture->c;
                        opponent_value = opponentcapture->value;
                        piecetag = board->boardarray[opponent_r][opponent_c];
                    }
                    movereturn = MovePiece(board, player, piece, j, k);
                    if(movereturn == 1) // if the test move made puts/leaves the opponent in check
                    {
                        if(IsLegalMove == 2) // if move is a potential capture move, reset captures and value updates
                        {
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
int Promotion(BOARD *board, PIECE *piece)
{
    char choice = '\0';
    if(piece->player->type == 'a')
    {
        if(piece->player->color == 'w' &&  piece->r == 7)
        {
            piece->value = 9;
            piece->piecetype = 'Q';
            board->boardarray[piece->r][piece->c] = "wQ";
            return 1;
        }
        else if(piece->player->color == 'b' && piece->r == 0)
        {
            piece->value = 9;
            piece->piecetype = 'Q';
            board->boardarray[piece->r][piece->c] = "bQ";
            return 1;
        }
    }
    if(piece->player->color == 'w')
    {
        if(piece->r == 7)
        {
            printf("Pawn Promotion: Please select a piece to promote this pawn to. Enter Q for queen, N for knight, B for bishop, or R for rook.\n");
            scanf(" %c", &choice);
        }
    }
    else if(piece->player->color == 'b')
    {
        if(piece->r == 0)
        {
            printf("Pawn Promotion: Please select a piece to promote this pawn to. Enter Q for queen, N for knight, B for bishop, or R for rook.\n");
            scanf(" %c", &choice);
        }
    }
    if(choice == 'Q' || choice == 'q')
    {
        piece->value = 9;
        piece->piecetype = 'Q';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wQ";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bQ";
        }
        return 1;
    }
    else if(choice == 'N' || choice == 'n')
    {
        piece->value = 3;
        piece->piecetype = 'N';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wN";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bN";
        }
        return 1;
    }
    else if(choice == 'B' || choice == 'b')
    {
        piece->value = 3;
        piece->piecetype = 'B';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wB";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bB";
        }
        return 1;
    }
    else if(choice == 'R' || choice == 'r')
    {
        piece->value = 5;
        piece->piecetype = 'R';
        if(piece->player->color == 'w')
        {
            board->boardarray[piece->r][piece->c] = "wR";
        }
        else
        {
            board->boardarray[piece->r][piece->c] = "bR";
        }
        return 1;
    }
    return 0;
}

