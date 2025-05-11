#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"
#ifndef solution_h
#define solution_h 1

#include "../library/DisjointSet.h"

namespace solution {
using namespace std;
const int sz = 2e5 + 10;
library::DisjointSet<sz> dsu;
void Solve() {
  int n, q;
  cin >> n >> q;
  dsu.Resize(n);
  while (q--) {
    int t, a, b;
    cin >> t >> a >> b;
    if (!t) {
      dsu.MergeSet(a, b);
    } else {
      cout << dsu.IsSameSet(a, b) << "\n";
    }
  }
}
}  // namespace solution
#endif

int main(int argc, char* argv[]) {
  solution::Solve();
  return 0;
}