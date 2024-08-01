#include "main.h"

//for initializeWorld
#include "laws/lawTable.h"
#include "elements/periodicTable.h"

//for printing
#include "devtools/printer.h"
#include <stdio.h>

//for tick timing
#include <unistd.h>

//barista
#include "barista/barista.h"

void initializeWorld(Chunk *CHUNK, Physics *PHYSICS) {
    CHUNK->physics = PHYSICS;
    CHUNK->tick = 0;
    CHUNK->hotLawCount = 2;
    CHUNK->hotLawMax = 255;
    initializeArray(CHUNK->TILES, CHUNK_SIZE, 0);
    initializeArray(CHUNK->UPDATES, CHUNK_SIZE, 0);
    prepareChunk(CHUNK);

    compileLaws(PHYSICS);
    compileElements(PHYSICS);

    //Player is defined globally. This may not be a good idea.
    CHUNK->truck = &PLAYER;
    PLAYER.chunk = CHUNK;
    PLAYER.index = moveIndex(0, PLAYER.x, PLAYER.y, 0);
    PLAYER.target = PLAYER.index;
}

void loopTicks(Chunk *CHUNK, Physics *PHYSICS) {
    for (; CHUNK->tick < TICK_LIMIT; CHUNK->tick++) {
        printIcons2d(CHUNK);
        printUpdates2d(CHUNK);
        printHotLawTable(CHUNK);
        updateChunk(CHUNK, PHYSICS);

        usleep(TICK_DURATION);  
    }
}

int main() {

    Chunk CHUNK;
    Physics PHYSICS;
    initializeWorld(&CHUNK, &PHYSICS);
    loadMap(&CHUNK);
    setBaristaChunk(&CHUNK);

    if (COMPILE_MODE == 0) { loopTicks(&CHUNK, &PHYSICS); }
    
    return 0;
}