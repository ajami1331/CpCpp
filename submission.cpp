<<<<<<< HEAD
#ifndef ATCODER_INTERNAL_BITOP_HPP
#define ATCODER_INTERNAL_BITOP_HPP 1
#ifdef _MSC_VER
#include <intrin.h>
#endif
#if __cplusplus >= 202002L
#include <bit>
#endif
namespace atcoder
{
namespace internal
{
#if __cplusplus >= 202002L
using std::bit_ceil;
#else
unsigned int bit_ceil(unsigned int n)
{
    unsigned int x = 1;
    while (x < (unsigned int)(n))
        x *= 2;
    return x;
}
#endif
int countr_zero(unsigned int n)
{
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}
constexpr int countr_zero_constexpr(unsigned int n)
{
    int x = 0;
    while (!(n & (1 << x)))
        x++;
    return x;
}
} // namespace internal
} // namespace atcoder
#endif // ATCODER_INTERNAL_BITOP_HPP
#ifndef ATCODER_LAZYSEGTREE_HPP
#define ATCODER_LAZYSEGTREE_HPP 1
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
namespace atcoder
{
#if __cplusplus >= 201703L
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id> struct lazy_segtree
=======
#ifndef LAZY_SEGMENT_TREE_H
#define LAZY_SEGMENT_TREE_H 1
#include <algorithm>
#include <functional>
namespace library
{
#if __cplusplus >= 201703L
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id, size_t sz> class LazySegmentTree
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
{
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");
    static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>, "mapping must work as F(F, S)");
    static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
                  "compostiion must work as F(F, F)");
    static_assert(std::is_convertible_v<decltype(id), std::function<F()>>, "id must work as F()");
#else
<<<<<<< HEAD
template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
struct lazy_segtree
{
#endif
  public:
    lazy_segtree() : lazy_segtree(0)
=======
template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)(), size_t sz>
class LazySegmentTree
{
#endif
  private:
    S tree[sz * 4];
    F lazy[sz * 4];
  public:
    LazySegmentTree()
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
    {
    }
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e()))
    {
<<<<<<< HEAD
    }
    explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size()))
    {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--)
        {
            update(i);
=======
        std::fill(tree, tree + sz * 4, e());
        std::fill(lazy, lazy + sz * 4, id());
    }
    void Build(int node, int begin, int end)
    {
        tree[node] = e();
        lazy[node] = id();
        if (begin == end)
        {
            return;
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (begin + end) >> 1;
        Build(left, begin, mid);
        Build(right, mid + 1, end);
        tree[node] = op(tree[left], tree[right]);
    }
<<<<<<< HEAD
    void set(int p, S x)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }
    S get(int p)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        return d[p];
    }
    S prod(int l, int r)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return e();
        l += size;
        r += size;
        for (int i = log; i >= 1; i--)
        {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r)
        {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod()
    {
        return d[1];
    }
    void apply(int p, F f)
    {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--)
            push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }
    void apply(int l, int r, F f)
    {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r)
            return;
        l += size;
        r += size;
        for (int i = log; i >= 1; i--)
        {
            if (((l >> i) << i) != l)
                push(l >> i);
            if (((r >> i) << i) != r)
                push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r)
            {
                if (l & 1)
                    all_apply(l++, f);
                if (r & 1)
                    all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++)
        {
            if (((l >> i) << i) != l)
                update(l >> i);
            if (((r >> i) << i) != r)
                update((r - 1) >> i);
        }
    }
    template <bool (*g)(S)> int max_right(int l)
    {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g)
    {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n)
            return _n;
        l += size;
        for (int i = log; i >= 1; i--)
            push(l >> i);
        S sm = e();
        do
        {
            while (l % 2 == 0)
                l >>= 1;
            if (!g(op(sm, d[l])))
            {
                while (l < size)
                {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l])))
                    {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
    template <bool (*g)(S)> int min_left(int r)
    {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g)
    {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0)
            return 0;
        r += size;
        for (int i = log; i >= 1; i--)
            push((r - 1) >> i);
        S sm = e();
        do
        {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!g(op(d[r], sm)))
            {
                while (r < size)
                {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm)))
                    {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;
    void update(int k)
    {
        d[k] = op(d[2 * k], d[2 * k + 1]);
    }
    void all_apply(int k, F f)
    {
        d[k] = mapping(f, d[k]);
        if (k < size)
            lz[k] = composition(f, lz[k]);
    }
    void push(int k)
    {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
} // namespace atcoder
#endif // ATCODER_LAZYSEGTREE_HPP
=======
    void Build(int node, int begin, int end, S *arr)
    {
        tree[node] = e();
        lazy[node] = id();
        if (begin == end)
        {
            tree[node] = arr[begin];
            return;
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (begin + end) >> 1;
        Build(left, begin, mid, arr);
        Build(right, mid + 1, end, arr);
        tree[node] = op(tree[left], tree[right]);
    }
    inline void Push(int node, int begin, int end)
    {
        tree[node] = mapping(lazy[node], tree[node]);
        if (begin != end)
        {
            int left = node << 1;
            int right = left | 1;
            lazy[left] = composition(lazy[node], lazy[left]);
            lazy[right] = composition(lazy[node], lazy[right]);
        }
        lazy[node] = id();
    }
    inline void Update(int node, int begin, int end, int l, int r, F x)
    {
        Push(node, begin, end);
        if (r < begin || end < l)
            return;
        if (l <= begin && end <= r)
        {
            lazy[node] = composition(x, lazy[node]);
            Push(node, begin, end);
            return;
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (begin + end) >> 1;
        Update(left, begin, mid, l, r, x);
        Update(right, mid + 1, end, l, r, x);
        tree[node] = op(tree[left], tree[right]);
    }
    inline S Query(int node, int begin, int end, int l, int r)
    {
        Push(node, begin, end);
        if (r < begin || end < l)
            return e();
        if (l <= begin && end <= r)
        {
            return tree[node];
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (begin + end) >> 1;
        return op(Query(left, begin, mid, l, r), Query(right, mid + 1, end, l, r));
    }
};
} // namespace library
#endif // LAZY_SEGMENT_TREE_H
#ifndef ATCODER_INTERNAL_BITOP_HPP
#define ATCODER_INTERNAL_BITOP_HPP 1
#ifdef _MSC_VER
#include <intrin.h>
#endif
#if __cplusplus >= 202002L
#include <bit>
#endif
namespace atcoder {
namespace internal {
#if __cplusplus >= 202002L
using std::bit_ceil;
#else
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}
#endif
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}
}  // namespace internal
}  // namespace atcoder
#endif  // ATCODER_INTERNAL_BITOP_HPP
#ifndef ATCODER_LAZYSEGTREE_HPP
#define ATCODER_LAZYSEGTREE_HPP 1
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>
namespace atcoder {
#if __cplusplus >= 201703L
template <class S,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
struct lazy_segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");
    static_assert(
        std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>,
        "mapping must work as F(F, S)");
    static_assert(
        std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
        "compostiion must work as F(F, F)");
    static_assert(std::is_convertible_v<decltype(id), std::function<F()>>,
                  "id must work as F()");
#else
template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {
#endif
  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }
    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }
    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }
    S all_prod() { return d[1]; }
    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;
        l += size;
        r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }
    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }
    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
}  // namespace atcoder
#endif  // ATCODER_LAZYSEGTREE_HPP
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
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
>>>>>>> 77610624860eb1c7c063d4598d5f9bec1e699ef6
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
            int m = (l + r) / 2;
            printf("%lld\n", seg.prod(l, m + 1) + seg.prod(m + 1, r + 1));
        }
    }
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main()
{
    solution::Solve();
    return 0;
}
