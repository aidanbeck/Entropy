#ifndef ELEMENTS_H
#define ELEMENTS_H

/*
    The Element struct.
    Format for Element data.
*/
typedef struct {
    char icon;
    char name[16];
    void (*rule)(int *TILES, int *nextTiles, int *nextUpdates, int index);
} Element;

#endif