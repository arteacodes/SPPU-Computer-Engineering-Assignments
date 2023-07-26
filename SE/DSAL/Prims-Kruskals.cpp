/*
You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures.
*/

#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;


struct Edge
{
    int s;
    int d;
    int wt;

    Edge()
    {}
};


class Graph
{
    int nv;  // no. of vertices
    int ne;  // no. of edges
    int **adj; 
    string city;
    string *offices;  // ptr to string array stores city names
    bool *visited;  // ptr to boolean array to track visited vertices
    

    public:
    Graph()
    {
        nv = 0;
        ne = 0;
        offices = NULL;
        adj = NULL;
    }

    void read();
    void add(string, int, string, int, int);
    void prims(Graph);
    void kruskals();
    void display();
};

void Graph::read()
{
    cout<<"\nEnter no. of offices: ";  // veritices
    cin>>nv;
    cout<<"Enter no. of telephone lines: ";  // edges
    cin>>ne;
    
    offices = new string[nv];
    
    adj = new int*[nv];
    for (int i=0; i<nv; i++)
    {
        adj[i] = new int[nv];
        for (int j=0; j<nv; j++)
        {
            adj[i][j] = 0;
        }
    }
    
    // read values and add to adj matrix
    for (int k=0; k<ne; k++)
    {
        string s, d;
        int srcid, destid, w;
        cout<<"\nLine "<<k<<":"<<endl;
        cout<<"Enter source city: ";
        cin>>s;
        cout<<"Enter source id: ";
        cin>>srcid;
        cout<<"Enter destination city: ";
        cin>>d;
        cout<<"Enter destination id: ";
        cin>>destid;
        cout<<"Enter cost of "<<s<<" -> "<<d<<": ";
        cin>>w;
        add(s, srcid, d, destid, w);
    }
    
    // fill with infinity where cost is not mentioned
    for (int i=0; i<nv; i++)
    {
        for (int j=0; j<nv; j++)
        {
            if (adj[i][j] == 0 && i!=j)
                adj[i][j] = 99;
        }
    }
}


void Graph::add(string src, int srcid, string dest, int destid, int w)
{
    offices[srcid] = src;
    offices[destid] = dest;
        
    adj[srcid][destid] = w;
    adj[destid][srcid] = w;
}


void Graph::prims(Graph g)
{
    int v = g.nv;
    int edges = 0;
    int mincost = 0;
    int r, c;  // row and column no.
    
    visited = new bool[v];
    visited[0] = true;
    
    while (edges < v-1)
    {
        int min = 99;
        for (int i=0; i<v; i++) {
            if (visited[i]) {
                for (int j=0; j<v; j++) {
                    if (!visited[j]  && adj[i][j]<min && i!=j) {
                        min = adj[i][j];
                        r = i;
                        c = j;
                    }
                }
            }
        }
        
        cout<<"("<<r<<","<<c<<") | ";
        cout<<offices[r]<<"-->"<<offices[c]<<" | "<<adj[r][c];
        cout<<endl;
        visited[c] = true;
        //cout<<"\n"<<offices[c]<<" is visited."<<endl;
        edges++;
        mincost += adj[r][c];
    }
    
    cout<<endl;
    for (int i=0; i<v; i++)
    {
        cout<<visited[i]<<" ";
    }
    cout<<"\nMinimum spanning tree cost: "<<mincost<<endl;
}

void Graph::kruskals()
{
    int mincost = 0; 
    Edge temp[nv*nv];  // temporary array of size nv*nv
    int k = 0;

    // copying elements
    for (int i=0; i<nv; i++) {
        for (int j=0; j<nv; j++) {
            temp[k].s = i;
            temp[k].d = j;
            temp[k].wt = adj[i][j];
            k++;
        }
    }

    // bubble sort
    Edge t;
    for (int i=0; i<nv*nv; i++) {
        for (int j=0; j<nv*nv; j++) {
            if (temp[i].wt < temp[j].wt) {
                t = temp[i];
                temp[i] = temp[j];
                temp[j] = t;
            }
        }
    }

    visited = new bool[nv];

    // kruskals algorithm
    for (int i=0; i<nv*nv; i++) {
        int r = temp[i].s;
        int c = temp[i].d;
        if (temp[i].wt!=0 && temp[i].wt!=99) {
            if (!visited[temp[i].s] || !visited[temp[i].d]) {
                cout<<"("<<r<<","<<c<<") | ";
                cout<<offices[r]<<"-->"<<offices[c]<<" | "<<adj[r][c];
                cout<<endl;
                visited[r] = true;
                visited[c] = true;
                mincost += adj[r][c];
            }
        }
    }
    cout<<"Minimum spanning tree cost: "<<mincost<<endl;
}


void Graph::display()
{
    cout<<"\nAdjacency Matrix: "<<endl;
    cout<<"   ";
    for (int k=0; k<nv; k++)
    {
        cout<<setw(8);
        cout<<offices[k];
    }
    cout<<endl;
    
    for (int i=0; i<nv; i++)
    {
        //cout<<setw(8);
        cout<<left<<offices[i]<<left<<": ";
        for (int j=0; j<nv; j++)
        {
            if (adj[i][j] < 10)
                cout<<"   "<<0<<adj[i][j]<<"   ";
            else
                cout<<"   "<<adj[i][j]<<"   ";
        }
        cout<<endl;
    }
}


int main()
{
    Graph g;

    int ch;
    char ans = 'y';
    
    do
    {
        cout<<"1. Input Graph\n2. Prim's Algorithm\n3. Kruskal's Algorithm\n4. Display Adjacency Matrix\nEnter choice: ";
        cin>>ch;
        switch (ch)
        {
            case 1:
            g.read();
            break;
            
            case 2:
            g.prims(g);
            break;
            
            case 3:
            g.kruskals();
            break;

            case 4:
            g.display();
            break;
            
            default:
            cout<<"\nInvalid choice!";
            break;
        }
        
        cout<<"\nContinue? (y/n): ";
        cin>>ans;
    } while (ans=='y' || ans=='Y');
}