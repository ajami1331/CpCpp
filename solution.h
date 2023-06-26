#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "library/PolyHash.h"
#include "library/SmallestStringRotation.h"

namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 1e4 + 10;
int n;
string s;
library::SmallestStringRotation<sz> ssr;
set <ull> st;

void Solve()
{
    scanf("%d", &n);
    while (n--)
    {
        cin >> s;
        ll ans = 0;
        st.clear();
        for (int i = 0; i < s.size(); i++)
        {
            string h;
            for (int j = i; j < s.size(); j++)
            {
                h += s[j];
                int rotation = ssr(h);
                string p = h;
                rotate(p.begin(), p.begin() + rotation, p.end());
                library::PolyHash<sz> ph(vector<char>(p.begin(), p.end()));
                ull hash = ph.GetHash(0, p.size() - 1);
                st.insert(hash);
            }
        }

        printf("%d\n", (int)st.size());
    }
}

} // namespace solution
#endif