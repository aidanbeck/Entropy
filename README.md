# entropy
A grid-based simulation written in C.

The goals of this program:
- Define areas of memory as 1d, 2d, or 3d chunks.
- Define "tiles" that can take up a byte of memory, or cell in a grid.
- Define a ruleset for each tile, how it affects the other tiles and itself.
- Optimized tile updating, handling only around where changes occur.
