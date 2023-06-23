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
#include "library/ZAlgo.h"

namespace solution
{
using namespace std;

const int sz = 1e6 + 10;
int n;
char s[sz];
char t[sz];
library::ZAlgo<char, sz + sz + sz, '$'> z;

void Solve()
{
    scanf("%d", &n);
    while (n-- && scanf("%s", s))
    {
        int len = strlen(s);
        for (int i = 0; i < len; i++)
        {
            t[i] = s[len - i - 1];
        }
        z.Init(s, len, t, len);
        for (int i = len + 1; i < z.n; i++)
        {
            if (z.z[i] == z.maxZ)
            {
                for (int j = i + z.maxZ - 1; j >= i; j--)
                {
                    putchar(z.s[j]);
                }
                putchar('\n');
                break;
            }
        }
    }
}

} // namespace solution
#endif