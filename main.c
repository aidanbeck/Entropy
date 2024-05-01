//COMPILE WITH: gcc main.c -o entropy.exe -Wall -Werror -Wpedantic
//RUN WITH: ./main.exe

#include "main.h"
#include "printer.h"
#include "map.h"
#include "tiles.h"

int getIndex(int x, int y, int z) {
    return z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x;
}

int getTile(int *chunk, int x, int y,  int z) {
    return chunk[z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x];
}

void addTile(int *chunk, int tile, int x, int y, int z) {
    chunk[z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x] = tile;
}

void addUpdate(int *tileUpdates, int x, int y, int z) {
    int i = getIndex(x,y,z);
    tileUpdates[i] = 1;
}

void fillTile(int *chunk, int tile, int x1, int y1, int z1, int x2, int y2, int z2) {
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
    newUpdates[index-CHUNK_LENGTH] = 1; //up
    newUpdates[index+CHUNK_LENGTH] = 1; //down
    newUpdates[index+CHUNK_LENGTH*CHUNK_HEIGHT] = 1; //forwards
    newUpdates[index-CHUNK_LENGTH*CHUNK_HEIGHT] = 1; //backwards
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

void updateChunk(int *chunk, int *tileUpdates) {

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
    for (int i = 0; i < CHUNK_SIZE; i++) {
        tileUpdates[i] = scheduledUpdates[i];

        if (updatedChunk[i] != -1) {
            chunk[i] = updatedChunk[i];
        }
    }

}

int main() {

    //set up world
    int tick = 0;
    int chunk[CHUNK_SIZE];        initializeArray(chunk, CHUNK_SIZE, 0);
    int tileUpdates[CHUNK_SIZE];  initializeArray(tileUpdates, CHUNK_SIZE, 0);
    compileRules();
    
    createBorder(chunk);
    mapTower(chunk);
    mapTowerUpdates(tileUpdates);

    //render & update chunk i times
    for (int i = 0; i < 128; i++) {
        
        usleep(100000);
        //printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printChunk3d(chunk, 1);
        
        updateChunk(chunk, tileUpdates);
        tick++;
    }
    
    return 0;
}