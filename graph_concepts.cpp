// A template for the Graph Concepts Exercise in C++.

#include <iostream>
#include <queue>
#include <string>
#include <fstream>
#include "digraph.h"
using namespace std;

// this is the breadthfirstsearch developed in class
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

// count how many connected graphs
int count_components(Digraph *g)
{
    // initiate a count and the size of the graph
    int count = 0;
    vector<int> vec1 = g->vertices();

    // create a dynamic array to keep track of visited vertex
    unordered_set<int> visitedset;
    unordered_map<int, int> searchTree;

    for (auto i : vec1) {
        if (visitedset.find(i) == visitedset.end())
        {
            count++;
            visitedset.insert(i);
            searchTree = breadthFirstSearch(*g, i);
        } 
        for (auto& j: searchTree)
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

Digraph* read_city_graph_undirected(char filename[])
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


    // part 2;
    char filename[] = "edmonton-roads-2.0.1.txt";
    Digraph* ptr_graph = read_city_graph_undirected(filename);
    int n = count_components(&(*ptr_graph));
    cout << n << endl;

    return 0;
}







// void depthfirstsearch(int u, int prev, const Digraph& g)
// {
//     if (searchTree.find(u) == searchTree.end())
//     {
//         return;
//     }
//     searchTree[u] = prev;
//     for (auto iter = g.neighbours(u); iter != g.endIterator(u); iter++)
//     {
//         depthfirstsearch(*iter,u,g);
//     }
// }
