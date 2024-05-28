#include "main.h"
#include "tools.h"
#include "tiles.h"
#include "moves.h"

//List of each tile class
Tile TILE_TYPES[TILE_TYPE_COUNT];


Tile tileAIR = {
    .icon = ' ',
    .name = "air",
};

Tile tileSTONE = {
    .icon = '#',
    .name = "stone",
};

Tile tileWOOD = {
    .icon = '+',
    .name = "wood",
};

Tile tileCENTIBODY = {
    .icon = ':',
    .name = "centipede body",
};

//FIRE
void ruleFIRE(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    writeUpdate(FIRE2, index, nextTiles, nextUpdates);
}
Tile tileFIRE = {
    .icon = '%',
    .name = "fire",
    .rule = ruleFIRE
};


Mesh CompassRose[4] = {
    //  0 
    // 2&3
    //  1 
    { .x= 0,    .y= -1,     .z= 0, .length=4 }, //N
    { .x= 0,    .y= 1,      .z= 0 }, //S
    { .x= 1,    .y= 0,      .z= 0 }, //E
    { .x= -1,   .y= 0,      .z= 0 }, //W
};
//FIRE2
void ruleFIRE2(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    writeUpdate(AIR, index, nextTiles, nextUpdates); //removed smoke for now

    int tileInDirection[4];
    readMesh(index, CompassRose, tileInDirection, TILES);

    int directionIndex[4];
    getMeshIndexes(index, CompassRose, directionIndex);


    for (int i = 0; i < 4; i++) {

        if (tileInDirection[i] == WOOD) {
            writeUpdate(FIRE, directionIndex[i], nextTiles, nextUpdates);
        }
    }
}
Tile tileFIRE2 = {
    .icon = '%',
    .name = "FIRE",
    .rule = ruleFIRE2
};

