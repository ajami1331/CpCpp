#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
#ifndef EdmondsKarp_h
#define EdmondsKarp_h 1
namespace library
{
using namespace std;
template <int INF> struct EdmondsKarp
{
    int n;
    vector<int> par;
    vector<bool> vis;
    vector<vector<int>> graph;
    EdmondsKarp()
    {
    }
    EdmondsKarp(int _n) : n(_n), par(_n), vis(_n), graph(_n, vector<int>(_n, 0))
    {
    }
    ~EdmondsKarp()
    {
    }
    void AddEdge(int from, int to, int cap, bool directed)
    {
        graph[from][to] += cap;
        graph[to][from] = directed ? graph[to][from] + cap : graph[to][from];
    }
    void SetEdgeCapacity(int from, int to, int cap, bool directed)
    {
        graph[from][to] = cap;
        graph[to][from] = directed ? cap : graph[to][from];
    }
    bool Bfs(int src, int sink)
    {
        int u;
        fill(vis.begin(), vis.end(), false);
        fill(par.begin(), par.end(), -1);
        vis[src] = true;
        queue<int> q;
        q.push(src);
        while (!q.empty())
        {
            u = q.front();
            q.pop();
            if (u == sink)
                return true;
            for (int i = 0; i < n; i++)
            {
                if (graph[u][i] > 0 && !vis[i])
                {
                    q.push(i);
                    vis[i] = true;
                    par[i] = u;
                }
            }
        }
        return par[sink] != -1;
    }
    int MinVal(int i)
    {
        int ret = INF;
        for (; par[i] != -1; i = par[i])
        {
            ret = min(ret, graph[par[i]][i]);
        }
        return ret;
    }
    void AugmentPath(int val, int i)
    {
        for (; par[i] != -1; i = par[i])
        {
            graph[par[i]][i] -= val;
            graph[i][par[i]] += val;
        }
    }
    int MaxFlow(int src, int sink)
    {
        int min_cap, ret = 0;
        while (this->Bfs(src, sink))
        {
            this->AugmentPath(min_cap = this->MinVal(sink), sink);
            ret += min_cap;
        }
        return ret;
    }
};
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
const int sz = 2e5 + 10;
const int INF = 1e9 + 10;
int from[555], to[555];
double cap[555];
void Solve()
{
    int n, m;
    int x;
    cin >> n >> m >> x;
    library::EdmondsKarp<INF> flow_graph(n);
    for (int i = 0; i < m; i++)
    {
        cin >> from[i] >> to[i] >> cap[i];
        --from[i];
        --to[i];
    }
    double lo = 1.0 / x, hi = INF, mid;
    int flow;
    for (int iter = 0; iter < 128; iter++)
    {
        mid = (lo + hi) / 2;
        for (int j = 0; j < m; j++)
            flow_graph.SetEdgeCapacity(from[j], to[j], cap[j] / mid, 0);
        flow = flow_graph.MaxFlow(0, n - 1);
        if (flow >= x)
            lo = mid;
        else
            hi = mid;
    }
    cout << fixed << setprecision(10) << (mid)*x << "\n";
    cerr << "-----\n";
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
