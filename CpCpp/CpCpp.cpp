#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#include "solution.h"
#include "utils.h"

int main(int argc, char *argv[])
{
#ifdef CLown1331
    const clock_t tStart = clock();
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    solution::Solve();
#ifdef CLown1331
    fprintf(stderr, "\n>> Runtime: %.10fs\n", static_cast<double>(clock() - tStart) / CLOCKS_PER_SEC);
    utils::CreateFileForSubmission();
#endif
    return 0;
}