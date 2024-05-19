//COMPILE WITH emcc -o ../compiled/latte.html barista.c -O3 --shell-file ../html_template/latte.html -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']"
//COMPILE WITH emcc -o ../compiled/latte.html barista.c -O0 --shell-file ../html_template/latte.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_multiplier']"

#include <stdio.h>
#include <emscripten/emscripten.h>
#include "main.h"
#include "updates.h"
#include "tools.h"


extern Chunk WORLD[WORLD_SIZE];
extern int chunkUpdates[WORLD_SIZE];
extern int tick;

void jsWriteIcon(int index, int tile) {
    EM_ASM({
        Module.writeIcon($0, $1);
    }, index, tile);
}

extern EMSCRIPTEN_KEEPALIVE int gameLoop() {

    updateWorld(WORLD, chunkUpdates);
    tick++;
    return tick;
}

extern EMSCRIPTEN_KEEPALIVE int writeFromJS(int index, int tile) {

    Chunk *toWrite = &WORLD[0];
    int *tiles = toWrite->chunk;
    int *updates = toWrite->updates;   

    //Write to C
    writeT(tile, index, tiles);
    updateT(updates, index);

    return updates[index];
}