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

## Flags
