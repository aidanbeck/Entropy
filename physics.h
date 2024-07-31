#ifndef PHYSICS_H
#define PHYSICS_H

#include "main.h"
#include <stdint.h> // for uint8_t

typedef struct Chunk Chunk; // Allow "Law" struct to reference "Chunk" struct.
typedef struct Mesh Mesh;

typedef struct {
    void (*func)(int index, Chunk *chunk);
} Law;

typedef struct {
    int lastTickUsed;
    int inputCount;
    int input[3];
    Law *law;
} HotLaw;

typedef struct {
    char icon;
    Law *defaultLaw;
    Law *endOfPush;
} Element;

typedef struct {
    Element PeriodicTable[256];
    Law     LawTable[1000]; //!!! Should be LAW_COUNT
} Physics;

//Low Level Functions
uint8_t view(int index, Chunk *CHUNK);
void place(uint8_t tile, int index, Chunk *CHUNK);
void update(int index, Chunk *CHUNK);
int indexIsEmpty(int index, Chunk *CHUNK);

int moveIndexX(int index, int x);
int moveIndexY(int index, int y);
int moveIndexZ(int index, int z);
int moveIndex(int index, int x, int y, int z);

void getMeshIndexes(int index, Mesh *MESH, int *array);
void viewMesh(int index, Mesh *MESH, uint8_t *array, Chunk *CHUNK);
void placeMesh(uint8_t tile, int index, Mesh *MESH, Chunk *CHUNK);
void updateMesh(int index, Mesh *MESH, Chunk *CHUNK);
void meshIsEmpty(int index, Mesh *MESH, int *array, Chunk *CHUNK);

void viewFaces(int index, uint8_t *array, Chunk *CHUNK);
void updates(int index, Chunk *CHUNK);
void uplace(uint8_t tile, int index, Chunk *CHUNK);
void uplaces(uint8_t tile, int index, Chunk *CHUNK);

void hot(int index, int *input, Law *law, Chunk *CHUNK);

//High Level Functions
int getRandomIndex();
int indexToX(int index);
int indexToY(int index);
int indexToZ(int index);
int indexInBounds(int index);
void getTargetDirection(int index, int targetIndex, int *x, int *y, int *z);
int matchesTargetAxis(int index, int targetIndex);
int moveIndexTowards(int index, int targetIndex, int distance, int *returnIndex, Chunk *CHUNK);

#endif