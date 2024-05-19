/*
    COMPILE WITH: gcc main.c printer.c map.c tiles.c tools.c updates.c -o main.exe -Wall -Wpedantic -Werror

    OR

    emcc -o ../deadletter/latte.html main.c printer.c map.c tiles.c tools.c updates.c barista.c -O0 --shell-file ../barista/html_template/latte.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_main', '_gameLoop', '_writeFromJS']"
*/

#include "main.h"
#include "printer.h"
#include "map.h"
#include "tiles.h"
#include "tools.h"
#include "updates.h"

#define MODE 1
/*
    Files that reference emscripten functions:
    * tools.c -- writeT
*/


Chunk WORLD[WORLD_SIZE];
int chunkUpdates[WORLD_SIZE]; //like tileupdates but for chunks that have tileupdates

int tick = 0;

int main() {

    //set up world
    for (int i = 0; i < WORLD_SIZE; i++) {

        Chunk newChunk;

        initializeArray(newChunk.chunk, CHUNK_SIZE, 0);
        initializeArray(newChunk.updates, CHUNK_SIZE, 0);

        newChunk.x = 0;
        newChunk.y = 0;
        newChunk.z = 0;

        WORLD[i] = newChunk;
    }
    Chunk *startChunk = &WORLD[0]; //create example chunk
    chunkUpdates[0] = 1; //turn on example chunk

    compileRules();
    createBorder(startChunk);
    mapSnek(startChunk);

    //if in console mode (0)
    if (MODE == 0) {

        //render & update chunk i times
        for (int i = 0; i < TICK_LIMIT; i++) {
            printf("\n\n---------------------Tick %d---------------------", tick);
            printChunk2d(startChunk->chunk);
            printUpdates2d(startChunk->updates);

            updateWorld(WORLD, chunkUpdates);
            tick++;
            usleep(TICK_DURATION);
        }
    }
    

    return 0;
}