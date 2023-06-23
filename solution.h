#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "library/ZAlgo.h"

namespace solution
{
using namespace std;
using ll = long long;

const int sz = 1e6 + 10;
int sLen, tLen;

struct Elem
{
    ll len;
    char c;
    Elem() {}
    Elem(int len, char c) : len(len), c(c) {}
    bool operator==(const Elem &rhs) const
    {
        return len == rhs.len && c == rhs.c;
    }
    bool operator<=(const Elem &rhs) const
    {
        return len <= rhs.len && c == rhs.c;
    }
    bool operator>=(const Elem &rhs) const
    {
        return len >= rhs.len && c == rhs.c;
    }
    bool operator!=(const Elem &rhs) const
    {
        return !(*this == rhs);
    }
} const outOfBound = Elem(0, '$');

Elem s[sz], t[sz];
vector <Elem> sVec, tVec;

library::ZAlgo<Elem, sz + sz + sz> zAlgo;

void Solve()
{
    scanf("%d %d", &sLen, &tLen);
    for (int i = 0; i < sLen; i++)
    {
        scanf("%lld-%c", &s[i].len, &s[i].c);
    }

    for (int i = 0; i < tLen; i++)
    {
        scanf("%lld-%c", &t[i].len, &t[i].c);
    }

    sVec.clear();
    tVec.clear();

    for (int i = 0; i < sLen; i++)
    {
        if (sVec.empty() || sVec.back().c != s[i].c)
        {
            sVec.push_back(s[i]);
        }
        else
        {
            sVec.back().len += s[i].len;
        }
    }

    for (int i = 0; i < tLen; i++)
    {
        if (tVec.empty() || tVec.back().c != t[i].c)
        {
            tVec.push_back(t[i]);
        }
        else
        {
            tVec.back().len += t[i].len;
        }
    }
    
    if (tVec.size() == 1)
    {
        ll ans = 0;
        for (int i = 0; i < sVec.size(); i++)
        {
            if (sVec[i] >= tVec[0])
            {
                ans += sVec[i].len - tVec[0].len + 1;
            }
        }
        printf("%lld\n", ans);
        return;
    }

    if (tVec.size() == 2)
    {
        ll ans = 0;
        for (int i = 0; i + 1 < sVec.size(); i++)
        {
            if (sVec[i] >= tVec[0] && sVec[i + 1] >= tVec[1])
            {
                ans++;
            }
        }
        printf("%lld\n", ans);
        return;
    }

    auto last = tVec.back();
    auto first = tVec.front();
    tVec.pop_back();
    reverse(tVec.begin(), tVec.end());
    tVec.pop_back();
    reverse(tVec.begin(), tVec.end());
    zAlgo.Init(tVec, sVec, outOfBound);
    ll ans = 0;
    for (int i = tVec.size() + 2; i < zAlgo.n; i++)
    {
        if (zAlgo.z[i] == tVec.size())
        {
            if (i + tVec.size() < zAlgo.n && zAlgo.s[i - 1] >= first && zAlgo.s[i + tVec.size()] >= last)
            {
                ans++;
            }
        }
    }
    printf("%lld\n", ans);
}

} // namespace solution
#endif