#include "periodictable.h"
#include "../tools.h"
#include "../moves.h"

int spawnDelay = 0;
void ruleSPAWN_RANDOM(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    if (spawnDelay > 0) {

        spawnDelay++;
        if (spawnDelay > 10) { spawnDelay = 0; }

        return;
    }

    spawnDelay++;

    printf("\n%d", spawnDelay);

    int randomIndex = getRandomIndex();
    for (int i = 0; i < 10; i++) {

        if ( readT(randomIndex, TILES) != AIR ) {
            randomIndex = getRandomIndex();
            continue;
        }
        break;
    }

    writeUpdate(WOOD, randomIndex, nextTiles, nextUpdates);
}

Element tileSPAWN_RANDOM = {
    .icon = 'R',
    .name = "Spawner (Random)",
    .rule = ruleSPAWN_RANDOM
};