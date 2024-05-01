#include "main.h"

void createBorder(int *chunk) {
    fillTile(chunk, STONE, 0, 0, 0, 16, 16, 16);
    fillTile(chunk, AIR, 1, 1, 1, 15, 15, 15);
}

void mapTower(int *chunk) {
    
    //beams
    fillTile(chunk, WOOD, 1, 8, 1, 15, 9, 2);   fillTile(chunk, SAND, 1, 7, 1, 15, 8, 2);
    fillTile(chunk, WOOD, 1, 8, 14, 15, 9, 15); fillTile(chunk, SAND, 1, 7, 14, 15, 8, 15);
    fillTile(chunk, WOOD, 1, 8, 1, 2, 9, 15);   fillTile(chunk, SAND, 1, 7, 1, 2, 8, 15);
    fillTile(chunk, WOOD, 14, 8, 1, 15, 9, 15); fillTile(chunk, SAND, 14, 7, 1, 15, 8, 15);

    //floor beams
    fillTile(chunk, WOOD, 14, 14, 1, 15, 15, 15);
    fillTile(chunk, WOOD, 1, 14, 14, 15, 15, 15);
    fillTile(chunk, WOOD, 1, 14, 1, 15, 15, 2);

    //tall beams
    fillTile(chunk, SAND, 1, 2, 1, 15, 3, 2);   fillTile(chunk, WOOD, 1, 3, 1, 15, 4, 2);
    fillTile(chunk, SAND, 1, 2, 14, 15, 3, 15); fillTile(chunk, WOOD, 2, 3, 14, 15, 4, 15);
    fillTile(chunk, SAND, 1, 2, 1, 3, 4, 15);   fillTile(chunk, WOOD, 1, 2, 1, 2, 4, 15);
    fillTile(chunk, SAND, 14, 2, 1, 15, 3, 15); fillTile(chunk, WOOD, 14, 3, 1, 15, 4, 15);

    //pillars
    fillTile(chunk, WOOD, 1, 1, 1, 2, 15, 2);
    fillTile(chunk, WOOD, 14, 1, 1, 15, 15, 2);
    fillTile(chunk, WOOD, 1, 1, 14, 2, 15, 15);
    fillTile(chunk, WOOD, 14, 1, 14, 15, 15, 15);

    //sand pillar
    fillTile(chunk, SAND, 7, 5, 7, 10, 15, 10);

    //wooden floor
    fillTile(chunk, WOOD, 1, 14, 1, 5, 15, 5);
    fillTile(chunk, WATER, 2, 14, 2, 4, 15, 4);

    //friendly missile
    addTile(chunk, MISSILE2, 12, 13, 12);
    addTile(chunk, MISSILE2, 13, 10, 14);

}

void mapTowerUpdates(int *tileUpdates) {
    addUpdate(tileUpdates, 12, 13, 12);
    addUpdate(tileUpdates, 13, 10, 14);
}