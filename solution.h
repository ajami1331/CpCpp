#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
namespace solution
{
using namespace std;
using ll = long long;
using ull = unsigned long long;

const int sz = 2e5 + 105;
int t, n, m, k, h;
ll ar[sz];
bool mark[sz];

bool check_first()
{
    fill(mark, mark + n + 2, false);

    vector <ll> v;

    for (int i = 1; i + 1  < n; i++)
    {
        if (ar[i] - ar[i - 1] <= n) 
        {
            v.emplace_back(ar[i] - ar[i - 1]);
            mark[v.back()] = true;
        }
    }

    vector <ll> pai_nai_khuje;

    for (int i = 1; i <= n; i++)
    {
        if (!mark[i])
        {
            pai_nai_khuje.emplace_back(i);
        }
    }

    bool fl = true;

    if (pai_nai_khuje.size() != 2 || pai_nai_khuje[0] + pai_nai_khuje[1] != ar[0])
    {
        fl = false;
    }

    v.emplace_back(pai_nai_khuje[0]);

    v.emplace_back(pai_nai_khuje[1]);

    sort(v.begin(), v.end());

    for (int i = 0; i < n && fl; i++)
    {
        fl = fl && (v[i] == i + 1);
    }
    
    return fl;
}

bool check_mittel()
{
    fill(mark, mark + n + 2, false);

    vector <ll> v;

    if (ar[0] <= n)
    {
        v.emplace_back(ar[0]);
        mark[ar[0]] = true;
    }

    for (int i = 1; i + 1  < n; i++)
    {
        if (ar[i] - ar[i - 1] <= n && !mark[ar[i] - ar[i - 1]])
        {
            v.emplace_back(ar[i] - ar[i - 1]);
            mark[v.back()] = true;
        }
        // else {
        //     cout << ar[i] << " " << ar[i - 1] << " " << (ar[i] - ar[i - 1]) << " " << mark[ar[i] - ar[i - 1]] << "\n";
        // }
    }

    vector <ll> pai_nai_khuje;

    for (int i = 1; i <= n; i++)
    {
        if (!mark[i])
        {
            pai_nai_khuje.emplace_back(i);
        }
    }

    // cout << "checking mittel: pai_nai_khuje.size()= " << pai_nai_khuje.size() << endl;

    // for (int x: pai_nai_khuje) cout << x << " "; cout << " vpp\n"; cout << "n: " << n << "\n";

    bool fl = true;

    if (pai_nai_khuje.size() != 2)
    {
        fl = false;
    }

    v.emplace_back(pai_nai_khuje[0]);

    v.emplace_back(pai_nai_khuje[1]);

    sort(v.begin(), v.end());

    for (int i = 0; i < n && fl; i++)
    {
        fl = fl && (v[i] == i + 1);
    }
    
    return fl;
}

void Solve()
{
    scanf("%d", &t);
    while (t-- && scanf("%d", &n) == 1)
    {
        for (int i = 0; i + 1 < n; i++)
        {
            scanf("%lld", &ar[i]);
        }

        ll sum = n;
        sum = (sum * (sum + 1ll)) / 2ll;

        int ind = max_element(ar, ar + n - 1) - ar;

        if (ind != n - 2)
        {
            puts("NO");
            continue;
        }

        if (ar[ind] > sum)
        {
            puts("NO");
            continue;
        }

        if (ar[ind] < sum)
        {
            vector <ll> v;
            v.emplace_back(ar[0]);
            for (int i = 1; i + 1  < n; i++)
            {
                v.emplace_back(ar[i] - ar[i - 1]);
            }
            v.emplace_back(sum - ar[ind]);
            sort(v.begin(), v.end());
            bool fl = true;
            for (int i = 0; i < n && fl; i++)
            {
                fl = fl && (v[i] == i + 1);
            }
            puts(fl ? "YES" : "NO");
            continue;
        }

        if (ar[ind] != sum)
        {
            puts("NO");
            continue;
        }

        if (check_first())
        {
            puts("YES");
            continue;
        }

        if (check_mittel())
        {
            puts("YES");
            continue;
        }

        puts("NO");
    }
}

} // namespace solution

#endif