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
        cout << "City Road Network:" << endl;
        cout << "==============================" << endl;

        for (int i = 0; i < adjList.size(); i++) {
            cout << "Intersection " << i
                << " (" << intersectionNames[i] << ") connects to:\n";

            for (Pair v : adjList[i]) {
                int dest = v.first;
                int distance = v.second;

                cout << "   -> Intersection " << dest
                    << " (Distance: " << distance << " blocks)\n";
            }
        }
    }

    // Depth-First Search (DFS)
    void dfs(int start) {
        vector<bool> visited(SIZE, false);
        stack<int> s;

        s.push(start);
        visited[start] = true;

        cout << "City Exploration (DFS) from Intersection "
            << start << " (" << intersectionNames[start] << ")\n";
        cout << "Purpose: Finding long, winding exploration paths\n";
        cout << "==============================================\n";


        while (!s.empty()) {
            int currentVertex = s.top();
            s.pop();

            cout << "Exploring Intersection " << currentVertex
                << " (" << intersectionNames[currentVertex] << ")\n";

            // Visit all adjacent vertices
            for (Pair neighbor : adjList[currentVertex]) {
                int dest = neighbor.first;
                int distance = neighbor.second;

                if (!visited[dest]) {
                    visited[dest] = true;
                    cout << "   -> Path toward Intersection " << dest
                        << " (" << intersectionNames[dest]
                        << ") - Distance: " << distance << " blocks\n";
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

        cout << "Layer-by-Layer Road Inspection (BFS) from Intersection "
            << start << " (" << intersectionNames[start] << ")\n";
        cout << "Purpose: Discovering nearest destinations first\n";
        cout << "==============================================\n";

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();

            cout << "Checking Intersection " << currentVertex
                << " (" << intersectionNames[currentVertex] << ")\n";

            // Visit all adjacent vertices
            for (Pair neighbor : adjList[currentVertex]) {
                int dest = neighbor.first;
                int distance = neighbor.second;

                if (!visited[dest]) {
                    visited[dest] = true;
                    cout << "   -> Nearby: Intersection " << dest
                        << " (" << intersectionNames[dest]
                        << ") - Distance: " << distance << " blocks\n";
                    q.push(dest);
                }
            }
        }
        cout << endl;
    }



    // Shortest Path (Dijkstra's Algorithm)
    void shortestPath(int start) {
        // distance array, initialize all distances as "infinity"
        vector<int> dist(SIZE, INT_MAX);
        dist[start] = 0;

        // Min-heap priority queue (distance, node)
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({ 0, start });

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            // Skip if we already found a better path
            if (currentDist > dist[node])
                continue;

            // Check neighbors
            for (auto& p : adjList[node]) {
                int neighbor = p.first;
                int weight = p.second;

                // Relaxation step
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    pq.push({ dist[neighbor], neighbor });
                }
            }
        }

        // Print the results
        cout << "Shortest path distances from Intersection "
            << start << " (" << intersectionNames[start] << "):\n";

        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : ";

            if (dist[i] == INT_MAX)
                cout << "unreachable";
            else
                cout << dist[i];

            cout << "\n";
        }

        cout << endl;
    }

    // Minimum Spanning Tree (Prim's Algorithm)
    void minimumSpanningTree() {
        vector<int> key(SIZE, INT_MAX);     // Minimum weight edge to each node
        vector<int> parent(SIZE, -1);       // To store MST structure
        vector<bool> inMST(SIZE, false);    // Track included nodes

        key[0] = 0; // Start MST from node 0

        for (int i = 0; i < SIZE - 1; i++) {
            // Pick the minimum key vertex not yet in MST
            int minKey = INT_MAX, u = -1;
            for (int v = 0; v < SIZE; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    u = v;
                }
            }

            inMST[u] = true;

            // Relax edges
            for (auto& p : adjList[u]) {
                int v = p.first;
                int weight = p.second;

                if (!inMST[v] && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                }
            }
        }

        // Print the MST
        cout << "Minimum Spanning Tree (Road Network):\n";
        cout << "=====================================\n";

        for (int i = 1; i < SIZE; i++) {
            if (parent[i] != -1) {
                cout << "Road between "
                    << intersectionNames[parent[i]]
                    << " and " << intersectionNames[i]
                    << " (Distance: " << key[i] << " blocks)\n";
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
    cout << "\n";

    graph.dfs(0);
    graph.bfs(0);
    graph.shortestPath(0);
    graph.minimumSpanningTree();

    return 0;
}
