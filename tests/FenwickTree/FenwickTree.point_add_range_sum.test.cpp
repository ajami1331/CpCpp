#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#ifndef solution_h
#define solution_h 1

#include "../../library/FenwickTree.h"

namespace solution {
using namespace std;
const int sz = 5e5 + 10;
using ll = long long;

library::FenwickTree<ll, sz> ft;
int n, q;
ll ar[sz];

void Solve() {
  cin >> n >> q;
  ft.Reset();
  for (int i = 0; i < n; i++) {
    cin >> ar[i];
    ft.Update(i + 1, ar[i]);
  }

  while (q--) {
    int type, x, y;
    cin >> type >> x >> y;
    if (type == 0)
      ft.Update(x + 1, y);
    else if (type == 1)
      cout << ft.QueryRange(x + 1, y) << "\n";
  }
}
}  // namespace solution
#endif

int main(int argc, char* argv[]) {
  solution::Solve();
  return 0;
}