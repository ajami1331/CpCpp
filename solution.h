#ifndef solution_h
#define solution_h 1

#include "library/Common.h"
#include "library/Debug.h"

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
