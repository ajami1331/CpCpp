#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#ifndef Math_h
#define Math_h 1
namespace library
{
template <long long mod> long long ModuloPower(long long b, long long p)
{
    long long ret = 1;
    for (; p > 0; p >>= 1)
    {
        if (p & 1)
            ret = (ret * b) % mod;
        b = (b * b) % mod;
    }
    return ret % mod;
}
template <long long mod> long long ModuloInverse(long long b)
{
    return ModuloPower<mod>(b, mod - 2);
}
} // namespace library
#endif
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
const int sz = 5050;
using ll = long long;
int t, n, cs;
int ar[sz];
vector <int> primesTaken;
vector <int> others;
const ll mod = 998244353LL;
ll fac[sz];
ll facInv[sz];
ll dp[sz][sz];
map <int, int> cnt;
bool isPrime(int x);
ll rec(int pos, int rem);
void Solve()
{
    memset(dp, -1, sizeof dp);
    fac[0] = 1;
    facInv[0] = library::ModuloInverse<mod>(fac[0]);
    for (ll i = 1; i < sz; i++)
    {
        fac[i] = (fac[i - 1] * i) % mod;
        facInv[i] = library::ModuloInverse<mod>(fac[i]);
    }
    scanf("%d", &n);
    primesTaken.clear();
    others.clear();
    cnt.clear();
    for (int i = 0; i < n + n; i++)
    {
        scanf("%d", &ar[i]);
        cnt[ar[i]]++;
        if (isPrime(ar[i]))
        {
            primesTaken.push_back(ar[i]);
        }
        else
        {
            others.push_back(ar[i]);
        }
    }
    sort(primesTaken.begin(), primesTaken.end());
    sort(others.begin(), others.end());
    primesTaken.resize(unique(primesTaken.begin(), primesTaken.end()) - primesTaken.begin());
    others.resize(unique(others.begin(), others.end()) - others.begin());
    if (primesTaken.size() < n)
    {
        printf("0\n");
    }
    else
    {
        ll ans = rec(0, n);
        for (int i = 0; i < others.size(); i++)
        {
            if (!isPrime(others[i]))
            {
                ans = (ans * facInv[cnt[others[i]]]) % mod;
            }
        }
        ans = (ans * fac[n]) % mod;
        printf("%lld\n", ans);
    }
}
ll rec(int pos, int rem)
{
    if (rem == 0)
    {
        return 1;
    }
    if (pos == primesTaken.size())
    {
        return 0;
    }
    auto &ret = dp[pos][rem];
    if (ret != -1)
    {
        return ret;
    }
    ret = (rec(pos + 1, rem) * facInv[cnt[primesTaken[pos]]]) % mod;
    ret = (ret + ((rec(pos + 1, rem - 1) * facInv[cnt[primesTaken[pos]] - 1]) % mod)) % mod;
    return ret;
}
bool isPrime(int x)
{
    if (x == 1)
    {
        return false;
    }
    if (x == 2)
    {
        return true;
    }
    for (int i = 2; i * i <= x; i++)
    {
        if (x % i == 0)
        {
            return false;
        }
    }
    return true;
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
