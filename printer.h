void printMemory1d(int *TILES);

void printUpdates1d(int *UPDATES);
void printUpdates2d(int *UPDATES);

void printIcons1d(int *TILES);
void printIcons2d(int *TILES);
void printIcons3d(int *TILES, int isometric);
#define PRINT_RES_3D (CHUNK_LENGTH+CHUNK_HEIGHT+1) * (CHUNK_WIDTH+CHUNK_HEIGHT)