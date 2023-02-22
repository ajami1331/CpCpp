#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#ifndef SegmentTree_h
#define SegmentTree_h 1
namespace library
{
template <typename T, size_t sz, T identityElem> class SegmentTree
{
  private:
    T tr[sz * 4];
    std::function<T(T, T)> combine;

  public:
    SegmentTree()
    {
        Reset();
    }
    SegmentTree(std::function<T(T, T)> combine) : SegmentTree()
    {
        SetCombine(combine);
    }
    ~SegmentTree()
    {
    }
    void SetCombine(std::function<T(T, T)> combine)
    {
        this->combine = combine;
    }
    void Reset()
    {
        std::fill(tr, tr + sz * 4, identityElem);
    }
    inline void Build(int node, int b, int e, T *arr)
    {
        if (b == e)
        {
            tr[node] = arr[b];
            return;
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (b + e) >> 1;
        Build(left, b, mid, arr);
        Build(right, mid + 1, e, arr);
        tr[node] = this->combine(tr[left], tr[right]);
    }
    inline void Update(int node, int b, int e, int idx, T x)
    {
        if (b == e)
        {
            tr[node] = x;
            return;
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (b + e) >> 1;
        if (idx <= mid)
            Update(left, b, mid, idx, x);
        else
            Update(right, mid + 1, e, idx, x);
        tr[node] = this->combine(tr[left], tr[right]);
    }
    inline T Query(int node, int b, int e, int l, int r)
    {
        if (r < b || e < l)
            return identityElem;
        if (b >= l && e <= r)
        {
            return tr[node];
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (b + e) >> 1;
        T p1 = Query(left, b, mid, l, r);
        T p2 = Query(right, mid + 1, e, l, r);
        return this->combine(p1, p2);
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
library::SegmentTree<ll, sz, 0LL> seg_tree([](ll x, ll y) { return x + y; });
int n, q;
ll ar[sz];
void Solve()
{
    cin >> n >> q;
    seg_tree.Reset();
    for (int i = 0; i < n; i++)
    {
        cin >> ar[i];
    }
    seg_tree.Build(1, 0, n - 1, ar);
    while (q--)
    {
        int x, y;
        cin >> x >> y;
        cout << seg_tree.Query(1, 0, n - 1, x, y - 1) << "\n";
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
