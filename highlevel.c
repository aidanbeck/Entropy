#include "main.h"
#include "physics.h"
#include "elements/periodicTable.h"
#include "laws/lawTable.h"
#include <stdlib.h>
#include <stdio.h>

int setSeedReady = 0;
int getRandomIndex() {

    if (setSeedReady == 0) {
        srand(138);
        setSeedReady = 1;
    }

    return rand() % CHUNK_SIZE;
}

int indexToX(int index) {
    int ROW_SIZE = CHUNK_WIDTH;
    return index % ROW_SIZE;
}

int indexToY(int index) {
    int ROW_SIZE = CHUNK_WIDTH;
    return index / ROW_SIZE;
}

int indexToZ(int index) {
    int LAYER_SIZE = CHUNK_WIDTH * CHUNK_LENGTH;
    return index / LAYER_SIZE;
}

/*
    Returns 1 if in bounds.
    Returns 0 if outside.
*/
int indexInBounds(int index) {

    int x = indexToX(index);
    int y = indexToY(index);

    if (x < 1 || x > CHUNK_WIDTH - 2) { return 0; } //!!! doesnt scale!
    if (y < 1 || y > CHUNK_LENGTH - 2) { return 0; }

    return 1;
}

void getTargetDirection(int index, int targetIndex, int *x, int *y, int *z) {

    int indexX = indexToX(index);
    int indexY = indexToY(index);
    int indexZ = indexToZ(index);

    int targetX = indexToX(targetIndex);
    int targetY = indexToY(targetIndex);
    int targetZ = indexToZ(targetIndex);

    int directionX = 0;
    int directionY = 0;
    int directionZ = 0;

    /*
        Else ifs are specified so that if x == 0, the index is not moved.
        Could it be more optimized to test for (x != 0) instead of (x > targetX) ?
    */
    if      (indexX < targetX) { directionX =  1; }
    else if (indexX > targetX) { directionX = -1; }
    if      (indexY < targetY) { directionY =  1; }
    else if (indexY > targetY) { directionY = -1; }
    if      (indexZ < targetZ) { directionZ =  1; }
    else if (indexZ > targetZ) { directionZ = -1; }

    *x = directionX;
    *y = directionY;
    *z = directionZ;
}

/*
    Returns 1 if the index matches an axis with the target.
    Returns 0 if not.
*/
int matchesTargetAxis(int index, int targetIndex) {

    int indexX = indexToX(index);
    int targetX = indexToX(targetIndex);
    if (indexX == targetX) { return 1; }

    int indexY = indexToY(index);
    int targetY = indexToY(targetIndex);
    if (indexY == targetY) { return 1; }

    //int indexZ = indexToZ(index);
    //int targetZ = indexToZ(targetIndex);
    //if (indexZ == targetZ) { return 1; } // Disabled because I don't want tiles to try and move on the Z axis.

    return 0;
}

/*
    Calculates the distances between two indexes along all three axis'.
    Returns the smallest distance.
*/
int getSmallestAxisDistance(int index, int targetIndex) {

    int indexX = indexToX(index);
    int targetX = indexToX(targetIndex);
    int xDistance = abs(indexX - targetX);

    int indexY = indexToY(index);
    int targetY = indexToY(targetIndex);
    int yDistance = abs(indexY - targetY);

    //int indexZ = indexToZ(index);
    //int targetZ = indexToZ(targetIndex);
    //int zDistance = abs(indexZ - targetZ); // Disabled because I don't want tiles to try and move on the Z axis.

    //if ALREADY on axis, ignore that axis
    if (xDistance == 0 ) {return yDistance; }
    if (yDistance == 0 ) {return xDistance; }

    if (xDistance < yDistance) {
        return xDistance;
    } else {
        return yDistance;
    }
}




/*
    Grab the indexes of coordinates between two points.
    (Starting with the first, and until the distance limit is reached, or an axis of the second point is passed)

    Return the number of indexes grabbed.
*/
int getIndexesTowards(int index, int targetIndex, int distance, int* indexes ) {

    //Initialize direction variables
    int xDir, yDir, zDir; getTargetDirection(index, targetIndex, &xDir, &yDir, &zDir);

    //If going the entire distance will overpass an axis of the target, shorten the distance.
    int smallestDistance = getSmallestAxisDistance(index, targetIndex);
    if (smallestDistance < distance) { distance = smallestDistance; }

    //Grab indexes of coordinates in the direction of target
    int movedIndex = index;

    for (int i = 0; i < 64; i++) {indexes[i] = 8; } //initialize !!!

    for (int i = 0; i < distance; i++) {
        
        movedIndex   = moveIndex(movedIndex, xDir, yDir, zDir);
        int inBounds = indexInBounds(movedIndex);

        if (inBounds == 1) { 
            indexes[i] = movedIndex;
        } else {
            return i - 1;
        }

    }

    return distance;
}

void pushTileTowards(int indexToPush, int distanceToPush, int initialIndex, int initialTarget, Chunk *CHUNK) {

    //get directional input
    int xDir, yDir, zDir; getTargetDirection(initialIndex, initialTarget, &xDir, &yDir, &zDir);
    int input[3] = {distanceToPush, xDir, yDir};

    uint8_t tile = view(indexToPush, CHUNK);
    if (tile == STONE ) { return; }
    if (tile == ZOMBIE) { uplace(CORPSE, indexToPush, CHUNK); }
    if (tile == TIRE) { input[0] = distanceToPush + 4; }
    if (tile == GAS) {} 

    hot(indexToPush, input, &L_PUSH, CHUNK);
}

//maybe this should return ending index so that gas can explode at the end?
void moveTileTowards(int index, int targetIndex, int distance, Chunk *CHUNK) {

    int indexes[64];
    if (distance > 64) {
        printf("Error! Distance of %d exceeds limit of 64!\n", distance);
        distance = 64;
    }

    int indexesDistance = getIndexesTowards(index, targetIndex, distance, indexes);

    printf("indexesInBoundsAndTowards: (%d), %d, %d, %d, %d\n", indexesDistance, indexes[0], indexes[1], indexes[2], indexes[3]);
    
    int emptyDistance = -1;

    for (int i = 0; i < indexesDistance; i++) {

        int isEmpty = indexIsEmpty(indexes[i], CHUNK);

        if (isEmpty == 0) { break; }
        emptyDistance = i;
        //uplace(TRAIL, indexes[i], CHUNK);

    }

    

    printf("emptyDistance: %d\n", emptyDistance);
    printf("indexes: %d, %d, %d, %d\n", indexIsEmpty(indexes[0], CHUNK), indexIsEmpty(indexes[1], CHUNK), indexIsEmpty(indexes[2], CHUNK), indexIsEmpty(indexes[3], CHUNK));

    if (emptyDistance == -1) { //against wall;
        return;
    }

    // move tile to new index
    uplaces(AIR, index, CHUNK);
    uint8_t tile = view(index, CHUNK);
    uplaces(tile, indexes[emptyDistance], CHUNK);

    // Update entities !!! this should be less hard coded.
    if (tile == TRUCK) { setTruckIndex(indexes[emptyDistance]); }
    // gas explosion can go here
    
    // if stopped prematurely
    if (emptyDistance < indexesDistance) {

        int indexToPush    = indexes[emptyDistance+1];
        int distanceToPush = abs(emptyDistance - indexesDistance);

        pushTileTowards(indexToPush, distanceToPush, index, targetIndex, CHUNK);
    }
}