/*Copyright Benny Lin*/
/* Last modified 1/27/2019*/

typedef struct move MOVE;
typedef struct movelist MOVELIST;

struct move {
	int src_row;
	int src_col;
	int dst_row;
	int dst_col;
	MOVE *nextentry;
	MOVE *preventry;
	char new_board[8][8];
	int score;
	MOVELIST *next_level;
	MOVELIST *prev_level;
};
struct movelist {
	MOVE *first;
	MOVE *last;
	MOVE *prevmove;
	BOARD *board;
}
void getmoves(char *org_board[8][8],PLAYER *player, PLAYER *oppenent, MOVELIST *list);
/*Adds entries for possible legal moves into a given list by evaluating a given board config and player perspective*/
void AddLegalMoves(MOVELIST *list, src_row, src_col, dest_row, dest_col, board[8][8]);
/*Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move*/

/*Deletes list of all possible legal moves: frees memory*/
void DeleteMoveList(MOVELIST *list);


/*Deletes a single move entry within the movelist*/
void DeleteMoveEntry(MOVE *entry);


void DeleteBoard(BOARD *board);


void DeletePlayer(PLAYER *entry);


void DeletePiece(PIECE *piece);

