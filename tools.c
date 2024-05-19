#include "main.h"
#include "tools.h"
#include "barista.h"

//Read Tile
int readT(int index, int *chunk) {
    int tile = chunk[index];
    return tile;
}

//Write Tile
void writeT(int tile, int index, int *updatedChunk) {
    updatedChunk[index] = tile;
    //jsWriteIcon(index, tile);
}

//Update Tile
void updateT(int *scheduledUpdates, int index) { //this might not be neccesary. Or, registerUpdate should be moved here.
    registerUpdate(scheduledUpdates, index);
}

//Write AND Update Tile
void writeUpdate(int tile, int index, int *updatedChunk, int *scheduledUpdates) {
    writeT(tile, index, updatedChunk);
    updateT(scheduledUpdates, index);
}

int moveIndexX(int index, int x) {
    index += x;
    return index;
}

int moveIndexY(int index, int y) {
    index += y * CHUNK_WIDTH;
    return index;
}

int moveIndexZ(int index, int z) {
    index += z * (CHUNK_WIDTH * CHUNK_LENGTH);
    return index;
}

int moveIndex(int index, int x, int y, int z) { //Should this use functions instead?

    index += x;
    index += y * CHUNK_WIDTH;
    index += z * (CHUNK_WIDTH * CHUNK_LENGTH);

    return index;
}

//readAllDirections - rename to "readCubeFaces"? This should be a Mesh in the future.
void readAllDirections(int index, int *array) {

    array[0] = moveIndexZ(index, 1); //up
    array[1] = moveIndexZ(index, -1); //down
    array[2] = moveIndexX(index, -1); //west
    array[3] = moveIndexX(index, 1); //east
    array[4] = moveIndexY(index, -1); //north
    array[5] = moveIndexY(index, 1); //south
}

void getMeshIndexes(int index, Mesh *mesh, int *array) {

    int length = mesh[0].length;

    for (int i = 0; i < length; i++) {
        array[i] = moveIndex(index, mesh[i].x, mesh[i].y, mesh[i].z);
    }

}

int readWest(int index) {
    return moveIndexX(index, -1);
}

int readEast(int index) {
    return moveIndexX(index, 1);
}

int readNorth(int index) {
    return moveIndexY(index, -1);
}

int readSouth(int index) {
    return moveIndexY(index, 1);
}

int readDown(int index) {
    return moveIndexZ(index, -1);
}

int readUp(int index) {
    return moveIndexZ(index, 1);
}

int detectChunkBorder(int index) {
    
    //todo: implement

    return 0;
}