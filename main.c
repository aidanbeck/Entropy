/*
    ## MODE 0 ##
    gcc *.c elements/ *.c -o main.exe -Wall -Wpedantic -Werror

    ## MODE 1 ##
    emcc -o ../deadletter/latte.html main.c printer.c map.c tiles.c tools.c updates.c barista.c -O0 --shell-file ../barista/html_template/latte.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_main', '_gameLoop', '_writeFromJS']"

    ## Files that reference emscripten functions ##
    * tools.c -- writeT
*/

#define MODE 0

#include "main.h" //
#include "printer.h" //
#include "map.h" //
#include "elements/periodictable.h"
#include "tools.h" //
#include "updates.h"

#include <stdio.h>
#include <unistd.h>

int tick = 0;
Chunk WORLD[WORLD_SIZE];
int chunksWithUpdates[WORLD_SIZE];

int main() {

    compileElements();

    //Create Example Chunk
    Chunk *startChunk = &WORLD[0];
    chunksWithUpdates[0] = 1;

    //Map Preset
    createBorder(startChunk);
    loadMap(startChunk);

    if (MODE == 0) { //Should this be it's own function?

        //Render & Update Example Chunk
        for (int i = 0; i < TICK_LIMIT; i++) {

            printf("\n\n---------------------Tick %d---------------------", tick);
            printUpdates2d(startChunk->UPDATES);
            printIcons2d(startChunk->TILES);
            
            updateWorld(WORLD, chunksWithUpdates);
            tick++;
            usleep(TICK_DURATION);
        }
    }
    

    return 0;
}