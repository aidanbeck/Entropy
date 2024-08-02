#include "periodicTable.h"
#include <stdio.h>

Truck PLAYER = {
    .x = 10,
    .y = 3,
    .tires = 4,
    .gas = 100,
    .points = 0
};

void updateTruck(int index, Chunk *CHUNK) {

    if (PLAYER.index != index) {
        printf("something has gone wrong! my index is %d but the truck block is at %d!\n", PLAYER.index, index);
    }

    if (PLAYER.index != PLAYER.target && PLAYER.gas > 0 && PLAYER.tires > 0) {
        
        moveTileTowards(index, PLAYER.target, 4, CHUNK);
        
        // These can be done here rather than inside the function if it is just given the information?
        //setTruckIndex(returnIndex);
        //PLAYER.gas -= steps;

        if (PLAYER.gas < 0) { PLAYER.gas = 0; }

    }

    update(index, CHUNK);
}

Law l_UPDATETRUCK = {.func=updateTruck};
Element E_TRUCK = {
    .icon = '=',
    .defaultLaw = &l_UPDATETRUCK
};

void setTruckIndex(int index) {

    Truck *truck = &PLAYER; //defined in this file

    //update truck information
    truck->index = index;
    truck->x = indexToX(index);
    truck->y = indexToY(index);    
}

//setTruckTarget is inside of barista.c because it needs to be accessible from JS