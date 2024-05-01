#include "main.h"

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
void printChunk(int *chunk/*, int *tileUpdates*/) {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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


void initializeString(char *array, int length, int lineLength, char value) {

    int seatNumber = 0;

    for (int i = 0; i < length; i++) {
        array[i] = value;
        seatNumber++;

        if (seatNumber == lineLength) {
            seatNumber = 0;
            array[i] = '\n';
            
        }
    }
}

void printChunk3d(int *chunk, int isometric) {

    char frame[PRINT_RES]; initializeString(frame, PRINT_RES, CHUNK_LENGTH*2, ' ');

    int mapHeight = CHUNK_WIDTH+CHUNK_HEIGHT;

    for (int y = CHUNK_HEIGHT; y > 0; y--) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            for (int x = 0; x < CHUNK_LENGTH; x++) {

                int tile = getTile(chunk, x, y, z);
                if (tile != AIR && tile != STONE) {

                    if (isometric == 1) {
                        frame[(z+y)*mapHeight+x+(CHUNK_HEIGHT-y)] = symbols[tile]; //isometric
                    } else {
                        frame[z*mapHeight+x] = symbols[tile]; //top down
                    }
                    
                    

                }
            }
        }
    }

    //print frame
    printf("%s", frame);
}