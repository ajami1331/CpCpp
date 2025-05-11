#ifndef solution_h
#define solution_h 1

#include "library/Common.h"
#include "library/Debug.h"

namespace solution {
const int sz = 2e5 + 105;
const int mod = 1e9 + 7;
const ll INF = 1e16;

bool is_regular(const string& s) {
  int cnt = 0;
  for (char c : s) {
    if (c == '(')
      cnt++;
    else
      cnt--;
    if (cnt < 0) return false;
  }
  return cnt == 0;
}

bool is_beautiful(string s) {
  if (is_regular(s)) return true;
  reverse(all(s));
  return is_regular(s);
}

void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    string s;
    cin >> n >> s;
    if (is_beautiful(s)) {
      printf("1\n1");
      for (int i = 1; i < n; i++) {
        printf(" 1");
      }
      printf("\n");
      continue;
    }
    int cnt = 0;
    vector<int> ans;
    int color = 0;
    for (char c : s) {
      if (cnt == 0) color = c == ')';
      if (c == '(')
        cnt++;
      else
        cnt--;
      ans.push_back(color);
    }
    string part1, part2;
    for (int i = 0; i < n; i++) {
      if (ans[i] == 0)
        part1.push_back(s[i]);
      else
        part2.push_back(s[i]);
    }
    if (is_beautiful(part1) && is_beautiful(part2)) {
      printf("2\n");
      for (int i = 0; i < n; i++) {
        printf("%d ", ans[i] + 1);
      }
      printf("\n");
    } else {
      printf("-1\n");
    }
  }
}

}  // namespace solution

#endif  // solution_h
