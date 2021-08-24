#include <stdio.h>
#include<stdlib.h>
#include "tetris.h"
#include "display.h"
#include "input.h"
#include "rlutil.h"
#include <stdbool.h>
#include <time.h>

TetrisCell blocks[7][4][4]=
{
    {
        { 0,0,0,0 },
        { 0,0,0,0 },
        { 1,1,1,1 },
        { 0,0,0,0 }
    },
    {
        { 0,0,0,0 },
        { 0,1,1,0 },
        { 0,1,1,0 },
        { 0,0,0,0 }
    },
    {
        { 0,0,0,0 },
        { 0,1,0,0 },
        { 1,1,1,0 },
        { 0,0,0,0 }
    },
    {
        { 0,0,0,0 },
        { 0,1,1,0 },
        { 1,1,0,0 },
        { 0,0,0,0 }
    },
    {
        { 0,0,0,0 },
        { 1,1,0,0 },
        { 0,1,1,0 },
        { 0,0,0,0 }
    },
    {
        { 0,0,0,0 },
        { 1,0,0,0 },
        { 1,1,1,0 },
        { 0,0,0,0 }
    },
    {
        { 0,0,0,0 },
        { 0,0,1,0 },
        { 1,1,1,0 },
        { 0,0,0,0 }
    }
};



int main()
{	
	//Initialize////////////////////////////////////////

    srand(time(NULL));


	time_t last_gravity_time;
	time(&last_gravity_time);
	double gravity_delay_seconds = 0.05;
    int count = 0;
    bool* IsGameOver;
	bool IsRunning=true;
	int gamecount=0;
    int currentgame = 0;
	TetrisCell* TetrisMap;
	BlockInfo* blockinfo;
    PLAYER_MOVE keyinput;
	FILE *fp=fopen("config.txt","rt");
	if(fp==NULL)
	{
		fp=fopen("config.txt","wt");
		gamecount=2;
		fprintf(fp,"%d",gamecount);
	}
	fscanf(fp,"%d",&gamecount);
	TetrisMap=(TetrisCell*)malloc(sizeof(TetrisCell)*gamecount*WIDTH*HEIGHT);
	blockinfo=(BlockInfo*)malloc(sizeof(BlockInfo)*gamecount);
    IsGameOver = (bool*)malloc(sizeof(bool)*gamecount);
	for(int i=0;i<gamecount;i++)
	{
        blockinfo[i].makenew = true;
        blockinfo[i].individualBlockRotate = R0;
        IsGameOver[i] = false;
	}

	InitializeMap(TetrisMap,gamecount);
	hidecursor();
	PrintControls();
	getch();
	cls();
	////////////////////////////////////////////////////
	
	
	//GameLoop//////////////////////////////////////////
	while(IsRunning)
	{ 
        for(int i=0;i<gamecount;i++)
        {
            Erase(TetrisMap, gamecount, i);
            if (!IsGameOver[i]&&blockinfo[i].makenew)
            {
                blockinfo[i].individualBlockShape = rand() % 7;
                blockinfo[i].makenew=false;
               
                blockinfo[i].x = WIDTH * i + 4;
                blockinfo[i].y = 0;

                blockinfo[i].individualBlockRotate = R0;

                PutBlock(TetrisMap, &(blockinfo[i]),blocks,gamecount);
            }
        }
                
		Display(TetrisMap, gamecount);
                keyinput=GetInput();

                if (keyinput == QUIT)
                    IsRunning = false;
				else if(keyinput==PAUSE)
				{		
					cls();
					printf("====================================\n\n\n\n\n\n\n\n                PAUSE\n\n\n\n\n\n\n\n     -press any key to restart-\n====================================");
					getch();
					cls();
				}
                else if(keyinput== MOVE_RIGHT)
                {
                    MoveRight(TetrisMap, &(blockinfo[currentgame]), blocks, gamecount);
                }
                else if (keyinput == MOVE_LEFT)
                {
                    MoveLeft(TetrisMap, &(blockinfo[currentgame]), blocks, gamecount);
                }
                else if (keyinput == SPEED_DOWN)
                {
                    MakeBlockDown(TetrisMap, &(blockinfo[currentgame]), blocks, gamecount);
                }
                else if (keyinput == ROTATE_RIGHT)
                {
                    if (CheckRotatePossible(TetrisMap, &(blockinfo[currentgame]), blocks, gamecount))
                    {
                        if (blockinfo[currentgame].individualBlockRotate == R0)
                            blockinfo[currentgame].individualBlockRotate = R90;
                        else  if (blockinfo[currentgame].individualBlockRotate == R90)
                            blockinfo[currentgame].individualBlockRotate = R180;
                        else  if (blockinfo[currentgame].individualBlockRotate == R180)
                            blockinfo[currentgame].individualBlockRotate = R270;
                        else if (blockinfo[currentgame].individualBlockRotate == R270)
                            blockinfo[currentgame].individualBlockRotate = R0;
                        RotUpdate(TetrisMap, &(blockinfo[currentgame]), blocks, gamecount);
                    }
                }
                else if (keyinput == PREVIOUS_GAME)
                {
                    currentgame--;
                    if (currentgame == -1)
                    {
                        currentgame = gamecount-1;
                    }
 
                }
                else if (keyinput == NEXT_GAME)
                {
                    currentgame++;
                    if (currentgame == gamecount)
                    {
                        currentgame = 0;
                    }
                }
		time_t current_time;
		time(&current_time);
		//Pull down blocks
		if(difftime(current_time, last_gravity_time) >= gravity_delay_seconds)
		{
			last_gravity_time = current_time;
			// Lower active Tetris piece
            for(int i=0;i<gamecount;i++)
                MakeBlockDown(TetrisMap, &(blockinfo[i]), blocks, gamecount);
		
		}
        for (int i=0; i<gamecount; i++)
        {
            if (CheckGameOver(TetrisMap,gamecount, i))
            {
               IsGameOver[i] = true;
            }
        }
        count = 0;
        for (int i=0; i<gamecount; i++)
        {
            if (IsGameOver[i])
            {
                count++;
            }
        }
        if (count == gamecount)
            IsRunning = false;
		//Check game end -> if game ends, set IsRunning to false.
	}
	/////////////////////////////////////////////////////
	
	
	//Game Ends//////////////////////////////////////////
	showcursor();

    free(blockinfo);
	free(TetrisMap);
	/////////////////////////////////////////////////////
	return 0;	
}
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
	
	