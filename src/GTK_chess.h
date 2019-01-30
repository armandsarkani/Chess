#ifndef GTK_CHESS_H
#define GTK_CHESS_H

#define MAX_GRID_SIZE 8
#define MAX_MSGLEN  100 
#define SQUARE_SIZE 50  
#define WINDOW_BORDER 10
#define BOARD_BORDER 10
#define BOARD_WIDTH  (MAX_GRID_SIZE*SQUARE_SIZE)
#define BOARD_HEIGHT (MAX_GRID_SIZE*SQUARE_SIZE)
#define WINDOW_WIDTH  (BOARD_WIDTH)
#define WINDOW_HEIGHT (BOARD_HEIGHT)

typedef enum
{
	BLACK = 0,
	WHITE = 1,
} GRID;

typedef enum
{
	WPAWN = 2,
	BPAWN,
	WROOK,
	BROOK,
	WBISHOP,
	BBISHOP,
	WKNIGHT,
	BKNIGHT,
	BQUEEN,
	WQUEEN,
	BKING,
	WKING
} PIECEICON;

void InitBoard(int Board[MAX_GRID_SIZE][MAX_GRID_SIZE]);
void ReverseGridColor(int Board[MAX_GRID_SIZE][MAX_GRID_SIZE], int g_x, int g_y);
static gboolean delete_event( GtkWidget *widget, GdkEvent *event, gpointer data);
static void destroy(GtkWidget *widget, gpointer data);
void DrawBoard(GtkWidget *table, int Board[MAX_GRID_SIZE][MAX_GRID_SIZE]);
void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y);
int area_click (GtkWidget *widget, GdkEvent  *event, gpointer  data);

#endif
