#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_set>

using namespace std;

ifstream fin("index.in");
ofstream fout("index.out");


bool newLetter(char letter, unordered_set<char> letters) // This function takes a letter and a set of letters and returns true if the letter is not present in the set
{
    return letters.find(letter) == letters.end();
}

int getCharacterIndex(unordered_set<char> letters, char letter) // this function takes a set of letters and a letter and returns the index of the letter in the set
{
    auto it = letters.find(letter);
    if (it != letters.end())
    {
        return distance(letters.begin(), it);
    }
    return -1; // if the letter is not in the set, it returns -1
}

char getCharacter(unordered_set<char> letters, int index) // this function takes a set of letters and an index and returns the character at that index in the set
{
    auto it = next(letters.begin(), index);
    if (it != letters.end())
    {
        return *it;
    }
    return '\0'; // if the index is out of range, it returns null character '\0'
}

stack<char> result; //creates a stack of characters named "result". This stack will be used to store the topological order of the graph

class Graph
{
public:
    int V; //declares an integer variable V which represents the number of vertices in the graph
    vector<vector<int>> adj; //declares a 2D vector named "adj" which will store the adjacency matrix of the graph
    Graph(int V)
    {
        this->V = V;
        adj.resize(V, vector<int>(V, 0));
    }
    void addEdge(int u, int v) //method to add an edge between vertex u and vertex v in the graph by setting the corresponding element in the adjacency matrix to 1
    {
        adj[u][v] = 1;
    }
    void removeEdge(int u, int v) //method to remove an edge between vertex u and vertex v in the graph by setting the corresponding element in the adjacency matrix to 0
    {
        adj[u][v] = 0;
    }
    void printGraph(unordered_set<char> letters)
    //method to print the graph, where each vertex is represented by a character from the unordered set "letters"
    //the adjacency matrix is printed as a list of vertices adjacent to each vertex
    {
        for (int i = 0; i < V; i++)
        {
            fout << getCharacter(letters, i) << ": "; //write the character that corresponds to the current vertex i to the output file, followed by a colon
            for (int j = 0; j < V; j++)
            {
                if (adj[i][j] == 1)
                {
                    fout << getCharacter(letters, j) << " "; //if there is an edge, write the character that corresponds to vertex j to the output file, followed by a space
                }
            }
            fout << endl;
        }
    }
    void topologicalSort(int v, vector<bool>& visited, unordered_set<char> letters) // this is a recursive function that performs a depth-first search traversal of the graph, starting from vertex v
    {
        visited[v] = true;
        for (int i = 0; i < V; i++)
        {
            if (adj[v][i] == 1 && !visited[i])
            {
                topologicalSort(i, visited, letters); // this function then calls itself recursively on any unvisited vertices that are adjacent to the current vertex v
            }
        }
        result.push(getCharacter(letters, v)); //finally, the character corresponding to the current vertex v is pushed onto the stack result
    }
};

int main()
{
    unordered_set<char> letters; // declare an unordered set to store unique letters in the words and a vector to store the words
    vector<string> words;
    string word; // declare a string to read input from file
    fin >> word;
    while (word != ".") // read words from input file until a '.' is reached
    {
        words.push_back(word);

        for(int i = 0; i < letters.size(); i++)
        {
            if(newLetter(word[i], letters))     // if the character is new, add it to the unordered set
            {
                letters.insert(word[i]);
            }
        }
        fin >> word;
    }

    Graph alphabet(letters.size()); // create a graph with the size of the letters set

    for (int i = 0; i < words.size() - 1; i++)
    {
        string word = words[i];
        string nextWord = words[i + 1];
        int k = 0; // find the first different character in the two words
        while (word[k] == nextWord[k])
        {
            k++;
        }
        // get the indexes of the characters in the letters set and add an edge to the graph
        int u = getCharacterIndex(letters, word[k]);
        int v = getCharacterIndex(letters, nextWord[k]);
        alphabet.addEdge(u, v);
    }

    vector<bool> visited(letters.size(), false);     // declare a vector to store visited nodes and perform topological sort
    alphabet.topologicalSort(0, visited, letters);

    while (!result.empty()) // print the result in reverse order
    {
        fout << result.top();
        result.pop();
    }
    return 0;
}
