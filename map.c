#include "tools.h"
#include "tiles.h"

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

void addTile(int *chunk, int tile, int x, int y, int z) {
    int i = getIndex(x,y,z);
    writeT(tile, i, chunk);
}

void addUpdate(int *updates, int x, int y, int z) {
    int i = getIndex(x,y,z);
    updates[i] = 1;
}

void fillTile(int *chunk, int tile, int x1, int y1, int z1, int x2, int y2, int z2) {
    for (int i = x1; i <= x2; i++) {
        for (int j = y1; j <= y2; j++) {
            for (int a = z1; a <= z2; a++) {
                addTile(chunk, tile, i, j, a);
            }
        }
    }
}

//Creates a border of STONE that is filled with AIR.
void createBorder(Chunk *CHUNK) {

    int *tiles = CHUNK->chunk;

    fillTile(tiles, STONE, 0, 0, 0, CHUNK_WIDTH-1, 0, CHUNK_LENGTH-1); //changed middle to zero so it doesn't try to access other heights    
    fillTile(tiles, AIR, 1, 0, 1, CHUNK_WIDTH-2, 0, CHUNK_LENGTH-2);
}


void loadMap(Chunk *CHUNK) {

    int *chunk = CHUNK->chunk; //Should I call this "tiles" or "chunk"? I should create another standard.
    int *updates = CHUNK->updates;

    //Centipede
    addTile(chunk, CENTITAIL_S, 1, 0, 2); addUpdate(updates, 1, 0, 2);
    addTile(chunk, CENTIBODY_S, 1, 0, 3);
    addTile(chunk, CENTIBODY_S, 1, 0, 4);
    addTile(chunk, CENTIBODY_S, 1, 0, 5);
    addTile(chunk, CENTIBODY_S, 1, 0, 6);
    addTile(chunk, CENTIBODY_S, 1, 0, 7);
    addTile(chunk, CENTIBODY_S, 1, 0, 8);
    addTile(chunk, CENTIBODY_S, 1, 0, 9);
    addTile(chunk, CENTIHEAD_S, 1, 0, 10); addUpdate(updates, 1, 0, 10);

}