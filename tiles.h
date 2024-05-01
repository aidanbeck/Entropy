#ifndef TILE_H
#define TILE_H

#include <stdio.h>
#include <unistd.h>
#include "main.h"

void compileRules();

typedef struct {
    char icon;
    char name[16];
    void (*rule)(int *chunk, int *updatedChunk, int *scheduledUpdates, int index);
} Tile;

extern Tile TILE_TYPES[TILE_TYPE_COUNT];

#endif