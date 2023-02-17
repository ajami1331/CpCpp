#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#ifndef AhoCorasick_h
#define AhoCorasick_h 1
namespace library
{
template <int MAX> struct AhoCorasick
{
    std::vector<int> mark[MAX + 7];
    int state, failure[MAX + 7];
    int trie[MAX + 7][26];
    AhoCorasick()
    {
        Init();
    }
    void Init()
    {
        mark[0].clear();
        std::fill(trie[0], trie[0] + 26, -1);
        state = 0;
    }
    int Value(char c)
    {
        return c - 'a';
    }
    void Add(char *s, int t)
    {
        int root = 0, id;
        for (int i = 0; s[i]; i++)
        {
            id = Value(s[i]);
            if (trie[root][id] == -1)
            {
                trie[root][id] = ++state;
                mark[state].clear();
                std::fill(trie[state], trie[state + 1] + 26, -1);
            }
            root = trie[root][id];
        }
        mark[root].push_back(t);
    }
    void ComputeFailure()
    {
        std::queue<int> Q;
        failure[0] = 0;
        for (int i = 0; i < 26; i++)
        {
            if (trie[0][i] != -1)
            {
                failure[trie[0][i]] = 0;
                Q.push(trie[0][i]);
            }
            else
                trie[0][i] = 0;
        }
        while (!Q.empty())
        {
            int u = Q.front();
            Q.pop();
            for (int v : mark[failure[u]])
                mark[u].push_back(v);
            for (int i = 0; i < 26; i++)
            {
                if (trie[u][i] != -1)
                {
                    failure[trie[u][i]] = trie[failure[u]][i];
                    Q.push(trie[u][i]);
                }
                else
                    trie[u][i] = trie[failure[u]][i];
            }
        }
    }
};
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
const int sz = 1e6 + 10;
const int MAX = 505 * 505 + 100;
char inp[sz], s[505][505];
int cnt[505];
library::AhoCorasick<MAX> automata;
void countFreq()
{
    for (int i = 0, root = 0, id; inp[i]; i++)
    {
        id = automata.Value(inp[i]);
        root = automata.trie[root][id];
        if (root == 0)
            continue;
        for (int i = 0; i < automata.mark[root].size(); i++)
            cnt[automata.mark[root][i]]++;
    }
}
void Solve()
{
    int t, n, cs;
    scanf("%d", &t);
    for (int cs = 1; cs <= t; cs++)
    {
        scanf("%d", &n);
        scanf("%s", inp);
        automata.Init();
        for (int i = 0; i < n; i++)
        {
            scanf("%s", s[i]);
            automata.Add(s[i], i);
        }
        automata.ComputeFailure();
        memset(cnt, 0, sizeof cnt);
        countFreq();
        printf("Case %d:\n", cs);
        for (int i = 0; i < n; i++)
        {
            printf("%d\n", cnt[i]);
        }
    }
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
