#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <omp.h>
#include <chrono>
using namespace std;

void BFS(const vector<vector<int>> &adjacencylist, vector<bool> &visited, queue<int> &q)
{
    while (!q.empty())
    {
        int vertex = q.front();
        q.pop();
        cout << vertex << " ";

#pragma omp parallel for // Parallelize the loop
        for (int i = 0; i < adjacencylist[vertex].size(); ++i)
        {
            int neighbour = adjacencylist[vertex][i];
            if (!visited[neighbour])
            {
#pragma omp critical // Ensure only one thread modifies visited
                {
                    visited[neighbour] = true;
                    q.push(neighbour);
                }
            }
        }
    }
}
int main()
{
    int nvertices, nedges;
    cout << "Enter the number of vertices: ";
    cin >> nvertices;
    cout << "Enter the number of edges: ";
    cin >> nedges;

    vector<vector<int>> adjacencylist(nvertices);

    cout << "Enter the edges in (source destination) format: ";
    for (int i = 0; i < nedges; i++)
    {
        int u, v;
        cin >> u >> v;
        adjacencylist[u].push_back(v);
        adjacencylist[v].push_back(u);
    }

    int startvertex;
    cout << "Enter the starting vertex: ";
    cin >> startvertex;

    // Measure BFS traversal time
    cout << "BFS traversal is: ";
    vector<bool> visitedBFS(nvertices, false);
    queue<int> q;
    visitedBFS[startvertex] = true;
    q.push(startvertex);
    auto start_bfs = chrono::steady_clock::now();
    BFS(adjacencylist, visitedBFS, q);
    auto end_bfs = chrono::steady_clock::now();
    cout << endl;
    auto duration_bfs = chrono::duration_cast<chrono::microseconds>(end_bfs - start_bfs);
    cout << "Time taken for BFS traversal: " << duration_bfs.count() << " microseconds" << endl;
    cout << "Speedup BFS: " << static_cast<double>(start_bfs.time_since_epoch().count()) / end_bfs.time_since_epoch().count() << endl;
return 0;
}