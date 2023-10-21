#ifndef FenwickTree_h
#define FenwickTree_h 1
#include <cstring>
#include <functional>
#include <numeric>
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
    void RangeUpdate(size_t l, size_t r, T v)
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
namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;
const int sz = 2e5 + 105;
int t, n, m;
char s[sz];
int type, l, r, x;
struct mod_plus : public binary_function<int, int, int>
{
    int operator()(const int &x, const int &y) const
    {
        return (x + y) % 26;
    }
};
struct mod_minus : public binary_function<int, int, int>
{
    int operator()(const int &x, const int &y) const
    {
        return (x - y + 26) % 26;
    }
};
library::FenwickTree<int, sz, mod_plus, mod_minus> ft;
set <int> two, three;
void push(int l, int r)
{
    l = max(l, 1);
    r = min(r, n);
    for (int i = l; i <= r; ++i)
    {
        if (i + 1 <= n && ft.Query(i) == ft.Query(i + 1))
        {
            two.insert(i);
        }
        else
        {
            two.erase(i);
        }
        if (i + 2 <= n && ft.Query(i) == ft.Query(i + 2))
        {
            three.insert(i);
        }
        else
        {
            three.erase(i);
        }
    }
}
void print()
{
    for (int i = 1; i <= n; ++i)
    {
        printf("%c", ft.Query(i) + 'a');
    }
    printf("\n");
}
void Solve()
{
    scanf("%d", &t);
    while (t-- && scanf("%d %d", &n, &m) == 2)
    {
        s[0] = 0;
        scanf("%s", s + 1);
        ft.Reset();
        two.clear();
        three.clear();
        for (int i = 1; i <= n; ++i)
        {
            ft.Update(i, s[i] - s[i - 1] + 26);
            if (i + 1 <= n && s[i] == s[i + 1])
            {
                two.insert(i);
            }
            if (i + 2 <= n && s[i] == s[i + 2])
            {
                three.insert(i);
            }
        }
        while (m--)
        {
            scanf("%d", &type);
            if (type == 1)
            {
                scanf("%d %d %d", &l, &r, &x);
                x %= 26;
                ft.RangeUpdate(l, r, x);
                push(l - 5, l + 5);
                push(r - 5, r + 5);
            }
            else
            {
                scanf("%d %d", &l, &r);
                int ans = 0;
                auto it = two.lower_bound(l);
                if (it != two.end() && *it + 1 <= r)
                {
                    ans = 1;
                }
                else
                {
                    it = three.lower_bound(l);
                    if (it != three.end() && *it + 2 <= r)
                    {
                        ans = 1;
                    }
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
int main()
{
    solution::Solve();
    return 0;
}
