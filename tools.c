//may rename this file in the future

#include "main.h"


//Read
int readT(int index, int *chunk) {
    int tile = chunk[index];
    return tile;
}

//Write
void writeT(int tile, int index, int *updatedChunk) {
    updatedChunk[index] = tile;
}

//Update
void updateT(int *scheduledUpdates, int index) { //this might not be neccesary. Or, registerUpdate should be moved here.
    registerUpdate(scheduledUpdates, index);
}

//write & update
void writeUpdate(int tile, int index, int *updatedChunk, int *scheduledUpdates) {
    writeT(tile, index, updatedChunk);
    updateT(scheduledUpdates, index);
}

//moveIndex
int moveIndex(int index, int x, int y, int z) { //can optimize by doing seperate functions per axis

    index += x;
    index -= CHUNK_LENGTH * y;
    index += (CHUNK_LENGTH*CHUNK_HEIGHT) * z;

    return index;
}

//readAllDirections
void readAllDirections(int index, int *array) {

    array[0] = moveIndex(index, 0, 1, 0); //above
    array[1] = moveIndex(index, 0, -1, 0); //below
    array[2] = moveIndex(index, -1, 0, 0); //left
    array[3] = moveIndex(index, 1, 0, 0); //right
    array[4] = moveIndex(index, 0, 0, 1); //front
    array[5] = moveIndex(index, 0, 0, -1); //back
} 


//readAbove
int readAbove(int index) {
    return index - CHUNK_LENGTH;
}

//readBelow
int readBelow(int index) {
    return index + CHUNK_LENGTH;
}

//readLeft
int readLeft(int index) {
    return index - 1;
}

//readRight
int readRight(int index) {
    return index + 1;
}

//readFront
int readFront(int index) {
    return index + (CHUNK_LENGTH*CHUNK_HEIGHT);
}

//readBack
int readBack(int index) {
    return index - (CHUNK_LENGTH*CHUNK_HEIGHT);
}

//detectChunkBorder
int detectChunkBorder(int index) {
    

    return 0;
}