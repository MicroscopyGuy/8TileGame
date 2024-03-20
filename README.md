# 8TileGame
**What this is**: BFS implementation to solve the 8TileGame, outputs tile swaps needed to transform
              an arbitrary (configurable) initial tile arrangement, into an equally arbitrary final arrangement.
              The tiles are arranged in a 3 x 3 grid, where one of the tiles is missing -- this is the blank tile.
              The goal is to reach the final arrangement from the initial arrangement by swapping the blank tile 
              with adjacent tiles.

**How fast is it**: The highest runtime occurs during a run where a solution doesn't exist, and this takes about 
                173ms. This was the average time measured in "TIMING_MODE" (toggled in constants.h) after 10,000 
                runs. The number of runs (TIMING_MODE_RUNS) can be configured in constants.h. Note that enabling 
                timing mode will run the code TIMING_MODE_RUNS number of times, and will suppress all output 
                beyond the reported runtimes.


**How does it keep track of states it's seen before?**
At the moment it uses a perfect hashing algorithm (see explored.c) to detect already-explored states.
The upsides of this approach are O(1) lookup time and the *guaranteed* absence of collisions.
However, the space complexity is O((x*y)!), where x, y = the #s of tiles along the x, y dimensions.

This is prohibitive for any Tile Game implementations beyond 3 x 3 boards -- which I would like to explore in the future.

**Any plans to improve on this, or change it in the future?**
At some point in the future I will implement a hash table to reduce the space complexity
to O(n) (where n = # of explored states). 

It would also be fun to experiment with other algorithms such as A*, and perhaps even on boards larger than 3 x 3.  
