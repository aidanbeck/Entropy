
#include <stdio.h>
#include <unistd.h>

void printChunk(int *chunk);
void printChunk2d(int *chunk);
void printUpdates2d(int *chunk);
void printChunk3d(int *chunk, int isometric);

void dumpMemory(Chunk *CHUNK);