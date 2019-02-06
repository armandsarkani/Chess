nclude "Board.h"
#include "Pieces.h"
#include "Movegen.h"
#include "Conditions.h"
/*Copyright Benny Lin*/
/* Last modified 2/6/2019*/

int scoremove(MOVE *move, PLAYER *player, PLAYER *opponent);
/*Passes a move entry. Move entry is accessed. Data( row, col, new_board) is used to evaluate ce
 *  Calls all other functions and sums the subscores for a final score
 *   Returns final score*/ 

int CheckKillerMoves(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board);
/*Scans the given board position and counts the number of ways the opponent can attack the given board position.
 *  Creates a subscore using the above data
 *    Returns a subscore*/

int CheckCaptureMoves(MOVE *move, PIECE *piece, PLAYER *opponent, BOARD *new_board);
/*Scans given board position and counts the number of opponent pieces the player can capture with that specific piece
 * Creates a subscore using the above data
 * Returns a subscore*/
	
int EvaluatePosition(MOVE *move, PIECE *piece, BOARD *board, PLAYER *player, PLAYER *opponent);
/*Returns the final score for a given move based on CheckKillerMoves, CheckCaptureMoves, and ReturnPosScore funcs*/
	
int ReturnPosScore(char piecetype, int pos);
/*returns the value of the position of the square that the piece is on*/
	
int BoardtoPSQTable(int row, int col);
/*returns the square that the piece is on*/
