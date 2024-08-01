#include "periodicTable.h"
#include "../laws/lawTable.h" //to access common laws

void shamble(int index, Chunk *CHUNK) {

    int speed = 2;

    int returnIndex;
    moveIndexTowards(index, PLAYER.index, speed, &returnIndex, CHUNK);
    
    update(index, CHUNK);
}

Law     l_SHAMBLE = { .func = shamble };

Element E_ZOMBIE = {
    .icon = 'Z',
    .defaultLaw = &l_SHAMBLE
};

Element E_CORPSE = {
    .icon = '@',
    .defaultLaw = &L_NOTHING
};