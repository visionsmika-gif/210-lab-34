#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int SIZE = 11;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;  // Creates alias 'Pair' for the pair<int,int> data type

vector<string> intersectionNames = {
    "Central Station",
    "5th Avenue",
    "Pine Street",
    "Market Square",
    "Liberty Plaza",
    "East Gate",
    "Riverside Drive",
    "Hilltop Road",
    "Sunset Boulevard",
    "Oakwood Junction",
    "Harbor Point"
};

class Graph {
public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;

    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);

        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }

    // Print the graph's adjacency list
    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // Depth-First Search (DFS)
    void dfs(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);
        visited[start] = true;

        // cout << "DFS starting from vertex " << start << ":" << endl;

        cout << "City Exploration (DFS) from Intersection "
            << start << " (" << intersectionNames[start] << ")\n";
        cout << "Purpose: Finding long, winding exploration paths\n";
        cout << "==============================================\n";


        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            // cout << currentVertex << " ";
            cout << "Exploring " << intersectionNames[currentVertex] << "\n";


            // Visit all adjacent vertices
            for (Pair neighbor : adjList[currentVertex]) {
                int dest = neighbor.first;
                int distance = neighbor.second;

                if (!visited[dest]) {
                    visited[dest] = true;
                    cout << "   → Path toward " << intersectionNames[dest]
                        << " (Distance: " << distance << " blocks)\n";
                    s.push(dest);
                }
            }
        }
        cout << endl;
    }

    // Breadth-First Search (BFS)
    void bfs(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        q.push(start);
        visited[start] = true;

        // cout << "BFS starting from vertex " << start << ":" << endl;

        cout << "Layer-by-Layer Road Inspection (BFS) from Intersection "
            << start << " (" << intersectionNames[start] << ")\n";
        cout << "Purpose: Discovering nearest destinations first\n";
        cout << "==============================================\n";

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();

            // cout << currentVertex << " ";
            cout << "Checking " << intersectionNames[currentVertex] << "\n";

            // Visit all adjacent vertices
            for (Pair neighbor : adjList[currentVertex]) {
                int dest = neighbor.first;
                int distance = neighbor.second;

                if (!visited[dest]) {
                    visited[dest] = true;
                    cout << "   → Nearby: " << intersectionNames[dest]
                        << " (Distance: " << distance << " blocks)\n";
                    q.push(dest);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w

        // Delete 2 nodes (nodes 5 and 6 have been deleted).
        // Also change the weights.
        {0,1,16}, {0,2,4}, {0,3,7},
        {2,3,5}, {2,4,2},

        // Add 6 nodes.
        {5, 2, 1}, {5, 8, 2},   // Nodes 5 and 8
        {6, 5, 3},              // Node 6
        {7, 1, 20},             // Node 7
        {9, 8, 4},              // Node 9
        {10, 8, 15}, {10, 9, 2} // Node 10
    };

    // Creates graph
    Graph graph(edges);

    // Prints adjacency list representation of graph
    graph.printGraph();

    graph.dfs(0);
    graph.bfs(0);

    return 0;
}
