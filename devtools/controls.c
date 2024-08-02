#include "../main.h"
#include "../physics.h"
#include "../elements/periodicTable.h"

#include <termios.h>
#include <stdio.h>
#include <unistd.h>

int getch(void) {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}



void moveTarget(int x, int y, int z) {
    int px = indexToX(PLAYER.index) + x;
    int py = indexToY(PLAYER.index) + y;

    
                        
    if (px < 1 ) { px = 1; }
    if (px > CHUNK_WIDTH - 2) {px = CHUNK_WIDTH - 2; }
    if (py < 1 ) { py = 1; }
    if (py > CHUNK_LENGTH - 2) {py = CHUNK_LENGTH - 2; }
                        
    PLAYER.target = moveIndex(0,px,py,0);
}

void detectKey() {
    int open = 1;
    while (open == 1) {
        open = 0;
        int c = getch();
        if (c == '\n') { // Check for Enter key
            open = 0;
            break;
        }
        else if (c == 0x1B) { // Check for special key prefix (ESC)
            c = getch();
            if (c == 0x5B) { // Check for [
                c = getch();
                switch (c) {
                    case 0x41:
                        
                        moveTarget(0, -4, 0);

                        open = 0;
                        break;
                    case 0x42:

                        moveTarget(0, 4, 0);
                        open = 0;
                        break;
                    case 0x44:
                        moveTarget(-4, 0, 0);
                        open = 0;
                        break;
                    case 0x43:
                        moveTarget(4, 0, 0);
                        open = 0;
                        break;
                }
            }
        }
    }
}