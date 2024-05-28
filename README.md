# entropy
A grid-based simulation written in C.

The goals of this program:
- Define areas of memory as 1d, 2d, or 3d chunks.
- Define "tiles" that can take up a byte of memory, or cell in a grid.
- Define a ruleset for each tile, how it affects the other tiles and itself.
- Optimized tile updating, handling only around where changes occur.



Variable Naming Standards:

- index       : A location within an array.
- tile        : An integer stored at an index that represents an ELEMENT*.
- update      : An integer stored at an index that indicates whether the
                RULE* of the tile at the same index should be called.
- TILES       : An array of tiles.
- UPDATES     : An array of updates.
- CHUNK       : An ADT containing a TILES array & an UPDATES array.
- TICK        : A "frame" of a CHUNK. 
- nextTiles   : An array of tiles that will overwrite TILES upon the next
                tick. Contains tiles equaling -1 that prevent overwriting
                the tile in that index.
- nextUpdates : An array of updates that will overwrite UPDATES upon the
                next tick.


*ELEMENT is not yet integrated into this program.
*RULE is not yet standardized naming in this program.