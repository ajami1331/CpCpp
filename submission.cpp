#include <algorithm>
#include <iostream>
#include <queue>
#ifndef solution_h
#define solution_h 1
namespace solution
{
using namespace std;
void Solve()
{
    int a, b;
    cin >> a >> b;
    cout << ((a * b) / 2) << "\n";
}
} // namespace solution
#endif
#define _CRT_SECURE_NO_WARNINGS
int main(int argc, char *argv[])
{
    solution::Solve();
    return 0;
}
