# 8TileGame
BFS implementation to solve the 8TileGame, roughly 173ms in worst case on my machine.

At the moment it uses a perfect hashing algorithm to detect already-explored states.
The upsides of this approach are O(1) lookup time and the *guaranteed* absence of collisions.
However, the space complexity is O((x*y)!), where x, y = the #s of tiles along the x, y dimensions.

This is prohibitive for any Tile Game implementation beyond a 3 x 3 board. 

At some point in the future I will implement a hash table to reduce the space complexity
to O(n) (where n = # of explored states).

It would also be fun to experiment with other algorithms such as A*, and perhaps even on boards larger than 3 x 3.  
