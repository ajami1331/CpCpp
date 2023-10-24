#ifndef LAZY_SEGMENT_TREE_H
#define LAZY_SEGMENT_TREE_H 1

#include <algorithm>
#include <functional>


namespace library
{
#if __cplusplus >= 201703L
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id, size_t sz> class LazySegmentTree
{
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>, "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>, "e must work as S()");
    static_assert(std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>, "mapping must work as S(F, S)");
    static_assert(std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
                  "compostiion must work as F(F, F)");
    static_assert(std::is_convertible_v<decltype(id), std::function<F()>>, "id must work as F()");

#else

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)(), size_t sz>
class LazySegmentTree
{

#endif
  private:
    S tree[sz * 4];
    F lazy[sz * 4];

  public:
    LazySegmentTree()
    {
        Reset();
    }
    
    void Reset()
    {
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
        }
        int left = node << 1;
        int right = left | 1;
        int mid = (begin + end) >> 1;
        Build(left, begin, mid);
        Build(right, mid + 1, end);
        tree[node] = op(tree[left], tree[right]);
    }

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