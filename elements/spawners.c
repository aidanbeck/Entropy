#include "periodicTable.h"
#include <stdlib.h> //for rand()

int spawnTimer = 0;
int spawnDelay = 1;

int spawnieCount = 4;
int spawnies[4] = { WOOD, GAS, PACKAGE, FIRE };

void spawnRandom(int index, Chunk *CHUNK) {

   update(index, CHUNK);

    if (spawnTimer > 0) {
        spawnTimer++;
        if (spawnTimer > spawnDelay) { spawnTimer = 0; }
        return;
    }

    spawnTimer++;

    int randomEnemy = spawnies[ rand() % spawnieCount ];
    int randomIndex = getRandomIndex();
    int canPlace = 0;

    for (int i = 0; i < 10; i++) {

        if ( indexIsEmpty(randomIndex, CHUNK) != 1) {
            randomIndex = getRandomIndex();
        } else {
            canPlace = 1;
            break;
        }
    }

    if (canPlace == 1) {
        uplaces(randomEnemy, randomIndex, CHUNK);
    }
}
Law     l_SPAWNRANDOM = { .func = spawnRandom };
Element E_SPAWNRANDOM = {
    .icon = 'R',
    .defaultLaw = &l_SPAWNRANDOM
};



int spawnElement = PACKAGE;
int spawnX = -4;
void spawnPackage(int index, Chunk *CHUNK) {

   update(index, CHUNK);

    int spawnIndex = moveIndexX(index, spawnX);

    if ( indexIsEmpty(spawnIndex, CHUNK) == 1 ) {
        uplaces(spawnElement, spawnIndex, CHUNK);
    }
}
Law     l_SPAWNPACKAGE = { .func = spawnPackage };
Element E_SPAWNPACKAGE = {
    .icon = 'S',
    .defaultLaw = &l_SPAWNPACKAGE
};