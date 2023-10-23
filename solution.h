#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <climits>
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
#include "library/LazySegmentTree.h"
#include "library/atcoder/lazysegtree"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
int n, m;

struct S
{
    ll val;
    ll cnt;
};

struct F
{
    int type;
    ll x;
    int step;
    F()
    {
        type = 0;
        x = 0;
        step = -1;
    }
    F(int type, ll x, int step) : type(type), x(x), step(step) {}
};

S op(S a, S b)
{
    return {a.val + b.val, a.cnt + b.cnt};
}

S e()
{
    return {0, 0};
}

S mapping(F f, S x)
{
    if (f.type == 0)
        return {x.val + (f.x * x.cnt), x.cnt};
    return {f.x * x.cnt, x.cnt};
}

F composition(F f, F g)
{
    if (f.step >= g.step)
    {
        if (f.type == 0 && g.type == 0)
            return {0, f.x + g.x, f.step};
        return f;
    }
    if (f.type == 0 && g.type == 0)
        return {0, f.x + g.x, g.step};
    return g;
}

F id()
{
    return {1, 0, -1};
}

library::LazySegmentTree<S, op, e, F, mapping, composition, id, sz> st;

void Solve()
{
    scanf("%d %d", &n, &m);
    vector<S> a(n);
    for (auto &x : a)
    {
        scanf("%lld", &x.val);
        x.cnt = 1; 
    }
    st.Build(1, 0, n - 1, a.data());
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(a);
    int step = 0;
    while (m--)
    {
        step++;
        int type, l, r, x;
        scanf("%d", &type);
        if (type == 1)
        {
            scanf("%d %d %d", &l, &r, &x);
            --l, --r;
            seg.apply(l, r + 1, {1, x, step});
            st.Update(1, 0, n - 1, l, r, {1, x, step});
        }
        else if (type == 2)
        {
            scanf("%d %d %d", &l, &r, &x);
            --l, --r;
            seg.apply(l, r + 1, {2, x, step});
            st.Update(1, 0, n - 1, l, r, {2, x, step});
        }
        else
        {
            scanf("%d %d", &l, &r);
            --l, --r;
            printf("%lld\n", seg.prod(l, r + 1).val);
        }
    }
}

} // namespace solution

#endif