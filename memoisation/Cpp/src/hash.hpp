#ifndef HASH_HPP
#define HASH_HPP

#include <functional>

namespace mem{

template <typename TT>
class hash
{
public:
    // Constructor
    hash()
    : isFunctionDef(false)
    {}

    hash(std::function<std::size_t(TT)> f)
    : myHash(f), isFunctionDef(true)
    {}

    // Operator () : to get the value and allow cast to function
    size_t operator()(TT const& tt) const {
        return isFunctionDef ? myHash(tt) : std::hash<TT>()(tt);
    }

private:
    std::function<std::size_t(TT)> myHash;
    bool isFunctionDef;
};

// Specilization for std::pair
template <typename U, typename V>
class hash<std::pair<U, V>>{
public:
    size_t operator()(std::pair<U,V> const& tt) const {
        return ((std::hash<U>()(std::get<0>(tt))
               ^ (std::hash<V>()(std::get<1>(tt)) << 1)) >> 1);
    }
};

namespace {

    // Combine the hash value of v to another hashvalue in seed
    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v)
    {
        // Come from boost::hash_combine
        seed ^= mem::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }

    // Recursive template code derived from Matthieu M.
    template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
    struct HashValueImpl
    {
        static void apply(size_t& seed, Tuple const& tuple)
        {
            HashValueImpl<Tuple, Index-1>::apply(seed, tuple);
            hash_combine(seed, std::get<Index>(tuple));
        }
    };

    template <class Tuple>
    struct HashValueImpl<Tuple,0>
    {
        static void apply(size_t& seed, Tuple const& tuple)
        {
            hash_combine(seed, std::get<0>(tuple));
        }
    };
}

// Specilization for std::tuple
template <typename ... TT>
class hash<std::tuple<TT...>>{
public:
    size_t operator()(std::tuple<TT...> const& tt) const {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};

// Specialisation for std::vector
//TODO


}
#endif
