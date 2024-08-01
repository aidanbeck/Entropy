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
                        
                        PLAYER.target = moveIndex(PLAYER.index, 0, -4, 0);

                        open = 0;
                        break;
                    case 0x42:

                        PLAYER.target = moveIndex(PLAYER.index, 0, 4, 0);
                        open = 0;
                        break;
                    case 0x44:
                        PLAYER.target = moveIndex(PLAYER.index, -4, 0, 0);
                        open = 0;
                        break;
                    case 0x43:
                        PLAYER.target = moveIndex(PLAYER.index, 4, 0, 0);
                        open = 0;
                        break;
                }
            }
        }
    }
}