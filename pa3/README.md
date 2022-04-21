# PA2 - DFS and directed graphs
This assignment uses a similar graph ADT to pa2, but it creates a directed graph and uses the DFS algorithm to identify strongly connected components of a graph.

## Files
List.c - contains the List ADT used as a stack for DFS and finding components, as well as the adjacency list for the Graph ADT<br>
List.h - header file that contains the function declarations for the List ADT<br>
Graph.c - contains the Graph ADT that can create the directed graphs and perform the DFS algorithm<br>
Graph.h - header file that contains the function declarations for the Graph ADT <br>
GraphTest.c - client for the Graph.c and it tests the functionality of each function in Graph.c<br>
FindComponents.c - takes an infile and creates a directed graph from it, and prints the adjacency list and strongly connected components to an outfile<br>
Makefile - creates executables and object files, as well as cleans up created binary files and object files

## Comments
I added a test file that is the same as the input file on the example pdf as my client tester instead of including the test that was originally on the Makefile.
