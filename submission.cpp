#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#ifndef FenwickTree_h
#define FenwickTree_h 1
namespace library
{
#define LOG2(x) (32 - __builtin_clz(x) - 1)
template <typename T, size_t sz, typename op_combine_type = std::plus<T>, typename op_decombine_type = std::minus<T>,
          typename less_type = std::less<T>>
class FenwickTree
{
  private:
    T tr[sz];
    int LOGN = LOG2(sz);
    op_combine_type op_combine;
    op_decombine_type op_decombine;
    less_type less;
  public:
    FenwickTree()
    {
        Reset();
    }
    void Reset()
    {
        memset(tr, 0, sizeof tr);
    }
    void Update(size_t x, T v)
    {
        for (; x < sz; x += (x & -x))
        {
            tr[x] = op_combine(tr[x], v);
        }
    }
    T Query(size_t x)
    {
        T ret = 0;
        for (; x > 0; x -= (x & -x))
        {
            ret = op_combine(ret, tr[x]);
        }
        return ret;
    }
    T QueryRange(size_t l, size_t r)
    {
        return op_decombine(Query(r), Query(l - 1));
    }
    T RangeUpdate(size_t l, size_t r, T v)
    {
        Update(l, v);
        Update(r + 1, op_decombine(0, v));
    }
    size_t BinarySearch(T v)
    {
        T sum = 0;
        size_t pos = 0;
        for (int i = LOGN; i >= 0; i--)
        {
            if (pos + (1 << i) >= sz)
                continue;
            T newSum = op_combine(sum, tr[pos + (1 << i)]);
            if (less(newSum, v))
            {
                sum = newSum;
                pos += (1 << i);
            }
        }
        return pos + 1;
    }
};
} // namespace library
#endif
#ifndef FenwickTreeRangeSum_h
#define FenwickTreeRangeSum_h 1
namespace library
{
template <typename T, size_t sz> class FenwickTreeRangeSum
{
  private:
    FenwickTree<T, sz> ft1;
    FenwickTree<T, sz> ft2;
  public:
    FenwickTreeRangeSum()
    {
        Reset();
    }
    void Reset()
    {
        ft1.Reset();
        ft2.Reset();
    }
    void Update(size_t x, T v)
    {
        RangeUpdate(x, x, v);
    }
    void RangeUpdate(size_t l, size_t r, T v)
    {
        ft1.Update(l, v);
        ft1.Update(r + 1, -v);
        ft2.Update(l, v * (l - 1));
        ft2.Update(r + 1, -v * r);
    }
    T Query(size_t x)
    {
        return ft1.Query(x) * x - ft2.Query(x);
    }
    T QueryRange(size_t l, size_t r)
    {
        return Query(r) - Query(l - 1);
    }
    T QueryPoint(size_t x)
    {
        return QueryRange(x, x);
    }
};
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int sz = 2e5 + 105;
int t, n, m;
char s[sz];
library::FenwickTreeRangeSum<int, sz> ft_two;
library::FenwickTreeRangeSum<int, sz> ft_three;
library::FenwickTreeRangeSum<int, sz> st;
int type, l, r, x;
int query(int x)
{
    return st.QueryPoint(x) % 26;
}
void print()
{
    for (int i = 1; i <= n; ++i)
    {
        cout << (char)(query(i) + 'a');
    }
    cout << endl;
}
void Solve()
{
    scanf("%d", &t);
    while (t-- && scanf("%d %d", &n, &m) == 2)
    {
        scanf("%s", s + 1);
        ft_two.Reset();
        ft_three.Reset();
        st.Reset();
        for (int i = 1; i <= n; ++i)
        {
            st.Update(i, s[i] - 'a');
            if (i + 1 <= n && s[i] == s[i + 1])
            {
                ft_two.RangeUpdate(i, i + 1, 1);
            }
            if (i + 2 <= n && s[i] == s[i + 2])
            {
                ft_three.RangeUpdate(i, i + 2, 1);
            }
        }
        while (m--)
        {
            scanf("%d", &type);
            if (type == 1)
            {
                scanf("%d %d %d", &l, &r, &x);
                x %= 26;
                if (x == 0)
                {
                    continue;
                }
                for (int i = max(1, l - 5); i <= min(l + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, -1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, -1);
                    }
                }
                for (int i = max(1, r - 5); i <= min(r + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, -1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, -1);
                    }
                }
                st.RangeUpdate(l, r, x);
                for (int i = max(1, l - 5); i <= min(l + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, 1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, 1);
                    }
                }
                for (int i = max(1, r - 5); i <= min(r + 5, n); i++)
                {
                    if (i + 1 <= n && query(i) == query(i + 1))
                    {
                        ft_two.RangeUpdate(i, i + 1, 1);
                    }
                    if (i + 2 <= n && query(i) == query(i + 2))
                    {
                        ft_three.RangeUpdate(i, i + 2, 1);
                    }
                }
            }
            else
            {
                scanf("%d %d", &l, &r);
                int ans = 0;
                if (l + 1 <= r && !ans)
                {
                    ans += query(l) == query(l + 1);
                }
                if (l <= r - 1 && !ans)
                {
                    ans += query(r - 1) == query(r);
                }
                if (l + 1 <= r - 1 && !ans)
                {
                    ans += ft_two.QueryRange(l + 1, r - 1);
                }
                if (l + 2 <= r && !ans)
                {
                    ans += query(l) == query(l + 2);
                }
                if (l <= r - 2 && !ans)
                {
                    ans += query(r - 2) == query(r);
                }
                if (l + 2 <= r - 2 && !ans)
                {
                    ans += ft_three.QueryRange(l + 2, r - 2);
                }
                if (ans > 0)
                {
                    printf("NO\n");
                }
                else
                {
                    printf("YES\n");
                }
            }
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
