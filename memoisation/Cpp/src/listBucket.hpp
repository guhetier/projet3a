#ifndef LISTBUCKET_HPP
#define LISTBUCKET_HPP

#include "bucket.hpp"
#include "hashTable.hpp"
#include <list>
#include <tuple>

template<typename K, typename V>
class ListBucket : public Bucket<K,V>, private std::list<std::pair<K,V>> {
public:

    ListBucket (int maxSize=5) : maxLength(maxSize){
        length = 0;
    }

    virtual void insert(const K& key, const V& val){
        try{
            remove(key);
        } catch (InvalidKeyException k){}

        this->emplace_front(key, val);
        if(length == maxLength)
            this->pop_back();
        else
            length++;
    }

    virtual V get(const K& key){
        //May throw an exception if the key is not found
        V val = remove(key);

        this->emplace_front(key, val);
        length++;
        return val;
    }

    virtual V remove(const K& key){
        for(auto i = this->begin(); i != this->end(); i++){
            if(std::get<0>(*i) == key){
                V r = std::get<1>(*i);
                this->erase(i);
                length--;
                return r;
            }
        }
        throw InvalidKeyException();
    }

private:
    const int maxLength;
    int length;
};

#endif
