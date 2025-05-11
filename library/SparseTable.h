#ifndef SparseTable_h
#define SparseTable_h 1

#include "Common.h"

namespace library {
#define LOG2(x) (32 - __builtin_clz(x) - 1)
template <typename T>
struct SparseTable {
  int n;
  int log2n;
  function<T(T, T)> combine;
  vector<T> table[32];

  SparseTable() {}

  SparseTable(T* arr, int len, function<T(T, T)> combine)
      : SparseTable(arr, len) {
    this->combine = combine;
  }

  SparseTable(T* arr, int len) : SparseTable(vector<T>(arr, arr + len)) {}

  SparseTable(const vector<T>& arr, function<T(T, T)> combine)
      : SparseTable(arr) {
    this->combine = combine;
  }

  SparseTable(const vector<T>& arr) {
    n = arr.size();
    log2n = LOG2(n) + 1;
    table[0] = arr;
    for (int i = 1; i < log2n; ++i) {
      table[i].resize(n - (1 << i) + 1);
      for (int j = 0; j + (1 << i) <= n; j++) {
        int x = table[i - 1][j];
        int y = table[i - 1][j + (1 << (i - 1))];
        table[i][j] = Combine(x, y);
      }
    }
  }

  T Combine(T x, T y) {
    if (this->combine != nullptr) return this->combine(x, y);
    return min(x, y);
  }

  T Query(int l, int r) {
    int k = LOG2(r - l + 1);
    int x = table[k][l];
    int y = table[k][r - (1 << k) + 1];
    return Combine(x, y);
  }
};
}  // namespace library

#endif