#include <bits/stdc++.h>

using namespace std;

int main()
{
    mersenne_twister_engine <uint_fast64_t, 64, 312, 156, 31, 0xb5026f5aa96619e9, 29, 0x5555555555555555, 17, 0x71d67fffeda60000, 37, 0xfff7eee000000000, 43, 6364136223846793005> rng(chrono::steady_clock::now().time_since_epoch().count());
    int a = uniform_int_distribution <int> (1, 100)(rng);
    int b = uniform_int_distribution <int> (1, 100)(rng);
    cout << a << " " << b << endl;
}