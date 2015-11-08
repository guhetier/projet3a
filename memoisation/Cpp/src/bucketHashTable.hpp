#ifndef BucketHashTABLE_HPP
#define  BucketHashTABLE_HPP

#include "hashTable.hpp"
#include "bucket.hpp"
#include "listBucket.hpp"

template<typename K, typename V>
class BucketHashTable : public HashTable<K, V> {

public:

    BucketHashTable(int n = 16, std::function<std::size_t(K)> h=mem::hash<K>())
    {
        //Length is the first power of 2 greater than n
        length = 1;
        while(length < n)
            length <<= 1;
        table = alloc(length);
        hash = h;
    }

    virtual ~BucketHashTable(){
        delete[] table;
    }

    virtual void add(const K& key, const V& val){
        int h = getOffset(hash(key));

        table[h].insert(key, val);
        nbElements++;

        if(nbElements/(float)length > maxFillingProp){
            resize(2*length);
        }
    }

    virtual V del(const K& key){
        int h = getOffset(hash(key));
        return table[h].remove(key);
    }

    virtual V get(const K& key){
        int h = getOffset(hash(key));
        return table[h].get(key);
    }

private:

    inline int getOffset(std::size_t h) const {
        return h & (length-1);
    }

    void resize(int newLength){
        // Allcoating a new table
        Bucket<K,V>* oldTable = table;
        table = alloc(newLength);
        int oldLength = length;
        length = newLength;

        // Re hashing and moving all the elements of the table
        for(int i = 0; i < oldLength; i++)
            //To-DO
            {}

        delete[] oldTable;
    }

    virtual Bucket<K, V>* alloc(int length){
        return new ListBucket<K,V>[length];
    }

    Bucket<K,V> *table;
    int length;
    int nbElements;
    const float maxFillingProp = 0.7;

    std::function<std::size_t(K)> hash;
};

#endif
