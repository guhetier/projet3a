#ifndef FIXEDPOINT_HPP
#define FIXEDPOINT_HPP

#include "hash.hpp"

#include <unordered_map>
#include <iostream>
#include <functional>



//Gestion propre de la mémoire par l'utilisation d'un objet
//En conservant les variables de la cloture dans un objet, il n'est plus nécessaire
//de les allouer dans le tas.

template <typename K, typename U,
        typename T = std::unordered_map<K, U, std::function<std::size_t(K)>>> //Type de l'argumement, Type de retour, , table de hash (est supposer posséder les même prototypes que la table de hash standard)

class Memo {

public:
    // Constructor
    // Build the memoised function
    // Allow to specify the hash function and the initial number of buckets on the hash table
    // Type T sould have an operator== methode defined or equal_to<K> should be defined
    Memo(std::function<U(std::function<U(K)>, K)> frec, int n = 100, std::function<std::size_t(K)> hf = mem::hash<K>())
    : table(n, hf)
    {
        fmemo = [this, &frec](K n){
            try{
                return table.at(n);
            }
            catch(std::out_of_range e){
                U r = frec(fmemo, n);
                table.insert(std::make_pair(n, r));//{n,r});
                return r;
            }
        };
    }

    // Exec the memoised function to arg
    U apply(K arg) const {
        return fmemo(arg);
    };

    // Overload operator (). Same as apply.
    U operator() (K arg) const {
        return fmemo(arg);
    }

private:
    T table;
    std::function<U(K)> fmemo;
};

#endif
