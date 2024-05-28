#include "main.h"
#include "tools.h" //Only used to get Mesh struct
#include "updates.h" //Only used for registerUpdate
#include "barista.h" //Sometimes used for jsWriteIcon

/*
    ## Naming Questions ##
    * Should readT and writeT be renamed to readTile and writeTile?
    * Should writeUpdate be renamed to writeAndUpdate? Or something else?
    * Should moveIndexX and gang be renamed to moveIndex_X? Or something else?
*/

//Read Tile
int readT(int index, int *TILES) {
    int tile = TILES[index];
    return tile;
}

//Write Tile
void writeT(int tile, int index, int *nextTiles) {
    nextTiles[index] = tile;
    //jsWriteIcon(index, tile);
}

//Update Tile
void updateT(int *nextUpdates, int index) { //This might be unnecessary. Or, registerUpdate should be moved here. Maybe updateT should update a single index, and there should be another function to update all tiles of a mesh.
    registerUpdate(nextUpdates, index);
}

//Write AND Update Tile. Could this be named better?
void writeUpdate(int tile, int index, int *nextTiles, int *nextUpdates) {
    writeT(tile, index, nextTiles);
    updateT(nextUpdates, index);
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

void readMesh(int index, Mesh *mesh, int *array, int *TILES) { //Should this use getMeshIndexes?

    int length = mesh[0].length;

    for (int i = 0; i < length; i++) {
        array[i] = readT(
            moveIndex(index, mesh[i].x, mesh[i].y, mesh[i].z),
            TILES
        );
    }
}

/*
    Useful for detecting if an index is safe to write to, and that it won't "eat" another tile trying to write to that space.
    1 indicates that a index is EMPTY on the next tick.
    0 indicates that the index is FULL on the next tick.
*/
int indexIsEmpty(int index, int *TILES, int *nextTiles) {

    int tile    = readT(index, TILES);
    int newTile = readT(index, nextTiles);

    if (newTile == 0) { return 1; } //The next tick is writing AIR there, so it will definitely be free.

    if (tile == 0 && newTile == -1) { return 1; } // Count non-updates as empty.

    return 0;
}


/*
    Returns 1 for each index in a mesh that is empty.
    Returns 0 for each index in a mesh that is full.
*/
void meshIsEmpty(int index, Mesh *mesh, int *array, int *TILES, int *nextTiles) {

    int length = mesh[0].length;

    for (int i = 0; i < length; i++) {

        int newIndex = moveIndex(index, mesh[i].x, mesh[i].y, mesh[i].z);
        array[i] = indexIsEmpty(newIndex, TILES, nextTiles);
    }
}