#ifndef StringUtils_h
#define StringUtils_h 1

#include "Common.h"

namespace library
{
static inline void ltrim(string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char c) -> bool { return !isspace(c); }));
}

static inline void rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), s.end());
}

static inline void trim(string &s)
{
    ltrim(s);
    rtrim(s);
}

static inline string &trim_i(string &s)
{
    ltrim(s);
    rtrim(s);
    return s;
}

static inline string trim_n(string s)
{
    ltrim(s);
    rtrim(s);
    return s;
}

vector<string> split(const string &s, char splitChar)
{
    vector<string> splittedString;
    string hand = "";
    for (char c : s)
    {
        if (c == splitChar)
        {
            splittedString.emplace_back(hand);
            hand.clear();
            continue;
        }
        hand.push_back(c);
    }
    splittedString.emplace_back(hand);
    return splittedString;
}
} // namespace library
#endif