#ifndef FastIO_h
#define FastIO_h 1

namespace library {
template <typename T>
inline T ReadInt() {
  T ret = 0, flag = 1, ip = getchar();
  for (; ip < 48 || ip > 57; ip = getchar()) {
    if (ip == 45) {
      flag = -1;
      ip = getchar();
      break;
    }
  }
  for (; ip > 47 && ip < 58; ip = getchar()) ret = ret * 10 + ip - 48;
  return flag * ret;
}

static const int buf_size = 4096;

inline int GetChar() {
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len) pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len) return -1;
  return buf[pos++];
}

inline int ReadChar() {
  int c = GetChar();
  while (c <= 32) c = GetChar();
  return c;
}

template <typename T>
inline T ReadIntBuffered() {
  int s = 1, c = ReadChar();
  T x = 0;
  if (c == '-') s = -1, c = GetChar();
  while ('0' <= c && c <= '9') x = x * 10 + c - '0', c = GetChar();
  return s == 1 ? x : -x;
}

}  // namespace library

#endif