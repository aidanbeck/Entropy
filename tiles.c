#include "main.h"
#include "tools.h"
#include "tiles.h"

//Tile class

//List of each tile class
Tile TILE_TYPES[TILE_TYPE_COUNT];


//SMOKE
void ruleSMOKE(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    
    writeUpdate(AIR, index, updatedChunk, scheduledUpdates);
    //writeT(AIR, index, updatedChunk);
    
    int above = readAbove(index);

    if (readT(above, chunk) == AIR) {
        
        writeUpdate(SMOKE, above, updatedChunk, scheduledUpdates);
    }

}
Tile tileSMOKE = {
    .icon = ':',
    .name = "smoke",
    .rule = ruleSMOKE
};


//FIRE
void ruleFIRE(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    writeUpdate(FIRE2, index, updatedChunk, scheduledUpdates);
}
Tile tileFIRE = {
    .icon = '%',
    .name = "fire",
    .rule = ruleFIRE
};


//FIRE2
void ruleFIRE2(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    writeUpdate(SMOKE, index, updatedChunk, scheduledUpdates);

    int directions[6];
    readAllDirections(index, directions);

    for (int i = 0; i < 6; i++) {
        int tile = readT(directions[i], chunk);
        if (tile == WOOD) {

            writeUpdate(FIRE, directions[i], updatedChunk, scheduledUpdates);
        }

    }
}
Tile tileFIRE2 = {
    .icon = '%',
    .name = "FIRE",
    .rule = ruleFIRE2
};


//MISSILE
void ruleMISSILE(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    int right = readRight(index);
    int tileRight = readT(right, chunk);
    
    if (tileRight == AIR) {

        writeUpdate(SMOKE, index, updatedChunk, scheduledUpdates);
        writeUpdate(MISSILE, right, updatedChunk, scheduledUpdates);

    } else if (tileRight == STONE || tileRight == SAND) {

        writeUpdate(MISSILE2, index, updatedChunk, scheduledUpdates);

    } else {

        writeUpdate(FIRE, index, updatedChunk, scheduledUpdates);
    }
}
Tile tileMISSILE = {
    .icon = '>',
    .name = "missile right",
    .rule = ruleMISSILE
};


//MISSILE2
void ruleMISSILE2(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    int left = readLeft(index);
    int tileLeft = readT(left, chunk);
    
    if (tileLeft == AIR) {

        writeUpdate(SMOKE, index, updatedChunk, scheduledUpdates);
        writeUpdate(MISSILE2, left, updatedChunk, scheduledUpdates);

    } else if (tileLeft == STONE || tileLeft == SAND) {

        writeUpdate(MISSILE, index, updatedChunk, scheduledUpdates);

    } else {

        writeUpdate(FIRE, index, updatedChunk, scheduledUpdates);
    }
}
Tile tileMISSILE2 = {
    .icon = '<',
    .name = "missile left",
    .rule = ruleMISSILE2
};


//WATER
void ruleWATER(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    int directions[6];
    readAllDirections(index, directions);

    for (int i = 1; i < 6; i++) { //loop starts at 1 because 0 is above.

        int tile = readT(directions[i], chunk);
        if (tile == AIR || tile == FIRE || tile == SAND) {

            writeUpdate(WATER, directions[i], updatedChunk, scheduledUpdates);
        }

    }
}
Tile tileWATER = {
    .icon = '~',
    .name = "water",
    .rule = ruleWATER
};


//SAND
void ruleSAND(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    int below = readBelow(index);
    int tileBelow = readT(below, chunk);

    if (tileBelow == AIR || tileBelow == WATER) {
        writeUpdate(AIR, index, updatedChunk, scheduledUpdates);
        writeUpdate(SAND, below, updatedChunk, scheduledUpdates);
    }

    //could also be interesting if it DOESNT wash away if there is air directly above it. Or, it only does if there isn't
}
Tile tileSAND = {
    .icon = 'X',
    .name = "sand",
    .rule = ruleSAND
};

//Compile array of tiles
void compileRules() {
    TILE_TYPES[SMOKE] = tileSMOKE;
    TILE_TYPES[FIRE] = tileFIRE;
    TILE_TYPES[FIRE2] = tileFIRE2;
    TILE_TYPES[MISSILE] = tileMISSILE;
    TILE_TYPES[MISSILE2] = tileMISSILE2;
    TILE_TYPES[WATER] = tileWATER;
    TILE_TYPES[SAND] = tileSAND;
}
