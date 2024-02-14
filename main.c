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

int getIndex(int x, int y) {
    return (y*CHUNK_LENGTH)+x;
}

int getTile(int *chunk, int x, int y) {
    return chunk[(y*CHUNK_LENGTH)+x];
}

void addTile(int *chunk, int tile, int x, int y) {
    chunk[(y*CHUNK_LENGTH)+x] = tile;
}

void addUpdate(int *tileUpdates, int x, int y) {
    int i = getIndex(x,y);
    tileUpdates[i] = 1;
}

void fillTile(int *chunk, int tile, int x1, int y1, int x2, int y2) {
    for (int i = x1; i < x2; i++) {
        for (int j = y1; j < y2; j++) {
            addTile(chunk, tile, i, j);
        }
    }
}

void registerUpdate(int *newUpdates, int index) {
    newUpdates[index] = 1;
    newUpdates[index-1] = 1;
    newUpdates[index+1] = 1;
    newUpdates[index-CHUNK_LENGTH] = 1;
    newUpdates[index+CHUNK_LENGTH] = 1;
}

void updateTile(int *chunk, int *updatedChunk, int *scheduledUpdates, int index) {
    int tile = chunk[index];

    //Smoke rules
    if (tile == SMOKE) {
        updatedChunk[index] = AIR; registerUpdate(scheduledUpdates, index);
        if (chunk[index-CHUNK_LENGTH] == AIR) { //-CHUNK_LENGHT is basically y + 1
            updatedChunk[index-CHUNK_LENGTH] = SMOKE; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH);
            
        }
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
        if (chunk[index+CHUNK_LENGTH] == WOOD) {
            updatedChunk[index+CHUNK_LENGTH] = FIRE; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH);
        }
        if (chunk[index-CHUNK_LENGTH] == WOOD) {
            updatedChunk[index-CHUNK_LENGTH] = FIRE; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH);
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

        if (chunk[index+CHUNK_LENGTH] == AIR || chunk[index+CHUNK_LENGTH] == FIRE || chunk[index+CHUNK_LENGTH] == SAND) {
            updatedChunk[index+CHUNK_LENGTH] = WATER; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH);
        }
    }

    else if (tile == SAND) {
        if (chunk[index+CHUNK_LENGTH] == AIR || chunk[index+CHUNK_LENGTH] == WATER) {
            updatedChunk[index] = AIR; registerUpdate(scheduledUpdates, index);
            updatedChunk[index+CHUNK_LENGTH] = SAND; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH);
        }
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

//prints a representation of the chunk to console (vertical slice)
void printChunk(int *chunk, int *tileUpdates) {
    for (int y = 0; y < CHUNK_LENGTH; y++) {
        
        for (int x = 0; x < CHUNK_HEIGHT; x++) {
            printf("%c ",symbols[chunk[(y*CHUNK_LENGTH)+x]]);
        }
        // printf(" : ");
        // for (int x = 0; x < CHUNK_HEIGHT; x++) {
        //     printf("%d ", tileUpdates[(y*CHUNK_LENGTH)+x]);
        // }

        printf("\n"); 
    }
}

int main() {

    //set up world
    int tick = 0;
    int chunk[CHUNK_SIZE];        initializeArray(chunk, CHUNK_SIZE, 0);
    int tileUpdates[CHUNK_SIZE];  initializeArray(tileUpdates, CHUNK_SIZE, 0);


    fillTile(chunk, STONE, 0, 0, 16, 16);
    fillTile(chunk, AIR, 1, 1, 15, 15);
    fillTile(chunk, WOOD, 8, 1, 11, 15);
    fillTile(chunk, SAND, 9, 1, 11, 15);
    
    fillTile(chunk, WOOD, 1, 8, 15, 12);

    addTile(chunk, MISSILE, 2, 2); addUpdate(tileUpdates,2,2);
    addTile(chunk, MISSILE, 4, 4); addUpdate(tileUpdates,4,4);
    
    addTile(chunk, WATER, 2, 6); addUpdate(tileUpdates,2,6);

    addTile(chunk, MISSILE, 3, 13); addUpdate(tileUpdates,3,13);
    
    
    //render & update chunk 30 times
    for (int i = 0; i < 60; i++) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n-\n");
        printChunk(chunk, tileUpdates); printf("\n");
        updateChunk(chunk, tileUpdates); tick++;
        usleep(250000);
    }
    
    return 0;
}