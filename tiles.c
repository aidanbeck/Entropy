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


Mesh Donut[8] = {
    //North is -1z, south is +1z, because screen is flipped
    { .x= 0, .y=0, .z= 1, .length=8 }, //N
    { .x= 1, .y=0, .z= 1 }, //NE
    { .x= 1, .y=0, .z= 0 }, //E
    { .x= 1, .y=0, .z= -1 }, //SE
    { .x= 0, .y=0, .z= -1 }, //S
    { .x= -1, .y=0, .z= -1 }, //SW
    { .x= -1, .y=0, .z= 0 }, //W
    { .x= -1, .y=0, .z= 1 } //NW
};

int headDirections[8] = {
    CENTIHEAD_N,
    CENTIHEAD_NE,
    CENTIHEAD_E,
    CENTIHEAD_SE,
    CENTIHEAD_S,
    CENTIHEAD_SW,
    CENTIHEAD_W,
    CENTIHEAD_NW
};
void ruleCENTIHEAD(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    //get direction & target
    int head = readT(index, chunk);
    int body;

    //get next space
    int targetIndex = index;
    int nextTarget;

    switch (head) {

        case CENTIHEAD_N:
            body = CENTIBODY_N;
            targetIndex = moveIndexZ(index, -1);
            nextTarget = moveIndexZ(targetIndex, -1);
            break;

        case CENTIHEAD_S:
            body = CENTIBODY_S;
            targetIndex = moveIndexZ(index, 1);
            nextTarget = moveIndexZ(targetIndex, 1);
            break;

        case CENTIHEAD_E:
            body = CENTIBODY_E;
            targetIndex = moveIndexX(index,1);
            nextTarget = moveIndexX(targetIndex, 1);
            break;

        case CENTIHEAD_W:
            body = CENTIBODY_W;
            targetIndex = moveIndexX(index, -1);
            nextTarget = moveIndexX(targetIndex, -1);
            break;
        
        case CENTIHEAD_NE:
            body = CENTIBODY_NE;
            targetIndex = moveIndex(index, 1, 0, -1);
            nextTarget = moveIndex(targetIndex, 1, 0, -1);
            break;

        case CENTIHEAD_NW:
            body = CENTIBODY_NW;
            targetIndex = moveIndex(index, -1, 0, -1);
            nextTarget = moveIndex(targetIndex, -1, 0, -1);
            break;

        case CENTIHEAD_SE:
            body = CENTIBODY_SE;
            targetIndex = moveIndex(index, 1, 0, 1);
            nextTarget = moveIndex(targetIndex, 1, 0, 1);
            break;
        
        case CENTIHEAD_SW:
            body = CENTIBODY_SW;
            targetIndex = moveIndex(index, -1, 0, 1);
            nextTarget = moveIndex(targetIndex, -1, 0, 1);
            break;
    }
    
    //set new head
    if (readT(targetIndex, chunk) == AIR) { //if next space is AIR

        //move head & body forwards
        writeUpdate(body, index, updatedChunk, scheduledUpdates);

        if (readT(nextTarget, chunk) != AIR) { //if space after next is air
            //detect where the head should turn
            //create mesh of free spaces
            int directions[8];
            getMeshIndexes(targetIndex, Donut, directions);
            int newHead;

            //for each space in the mesh
            for (int i = 0; i < 8; i++) {
                if (readT(directions[i],chunk) == AIR) {

                    //turn head
                    newHead = headDirections[i];

                }
            }
            writeUpdate(newHead, targetIndex, updatedChunk, scheduledUpdates);
        } else {
            writeUpdate(head, targetIndex, updatedChunk, scheduledUpdates);
        }

        
        
    }
    
    //turn head towards free space
    else {
        //die?
    }

}
Tile tileCENTIHEAD = {
    .icon = 'O',
    .name = "centipede",
    .rule = ruleCENTIHEAD
};


