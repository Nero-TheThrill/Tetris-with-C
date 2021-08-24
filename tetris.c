#include "tetris.h"

#include <stdlib.h>

void InitializeMap(TetrisCell* TetrisMap, int gamecount)
{
	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH*gamecount;j++)
		{
			TetrisMap[i*WIDTH*gamecount+j]=SPACE;		
		}
	}
	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<WIDTH*gamecount;j++)
		{
			if(j%WIDTH==11)
			{
				TetrisMap[i*WIDTH*gamecount+j]=WALL;
			}
			if(j%WIDTH==0)
			{
				TetrisMap[i*WIDTH*gamecount+j]=WALL;		
			}
			if(i==HEIGHT-1)
			{
				TetrisMap[i*WIDTH*gamecount+j]=WALL;		
			}
		}
	}
}

void PutBlock(TetrisCell* TetrisMap, BlockInfo* tetrisblock,TetrisCell blocks[][4][4],int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x;
    TetrisCell* RotatedBlock = Rotate(tetrisblock, blocks);

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(RotatedBlock[i * 4 + j] ==1)
                TetrisMap[startpos + i * WIDTH*gamecount + j] = RotatedBlock[i * 4 + j];
        }
    }
    free(RotatedBlock);
}

void MakeBlockDown(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x;
    TetrisCell* RotatedBlock = Rotate(tetrisblock, blocks);

   
    if(!CheckGround(TetrisMap,tetrisblock,blocks,gamecount)&&!tetrisblock->makenew)
    {
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                if (RotatedBlock[i * 4 + j] == 1)
                    TetrisMap[startpos + i * WIDTH*gamecount + j] = 0;
            }
        }
        tetrisblock->y++;
        y = tetrisblock->y;
        startpos = y * WIDTH*gamecount + x;
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                if (RotatedBlock[i * 4 + j] == 1)
                    TetrisMap[startpos + i * WIDTH*gamecount + j] = RotatedBlock[i * 4 + j];
            }
        }
    }
    free(RotatedBlock);

}

bool CheckGround(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = (y+1) * WIDTH *gamecount + x;
    TetrisCell* RotatedBlock = Rotate(tetrisblock, blocks);

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (RotatedBlock[i * 4 + j] == 1)
            {
                if(TetrisMap[startpos + i * WIDTH*gamecount + j] ==WALL|| TetrisMap[startpos + i * WIDTH*gamecount + j] == STATIC)
                {
                    startpos = y* WIDTH *gamecount + x;
                    for (int k=0; k < 4; k++)
                    {
                        for (int l=0; l < 4; l++)
                        {
                            if (RotatedBlock[k * 4 + l] == 1)
                                TetrisMap[startpos + k * WIDTH*gamecount + l] = STATIC;
                        }
                    }
                    tetrisblock->makenew = true;
                    return true;
                }
            }
       
        }
    }
    free(RotatedBlock);
    return false;
}

void MoveLeft(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x;
    TetrisCell* RotatedBlock = Rotate(tetrisblock, blocks);

    if (!CheckLeftWall(TetrisMap, tetrisblock, blocks, gamecount))
    {
        for (int i=0; i < 4; i++)
        {
            for (int j=0; j < 4; j++)
            {
                if (RotatedBlock[i * 4 + j] == 1)
                    TetrisMap[startpos + i * WIDTH*gamecount + j] = 0;
            }
        }
        tetrisblock->x--;
        x = tetrisblock->x;
        startpos = y * WIDTH*gamecount + x;
        for (int i=0; i < 4; i++)
        {
            for (int j=0; j < 4; j++)
            {
                if (RotatedBlock[i * 4 + j] == 1)
                    TetrisMap[startpos + i * WIDTH*gamecount + j] = RotatedBlock[i * 4 + j];
            }
        }
    }
    free(RotatedBlock);
}

void MoveRight(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x;
    TetrisCell* RotatedBlock = Rotate(tetrisblock, blocks);

    if (!CheckRightWall(TetrisMap, tetrisblock, blocks, gamecount))
    {
        for (int i=0; i < 4; i++)
        {
            for (int j=0; j < 4; j++)
            {
                if (RotatedBlock[i * 4 + j] == 1)
                    TetrisMap[startpos + i * WIDTH*gamecount + j] = 0;
            }
        }
        tetrisblock->x++;
        x = tetrisblock->x;
        startpos = y * WIDTH*gamecount + x;
        for (int i=0; i < 4; i++)
        {
            for (int j=0; j < 4; j++)
            {
                if (RotatedBlock[i * 4 + j] == 1)
                    TetrisMap[startpos + i * WIDTH*gamecount + j] = RotatedBlock[i * 4 + j];
            }
        }
    }
    free(RotatedBlock);
}

bool CheckRightWall(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x+1;
    TetrisCell* RotatedBlock = Rotate(tetrisblock, blocks);

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (RotatedBlock[i * 4 + j] == 1)
            {
                if (TetrisMap[startpos + i * WIDTH*gamecount + j] == WALL || TetrisMap[startpos + i * WIDTH*gamecount + j] == STATIC)
                    return true;
            }

        }
    }
    free(RotatedBlock);
    return false;
}
bool CheckLeftWall(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x -1;
    TetrisCell* RotatedBlock=Rotate(tetrisblock,blocks);

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (RotatedBlock[i*4+j] == 1)
            {
                if (TetrisMap[startpos + i * WIDTH*gamecount + j] == WALL || TetrisMap[startpos + i * WIDTH*gamecount + j] == STATIC)
                    return true;
            }

        }
    }
    free(RotatedBlock);
    return false;
}

