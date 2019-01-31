#ifndef backupAI_h
#define backupAI_h

#include "Board.h"
#include "Pieces.h"
#include "Movegen.c"
#include <time.h>

MOVE *AI(BOARD *board, PLAYER *player, PLAYER *opponent);

#endif /* AI_h */
