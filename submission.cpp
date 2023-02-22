#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <numeric>
#ifndef FenwickTree_h
#define FenwickTree_h 1
namespace library
{
template <typename T, size_t sz, typename op_combine_type = std::plus<T>, typename op_decombine_type = std::minus<T>,
          typename less_type = std::less<T>>
class FenwickTree
{
  private:
    T tr[sz];
    int LOGN = std::__lg(sz);
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
    /// @brief: Only works with point updates
    T QueryRange(size_t l, size_t r)
    {
        return op_decombine(Query(r), Query(l - 1));
    }
    /// @brief: Only works with point queries
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
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
const int sz = 5e5 + 10;
using ll = long long;
library::FenwickTree<ll, sz> ft;
int n, q;
ll ar[sz];
void Solve()
{
    cin >> n >> q;
    ft.Reset();
    for (int i = 0; i < n; i++)
    {
        cin >> ar[i];
        ft.Update(i + 1, ar[i]);
    }
    while (q--)
    {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 0)
            ft.Update(x + 1, y);
        else if (type == 1)
            cout << ft.QueryRange(x + 1, y) << "\n";
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
