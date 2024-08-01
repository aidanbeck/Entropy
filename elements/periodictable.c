#include "../main.h"
#include "../physics.h"
#include "periodicTable.h"

void compileElements(Physics *PHYSICS) {

    Element *E = PHYSICS->PeriodicTable;

    E[AIR] = E_AIR;
    E[STONE] = E_STONE;
    E[WOOD] = E_WOOD;
    E[PACKAGE] = E_PACKAGE;
    E[CENTIBODY] = E_CENTIBODY;
    E[FIRE] = E_FIRE;
    E[FIRE2] = E_FIRE2;
    E[GAS] = E_GAS;

    E[SPAWNRANDOM] = E_SPAWNRANDOM;
    E[SPAWNPACKAGE] = E_SPAWNPACKAGE;

    E[TRUCK] = E_TRUCK;
    E[MAILBOX] = E_MAILBOX;
    E[ZOMBIE] = E_ZOMBIE;
    E[CORPSE] = E_CORPSE;
    E[TIRE] = E_TIRE;

    E[TRAIL] = E_TRAIL;
    E[COW] = E_COW;
}