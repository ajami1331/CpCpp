#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>
#ifndef FastIO_h
#define FastIO_h 1
namespace library
{
template <typename T> inline T ReadInt()
{
    T ret = 0, flag = 1, ip = getchar();
    for (; ip < 48 || ip > 57; ip = getchar())
    {
        if (ip == 45)
        {
            flag = -1;
            ip = getchar();
            break;
        }
    }
    for (; ip > 47 && ip < 58; ip = getchar())
        ret = ret * 10 + ip - 48;
    return flag * ret;
}
static const int buf_size = 4096;
inline int GetChar()
{
    static char buf[buf_size];
    static int len = 0, pos = 0;
    if (pos == len)
        pos = 0, len = fread(buf, 1, buf_size, stdin);
    if (pos == len)
        return -1;
    return buf[pos++];
}
inline int ReadChar()
{
    int c = GetChar();
    while (c <= 32)
        c = GetChar();
    return c;
}
template <typename T> inline T ReadIntBuffered()
{
    int s = 1, c = ReadChar();
    T x = 0;
    if (c == '-')
        s = -1, c = GetChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = GetChar();
    return s == 1 ? x : -x;
}
} // namespace library
#endif
#ifndef Math_h
#define Math_h 1
namespace library
{
template <long long mod> long long ModuloPower(long long b, long long p)
{
    long long ret = 1;
    for (; p > 0; p >>= 1)
    {
        if (p & 1)
            ret = (ret * b) % mod;
        b = (b * b) % mod;
    }
    return ret % mod;
}
template <long long mod> long long ModuloInverse(long long b)
{
    return ModuloPower<mod>(b, mod - 2);
}
} // namespace library
#endif
#ifndef SparseTable_h
#define SparseTable_h 1
namespace library
{
template <typename T> struct SparseTable
{
    int n;
    int log2n;
    std::function<T(T, T)> combine;
    std::vector<T> table[32];
    SparseTable()
    {
    }
    SparseTable(T *arr, int len, std::function<T(T, T)> combine) : SparseTable(arr, len)
    {
        this->combine = combine;
    }
    SparseTable(T *arr, int len) : SparseTable(std::vector<T>(arr, arr + len))
    {
    }
    SparseTable(const std::vector<T> &arr, std::function<T(T, T)> combine) : SparseTable(arr)
    {
        this->combine = combine;
    }
    SparseTable(const std::vector<T> &arr)
    {
        n = arr.size();
        log2n = std::__lg(n) + 1;
        table[0] = arr;
        for (int i = 1; i < log2n; ++i)
        {
            table[i].resize(n - (1 << i) + 1);
            for (int j = 0; j + (1 << i) <= n; j++)
            {
                int x = table[i - 1][j];
                int y = table[i - 1][j + (1 << (i - 1))];
                table[i][j] = Combine(x, y);
            }
        }
    }
    T Combine(T x, T y)
    {
        if (this->combine != nullptr)
            return this->combine(x, y);
        return std::min(x, y);
    }
    T Query(int l, int r)
    {
        int k = std::__lg(r - l + 1);
        int x = table[k][l];
        int y = table[k][r - (1 << k) + 1];
        return Combine(x, y);
    }
};
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
const int sz = 5e5 + 10;
int ar[sz];
void Solve()
{
    int n, q;
    n = library::ReadInt<int>();
    q = library::ReadInt<int>();
    for (int i = 0; i < n; ++i)
    {
        ar[i] = library::ReadInt<int>();
    }
    library::SparseTable<int> st(ar, n);
    while (q--)
    {
        int u, v;
        u = library::ReadInt<int>();
        v = library::ReadInt<int>() - 1;
        printf("%d\n", st.Query(u, v));
    }
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
