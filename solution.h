#ifndef solution_h
#define solution_h 1

#include <cstdio>
#include <cstring>
#include <iostream>
#include "library/SegmentTree.h"

namespace solution
{
using namespace std;
const int sz = 1e5 + 10;

struct Fountain
{
    int beauty;
    int price;
    char type;
    bool operator<(const Fountain &other) const
    {
        return price < other.price;
    }
};

library::SegmentTree<int, sz, -1, 0> coins([](int x, int y) { return max(x, y); });
library::SegmentTree<int, sz, -1, 0> diamonds([](int x, int y) { return max(x, y); });
Fountain fountains[sz];
int n, c, d, ans;
int last[sz];

void Solve()
{
    cin >> n >> c >> d;

    for (int i = 0; i < n; i++)
        cin >> fountains[i].beauty >> fountains[i].price >> fountains[i].type;

    coins.Reset();

    diamonds.Reset();

    sort(fountains, fountains + n);

    memset(last, -1, sizeof last);

    for (int i = 0; i < n; i++)
    {
        last[fountains[i].price] = i;
        if (fountains[i].type == 'C')
        {
            coins.Update(1, 0, n - 1, i, fountains[i].beauty);
        }
        else
        {
            diamonds.Update(1, 0, n - 1, i, fountains[i].beauty);
        }
    }

    for (int i = 1; i < sz; i++)
        if (last[i] == -1)
            last[i] = last[i - 1];

    ans = 0;

    for (int i = 0; i < n; i++)
    {
        int baki_c = c;
        int baki_d = d;

        if (fountains[i].type == 'C')
            baki_c -= fountains[i].price;
        if (fountains[i].type == 'D')
            baki_d -= fountains[i].price;

        if (baki_c < 0 || baki_d < 0)
            continue;

        int hand_1, hand_2;

        hand_1 = fountains[i].beauty;

        if (fountains[i].type == 'C')
            coins.Update(1, 0, n - 1, i, -1);
        else
            diamonds.Update(1, 0, n - 1, i, -1);

        int l, r;

        l = 0;
        r = last[baki_c];

        if (r != -1)
        {
            hand_2 = coins.Query(1, 0, n - 1, l, r);
            if (hand_2 != -1)
                ans = max(ans, hand_1 + hand_2);
        }

        l = 0;
        r = last[baki_d];

        if (r != -1)
        {
            hand_2 = diamonds.Query(1, 0, n - 1, l, r);
            if (hand_2 != -1)
                ans = max(ans, hand_1 + hand_2);
        }

        if (fountains[i].type == 'C')
            coins.Update(1, 0, n - 1, i, fountains[i].beauty);
        else
            diamonds.Update(1, 0, n - 1, i, fountains[i].beauty);
    }

    cout << ans << "\n";
}
} // namespace solution
#endif