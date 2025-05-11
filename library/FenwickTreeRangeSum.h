#ifndef FenwickTreeRangeSum_h
#define FenwickTreeRangeSum_h 1

#include "FenwickTree.h"

namespace library {
template <typename T, size_t sz>
class FenwickTreeRangeSum {
 private:
  FenwickTree<T, sz> ft1;
  FenwickTree<T, sz> ft2;

 public:
  FenwickTreeRangeSum() { Reset(); }

  void Reset() {
    ft1.Reset();
    ft2.Reset();
  }

  void Update(size_t x, T v) { RangeUpdate(x, x, v); }

  void RangeUpdate(size_t l, size_t r, T v) {
    ft1.Update(l, v);
    ft1.Update(r + 1, -v);
    ft2.Update(l, v * (l - 1));
    ft2.Update(r + 1, -v * r);
  }

  T Query(size_t x) { return ft1.Query(x) * x - ft2.Query(x); }

  T QueryRange(size_t l, size_t r) { return Query(r) - Query(l - 1); }

  T QueryPoint(size_t x) { return QueryRange(x, x); }
};
}  // namespace library

#endif