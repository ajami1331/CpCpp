#ifndef Dinic_h
#define Dinic_h 1

#include <algorithm>
#include <vector>

namespace library
{

struct Edge
{
    int from, to, cap, flow, index;
    Edge(int from, int to, int cap, int flow, int index) : from(from), to(to), cap(cap), flow(flow), index(index)
    {
    }
};

template <int INF> struct Dinic
{
    int N;
    std::vector<std::vector<Edge>> G;
    std::vector<Edge *> dad;
    std::vector<int> Q;

    Dinic(int N) : N(N), G(N), dad(N), Q(N)
    {
    }

    void AddEdge(int from, int to, int cap)
    {
        G[from].emplace_back(from, to, cap, 0, G[to].size());
        if (from == to)
            G[from].back().index++;
        G[to].emplace_back(to, from, 0, 0, G[from].size() - 1);
    }

    long long BlockingFlow(int s, int t)
    {
        std::fill(dad.begin(), dad.end(), (Edge *)NULL);
        dad[s] = &G[0][0] - 1;

        int head = 0, tail = 0;
        Q[tail++] = s;
        while (head < tail)
        {
            int x = Q[head++];
            for (int i = 0; i < G[x].size(); i++)
            {
                Edge &e = G[x][i];
                if (!dad[e.to] && e.cap - e.flow > 0)
                {
                    dad[e.to] = &G[x][i];
                    Q[tail++] = e.to;
                }
            }
        }
        if (!dad[t])
            return 0;

        long long totflow = 0;
        for (int i = 0; i < G[t].size(); i++)
        {
            Edge *start = &G[G[t][i].to][G[t][i].index];
            int amt = INF;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from])
            {
                if (!e)
                {
                    amt = 0;
                    break;
                }
                amt = std::min(amt, e->cap - e->flow);
            }
            if (amt == 0)
                continue;
            for (Edge *e = start; amt && e != dad[s]; e = dad[e->from])
            {
                e->flow += amt;
                G[e->to][e->index].flow -= amt;
            }
            totflow += amt;
        }
        return totflow;
    }

    long long MaxFlow(int s, int t)
    {
        long long totflow = 0;
        while (long long flow = BlockingFlow(s, t))
            totflow += flow;
        return totflow;
    }

    void ClearFlow()
    {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < G[i].size(); ++j)
                G[i][j].flow = 0;
    }
};
} // namespace library
#endif