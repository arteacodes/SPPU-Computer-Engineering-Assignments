#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
    int vertices;
    vector<vector<int>> adjlist;

    public:
    Graph(int v) {
        vertices = v;
        adjlist.resize(v);
    }

    void print() {
        for (const auto& inner_vector : adjlist) {
    // Access elements of the inner vector
    for (const auto& element : inner_vector) {
        cout << element << " ";
    }
    cout << endl;
}

    }

    void addEdge(int a, int b) {  // add a->b and b->a for undirected graph
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    void bfs(vector<bool> &visited, queue<int> &q) {  // recursive bfs
        if (q.empty()) {
            return;
        }

        // deque front node and print it
        int u = q.front();
        q.pop();
        cout<<u<<" ";

        for (int v : adjlist[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }

        bfs(visited, q);
    }

    void dfs(int u, vector<bool> &visited) { // recursive dfs
        visited[u] = true;
        cout<<u<<" ";

        for (int v : adjlist[u]) {
            if (!visited[v]) {
                dfs(v, visited);
            }
        }
    }
};


int main()
{
    int vertices, edges, u, v, choice;
    char ans = 'y';

    cout<<"Enter no. of vertices: ";
    cin>>vertices;

    Graph g(vertices);

    cout<<"Enter no. of edges: ";
    cin>>edges;
    cout<<endl;

    for (int i=0; i<edges; i++) {
        cout<<"Enter the edge pairs (u v): ";
        cin>>u>>v;
        g.addEdge(u, v);
        g.print();
    }

    do {
        cout<<"\n1. BFS\n2. DFS\nEnter choice: ";
        cin>>choice;

        vector<bool> visited(vertices, false);
        queue<int> q;

        switch(choice) {
            case 1:
            for (int i=0; i<vertices; i++) {
                if (!visited[i]) {
                    visited[i] = true;
                    q.push(i);
                    g.bfs(visited, q);
                }
            }
            break;

            case 2:
            for (int i=0; i<vertices; i++) {
                if (!visited[i]) {
                    g.dfs(i, visited);
                }
            }
            break;

            default:
            cout<<"\nInvalid!";
            break;
        }

        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    }
    while (ans == 'y' || ans == 'Y');
}
