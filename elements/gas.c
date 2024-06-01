#include "periodictable.h"
#include "../tools.h"
#include "../moves.h"

Mesh CompassRose2[4] = {
    //  0 
    // 2&3
    //  1 
    { .x= 0,    .y= -1,     .z= 0, .length=4 }, //N
    { .x= 0,    .y= 1,      .z= 0 }, //S
    { .x= 1,    .y= 0,      .z= 0 }, //E
    { .x= -1,   .y= 0,      .z= 0 }, //W
};

Mesh Explosion[20] = {
    //  89A
    // J701B
    // I6&2C
    // H543D
    //  GFE

    { .x= -1,   .y= -2,     .z= 0, .length=20 },
    { .x=  0,   .y= -2,     .z= 0 },
    { .x=  1,   .y= -2,     .z= 0 },

    { .x= -2,   .y= -1,     .z= 0 },
    { .x= -1,   .y= -1,     .z= 0 },
    { .x=  0,   .y= -1,     .z= 0 },
    { .x=  1,   .y= -1,     .z= 0 },
    { .x=  2,   .y= -1,     .z= 0 },

    { .x= -2,   .y=  0,     .z= 0 },
    { .x= -1,   .y=  0,     .z= 0 },
    // // { .x=  0,   .y=  0,     .z= 0 },
    { .x=  1,   .y=  0,     .z= 0 },
    { .x=  2,   .y=  0,     .z= 0 },

    { .x= -2,   .y=  1,     .z= 0 },
    { .x= -1,   .y=  1,     .z= 0 },
    { .x=  0,   .y=  1,     .z= 0 },
    { .x=  1,   .y=  1,     .z= 0 },
    { .x=  2,   .y=  1,     .z= 0 },

    { .x=  1,   .y=  2,     .z= 0 },
    { .x=  0,   .y=  2,     .z= 0 },
    { .x= -1,   .y=  2,     .z= 0 },
};

void damageGAS(int *TILES, int *nextTiles, int *nextUpdates, int index) {
    
    writeUpdate(FIRE, index, nextTiles, nextUpdates); //turn into fire

    int directionIndex[20];
    getMeshIndexes(index, Explosion, directionIndex);

    for (int i = 0; i < 20; i++) {

        if (indexInBounds(directionIndex[i]) == 0) { continue; }

        if ( indexIsEmpty( directionIndex[i], TILES, nextTiles) == 1) {
            writeUpdate(FIRE, directionIndex[i], nextTiles, nextUpdates); //segway
            printf("[%d]",directionIndex[i]);
        }
    }
}

void ruleGAS(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    int tileInDirection[4];
    readMesh(index, CompassRose2, tileInDirection, TILES);

    int directionIndex[4];
    getMeshIndexes(index, CompassRose2, directionIndex);


    for (int i = 0; i < 4; i++) {

        if (tileInDirection[i] == FIRE) {
            
            damageGAS(TILES, nextTiles, nextUpdates, index);
            break;
        }
    }
}
Element eGAS = {
    .icon = 'U',
    .name = "Gas can",
    .rule = ruleGAS
};