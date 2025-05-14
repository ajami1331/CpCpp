#ifndef solution_h
#define solution_h 1

#include "atcoder/dsu.hpp"
#include "library/Common.h"
#include "library/Debug.h"
namespace solution {
const int sz = 2e5 + 105;
const int mod = 1e9 + 7;
const ll INF = 1e16;

void solve() {
  int n;
  std::ignore = scanf("%d", &n);
  atcoder::dsu ds(n);
  for (int i = 0; i < n; ++i) {
    int x;
    std::ignore = scanf("%d", &x);
    ds.merge(i, x - 1);
  }
  printf("%d\n", static_cast<int>(ds.groups().size()));
}

}  // namespace solution

#endif  // solution_h
