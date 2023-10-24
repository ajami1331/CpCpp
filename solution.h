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
<<<<<<< HEAD
=======
#include "library/LazySegmentTree.h"
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
#include "library/atcoder/lazysegtree"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
<<<<<<< HEAD
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
=======
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
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
}

S e()
{
<<<<<<< HEAD
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
=======
    return {0, 0};
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
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
<<<<<<< HEAD
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
=======
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
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
        }
    }
}

} // namespace solution

#endif