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


//HUMAN
Entity human4 = {
    .index = 4*CHUNK_WIDTH*CHUNK_HEIGHT + 4*CHUNK_HEIGHT + 4,
    .id = 4,
    .xDir = 0,
    .yDir = 0,
    .zDir = 0,
    .moveCountdown = 0
};
Entity human5 = {
    .index = 5*CHUNK_WIDTH*CHUNK_HEIGHT + 5*CHUNK_HEIGHT + 5,
    .id = 5,
    .xDir = 0,
    .yDir = 0,
    .zDir = 0,
    .moveCountdown = 0
};
Entity human6 = {
    .index = 6*CHUNK_WIDTH*CHUNK_HEIGHT + 6*CHUNK_HEIGHT + 6,
    .id = 6,
    .xDir = 0,
    .yDir = 0,
    .zDir = 0,
    .moveCountdown = 0
};
Entity human7 = {
    .index = 7*CHUNK_WIDTH*CHUNK_HEIGHT + 7*CHUNK_HEIGHT + 7,
    .id = 7,
    .xDir = 0,
    .yDir = 0,
    .zDir = 0,
    .moveCountdown = 0
};
Entity human8 = {
    .index = 8*CHUNK_WIDTH*CHUNK_HEIGHT + 8*CHUNK_HEIGHT + 8,
    .id = 8,
    .xDir = 0,
    .yDir = 0,
    .zDir = 0,
    .moveCountdown = 0
};
Entity human9 = {
    .index = 9*CHUNK_WIDTH*CHUNK_HEIGHT + 9*CHUNK_HEIGHT + 9,
    .id = 9,
    .xDir = 0,
    .yDir = 0,
    .zDir = 0,
    .moveCountdown = 0
};
Entity human10 = {
    .index = 10*CHUNK_WIDTH*CHUNK_HEIGHT + 10*CHUNK_HEIGHT + 10,
    .id = 10,
    .xDir = 0,
    .yDir = 0,
    .zDir = 0,
    .moveCountdown = 0
};

Entity defaultHuman = {
    .index = -1,
    .id = -1,
    .xDir = -1,
    .yDir = -1,
    .zDir = -1,
    .moveCountdown = -1
};

Entity HUMANS[7];

void ruleHUMAN(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    //Find out what human you are
    Entity *You = &defaultHuman;
    for (int i = 0; i < 7; i++) {
        if (index == HUMANS[i].index) {
            You = &HUMANS[i]; //!!!printf("\nfound index%d, id%d", HUMANS[i].index, HUMANS[i].id);
        }
    }

    if (You->index == -1) { //needed?
        return;
    }

    int below = readBelow(index);
    int tileBelow = readT(below, chunk);

    if (tileBelow == AIR || tileBelow == WATER) { //if falling
        writeUpdate(AIR, index, updatedChunk, scheduledUpdates);
        writeUpdate(HUMAN, below, updatedChunk, scheduledUpdates);
        You->index = below;
    
    } else if (You->moveCountdown == 0) { //if deciding

        //srand(getpid()); //use system id or something for random number idk
        int random = rand() % 10;

        if (random == 1) {
            You->xDir = 0;
        } else if (random == 2) { 
            You->xDir = 1; 
        } else if (random == 3) {
            You->xDir = -1;
        } else if (random == 4) {
            You->yDir = 0;
        } else if (random == 5) {
            You->yDir = 1;
        } else if (random == 6) {
            You->yDir = -1;
        } else if (random == 7) {
            You->zDir = 0;
        } else if (random == 8) {
            You->zDir = 1;
        } else if (random == 9) {
            You->zDir = -1;
        }

        You->moveCountdown = 8;
        //printf("\ndecided x%d y%d z%d", You->xDir, You->yDir, You->zDir);
        updateT(scheduledUpdates, index);

    } else {

        updateT(scheduledUpdates, index);
        You->moveCountdown--;
        //printf("\ncountdown %d", You->moveCountdown);

        int newIndex = moveIndex(index, You->xDir, You->yDir, You->zDir);
        int newTile = readT(newIndex, chunk);

        if (newTile == AIR || newTile == WATER || newTile == WOOD) {
            writeUpdate(SMOKE, index, updatedChunk, scheduledUpdates);
            writeUpdate(HUMAN, newIndex, updatedChunk, scheduledUpdates);

            //build sand structure
            int below = readBelow(index);
            int tileBelow = readT(below, chunk);
            if (tileBelow == WOOD) {
                writeT(SAND, index, updatedChunk);
            }
            if (tileBelow == SAND) {
                writeT(WOOD, index, updatedChunk);
            }
            if (newTile == WATER || below == STONE) {
                writeT(WOOD, index, updatedChunk);
            }
            

            //printf("\nm%d", newIndex);
            You->index = newIndex;
            
        }

    }
    


}
Tile tileHUMAN = {
    .icon = '&',
    .name = "human",
    .rule = ruleHUMAN
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
    TILE_TYPES[HUMAN] = tileHUMAN;

    //humans
    HUMANS[0] = human4;
    HUMANS[1] = human5;
    HUMANS[2] = human6;
    HUMANS[3] = human7;
    HUMANS[4] = human8;
    HUMANS[5] = human9;
    HUMANS[6] = human10;
}
