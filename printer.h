
#include <stdio.h>
#include <unistd.h>

//String size for printChunk3d
#define PRINT_RES_3D ((CHUNK_LENGTH+CHUNK_HEIGHT+1) * (CHUNK_WIDTH+CHUNK_HEIGHT))

void printChunk(int *chunk);
void printChunk2d(int *chunk);
void printUpdates2d(int *chunk);
void printChunk3d(int *chunk, int isometric);

void dumpMemory(Chunk *CHUNK);