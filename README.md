# 8TileGame
BFS implementation to solve the 8TileGame, roughly 173ms in worst case on my machine.

At the moment it uses a perfect hashing algorithm to detect already-explored states.
The upsides of this approach are O(1) lookup time and the *guaranteed* absence of collisions.
However, the space complexity is (x*y)!, where x, y = the #s of tiles along the x, y dimensions.

This is prohibitive for any Tile Game implementation beyond a 3 x 3 board. 

To reduce the space complexity to a more manageable O(n) (where n = # explored states), while
maintaining the O(1) lookup time, I will be implementing a hash table at some point in the future.


