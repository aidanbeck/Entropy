#ifndef TILE_H
#define TILE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

//Tile Dictionary
enum Tiles {
    AIR,
    STONE,
    WOOD,
    FIRE,
    FIRE2,

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

void compileRules();

#endif