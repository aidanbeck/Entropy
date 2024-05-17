//COMPILE WITH: gcc main.c -o entropy.exe -Wall -Werror -Wpedantic
//RUN WITH: ./main.exe

#include "main.h"
#include "printer.h"
#include "map.h"
#include "tiles.h"
#include "tools.h"

int getIndex(int x, int y, int z) { //needs to be audited
    return z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x;
}

void addTile(int *chunk, int tile, int x, int y, int z) {
    int i = getIndex(x,y,z);
    chunk[i] = tile;
}

void addUpdate(int *updates, int x, int y, int z) {
    int i = getIndex(x,y,z);
    updates[i] = 1;
}

void fillTile(int *chunk, int tile, int x1, int y1, int z1, int x2, int y2, int z2) { //audit. Does this place them AT both coordinates, or between? Should be at.
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            for (int a = z1; a < z2; a++) {
                addTile(chunk, tile, i, j, a);
            }
        }
    }
}

void registerUpdate(int *newUpdates, int index) {
    newUpdates[index] = 1;              //self
    newUpdates[index-1] = 1;            //left
    newUpdates[index+1] = 1;            //right
    //newUpdates[index-CHUNK_LENGTH] = 1; //up  //commented out because they will break 2D mode
    //newUpdates[index+CHUNK_LENGTH] = 1; //down
    newUpdates[index+CHUNK_WIDTH*CHUNK_HEIGHT] = 1; //forwards
    newUpdates[index-CHUNK_WIDTH*CHUNK_HEIGHT] = 1; //backwards
}

//the rules for each tile
void updateTile(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    int tile = chunk[index];

    Tile data = TILE_TYPES[tile];
    
    if (data.rule != NULL) { //may want to check if data in general is defined as well
        data.rule(chunk, updatedChunk, scheduledUpdates, index);
    }

}

void initializeArray(int *array, int length, int value) {
    for (int i = 0; i < length; i++) {
        array[i] = value;
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

void updateWorld(Chunk *WORLD, int *chunkUpdates) {

    int scheduledUpdates[WORLD_SIZE]; initializeArray(scheduledUpdates, WORLD_SIZE, 0); //list chunks that get updates. 0 means don't update, 1 means do.

    //update all chunks that have updates scheduled
    for (int i = 0; i < WORLD_SIZE; i++) {
        if (chunkUpdates[i] == 1) {

            Chunk *toUpdate = &WORLD[i];
            scheduledUpdates[i] = updateChunk(toUpdate);
            
        }
    }

    //add new scheduled updates to updates list for the next tick
    for (int i = 0; i < CHUNK_SIZE; i++) {
        chunkUpdates[i] = scheduledUpdates[i];
    }

}

Chunk WORLD[WORLD_SIZE];
int chunkUpdates[WORLD_SIZE]; //like tileupdates but for chunks that have tileupdates

int main() {

    //set up world
    for (int i = 0; i < WORLD_SIZE; i++) {

        Chunk newChunk;

        initializeArray(newChunk.chunk, CHUNK_SIZE, 0);
        initializeArray(newChunk.updates, CHUNK_SIZE, 0);

        newChunk.x = 0;
        newChunk.y = 0;
        newChunk.z = 0;

        WORLD[i] = newChunk;
    }
    Chunk *startChunk = &WORLD[0]; //create example chunk
    chunkUpdates[0] = 1; //turn on example chunk


    int tick = 0;
    compileRules();
    createBorder(startChunk);
    mapSnek(startChunk);

    //render & update chunk i times
    for (int i = 0; i < TICK_LIMIT; i++) {
        
        printf("\n\n---------------------Tick %d---------------------", tick);
        printChunk2d(startChunk->chunk);
        printUpdates2d(startChunk->updates);

        updateWorld(WORLD, chunkUpdates);
        tick++;
        usleep(TICK_DURATION);
    }



    return 0;
}