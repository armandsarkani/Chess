#include <gtk/gtk.h>
#include <stdlib.h>
#include "GTK_chess.h"

int Board[MAX_GRID_SIZE][MAX_GRID_SIZE] = {{0}};



int main(int argc, char *argv[])
{
	//GtkWidget *window;
	//GtkWidget *fixed;
	
	CHESSBOARD *chessboard = CreateChessBoard();
	
	gtk_init(&argc, &argv);
	
	/*create a new window */
	chessboard->window = gtk_window_new(GTK_WINDOW_TOPLEVEL) ;
	gtk_widget_set_size_request(chessboard->window, WINDOW_WIDTH, WINDOW_HEIGHT) ; 
	gtk_container_set_border_width (GTK_CONTAINER(chessboard->window), WINDOW_BORDER) ; 
	gtk_window_set_position(GTK_WINDOW(chessboard->window), GTK_WIN_POS_CENTER) ; 
	gtk_window_set_title(GTK_WINDOW(chessboard->window), "Let's play Chess!") ; 
	gtk_window_set_resizable(GTK_WINDOW(chessboard->window), FALSE) ; 
	
	//frame = gtk_frame_new(NULL);
	//gtk_container_add(GTK_CONTAINER(window), frame);
	
	/*Click Events*/
	g_signal_connect(chessboard->window, "delete-event", G_CALLBACK(delete_event), NULL);
	gtk_widget_set_events(chessboard->window, GDK_BUTTON_PRESS_MASK) ; 	
	g_signal_connect(chessboard->window, "button_press_event", G_CALLBACK(area_click), chessboard) ; 
	
	/*Create table and draw board */
	
	//Piecetable = gtk_table_new(8, 8, TRUE);
	InitBoard(chessboard);
	DrawBoard(chessboard);
	
	gtk_container_add(GTK_CONTAINER(chessboard->window), chessboard->table);
	gtk_widget_show_all(chessboard->window);

	gtk_main();
	
	return 0;
}

void InitBoard(CHESSBOARD *chessboard)
{
	chessboard->table = gtk_table_new(MAX_GRID_SIZE, MAX_GRID_SIZE, TRUE);
	gtk_widget_set_size_request (chessboard->table, BOARD_WIDTH, BOARD_HEIGHT) ;
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
		Board[pawn][1] = BPAWN;
		Board[pawn][6] = WPAWN;
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
	Board[3][7] = WQUEEN;
	Board[4][7] = WKING;
	Board[5][7] = WBISHOP;
	Board[6][7] = WKNIGHT;
	Board[7][7] = WROOK;
	
}

void ReverseGridColor(int g_x, int g_y)
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

void DrawBoard(CHESSBOARD *chessboard)
{
	chessboard->table = gtk_table_new(MAX_GRID_SIZE, MAX_GRID_SIZE, TRUE);
	gtk_widget_set_size_request (chessboard->table, BOARD_WIDTH, BOARD_HEIGHT) ;
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
			//gtk_widget_set_events(chess_icon, GDK_BUTTON_PRESS_MASK) ; 
			//g_signal_connect(chess_icon, "button_press_event", G_CALLBACK(area_click), window) ; 
			gtk_table_attach(GTK_TABLE(chessboard->table), chess_icon, i, i + 1, j, j + 1, GTK_FILL, GTK_FILL, 0, 0) ;
		}
	}

}


void CoordToGrid(int c_x, int c_y, int *g_x, int *g_y)
{
	int x = (c_x - BOARD_BORDER) / SQUARE_SIZE;
	int y = (c_y - BOARD_BORDER) / SQUARE_SIZE;
	
	if(x < 0){ x = 0; }
	else if(x >= MAX_GRID_SIZE){ x = MAX_GRID_SIZE - 1; }
	
	if(y < 0){ y = 0; }
	else if(y >= MAX_GRID_SIZE){ y = MAX_GRID_SIZE - 1; }
	
	*g_x = x;
	*g_y = y;
}