Mesh Donut[8] = {
    // 701
    // 6&2
    // 543
    { .x= 0,    .y= -1,     .z= 0, .length=8 }, //N
    { .x= 1,    .y= -1,     .z= 0 }, //NE
    { .x= 1,    .y= 0,      .z= 0 }, //E
    { .x= 1,    .y= 1,      .z= 0 }, //SE
    { .x= 0,    .y= 1,      .z= 0 }, //S
    { .x= -1,   .y= 1,      .z= 0 }, //SW
    { .x= -1,   .y= 0,      .z= 0 }, //W
    { .x= -1,   .y= -1,      .z= 0 } //NW
};
Mesh DonutInverted[8] = {
    // 345
    // 2&6
    // 107
    { .x= 0,    .y= 1,     .z= 0, .length=8 }, //N opposite
    { .x= -1,    .y= 1,     .z= 0 }, //NE  opposite
    { .x= -1,    .y= 0,      .z= 0 }, //E  opposite
    { .x= -1,    .y= -1,      .z= 0 }, //SE  opposite
    { .x= 0,    .y= -1,      .z= 0 }, //S  opposite
    { .x= 1,   .y= -1,      .z= 0 }, //SW  opposite
    { .x= 1,   .y= 0,      .z= 0 }, //W  opposite
    { .x= 1,   .y= 1,      .z= 0 } //NW  opposite
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
void ruleCENTIHEAD(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    //get head direction
    int head = readT(index, TILES);

    //target index of next space
    int targetIndex = index;

    //get index the target is facing
    int nextTarget;

    //initialize body
    int body;


    switch (head) {

        case CENTIHEAD_N:
            body = CENTIBODY_N;
            targetIndex = moveIndexY(index, -1);
            nextTarget = moveIndexY(targetIndex, -1);
            break;

        case CENTIHEAD_S:
            body = CENTIBODY_S;
            targetIndex = moveIndexY(index, 1);
            nextTarget = moveIndexY(targetIndex, 1);
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
            targetIndex = moveIndex(index, 1, -1, 0);
            nextTarget = moveIndex(targetIndex, 1, -1, 0);
            break;

        case CENTIHEAD_NW:
            body = CENTIBODY_NW;
            targetIndex = moveIndex(index, -1, -1, 0);
            nextTarget = moveIndex(targetIndex, -1, -1, 0);
            break;

        case CENTIHEAD_SE:
            body = CENTIBODY_SE;
            targetIndex = moveIndex(index, 1, 1, 0);
            nextTarget = moveIndex(targetIndex, 1, 1, 0);
            break;
        
        case CENTIHEAD_SW:
            body = CENTIBODY_SW;
            targetIndex = moveIndex(index, -1, 1, 0);
            nextTarget = moveIndex(targetIndex, -1, 1, 0);
            break;
    }
    
    //set new head
    if (readT(targetIndex, TILES) == AIR) { //if next space is AIR

        //move head & body forwards
        writeUpdate(body, index, nextTiles, nextUpdates);

        if (readT(nextTarget, TILES) != AIR) { //if space after next is air
            //detect where the head should turn
            //create mesh of free spaces
            int directions[8];
            getMeshIndexes(targetIndex, Donut, directions);
            int newHead;

            //for each space in the mesh
            for (int i = 0; i < 8; i++) {
                if (readT(directions[i],TILES) == AIR) {

                    //turn head
                    newHead = headDirections[i];

                }
            }
            writeUpdate(newHead, targetIndex, nextTiles, nextUpdates);
        } else {
            writeUpdate(head, targetIndex, nextTiles, nextUpdates);
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
void ruleCENTITAIL(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    //get direction & target
    int tail = readT(index, TILES);

    //get next space
    int targetIndex = index;

    switch (tail) {

        case CENTITAIL_N:
            targetIndex = moveIndexY(index, -1);
            break;

        case CENTITAIL_S:
            targetIndex = moveIndexY(index, 1);
            break;

        case CENTITAIL_E:
            targetIndex = moveIndexX(index,1);
            break;

        case CENTITAIL_W:
            targetIndex = moveIndexX(index, -1);
            break;
        
        case CENTITAIL_NE:
            targetIndex = moveIndex(index, 1, -1, 0);
            break;

        case CENTITAIL_NW:
            targetIndex = moveIndex(index, -1, -1, 0);
            break;

        case CENTITAIL_SE:
            targetIndex = moveIndex(index, 1, 1, 0);
            break;
        
        case CENTITAIL_SW:
            targetIndex = moveIndex(index, -1, 1, 0);
            break;
    }

    //set new tail
    int newTail;
    int pointingTo = readT(targetIndex, TILES);
    if (pointingTo >= CENTIBODY_N && pointingTo <= CENTIBODY_SW) { //if pointing to CENTIBODY

        for (int i = 0; i < 8; i++) {

            if (pointingTo == bodyDirections[i]) { //find direction of body

                newTail = tailDirections[i]; //set tail to that direction
            }

        }
        writeUpdate(newTail, targetIndex, nextTiles, nextUpdates);
        
        //turn OG tail into air
        writeUpdate(AIR, index, nextTiles, nextUpdates);
    } else {
        updateT(nextUpdates, index); //should die?
    }

    

}
Tile tileCENTITAIL = {
    .icon = '[',
    .name = "centipede",
    .rule = ruleCENTITAIL
};


//BALL
void ruleBALL(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    // Set self to air

    // Get all directions, and their opposites
    int tileInDirection[8];
    //readMesh(index, Donut, tileInDirection, TILES);
    meshIsEmpty(index, Donut, tileInDirection, TILES, nextTiles);

    int tileInOppositeDirection[8];
    //readMesh(index, DonutInverted, tileInOppositeDirection, TILES);
    meshIsEmpty(index, DonutInverted, tileInOppositeDirection, TILES, nextTiles);

    int oppositeDirectionIndex[8];
    getMeshIndexes(index, DonutInverted, oppositeDirectionIndex);


    int newIndex = index;

    for (int i = 0; i < 8; i++) {

        int surroundedByAir = tileInDirection[i];
        int oppositeIsEmpty = tileInOppositeDirection[i];

        if (surroundedByAir != 1 && oppositeIsEmpty) { // If not surrounded by AIR, AND the opposite direction of nearby tile is empty
            newIndex = oppositeDirectionIndex[i];
            
        }
    }

    //write ball wherever it ends up.
    //If it doesn't move, it just rewrites itself to it's same spot!
    if (newIndex != index) {
        writeUpdate(BALL, newIndex, nextTiles, nextUpdates);
        writeUpdate(AIR, index, nextTiles, nextUpdates);
    }
    

}
Tile tileBALL = {
    .icon = 'O',
    .name = "ball",
    .rule = ruleBALL
};

int RAT_TARGET = 0;//823 + 12; //Magic Number. The index all rats will chase.
void ruleRAT(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    int steps = moveIndexTowards(index, RAT_TARGET, 5, TILES, nextTiles, nextUpdates);
    
    if (steps == 0) { 
        RAT_TARGET = RAT_TARGET + 15; //getRandomIndex();
        updateT(nextUpdates, index);
    }

    
    
}
Tile tileRAT = {
    .icon = 'a',
    .name = "rat",
    .rule = ruleRAT
};


//Compile array of tiles
void compileRules() {

    //nonrules
    TILE_TYPES[AIR] = tileAIR;
    TILE_TYPES[STONE] = tileSTONE;
    TILE_TYPES[WOOD] = tileWOOD;

    TILE_TYPES[FIRE] = tileFIRE;
    TILE_TYPES[FIRE2] = tileFIRE2;

    TILE_TYPES[CENTIHEAD_N] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_S] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_E] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_W] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_NE] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_NW] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_SE] = tileCENTIHEAD;
    TILE_TYPES[CENTIHEAD_SW] = tileCENTIHEAD;

    TILE_TYPES[CENTIBODY_N] = tileCENTIBODY;
    TILE_TYPES[CENTIBODY_S] = tileCENTIBODY;
    TILE_TYPES[CENTIBODY_E] = tileCENTIBODY;
    TILE_TYPES[CENTIBODY_W] = tileCENTIBODY;
    TILE_TYPES[CENTIBODY_NE] = tileCENTIBODY;
    TILE_TYPES[CENTIBODY_NW] = tileCENTIBODY;
    TILE_TYPES[CENTIBODY_SE] = tileCENTIBODY;
    TILE_TYPES[CENTIBODY_SW] = tileCENTIBODY;

    TILE_TYPES[CENTITAIL_N] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_S] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_E] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_W] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_NE] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_NW] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_SE] = tileCENTITAIL;
    TILE_TYPES[CENTITAIL_SW] = tileCENTITAIL;

    TILE_TYPES[BALL] = tileBALL;
    TILE_TYPES[RAT] = tileRAT;
}
