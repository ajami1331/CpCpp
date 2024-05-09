#ifndef solution_h
#define solution_h 1

#include "library/Common.h"
#include "library/Debug.h"

namespace solution
{
const int sz = 3e5 + 105;
const int mod = 1e9 + 7;
const ll max_possible = 1LL * sz * mod;
int t;
int n;
vector <int> perfect_squares;
int dp[sz];

void solve_case()
{
    scanf("%d", &n);
    printf("%d\n", dp[n] > n ? -1 : dp[n]);
}

void solve()
{
    for (int i = 1; i * i <= sz; i++)
    {
        perfect_squares.push_back(i * i);
    }
    dp[0] = 0;
    fill(dp + 1, dp + sz, mod);
    for (int j = 0; j < perfect_squares.size(); j++)
    {
        for (int i = sz - 1; i >= perfect_squares[j]; i--)
        {
            dp[i] = min(dp[i], dp[i - perfect_squares[j]] + 1);
        }
    }
    scanf("%d", &t);
    while (t--)
    {
        solve_case();
    }
}

} // namespace solution

#endif // solution_h
