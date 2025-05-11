#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#ifndef solution_h
#define solution_h 1

#include "../../library/SegmentTree.h"

namespace solution {
using namespace std;
const int sz = 5e5 + 10;
using ll = long long;

library::SegmentTree<ll, sz, 0LL> seg_tree([](ll x, ll y) { return x + y; });
int n, q;
ll ar[sz];

void Solve() {
  cin >> n >> q;
  seg_tree.Reset();
  for (int i = 0; i < n; i++) {
    cin >> ar[i];
  }

  seg_tree.Build(1, 0, n - 1, ar);

  while (q--) {
    int type, x, y;
    cin >> type >> x >> y;
    if (type == 0) {
      ar[x] += y;
      seg_tree.Update(1, 0, n - 1, x, ar[x]);
    } else {
      cout << seg_tree.Query(1, 0, n - 1, x, y - 1) << "\n";
    }
  }
}
}  // namespace solution
#endif

int main(int argc, char* argv[]) {
  solution::Solve();
  return 0;
}