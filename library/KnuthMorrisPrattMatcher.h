#ifndef KnuthMorrisPrattMatcher_h
#define KnuthMorrisPrattMatcher_h 1

#include "Common.h"

template <size_t MAXLEN> struct KnuthMorrisPrattMatcher
{
    char m[MAXLEN];
    int table[MAXLEN], lenM;

    void Init(const char *str, int n)
    {
        strncpy(m, str, n);
        lenM = n;
        table[0] = 0;
        int i = 1, j = 0;
        while (i < lenM)
        {
            if (m[i] == m[j])
            {
                j++;
                table[i] = j;
                i++;
            }
            else
            {
                if (j)
                {
                    j = table[j - 1];
                }
                else
                {
                    table[i] = 0;
                    i++;
                }
            }
        }
    }

    vector<int> MatchString(const char *s, int lenS)
    {
        int i = 0, j = 0;
        vector<int> matches;
        while (i < lenS)
        {
            while (i < lenS && j < lenM && s[i] == m[j])
            {
                i++;
                j++;
            }
            if (j == lenM)
            {
                j = table[j - 1];
                matches.emplace_back(i - lenM);
            }
            else if (i < lenS && s[i] != m[j])
            {
                if (j)
                {
                    j = table[j - 1];
                }
                else
                {
                    i++;
                }
            }
        }
        return matches;
    }
};

#endif