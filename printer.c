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
    '~', //🌊
    '&',

    'N',
    'S',
    'E',
    'W',
    'n',
    'u',
    's',
    '5',

    '^',
    'v',
    '>',
    '<',
    '/',
    '\\',
    '/',
    '\\',

    '[',
    '[',
    '[',
    '[',
    '[',
    '[',
    '[',
    '[',

    'O',
    'O',
    'O',
    'O',
    'O',
    'O',
    'O',
    'O',
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

void printChunk2d(int *chunk) {

    printf("\n\n---2d Render---\n");
    for (int i = 0; i < CHUNK_LENGTH; i++) { // This starts at CHUNK_LENGTH and deecrements to 0. This way, 0 is the bottom of the display. Both values are subtracted by 1 because if this is not done, the display will be wrong
        for (int j = 0; j < CHUNK_WIDTH; j++) {
            int tile = chunk[i*CHUNK_WIDTH + j];
            char icon = symbols[tile];

            printf("%c", icon);
        }
        printf(" %d\n",i);
    }
}

void printUpdates2d(int *tileUpdates) {

    printf("\n\n---2d Updates---\n");
    for (int i = CHUNK_LENGTH-1; i > -1; i--) { // This starts at CHUNK_LENGTH and deecrements to 0. This way, 0 is the bottom of the display. Both values are subtracted by 1 because if this is not done, the display will be wrong
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            int update = tileUpdates[i*CHUNK_WIDTH + j];
            printf("%d", update);
        }
        printf(" %d\n",i);
    }
}

int getTile(int *chunk, int x, int y,  int z) { //used in 3d printer, doesn't work right with non cubic chunks
    return chunk[z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x];
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
            for (int x = 0; x < CHUNK_LENGTH; x++) {    //can add x or y offset to CHUNK_LENGTH and CHUNK_WIDTH

                int tile = getTile(chunk, x, y, z);
                if (tile != AIR /*&& tile != STONE*/) {

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

void dumpIcons(int *chunk) {
    //Dump all map icons (don't organize)
    printf("\n\n---Icon Dump---\n");
    for (int i = 0; i < CHUNK_SIZE; i++) {
        int tile = chunk[i];
        char icon = symbols[tile];
        printf("%c", icon);
    }
}

void dumpMemory(Chunk *CHUNK) {

    printf("\n\n---Memory Dump---\n");
    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", CHUNK->chunk[i]);
    }

    printf("\n\n---Updates Dump---\n");
    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", CHUNK->updates[i]);
    }


}