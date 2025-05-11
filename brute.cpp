#ifndef COMMON_H
#define COMMON_H 1
#include <algorithm>
#include <cassert>
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
int t, n;
char s[sz];
void solve_case() {
  scanf("%d", &n);
  scanf("%s", s);
  int ans = 0;
  if (n & 1) {
    map<char, int> mp[2];
    for (int i = 0; i < n; i++) {
      mp[i & 1][s[i]]++;
    }
    map<char, int> np[2];
    ans = n;
    for (int i = 0; i < n; i++) {
      mp[i & 1][s[i]]--;
      int cur_ans = 1;
      for (int j = 0; j < 2; j++) {
        int mx = 0;
        for (char c = 'a'; c <= 'z'; c++) {
          mx = max(mx, mp[j][c] + np[j ^ 1][c]);
        }
        cur_ans += n / 2 - mx;
      }
      np[i & 1][s[i]]++;
      ans = min(ans, cur_ans);
    }
  } else {
    map<char, int> mp[2];
    for (int i = 0; i < n; i++) {
      mp[i & 1][s[i]]++;
    }
    for (int i = 0; i < 2; i++) {
      int mx = 0;
      for (auto& x : mp[i]) {
        mx = max(mx, x.second);
      }
      ans += n / 2 - mx;
    }
  }
  printf("%d\n", ans);
}
void solve() {
  scanf("%d", &t);
  while (t--) {
    solve_case();
  }
}
}  // namespace solution
#endif  // solution_h
#define _CRT_SECURE_NO_WARNINGS
int main() {
  solution::solve();
  return 0;
}
