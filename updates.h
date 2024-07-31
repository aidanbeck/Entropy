#ifndef UPDATES_H
#define UPDATES_H

#include "main.h"


void prepareChunk(Chunk *CHUNK);
void updateAllTiles(Chunk *CHUNK, Physics *PHYSICS);
void overwriteChunk(Chunk *CHUNK);
void updateChunk(Chunk *CHUNK, Physics *PHYSICS);

void initializeArray(uint8_t *array, int length, int value);

#endif