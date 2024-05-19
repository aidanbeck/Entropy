#include "main.h"
#include "barista.h"
#include "tools.h"

int getIndex(int x, int y, int z) { //useful example of chunk navigation

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

/*
    Creates a border of STONE that is filled with AIR.
    
*/
void createBorder(Chunk *CHUNK) {

    int *tiles = CHUNK->chunk;

    fillTile(tiles, STONE, 0, 0, 0, CHUNK_WIDTH-1, 0, CHUNK_LENGTH-1); //changed middle to zero so it doesn't try to access other heights    
    fillTile(tiles, AIR, 1, 0, 1, CHUNK_WIDTH-2, 0, CHUNK_LENGTH-2);
}


void mapSnek(Chunk *CHUNK) {

    int *chunk = CHUNK->chunk; //normally I should probably call this tiles?
    int *updates = CHUNK->updates;

    addTile(chunk, CENTITAIL_S, 1, 0, 2); addUpdate(updates, 1, 0, 2);

    addTile(chunk, CENTIBODY_S, 1, 0, 3);
    addTile(chunk, CENTIBODY_S, 1, 0, 4);
    addTile(chunk, CENTIBODY_S, 1, 0, 5);
    addTile(chunk, CENTIBODY_S, 1, 0, 6);
    addTile(chunk, CENTIBODY_S, 1, 0, 7);
    addTile(chunk, CENTIBODY_S, 1, 0, 8);
    addTile(chunk, CENTIBODY_S, 1, 0, 9);

    addTile(chunk, CENTIHEAD_S, 1, 0, 10); addUpdate(updates, 1, 0, 10);

    //  +
    // +++
    addTile(chunk, WOOD, 0, 0, 0);
    addTile(chunk, WOOD, 1, 0, 0);
    addTile(chunk, WOOD, 2, 0, 0);
    addTile(chunk, WOOD, 1, 0, 1);

}

void mapTower(Chunk *CHUNK) {

    int *chunk = CHUNK->chunk; //normally I should probably call this tiles?
    int *updates = CHUNK->updates;

    //beams
    // fillTile(chunk, WOOD, 1, 8, 1, 15, 9, 2);   fillTile(chunk, SAND, 1, 7, 1, 15, 8, 2);
    // fillTile(chunk, WOOD, 1, 8, 14, 15, 9, 15); fillTile(chunk, SAND, 1, 7, 14, 15, 8, 15);
    // fillTile(chunk, WOOD, 1, 8, 1, 2, 9, 15);   fillTile(chunk, SAND, 1, 7, 1, 2, 8, 15);
    // fillTile(chunk, WOOD, 14, 8, 1, 15, 9, 15); fillTile(chunk, SAND, 14, 7, 1, 15, 8, 15);

    // //floor beams
    fillTile(chunk, WOOD, 14, 14, 1, 15, 15, 15);
    fillTile(chunk, WOOD, 1, 14, 14, 15, 15, 15);
    fillTile(chunk, WOOD, 1, 14, 1, 15, 15, 2);

    // //tall beams
    // fillTile(chunk, SAND, 1, 2, 1, 15, 3, 2);   fillTile(chunk, WOOD, 1, 3, 1, 15, 4, 2);
    // fillTile(chunk, SAND, 1, 2, 14, 15, 3, 15); fillTile(chunk, WOOD, 2, 3, 14, 15, 4, 15);
    // fillTile(chunk, SAND, 1, 2, 1, 3, 4, 15);   fillTile(chunk, WOOD, 1, 2, 1, 2, 4, 15);
    // fillTile(chunk, SAND, 14, 2, 1, 15, 3, 15); fillTile(chunk, WOOD, 14, 3, 1, 15, 4, 15);

    //pillars
    // fillTile(chunk, WOOD, 1, 1, 1, 2, 15, 2);
    // fillTile(chunk, WOOD, 14, 1, 1, 15, 15, 2);
    // fillTile(chunk, WOOD, 1, 1, 14, 2, 15, 15);
    // fillTile(chunk, WOOD, 14, 1, 14, 15, 15, 15);

    //sand pillar
    //fillTile(chunk, SAND, 7, 5, 7, 10, 15, 10);

    //wooden floor
    //fillTile(chunk, WOOD, 1, 14, 1, 5, 15, 5);
    // fillTile(chunk, WATER, 2, 14, 2, 4, 15, 4);

    //friendly missile
    //addTile(chunk, MISSILE2, 12, 13, 12);
    //addTile(chunk, MISSILE2, 13, 10, 14);

    //traveler
    // addTile(chunk, HUMAN, 4, 4, 4);
    // addTile(chunk, HUMAN, 5, 5, 5);
    // addTile(chunk, HUMAN, 6, 6, 6);
    // addTile(chunk, HUMAN, 7, 7, 7);
    // addTile(chunk, HUMAN, 8, 8, 8);
    // addTile(chunk, HUMAN, 9, 9, 9);
    // addTile(chunk, HUMAN, 10, 10, 10);

    addTile(chunk, CENTIHEAD_E, 8, 14, 10); addUpdate(updates, 8, 14, 10);
    addTile(chunk, CENTIBODY_S, 8, 14, 9);
    addTile(chunk, CENTIBODY_S, 8, 14, 8);
    addTile(chunk, CENTIBODY_S, 8, 14, 7);
    addTile(chunk, CENTIBODY_S, 8, 14, 6);
    addTile(chunk, CENTIBODY_S, 8, 14, 5);
    addTile(chunk, CENTIBODY_S, 8, 14, 4);
    addTile(chunk, CENTIBODY_S, 8, 14, 3);
    addTile(chunk, CENTITAIL_S, 8, 14, 2); addUpdate(updates, 8, 14, 2);


    addTile(chunk, CENTIHEAD_SE, 10, 14, 10); addUpdate(updates, 10, 14, 10);
    addTile(chunk, CENTIBODY_S, 10, 14, 9);
    addTile(chunk, CENTIBODY_S, 10, 14, 8);
    addTile(chunk, CENTIBODY_S, 10, 14, 7);
    addTile(chunk, CENTIBODY_S, 10, 14, 6);
    addTile(chunk, CENTIBODY_S, 10, 14, 5);
    addTile(chunk, CENTIBODY_S, 10, 14, 4);
    addTile(chunk, CENTIBODY_S, 10, 14, 3);
    addTile(chunk, CENTITAIL_S, 10, 14, 2); addUpdate(updates, 10, 14, 2);

    //addTile(chunk, SAND, 6, 14, 10);

    //tile updates
    addUpdate(updates, 12, 13, 12);
    addUpdate(updates, 13, 10, 14);

    addUpdate(updates, 4, 4, 4);
    addUpdate(updates, 5, 5, 5);
    addUpdate(updates, 6, 6, 6);
    addUpdate(updates, 7, 7, 7);
    addUpdate(updates, 8, 8, 8);
    addUpdate(updates, 9, 9, 9);
    addUpdate(updates, 10, 10, 10);
}