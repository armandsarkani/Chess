fndef AI_h
#define AI_h

#include "Board.h"
#include "Pieces.h"
#include "Movegen.c"

typedef struct move MOVE;
typedef struct movelist MOVELIST;


void AI(char *board[8][8], PLAYER *color);

int NegaMax(int depth, MOVE *origmove, int alpha, int beta);

#endif /* AI_h */
