/*Stalemate checks if the player's king cannot move, because it will put itself in check.
 
Stalemate(){

//Checks for check for all possible moves of king. 


if (check is false) //only occurs when not in check
{
check future moves for king
	if all future moves for king lead to check
	return draw
}

else

	you are not in a position for a stalemate, so return false

}



//50 turn limit
//ends game if 50 consecutive moves were made without capture/pawn movement

Draw50(){

//Quick note: somewhere outside the function we would need a counter to keep track of the number of moves that have been made without capture/pawn movement
//There would also be another function in which would reset that counter once one of the two conditions are met. ie
(assuming we added an int named ConsecMove)

if (coordinate chosen has successfully moved AND is type pawn OR new coordinate == opponent's piece (meaning it captured an opponent's piece){
	ConsecMove now equals 0;
} 

else //assuming that we have hit 50
{

print("50 Turn Rule Conditions Met!\n ")
return 3;


}
}

//Three Move Draw
//Ends game if only legal moves are repeated 3 times

DrawThreeMove(){

//As we check for legal moves, we should have some type of counter for each time this specific movement has been referenced.


if (that counter == 3)
	//player's only legal moves are those that are repeated
	printf("ThreeFold Rule Conditions Met \n");

return 3;

}







