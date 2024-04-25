#ifndef ConvexHullTrick_h
#define ConvexHullTrick_h 1

#include <algorithm>
#include <complex>
#include <numeric>
#include <vector>

namespace library
{

struct ConvexHullTrick
{
    std::vector<long long> M, C;
    int pointer = 0;

    bool bad(int l1, int l2, int l3)
    {
        return 1.0 * (C[l3] - C[l1]) * (M[l1] - M[l2]) < 1.0 * (C[l2] - C[l1]) * (M[l1] - M[l3]);
    }

    void add_line(long long m, long long c)
    {
        M.push_back(m);
        C.push_back(c);
        while (M.size() >= 3 && bad(M.size() - 3, M.size() - 2, M.size() - 1))
        {
            M.erase(M.end() - 2);
            C.erase(C.end() - 2);
        }
    }

    long long get(long long x)
    {
        if (pointer >= M.size())
            pointer = M.size() - 1;
        while (pointer < M.size() - 1 && M[pointer + 1] * x + C[pointer + 1] < M[pointer] * x + C[pointer])
            ++pointer;
        return M[pointer] * x + C[pointer];
    }
};

} // namespace library

#endif