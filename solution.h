#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>
#include <utility>
#include "library/KnuthMorrisPrattMatcher.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 1e6 + 10;
int n;
char s[sz];

void Solve()
{
    int cs = 0;
    while (cin >> n && n > 0)
    {
        cin >> s;
        KnuthMorrisPrattMatcher<sz> matcher;
        matcher.Init(s, n);
        cout << "Test case #" << (++cs) << "\n";
        for (int i = 0; i < n; i++)
        {
            int len = i + 1 - matcher.table[i];
            if ((i + 1) % len == 0 && (i + 1) / len > 1)
            {
                cout << (i + 1) << " " << (i + 1) / len << "\n";
            }
        }
        cout << "\n";
    }
}

} // namespace solution
#endif