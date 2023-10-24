#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include "library/atcoder/lazysegtree"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
int t, n, m;
int type, l, r, x;

using S = ll;
struct F
{
    int type;
    ll x;
    int step;
    F(int type = 0, ll x = 0, int step = 0) : type(type), x(x), step(step)
    {
    }
    F operator+(const F &f) const
    {
        if (step > f.step)
        {
            if (type == 0)
            {
                return F(0, f.x + x, step);
            }
            else
            {
                return *this;
            }
        }

        if (f.type == 0)
        {
            return F(0, f.x + x, step);
        }

        return f;
    }
    S operator+(const S &s) const
    {
        if (type == 0)
        {
            return x + s;
        }

        return x;
    }
};

S op(S a, S b)
{
    return a + b;
}

S e()
{
    return 0;
}

S mapping(F f, S x)
{
    return f + x;
}

F composition(F f, F g)
{
    return f + g;
}

F id()
{
    return F();
}

void Solve()
{
    scanf("%d %d", &n, &m);
    vector<S> a(n);
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &a[i]);
    }

    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);

    for (int step = 1; step <= m; step++)
    {
        scanf("%d %d %d", &type, &l, &r);
        --l, --r, type--;
        if (type == 0)
        {
            scanf("%d", &x);
            seg.apply(l, r, F(0, x, step));
        }
        else if (type == 1)
        {
            scanf("%d", &x);
            seg.apply(l, r, F(1, x, step));
        }
        else
        {

            printf("%lld\n", seg.prod(l, r));
        }
    }
}

} // namespace solution

#endif