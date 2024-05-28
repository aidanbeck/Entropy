
//Should "Mesh" and Mesh-related code be stored in a "Meshes.c" file?
typedef struct {
    int x;
    int y;
    int z;
    int length; //Should length be stored another way?
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
void readMesh(int index, Mesh *mesh, int *array, int *chunk);

int readEast(int index);
int readWest(int index);
int readNorth(int index);
int readSouth(int index);
int readDown(int index);
int readUp(int index);

int indexIsEmpty(int index, int *chunk, int *updatedChunk);
void meshIsEmpty(int index, Mesh *mesh, int *array, int *chunk, int *updatedChunk);