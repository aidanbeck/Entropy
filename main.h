#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//Ticks
#define TICK_LIMIT 50000
#define TICK_DURATION 300000

//Chunk Scaling
#define CHUNK_LENGTH 15
#define CHUNK_WIDTH 15*10
#define CHUNK_HEIGHT 1
#define CHUNK_SIZE (CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT)

//World Scaling (currently unused)
#define WORLD_LENGTH 1
#define WORLD_WIDTH 1
#define WORLD_HEIGHT 1
#define WORLD_SIZE (CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT)

//String size for printer.c
#define PRINT_RES ((CHUNK_LENGTH+CHUNK_HEIGHT+1) * (CHUNK_WIDTH+CHUNK_HEIGHT))

//Main Functions
void initializeArray(int *array, int length, int value);
void registerUpdate(int *newUpdates, int index);

//Tile Dictionary
enum Tiles {
    AIR,
    STONE,
    // SAND,
    WOOD,
    FIRE,
    FIRE2,
    //SMOKE,
    //MISSILE,
    //MISSILE2,
    //WATER,
    //HUMAN,

    CENTIHEAD_N, //centipede parts
    CENTIHEAD_S,
    CENTIHEAD_E,
    CENTIHEAD_W,
    CENTIHEAD_NE,
    CENTIHEAD_NW,
    CENTIHEAD_SE,
    CENTIHEAD_SW,

    CENTIBODY_N,
    CENTIBODY_S,
    CENTIBODY_E,
    CENTIBODY_W,
    CENTIBODY_NE,
    CENTIBODY_NW,
    CENTIBODY_SE,
    CENTIBODY_SW,

    CENTITAIL_N,
    CENTITAIL_S,
    CENTITAIL_E,
    CENTITAIL_W,
    CENTITAIL_NE,
    CENTITAIL_NW,
    CENTITAIL_SE,
    CENTITAIL_SW,

    BALL,

    TILE_TYPE_COUNT
};

//Chunk Structure
typedef struct {
    int chunk[CHUNK_SIZE];
    int updates[CHUNK_SIZE];
    int x;
    int y;
    int z;
} Chunk;

#endif