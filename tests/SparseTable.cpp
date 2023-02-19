#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"
#ifndef solution_h
#define solution_h 1

#include "../library/SparseTable.h"
#include <cstdio>
#include <cstring>
#include <iostream>

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

int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}