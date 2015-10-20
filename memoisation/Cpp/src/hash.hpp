#ifndef HASH_HPP
#define HASH_HPP

#include <functional>

namespace mem{

template <typename TT>
struct hash
{
    std::function<std::size_t(TT)> myHash;
    bool isFunctionDef;

    hash()
    : isFunctionDef(false)
    {}

    hash(std::function<std::size_t(TT)> f)
    : myHash(f), isFunctionDef(true)
    {}


    size_t operator()(TT const& tt) const {
        return isFunctionDef ? myHash(tt) : std::hash<TT>()(tt);
    }
};

template <typename U, typename V>
struct hash<std::pair<U, V>>
    {
        size_t
        operator()(std::pair<U,V> const& tt) const
        {
            size_t seed = 2;
            return ((std::hash<U>()(std::get<0>(tt))
                   ^ (std::hash<V>()(std::get<1>(tt)) << 1)) >> 1);
            return seed;
        }
};

template <typename ... TT>
    struct hash<std::tuple<TT...>>
    {
        size_t
        operator()(std::tuple<TT...> const& tt) const
        {
            size_t seed = 0;
            return seed;
        }
};
}
#endif
