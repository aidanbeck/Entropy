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
        if (chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == WOOD) {
            updatedChunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] = FIRE; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH*CHUNK_HEIGHT);
        }
        if (chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == WOOD) {
            updatedChunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] = FIRE; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH*CHUNK_HEIGHT);
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

        //downwards
        if (chunk[index+CHUNK_LENGTH] == AIR || chunk[index+CHUNK_LENGTH] == FIRE || chunk[index+CHUNK_LENGTH] == SAND) {
            updatedChunk[index+CHUNK_LENGTH] = WATER; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH);
        }

        //forwards and back
        if (chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == AIR || chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == FIRE || chunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] == SAND) {
            updatedChunk[index+CHUNK_LENGTH*CHUNK_HEIGHT] = WATER; registerUpdate(scheduledUpdates, index+CHUNK_LENGTH*CHUNK_HEIGHT);
        }
        if (chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == AIR || chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == FIRE || chunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] == SAND) {
            updatedChunk[index-CHUNK_LENGTH*CHUNK_HEIGHT] = WATER; registerUpdate(scheduledUpdates, index-CHUNK_LENGTH*CHUNK_HEIGHT);
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
        
        int z = 9;
        for (int x = 0; x < CHUNK_HEIGHT; x++) {
            printf("%c ",symbols[chunk[z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x]]);
        }
        
        printf(" : ");
        
        z = 9;
        for (int x = 0; x < CHUNK_HEIGHT; x++) {
            printf("%c ",symbols[chunk[y*CHUNK_WIDTH*CHUNK_HEIGHT + z*CHUNK_HEIGHT + x]]);
        }
        
        // for (int x = 0; x < CHUNK_HEIGHT; x++) {
        //     printf("%d ", tileUpdates[(y*CHUNK_LENGTH)+x]);
        // }

        printf("\n"); 
    }
}

void printChunk3d(int *chunk) {
    int renderMap[PRINT_RES]; initializeArray(renderMap, PRINT_RES, 0);
    int renderMapOffset[PRINT_RES]; initializeArray(renderMapOffset, PRINT_RES, 0);

    int mapLength = CHUNK_LENGTH+CHUNK_HEIGHT;
    int mapHeight = CHUNK_WIDTH+CHUNK_HEIGHT;

    for (int y = CHUNK_HEIGHT; y > 0; y--) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            for (int x = 0; x < CHUNK_LENGTH; x++) {

                int tile = getTile(chunk, x, y, z);
                if (tile != AIR && tile != STONE) {
                    //renderMap[z*mapHeight+x] = tile; 2d top down
                    renderMap[(z+y)*mapHeight+x+(CHUNK_HEIGHT-y)] = tile;
                }


            }
        }
    }

    
    for (int y = 0; y < mapHeight; y++) {
        for (int x = 0; x < mapLength; x++) {
            int tile = renderMap[y*mapHeight+x];
            //int offset = renderMapOffset[y*mapHeight+x];
            char character = symbols[tile];
            printf("%c", character);
            //printf(" ");
            
        }
        printf("\n");
    }

}

int main() {

    //set up world
    int tick = 0;
    int chunk[CHUNK_SIZE];        initializeArray(chunk, CHUNK_SIZE, 0);
    int tileUpdates[CHUNK_SIZE];  initializeArray(tileUpdates, CHUNK_SIZE, 0);


    // fillTile(chunk, STONE, 0, 0, 0, 16, 1, 16);
    // 
    // fillTile(chunk, SAND, 8, 0, 8, 9, 9, 9);

    fillTile(chunk, STONE, 0, 0, 0, 16, 16, 16);
    fillTile(chunk, AIR, 1, 1, 1, 15, 15, 15);

    //beams
    fillTile(chunk, WOOD, 1, 8, 1, 15, 9, 2);   fillTile(chunk, SAND, 1, 7, 1, 15, 8, 2);
    fillTile(chunk, WOOD, 1, 8, 14, 15, 9, 15); fillTile(chunk, SAND, 1, 7, 14, 15, 8, 15);
    fillTile(chunk, WOOD, 1, 8, 1, 2, 9, 15);   fillTile(chunk, SAND, 1, 7, 1, 2, 8, 15);
    fillTile(chunk, WOOD, 14, 8, 1, 15, 9, 15); fillTile(chunk, SAND, 14, 7, 1, 15, 8, 15);

    //floor beams
    fillTile(chunk, WOOD, 14, 14, 1, 15, 15, 15);
    fillTile(chunk, WOOD, 1, 14, 14, 15, 15, 15);
    fillTile(chunk, WOOD, 1, 14, 1, 15, 15, 2);
    

    //tall beams
    fillTile(chunk, SAND, 1, 2, 1, 15, 3, 2);   fillTile(chunk, WOOD, 1, 3, 1, 15, 4, 2);
    fillTile(chunk, SAND, 1, 2, 14, 15, 3, 15); fillTile(chunk, WOOD, 2, 3, 14, 15, 4, 15);
    fillTile(chunk, SAND, 1, 2, 1, 3, 4, 15);   fillTile(chunk, WOOD, 1, 2, 1, 2, 4, 15);
    fillTile(chunk, SAND, 14, 2, 1, 15, 3, 15); fillTile(chunk, WOOD, 14, 3, 1, 15, 4, 15);

    //pillars
    fillTile(chunk, WOOD, 1, 1, 1, 2, 15, 2);
    fillTile(chunk, WOOD, 14, 1, 1, 15, 15, 2);
    fillTile(chunk, WOOD, 1, 1, 14, 2, 15, 15);
    fillTile(chunk, WOOD, 14, 1, 14, 15, 15, 15);

    //sand pillar
    fillTile(chunk, SAND, 7, 5, 7, 10, 15, 10);

    //wooden floor
    fillTile(chunk, WOOD, 1, 14, 1, 5, 15, 5);
    fillTile(chunk, WATER, 2, 14, 2, 4, 15, 4);

    //friendly missile
    addTile(chunk, MISSILE2, 12, 13, 12); addUpdate(tileUpdates, 12, 13, 12);
    addTile(chunk, MISSILE2, 13, 10, 14); addUpdate(tileUpdates, 13, 10, 14);

    // fillTile(chunk, WOOD, 1, 1, 1, 15, 2, 15);
    // fillTile(chunk, SAND, 1, 2, 1, 15, 3, 15);
    // addUpdate(tileUpdates, 1,2,1);

    
    //render & update chunk 30 times
    for (int i = 0; i < 120+64; i++) {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        printf("\n-\n");
        //printChunk(chunk, tileUpdates); printf("\n");
        printChunk3d(chunk);
        updateChunk(chunk, tileUpdates); tick++;
        usleep(100000);
    }
    
    return 0;
}