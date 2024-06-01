#include "periodictable.h"
#include "../tools.h"
#include "../moves.h"

Mesh CompassRose[4] = {
    //  0 
    // 2&3
    //  1 
    { .x= 0,    .y= -1,     .z= 0, .length=4 }, //N
    { .x= 0,    .y= 1,      .z= 0 }, //S
    { .x= 1,    .y= 0,      .z= 0 }, //E
    { .x= -1,   .y= 0,      .z= 0 }, //W
};

//FIRE
void ruleFIRE(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    writeUpdate(FIRE2, index, nextTiles, nextUpdates);
}
Element eFIRE = {
    .icon = '%',
    .name = "fire",
    .rule = ruleFIRE
};

//FIRE2
void ruleFIRE2(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    writeUpdate(AIR, index, nextTiles, nextUpdates); //removed smoke for now

    int tileInDirection[4];
    readMesh(index, CompassRose, tileInDirection, TILES);

    int directionIndex[4];
    getMeshIndexes(index, CompassRose, directionIndex);


    for (int i = 0; i < 4; i++) {

        if (tileInDirection[i] == WOOD || tileInDirection[i] == SPAWN_RANDOM) {
            writeUpdate(FIRE, directionIndex[i], nextTiles, nextUpdates);
        }
    }
}
Element eFIRE2 = {
    .icon = '%',
    .name = "FIRE",
    .rule = ruleFIRE2
};