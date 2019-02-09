#ifndef AI_h
#define AI_h

#include "Board.h"
#include "Pieces.h"
#include "Movegen.h"
#include "Evaluate.h"
#include "Conditions.h"





MOVE *AI(BOARD *board, PLAYER *player, PLAYER *opponent, int turn_counter);

int NegaMax(int depth, MOVE *origmove, int alpha, int beta, int AI_tracker, int turn_counter);


#endif /* AI_h */
