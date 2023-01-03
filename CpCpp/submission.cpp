#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#ifndef solution_h
#define solution_h 1
namespace solution
{
    using namespace std;
    void Solve()
    {
        int t, n;
        cin >> t;
        while (t--) {
            cin >> n;
            cerr << n << ": --> \n";
            if (n == 3) {
                cout << "NO\n";
            }
            else {
                cout << "YES\n";
                if (n & 1) {
                    for (int i = 0; i < n; i++) {
                        if (i & 1) cout << ((n - 1) / 2) << " ";
                        else cout << -(((n - 1) / 2) - 1) << " ";
                    }
                    cout << "\n";
                }
                else {
                    for (int i = 0; i < n; i++) {
                        if (i & 1) cout << "-";
                        cout << 1 << " ";
                    }
                    cout << "\n";
                }
            }
        }
    }
}
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char* argv[])
{
#ifndef CLown1331
#endif
    solution::Solve();
#if ok
#endif
    return 0;
}
