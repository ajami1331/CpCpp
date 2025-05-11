#ifndef AhoCorasick_h
#define AhoCorasick_h 1

#include "Common.h"

namespace library {
template <size_t MAXLEN, size_t AC_ALPHABET_SIZE = 26>
struct AhoCorasick {
  vector<int> mark[MAXLEN + 7];
  int state, failure[MAXLEN + 7];
  int trie[MAXLEN + 7][AC_ALPHABET_SIZE];

  AhoCorasick() { Init(); }

  void Init() {
    mark[0].clear();
    fill(trie[0], trie[0] + AC_ALPHABET_SIZE, -1);
    state = 0;
  }

  int Value(char c) { return c - 'a'; }

  void Add(char* s, int t) {
    int root = 0, id;
    for (int i = 0; s[i]; i++) {
      id = Value(s[i]);
      if (trie[root][id] == -1) {
        trie[root][id] = ++state;
        mark[state].clear();
        fill(trie[state], trie[state + 1] + AC_ALPHABET_SIZE, -1);
      }
      root = trie[root][id];
    }
    mark[root].emplace_back(t);
  }

  void ComputeFailure() {
    queue<int> Q;
    failure[0] = 0;
    for (int i = 0; i < AC_ALPHABET_SIZE; i++) {
      if (trie[0][i] != -1) {
        failure[trie[0][i]] = 0;
        Q.push(trie[0][i]);
      } else
        trie[0][i] = 0;
    }
    while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      for (int v : mark[failure[u]]) mark[u].emplace_back(v);
      for (int i = 0; i < AC_ALPHABET_SIZE; i++) {
        if (trie[u][i] != -1) {
          failure[trie[u][i]] = trie[failure[u]][i];
          Q.push(trie[u][i]);
        } else
          trie[u][i] = trie[failure[u]][i];
      }
    }
  }
};

}  // namespace library

#endif