gint area_click (GtkWidget *widget, CHESSBOARD *chessboard, GdkEvent *event, gpointer data)
{
	//GdkColor color;
	//GdkColor red = {0, 0xffff, 0x0000, 0x0000};
	
	int coord_x, coord_y, grid_x, grid_y;
	int selected = 0;
	
	/* Find coordinate on mouse click */
	GdkModifierType state ; 
	gdk_window_get_pointer(widget->window, &coord_x, &coord_y, &state) ; 
	if(coord_x > 0 && coord_x < WINDOW_WIDTH && coord_y > 0 && coord_y < WINDOW_HEIGHT){
		CoordToGrid(coord_x, coord_y, &grid_x, &grid_y);
	}
	printf("coord_x = %d, coord_y = %d, grid_x = %d, grid_y = %d \n", coord_x, coord_y, grid_x, grid_y);
	//printf("PieceNumber = %d\n", chessboard->PieceNumber);
	
	/* Store or Move Piece */
	chessboard->PieceNumber = PickPiece(chessboard, grid_x, grid_y);	
	if((chessboard->PieceNumber == 1 || chessboard->PieceNumber == 2)){
		StoreDest(chessboard, grid_x, grid_y);
		MovePiece(chessboard);
	}
	else
	{
		//StoreSource(chessboard, grid_x, grid_y);
	}
	printf("PieceNumber = %d\n", chessboard->PieceNumber);
	
	//gtk_widget_destroy(chessboard->table);
	//gtk_container_remove(GTK_CONTAINER(chessboard->window), chessboard->table) ;
	//DrawBoard(chessboard);
	/*printf("chessboard->select = %d\n", chessboard->select);
	
	if(chessboard->select == 1){
		MovePiece(chessboard, grid_x, grid_y);
	}
	
	if(chessboard->select == 0){
		chessboard->PieceNumber = PickPiece(chessboard, grid_x, grid_y);
		printf("chessboard->select = %d\n", chessboard->select);
	}
	else /*
	
	
		
		//gtk_container_remove(GTK_CONTAINER(widget->window), chessboard->table) ; 
		//DrawBoard(chessboard);
		//gtk_widget_show(chessboard->table) ; 
			
	//gtk_widget_modify_fg (chess_icon, GTK_STATE_NORMAL, &color);
	
  
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
void StoreDest(CHESSBOARD *chessboard, int g_x, int g_y){
	chessboard->dest_r = g_x;
	chessboard->dest_c = g_y;
	printf("Dest %d %d \n", chessboard->dest_r , chessboard->dest_c);
}

void StoreSource(CHESSBOARD *chessboard, int g_x, int g_y){
	chessboard->src_r = g_x;
	chessboard->src_c = g_y;
	printf("Stored %d %d \n", chessboard->src_r , chessboard->src_c);
}

void MovePiece(CHESSBOARD *chessboard){
	int src_r, src_c, dest_r, dest_c;
	src_c = chessboard->src_c;
	src_r = chessboard->src_r;
	dest_r = chessboard->dest_r;
	dest_c = chessboard->dest_c;
	
	printf("Moved from %d %d to %d %d\n", src_r, src_c, dest_r, dest_c);
	//Board[dest_r][dest_c] = Board[src_r][src_c];
}

int PickPiece(CHESSBOARD *chessboard, int x, int y){
	if(Board[x][y] != WHITE || Board[x][y] != BLACK){
		chessboard->select = 1;
		switch(Board[x][y])
		{
			case WPAWN:
				printf("Piece selected: White Pawn.\n");
				break;
			case WROOK:
				printf("Piece selected: White Rook.\n");
				break;
			case WBISHOP:
				printf("Piece selected: White Bishop.\n");
				break;
			case WKNIGHT:
				printf("Piece selected: White Knight.\n");
				break;
			case WQUEEN:
				printf("Piece selected: White Queen.\n");
				break;
			case WKING:
				printf("Piece selected: White King.\n");
				break;
				
			case BPAWN:
				printf("Piece selected: Black Pawn.\n");
				break;
			case BROOK:
				printf("Piece selected: Black Rook.\n");
				break;
			case BBISHOP:
				printf("Piece selected: Black Bishop.\n");
				break;
			case BKNIGHT:
				printf("Piece selected: Black Kinght.\n");
				break;
			case BQUEEN:
				printf("Piece selected: Black Queen.\n");
				break;
			case BKING:
				printf("Piece selected: Black King.\n");
				break;
			default:
				break;
		}
		return Board[x][y];
	}
	else{
		chessboard->select = 0;
		return 0;
	}
}

CHESSBOARD *CreateChessBoard(void){
	
	CHESSBOARD *chessboard = malloc(sizeof(CHESSBOARD));
	chessboard->PieceNumber = 0;
	chessboard->src_r = 0;
	chessboard->src_c = 0;
	chessboard->dest_r = 0;
	chessboard->dest_c = 0;
	//chessboard->select = 0;
	return chessboard;
}


