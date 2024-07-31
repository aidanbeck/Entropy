#include "periodicTable.h"

Mesh compassRose2[4] = {
    { .x= 0,    .y= -1,     .z= 0, .length=4 }, //N
    { .x= 0,    .y= 1,      .z= 0 }, //S
    { .x= 1,    .y= 0,      .z= 0 }, //E
    { .x= -1,   .y= 0,      .z= 0 }, //W
};

Mesh Explosion[20] = {
    //  89A
    // J701B
    // I6&2C
    // H543D
    //  GFE

    { .x= -1,   .y= -2,     .z= 0, .length=20 },
    { .x=  0,   .y= -2,     .z= 0 },
    { .x=  1,   .y= -2,     .z= 0 },

    { .x= -2,   .y= -1,     .z= 0 },
    { .x= -1,   .y= -1,     .z= 0 },
    { .x=  0,   .y= -1,     .z= 0 },
    { .x=  1,   .y= -1,     .z= 0 },
    { .x=  2,   .y= -1,     .z= 0 },

    { .x= -2,   .y=  0,     .z= 0 },
    { .x= -1,   .y=  0,     .z= 0 },
    // // { .x=  0,   .y=  0,     .z= 0 },
    { .x=  1,   .y=  0,     .z= 0 },
    { .x=  2,   .y=  0,     .z= 0 },

    { .x= -2,   .y=  1,     .z= 0 },
    { .x= -1,   .y=  1,     .z= 0 },
    { .x=  0,   .y=  1,     .z= 0 },
    { .x=  1,   .y=  1,     .z= 0 },
    { .x=  2,   .y=  1,     .z= 0 },

    { .x=  1,   .y=  2,     .z= 0 },
    { .x=  0,   .y=  2,     .z= 0 },
    { .x= -1,   .y=  2,     .z= 0 },
};

void explode(int index, Chunk *CHUNK) {
    
    uplace(FIRE, index, CHUNK); //turn into fire

    int meshIndexes[20];
    getMeshIndexes(index, Explosion, meshIndexes);

    for (int i = 0; i < 20; i++) {

        if (indexIsEmpty(meshIndexes[i], CHUNK) == 0) {continue;}
        if (indexInBounds(meshIndexes[i]) == 0)       {continue;}

        uplaces(FIRE, meshIndexes[i], CHUNK);
    }
}
Law     l_EXPLODE = { .func = explode };

void explodeOnFlame(int index, Chunk *CHUNK) {

    uint8_t meshTiles[4];
    viewMesh(index, compassRose2, meshTiles, CHUNK);

    int meshIndexes[4];
    getMeshIndexes(index, compassRose2, meshIndexes);


    for (int i = 0; i < 4; i++) {

        if (meshTiles[i] != FIRE) { continue; }
        explode(index, CHUNK);
        break;
    }
}
Law     l_EXPLODEONFLAME = { .func = explodeOnFlame };
Element E_GAS = {
    .icon = 'U',
    .defaultLaw = &l_EXPLODEONFLAME,
    .endOfPush = &l_EXPLODE
};

/*
    If I want gas to "explode" after being pushed, how should I go about this?

    Perhaps the moveTowardsIndex function could return:
    - steps it took
    - steps it tried to take
    - the new index

    Then, in the "push" function, it could take the newIndex, and run that element's "endOfPush" law if it has one.
    And, E_GAS's endOfPush law will be Explode
*/