void Erase(TetrisCell* TetrisMap, int gamecount,int gamenumber)
{

    for(int i=HEIGHT-1;i>=0;i--)
    {
        int countstatic = 0;
        for(int j=WIDTH*gamenumber;j<WIDTH*gamenumber+WIDTH;j++)
        {
            if (TetrisMap[i*WIDTH*gamecount + j] == STATIC)
                countstatic++;
        }
        if(countstatic==WIDTH-2)
        {

            for(int k=i-1;k>=0;k--)
            {
                for(int l=WIDTH*gamenumber;l<WIDTH*gamenumber+WIDTH;l++)
                {
                    TetrisMap[(k+1)*WIDTH*gamecount+l] = TetrisMap[k*WIDTH*gamecount+l];
                }
            }
            i++;
        }
    }

}

TetrisCell* Rotate(BlockInfo* tetrisblock, TetrisCell blocks[][4][4])
{
    BlockShape blockshape = tetrisblock->individualBlockShape;
    BlockRotate blockrotate = tetrisblock->individualBlockRotate;
   
    TetrisCell* tmprotblock=(TetrisCell*)malloc(sizeof(TetrisCell)*16);
    TetrisCell* rotblock= (TetrisCell*)malloc(sizeof(TetrisCell) * 16);

    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            rotblock[i*4+j] = blocks[blockshape][i][j];
            tmprotblock[i * 4 + j] = blocks[blockshape][i][j];
        }
    }
    if(blockrotate==R0)
    {
        for (int i=0; i<4; i++)
        {
            for (int j=0; j<4; j++)
            {
                rotblock[i * 4 + j] = blocks[blockshape][i][j];
            }
        }
    }
    else
    {

        for (int i=0; i < (int)blockrotate; i++)
        {
            rotblock[0] = tmprotblock[3];
            rotblock[1] = tmprotblock[7];
            rotblock[2] = tmprotblock[11];
            rotblock[3] = tmprotblock[15];
            rotblock[4] = tmprotblock[2];
            rotblock[5] = tmprotblock[6];
            rotblock[6] = tmprotblock[10];
            rotblock[7] = tmprotblock[14];
            rotblock[8] = tmprotblock[1];
            rotblock[9] = tmprotblock[5];
            rotblock[10] = tmprotblock[9];
            rotblock[11] = tmprotblock[13];
            rotblock[12] = tmprotblock[0];
            rotblock[13] = tmprotblock[4];
            rotblock[14] = tmprotblock[8];
            rotblock[15] = tmprotblock[12];

            for (int k=0; k < 4; k++)
            {
                for (int l=0; l < 4; l++)
                {
                    tmprotblock[k * 4 + l] = rotblock[k * 4 + l];
                }
            }
        }
    }
    free(tmprotblock);

    return rotblock;
}

void RotUpdate(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x;



    BlockInfo tmpinfo = *tetrisblock;
    if (tmpinfo.individualBlockRotate == R0)
        tmpinfo.individualBlockRotate = R270;
    else  if (tmpinfo.individualBlockRotate == R90)
        tmpinfo.individualBlockRotate = R0;
    else  if (tmpinfo.individualBlockRotate == R180)
        tmpinfo.individualBlockRotate = R90;
    else if (tmpinfo.individualBlockRotate == R270)
        tmpinfo.individualBlockRotate = R180;
    TetrisCell* RotatedBlock_1 = Rotate(&tmpinfo, blocks);


    for (int i=0; i < 4; i++)
    {
        for (int j=0; j < 4; j++)
        {
            if (RotatedBlock_1[i * 4 + j] == 1)
                TetrisMap[startpos + i * WIDTH*gamecount + j] = 0;
        }
    }
    TetrisCell* RotatedBlock_2 = Rotate(tetrisblock, blocks);
    for (int i=0; i < 4; i++)
    {
        for (int j=0; j < 4; j++)
        {
            if (RotatedBlock_2[i * 4 + j] == 1)
                TetrisMap[startpos + i * WIDTH*gamecount + j] = RotatedBlock_2[i * 4 + j];
        }
    }
    free(RotatedBlock_2);
    free(RotatedBlock_1);
}


bool CheckRotatePossible(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount)
{
    int x = tetrisblock->x;
    int y = tetrisblock->y;
    int startpos = y * WIDTH *gamecount + x;


    BlockInfo tmpinfo = *tetrisblock;
    if (tmpinfo.individualBlockRotate == R0)
        tmpinfo.individualBlockRotate = R90;
    else  if (tmpinfo.individualBlockRotate == R90)
        tmpinfo.individualBlockRotate = R180;
    else  if (tmpinfo.individualBlockRotate == R180)
        tmpinfo.individualBlockRotate = R270;
    else if (tmpinfo.individualBlockRotate == R270)
        tmpinfo.individualBlockRotate = R0;

    TetrisCell* Checkthis = Rotate(&tmpinfo, blocks);


    for (int i=0; i<4; i++)
    {
        for (int j=0; j<4; j++)
        {
            if (Checkthis[i * 4 + j] == 1)
            {
                if (TetrisMap[startpos + i * WIDTH*gamecount + j] == WALL || TetrisMap[startpos + i * WIDTH*gamecount + j] == STATIC)
                    return false;
            }

        }
    }
    free(Checkthis);
    return true;
}

bool CheckGameOver(TetrisCell* TetrisMap,int gamecount, int gamenumber)
{
    for (int j=0; j < WIDTH; j++)
    {
            
        if (TetrisMap[gamecount*WIDTH+gamenumber*WIDTH + j] == STATIC)
        {
            return true;
        }
    }

    return false;
}


