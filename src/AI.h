fndef AI_h
#define AI_h

#include "Board.h"
#include "Pieces.h"

typedef struct move MOVE;
typedef struct movelist MOVELIST;

struct move {
	int src_row;
	int src_col;
	int dst_row;
	int dst_col;
	MOVE *nextentry;
	MOVE *preventry;
	char newboard[8][8];
	int score;
};

struct movelist {
	MOVE *first;
	MOVE *last;	
};

#endif /* AI_h */
