#include<stdio.h>
#include<conio.h>

char p1_name[100], p2_name[100];               	  	//Player Names
char c_board[10][21]=                          		//Chess Board Matrix
{
	{" A B C D E F G H  \0"},
	{"8EbHbCbQbKbCbHbEb8\0"},
	{"7SbSbSbSbSbSbSbSb7\0"},
	{"6                6\0"},
	{"5                5\0"},
	{"4                4\0"},
	{"3                3\0"},
	{"2SwSwSwSwSwSwSwSw2\0"},
	{"1EwHwCwQwKwCwHwEw1\0"},
	{" A B C D E F G H  \0"},
};
int king(int i, int j, int I, int J);				//Piece Wrong Movement Functions
int queen(int i, int j, int I,int J);
int bishop(int i, int j, int I,int J);
int knight(int i, int j, int I,int J);
int rook(int i, int j, int I,int J);

int start()                                     	//Game Start Sequence
{                                               	//Asks Player names and
	printf("Welcome to Chess\n");            		//input to play
	printf("Enter Player1's name:\n");
	gets(p1_name);
	printf("Enter Player2's name:\n");
	gets(p2_name);
	printf("Press any button to play");
	getch();
	return 0;
}

int board()                                      //Displays Board
{
	int i,j;
	clrscr();
	for(i=0;i<10;i++)
	{
		for(j=0;j<19;j++)
		{
			printf("%c",c_board[i][j]);
		}
		printf("\n");
	}
	return 0;
}

int piece_sel()                                 			 //Takes Input for moving
{                                               			 //pieces

	static int count=1;                     				 //Move Counter
	int i = 8, j = 1, I = 8, J = 1, x, move = 0;                                     //i,j are Piece Coordinates and I,J are Move Coordinates Move is a counter for black or white move white = 0 black = 1
	char col, Col, row, Row, loc[2], Loc[2];									//
	if(count % 2)
	{
		printf("It is White's Move \n");
		move = 0;
	}
	else
	{
		printf("It is Black's Move \n");
		move = 1;
	}

	printf("Which piece to move \n");       		 //Piece Selector
	printf("Enter Location \n");
	gets(loc);
	col=loc[0];
	row=loc[1];

	for(x=49;x<row;x++)
	{
		i--;
	}
	for(x=65;x<col;x++)
	{
		j=j+2;
	}

	if(move==1 && c_board[i][j+1]=='w')				//Wrong Colour Piece Selection Detector
	{
		printf("Black can't move that piece \n");
		getch();
		return 0;
	}

	else if(move==0 && c_board[i][j+1]=='b')
	{
		printf("White can't move that piece \n");
		getch();
		return 0;
	}

	printf("Where do you want to move \n");  				//Piece Placement Selector
	printf("Enter Location \n");
	gets(Loc);
	Col=Loc[0];
	Row=Loc[1];
	
	for(x=49;x<Row;x++)
	{
		I--;
	}
	for(x=65;x<Col;x++)
	{
		J=J+2;
	}

	if(move==0 && c_board[I][J+1]=='w')						//Own Piece Killing Avoidance
	{
		printf("There is already a White Piece there \n");
		getch();
		return 0;
	}

	else if(move==1 && c_board[I][J+1]=='b')
	{
		printf("There is already a Black Piece there \n");
		getch();
		return 0;
	}

	if(c_board[i][j]=='K')									//Piece Detection and Movement Validator
	king(i, j, I, J);
	else if(c_board[i][j]=='Q')
	queen(i, j, I, J);
	/*else if(c_board[j][i]=='C')							//Activate once Bishop, Knight, Rook codes written
	bishop(i, j, I, J);
	else if(c_board[j][i]=='H')
	knight(i, j, I, J);
	else if(c_board[j][i]=='E')
	rook(i, j, I, J);*/
	count++;
	return 0;
}

int move(int i, int j, int I, int J)
{						 						//Piece Movement
	char temp[2];
	if(c_board[I][J]==' ')                   	//For Moving in a Empty Space 
	{
		temp[0] = c_board[I][J];
		temp[1] = c_board[I][J+1];
		c_board[I][J] = c_board[i][j];
		c_board[I][J+1] = c_board[i][j+1];
		c_board[i][j] = temp[0];
		c_board[i][j+1] = temp[1];
	}
	else                                     	//For Capturing Piece
	{
		c_board[I][J] = c_board[i][j];
		c_board[I][J+1] = c_board[i][j+1];
		c_board[i][j] = ' ';
		c_board[i][j+1] = ' ';
	}
	return 0;

}

