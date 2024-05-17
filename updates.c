#include "main.h"
#include "tiles.h"

/*
    Resets every index of an array to a set value.
    Helper function, used to clean chunks or update schedules.
*/
void initializeArray(int *array, int length, int value) {
    for (int i = 0; i < length; i++) {
        array[i] = value;
    }
}

/*
    Adds the index in each direction to the "scheduledUpdates" array.
    This should probably use a mesh instead, because it breaks if it hits a border.
*/
void registerUpdate(int *newUpdates, int index) {
    newUpdates[index] = 1;              //self
    newUpdates[index-1] = 1;            //left
    newUpdates[index+1] = 1;            //right
    //newUpdates[index-CHUNK_LENGTH] = 1; //up  //commented out because they will break 2D mode
    //newUpdates[index+CHUNK_LENGTH] = 1; //down
    newUpdates[index+CHUNK_WIDTH*CHUNK_HEIGHT] = 1; //forwards
    newUpdates[index-CHUNK_WIDTH*CHUNK_HEIGHT] = 1; //backwards
}

/*
    Runs the rule function of a tile if it has one.
*/
void updateTile(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {

    int tile = chunk[index];
    Tile data = TILE_TYPES[tile];
    
    if (data.rule != NULL) { //may want to check if data in general is defined as well
        data.rule(chunk, updatedChunk, scheduledUpdates, index);
    }

}

int updateChunk(Chunk *CHUNK) {

    int *chunk = CHUNK->chunk;
    int *tileUpdates = CHUNK->updates; //names might not be standardized

    int scheduledUpdates[CHUNK_SIZE]; initializeArray(scheduledUpdates, CHUNK_SIZE, 0);//a list of what tiles to update on the next tick. 0 indicates don't update this tile, 1 indicates do update
    int updatedChunk[CHUNK_SIZE]; initializeArray(updatedChunk, CHUNK_SIZE, -1); //a list of tiles that need to be changed. -1 indicates no change.

    //update all tiles that have updates scheduled
    for (int i = 0; i < CHUNK_SIZE; i++) {
        if (tileUpdates[i] == 1) {
            updateTile(chunk, updatedChunk, scheduledUpdates, i);
        }
    }

    //add new scheduled updates to updates list for the next tick
    //also make any changes to the chunk that were decided upon.
    int shouldUpdateChunk = 0;

    for (int i = 0; i < CHUNK_SIZE; i++) {
        tileUpdates[i] = scheduledUpdates[i];

        if (tileUpdates[i] == 1 && shouldUpdateChunk == 0) { //if the chunk will have more tile updates
            shouldUpdateChunk = 1; //set the chunk to update
        }

        //!!! there needs to be some tech here where a tile can update & write to the chunk next to it

        if (updatedChunk[i] != -1) { //write changed tiles
            chunk[i] = updatedChunk[i];
        }
    }

    return shouldUpdateChunk;
}