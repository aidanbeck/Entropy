#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define CHUNK_LENGTH 16
#define CHUNK_WIDTH 16
#define CHUNK_HEIGHT 16
#define CHUNK_SIZE (CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT)

#define WORLD_LENGTH 16
#define WORLD_WIDTH 16
#define WORLD_HEIGHT 2
#define WORLD_SIZE (CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT)




#define PRINT_RES ((CHUNK_LENGTH+CHUNK_HEIGHT+1) * (CHUNK_WIDTH+CHUNK_HEIGHT))

void initializeArray(int *array, int length, int value);
int getTile(int *chunk, int x, int y,  int z);
void addTile(int *chunk, int tile, int x, int y, int z);
void addUpdate(int *tileUpdates, int x, int y, int z);
void fillTile(int *chunk, int tile, int x1, int y1, int z1, int x2, int y2, int z2);

void registerUpdate(int *newUpdates, int index);

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
    WATER,
    HUMAN,

    TILE_TYPE_COUNT
};

typedef struct {
    int chunk[CHUNK_SIZE];
    int updates[CHUNK_SIZE];
    int x;
    int y;
    int z;
} Chunk;

#endif