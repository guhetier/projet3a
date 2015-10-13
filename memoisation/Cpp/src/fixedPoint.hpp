#ifndef FIXEDPOINT_HPP
#define FIXEDPOINT_HPP

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
    Memo(std::function<U(std::function<U(T)>, T)> frec/*, const std::hash<T>& hf = std::hash<T>(), const std::equal_to<T>& eq = std::equal_to<T>()*/){
        table(10, std::unordered_map<T,U>::hasher(),
                std::unordered_map<T,U>::key_equal(),
                std::unordered_map<T,U>::allocator_type());
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

    // // Let specify the hash function and the initial number of buckets on the hash table
    // Memo(std::function<U(std::function<U(T)>, T)> frec, int n, const std::hash<U>& hf = std::hash<U>())
    //     : Memo(frec) {
    //     table(hf);
    // }

    // Exec the memoised function to arg
    U apply(T arg) const {
        return fmemo(arg);
    };

    // Overload operator (). Same as apply.
    U operator() (T arg) const {
        return fmemo(arg);
    }

private:
    std::unordered_map<T, U> table;
    std::function<U(T)> fmemo;
};

#endif
