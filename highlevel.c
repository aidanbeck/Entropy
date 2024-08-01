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

    if (x <= 1 || x >= 150) { return 0; }
    if (y <= 1 || y >= 15) { return 0; }

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
    Returns with the number of steps it successfully made.
    Should possibly refactor this using a "findDirection" function or something so that they go in a straight line.
*/
int moveIndexTowards(int index, int targetIndex, int distance, int *returnIndex, Chunk *CHUNK) {

    int tile = CHUNK->TILES[index];
    int newIndex = index;
    int steps = 0;

    int x, y, z; //Direction. Velocity? Needs naming consistency.
    getTargetDirection(index, targetIndex, &x, &y, &z);

    for (int i = 0; i < distance; i++) {

        //if X or Y match an axis, and it is not traveling in a straight line, stop stepping early (this avoids zigzags)
        if (x != 0 && y != 0) { // if traveling diagonally
            if (matchesTargetAxis(index, targetIndex) == 1) { //if matching axis
                printf(" hit axis. stopping. ");
                return steps;
            }
        }

        newIndex = moveIndex(index, x, y, z);

        if (indexIsEmpty(newIndex, CHUNK) == 1 && index != targetIndex) { //if index is empty & NOT the target

            uplaces(TRAIL, index, CHUNK);
            uplaces(tile, newIndex, CHUNK);
            index = newIndex;
            steps++;

        }
    }

    *returnIndex = newIndex;

    if (tile == TRUCK) { // spaghetti code special exception
        PLAYER.index = newIndex;
    }



    //Push the tile that it runs into the number of steps it took.
    //This works unless the tile also tries to move.

    int indexAtEndOfPath = moveIndex(index, x, y, z);
    int tileAtEndOfPath = view( indexAtEndOfPath, CHUNK );

    if (tileAtEndOfPath != AIR && tileAtEndOfPath != STONE && steps != 0) {

        if (tileAtEndOfPath == TRUCK) { //spaghetti code special exception
            PLAYER.tires--; //eventually handle this with function?
        }
        if (tileAtEndOfPath == ZOMBIE) {
            place(CORPSE, indexAtEndOfPath, CHUNK); //dies if pushed
        }

        int input[3] = {steps, x, y};
        hot(indexAtEndOfPath, input, &L_PUSH, CHUNK);
    }    

    return steps;
}