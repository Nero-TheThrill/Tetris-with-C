#pragma once
#include<stdbool.h>
#define WIDTH 12
#define HEIGHT 21
typedef enum
{
	SPACE,BLOCK,WALL,STATIC
}TetrisCell;

typedef enum
{
	I,O,T,S,Z,J,L
}BlockShape;

typedef enum
{
    R0,R90,R180,R270
}BlockRotate;

typedef struct BlockInfo
{
	int x;
	int y;
	bool makenew;
    BlockShape individualBlockShape;
    BlockRotate individualBlockRotate;
}BlockInfo;



void InitializeMap(TetrisCell* TetrisMap,int gamecount);
void PutBlock(TetrisCell* TetrisMap,  BlockInfo* tetrisblock,TetrisCell blocks[][4][4],int gamecount);
void MakeBlockDown(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount);
bool CheckGround(TetrisCell* TetrisMap,BlockInfo* tetrisblock,TetrisCell blocks[][4][4],int gamecount);
void MoveLeft(TetrisCell* TetrisMap,BlockInfo* tetrisblock,TetrisCell blocks[][4][4],int gamecount);
void MoveRight(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount);
bool CheckRightWall(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount);
bool CheckLeftWall(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount);
void Erase(TetrisCell* TetrisMap,int gamecount,int gamenumber);
TetrisCell* Rotate(BlockInfo* tetrisblock, TetrisCell blocks[][4][4]);
void RotUpdate(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4],int gamecount);
bool CheckRotatePossible(TetrisCell* TetrisMap, BlockInfo* tetrisblock, TetrisCell blocks[][4][4], int gamecount);
bool CheckGameOver(TetrisCell* TetrisMap,int gamecount, int gamenumber);