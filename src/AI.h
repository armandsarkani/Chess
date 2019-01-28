#ifndef AI_h
#define AI_h

#include "Board.h"
#include "Pieces.h"
#include "Movegen.c"

typedef struct move MOVE;
typedef struct movelist MOVELIST;


<<<<<<< HEAD
void AI(char *board[8][8], PLAYER *player, PLAYER *opponent);

int NegaMax(int depth, MOVE *origmove, int alpha, int beta, int AI_tracker);
=======
void AI(char *board[8][8], PLAYER *color);

int NegaMax(int depth, MOVE *origmove, int alpha, int beta);
>>>>>>> e5bdb7aadda58ae5f1b0257438b03b8762da1cfc

#endif /* AI_h */
