#ifndef FIXEDPOINT_HPP
#define FIXEDPOINT_HPP

//#include "hash.hpp"

#include <unordered_map>
#include <iostream>
#include <functional>



//Gestion propre de la mémoire par l'utilisation d'un objet
//En conservant les variables de la cloture dans un objet, il n'est plus nécessaire
//de les allouer dans le tas.

template <typename T, typename U> //Type de l'argumement, Type de retour
class Memo {

public:
    // Constructor
    // Build the memoised function
    Memo(std::function<U(std::function<U(T)>, T)> frec){
        fmemo = [this, &frec](T n){
            try{
                return table.at(n);
            }
            catch(std::out_of_range e){
                U r = frec(fmemo, n);
                table.insert({n,r});
                return r;
            }
        };
    }

    // Allow to specify the hash function and the initial number of buckets on the hash table
    // Type T sould have an operator== methode defined or equal_to<T> should be defined
    Memo(std::function<U(std::function<U(T)>, T)> frec, int n, std::function<std::size_t(T)> hf)
    : table(n, hf)
    {
        fmemo = [this, &frec](T n){
            try{
                return table.at(n);
            }
            catch(std::out_of_range e){
                U r = frec(fmemo, n);
                table.insert({n,r});
                return r;
            }
        };
    }

    // Exec the memoised function to arg
    U apply(T arg) const {
        return fmemo(arg);
    };

    // Overload operator (). Same as apply.
    U operator() (T arg) const {
        return fmemo(arg);
    }

private:
    std::unordered_map<T, U, std::function<std::size_t(T)>> table;
    //std::unordered_map<T, U, mem::hash<T>> table;
    std::function<U(T)> fmemo;
};

#endif
