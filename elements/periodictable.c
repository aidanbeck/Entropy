#include "../elements.h"
#include "periodictable.h"

Element ELEMENTS[DICTIONARY_LENGTH];

void compileElements() {

    /*
        Add each custom Element to the ELEMENTS array.
        ELEMENTS[DICTIONARY_NAME] = ElementVariable;
    */
   ELEMENTS[AIR]    = eAIR;
   ELEMENTS[STONE]  = eSTONE;
   ELEMENTS[WOOD]   = eWOOD;
   ELEMENTS[FIRE]   = eFIRE;
   ELEMENTS[FIRE2]  = eFIRE2;
   ELEMENTS[PACKAGE]= ePACKAGE;

    ELEMENTS[SPAWNER] = eSPAWNER;
    ELEMENTS[SPAWN_RANDOM] = eSPAWN_RANDOM;
}