#include "../elements/periodicTable.h"
#include "printer.h"
#include <stdio.h>

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

    printf("\n\n---2d Updates---\n");

    char hexish[36] = ".|23456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            int update = CHUNK->UPDATES[i*CHUNK_WIDTH + j];
            printf("%c", hexish[update]);
        }
        printf(" %d\n",i);
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

    printf("\n\n---2d Icons---\n");

    for (int i = 0; i < CHUNK_LENGTH; i++) {
        for (int j = 0; j < CHUNK_WIDTH; j++) {

            

            int tile = CHUNK->TILES[i*CHUNK_WIDTH + j];
            char icon = CHUNK->physics->PeriodicTable[tile].icon;
            printf("%c", icon);
        }
        printf(" %d\n",i);
    }
    printf("0123456789   10's   0123456789   30's   0123456789   50's   0123456789\n");
    printf("   00's   0123456789   20's   0123456789   40's   0123456789   60's   \n");
}

void printPlayer(Chunk *CHUNK) {
    printf("\n-Truck-\n");
    printf("tires: %d.  gas: %d.  points: %d.\n", PLAYER.tires, PLAYER.gas, PLAYER.points);

    int ix = indexToX(PLAYER.index);
    int iy = indexToY(PLAYER.index);    
    printf("index: %d. (%d,%d)\n", PLAYER.index, ix, iy);

    int tx = indexToX(PLAYER.target);
    int ty = indexToY(PLAYER.target);
    printf("target: %d. (%d,%d)\n", PLAYER.target, tx, ty);

}

void printHotLawTable(Chunk *CHUNK) {

    HotLaw **table = CHUNK->hotLawTable;

    printf("\ncount:%d, max:%d  -  ", CHUNK->hotLawCount, CHUNK->hotLawMax);

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