#ifndef solution_h
#define solution_h 1

#include "library/Common.h"
#include "library/Debug.h"

namespace solution
{
const int sz = 3e5 + 105;
const int mod = 1e9 + 7;

void solve()
{
    int t, a, b, c;
    cin >> t;
    while (t-- && cin >> a >> b >> c)
    {
        cout << (a ^ b ^ c) << "\n";
    }
    
}

} // namespace solution

#endif // solution_h
