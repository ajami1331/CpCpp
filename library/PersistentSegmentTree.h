#ifndef PersistentSegmentTree_h
#define PersistentSegmentTree_h 1

#include "Common.h"

namespace library {

template <typename T, size_t sz>
class PersistentSegmentTree {
 private:
  int nxt = 0;
  struct node {
    size_t left;
    size_t right;
    T val;
  } nodes[sz * 32];
  function<T(T, T)> combine;
  function<T(T, T)> replace;

  size_t UpdateInternal(size_t node_idx, int l, int r, int idx, T x) {
    auto& cur_node = nodes[node_idx];
    if (r < idx || idx < l) {
      return node_idx;
    }
    if (l == r) {
      size_t n_node_idx = ++nxt;
      auto& n_node = nodes[n_node_idx];
      n_node.val = this->replace(cur_node.val, x);
      n_node.left = cur_node.left;
      n_node.right = cur_node.right;
      return n_node_idx;
    }
    int mid = (l + r) >> 1;
    size_t n_node_idx = ++nxt;
    auto& n_node = nodes[n_node_idx];
    n_node.val = cur_node.val;
    n_node.left = UpdateInternal(cur_node.left, l, mid, idx, x);
    n_node.right = UpdateInternal(cur_node.right, mid + 1, r, idx, x);
    auto& n_node_left = nodes[n_node.left];
    auto& n_node_right = nodes[n_node.right];
    n_node.val = combine(n_node_left.val, n_node_right.val);
    return n_node_idx;
  }

  void BuildInternal(size_t node_idx, int l, int r, T defaultValue) {
    auto& cur_node = nodes[node_idx];
    if (l == r) {
      cur_node.val = defaultValue;
      return;
    }
    int mid = (l + r) >> 1;
    cur_node.left = ++nxt;
    cur_node.right = ++nxt;
    size_t left_idx = cur_node.left;
    size_t right_idx = cur_node.right;
    BuildInternal(left_idx, l, mid, defaultValue);
    BuildInternal(right_idx, mid + 1, r, defaultValue);
    auto& node_left = nodes[left_idx];
    auto& node_right = nodes[right_idx];
    cur_node.val = combine(node_left.val, node_right.val);
  }

  void BuildInternal(size_t node_idx, int l, int r, T* arr) {
    auto& cur_node = nodes[node_idx];
    if (l == r) {
      cur_node.val = arr[l];
      return;
    }
    int mid = (l + r) >> 1;
    cur_node.left = ++nxt;
    cur_node.right = ++nxt;
    size_t left_idx = cur_node.left;
    size_t right_idx = cur_node.right;
    BuildInternal(left_idx, l, mid, arr);
    BuildInternal(right_idx, mid + 1, r, arr);
    auto& node_left = nodes[left_idx];
    auto& node_right = nodes[right_idx];
    cur_node.val = combine(node_left.val, node_right.val);
  }

 public:
  vector<size_t> roots;

  PersistentSegmentTree(
      function<T(T, T)> combine = [](T a, T b) { return a + b; },
      function<T(T, T)> replace = [](T a, T b) { return a + b; }) {
    SetCombine(combine);
    SetReplace(replace);
    Reset();
  }

  ~PersistentSegmentTree() {}

  void SetCombine(function<T(T, T)> combine) { this->combine = combine; }

  void SetReplace(function<T(T, T)> replace) { this->replace = replace; }

  void Reset() {
    nxt = 0;
    roots.clear();
  }

  size_t Build(int l, int r, T defaultValue) {
    Reset();
    roots.emplace_back(++nxt);
    BuildInternal(roots.back(), l, r, defaultValue);
    return roots.back();
  }

  size_t Build(int l, int r, T* arr) {
    Reset();
    roots.emplace_back(++nxt);
    BuildInternal(roots.back(), l, r, arr);
    return roots.back();
  }

  size_t Update(size_t node_idx, int l, int r, int idx, T x) {
    roots.emplace_back(UpdateInternal(node_idx, l, r, idx, x));
    return roots.back();
  }

  T Query(size_t node_idx, int l, int r, int i, int j) {
    auto& cur_node = nodes[node_idx];
    if (r < i || l > j) {
      return 0;
    }
    if (i <= l && r <= j) {
      return cur_node.val;
    }
    int mid = (l + r) >> 1;
    return combine(Query(cur_node.left, l, mid, i, j),
                   Query(cur_node.right, mid + 1, r, i, j));
  }
};
}  // namespace library
#endif