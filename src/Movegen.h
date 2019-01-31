

/* Last modified 1/30/2019*/



/*Things that need to be added:
  	DeleteMoveList
	DeleteMoveEntry
	
*/

/*CallPiece testcondition:
 *
 * 0 = checks for legality of move
 * 1 = */

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
};
/*Adds entries for possible legal moves into a given list by evaluating a given board config and player perspective*/
void getmoves(char *org_board[8][8],PLAYER *player, PLAYER *oppenent, MOVELIST *list);

/*Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move*/
void AddLegalMoves(MOVELIST *list, src_row, src_col, dest_row, dest_col, board[8][8]);

/*Creates a new move list*/
MOVELIST *NewMoveList(void);

/*Creates a new move*/
MOVE *CreateMove(void);

/*Deletes list of all possible legal moves: frees memory*/
void DeleteMoveList(MOVELIST *list);

/*Deletes a single move entry within the movelist*/
void DeleteMoveEntry(MOVE *entry);

/*Deletes a board*/
void DeleteBoard(BOARD *board);

/*Deletes a player*/
void DeletePlayer(PLAYER *entry);

/*Deletes a piece*/
void DeletePiece(PIECE *piece);



