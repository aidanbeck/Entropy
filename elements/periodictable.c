#include "../elements.h"
#include "periodictable.h"

Element ELEMENTS[DICTIONARY_LENGTH];

void compileElements() {

    /*
        Add each custom Element to the ELEMENTS array.
        ELEMENTS[DICTIONARY_NAME] = ElementVariable;
    */
   ELEMENTS[SPAWN_RANDOM] = tileSPAWN_RANDOM;
}