#ifndef FenwickTree_h
#define FenwickTree_h 1

#include "Common.h"

namespace library
{
template <typename T, size_t sz, typename op_combine_type = plus<T>, typename op_decombine_type = minus<T>,
          typename less_type = less<T>>
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

    /// @brief: Only works with point updates
    T QueryRange(size_t l, size_t r)
    {
        return op_decombine(Query(r), Query(l - 1));
    }

    /// @brief: Only works with point queries
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