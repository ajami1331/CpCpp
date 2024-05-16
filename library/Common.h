#ifndef COMMON_H
#define COMMON_H 1

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <random>

using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define szx(x) (int)(x).size()

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

constexpr int LOG2(int x)
{
    return 32 - __builtin_clz(x) - 1;
}

#endif // COMMON_H