
//Should "Mesh" and Mesh-related code be stored in a "Meshes.c" file?
typedef struct {
    int x;
    int y;
    int z;
    int length; //Should length be stored another way?
} Mesh;

int readT(int index, int *TILES);
void writeT(int tile, int index, int *nextTiles);
void updateT(int *nextUpdates, int index);
void writeUpdate(int tile, int index, int *nextTiles, int *nextUpdates);

int moveIndexX(int index, int x);
int moveIndexY(int index, int y);
int moveIndexZ(int index, int z);
int moveIndex(int index, int x, int y, int z);

void readAllDirections(int index, int *array);
void getMeshIndexes(int index, Mesh *mesh, int *array);
void readMesh(int index, Mesh *mesh, int *array, int *TILES);

int indexIsEmpty(int index, int *TILES, int *nextTiles);
void meshIsEmpty(int index, Mesh *mesh, int *array, int *TILES, int *nextTiles);