#ifndef COMMON_H
#define COMMON_H 1
#include <algorithm>
#include <cassert>
#include <chrono>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define szx(x) (int)(x).size()
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
constexpr int LOG2(int x) { return 32 - __builtin_clz(x) - 1; }
#endif  // COMMON_H
#ifndef ATCODER_DSU_HPP
#define ATCODER_DSU_HPP 1
#include <algorithm>
#include <cassert>
#include <vector>
namespace atcoder {
struct dsu {
 public:
  dsu() : _n(0) {}
  explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}
  int merge(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    int x = leader(a), y = leader(b);
    if (x == y) return x;
    if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
    parent_or_size[x] += parent_or_size[y];
    parent_or_size[y] = x;
    return x;
  }
  bool same(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    return leader(a) == leader(b);
  }
  int leader(int a) {
    assert(0 <= a && a < _n);
    if (parent_or_size[a] < 0) return a;
    return parent_or_size[a] = leader(parent_or_size[a]);
  }
  int size(int a) {
    assert(0 <= a && a < _n);
    return -parent_or_size[leader(a)];
  }
  std::vector<std::vector<int>> groups() {
    std::vector<int> leader_buf(_n), group_size(_n);
    for (int i = 0; i < _n; i++) {
      leader_buf[i] = leader(i);
      group_size[leader_buf[i]]++;
    }
    std::vector<std::vector<int>> result(_n);
    for (int i = 0; i < _n; i++) {
      result[i].reserve(group_size[i]);
    }
    for (int i = 0; i < _n; i++) {
      result[leader_buf[i]].push_back(i);
    }
    result.erase(
        std::remove_if(result.begin(), result.end(),
                       [&](const std::vector<int>& v) { return v.empty(); }),
        result.end());
    return result;
  }
 private:
  int _n;
  std::vector<int> parent_or_size;
};
}  // namespace atcoder
#endif  // ATCODER_DSU_HPP
#ifndef DEBUG_H
#define DEBUG_H 1
#ifndef CLown1331
#define debug(...) 0
#define ASSERT(...) 0
#define dbg(...) 0
#endif
#endif  // DEBUG_H
#ifndef solution_h
#define solution_h 1
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
#define _CRT_SECURE_NO_WARNINGS
int main() {
  solution::solve();
  return 0;
}