int king(int i, int j, int I, int J)								//Done
{
	int count = 0;
	if(I != i+2 || J != j)
		if(I != i-2 || J != j)
			if(I != i || J == j+1)
				if(I != i || J != j-1)
				count = 0;
				else
				count = 1;
			else
			count = 1;
		else
		count = 1;
	else
	count = 1;
	if(count == 1)
	move(i, j, I, J);
	else
	printf("Invalid Move");
	return 0;
}

int queen(int i, int j, int I,int J)								//Done
{
	int count = 0, x, y;

	for(x=2, y=1 ; x<=8 ; x += 2, y++)									//Queen Horizontal and Vertical Move
	{
		if(I != i+x || J != j)
			if(I != i-x || J != j)
				if(I != i || J != j+y)
					if(I != i || J != j-y)
						count = 0;
		if(count == 1)
			{
				move(i, j, I, J);
				return 0;
			}
	}

	for (x=1 ; x<=8 ; x++)											//Queen Vertical Move
	{
		if(I != i || J != j+x)
			if(I != i || J != j-x)
				count = 0;
			else
			{
				count = 1;
				break;
			}
		else
		{
			count = 1;
			break;
		}
	}
	if(count == 1)
	{
		move(i, j, I, J);
		return 0;
	}

	for (x=1, y=1 ; x<=8 ; x+=2, y++)											//Queen Left to Right Diagonal Move
	{
		if(I != i+x || J != j+x)
			if(I != i-x || J != j-x)
				count = 0;
			else
			{
				count = 1;
				break;
			}
		else
		{
			count = 1;
			break;
		}
	}
	if(count == 1)
	{
		move(i, j, I, J);
		return 0;
	}

	for (x=1 ; x<=8 ; x++)											//Queen Right to Left Diagonal Move
	{
		if(I != i-x || J != j+x)
			if(I != i+x || J != j-x)
				count = 0;
			else
			{
				count = 1;
				break;
			}
		else
		{
			count = 1;
			break;
		}
	}
	if(count == 1)
	{
		move(i, j, I, J);
		return 0;
	}
	else
	{
		printf("Invalid Move");
		return 0;
	}

}

/*int bishop(int i, int j, int I, int J)								//Not Done
{
	int count = 0, x;

	for (x=1 ; x<=8 ; x++)											//Bishop Left to Right Diagonal Move
	{
		if(I != i+x || J != j+x)
			if(I != i-x || J != j-x)
				count = 0;
			else
			{
				count = 1;
				break;
			}
		else
		{
			count = 1;
			break;
		}
	}
	if(count == 1)
	{
		move(i, j, I, J);
		return 0;
	}

	for (x=1 ; x<=8 ; x++)											//Bishop Right to Left Diagonal Move
	{
		if(I != i-x || J != j+x)
			if(I != i+x || J != j-x)
				count = 0;
			else
			{
				count = 1;
				break;
			}
		else
		{
			count = 1;
			break;
		}
	}
	if(count == 1)
	{
		move(i, j, I, J);
		return 0;
	}
	else
	{
		printf("Invalid Move");
		return 0;
	}


}*/

/*int knight(int i, int j, int I, int J)								//Not Done
{
	int count = 0;
	if(I != i+2 || J != j)
		if(I != i-2 || J != j)
			if(I != i || J == j+1)
				if(I != i || J != j-1)
				count = 0;
				else
				count = 1;
			else
			count = 1;
		else
		count = 1;
	else
	count = 1;
	if(count == 1)
	move(i, j, I, J);
	return 0;
}*/

/*int rook(int i, int j, int I, int J)								//Not Done
{
	int count = 0;
	if(I != i+2 || J != j)
		if(I != i-2 || J != j)
			if(I != i || J == j+1)
				if(I != i || J != j-1)
				count = 0;
				else
				count = 1;
			else
			count = 1;
		else
		count = 1;
	else
	count = 1;
	if(count == 1)
	move(i, j, I, J);
	return 0;
}*/

/*int pawn(int i, int j, int I, int J)								//Not Done
{
	int count = 0;
	if(I != i+2 || J != j)
		if(I != i-2 || J != j)
			if(I != i || J == j+1)
				if(I != i || J != j-1)
				count = 0;
				else
				count = 1;
			else
			count = 1;
		else
		count = 1;
	else
	count = 1;
	if(count == 1)
	move(i, j, I, J);
	return 0;
}*/


int main()                                       //Main Function
{
	int chc_mate=0, i=0;
	clrscr();
	start();
	board();
	piece_sel();
	clrscr();
	board();
	do					 //Runs a Input and Display
	{					 //Loop until Check Mate
	piece_sel();
	board();
	i++;
	}while(i==5);
	getch();
	return 0;
}