#ifndef BucketHashTABLE_HPP
#define  BucketHashTABLE_HPP

#include "listBucket.hpp"
#include "hash.hpp"
#include <functional>
#include <stdexcept>

template<typename K, typename V, typename B>
class BucketHashTable {

public:

    BucketHashTable(int n = 16, std::function<std::size_t(K)> h=mem::hash<K>())
    {
        //Length is the first power of 2 greater than n
        length = 1;
        while(length < n)
            length <<= 1;
        table = new ListBucket<K,V>[length];
        hash = h;
    }

    virtual ~BucketHashTable(){
        delete[] table;
    }

    void insert(const std::pair<const K, V>& val){
        int h = getOffset(hash(std::get<0>(val)));

        table[h].insert(val);
        nbElements++;

        if(nbElements/(float)length > maxFillingProp){
            resize(2*length);
        }
    }

    const V& at(const K& key) const{
        int h = getOffset(hash(key));
        return table[h].get(key);
    }

    V& at(const K& key){
        int h = getOffset(hash(key));
        return table[h].at(key);
    }

    V del(const K& key){
        int h = getOffset(hash(key));
        return table[h].remove(key);
    }

private:

    inline int getOffset(std::size_t h) const {
        return h & (length-1);
    }

    void resize(int newLength){
        // Allcoating a new table
        ListBucket<K,V>* oldTable = table;
        table = new ListBucket<K,V>[newLength];
        int oldLength = length;
        length = newLength;

        // Re hashing and moving all the elements of the table
        for(int i = 0; i < oldLength; i++)
            //To-DO
            {}

        delete[] oldTable;
    }

    B *table;
    int length;
    int nbElements;
    const float maxFillingProp = 0.7;

    std::function<std::size_t(K)> hash;
};

#endif
