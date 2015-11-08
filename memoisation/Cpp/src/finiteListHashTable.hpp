#ifndef FINITELISTHASHTABLE_HPP
#define FINITELISTHASHTABLE_HPP

#include "bucketHashTable.hpp"
#include "listBucket.hpp"

template <typename K, typename V>
class FiniteListHashTable : public BucketHashTable<K,V>{

public:
    FiniteListHashTable(int n=16, std::function<std::size_t(K)> h=mem::hash<K>())
        : BucketHashTable<K,V>(n, h)
    {}

    ~FiniteListHashTable(){
    }

private:
    Bucket<K, V>* alloc(int length){
        return new ListBucket<K, V>[length];
    }
};

#endif
