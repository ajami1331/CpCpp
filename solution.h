#ifndef solution_h
#define solution_h 1

#include <cstdio>
#include <cstring>
#include <iostream>
#include "library/FastIO.h"
#include "library/SparseTable.h"
// #include "library/LCA.h"

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