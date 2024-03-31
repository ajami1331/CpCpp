#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <utility>
#include <vector>
#include "library/Debug.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = long long;
const int sz = 2e5 + 105;
struct Solution
{
    int t;

    void Solve()
    {
        cin >> t;
        string s;
        while (t-- && cin >> s)
        {
            string ans = "";
            ans.push_back(s.front());
            for (int i = 1; i + 1 < s.size(); i += 2)
            {
                ans.push_back(s[i]);
            }
            ans.push_back(s.back());
            cout << ans << "\n";
        }
    }
};

} // namespace solution

#endif // solution_h
