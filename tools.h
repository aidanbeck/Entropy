//may rename this file in the future
#include "main.h"

typedef struct {
    int x;
    int y;
    int z;
    int length; //?
} Mesh;

int readT(int index, int *chunk);
void writeT(int tile, int index, int *updatedChunk);
void updateT(int *scheduledUpdates, int index);
void writeUpdate(int tile, int index, int *updatedChunk, int *scheduledUpdates);


int moveIndexX(int index, int x);
int moveIndexY(int index, int y);
int moveIndexZ(int index, int z);

int moveIndex(int index, int x, int y, int z);


void readAllDirections(int index, int *array);
void getMeshIndexes(int index, Mesh *mesh, int *array);

int readAbove(int index);
int readBelow(int index);
int readLeft(int index);
int readRight(int index);
int readFront(int index);
int readBack(int index);

