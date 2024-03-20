#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <math.h>
#include "breadthFirstSearch.h"
#include "constants.h"

int main(int argc, char* argv[])
{ 
    clock_t begin, end;
    if (!TIMING_MODE){
      
      begin = clock();   
      breadthFirstSearch();
      end = clock();

      printf("BFS took %f milliseconds\n", ((double) (end - begin)/CLOCKS_PER_SEC) * 1000);
    }

    else{
      begin = clock();
      runNTimes(TIMING_MODE_RUNS);
      end = clock();
      printf("BFS took %f milliseconds\n", ((double) (end - begin)/CLOCKS_PER_SEC) * 1000);
    }

    //runNTimes(1000); // uncomment and run to yield accurate avg runtime
  
  
  return 0;   
}


/* Rough structure:

function search(initialState, goalStates)
{
    fringe = [new node from initialState]
    explored=[]
    while (fringe not empty)
        node = fringe.remove()
        if node.state not in explored
            if node.state in goalStates report SUCCESS
            fringe += node.successors()
            explored +=node.state
    report FAILURE
}
*/



