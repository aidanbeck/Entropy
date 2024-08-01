This file notes major engine changes I would like to implement in the future.

# Chunking

## Eliminate Quad-Chunk memory in favor of using a global list of updates
- Currently (US/7/9/2024) a chunk contains 4 arrays of bytes. TILES, UPDATES, nextTiles, & nextUpdates. It also includes a hotLaws pointer array.
- A new method could eliminate all but TILES.


### First, lets introduce new "update" ADTs.
### There will be different types, so that no update has memory it doesn't need.

- struct basicUpdate
    - index: byte
    - chunk: byte byte byte

- struct complexUpdate
    - law:   byte (byte?)
    - index: byte
    - chunk: byte byte byte

- struct inputUpdate
    - law: byte
    - input: byte
    - index: byte
    - chunk: byte byte byte

- struct inputUpdate_2
    - law: byte
    - input: byte byte //just carries an extra byte. Can make as many sizes as are needed by blocks.
    - chunk: byte byte byte

- // each struct will also have a "timed" version. It will be the same, but with a single byte keeping track of the "tick"
- // "chunk" will refer to an index inside of an array of the loaded chunks. Three bytes gives us 16,777,215 chunks, enough for 1k players to have 32x32x16. Visible chunks at once can be lowered, or the "chunk" variable can be given an extra byte if it goes above those numbers.


### Each update type will have it's own array ADT. Multiple arrays can be joined as linked lists

- struct complexArray
    - int updatesInArray
    - complexUpdate[100]
    - complexarray *nextArray

- struct complexTimedArray
    - int updatesInArray
    - int firstUpdateIndex
    - int lastUpdateIndex
    - complexTimedUpdate[100] globalUpdates  // different between each array ADT
                                             // 100 is just an example. It could be different for each array type
    - complexTimedArray *nextArray           // for linked list purposes


- Every tick, the updater will cycle through ALL the array types.
- Blocks will write to the world right then and there
- Updates added will get added to the update array. If they are nearing the end of the array, a new array will be created and linked.

- If this sytem causes problems with mid-tick events, "writing" tiles can just be written to their own "writing scheduled array".
- This would be like nextTiles is now. Except, how can you check that a tile WONT be written to the next tick?


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
- I think I already wrote about this above I am so dumb