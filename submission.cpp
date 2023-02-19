#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>
#ifndef SparseTable_h
#define SparseTable_h 1
namespace library
{
#define LOG2(x) (32 - __builtin_clz(x) - 1)
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
        log2n = LOG2(n) + 1;
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
        int k = LOG2(r - l + 1);
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
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &ar[i]);
    }
    library::SparseTable<int> st(ar, n);
    while (q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", st.Query(u, v - 1));
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
