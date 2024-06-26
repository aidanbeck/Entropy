#include "periodictable.h"
#include "../tools.h"
#include "../moves.h"

int spawnTimer = 0;
int spawnDelay = 5;

int EnemyNum = 4;
int Enemies[4] = { WOOD, GAS, PACKAGE, FIRE };

void ruleSPAWN_RANDOM(int *TILES, int *nextTiles, int *nextUpdates, int index) {

    /*
        updateT(nextUpdates, index);

        updateT crashes because CURRENTLY, updateT runs registerUpdate, which updates many tiles.
        Because this is on the border, it updates tiles out of bounds and seg faults.

        updateT should be changed to update a single index, and there should be an updateMesh.
        Other tiles should be refactored to use an updateMesh function.

        For now, I will manually re-update this tile.
    */
   nextUpdates[index] = 1;


    if (spawnTimer > 0) {

        spawnTimer++;
        if (spawnTimer > spawnDelay) { spawnTimer = 0; }

        return;
    }

    spawnTimer++;

    int randomEnemy = Enemies[ rand() % EnemyNum ];
    int randomIndex = getRandomIndex();
    int canPlace = 0;

    for (int i = 0; i < 10; i++) {

        if ( indexIsEmpty(randomIndex, TILES, nextTiles) != 1) {
            randomIndex = getRandomIndex();
        } else {
            canPlace = 1;
            break;
        }
    }

    if (canPlace == 1) {
        writeUpdate(randomEnemy, randomIndex, nextTiles, nextUpdates);
    }
}

Element eSPAWN_RANDOM = {
    .icon = 'R',
    .name = "Spawner (Random)",
    .rule = ruleSPAWN_RANDOM
};




int spawnElement = PACKAGE;
int spawnX = -4;

void ruleSPAWN(int *TILES, int *nextTiles, int *nextUpdates, int index) {

   nextUpdates[index] = 1;

    int spawnIndex = moveIndexX(index, spawnX);

    if ( indexIsEmpty(spawnIndex, TILES, nextTiles) == 1 ) {
        writeUpdate(spawnElement, spawnIndex, nextTiles, nextUpdates);
    }
}

Element eSPAWNER = {
    .icon = 'S',
    .name = "Spawner",
    .rule = ruleSPAWN
};