int tailDirections[8] = {
    CENTITAIL_N,
    CENTITAIL_NE,
    CENTITAIL_E,
    CENTITAIL_SE,
    CENTITAIL_S,
    CENTITAIL_SW,
    CENTITAIL_W,
    CENTITAIL_NW
};
int bodyDirections[8] = {
    CENTIBODY_N,
    CENTIBODY_NE,
    CENTIBODY_E,
    CENTIBODY_SE,
    CENTIBODY_S,
    CENTIBODY_SW,
    CENTIBODY_W,
    CENTIBODY_NW
};
void ruleCENTITAIL(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    //get direction & target
    int tail = readT(index, chunk);

    //get next space
    int targetIndex = index;

    switch (tail) {

        case CENTITAIL_N:
            targetIndex = moveIndexZ(index, 1);
            break;

        case CENTITAIL_S:
            targetIndex = moveIndexZ(index, -1);
            break;

        case CENTITAIL_E:
            targetIndex = moveIndexX(index,1);
            break;

        case CENTITAIL_W:
            targetIndex = moveIndexX(index, -1);
            break;
        
        case CENTITAIL_NE:
            targetIndex = moveIndex(index, 1, 0, 1);
            break;

        case CENTITAIL_NW:
            targetIndex = moveIndex(index, -1, 0, 1);
            break;

        case CENTITAIL_SE:
            targetIndex = moveIndex(index, 1, 0, -1);
            break;
        
        case CENTITAIL_SW:
            targetIndex = moveIndex(index, -1, 0, -1);
            break;
    }

    //set new tail
    int newTail;
    int pointingTo = readT(targetIndex, chunk);
    if (pointingTo >= CENTIBODY_N && pointingTo <= CENTIBODY_SW) { //if pointing to CENTIBODY

        for (int i = 0; i < 8; i++) {

            if (pointingTo == bodyDirections[i]) { //find direction of body

                newTail = tailDirections[i]; //set tail to that direction
            }

        }
        writeUpdate(newTail, targetIndex, updatedChunk, scheduledUpdates);
        
        //turn OG tail into air
        writeUpdate(AIR, index, updatedChunk, scheduledUpdates);
    } else {
        updateT(scheduledUpdates, index); //should die?
    }

    

}
Tile tileCENTITAIL = {
    .icon = '[',
    .name = "centipede",
    .rule = ruleCENTITAIL
};


//BALL
int ballDirections[8] = {
    BALL_N,
    BALL_NE,
    BALL_E,
    BALL_SE,
    BALL_S,
    BALL_SW,
    BALL_W,
    BALL_NW
};
void ruleBALL(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    int nextIndex = index;

    //nextIndex = moveIndexX(index, -1);
    nextIndex = moveIndex(index, -1, 0, -1);

    int tileAtNextIndex = readT(nextIndex, chunk);

    if (tileAtNextIndex == AIR) {
        writeUpdate(BALL_N, nextIndex, updatedChunk, scheduledUpdates);
        writeUpdate(AIR, index, updatedChunk, scheduledUpdates);
    }

    


}
Tile tileBALL = {
    .icon = 'O',
    .name = "ball",
    .rule = ruleBALL
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

    TILE_TYPES[CENTIHEAD_N] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_S] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_E] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_W] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_NE] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_NW] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_SE] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_SW] = tileCENTIHEAD;

    TILE_TYPES[CENTITAIL_N] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_S] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_E] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_W] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_NE] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_NW] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_SE] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_SW] = tileCENTITAIL;

    TILE_TYPES[BALL_N] = tileBALL;
    TILE_TYPES[BALL_S] = tileBALL;
    TILE_TYPES[BALL_E] = tileBALL;
    TILE_TYPES[BALL_W] = tileBALL;

    //initialize humans
    int humanCount = 7;
    for (int i = 0; i < humanCount; i++) {

        Entity human;
        human.id = i + 4;
        human.index = human.id*CHUNK_WIDTH*CHUNK_HEIGHT + human.id*CHUNK_HEIGHT + human.id;
        human.moveCountdown = 0;
        human.xDir = 0;
        human.yDir = 0;
        human.zDir = 0;

        HUMANS[i] = human;
    }
}
