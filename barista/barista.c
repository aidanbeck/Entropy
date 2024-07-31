#include "../main.h"

Chunk *baristaChunk;

void setBaristaChunk(Chunk *CHUNK) {
    baristaChunk = CHUNK;
}

#if COMPILE_MODE == 1 //emcc mode

#include <emscripten/emscripten.h>
#include "../updates.h"
#include "../physics.h"

void placeToJS(int index, int tile) { //write icon TO js FROM C
    EM_ASM({
        Module.writeIcon($0, $1);
    }, index, tile);
}

extern EMSCRIPTEN_KEEPALIVE int tickFromJS() { //take target index as input?

    updateChunk(baristaChunk, baristaChunk->physics);
    //setTruckTarget(targetIndex);
    return 0;
}

extern EMSCRIPTEN_KEEPALIVE int placeFromJS(int index, int tile) {

    //index++;
    
    uint8_t byteTile = (uint8_t)tile;

    uplaces(byteTile, index, baristaChunk);

    return baristaChunk->UPDATES[index];
}

extern EMSCRIPTEN_KEEPALIVE void setTruckTarget(int index) {

    Truck *truck = baristaChunk->truck;

    //update truck information
    truck->target = index;  
}

#endif