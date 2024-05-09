#ifndef ZAlgo_H
#define ZAlgo_H 1

#include "Common.h"

namespace library
{

template <class T, size_t MAXLEN> struct ZAlgo
{
  public:
    T outOfBound;
    T s[MAXLEN];
    int z[MAXLEN];
    int occurrence[MAXLEN];
    int n;
    int maxZ;

    void Init(const T *a, int aLen, const T *b, int bLen, const T &_outOfBound)
    {
        n = 0;
        for (int i = 0; i < aLen; i++)
            s[n++] = a[i];
        outOfBound = _outOfBound;
        s[n++] = outOfBound;
        for (int i = 0; i < bLen; i++)
            s[n++] = b[i];
        maxZ = 0;
        memset(occurrence, 0, sizeof(occurrence));
        memset(z, 0, sizeof(z));
        Compute();
    }

    void Init(const vector<T> &a, const vector<T> &b, const T &_outOfBound)
    {
        n = 0;
        for (int i = 0; i < a.size(); i++)
            s[n++] = a[i];
        outOfBound = _outOfBound;
        s[n++] = outOfBound;
        for (int i = 0; i < b.size(); i++)
            s[n++] = b[i];
        maxZ = 0;
        memset(occurrence, 0, sizeof(occurrence));
        memset(z, 0, sizeof(z));
        Compute();
    }

  private:
    void Compute()
    {
        int l = 0;
        int r = 0;
        for (int i = 1; i < n; i++)
        {
            if (i > r)
            {
                l = r = i;
                while (r < n && s[r - l] == s[r])
                {
                    r++;
                }

                z[i] = r - l;
                r--;
            }
            else
            {
                int k = i - l;
                if (z[k] < r - i + 1)
                {
                    z[i] = z[k];
                }
                else
                {
                    l = i;
                    while (r < n && s[r - l] == s[r])
                    {
                        r++;
                    }

                    z[i] = r - l;
                    r--;
                }
            }
        }

        int iter = 0;
        while (s[iter] != outOfBound)
            iter++;
        for (int i = iter + 1; i < n; i++)
        {
            maxZ = max(maxZ, z[i]);
            occurrence[z[i]]++;
        }
    }
};
} // namespace library

#endif