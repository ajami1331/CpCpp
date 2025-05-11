/// src:
/// https://github.com/sgtlaugh/algovault/blob/master/code_library/hashing.cpp
#ifndef PolyHash_h
#define PolyHash_h 1

#include "Common.h"

// #define IMPLEMENT_REV_HASH

namespace library {

constexpr unsigned long long mod = (1ULL << 61) - 1;

const unsigned long long seed =
    chrono::system_clock::now().time_since_epoch().count();
const unsigned long long polyhash_base =
    mt19937_64(seed)() % (mod / 3) + (mod / 3);

long long ModMul(unsigned long long a, unsigned long long b) {
  unsigned long long l1 = (unsigned int)a, h1 = a >> 32, l2 = (unsigned int)b,
                     h2 = b >> 32;
  unsigned long long l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
  unsigned long long ret =
      (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
  ret = (ret & mod) + (ret >> 61);
  ret = (ret & mod) + (ret >> 61);
  return ret - 1;
}

template <size_t MAXLEN>
struct PolyHash {
  vector<long long> pref;
/// Removes the suff vector and usage if reverse hash is not required for more
/// speed
#ifdef IMPLEMENT_REV_HASH
  vector<long long> suff;
#endif
  inline static unsigned long long polyhash_base_pow[MAXLEN];

  PolyHash() {}

  template <typename T>
  PolyHash(const vector<T>& ar) {
    if (!polyhash_base_pow[0]) init();

    int n = ar.size();
    assert(n < MAXLEN);
    pref.resize(n + 3, 0);

    for (int i = 1; i <= n; i++) {
      pref[i] = ModMul(pref[i - 1], polyhash_base) + ar[i - 1] + 997;
      if (pref[i] >= mod) pref[i] -= mod;
    }

#ifdef IMPLEMENT_REV_HASH
    suff.resize(n + 3, 0);
    for (int i = n; i >= 1; i--) {
      suff[i] = ModMul(suff[i + 1], polyhash_base) + ar[i - 1] + 997;
      if (suff[i] >= mod) suff[i] -= mod;
    }
#endif
  }

  PolyHash(const char* str) : PolyHash(vector<char>(str, str + strlen(str))) {}

  unsigned long long GetHash(int l, int r) {
    long long h = pref[r + 1] - ModMul(polyhash_base_pow[r - l + 1], pref[l]);
    return h < 0 ? h + mod : h;
  }

#ifdef IMPLEMENT_REV_HASH
  unsigned long long ReverseHash(int l, int r) {
    long long h =
        suff[l + 1] - ModMul(polyhash_base_pow[r - l + 1], suff[r + 2]);
    return h < 0 ? h + mod : h;
  }
#endif

  unsigned long long GetHash(int l, int r, int x, int y) {
    return (ModMul(GetHash(l, r), polyhash_base_pow[y - x + 1]) +
            GetHash(x, y)) %
           mod;
  }

  void init() {
    polyhash_base_pow[0] = 1;
    for (int i = 1; i < MAXLEN; i++) {
      polyhash_base_pow[i] = ModMul(polyhash_base_pow[i - 1], polyhash_base);
    }
  }
};
}  // namespace library

#endif
