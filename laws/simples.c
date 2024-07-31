#include "lawTable.h"

void nothing(int index, Chunk *CHUNK) {
    printf("nothing");
}
Law L_NOTHING = {.func=nothing};

void push(int index, Chunk *CHUNK) {

    int distance = CHUNK->input[0];
    int x = CHUNK->input[1];
    int y = CHUNK->input[2];

    int target = moveIndex(index, x*distance, y*distance, 0);
    

    int returnIndex;
    int steps = moveIndexTowards(index, target, distance, &returnIndex, CHUNK);

    
    uint8_t tile = CHUNK->TILES[index];
    Element *data = &CHUNK->physics->PeriodicTable[tile];

    //if it doesn't move at all, just run the defaultLaw
    if (steps == 0) {
        data->defaultLaw->func(index, CHUNK);
    }
    //if it does, cook the endOfPush law at the new index.
    else if (data->endOfPush != NULL) {
        data->endOfPush->func(returnIndex, CHUNK);
    }
}
Law L_PUSH = {.func=push};


void afterPush(int index, Chunk *CHUNK) {

    uint8_t tile = CHUNK->TILES[index];
    Element *data = &CHUNK->physics->PeriodicTable[tile];

    if (data->endOfPush != NULL) {
        data->endOfPush->func(index, CHUNK);
    }
}
Law L_AFTERPUSH = {.func=afterPush};