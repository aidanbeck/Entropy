#include "periodicTable.h"
#include "../laws/lawTable.h" //to access common laws

Element E_AIR = {
    .icon = ' ',
    .defaultLaw = &L_NOTHING
};

Element E_STONE = {
    .icon = '#',
    .defaultLaw = &L_NOTHING
};

Element E_WOOD = {
    .icon = '+',
    .defaultLaw = &L_NOTHING
};

Element E_PACKAGE = {
    .icon = 'H',
    .defaultLaw = &L_NOTHING
};  

Element E_CENTIBODY = {
    .icon = ':',
    .defaultLaw = &L_NOTHING
};

Element E_TIRE = {
    .icon = 'O',
    .defaultLaw = &L_NOTHING
};



// Not Simple But Temporary
void evaporate(int index, Chunk *CHUNK) { CHUNK->TILES[index] = 0; }
Law     l_EVAPORATE = { .func = evaporate };
Element E_TRAIL = { .defaultLaw = &l_EVAPORATE, .icon = '~'};


void cow(int index, Chunk *CHUNK) {
    moveTileTowards(index, index+10, 4, CHUNK);
    update(index, CHUNK);
}
Law l_COW = { .func = cow};
Element E_COW = { .defaultLaw = &l_COW, .icon = 'n'};