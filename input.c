#include "rlutil.h"

#include "input.h"

PLAYER_MOVE GetInput(void)
{
    int cnt = kbhit(); // for ANSI escapes processing
    if (!cnt)
        return NONE;
    int k = getch();
    switch (k)
    {
#ifdef _WIN32
        case 27:
            return QUIT;
#else  // _WIN32
        case 155: // single-character CSI
        case 27:
        {
            // Process ANSI escape sequences
            if (cnt >= 3 && getch() == '[')
            {
                switch (k = getch())
                {
                    case 'A':
                        return ROTATE_RIGHT;
                    case 'B':
                        return SPEED_DOWN;
                    case 'C':
                        return MOVE_RIGHT;
                    case 'D':
                        return MOVE_LEFT;
                    default:
                        return UNKOWN;
                }
            }
            else
                return QUIT;
        }
#endif // _WIN32
        case 'a':
            return MOVE_LEFT;
        case 'd':
            return MOVE_RIGHT;
        case 'q':
            return QUIT;
        case 's':
            return SPEED_DOWN;
        case 'w':
            return ROTATE_RIGHT;

        case 'z':
            return PREVIOUS_GAME;
        case 'x':
            return NEXT_GAME;
		case 'p':
			return PAUSE;
        case 224:
        {
            int kk;
            switch (kk = getch())
            {
                case 72:
                    return ROTATE_RIGHT;
                case 75:
                    return MOVE_LEFT;
                case 77:
                    return MOVE_RIGHT;
                case 80:
                    return SPEED_DOWN;
                default:
                    return UNKOWN;
            }
        }

        default:
            return UNKOWN;
    }
}

void PrintControls(void)
{
    puts("-------- TETRIS --------\n\n");
    puts("Use the arrow keys or W,A,S,D to play.\n"
         "\tLeft  - Move Left\n"
         "\tRight - Move Right\n"
         "\tUp    - Rotate\n"
         "\tDown  - Move Down Quickly\n\n"
         "Quit the game with Q or Esc\n"
         "Cycle through the games with Z and X\n");
    puts("\nYou change the number of active games by modifying config.txt.\nValid "
         "values are 1-8\n\n");
}
