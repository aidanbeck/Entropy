#include "tools.h"
#include "elements/periodictable.h"

/*
    getIndex, addTile, addUpdate, & fillTile seem to be redundant due to the functions in
    tools.c. However, they take XYZ coordinates instead of an index. This makes "mapping",
    or creating structures by writing a function, significantly easier.
*/

/*
    This file is out of date with current directional standards! It will need to be adjusted.
*/

int getIndex(int x, int y, int z) {

    x = x;
    y = y * CHUNK_WIDTH * CHUNK_LENGTH;
    z = z * CHUNK_WIDTH;

    return x + y + z;
}

void addTile(int *TILES, int tile, int x, int y, int z) {
    int i = getIndex(x,y,z);
    writeT(tile, i, TILES);
}

void addUpdate(int *UPDATES, int x, int y, int z) {
    int i = getIndex(x,y,z);
    UPDATES[i] = 1;
}

void fillTile(int *TILES, int tile, int x1, int y1, int z1, int x2, int y2, int z2) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            for (int a = z1; a <= z2; a++) {
                addTile(TILES, tile, i, j, a);
            }
        }
    }
}

//Creates a border of STONE that is filled with AIR.
void createBorder(Chunk *CHUNK) {

    int *tiles = CHUNK->TILES;

    fillTile(tiles, STONE, 0, 0, 0, CHUNK_WIDTH-1, 0, CHUNK_LENGTH-1); //changed middle to zero so it doesn't try to access other heights    
    fillTile(tiles, AIR, 1, 0, 1, CHUNK_WIDTH-2, 0, CHUNK_LENGTH-2);
}


void loadMap(Chunk *CHUNK) {

    int *TILES = CHUNK->TILES;
    int *UPDATES = CHUNK->UPDATES;

    //SPAWNER
    // addTile(TILES, SPAWN_RANDOM, 0, 0, 0);
    // addUpdate(UPDATES, 0, 0, 0);

    //WALL
    // fillTile(TILES, GAS, 40, 0, 1, 40, 0, 13);

    // //PACKAGE SPAWNERS
    fillTile(TILES, SPAWNER, 147, 0, 5, 149, 0, 7);

    addUpdate(UPDATES, 147, 0, 5);
    addUpdate(UPDATES, 148, 0, 5);
    addUpdate(UPDATES, 149, 0, 5);
    addUpdate(UPDATES, 147, 0, 6);
    addUpdate(UPDATES, 148, 0, 6);
    addUpdate(UPDATES, 149, 0, 6);
    addUpdate(UPDATES, 147, 0, 7);
    addUpdate(UPDATES, 148, 0, 7);
    addUpdate(UPDATES, 149, 0, 7);

}