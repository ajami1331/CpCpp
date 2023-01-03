#ifndef StringUtils_h
#define StringUtils_h 1

namespace library
{
    static inline void ltrim(std::string& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char c) -> bool {
            return !std::isspace(c);
            }));
    }

    static inline void rtrim(std::string& s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }

    static inline void trim(std::string& s)
    {
        ltrim(s);
        rtrim(s);
    }

    static inline std::string& trim_i(std::string& s)
    {
        ltrim(s);
        rtrim(s);
        return s;
    }

    static inline std::string trim_n(std::string s)
    {
        ltrim(s);
        rtrim(s);
        return s;
    }

    std::vector <std::string> split(const std::string& s, char splitChar) {
        std::vector <std::string> splittedString;
        std::string hand = "";
        for (char c : s) {
            if (c == splitChar) {
                splittedString.emplace_back(hand);
                hand.clear();
                continue;
            }
            hand.push_back(c);
        }
        splittedString.emplace_back(hand);
        return splittedString;
    }
}
#endif