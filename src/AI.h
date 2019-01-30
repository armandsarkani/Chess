#ifndef AI_h
#define AI_h

#include "Board.h"
#include "Pieces.h"
#include "Movegen.c"

typedef struct move MOVE;
typedef struct movelist MOVELIST;


MOVE *AI(char *board[8][8], PLAYER *player, PLAYER *opponent);

int NegaMax(int depth, MOVE *origmove, int alpha, int beta, int AI_tracker);

#endif /* AI_h */
