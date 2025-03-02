# DSA - HW2
My homework for Data Structures and Algorithms with Graphs &amp; Trees in C++

# Tasks
----------
Exercice 1
----------


The code implements a solution to a problem of sorting a dictionary consisting of words in lexicographic order. The input is read from a file named "index.in" and the output is written to a file named "index.out".

The program first reads in the words from the input file and builds a directed graph where each letter is represented as a vertex in the graph. Then, edges are added between vertices corresponding to letters that appear in adjacent words in the dictionary, and the resulting graph is topologically sorted to determine the order in which the letters should appear in the sorted dictionary.

The program uses a stack to keep track of the order in which the letters should appear, and the topological sort algorithm is implemented using depth-first search (DFS) with backtracking to add letters to the stack in the correct order. Finally, the letters are popped off the stack and written to the output file to produce the sorted dictionary.


----------
Exercice 2
----------

This C++ program implements a Quadtree data structure and provides several functionalities such as creating a Quadtree, merging two Quadtree structures, calculating the number of black pixels in a given Quadtree, and displaying the final Quadtree structure.

The program starts with the definition of a suitable representation of a Quadtree using a Node struct that holds a level number and a character representing the type of the node. The Node struct also holds four pointers to its child nodes in the quadtree.

The program also defines a function named Tree that transforms a given string of preorder traversal into a Quadtree representation. The unify function takes two Quadtree structures and returns a merged Quadtree structure based on the given algorithm. The blackPixels function takes a Quadtree and returns the number of black pixels in the given Quadtree.

The program also includes functions to display the final Quadtree structure, which can be displayed in two ways. The first one is a linear display that prints the Quadtree nodes in a single line. The second one is a level-by-level display that prints the Quadtree nodes in a hierarchical structure.

Lastly, the program provides an interactive menu that allows the user to test various functionalities such as adding preorder strings, displaying Quadtree structures, merging Quadtree structures, calculating black pixels, and exiting the program.
