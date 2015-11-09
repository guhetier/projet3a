#ifndef LISTBUCKET_HPP
#define LISTBUCKET_HPP

#include <list>
#include <tuple>

template<typename K, typename V>
class ListBucket : private std::list<std::pair<K,V>> {
public:

    ListBucket (int maxSize=5) : maxLength(maxSize){
    }

    void insert(const std::pair<const K, V> val){
        try{
            remove(std::get<0>(val));
        } catch (std::out_of_range k){}

        this->push_front(val);
        if(this->size() == maxLength)
            this->pop_back();
    }

    V& at(const K& key) {
        //May throw an exception if the key is not found
        std::pair<K,V> val = remove(key);

        this->push_front(val);
        return std::get<1>(this->front());
    }

    std::pair<K,V> remove(const K& key){
        for(auto i = this->begin(); i != this->end(); i++){
            if(std::get<0>(*i) == key){
                this->erase(i);
                return *i;
            }
        }
        throw std::out_of_range("Can not find the key");
    }

private:
    const int maxLength;
};

#endif
