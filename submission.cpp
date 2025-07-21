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
  int t, n;
  cin >> t;
  while (t-- && cin >> n) {
    vector<int> ar(n);
    for (int& x : ar) {
      cin >> x;
    }
    set<int> st;
    for (int& x : ar) {
      while (x % 10 != 0 && x % 10 != 2) {
        x += x % 10;
      }
      st.insert(x);
    }
    if (st.size() == 1) {
      cout << "Yes\n";
      continue;
    }
    st.clear();
    for (int x : ar) {
      if (x % 10 == 0) {
        st.insert(x);
      } else {
        st.insert(x % 20);
      }
    }
    if (st.size() == 1) {
      cout << "Yes\n";
      continue;
    }
    cout << "No\n";
  }
}
}  // namespace solution
#endif  // solution_h
#define _CRT_SECURE_NO_WARNINGS
int main() {
  solution::solve();
  return 0;
}
