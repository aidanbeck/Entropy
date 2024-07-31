#include "periodicTable.h"

Mesh compassRose[4] = {
    { .x = 0, .y = -1, .z = 0, .length = 4},
    { .x = 0, .y = 1, .z = 0},
    { .x = -1, .y = 0, .z = 0},
    { .x = 1, .y = 0, .z = 0},
};

//FIRE
void burnFrame(int index, Chunk *CHUNK) {
    uplace(FIRE2, index, CHUNK);
}
Law     l_BURNFRAME = { .func = burnFrame };
Element E_FIRE = {
    .icon = '%',
    .defaultLaw = &l_BURNFRAME
};

//FIRE2
void fireSpread(int index, Chunk *CHUNK) {

    uplace(AIR, index, CHUNK); //removed smoke for now

    int meshIndexes[4];
    getMeshIndexes(index, compassRose, meshIndexes);

    uint8_t meshTiles[4];
    viewFaces(index, meshTiles, CHUNK);

    for (int i = 0; i < 4; i++) {

        if (meshTiles[i] == WOOD) {
            uplaces(FIRE, meshIndexes[i], CHUNK);
        }
    }
}
Law     l_FIRESPREAD = { .func = fireSpread };
Element E_FIRE2 = {
    .icon = '%',
    .defaultLaw = &l_FIRESPREAD
};

/*
    Potential Improvements Notes:


*/