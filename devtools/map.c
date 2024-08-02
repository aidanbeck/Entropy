#include "../main.h"
#include "../physics.h"
#include "../elements/periodicTable.h"
#include <stdio.h>

/*
    getIndex, addTile, addUpdate, & fillTile seem to be redundant due to the functions in
    tools.c. However, they take XYZ coordinates instead of an index. This makes "mapping",
    or creating structures by writing a function, significantly easier.
*/

int getIndex(int x, int y, int z) {
    return moveIndex(0,x,y,z);
}

void addTile(Chunk *CHUNK, int tile, int x, int y, int z) {
    int i = getIndex(x,y,z);
    //CHUNK->TILES[i] = tile;
    place(tile, i, CHUNK);
}

void addUpdate(Chunk *CHUNK, int x, int y, int z) {
    int i = getIndex(x,y,z);
    CHUNK->nextUpdates[i] = 1;
}

void addBoth(Chunk *CHUNK, int tile, int x, int y, int z) {
    int i = getIndex(x,y,z);
    place(tile, i, CHUNK);
    CHUNK->nextUpdates[i] = 1;
}

void fillTile(Chunk *CHUNK, int tile, int x1, int y1, int z1, int x2, int y2, int z2) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            for (int a = z1; a <= z2; a++) {
                addTile(CHUNK, tile, i, j, a);
            }
        }
    }
}

//Creates a border of STONE that is filled with AIR.
void createBorder(Chunk *CHUNK) {

    fillTile(CHUNK, STONE, 0, 0, 0, CHUNK_WIDTH-1, CHUNK_LENGTH-1, 0); 
    fillTile(CHUNK, AIR,   1, 1, 0, CHUNK_WIDTH-2, CHUNK_LENGTH-2, 0);
}

void loadMap(Chunk *CHUNK) {

    createBorder(CHUNK);
    fillTile(CHUNK, STONE, 30, 3, 0, 31, 10, 0);


    addBoth(CHUNK, TRUCK, PLAYER.x, PLAYER.y, 0);

    addTile(CHUNK, TIRE, PLAYER.x+2, PLAYER.y, 0);

    //addTile(CHUNK, SPAWNRANDOM, 50, 3, 0); addUpdate(CHUNK, 50, 3, 0);

    //addTile(CHUNK, COW, 3, 3, 0); addUpdate(CHUNK, 3, 3, 0);

    // addTile(CHUNK, GAS, 20, 3, 0);
    addTile(CHUNK, STONE, 28, 3, 0);
    // addTile(CHUNK, STONE, 28, 3, 0);

    // addTile(CHUNK, FIRE, 33, 3, 0); //addUpdate(CHUNK, 33, 3, 0);

    // fillTile(CHUNK, WOOD, 34, 3, 0, 36, 10, 0);
    addBoth(CHUNK, ZOMBIE, 33, 4, 0);

    addBoth(CHUNK, ZOMBIE, 33, 6, 0);

    addBoth(CHUNK, ZOMBIE, 23, 9, 0);

    addBoth(CHUNK, MAILBOX, 42, 7, 0);

    addBoth(CHUNK, SPAWNPACKAGE, 43, 7, 0);
}