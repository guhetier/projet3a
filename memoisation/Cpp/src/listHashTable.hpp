#ifndef LISTHASHTABLE_HPP
#define  LISTHASHTABLE_HPP

#include "hashTable.hpp"
#include <deque>

template<typename K, typename T>
class ListHashTable : public HashTable<K, T> {
public:

    ListHashTable(int n = 16, std::function<std::size_t(K)> h=mem::hash<K>())
    {
        //Length is the first power of 2 greater than n
        length = 1;
        while(length < n)
            length <<= 1;
        table = new std::deque<std::pair<K,T>>[length];
        hash = h;
    }

    virtual ~ListHashTable(){
        delete[] table;
    }

    virtual void add(const K& key, const T& val){
        int h = getOffset(hash(key));
        for(auto i : table[h]){
            if(std::get<0>(i) == key){
                std::get<1>(i) = val;
                return;
            }
        }

        table[h].push_front(std::make_pair(key, val));
        nbElements++;

        if(nbElements/(float)length > maxFillingProp){
            resize(2*length);
        }
    }

    virtual T del(const K& key){
        int h = getOffset(hash(key));
        for(auto i = table[h].begin(); i != table[h].end(); i++){
            if(std::get<0>(*i) == key){
                T r = std::get<1>(*i);
                table[h].erase(i);
                nbElements--;
                return r;
            }
        }
        throw InvalidKeyException();
    }

    virtual T get(const K& key) const {
        int h = getOffset(hash(key));
        for(auto i : table[h]){
            if(std::get<0>(i) == key)
                return std::get<1>(i);
        }
        throw InvalidKeyException();
    }

private:

    inline int getOffset(std::size_t h) const {
        return h & (length-1);
    }

    void resize(int newLength){
        // Allcoating a new table
        std::deque<std::pair<K,T>>* oldTable = table;
        table = new std::deque<std::pair<K,T>>[newLength];
        int oldLength = length;
        length = newLength;

        // Re hashing and moving all the elements of the table
        for(int i = 0; i < oldLength; i++)
            for(auto p: oldTable[i]){
                int h = getOffset(hash(std::get<0>(p)));
                table[h].push_front(p);
            }

        delete[] oldTable;
    }

    std::deque<std::pair<K,T>> *table;
    int length;
    int nbElements;
    const float maxFillingProp = 0.7;

    std::function<std::size_t(K)> hash;
};

#endif
