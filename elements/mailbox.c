#include "periodicTable.h"
#include <stdio.h>

Mesh compassRose3[4] = { // this numbered system for reusal is BAD BAD BAD
    { .x = 0, .y = -1, .z = 0, .length = 4},
    { .x = 0, .y = 1, .z = 0},
    { .x = -1, .y = 0, .z = 0},
    { .x = 1, .y = 0, .z = 0},
};

void collectMail(int index, Chunk *CHUNK) {


    int meshIndexes[4];
    getMeshIndexes(index, compassRose3, meshIndexes);

    uint8_t meshTiles[4];
    viewFaces(index, meshTiles, CHUNK);

    for (int i = 0; i < 4; i++) {

        if (meshTiles[i] == PACKAGE) {
            uplaces(AIR, meshIndexes[i], CHUNK);
            PLAYER.points++;
            printf("you got a point!\n");
        }
    }
}
Law     l_COLLECTMAIL = { .func = collectMail };
Element E_MAILBOX = {
    .icon = '%',
    .defaultLaw = &l_COLLECTMAIL
};