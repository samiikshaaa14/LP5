#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <omp.h>
#include <chrono>
using namespace std;

void DFS(const vector<vector<int>> &adjacencylist, vector<bool> &visited, stack<int> &s)
{
    while (!s.empty())
    {
        int vertex = s.top();
        s.pop();
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
                    s.push(neighbour);
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
    cout << "DFS traversal is: ";
    vector<bool> visitedDFS(nvertices, false);
    stack<int> s;
    visitedDFS[startvertex] = true;
    s.push(startvertex);
    auto start_dfs = chrono::steady_clock::now();
    DFS(adjacencylist, visitedDFS, s);
    auto end_dfs = chrono::steady_clock::now();
    cout << endl;
    auto duration_dfs = chrono::duration_cast<chrono::microseconds>(end_dfs - start_dfs);
    cout << "Time taken for DFS traversal: " << duration_dfs.count() << " microseconds" << endl;
    cout << "Speedup DFS: " << static_cast<double>(start_dfs.time_since_epoch().count()) / end_dfs.time_since_epoch().count() << endl;

return 0;
}