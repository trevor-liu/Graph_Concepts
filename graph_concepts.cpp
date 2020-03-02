//---------------------------------------------------------------------------------
// Name: Trevor Liu
// ID #: 1589202
// CMPUT 275 Winter2020
// 

#include <iostream>
#include <queue>
#include <fstream>
#include "digraph.h"
using namespace std;

/*
    Description: Using breadthFirstSearch to find all possibel path
    Arguments:
        graph (Digraph &): pass by reference of a graph
        startVertex (int): Which vertex should we start with
    Returns:
        searchTree (unordered_map): vertexes that travelled through
*/
unordered_map<int, int> breadthFirstSearch(const Digraph &graph, int startVertex)
{
    unordered_map<int, int> searchTree; // map each vertex to its predecessor

    searchTree[startVertex] = -1;

    queue<int> q;
    q.push(startVertex);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (auto iter = graph.neighbours(v); iter != graph.endIterator(v); iter++)
        {
            if (searchTree.find(*iter) == searchTree.end())
            {
                searchTree[*iter] = v;
                q.push(*iter);
            }
        }
    }

    return searchTree;
}

/*
    Description: Count how many connected components is in the graph.
    Arguments:
        g (Digraph*): A pointers to an instances of Digraph
    Returns:
        count (int): number of connected components
*/
int count_components(Digraph *g)
{
    // initiate a count and the size of the graph
    int count = 0;
    vector<int> vec1 = g->vertices();

    // create a dynamic array to keep track of visited vertex
    unordered_set<int> visitedset;

    // To store the return from the breadthfirstsearch
    unordered_map<int, int> searchTree;

    // iterate thorugh the vec1 from the graph
    for (auto i : vec1)
    {
        // if the vertex have not visit yet, use breadthfirstsearch
        // to find paths
        if (visitedset.find(i) == visitedset.end())
        {
            count++;
            visitedset.insert(i);
            searchTree = breadthFirstSearch(*g, i);
        }

        // store the visited vertex back in to visitedset
        for (auto &j : searchTree)
        {
            if (visitedset.find(j.first) == visitedset.end())
            {
                visitedset.insert(j.first);
            }
            else if (visitedset.find(j.second) == visitedset.end())
            {
                visitedset.insert(j.second);
            }
        }
    }
    return count;
}

/*
    Description: Read from a file and make a graph.
    Arguments:
        filename[] (char): A character array for filename to read from
    Returns:
        graph (Digraph*): return a pointer to the graph generated
*/
Digraph *read_city_graph_undirected(char filename[])
{
    static Digraph graph;
    ifstream file;

    file.open(filename);
    if (!file.is_open())
    {
        cout << "error when opening file" << endl;
    }
    else
    {
        string line;
        while (file.good())
        {
            getline(file, line);

            // The input for vertices
            if (line[0] == 'V')
            {
                // find the index when the vectex end
                int endofvert = line.find(',', 2);
                graph.addVertex(stoi(line.substr(2, endofvert)));
            }
            // The Edges of the graph
            else if (line[0] == 'E')
            {
                // find the index of the left and right edges
                int endoffirstedge = line.find(',', 2);
                int endofsecondedge = line.find(',', endoffirstedge + 1);
                int firstedge = stoi(line.substr(2, endoffirstedge));
                int secondedge = stoi(line.substr(endoffirstedge + 1, endofsecondedge));

                // adding the edges to the undigraph
                graph.addEdge(firstedge, secondedge);
                graph.addEdge(secondedge, firstedge);
            }
            // Neither
            else
            {
                cout << "error" << endl;
            }
        }
    }
    return &graph;
}
int main(int argc, char *argv[])
{
    // Part 1
    Digraph graph;
    int nodes[] = {1, 2, 3, 4, 5, 6};
    for (auto v : nodes)
        graph.addVertex(v);
    int edges[][2] = {{1, 2}, {3, 4}, {3, 5}, {4, 5}};
    for (auto e : edges)
    {
        graph.addEdge(e[0], e[1]);
        graph.addEdge(e[1], e[0]);
    }

    // printing the result out before and after adding the new edges.
    cout << count_components(&graph) << endl;
    graph.addEdge(1, 4);
    graph.addEdge(4, 1);
    cout << count_components(&graph) << endl;

    // part 2
    // read from the file and create a tree
    char filename[] = "edmonton-roads-2.0.1.txt";
    Digraph *ptr_graph = read_city_graph_undirected(filename);

    // count the connected components in edmonton map
    int n = count_components(&(*ptr_graph));
    cout << n << endl;

    return 0;
}
