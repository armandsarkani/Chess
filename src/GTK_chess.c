#include <gtk/gtk.h>
#include "GTK_chess.h"



void InitBoard(int Board[MAX_GRID_SIZE][MAX_GRID_SIZE])
{
	/* Initialize Board colors */
	int j = 0;
	while(j < 8){
		if(j%2 == 0){	
			for(int i = 0; i < MAX_GRID_SIZE; i++){
				if(i%2 == 0){Board[i][j] = WHITE;}
				else{Board[i][j] = BLACK;}
			}
		}
		else{
			for(int i = 0; i < MAX_GRID_SIZE; i++){
				if(i%2 == 0){Board[i][j] = BLACK;}
				else{Board[i][j] = WHITE;}
			}
		}
	j++;	//Increment to next row
	}
	for(int pawn = 0; pawn < MAX_GRID_SIZE; pawn++)
    {
		Board[pawn][6] = WPAWN;
		Board[pawn][1] = BPAWN;
    }
	//Black pieces 
	Board[0][0] = BROOK;
	Board[1][0] = BKNIGHT;
	Board[2][0] = BBISHOP;
	Board[3][0] = BQUEEN;
	Board[4][0] = BKING;
	Board[5][0] = BBISHOP;
	Board[6][0] = BKNIGHT;
	Board[7][0] = BROOK;
	
	//White Pieces 
	Board[0][7] = WROOK;
	Board[1][7] = WKNIGHT;
	Board[2][7] = WBISHOP;
	Board[3][7] = WKING;
	Board[4][7] = WQUEEN;
	Board[5][7] = WBISHOP;
	Board[6][7] = WKNIGHT;
	Board[7][7] = WROOK;
	
    /*for(int pawn = 0; pawn < 8; pawn++)
    {
		PieceBoard[pawn][6] = WPAWN;
		PieceBoard[pawn][1] = BPAWN;
    }
	Black pieces 
	PieceBoard[0][0] = BROOK;
	PieceBoard[1][0] = BKNIGHT;
	PieceBoard[2][0] = BBISHOP;
	PieceBoard[3][0] = BQUEEN;
	PieceBoard[4][0] = BKING;
	PieceBoard[5][0] = BBISHOP;
	PieceBoard[6][0] = BKNIGHT;
	PieceBoard[7][0] = BROOK;
	
	/*White Pieces 
	PieceBoard[0][7] = WROOK;
	PieceBoard[1][7] = WKNIGHT;
	PieceBoard[2][7] = WBISHOP;
	PieceBoard[3][7] = WKING;
	PieceBoard[4][7] = WQUEEN;
	PieceBoard[5][7] = WBISHOP;
	PieceBoard[6][7] = WKNIGHT;
	PieceBoard[7][7] = WROOK;*/
}

void ReverseGridColor(int Board[MAX_GRID_SIZE][MAX_GRID_SIZE], int g_x, int g_y)
{
	if(Board[g_x][g_y] == BLACK)
	{
		Board[g_x][g_y] = WHITE;
	}
	else
	{
		Board[g_x][g_y] = BLACK;
	}
}

static gboolean delete_event( GtkWidget *widget, GdkEvent *event, gpointer data)
{
	g_print("delete event occurred\n");
	gtk_main_quit();
	return TRUE;
}

static void destroy(GtkWidget *widget, gpointer data)
{
	gtk_main_quit();
}

