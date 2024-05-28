#include "tiles.h"
#include "printer.h"

/*
    Helper function for printIcons3d.
    Doesn't work for non-cubic chunks(?)
*/
int getTile(int *TILES, int x, int y,  int z) {
    return TILES[z*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_HEIGHT + x];
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

void printMemory1d(int *TILES) {

    printf("\n\n---1d Memory---\n");
    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", TILES[i]);
    }
}

void printUpdates1d(int *UPDATES) {
    
    printf("\n\n---1d Updates---\n");

    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", UPDATES[i]);
    }
}

void printUpdates2d(int *UPDATES) {

    printf("\n\n---2d Updates---\n");

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            int update = UPDATES[i*CHUNK_WIDTH + j];
            printf("%d", update);
        }
        printf(" %d\n",i);
    }
}

void printIcons1d(int *TILES) {

    printf("\n\n---1d Icons---\n");

    for (int i = 0; i < CHUNK_SIZE; i++) {

        int tile = TILES[i];
        char icon = TILE_TYPES[tile].icon;
        printf("%c", icon);
    }
}

void printIcons2d(int *tiles) {

    

    printf("\n\n---2d Icons---\n");

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            

            int tile = tiles[i*CHUNK_WIDTH + j];
            char icon = TILE_TYPES[tile].icon;
            printf("%c", icon);
        }
        printf(" %d\n",i);
    }
}

/*
    I haven't looked at this in a while, but it is likely a mess and should be refactored.
*/
void printIcons3d(int *TILES, int isometric) {

    char frame[PRINT_RES_3D]; initializeString(frame, PRINT_RES_3D, CHUNK_LENGTH*2, ' ');

    int mapHeight = CHUNK_WIDTH+CHUNK_HEIGHT;

    for (int y = CHUNK_HEIGHT; y > 0; y--) {
        for (int z = 0; z < CHUNK_WIDTH; z++) {
            for (int x = 0; x < CHUNK_LENGTH; x++) {    //can add x or y offset to CHUNK_LENGTH and CHUNK_WIDTH

                int tile = getTile(TILES, x, y, z);
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