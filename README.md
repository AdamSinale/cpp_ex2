ID: 322453689
MAIL: adam.sinale@gmail.com


# Graph Algorithms Explanations

This project includes a  `Graph` class and it's common algorithms. It is implemented in C++ and supports both directed and undirected graphs, negative and positive edges, weighted or not.

## Graph Class:

implements the fuctions needed to implement comfortably the Algorithms functions.
The Graph is represented as a matrix and given in each Algorithm function.

Will receive a matrix (vector of vectors) of the type int, as well as a bit representing whether the graph is directed or not(1 for yes, 0 for no).
Sending a matrix with different weights on each side of an edge will return an Error.

## basic operators:

**cout << Graph :**

Will print to the stream the values of the matrix the following way:

\[V11, V12, ..., V1n\]

\[V21, V22, ..., V2n\]

\         ...        ]

\[Vn1, Vn2, ..., Vnn\]


**Graph + Graph :**

Will allow only graphs of the same type(directed or undirected).
Creates a new Graph adding each one cell's value to its parallel cell in the other graph and inserts the summed value to the new graph.

**Graph++:**

Creates a new Graph adding to each cell's value 1.

**++Graph :**

Adds to each cell of the existing Graph 1.

**Graph += Graph :**

Will allow only graphs of the same type(directed or undirected). 
Adds to each cell of the first Graph the value to its parallel cell in the other graph.

**Graph+ :**

Will return the graph unchanged

**Graph - Graph :**

Will allow only graphs of the same type(directed or undirected).
Creates a new Graph removing from each of the first Graph's cell value the parallel cell value in the other graph and inserts the value to the new graph.

**Graph -= Graph :**

Will allow only graphs of the same type(directed or undirected). 
Removes from each cell of the first Graph the value of its parallel cell in the other graph.

**Graph-- :**

Creates a new Graph removing from each cell's value 1.

**--Graph :**

Removes from each cell of the existing Graph 1.

**-Graph :**

Will return the graph after turing each positive value to its negative counterpart and the opposite( multiplying each value by -1).

**Graph * int  /  int * Graph :**

Creates a new Graph with the values of the given one multiplying each of its cells' values by the int

**Graph \*= int :**

Multiplies each of the cells' values in the existing Graph by the int

**Graph * Graph :**

Won't allow Graphs of different sizes.
Basic Graphs multipication, multiplying the i-th value of each row bythe i-th value of each column and adding them. Repeat this for all column and row combination.

**Graph \ int :**

Creates a new Graph with the values of the given one deviding each of its cells' values by the int

**Graph \= int :**

Devides each of the cells' values in the existing Graph by the int


**Constructor: Graph():**

Initializes a new instance of the Graph class.

**loadGraph(matrix):**

loads the given matrix to the graph object.

**getEdge(i, j):**

Returns the edge between i and j.

**getNumV():**

Returns the number of vertices.

**isDirected():**

Returns 1 if the graph is considered directed and 0 if not.

**check_borders(s,f):**

Checks wether the given verices exist in the graph.

**printGraph():**

Prints the graph's info- num of vertices and edges.

## Algorithms Library


**isConnected(Graph graph)**:

checks whether a graph is connected by going over all the vertices and contucting bfs search from each of them checking if one of them doesnt reach another.

**isBipartite(Graph &graph)**:

checks whether we can split the graph into 2 groups with no edges between a single group's vertices. Does that by going through every SCC and doing bfs, if the current vertex is of groups A, its neibors of group B and when it is already A we return false.

**shortestPath(Graph graph, start, finish)**:

Finds the shortest path using bellman ford algorithm, going n-1 times and when we do for the nth time, if there is a cycle we check if it's a part of the path and if so return "-1", else we return the path.

**isContainsCycle(Graph &graph)**:

We run a dfs algorithm from each vertex that will return the paths from him to everyone. the moment one of them returns a path where a vector's parent is the starting vertex(and when undirected not his direct son) it means we have a cycle and return true.

**negativeCycle(Graph graph)**:

We run bellman for n times. on the nth time when there is a changed distance and its not a direct son in a undirected graph we go through the changed vertex until we visit him again, if we never do- there is another negative sub-cycle and we will return him.
