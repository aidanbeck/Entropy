#include "../elements/periodicTable.h"
#include "printer.h"
#include <stdio.h>

void clearScreen() {
    printf("\033[2J"); // Clear the screen
    printf("\033[H");  // Move the cursor to the top-left corner
}

void printAt(int x, int y, char character) {
    printf("\033[%d;%dH%c", y+1, x+1, character);
}

void printStringAt(int x, int y, char* string) {
    printf("\033[%d;%dH%s", y+1, x+1, string);
}

void printMemory1d(Chunk *CHUNK) {

    printf("\n\n---1d Memory---\n");
    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", CHUNK->TILES[i]);
    }
}

void printUpdates1d(Chunk *CHUNK) {
    
    printf("\n\n---1d Updates---\n");

    for (int i = 0; i < CHUNK_SIZE; i++) {
        printf("%d", CHUNK->UPDATES[i]);
    }
}

void printUpdates2d(Chunk *CHUNK) {

    printStringAt(75,0, "2D Updates");

    char hexish[36] = ".|23456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            int update = CHUNK->UPDATES[i*CHUNK_WIDTH + j];
            //printf("%c", hexish[update]);
            printAt(j+75+1, i+1, hexish[update]);
        }
        //printf(" %d\n",i);
    }
}

void printIcons1d(Chunk *CHUNK) {

    printf("\n\n---1d Icons---\n");

    for (int i = 0; i < CHUNK_SIZE; i++) {

        int tile = CHUNK->TILES[i];
        char icon = CHUNK->physics->PeriodicTable[tile].icon;
        printf("%c", icon);
    }
}

void printIcons2d(Chunk *CHUNK) {

    printStringAt(0,0, "2D Icons");

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            

            int tile = CHUNK->TILES[i*CHUNK_WIDTH + j];
            char icon = CHUNK->physics->PeriodicTable[tile].icon;
            //printf("%c", icon);
            printAt(j, i+1, icon);
        }
        //printf(" %d\n",i);
    }
    //printf("0123456789   10's   0123456789   30's   0123456789   50's   0123456789\n");
    //printf("   00's   0123456789   20's   0123456789   40's   0123456789   60's   \n");
}

void printPlayer(Chunk *CHUNK) {
    printf("\n-Truck-\n");
    printf("tires: %d.  gas: %d.  points: %d.                \n", PLAYER.tires, PLAYER.gas, PLAYER.points);

    int ix = indexToX(PLAYER.index);
    int iy = indexToY(PLAYER.index);    
    printf("index: %d. (%d,%d)                      \n", PLAYER.index, ix, iy);

    int tx = indexToX(PLAYER.target);
    int ty = indexToY(PLAYER.target);
    printf("target: %d. (%d,%d)                        \n", PLAYER.target, tx, ty);

}

void printHotLawTable(Chunk *CHUNK) {

    HotLaw **table = CHUNK->hotLawTable;
    
    printf("\n-HotLaws-\n");
    printf("count:%d, max:%d  -  ", CHUNK->hotLawCount, CHUNK->hotLawMax);

    for (int i = 0; i < 255; i++) {
        if (table[i] == NULL) { 
            //printf("%p #%d NULL,   ",(void*)table[i], i);
        } else {
            printf("(%d)A:%dB:%dC:%d   ", i, table[i]->input[0], table[i]->input[1], table[i]->input[2]);
            //printf("(%d)%p A:%d B:%d C:%d   \n", i, (void*)table[i], table[i]->input[0], table[i]->input[1], table[i]->input[2]);
        }
    }
    printf("\n");
}