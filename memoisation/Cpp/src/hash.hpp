#ifndef HASH_HPP
#define HASH_HPP

#include <functional>
#include <vector>
#include <array>

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

namespace{
    // Combine the hash value of v to another hashvalue seed
    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v)
    {
        // Come from boost::hash_combine, use golden number to spread entropy
        seed ^= mem::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
    }
}

// Specilization for std::pair
template <typename U, typename V>
class hash<std::pair<U, V>>{
public:
    size_t operator()(std::pair<U,V> const& tt) const {
        size_t seed = 0;
        hash_combine(seed, std::get<0>(tt));
        hash_combine(seed, std::get<1>(tt));
        return seed;
    }
};

// Specilization for std::vector
template <typename T>
class hash<std::vector<T>>{
public:
    size_t operator()(std::vector<T> const& tt) const {
        size_t seed = 0;
        for(auto i = tt.begin(); i != tt.end(); i++){
            hash_combine(seed, *i);
        }
        return seed;
    }
};

// Specilization for std::array
template <typename T, int N>
class hash<std::array<T, N>>{
public:
    size_t operator()(std::array<T,N> const& tt) const {
        size_t seed = 0;
        for(auto i = tt.begin(); i != tt.end(); i++){
            hash_combine(seed, *i);
        }
        return seed;
    }
};

namespace {
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

}
#endif
