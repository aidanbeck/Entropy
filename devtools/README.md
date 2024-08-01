## How To COMPILE with GCC
- set COMPILE_MODE in main.h to 0
- gcc *.c elements/*.c laws/*.c devtools/*.c barista/*.c -o main.exe -Wall -Wpedantic -Werror
- ./main.exe

## How To COMPILE with EMCC
- set COMPILE_MODE in main.h to 1
- emcc -o ../deadletter/barista/latte.html *.c elements/*.c laws/*.c devtools/map.c barista/barista.c -O1 --shell-file ../barista/html_template/latte.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_main', '_tickFromJS', '_placeFromJS']"
- Navigate to folder with compiled wasm and html
- Start an http server by running: python3 -m http.server
- Go to url: localhost:8000


## How To Add A LAW

1. Create a function inside a .c file within the "laws" directory. #include "lawTable.h"
- void explode(int index, Chunk *CHUNK) {}

2. In the same file, create a "Law" variable that references the function
- Law L_EXPLODE = {.func=explode};

3. In lawTable.h, add the name of the law to the "L_Dictionary enum", and the law variable to the "Extern List"
- EXPLODE,
- extern Law L_EXPLODE

4. In lawTable.c, add your law element to the compileLaws function.
- L[EXPLODE] = L_EXPLODE;


## How To Add An ELEMENT (With a common defaultLaw)

1. Make sure that your .c file #include's "periodicTable.h", as well as "../laws/lawTable.h" to access the common law.

2. Create an "Element" variable that contains a pointer to your law as well as an icon
- Element E_CREEPER = { .defaultLaw = &L_EXPLODE, .icon = '&'};

3. In periodicTable.h, add the name of the element to the "E_Dictionary enum", and the element variable to the "Extern List"
- CREEPER,
- extern Element E_CREEPER

4. In lawTable.c, add your law element to the compileLaws function.
- E[CREEPER] = E_CREEPER;


## How To Add An ELEMENT (With a custom defaultLaw)

1. Create a function inside a .c file within the "elements" directory. #include "periodicTable.h"
- void eatApples(int index, Chunk *CHUNK) {}

2. In the same file, create a "Law" variable that references the function
- Law l_EATAPPLES = {.func=eatApples};   // I use lowercase "l" to designate that it is not a common law

3. Create an "Element" variable that contains a pointer to your "Law" variable as well as an icon
- Element E_ANT = { .defaultLaw = &l_EATAPPLES, .icon = ':'};

4. In periodicTable.h, add the name of the element to the "E_Dictionary enum", and the element variable to the "Extern List"
- ANT,
- extern Element E_ANT

5. In lawTable.c, add your law element to the compileLaws function.
- E[ANT] = E_ANT;


## Areas Of Improvement:
- getMeshIndexes and viewFaces, and making two arrays and manually comparing them, this could be simplified
- Meshes could be in a more standardized location
- the "endOfPush" stuff needs standardizing
- the moveIndexTowards function is likely a mess

## Hotlaw system was a mistake
- The entire howlaw system is likely a mistake. Or rather, the entire way updates in general are stored is wrong.
- Potentially, even the way "nextTiles" being a thing is wrong.
- Instead, I should have a single array of "updates" independent of chunks.
- Likely only needs to be 100 or so long. Each update contains it's chunk id as well as it's index within that chunk
- When it gets to over 100, another 100 is made. It's like a linked list with each link having 100 slots
- it also can contain when it's supposed to "fire" so it can delay a couple ticks.
- The ticker goes through the list, and moves each update not yet firing forwards
- this saves memory and possible CPU by a lot given that most tiles do not update every tick
- I have a better explanation of this in my notebook
- HotLaws are also possibly less needed, as each "update" can store a few variables without it being as big of a deal
- In fact, there can be different update lists for each variable combonation
- The question: Do I fix this now or later? 


## Next Build TODO List
- Make "zombies"
    ✔️ They path towards the player 
    ✔️ Player loses tires when pushed
    ✔️ They die to fire
    ✔️ They die to getting pushed

- Make "Tire"
    - distrubutes intendedSteps instead of steps when pushed?? OR steps + intendedSteps (optional)

- Client Side:
    - Let the player spend Gas to increase gas (+25)
    - Let the player spend tire to increase tires (+1)
    - Let the player use moveTruck() when moving the truck, instead of the normal place command
    - Alert game over (accessible by barista)
    - If the player has no tires, and they are adjacent, trigger a "game over" function (access client from barista) (also needs C function)
