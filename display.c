#include "display.h"
#include "rlutil.h"
void Display(TetrisCell* TetrisMap,int gamecount)
{
	locate(1,1);
	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH*gamecount;j++)
		{
		
			if(i!=0&&i!=HEIGHT-1&&TetrisMap[i*WIDTH*gamecount+j]==WALL)
				printf("|");
			if(i==HEIGHT-1&&TetrisMap[i*WIDTH*gamecount+j]==WALL)
				printf("^");
			if(i != 0 && TetrisMap[i*WIDTH*gamecount+j]==BLOCK)
				printf("*");
			if(TetrisMap[i*WIDTH*gamecount+j]==STATIC)
				printf("*");
			if(TetrisMap[i*WIDTH*gamecount+j]==SPACE)
				printf(" ");
		}
		printf("\n");
	}
	
}
