#ifndef Math_h
#define Math_h 1

namespace library {
template <long long mod>
long long ModuloPower(long long b, long long p) {
  long long ret = 1;
  for (; p > 0; p >>= 1) {
    if (p & 1) ret = (ret * b) % mod;
    b = (b * b) % mod;
  }
  return ret % mod;
}

template <long long mod>
long long ModuloInverse(long long b) {
  return ModuloPower<mod>(b, mod - 2);
}

}  // namespace library

#endif