void DrawBoard(GtkWidget *table, int Board[MAX_GRID_SIZE][MAX_GRID_SIZE])
{
	//GtkWidget *Board_icon;
	GtkWidget *chess_icon;
	int i, j;
	/* Draw Checker Board */
    for(i = 0; i < MAX_GRID_SIZE; i ++)
	{
		for(j = 0; j < MAX_GRID_SIZE; j ++)
		{
			switch(Board[i][j])
			{
				case BLACK:
					chess_icon = gtk_image_new_from_file("./chess_icon/Bsquare.jpg") ;
					break;
				case WHITE:
					chess_icon = gtk_image_new_from_file("./chess_icon/Wsquare.jpg") ;
					break;
				case WPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/WPawn.png") ;
					break;
				case BPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/BPawn.png") ;
					break;
				case WROOK:
					chess_icon = gtk_image_new_from_file("./chess_icon/WRook.png") ;
					break;
				case BROOK:
					chess_icon = gtk_image_new_from_file("./chess_icon/BRook.png") ;
					break;
				case WBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/WBishop.png") ;
					break;
				case BBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/BBishop.png") ;
					break;
				case WKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKnight.png") ;
					break;
				case BKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/BKnight.png") ;
					break;
				case WQUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icon/WQueen.png") ;
					break;
				case BQUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icon/BQueen.png") ;
					break;
				case WKING:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.png") ;
					break;
				case BKING:
					chess_icon = gtk_image_new_from_file("./chess_icon/BKing.png") ;
					break;
				default:
					break;
			}
			gtk_table_attach(GTK_TABLE(table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}
	/*for(i = 0; i < 8; i ++)
	{
		for(j = 0; j < 8; j ++)
		{
			switch(PieceBoard[i][j])
			{
				case WPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/WPawn.png") ;
					break;
				case BPAWN:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case WROOK:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case BROOK:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case WBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case BBISHOP:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case WKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case BKNIGHT:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case WQUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case BQUEEN:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case WKING:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				case BKING:
					chess_icon = gtk_image_new_from_file("./chess_icon/WKing.jpg") ;
					break;
				default:
					break;
			}
			//gtk_table_attach(GTK_TABLE(Piecetable), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}*/
}


void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	int x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	int y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
	*g_x = x < 0 ? 0 : x > 0 ? MAX_GRID_SIZE - 1 : x;
	*g_y = y < 0 ? 0 : y > 0 ? MAX_GRID_SIZE - 1 : y;
}

int area_click (GtkWidget *widget, GdkEvent  *event, gpointer  data)
{
	int x1, y1 ; 
	char words[MAX_MSGLEN] ; 
	//GdkColor color;
	//gdk_color_parse ("red", &color);
	int coord_x, coord_y, grid_x, grid_y;  

	GdkModifierType state ; 

	gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ; 
	
	if(coord_x > 0 && coord_x < WINDOW_WIDTH && coord_y > 0 && coord_y < WINDOW_HEIGHT){
		CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);
	}
	//gtk_widget_modify_fg (chess_icon, GTK_STATE_NORMAL, &color);
	
  printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);
/*
    gtk_container_remove(GTK_CONTAINER(window), fixed) ; 
    table = gtk_table_new (8, 8, TRUE) ;
    gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ;
    DrawBoard(table, Piecetable, Board, PieceBoard); 
	//gtk_table_attach(GTK_TABLE(table), chess_icon, grid_x, grid_x+1, grid_y+1, grid_y+1, GTK_FILL, GTK_FILL, 0, 0) ;

    /*set fixed

    fixed = gtk_fixed_new() ;
    gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0) ;
    gtk_container_add(GTK_CONTAINER(window), fixed) ;
    gtk_widget_show_all(window) ; 
*/
  return TRUE ; 
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	//GtkWidget *frame;
	GtkWidget *table;
	//GtkWidget *Piecetable;
	GtkWidget *fixed;
	int Board[MAX_GRID_SIZE][MAX_GRID_SIZE];
	//int PieceBoard[8][8] = {{0}};
	
	gtk_init(&argc, &argv);
	
	/*create a new window */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
	gtk_widget_set_size_request(window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
	gtk_container_set_border_width (GTK_CONTAINER(window), WINDOW_BORDER) ; 
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER) ; 
	gtk_window_set_title(GTK_WINDOW(window), "Let's play Chess!") ; 
	gtk_window_set_resizable(GTK_WINDOW(window), TRUE) ; 
	
	//frame = gtk_frame_new(NULL);
	//gtk_container_add(GTK_CONTAINER(window), frame);
	
	/*Click Events*/
	g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);
	gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK) ; 	
	g_signal_connect(window, "button_press_event", G_CALLBACK(area_click), NULL) ; 
	
	/*Create table and draw board */
	table = gtk_table_new(MAX_GRID_SIZE, MAX_GRID_SIZE, TRUE);
	//Piecetable = gtk_table_new(8, 8, TRUE);
	InitBoard(Board);
	gtk_widget_set_size_request (table, BOARD_WIDTH, BOARD_HEIGHT) ; 
	//gtk_widget_set_size_request (Piecetable, BOARD_WIDTH, BOARD_HEIGHT) ; 
	DrawBoard(table, Board);
	
	fixed = gtk_fixed_new() ; 
	gtk_fixed_put(GTK_FIXED(fixed), table, 0, 0); 
	//gtk_fixed_put(GTK_FIXED(fixed), Piecetable, 0, 0);
	gtk_container_add(GTK_CONTAINER(window), fixed); 
	
	//gtk_widget_show(Piecetable);
	
	
	
	gtk_widget_show_all(window);

	gtk_main();
	
	return 0;
}
