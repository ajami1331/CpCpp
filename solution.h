#ifndef solution_h
#define solution_h 1

#include <algorithm>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iomanip>
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
const int mod = 1e9 + 7;

struct Solution
{
    int n;
    ll A, cf, cm, m;
    vector<ll> a;
    vector<pair<ll, int>> b;
    vector<ll> c;
    vector<ll> suf;
    vector<ll> pref;

    ll f(ll baki, ll N)
    {
        ll l = 0;
        ll r = A;

        while (l + 4 < r)
        {
            ll mid = (l + r) / 2;

            ll koita = upper_bound(c.begin(), c.end(), mid) - c.begin();

            koita = min(koita, N);

            ll cost = (koita * mid) - pref[koita];

            if (cost <= baki)
            {
                l = mid;
            }
            else
            {
                r = mid;
            }
        }

        ll ans = 0;

        for (; l <= r; l++)
        {
            ll koita = upper_bound(c.begin(), c.end(), l) - c.begin();

            ll cost = (koita * l) - pref[koita];

            if (cost <= baki)
            {
                ans = l;
            }
        }

        return ans;
    }

    void Solve()
    {
        scanf("%d %lld %lld %lld %lld", &n, &A, &cf, &cm, &m);

        a.resize(n);
        b.clear();
        c.resize(n);

        for (int i = 0; i < n; i++)
        {
            scanf("%lld", &a[i]);
            b.emplace_back(A - a[i], i);
            c[i] = a[i];
        }

        sort(b.begin(), b.end(), [](const pair<ll, int> &x, const pair<ll, int> &y) { return x.first > y.first; });

        sort(c.begin(), c.end());

        suf.resize(n + 1);
        suf[n] = 0;

        pref.resize(n + 1);
        pref[0] = 0;

        for (int i = n - 1; i >= 0; i--)
        {
            suf[i] = suf[i + 1] + b[i].first;
        }

        for (int i = 1; i <= n; i++)
        {
            pref[i] = pref[i - 1] + c[i - 1];
        }

        ll ans = 0;

        int max_c = n;

        ll min_f = c[0];

        for (ll i = n; i >= 0; i--)
        {
            if (suf[i] > m)
            {
                break;
            }

            ll cfc = cf * (n - i);
            ll baki = m - suf[i];

            // cout << "i = " << i << " baki = " << baki << endl;

            ll f_baki = 0;
            ll sum = 0;

            if (i == 0)
            {
                sum = cfc + cm * A;
            }
            else
            {
                f_baki = f(baki, i);
                sum = cfc + cm * f_baki;
            }

            // cout << cfc << " " << cm << " " << f_baki << " " << sum << endl;

            if (sum > ans)
            {
                ans = sum;
                max_c = i;
                min_f = f_baki;
            }

            // if (A == 6746 && f_baki == 4570)
            // {
            //     cout << "n - i" << n - i << endl;
            //     cout << "i = " << i << " baki = " << baki << endl;
            //     cout << cfc << " " << cm << " " << f_baki << " " << sum << endl;
            // }
            // if (A == 6746 && f_baki == 5674)
            // {
            //     ll koita = lower_bound(c.begin(), c.end(), f_baki) - c.begin();
            //     ll cost = (koita * f_baki) - pref[koita];
            //     cout << "n - i" << n - i << endl;
            //     cout << "i = " << i << " baki = " << baki << endl;
            //     cout << "koita = " << koita << " cost = " << cost << endl;
            //     cout << cfc << " " << cm << " " << f_baki << " " << sum << endl;
            // }
        }

        for (int i = 0; i < n; i++)
        {
            if (i >= max_c)
            {
                a[b[i].second] = A;
            }

            a[b[i].second] = max(a[b[i].second], min_f);
        }

        printf("%lld\n", ans);
        for (int i = 0; i < n; i++)
        {
            printf("%lld%c", a[i], i == n - 1 ? '\n' : ' ');
        }
    }
};

} // namespace solution

#endif // solution_h
