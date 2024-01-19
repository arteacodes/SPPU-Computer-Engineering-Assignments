#include <iostream>
#include <iomanip>
using namespace std;

#define INF 99;

class Greedy
{
    int nv;  // no. of vertices
    int ne;  // no. of edges
    int **adj;  // adjacency matrix
    bool *visited;

    public:
    Greedy()
    {
        nv = 0;
        ne = 0;
        adj = NULL;
    }

    void accept();
    void addEdge(int, int, int);
    void prims();
    void display();
};


void Greedy::accept()
{
    cout<<"\nEnter no. of vertices: ";
    cin>>nv;

    cout<<"Enter no. of edges: ";
    cin>>ne;

    adj = new int* [nv];
    for (int i=0; i<nv; i++)
    {
        adj[i] = new int[nv];
        for (int j=0; j<nv; j++)
        {
            adj[i][j] = 0;
        }
    }

    // read values and add to adj matrix
    for (int i=0; i<ne; i++)
    {
        int n1, n2, weight;
        cout<<"\n--- Edge "<<i+1<<" ---\n";
        cout<<"Enter vertice 1: ";
        cin>>n1;
        cout<<"Enter vertice 2: ";
        cin>>n2;
        cout<<"Enter edge weight: ";
        cin>>weight;
        addEdge(n1, n2, weight);
    }

    // fill with infinity where cost is not mentioned
    for (int i=0; i<nv; i++)
    {
        for (int j=0; j<nv; j++)
        {
            if (adj[i][j] == 0 && i!=j)
                adj[i][j] = INF;
        }
    }
}


void Greedy::addEdge(int a, int b, int w)
{
    adj[a][b] = w;
    adj[b][a] = w;
}


void Greedy::prims()
{
    int edges = 0;
    int mincost = 0;
    int row, col;  // row and column number

    visited = new bool[nv];
    visited[0] = true;

    while (edges < nv-1)
    {
        int min = INF;
        for (int i=0; i<nv; i++)
        {
            if (visited[i])
            {
                for (int j=0; j<nv; j++)
                {
                    if (!visited[j] && adj[i][j]<min && i!=j)
                    {
                        min = adj[i][j];
                        row = i;
                        col = j;
                    }
                }
            }
        }

        cout<<endl;
        cout<<"("<<row<<","<<col<<") | ";
        cout<<adj[row][col]<<endl;
        visited[col] = true;
        edges++;
        mincost += adj[row][col];
    }

    cout<<"\nMinimum spanning tree cost = "<<mincost<<endl;
}


void Greedy::display()
{
    cout<<"\nAdjacency Matrix: "<<endl;

    cout<<"  ";
    for (int m=0; m<nv; m++)
    {
        cout<<"    "<<m;
    }
    cout<<endl;
    
    for (int n=0; n<nv; n++)
    {
        cout<<"-----";
    }
    cout<<endl;

    for (int i=0; i<nv; i++)
    {
        cout<<left<<i<<left<<" | ";
        for (int j=0; j<nv; j++)
        {
            if (adj[i][j] < 10)
                cout<<" "<<0<<adj[i][j]<<" ";
            else
                cout<<" "<<adj[i][j]<<" ";
        }
        cout<<endl;
    }
}

int main()
{
    Greedy g;

    int ch;
    char ans = 'y';

    do
    {
        g.accept();
        g.prims();
        g.display();

        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    }
    while (ans == 'y' || ans == 'Y');
}