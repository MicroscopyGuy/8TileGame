# 8TileGame

## What is this? 
BFS implementation to solve the 8TileGame, outputs tile swaps needed to transform
an arbitrary (configurable) initial tile arrangement, into an equally arbitrary final arrangement.
The tiles are arranged in a 3 x 3 grid, where one of the tiles is missing -- this is the blank tile.
The goal is to reach the final arrangement from the initial arrangement by swapping the blank tile 
with adjacent tiles.
              
## How does Breadth First Search Work to find the fastest solution?
 Breadth first search is a graph (nodes connected by edges) traversal algorithm which searches layer 
by layer. One example is if used to search for oil, it would shave off a layer of earth one at a 
time until the search was fruitful or it couldn't search anymore. It would then know that any oil 
discovered was the closest to the surface within the search area.

#### Other algorithms, for context:
Plenty of other algorithms for this exist, and have varying approaches. Depth first search is more or 
less the opposite, and if used in the same example above, would repeatedly tunnel straight-down until it 
found oil, or couldn't search anymore. This might be faster, but it would not guarantee the shallowest oil.

A* is similar to breadth first search, except it prioritizes where to look next by the addition of 
a heuristic, or hint. 

## How fast is this BFS implementation?
The highest runtime occurs during a run where a solution doesn't exist, which requires searching through roughly
485,000 (non-unique) states and takes roughly 173ms on my machine. This was the avg runtime measured in "TIMING_MODE" after TIMING_MODE_RUNS # of runs, 
in this case 10,000 (both adjusted in constants.h). This puts the avg search rate of non-unique states at around 2,800,000 states per second. 

Note that timing mode suppresses all output beyond the reported runtimes.
              

## How does this code keep track of states it's seen before?
At the moment it uses a perfect hashing algorithm (see explored.c) to detect already-explored states.
The upsides of this approach are O(1) lookup time and the *guaranteed* absence of collisions.
However, the hash algorithm runs in O((xy)^2) time, and the overall space complexity of this operation is O((x*y)!), where x, y = the #s of tiles along the x, y dimensions.

This is prohibitive for any Tile Game implementation beyond 3 x 3 boards.

## Any plans to improve on this, or change it in the future?
At some point in the future I will implement a hash table to reduce the space complexity
to O(n) (where n = # of explored states). 

It would also be fun to experiment with other algorithms such as A*, and perhaps even on boards larger than 3 x 3.  


