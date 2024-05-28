#ifndef MAIN_H
#define MAIN_H
//Why do I need these^?

//Ticks
#define TICK_LIMIT 500
#define TICK_DURATION 500000

//Chunk Scaling
#define CHUNK_LENGTH 15
#define CHUNK_WIDTH 75
#define CHUNK_HEIGHT 1
#define CHUNK_SIZE (CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT)

//World Scaling (currently unused)
#define WORLD_LENGTH 1
#define WORLD_WIDTH 1
#define WORLD_HEIGHT 1
#define WORLD_SIZE (CHUNK_LENGTH * CHUNK_WIDTH * CHUNK_HEIGHT)

//Chunk Structure
typedef struct {
    int TILES[CHUNK_SIZE];
    int UPDATES[CHUNK_SIZE];
} Chunk;

#endif