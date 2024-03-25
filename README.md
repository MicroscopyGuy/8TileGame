# 8TileGame

## What is this? 

The 8 Tile Game (or 8 Puzzle) is a game which features 8 tiles on a 3 x 3 grid. The player must repeatedly swap 
the blank tile with an adacent tile to transform some initial arrangement into a different final arrangement.
This code is a BFS (Breadth First Search) implementation which outputs the fewest swaps needed to complete the game, or
reports that no solution was possible between the selected initial and final configurations.

To visualize and play this game yourself, you can visit: https://sliding.toys/mystic-square/8-puzzle/. Note that 
I have no affiliation with this site. 

## How does Breadth First Search work to find the fastest solution?
BFS is a graph (nodes connected by edges) traversal algorithm which searches layer 
by layer. One example is if used to search for oil, it would shave off a layer of earth one at a 
time until the search was fruitful or it couldn't search anymore. It would then know that any oil 
discovered was the closest to the surface within the search area.

#### Other algorithms, for context:
Plenty of other algorithms for this exist, and have varying approaches. DFS (Depth First Search) is more or 
less the opposite, and if used in the same example above, would repeatedly tunnel straight-down until it 
found oil, or couldn't search anymore. This might be faster, but it would not guarantee the shallowest oil.

A*(pronounced Ay-Star) is similar to BFS, except it prioritizes where to look next by the addition of 
a heuristic, or hint. 

## How fast is this BFS implementation?
The longest runtime occurs during a run where a solution doesn't exist, which requires searching through roughly
485,000 (non-unique) states and takes roughly 173ms on my machine. This was the avg runtime measured in "TIMING_MODE" after TIMING_MODE_RUNS # of runs, 
in this case 10,000 (both adjusted in constants.h). This puts the avg search rate of non-unique states at around 2,800,000 states per second. 

Note that timing mode suppresses all output beyond the reported runtimes.
              
## How does this code keep track of states it's seen before?
At the moment it uses a perfect hashing algorithm (see explored.c) to detect already-explored states.
The upsides of this approach are O(1) lookup time and the *guaranteed* absence of collisions.
However, the hash algorithm runs in O((xy)^2) time, and the overall space complexity of this operation is O((x*y)!), where x, y = the #s of tiles along the x, y dimensions.

This is prohibitive for any Tile Game implementation beyond 3 x 3 boards.

## How can I use this code?
This was developed using the GCC compiler, and is what I recommend for compilation.
To simply run the code, ensure that TIMING_MODE is toggled to 0 in constants.h.
You can select different initial and final arrangements by changing them manually in constants.c.

Once you have an arrangement of tiles you would like to solve, simply compile this code with gcc and then run it!


## Any plans to improve on this, or change it in the future?
At some point in the future I will implement a hash table to reduce the space complexity
to O(n) (where n = # of explored states). 

It would also be fun to experiment with other algorithms such as A*, and perhaps even on boards larger than 3 x 3.  


