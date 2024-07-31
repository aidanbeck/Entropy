#include "main.h"
#include "physics.h"
#include "barista/barista.h" // for placeToJS
#include <stdint.h> // for uint8_t
#include <stdlib.h> // for malloc in hot()
#include <stdio.h>


//View Tile At Index
uint8_t view(int index, Chunk *CHUNK) {
    uint8_t tile = CHUNK->TILES[index];
    return tile;
}

//Place Tile At Index
void place(uint8_t tile, int index, Chunk *CHUNK) {
    CHUNK->nextTiles[index] = tile;

    #if COMPILE_MODE == 1
    placeToJS(index, tile);
    #endif
}

//Update Index
void update(int index, Chunk *CHUNK) {
    if (CHUNK->nextUpdates[index] == 0) {
        CHUNK->nextUpdates[index] = 1; //DEFAULT
    } 
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

int moveIndex(int index, int x, int y, int z) {

    index += x;
    index += y * CHUNK_WIDTH;
    index += z * (CHUNK_WIDTH * CHUNK_LENGTH);

    return index;
}

/*
    Useful for detecting if an index is safe to write to, and that it won't "eat" another tile trying to write to that space.
    1 indicates that a index is EMPTY on the next tick.
    0 indicates that the index is FULL on the next tick.
*/
int indexIsEmpty(int index, Chunk *CHUNK) {

    uint8_t tile     = view(index, CHUNK);
    uint8_t nextTile = CHUNK->nextTiles[index]; //hacky. Should make viewNext().

    if (nextTile == 0)                { return 1; } //nextTile is AIR
    if (tile == 0 && nextTile == 255) { return 1; } // tile is AIR and nextTile is UNCHANGED
    return 0;
}

void getMeshIndexes(int index, Mesh *MESH, int *array) {

    int length = MESH[0].length;

    for (int i = 0; i < length; i++) {
        array[i] = moveIndex(index, MESH[i].x, MESH[i].y, MESH[i].z);
    }
}

void viewMesh(int index, Mesh *MESH, uint8_t *array, Chunk *CHUNK) {

    int length = MESH[0].length;

    for (int i = 0; i < length; i++) {
        array[i] = view(
            moveIndex(index, MESH[i].x, MESH[i].y, MESH[i].z),
            CHUNK
        );
    }
}

void placeMesh(uint8_t tile, int index, Mesh *MESH, Chunk *CHUNK) {
    int length = MESH[0].length;

    for (int i = 0; i < length; i++) {
        place(
            tile,
            moveIndex(index, MESH[i].x, MESH[i].y, MESH[i].z),
            CHUNK
        );
    }
}

void updateMesh(int index, Mesh *MESH, Chunk *CHUNK) {
    int length = MESH[0].length;

    for (int i = 0; i < length; i++) {
        int index2 = moveIndex(index, MESH[i].x, MESH[i].y, MESH[i].z);
        update(index2, CHUNK);
    }
}

/*
    Returns 1 for each index in a mesh that is empty.
    Returns 0 for each index in a mesh that is full.
*/
void meshIsEmpty(int index, Mesh *MESH, int *array, Chunk *CHUNK) {

    int length = MESH[0].length;

    for (int i = 0; i < length; i++) {

        int newIndex = moveIndex(index, MESH[i].x, MESH[i].y, MESH[i].z);
        array[i] = indexIsEmpty(newIndex, CHUNK);
    }
}



//Convienence Functions

// Mesh cubeFaces[6] = {
//     { .x = 0, .y = 0, .z = 1, .length = 6},
//     { .x = 0, .y = 0, .z = -1},
//     { .x = 0, .y = -1, .z = 0},
//     { .x = 0, .y = 1, .z = 0},
//     { .x = -1, .y = 0, .z = 0},
//     { .x = 1, .y = 0, .z = 0},
// };

Mesh squareEdges[4] = {
    { .x = 0, .y = -1, .z = 0, .length = 4},
    { .x = 0, .y = 1, .z = 0},
    { .x = -1, .y = 0, .z = 0},
    { .x = 1, .y = 0, .z = 0},
};

//View All Adjacent Indexes
void viewFaces(int index, uint8_t *array, Chunk *CHUNK) {
    viewMesh(index, squareEdges, array, CHUNK);
}

//Update Index & Adjacent Indexes
void updates(int index, Chunk *CHUNK) {
    update(index, CHUNK); //should this be here?
    updateMesh(index, squareEdges, CHUNK);
}

//Place Tile At Index & Update Index
void uplace(uint8_t tile, int index, Chunk *CHUNK) {
    place(tile, index, CHUNK);
    update(index, CHUNK);
}

//Place Tile At Index, Update Index, Update Adjacent Indexes
void uplaces(uint8_t tile, int index, Chunk *CHUNK) {
    place(tile, index, CHUNK);
    updates(index, CHUNK);
}




//Add a "Hot Law" update
//This may need refactoring.
void hot(int index, int *input, Law *law, Chunk *CHUNK) { //instead of "law" being a pointer, it could be an integer, and you could use enums for readability.

    //find if hotLaw already exists
    //TODO!!!

    //create hotlaw if it doesn't
    HotLaw *newHotLaw = malloc(sizeof(HotLaw));
    if (!newHotLaw || CHUNK->hotLawCount > CHUNK->hotLawMax) { return; }
    newHotLaw->law = law;
    newHotLaw->lastTickUsed = CHUNK->tick;
    newHotLaw->input[0] = input[0];
    newHotLaw->input[1] = input[1];
    newHotLaw->input[2] = input[2];

    //add hot law (again only if it doesn't)
    while (CHUNK->hotLawTable[ CHUNK->hotLawCount ] != NULL) { CHUNK->hotLawCount++; } //don't overwrite rules in use.

    uint8_t hotLawIndex = CHUNK->hotLawCount;
    CHUNK->hotLawTable[ hotLawIndex ] = newHotLaw;
    CHUNK->hotLawCount++;

    //set nextUpdate to index of hotLaw.
    CHUNK->nextUpdates[index] = hotLawIndex;
}