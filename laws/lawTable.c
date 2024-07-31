#include "../main.h"
#include "../physics.h"
#include "lawTable.h"

void compileLaws(Physics *PHYSICS) {

    Law *L = PHYSICS->LawTable;

    L[NOTHING] = L_NOTHING;
    L[PUSH] = L_PUSH;

}