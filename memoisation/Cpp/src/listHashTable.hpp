#ifndef LISTHASHTABLE_HPP
#define  LISTHASHTABLE_HPP

#include <functional>
#include <list>
#include <stdexcept>
#include "hash.hpp"

template<typename K, typename V>
class ListHashTable {
public:

    ListHashTable(int n = 16, std::function<std::size_t(K)> h=mem::hash<K>())
    {
        //Length is the first power of 2 greater than n
        length = 1;
        while(length < n)
            length <<= 1;
        table = new std::list<std::pair<const K,V>>[length];
        hash = h;
    }

    ~ListHashTable(){
        delete[] table;
    }

    void insert(const std::pair<const K, V>& val){
        const K& key = std::get<0>(val);
        int h = getOffset(hash(key));

        for(auto i : table[h]){
            if(std::get<0>(i) == key){
                std::get<1>(i) = std::get<1>(val);
                return;
            }
        }

        table[h].push_front(val);
        nbElements++;

        if(nbElements/(float)length > maxFillingProp){
            resize(2*length);
        }
    }

    V& at(const K& key){
        int h = getOffset(hash(key));
        for(auto i : table[h]){
            if(std::get<0>(i) == key)
                return std::get<1>(i);
        }
        throw std::out_of_range("Can not find the key");
    }


    const V& at(const K& key) const{
        int h = getOffset(hash(key));
        for(auto i : table[h]){
            if(std::get<0>(i) == key)
                return std::get<1>(i);
        }
        throw std::out_of_range("Can not find the key");
    }


    V del(const K& key){
        int h = getOffset(hash(key));
        for(auto i = table[h].begin(); i != table[h].end(); i++){
            if(std::get<0>(*i) == key){
                V r = std::get<1>(*i);
                table[h].erase(i);
                nbElements--;
                return r;
            }
        }
        throw std::out_of_range("Can not find the key");
    }

private:

    inline int getOffset(std::size_t h) const {
        return h & (length-1);
    }

    void resize(int newLength){
        // Allcoating a new table
        std::list<std::pair<const K,V>>* oldTable = table;
        table = new std::list<std::pair<const K,V>>[newLength];
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

    std::list<std::pair<const K,V>> *table;
    int length;
    int nbElements;
    const float maxFillingProp = 0.7;

    std::function<std::size_t(K)> hash;
};

#endif
