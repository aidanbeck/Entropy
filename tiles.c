#include "main.h"
#include "tiles.h"

//Tile class

//List of each tile class
Tile TILE_TYPES[TILE_TYPE_COUNT];


//SMOKE
void ruleSMOKE(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    
    updatedChunk[index] = AIR; registerUpdate(scheduledUpdates, index);

    if (chunk[index-CHUNK_LENGTH] == AIR) { //-CHUNK_LENGHT is basically y + 1
        updatedChunk[index-CHUNK_LENGTH] = SMOKE; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH);     
    }
}
Tile tileSMOKE = {
    .icon = ':',
    .name = "smoke",
    .rule = ruleSMOKE
};


//FIRE
void ruleFIRE(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    updatedChunk[index] = FIRE2; registerUpdate(scheduledUpdates, index);
}
Tile tileFIRE = {
    .icon = '%',
    .name = "fire",
    .rule = ruleFIRE
};


//FIRE2
void ruleFIRE2(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    updatedChunk[index] = SMOKE; registerUpdate(scheduledUpdates, index);
    if (chunk[index+1] == WOOD) {
        updatedChunk[index+1] = FIRE; registerUpdate(scheduledUpdates, index+1);
    }
    if (chunk[index-1] == WOOD) {
        updatedChunk[index-1] = FIRE; registerUpdate(scheduledUpdates, index-1);
    }
    if (chunk[index+CHUNK_LENGTH] == WOOD) {
        updatedChunk[index+CHUNK_LENGTH] = FIRE; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH);
    }
    if (chunk[index-CHUNK_LENGTH] == WOOD) {
        updatedChunk[index-CHUNK_LENGTH] = FIRE; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH);
    }
    if (chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == WOOD) {
        updatedChunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] = FIRE; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH*CHUNK_HEIGHT);
    }
    if (chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == WOOD) {
        updatedChunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] = FIRE; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH*CHUNK_HEIGHT);
    }
}
Tile tileFIRE2 = {
    .icon = '%',
    .name = "FIRE",
    .rule = ruleFIRE2
};


//MISSILE
void ruleMISSILE(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    if (chunk[index+1] == AIR) {
        updatedChunk[index] = SMOKE; registerUpdate(scheduledUpdates, index);
        updatedChunk[index+1] = MISSILE; registerUpdate(scheduledUpdates, index+1);
    } else if (chunk[index+1] == STONE || chunk[index+1] == SAND) {
        updatedChunk[index] = MISSILE2; registerUpdate(scheduledUpdates, index);
    } else {
        updatedChunk[index] = FIRE; registerUpdate(scheduledUpdates, index);
    }
}
Tile tileMISSILE = {
    .icon = '>',
    .name = "missile right",
    .rule = ruleMISSILE
};


//MISSILE2
void ruleMISSILE2(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    if (chunk[index-1] == AIR) {
        updatedChunk[index] = SMOKE; registerUpdate(scheduledUpdates, index);
        updatedChunk[index-1] = MISSILE2; registerUpdate(scheduledUpdates, index+1);
    } else if (chunk[index-1] == STONE || chunk[index-1] == SAND) {
        updatedChunk[index] = MISSILE; registerUpdate(scheduledUpdates, index);
    } else {
        updatedChunk[index] = FIRE; registerUpdate(scheduledUpdates, index);
    }
}
Tile tileMISSILE2 = {
    .icon = '<',
    .name = "missile left",
    .rule = ruleMISSILE2
};


//WATER
void ruleWATER(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    //left and right
    if (chunk[index+1] == AIR || chunk[index+1] == FIRE || chunk[index+1] == SAND) {
        updatedChunk[index+1] = WATER; registerUpdate(scheduledUpdates, index+1);
    }
    if (chunk[index-1] == AIR || chunk[index-1] == FIRE || chunk[index-1] == SAND) {
        updatedChunk[index-1] = WATER; registerUpdate(scheduledUpdates, index-1);
    }
    
    //downwards
    if (chunk[index+CHUNK_LENGTH] == AIR || chunk[index+CHUNK_LENGTH] == FIRE || chunk[index+CHUNK_LENGTH] == SAND) {
        updatedChunk[index+CHUNK_LENGTH] = WATER; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH);
    }

    //forwards and back
    if (chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == AIR || chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == FIRE || chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == SAND) {
        updatedChunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] = WATER; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH*CHUNK_HEIGHT);
    }
    if (chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == AIR || chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == FIRE || chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == SAND) {
        updatedChunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] = WATER; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH*CHUNK_HEIGHT);
    }
}
Tile tileWATER = {
    .icon = '~',
    .name = "water",
    .rule = ruleWATER
};


//SAND
void ruleSAND(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    if (chunk[index+CHUNK_LENGTH] == AIR || chunk[index+CHUNK_LENGTH] == WATER) {
        updatedChunk[index] = AIR; registerUpdate(scheduledUpdates, index);
        updatedChunk[index+CHUNK_LENGTH] = SAND; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH);
    }
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
    //TILE_TYPES[WATER] = WATER;
    //TILE_TYPES[SAND] = SAND;
}
