//COMPILE WITH: gcc main.c -o entropy.exe -Wall -Werror -Wpedantic
//RUN WITH: ./entropy.exe

#include "main.h"

enum Tiles {
    AIR,
    STONE,
    SAND,
    WOOD,
    FIRE,
    FIRE2,
    SMOKE,
    MISSILE,
    MISSILE2,
    WATER
};

void registerUpdate(int *newUpdates, int index) {
    newUpdates[index] = 1;
    newUpdates[index-1] = 1;
    newUpdates[index+1] = 1;
}

void updateTile(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    int tile = chunk[index];

    //Smoke rules
    if (tile == SMOKE) {
        updatedChunk[index] = AIR; registerUpdate(scheduledUpdates, index);
    }

    //fire rules
    else if (tile == FIRE) {
        updatedChunk[index] = FIRE2; registerUpdate(scheduledUpdates, index);

        
    }
    else if (tile == FIRE2) {
        updatedChunk[index] = SMOKE; registerUpdate(scheduledUpdates, index);

        if (chunk[index+1] == WOOD) {
            updatedChunk[index+1] = FIRE; registerUpdate(scheduledUpdates, index+1);
        }
        if (chunk[index-1] == WOOD) {
            updatedChunk[index-1] = FIRE; registerUpdate(scheduledUpdates, index-1);
        }
    }

    //missile rules
    else if (tile == MISSILE) {
        if (chunk[index+1] == AIR) {
            updatedChunk[index] = SMOKE; registerUpdate(scheduledUpdates, index);
            updatedChunk[index+1] = MISSILE; registerUpdate(scheduledUpdates, index+1);
        } else if (chunk[index+1] == STONE || chunk[index+1] == SAND) {
            updatedChunk[index] = MISSILE2; registerUpdate(scheduledUpdates, index);
        } else {
            updatedChunk[index] = FIRE; registerUpdate(scheduledUpdates, index);
        }
    }

    //missile2 rules
    else if (tile == MISSILE2) {
        if (chunk[index-1] == AIR) {
            updatedChunk[index] = SMOKE; registerUpdate(scheduledUpdates, index);
            updatedChunk[index-1] = MISSILE2; registerUpdate(scheduledUpdates, index+1);
        } else if (chunk[index-1] == STONE || chunk[index-1] == SAND) {
            updatedChunk[index] = MISSILE; registerUpdate(scheduledUpdates, index);
        } else {
            updatedChunk[index] = FIRE; registerUpdate(scheduledUpdates, index);
        }
    }

    //water rules
    else if (tile == WATER) {
        if (chunk[index+1] == AIR || chunk[index+1] == FIRE || chunk[index+1] == SAND) {
            updatedChunk[index+1] = WATER; registerUpdate(scheduledUpdates, index+1);
        }
        if (chunk[index-1] == AIR || chunk[index-1] == FIRE || chunk[index-1] == SAND) {
            updatedChunk[index-1] = WATER; registerUpdate(scheduledUpdates, index-1);
        }
    }

}

void initializeArray(int *array, int length, int value) {
    for (int i = 0; i < length; i++) {
        array[i] = value;
    }
}

void updateChunk(int *chunk, int *tileUpdates) {

    int scheduledUpdates[CHUNK_LENGTH]; initializeArray(scheduledUpdates, CHUNK_LENGTH, 0);//a list of what tiles to update on the next tick. 0 indicates don't update this tile, 1 indicates do update
    int updatedChunk[CHUNK_LENGTH]; initializeArray(updatedChunk, CHUNK_LENGTH, -1); //a list of tiles that need to be changed. -1 indicates no change.

    //update all tiles that have updates scheduled
    for (int i = 0; i < CHUNK_LENGTH; i++) {
        if (tileUpdates[i] == 1) {
            updateTile(chunk, updatedChunk, scheduledUpdates, i);
        }
    }

    //add new scheduled updates to updates list for the next tick
    //also make any changes to the chunk that were decided upon.
    for (int i = 0; i < CHUNK_LENGTH; i++) {
        tileUpdates[i] = scheduledUpdates[i];

        if (updatedChunk[i] != -1) {
            chunk[i] = updatedChunk[i];
        }
    }

}

//text characters used to print tiles from the chunk. Each represents a tile enum.
char symbols[] = {
    ' ',
    '#', //⛰️
    'X',
    '+', //🌲
    '%', //🔥
    '%',
    ':', //☁
    '>', //🚀
    '<',
    '~' //🌊
};

//prints a representation of the chunk to console.
void printChunk(int *chunk) {
    for (int i = 0; i < CHUNK_LENGTH; i++) {
        printf("%c",symbols[chunk[i]]);
    }
}

//print tile update list
void printUpdates(int *tileUpdates) {
    for (int i = 0; i < CHUNK_LENGTH; i++) {
        printf("%d",tileUpdates[i]);
    }
}

int main() {

    //set up world
    int tick = 0;
    int chunk[CHUNK_LENGTH];        initializeArray(chunk, CHUNK_LENGTH, 0);
    int tileUpdates[CHUNK_LENGTH];  initializeArray(tileUpdates, CHUNK_LENGTH, 0);

    chunk[0] = STONE;
    chunk[10] = MISSILE2; tileUpdates[10] = 1;
    chunk[11] = SAND;
    chunk[15] = MISSILE2; tileUpdates[15] = 1;
    
    chunk[CHUNK_LENGTH-1] = STONE;
    chunk[CHUNK_LENGTH-3] = MISSILE; tileUpdates[CHUNK_LENGTH-3] = 1;

    initializeArray(chunk+16, CHUNK_LENGTH-16-16, WOOD);
    chunk[CHUNK_LENGTH/2] = WATER;

    
    
    //render & update chunk 30 times
    for (int i = 0; i < 9000; i++) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printUpdates(tileUpdates); printf("\n"); printChunk(chunk); printf("\n");
        updateChunk(chunk, tileUpdates); tick++;
        usleep(200000);
    }
    
    return 0;
}