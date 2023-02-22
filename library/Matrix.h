#ifndef Matrix_h
#define Matrix_h 1

#include <algorithm>
#include <vector>

namespace library
{
template <long long mod> struct Matrix
{
    int mat_sz;
    std::vector<std::vector<int>> a;

    Matrix(int _mat_sz) : mat_sz(_mat_sz), a(std::vector<std::vector<int>>(_mat_sz, std::vector<int>(_mat_sz, 0)))
    {
    }

    ~Matrix()
    {
    }

    void Clear()
    {
        for (int i = 0; i < mat_sz; i++)
        {
            std::fill(a[i].begin(), a[i].end(), 0);
        }
    }

    void One()
    {
        for (int i = 0; i < mat_sz; i++)
        {
            for (int j = 0; j < mat_sz; j++)
            {
                a[i][j] = (i == j);
            }
        }
    }

    Matrix operator+(const Matrix &b) const
    {
        Matrix tmp(mat_sz);
        tmp.Clear();
        for (int i = 0; i < mat_sz; i++)
        {
            for (int j = 0; j < mat_sz; j++)
            {
                tmp.a[i][j] = a[i][j] + b.a[i][j];
                if (tmp.a[i][j] >= mod)
                {
                    tmp.a[i][j] -= mod;
                }
            }
        }
        return tmp;
    }

    Matrix operator*(const Matrix &b) const
    {
        Matrix tmp(mat_sz);
        tmp.Clear();
        for (int i = 0; i < mat_sz; i++)
        {
            for (int j = 0; j < mat_sz; j++)
            {
                for (int k = 0; k < mat_sz; k++)
                {
                    tmp.a[i][k] += (long long)a[i][j] * b.a[j][k] % mod;
                    if (tmp.a[i][k] >= mod)
                    {
                        tmp.a[i][k] -= mod;
                    }
                }
            }
        }
        return tmp;
    }

    Matrix operator^(long long x) const
    {
        return Pow(x);
    }

    Matrix operator^=(long long x) const
    {
        return *this = Pow(x);
    }

    Matrix Pow(long long x)
    {
        Matrix ans(mat_sz), num = *this;
        ans.One();
        while (x > 0)
        {
            if (x & 1)
            {
                ans = ans * num;
            }
            num = num * num;
            x >>= 1;
        }
        return ans;
    }
};

} // namespace library

#endif