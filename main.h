#ifndef MAIN_H
#define MAIN_H

#include <stdint.h> // for uint8_t
#include "physics.h"
#include "updates.h"
#include "devtools/map.h"

//Compile Mod | 0 - gcc | 1 - emcc |
#define COMPILE_MODE 0

//Ticks
#define TICK_LIMIT 40
#define TICK_DURATION 500000

//Chunk Scaling
#define CHUNK_LENGTH 15
#define CHUNK_WIDTH 75
#define CHUNK_HEIGHT 1
#define CHUNK_SIZE (CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT)

typedef struct {
    int index;
    int target;
    int x;
    int y;
    int tires;
    int gas;
    Chunk *chunk;
} Truck;

//Chunk Structure
struct Chunk {
    int tick;
    int input[3];
    
    uint8_t TILES[CHUNK_SIZE];
    uint8_t UPDATES[CHUNK_SIZE];
    uint8_t nextTiles[CHUNK_SIZE];
    uint8_t nextUpdates[CHUNK_SIZE];

    int hotLawCount;
    int hotLawMax;
    HotLaw *hotLawTable[256]; // POINTERS

    Physics *physics;
    Truck *truck;
};

struct Mesh {
    int x;
    int y;
    int z;
    int length;
};


#endif