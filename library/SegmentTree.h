#ifndef SegmentTree_h
#define SegmentTree_h 1

#include <algorithm>
#include <functional>

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