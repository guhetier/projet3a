#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "hash.hpp"
#include <functional>
#include <exception>
#include <string>

template<typename K, typename T>
class HashTable{
public:
    virtual ~HashTable(){};

    virtual void add(const K& key, const T& val) = 0;
    virtual T del(const K& key) = 0;
    virtual T get(const K& key) = 0;
};

class InvalidKeyException: public std::exception {
    virtual const char* what() const throw() {
        return std::string("There exist no such key in the table").c_str();
    }
};

#endif
