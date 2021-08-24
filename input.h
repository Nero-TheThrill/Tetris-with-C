#pragma once

typedef enum 
{
    QUIT,
    MOVE_RIGHT,
    MOVE_LEFT,
    SPEED_DOWN,
    ROTATE_RIGHT,
    PREVIOUS_GAME,
    NEXT_GAME,
    NONE,
	PAUSE,
    UNKOWN
} PLAYER_MOVE;

PLAYER_MOVE GetInput(void);

void PrintControls(void);