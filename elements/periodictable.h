#ifndef PERIODICTABLE_H
#define PERIODICTABLE_H

#include "../main.h"
#include "../physics.h"

enum E_Dictionary {

    AIR,
    STONE,
    WOOD,
    PACKAGE,
    CENTIBODY,
    FIRE,
    FIRE2,
    GAS,
    SPAWNRANDOM,
    SPAWNPACKAGE,
    TRUCK,
   
    TRAIL,
    COW,

    ELEMENT_COUNT
};

// Extern List
extern Element E_AIR;
extern Element E_STONE;
extern Element E_WOOD;
extern Element E_PACKAGE;
extern Element E_CENTIBODY;
extern Element E_FIRE;
extern Element E_FIRE2;
extern Element E_GAS;
extern Element E_SPAWNRANDOM;
extern Element E_SPAWNPACKAGE;
extern Element E_TRUCK;

extern Element E_TRAIL;
extern Element E_COW;

void compileElements(Physics *PHYSICS);
void setTruckIndex(int index);
void setTruckTarget(int index);
extern Truck PLAYER; //good idea?

#endif