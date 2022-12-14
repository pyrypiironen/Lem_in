# Lem_in

## Description

In this project, we will be given a graph in text format, including the locations of the nodes called rooms and the connections, as called links, between them. Our task was to find the most efficient combination of paths through the graph from starting node to the ending node with different numbers of ants moving on the graph. In the other words our goal was to find the quickest way to get `n` ants across the farm. This project made us learn graph theory, algorithm design, and implementing efficient solutions in code.
### Game rules
- At the beginning of the game, all the ants are in the room `##start`.
- The goal is to bring them to the room `##end` with as few turns as possible.
- Each room can only contain one ant at a time. 
  - Except `##start` and `##end` which can contain as many ants as necessary.
- At each turn you will only display the ants that moved.
- At each turn you can move each ant only once and through a tube.
  - The room at the receiving end must be empty.
- Your algorithm must render within a reasonable time, even in a case with 4000 rooms.
  - 2 or 3 seconds is great, 9 seconds is mediocre, 15 seconds is too much.
- You must display your result on the standard output in the following  format:

<img width="432" alt="Screen Shot 2023-01-03 at 2 51 49 PM" src="https://user-images.githubusercontent.com/93189576/210361572-fc5003cb-6070-4119-ac1f-3288280d905d.png">

*`x`, `z`, `r` represents the ants' numbers (from 1 to number of ants) and `y`, `w` and `o` represent the rooms’ names.*

Example 1: 

<img width="326" alt="Screen Shot 2023-01-03 at 2 56 00 PM" src="https://user-images.githubusercontent.com/93189576/210361601-13630c7e-ab79-42e9-b116-a1f7eb451af7.png">

Example 2:

<img width="288" alt="Screen Shot 2023-01-03 at 3 01 20 PM" src="https://user-images.githubusercontent.com/93189576/210362172-bda51b2e-b4b7-4696-8f2c-de63496c2ddf.png">

*When there is a pipe from `##start` to `##end`, all ants can move on same turn.*

## Usage

Run `make` to compile program.

### Lem-in

`./lem-in < <map.textfile>`

Requirements of text file:
- The rooms are defined by: `name` `coord_x` `coord_y`.
  - Room name can't start with the character `L`.
- The links are defined by: `name1-name2`.
- Lines that start with `##` are commands modifying the properties of the line that comes right after.
  - For example, `##start` signals the ant farm’s entrance and `##end` its exit.
  - Any unknown command will be ignored.
- Lines that start with `#` are notes and will be ignored.
- If there isn't enough data to process normally you must display `ERROR`.
- `ERROR` will be also display, if the input isn't clean.

Example of valid input:

<img width="612" alt="Screen Shot 2023-01-03 at 3 40 04 PM" src="https://user-images.githubusercontent.com/93189576/210368438-67eeb36b-d9ab-4c0c-9f5c-ea343b0440dd.png">

<details>
<summary>Example of valid input executed on command line. Click to open.</summary>
	<p>
<img width="489" src="https://user-images.githubusercontent.com/93189576/210369527-717ea0cb-f6b3-4839-bef7-a8fbb2dc9485.png" alt="1">
	</p>
</details>




## The algorithm

To solve this problem, we wrote two different algorithms, which we run in parallel for each input file and then choose the better solution. 

The first algorithm uses recursion to find all possible paths with a certain step count from start to end (with some optimisations). We start from the shortest distance and keep adding longer and longer paths until a solution is found. This approach works very well and is very accurate for most map types but falls short on some of the more complex and "weblike" maps. On these map types, the exhaustive nature of the algorithm causes it to be too slow, which is where the second algorithm comes in.

The second algorithm is our implementation of the algorithm presented by Matthew Daws in his blog [here](https://matthewdaws.github.io/blog/2015-06-08-Paths.html) and [here](https://matthewdaws.github.io/blog/2015-06-15-Paths-Implementation.html). It uses some very clever ideas to modify the "flow" between rooms after each run, which makes it incredibly fast and ideal for the complex maps where our first algorithm fails to deliver.

Below is a more detailed explanation of both of these algorithms.

### The recursive algorithm

The idea behind the recursive algorithm is to search for paths from start to end one "layer" at a time (meaning first adding the 3-step paths for example, then the 4-step paths etc.). Between each search we should check if a solution has been found and break the loop if it has. In this case, solution is considered to be found when there exists a combination of as many _unique_ paths through the map as there are pipes from start or to end (smaller of the two). This is because that is the highest number of paths we are able to use simultaneously. If this many unique paths don't exist, we use the highest number that can be found. The fact that we add paths in ascending order of length ensures that the first such solution we find will be close to optimal. 

There are cases where the solution that uses the highest number of routes is not the best solution. For example, this often happens when the number of ants is small and that solution does not include the shortest route. Because of this, we calculate and keep track of the move counts needed for each combination of unique paths we find. This makes it easy for us to choose which combination to use at the end.

In the example map below, there are two pipes leading to end which means we keep searching until we find a combination of two unique paths leading to end (marked in red). The best combination of _one_ unique path is obviously always the shortest path (marked in green). Which path combination is better in this map will depend on the number of ants.

<img width="566" alt="Näyttökuva 2023-1-10 kello 18 49 28" src="https://user-images.githubusercontent.com/39819007/211612683-96e1eb57-191f-4714-b6b6-c16eb7745d70.png">

### The flow algorithm

The flow algorithm collects the paths using a combination breadth-first search (bfs) and updating the "flow" between rooms (this can also be thought of as arrows between rooms). Bfs is called in a loop until it is no longer possible to add paths. This happens when the flow has blocked all paths from start to end. After each round of bfs, the map is backtracked against the flow and all new paths are saved. Any arrows that are not part of some path at this point are cleared before the next round of bfs.

The rules for the flow are as follows:
- Each room can be visited only once per round of bfs (max six times in total)
- If a room **is not** part of an already saved path
	- We will always go there
- If a room **is** part of an already saved path
	- We are not allowed to move forward _with_ the flow of this path
	- We must move _against_ the flow of this path
	- When we move against the flow of the path, the link between these rooms gets cut for the purposes of the backtracking

After this step is complete and no more paths can be added, we use the same algorithm from before for finding the best combination of paths for our ants to use.



## Flags
