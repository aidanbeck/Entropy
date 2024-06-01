int getRandomIndex();
int stepIndexTowards(int index, int targetIndex);
int moveIndexTowards(int index, int targetIndex, int distance, int *TILES, int *nextTiles, int *nextUpdates);
int indexInBounds(int index);