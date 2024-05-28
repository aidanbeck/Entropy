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

int stepIndexTowards(int index, int targetIndex) {
    
    int x = indexToX(index);
    int y = indexToY(index);
    int z = indexToZ(index);

    int targetX = indexToX(targetIndex);
    int targetY = indexToY(targetIndex);
    int targetZ = indexToZ(targetIndex);

    /*
        Else ifs are specified so that if x == 0, the index is not moved.
        Could it be more optimized to test for (x != 0) instead of (x > targetX) ?
    */
    if      (x < targetX) { index = moveIndexX(index,  1); }
    else if (x > targetX) { index = moveIndexX(index, -1); }
    if      (y < targetY) { index = moveIndexY(index,  1); }
    else if (y > targetY) { index = moveIndexY(index, -1); }
    if      (z < targetZ) { index = moveIndexZ(index,  1); }
    else if (z > targetZ) { index = moveIndexZ(index, -1); }

    return index;
}


/*
    Returns with the number of steps it successfully made.
    Should possibly refactor this using a "findDirection" function or something so that they go in a straight line.
*/
int moveIndexTowards(int index, int targetIndex, int distance, int *TILES, int *nextTiles, int *nextUpdates) {

    int tile = TILES[index];
    int newIndex;

    int steps = 0;

    for (int i = 0; i < distance; i++) {

        newIndex = stepIndexTowards(index, targetIndex);

        if (indexIsEmpty(newIndex, TILES, nextTiles) == 1) {

            writeUpdate(AIR, index, nextTiles, nextUpdates);
            writeUpdate(tile, newIndex, nextTiles, nextUpdates);
            index = newIndex;
            steps++;
        }
    }

    return steps;
}