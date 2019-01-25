//Copyright Benny Lin
/* Last modified 1/24/2019*/
* 


/*Things that need to be added:

	DeleteMoveList
	DeleteMoveEntry
	
*/

void getmoves(char *org_board[8][8],PLAYER *player, PLAYER *oppenent, MOVELIST *list);
//Adds entries for possible legal moves into a given list by evaluating a given board config and player perspective
//
void AddLegalMoves(MOVELIST *list, src_row, src_col, dest_row, dest_col, board[8][8]){
////Adds move information into the given list, allocating space and making new entries; stores resulting board from making the move
//
void DeleteMoveList()
////Deletes list of all possible legal moves: frees memory
//
void DeleteMoveEntry()
////Deletes a single move entry within the movelist
