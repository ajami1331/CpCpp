#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#ifndef ZAlgo_H
#define ZAlgo_H 1
namespace library
{
template <class T, size_t MAXLEN> struct ZAlgo
{
  public:
    T outOfBound;
    T s[MAXLEN];
    int z[MAXLEN];
    int occurrence[MAXLEN];
    int n;
    int maxZ;
    void Init(const T *a, int aLen, const T *b, int bLen, const T &_outOfBound)
    {
        n = 0;
        for (int i = 0; i < aLen; i++)
            s[n++] = a[i];
        outOfBound = _outOfBound;
        s[n++] = outOfBound;
        for (int i = 0; i < bLen; i++)
            s[n++] = b[i];
        maxZ = 0;
        memset(occurrence, 0, sizeof(occurrence));
        memset(z, 0, sizeof(z));
        Compute();
    }
    void Init(const std::vector<T> &a, const std::vector<T> &b, const T &_outOfBound)
    {
        n = 0;
        for (int i = 0; i < a.size(); i++)
            s[n++] = a[i];
        outOfBound = _outOfBound;
        s[n++] = outOfBound;
        for (int i = 0; i < b.size(); i++)
            s[n++] = b[i];
        maxZ = 0;
        memset(occurrence, 0, sizeof(occurrence));
        memset(z, 0, sizeof(z));
        Compute();
    }
  private:
    void Compute()
    {
        int l = 0;
        int r = 0;
        for (int i = 1; i < n; i++)
        {
            if (i > r)
            {
                l = r = i;
                while (r < n && s[r - l] == s[r])
                {
                    r++;
                }
                z[i] = r - l;
                r--;
            }
            else
            {
                int k = i - l;
                if (z[k] < r - i + 1)
                {
                    z[i] = z[k];
                }
                else
                {
                    l = i;
                    while (r < n && s[r - l] == s[r])
                    {
                        r++;
                    }
                    z[i] = r - l;
                    r--;
                }
            }
        }
        int iter = 0;
        while (s[iter] != outOfBound)
            iter++;
        for (int i = iter + 1; i < n; i++)
        {
            maxZ = std::max(maxZ, z[i]);
            occurrence[z[i]]++;
        }
    }
};
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
using ll = long long;
const int sz = 1e6 + 10;
int sLen, tLen;
struct Elem
{
    ll len;
    char c;
    Elem() {}
    Elem(int len, char c) : len(len), c(c) {}
    bool operator==(const Elem &rhs) const
    {
        return len == rhs.len && c == rhs.c;
    }
    bool operator<=(const Elem &rhs) const
    {
        return len <= rhs.len && c == rhs.c;
    }
    bool operator>=(const Elem &rhs) const
    {
        return len >= rhs.len && c == rhs.c;
    }
    bool operator!=(const Elem &rhs) const
    {
        return !(*this == rhs);
    }
} const outOfBound = Elem(0, '$');
Elem s[sz], t[sz];
vector <Elem> sVec, tVec;
library::ZAlgo<Elem, sz + sz + sz> zAlgo;
void Solve()
{
    scanf("%d %d", &sLen, &tLen);
    for (int i = 0; i < sLen; i++)
    {
        scanf("%lld-%c", &s[i].len, &s[i].c);
    }
    for (int i = 0; i < tLen; i++)
    {
        scanf("%lld-%c", &t[i].len, &t[i].c);
    }
    sVec.clear();
    tVec.clear();
    for (int i = 0; i < sLen; i++)
    {
        if (sVec.empty() || sVec.back().c != s[i].c)
        {
            sVec.push_back(s[i]);
        }
        else
        {
            sVec.back().len += s[i].len;
        }
    }
    for (int i = 0; i < tLen; i++)
    {
        if (tVec.empty() || tVec.back().c != t[i].c)
        {
            tVec.push_back(t[i]);
        }
        else
        {
            tVec.back().len += t[i].len;
        }
    }
    if (tVec.size() == 1)
    {
        ll ans = 0;
        for (int i = 0; i < sVec.size(); i++)
        {
            if (sVec[i] >= tVec[0])
            {
                ans += sVec[i].len - tVec[0].len + 1;
            }
        }
        printf("%lld\n", ans);
        return;
    }
    if (tVec.size() == 2)
    {
        ll ans = 0;
        for (int i = 0; i + 1 < sVec.size(); i++)
        {
            if (sVec[i] >= tVec[0] && sVec[i + 1] >= tVec[1])
            {
                ans++;
            }
        }
        printf("%lld\n", ans);
        return;
    }
    auto last = tVec.back();
    auto first = tVec.front();
    tVec.pop_back();
    reverse(tVec.begin(), tVec.end());
    tVec.pop_back();
    reverse(tVec.begin(), tVec.end());
    zAlgo.Init(tVec, sVec, outOfBound);
    ll ans = 0;
    for (int i = tVec.size() + 2; i < zAlgo.n; i++)
    {
        if (zAlgo.z[i] == tVec.size())
        {
            if (i + tVec.size() < zAlgo.n && zAlgo.s[i - 1] >= first && zAlgo.s[i + tVec.size()] >= last)
            {
                ans++;
            }
        }
    }
    printf("%lld\n", ans);
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
