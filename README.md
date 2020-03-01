# A*search in CPP

![Screen Shot 2020-02-27 at 21 57 26](https://user-images.githubusercontent.com/16607351/75455832-2274ea80-59bd-11ea-85ef-6d3ffbe7abec.png)

## A*search Overview
Finds a path from the start node to the goal node by checking for open neighbors of the current node, computing a heuristic for each of the neighbors, and adding those neighbors to the list of open nodes to explore next. 
The next node to explore is the one with the lowest total cost + heuristic (g + h). 
This process is repeated until the end is found, as long as there are still open nodes to explore.

## Future feature
Route Planning
