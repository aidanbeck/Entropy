#include "main.h"
#include "tools.h"
#include "map.h"
#include "tiles.h"
#include <stdio.h>
#include <stdlib.h>


int setSeedReady = 0;
int getRandomIndex() {

    if (setSeedReady == 0) {
        srand(137);
        setSeedReady = 1;
    }

    int index = rand() % CHUNK_SIZE;

    return index;
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


// function to get the target *direction*, not index
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

///useless?
int stepIndexTowards(int index, int targetIndex) {

    int x, y, z;
    getTargetDirection(index, targetIndex, &x, &y, &z);

    return moveIndex(index, x, y, z);
}

int matchesTargetAxis(int index, int targetIndex) {

    int indexX = indexToX(index);
    int indexY = indexToY(index);
    //int indexZ = indexToZ(index);

    int targetX = indexToX(targetIndex);
    int targetY = indexToY(targetIndex);
    //int targetZ = indexToZ(targetIndex);

    if (indexX == targetX) { return 1; }
    if (indexY == targetY) { return 1; }
    //if (indexZ == targetZ) { return 1; } // Disabled because I don't want tiles to try and move on the Z axis.

    return 0;
}

/*
    Returns with the number of steps it successfully made.
    Should possibly refactor this using a "findDirection" function or something so that they go in a straight line.
*/
int moveIndexTowards(int index, int targetIndex, int distance, int *TILES, int *nextTiles, int *nextUpdates) {

    int tile = TILES[index];
    int newIndex;

    int steps = 0;

    int x, y, z; //Direction. Velocity? Needs naming consistency.
    getTargetDirection(index, targetIndex, &x, &y, &z);

    for (int i = 0; i < distance; i++) {

        //if X or Y match an axis, and it is not traveling in a straight line, stop stepping early (this avoids zigzags)
        if (x != 0 && y != 0) { // if traveling diagonally
            if (matchesTargetAxis(index, targetIndex) == 1) { //if matching axis
                return steps;
            }
        }

        newIndex = moveIndex(index, x, y, z);

        if (indexIsEmpty(newIndex, TILES, nextTiles) == 1 && index != targetIndex) { //if index is empty & NOT the target

            writeUpdate(AIR, index, nextTiles, nextUpdates);
            writeUpdate(tile, newIndex, nextTiles, nextUpdates);
            index = newIndex;
            steps++;

        }
    }


    //Push the tile that it runs into the number of steps it took.
    //This works unless the tile also tries to move.

    int indexAtEndOfPath = moveIndex(index, x, y, z);
    int tileAtEndOfPath = readT( indexAtEndOfPath, TILES );

    if (tileAtEndOfPath != AIR && tileAtEndOfPath != STONE && steps != 0) {

        int pushToIndex = moveIndex( index, x*distance, y*distance, 0 );

        printf("\ne:%d, i:%d, t:%d, d:%d", tileAtEndOfPath, indexAtEndOfPath, pushToIndex, steps);

        moveIndexTowards(indexAtEndOfPath, pushToIndex, steps, TILES, nextTiles, nextUpdates);

        TILES[indexAtEndOfPath] = AIR; //this is VERY MANUAL overwrite of the tile at the end of path.
        //Necessary so that if on this tick the tile decides to move, it will be prevented.
        //Sometimes it eats a moving entity. Why??

    }

    return steps;
}