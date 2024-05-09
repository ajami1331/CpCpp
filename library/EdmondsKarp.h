#ifndef EdmondsKarp_h
#define EdmondsKarp_h 1

#include "Common.h"

namespace library
{

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

    void AddEdge(int from, int to, int cap, bool undirected)
    {
        graph[from][to] += cap;
        graph[to][from] = undirected ? graph[to][from] + cap : graph[to][from];
    }

    void SetEdgeCapacity(int from, int to, int cap, bool undirected)
    {
        graph[from][to] = cap;
        graph[to][from] = undirected ? cap : graph[to][from];
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
