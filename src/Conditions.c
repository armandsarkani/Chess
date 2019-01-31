/*Stalemate*/

/*Stalemate occurs when the player is not in check, but has no more legal moves*/
 
int Stalemate(BOARD *board, PLAYER *player, PLAYER *opponent){
	/*Essentially, Stalemate is checkmate without being in check*/
	if (Checkmate(board, player, opponent)==1)
	{
		printf("Conditions for Stalemate have been met!\n");
		return 1;
	}
}


/*50 turn limit*/

//Ends game if 50 consecutive moves were made without capture/pawn movement

int Draw50 (BOARD *board, PLAYER *player, PLAYER *opponent, int TurnCount){

if (Piece was captured || Pawn was moved){
	TurnCounter = 0;

}	
else{
TurnCount += 1;
}
}

