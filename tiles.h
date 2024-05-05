#ifndef TILE_H
#define TILE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

void compileRules();

typedef struct {
    char icon;
    char name[16];
    void (*rule)(int *chunk, int *updatedChunk, int *scheduledUpdates, int index);
} Tile;

typedef struct {
    int index;
    int id;
    int xDir;
    int yDir;
    int zDir;
    int moveCountdown;
} Entity;

extern Tile TILE_TYPES[TILE_TYPE_COUNT];

#endif