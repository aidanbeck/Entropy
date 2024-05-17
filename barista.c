//COMPILE WITH emcc -o ../compiled/latte.html barista.c -O3 --shell-file ../html_template/latte.html -s NO_EXIT_RUNTIME=1 -s "EXPORTED_RUNTIME_METHODS=['ccall']"
//COMPILE WITH emcc -o ../compiled/latte.html barista.c -O3 --shell-file ../html_template/latte.html -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_multiplier']"

#include <stdio.h>
#include <emscripten/emscripten.h>
#include "main.h"

extern EMSCRIPTEN_KEEPALIVE int multiplier(int x, int y) {
    int result = x*y;
    return result;
}
