#ifndef SmallestStringRotation_h
#define SmallestStringRotation_h 1

#include "Common.h"

namespace library
{

template <size_t MAXLEN> struct SmallestStringRotation
{
    int f[MAXLEN];
    int operator()(const string &s)
    {
        int n = s.size();
        string t = s + s;
        memset(f, -1, sizeof f);
        int k = 0;
        for (int j = 1; j < 2 * n; ++j)
        {
            int i = f[j - k - 1];
            while (i != -1 && t[j] != t[k + i + 1])
            {
                if (t[j] < t[k + i + 1])
                {
                    k = j - i - 1;
                }
                i = f[i];
            }
            if (i == -1 && t[j] != t[k + i + 1])
            {
                if (t[j] < t[k + i + 1])
                {
                    k = j;
                }
                f[j - k] = -1;
            }
            else
            {
                f[j - k] = i + 1;
            }
        }
        return k;
    }
};

} // namespace library

#endif