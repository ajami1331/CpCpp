#include <bits/stdc++.h>

using namespace std;

int main() {
  mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
  int t = 1;
  cout << t << endl;
  while (t--) {
    int n = rng() % 10 + 1;
    cout << n << endl;
    for (int i = 0; i < n; i++) {
      cout << char(rng() % 26 + 'a');
    }
    cout << endl;
  }
  return 0;
}