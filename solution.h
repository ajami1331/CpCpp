#ifndef solution_h
#define solution_h 1

#include <cstdio>
#include <cstring>
#include "library/AhoCorasick.h"

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