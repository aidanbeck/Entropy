#ifndef PERIODICTABLE_H
#define PERIODICTABLE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>

#include "../main.h"
#include "../elements.h"

/*
    Dictionary of Element "enums".
    Useful for easily referring to an element type in code.
*/
enum Dictionary {
    AIR,
    STONE,
    WOOD,
    FIRE,
    FIRE2,

    CENTIHEAD_N, //centipede parts
    CENTIHEAD_S,
    CENTIHEAD_E,
    CENTIHEAD_W,
    CENTIHEAD_NE,
    CENTIHEAD_NW,
    CENTIHEAD_SE,
    CENTIHEAD_SW,

    CENTIBODY_N,
    CENTIBODY_S,
    CENTIBODY_E,
    CENTIBODY_W,
    CENTIBODY_NE,
    CENTIBODY_NW,
    CENTIBODY_SE,
    CENTIBODY_SW,

    CENTITAIL_N,
    CENTITAIL_S,
    CENTITAIL_E,
    CENTITAIL_W,
    CENTITAIL_NE,
    CENTITAIL_NW,
    CENTITAIL_SE,
    CENTITAIL_SW,

    BALL,
    RAT,
    SPAWN_RANDOM,

    DICTIONARY_LENGTH
};

/*
    List of Element "externs".
    Allows files that link elements/periodictable.h to access element data. (or can they access it without?)
*/
extern Element tileSPAWN_RANDOM;
extern Element tileWATER;


/*
    Compiles ELEMENTS list.
    These are down here so that DICTIONARY_LENGTH can be defined.
*/
extern Element ELEMENTS[DICTIONARY_LENGTH];
void compileElements();

#endif