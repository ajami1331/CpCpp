#ifndef solution_h
#define solution_h 1

#include "library/Common.h"
#include "library/Debug.h"

namespace solution
{
const int sz = 2e5 + 105;
const int mod = 1e9 + 7;
const ll INF = 1e16;
int t, n;
char s[sz];

void solve_case()
{
    scanf("%d", &n);
    scanf("%s", s);
    int ans = 0;
    if (n & 1)
    {
        map <char, int> mp[2];
        for (int i = 0; i < n; i++)
        {
            mp[i & 1][s[i]]++;
        }
        map <char, int> np[2];
        ans = n;
        for (int i = 0; i < n; i++)
        {
            mp[i & 1][s[i]]--;
            int cur_ans = 1;
            for (int j = 0; j < 2; j++)
            {
                int mx = 0;
                for (auto &x : mp[j])
                {
                    mx = max(mx, x.second + np[j ^ 1][x.first]);
                }
                cur_ans += n / 2 - mx;
            }
            np[i & 1][s[i]]++;
            ans = min(ans, cur_ans);
        }
    }
    else
    {
        map <char, int> mp[2];
        for (int i = 0; i < n; i++)
        {
            mp[i & 1][s[i]]++;
        }
        for (int i = 0; i < 2; i++)
        {
            int mx = 0;
            for (auto &x : mp[i])
            {
                mx = max(mx, x.second);
            }
            ans += n / 2 - mx;
        }
    }
    printf("%d\n", ans);
}
void solve()
{
    scanf("%d", &t);
    while (t--)
    {
        solve_case();
    }
}

} // namespace solution

#endif // solution_h
