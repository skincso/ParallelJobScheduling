# ParallelJobScheduling

---- About ----

A computational graph is a directed acyclic graph (DAG), where the nodes represent operations and the edges represent
dependencies between these operations. Each path in the graph represents a computation in which the nodes must be 
executed in sequential order. An arbitrary set of nodes can be executed in parallel, if they are not connected directly
with each other. The goal is to identify all the nodes that can be executed in parallel.


---- How to build and run on Linux ----

Clone the project from GitHub.
 $ git clone https://github.com/skincso/ParallelJobScheduling.git

Create build directory
 $ mkdir pjs_build

Generate Makefile in the build directory, and build the project.
 $ cd pjs_build
 $ cmake ..
 $ make

Run the program by navigating to src/ and run ./PJS.
 $ cd src/
 $ ./PJS


---- Input file format ----

The program reads the graph from a text file.
In the first line shall be the nodes's names, separated by semicolon (;).
Nodes' names can be characters, numbers, or other string, but they must be unique.
From the second line, there should be the node where the edges start from, and after a colon (:)
the nodes where the edges go, separated by comma (,).

For example:
A;B;C;D
A:B
B:C,D

Where A, B, C and D are the nodes.
There are edges from A to B, B to C, and B to D.


---- Test inputs ----

You can find other test inputs in the ParallelJobScheduling/src/graphs/ directory.
If you'd like to test the program with other input files, go to src/CMakeLists.txt and change the InputFile variable in line 14.


---- Design choices ----

The graph is represented by adjacency list.
Nodes are stored in a vector, and each node has a vector, where its adjacents' references are.

I used Kahn's algorithm to solve the given problem:

 1. Find nodes with no indegrees.
 2. Store these nodes and delete them from the graph.
 3. Delete the edges originating from the nodes stored in step 2. (Decrement number of indegrees.)
 Repeat steps 1. 2. 3. until no element with zero indegrees can be found.
 Check whether every node is executed.











