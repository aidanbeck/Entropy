//COMPILE WITH emcc -o ../compiled/latte.html barista.c -O3 --shell-file ../html_template/latte.html -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']"
//COMPILE WITH emcc -o ../compiled/latte.html barista.c -O0 --shell-file ../html_template/latte.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_multiplier']"

#include <stdio.h>
#include <emscripten/emscripten.h>
#include "main.h"

void jsWriteIcon(int index, int tile) {
    EM_ASM({
        Module.writeIcon($0, $1);
    }, index, tile);
}