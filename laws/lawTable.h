#ifndef LAWTABLE_H
#define LAWTABLE_H

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <unistd.h>

#include "../main.h"
#include "../physics.h"
#include <stdio.h>

// This does not include unique defaultLaws
enum L_Dictionary {
    NOTHING,
    DEFAULT,

    PUSH,

    LAW_COUNT
};

// Extern List
extern Law L_NOTHING;
extern Law L_PUSH;

void compileLaws(Physics *PHYSICS);
#endif