#include <stdio.h>
#include <emscripten/emscripten.h>
#include "main.h"
#include "updates.h"
#include "tools.h"

extern Chunk WORLD[WORLD_SIZE];
extern int chunksWithUpdates[WORLD_SIZE];
extern int tick;

void jsWriteIcon(int index, int tile) {
    EM_ASM({
        Module.writeIcon($0, $1);
    }, index, tile);
}

extern EMSCRIPTEN_KEEPALIVE int gameLoop() {

    updateWorld(WORLD, chunksWithUpdates);
    tick++;
    return tick;
}

extern EMSCRIPTEN_KEEPALIVE int writeFromJS(int index, int tile) {

    Chunk *toWrite = &WORLD[0];
    int *tiles = toWrite->TILES;
    int *UPDATES = toWrite->UPDATES;   

    //Write to C
    writeT(tile, index, tiles);
    updateT(UPDATES, index);

    return UPDATES[index];
}