<<<<<<< HEAD

/*Benny Lin*/
/*Last Modified 1/27/19*/

/*Things that need to be developed:
 * 	
 * 		Functions:
		int score_move();
=======
/*Benny Lin*/
/*Last Modified 1/24/19*/

/*Things that need to be developed:
	
	Functions:
		int score_move();
		
>>>>>>> e5bdb7aadda58ae5f1b0257438b03b8762da1cfc
		int CheckKillerMoves();
		int CheckCaptureMoves();
		int EvaluatePosition();
	
	Constants:
		Piece-SquareTable (needs some redefinition)
			*A PST is a 1-D array of 64 elements. Each element represents a position on the board. A position is given more weight if it 
			is better for the piece to be there. Higher values = better positions. The array encourages certain behaviors for the pieces.
			i.e. Pawns are enccouraged to move forward and stay in the center, knights are encouraged to stay in the center of the board, 
			kings are encouraged to stay out of corners of the board 
		Piece value (needs more discussion on how much a piece is worth vs. position)
		
	General formula for what is a good move
*/

int score_move(MOVE *move, PLAYER *opponent){
	/*Passes a move entry. Move entry is accessed. Data( row, col, new_board) is used to evaluate ce
<<<<<<< HEAD
 *  * 	Calls all other functions and sums the subscores for a final score
 *   * 		Returns final score*/ 
=======
 * 	Calls all other functions and sums the subscores for a final score
 * 		Returns final score*/ 
>>>>>>> e5bdb7aadda58ae5f1b0257438b03b8762da1cfc
}

int CheckKillerMoves( int dest_row, int dest_col, PLAYER* opponent){
	/*Scans the given board position and counts the number of ways the opponent can attack the given board position.
<<<<<<< HEAD
 *  * 	Creates a subscore using the above data
 *   * 		Returns a subscore*/
	
}

int CheckCaptureMoves(int dest_row, int dest_col, PIECE *piece, PLAYER* opponent){
	/*Scans given board position and counts the number of opponent pieces the player can capture with that specific piece
 *  * 	Creates a subscore using the above data
 *   * 		Returns a subscore*/
	
}

int EvaluatePositon(int row, int col, PIECE *piece){
	/*****Needs more development; board position of player piece is only relative to positions of opponent piece****/
	/*Evaluates the given board position and creates a subscore for it
 *  * 	Uses the Piece Square Table of the respective piece and other data to calculate board position subscore
 *   * 		Returns subscore*/
=======
 * 	Creates a subscore using the above data
 * 		Returns a subscore*/
	
}

int CheckCaptureMoves(int dest_row. int dest_col, PIECE *piece, PLAYER* opponent){
	/*Scans given board position and counts the number of opponent pieces the player can capture with that specific piece
 * 	Creates a subscore using the above data
 * 		Returns a subscore*/
	
}

int EvaluatePosiiton(int row, int col, PIECE *piece){
	/*****Needs more development; board position of player piece is only relative to positions of opponent piece****/
	/*Evaluates the given board position and creates a subscore for it
 * 	Uses the Piece Square Table of the respective piece and other data to calculate board position subscore
 * 		Returns subscore*/
>>>>>>> e5bdb7aadda58ae5f1b0257438b03b8762da1cfc
}
