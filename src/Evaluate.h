#include "Board.h"
#include "Pieces.h"
#include "Movegen.h"
#include "Conditions.h"
/*Copyright Benny Lin*/
/* Last modified 1/30/2019*/
/* 
  Things that need to be developed:
	
	Functions:
		int score_move();
		
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


int scoremove(MOVE *move, PLAYER *player, PLAYER *opponent);
	/*Passes a move entry. Move entry is accessed. Data( row, col, new_board) is used to evaluate ce
  	Calls all other functions and sums the subscores for a final score
  		Returns final score*/ 


int CheckKillerMoves( MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board);
	/*Scans the given board position and counts the number of ways the opponent can attack the given board position.
  	Creates a subscore using the above data
  		Returns a subscore*/
	


int CheckCaptureMoves(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board);
	/*Scans given board position and counts the number of opponent pieces the player can capture with that specific piece
  	Creates a subscore using the above data
  		Returns a subscore*/
	


int EvaluatePosition(MOVE *move, PIECE *piece, BOARD *board, PLAYER *player, PLAYER *opponent);
	/*Needs more development; board position of player piece is only relative to positions of opponent piece*/
	/*Evaluates the given board position and creates a subscore for it
  	Uses the Piece Square Table of the respective piece and other data to calculate board position subscore
  		Returns subscore*/
	
int ReturnPosScore(char piecetype, int pos);
	/*returns the value of the position of the square that the piece is on*/
	
int BoardtoPSQTable(int row, int col);
	/*returns the square that the piece is on*/
