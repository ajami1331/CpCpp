#ifndef DEBUG_H
#define DEBUG_H 1

#include "Common.h"

#ifdef CLown1331

#define SFINAE(x, ...)                                                                                                 \
    template <class, class = void> struct x : false_type                                                          \
    {                                                                                                                  \
    };                                                                                                                 \
    template <class T> struct x<T, void_t<__VA_ARGS__>> : true_type                                          \
    {                                                                                                                  \
    }

SFINAE(DefaultIO, decltype(cout << declval<T &>()));
SFINAE(IsTuple, typename tuple_size<T>::type);
SFINAE(Iterable, decltype(begin(declval<T>())));

template <class T> constexpr char Space(const T &)
{
    return (Iterable<T>::value or IsTuple<T>::value) ? '\n' : ' ';
}

template <auto &os> struct Writer
{
    template <class T> void Impl(T const &t) const
    {
        if constexpr (DefaultIO<T>::value)
            os << t;
        else if constexpr (Iterable<T>::value)
        {
            int i = 0;
            for (auto &&x : t)
                ((i++) ? (os << Space(x), Impl(x)) : Impl(x));
        }
        else if constexpr (IsTuple<T>::value)
            apply(
                [this](auto const &...args) {
                    int i = 0;
                    (((i++) ? (os << ' ', Impl(args)) : Impl(args)), ...);
                },
                t);
        else
            static_assert(IsTuple<T>::value, "No matching type for print");
    }
    template <class F, class... Ts> auto &operator()(F const &f, Ts const &...ts) const
    {
        return Impl(f), ((os << ' ', Impl(ts)), ...), os << '\n', *this;
    }
};

#define debug(args...)                                                                                                 \
    {                                                                                                                  \
        string _s = #args;                                                                                        \
        replace(_s.begin(), _s.end(), ',', ' ');                                                                  \
        stringstream _ss(_s);                                                                                     \
        istream_iterator<string> _it(_ss);                                                                   \
        cerr << "Line " << __LINE__ << "\n";                                                                      \
        err(_it, args);                                                                                                \
    }

void err(istream_iterator<string> it)
{
    ignore = it;
}

template <typename T, typename... Args> void err(istream_iterator<string> it, T a, Args... args)
{
    cerr << "\033[0;31m" << *it << " = ";
    Writer<cerr>{}(a);
    cerr << "\033[0m";
    err(++it, args...);
}

int recursion_depth = 0;
#define dbg(...)                                                                                                       \
    [&]() -> auto &&                                                                                                   \
    {                                                                                                                  \
        ++recursion_depth;                                                                                             \
        auto &&value = __VA_ARGS__;                                                                                    \
        --recursion_depth;                                                                                             \
        cerr << string(recursion_depth, '\t') << #__VA_ARGS__ " = " << value << endl;                        \
        return forward<decltype(value)>(value);                                                                   \
    }                                                                                                                  \
    ()

#define ASSERT(...)                                                                                                    \
    if (not(__VA_ARGS__))                                                                                              \
    throw runtime_error(#__VA_ARGS__)
#else
#define debug(...) 0
#define ASSERT(...) 0
#define dbg(...) 0
#endif
#endif // DEBUG_H