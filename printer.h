void printMemory1d(int *chunk);

void printUpdates1d(int *tileUpdates);
void printUpdates2d(int *tileUpdates);

void printIcons1d(int *chunk);
void printIcons2d(int *chunk);
void printIcons3d(int *chunk, int isometric);
#define PRINT_RES_3D (CHUNK_LENGTH+CHUNK_HEIGHT+1) * (CHUNK_WIDTH+CHUNK_HEIGHT)