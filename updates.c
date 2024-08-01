#include "main.h"
#include "physics.h"
#include "elements/periodicTable.h" //for moveTruck
#include <stdlib.h> //so I can use NULL
#include <stdio.h>

#define DEFAULT 1
#define UNCHANGED 255

void initializeArray(uint8_t *array, int length, int value) {
    for (int i = 0; i < length; i++) {
        array[i] = value;
    }
}

void prepareHotLawTable(HotLaw **table, int currentTick) {
    // for (int i = 0; i < 255; i++) {

    //     if (table[i] == NULL) { continue; }
    //     if (table[i]->lastTickUsed == currentTick) { continue; }

    //     free(table[i]);
    //     table[i] = NULL;
    // }
}

void updateTile(int index, int update, Chunk *CHUNK, Physics *PHYSICS) {
    
    uint8_t tile = CHUNK->TILES[index];
    Element *data = &PHYSICS->PeriodicTable[tile];
    
    if (update == DEFAULT) {
        data->defaultLaw->func(index, CHUNK); //Maybe I should have a "runDefaultLaw" helper
        return;
    }
    

    //Maybe I should have a "runHotLaw" helper
    // !!!! HERE RIGHT HERE !!! OR maybe in prepareHotLawTable
    

    HotLaw *hotlaw = CHUNK->hotLawTable[update];
    hotlaw->lastTickUsed = CHUNK->tick; // update hotlaw's last tick
    CHUNK->input[0] = hotlaw->input[0];       // let CHUNK carry input
    CHUNK->input[1] = hotlaw->input[1];
    CHUNK->input[2] = hotlaw->input[2];
    hotlaw->law->func(index, CHUNK);    // run hot law function

    //free hot law
    free(CHUNK->hotLawTable[update]);
    CHUNK->hotLawTable[update] = NULL;
    if (CHUNK->hotLawCount > update) {
        CHUNK->hotLawCount = update;
    }

}

void prepareChunk(Chunk *CHUNK) {

    uint8_t *nextTiles   = CHUNK->nextTiles;
    uint8_t *nextUpdates = CHUNK->nextUpdates;
    HotLaw  **table      = CHUNK->hotLawTable;
    int     tick         = CHUNK->tick;

    initializeArray(nextTiles, CHUNK_SIZE, UNCHANGED);
    initializeArray(nextUpdates, CHUNK_SIZE, 0);
    prepareHotLawTable(table, tick);
}

void overwriteChunk(Chunk *CHUNK) {
    
    uint8_t *updates     = CHUNK->UPDATES;
    uint8_t *nextUpdates = CHUNK->nextUpdates;
    uint8_t *tiles       = CHUNK->TILES;
    uint8_t *nextTiles   = CHUNK->nextTiles;
    
    for (int i = 0; i < CHUNK_SIZE; i++) {

        updates[i] = nextUpdates[i];

        if (nextTiles[i] == UNCHANGED) { continue; }
        tiles[i] = nextTiles[i];
    }
}

void updateAllTiles(Chunk *CHUNK, Physics *PHYSICS) {
    uint8_t *updates     = CHUNK->UPDATES;
    for (int i = 0; i < CHUNK_SIZE; i++) {
        //printf(",%d", CHUNK->physics->PeriodicTable[CHUNK->TILES[i]].icon);
        if (updates[i] == 0) { continue; }
        updateTile(i, updates[i], CHUNK, PHYSICS);
    }
}

void updateChunk(Chunk *CHUNK, Physics *PHYSICS) {
  
    updateAllTiles(CHUNK, PHYSICS);
    overwriteChunk(CHUNK);
    prepareChunk(CHUNK); //prepare for the next update
}
/*
    updateChunk Potential Improvement:

    This could probably be split into four helper functions.
    - prepareChunk
    - runAllUpdates
    - writeNextUpdates
    - writeNextTiles

    I could also potentially reduce the size of each loop.
    Let's say I add the following ints to the Chunk structure:
    - firstUpdate
    - lastUpdate
    - firstNextUpdate
    - lastNextUpdate
    - firstNextTile
    - lastNextTile
    These names are a bit weird because "firstNext" doesn't make a
    whole lot of sense by itself. I might want to change "nextUpdates"
    and "nextTiles" anyways. I could manipulate the "first" and "last"
    variables to use them in each loop, since I know that nothing needs
    to be done outside of those two numbers.

*/