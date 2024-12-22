#ifndef COMMON_H
#define COMMON_H 1

#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <chrono>
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

#ifdef CLown1331
// duplicate printf that outputs to file and stdout
FILE *local_foutput;
#define printf(...) fprintf(local_foutput, __VA_ARGS__), printf(__VA_ARGS__), fflush(stdout)
#define puts(s) fputs(s, local_foutput), puts(s), fflush(stdout)
#define putchar(c) fputc(c, local_foutput), putchar(c), fflush(stdout)

#endif // CLown1331

#endif // COMMON_H