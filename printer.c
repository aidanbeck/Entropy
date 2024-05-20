#include "tiles.h"
#include "printer.h"

/*
    Helper function for printIcons3d.
    Doesn't work for non-cubic chunks(?)
*/
int getTile(int *chunk, int x, int y,  int z) {
    return chunk[z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x];
}

/*
    Helper function for printIcons3d.
    Eventually should be a helper function for the other functions to decrease stutter.
*/
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

void printMemory1d(int *chunk) {

    printf("\n\n---1d Memory---\n");
    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", chunk[i]);
    }
}

void printUpdates1d(int *tileUpdates) {
    
    printf("\n\n---1d Updates---\n");

    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", tileUpdates[i]);
    }
}

void printUpdates2d(int *tileUpdates) {

    printf("\n\n---2d Updates---\n");

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            int update = tileUpdates[i*CHUNK_WIDTH + j];
            printf("%d", update);
        }
        printf(" %d\n",i);
    }
}

void printIcons1d(int *chunk) {

    printf("\n\n---1d Icons---\n");

    for (int i = 0; i < CHUNK_SIZE; i++) {

        int tile = chunk[i];
        char icon = TILE_TYPES[tile].icon;
        printf("%c", icon);
    }
}

void printIcons2d(int *chunk) {

    printf("\n\n---2d Icons---\n");

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            int tile = chunk[i*CHUNK_WIDTH + j];
            char icon = TILE_TYPES[tile].icon;
            printf("%c", icon);
        }
        printf(" %d\n",i);
    }
}

/*
    I haven't looked at this in a while, but it is likely a mess and should be refactored.
*/
void printIcons3d(int *chunk, int isometric) {

    char frame[PRINT_RES_3D]; initializeString(frame, PRINT_RES_3D, CHUNK_LENGTH*2, ' ');

    int mapHeight = CHUNK_WIDTH+CHUNK_HEIGHT;

    for (int y = CHUNK_HEIGHT; y > 0; y--) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            for (int x = 0; x < CHUNK_LENGTH; x++) {    //can add x or y offset to CHUNK_LENGTH and CHUNK_WIDTH

                int tile = getTile(chunk, x, y, z);
                if (tile != AIR /*&& tile != STONE*/) {

                    if (isometric == 1) {
                        frame[(z+y)*mapHeight+x+(CHUNK_HEIGHT-y)] = TILE_TYPES[tile].icon; //isometric
                    } else {
                        frame[z*mapHeight+x] = TILE_TYPES[tile].icon; //top down
                    }
                }
            }
        }
    }

    printf("%s", frame);
}