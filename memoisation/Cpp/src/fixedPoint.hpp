#ifndef FIXEDPOINT_HPP
#define FIXEDPOINT_HPP

#include <unordered_map>
#include <algorithm>
#include <iostream>

template <typename T, typename U>
const std::function<U(T)>& rec (std::function<U(std::function<U(T)>, T)> frec){
    std::function<U(T)>* g = new std::function<U(T)>;
    *g = [frec, g](T n){
        return frec(*g, n);
    };
    return *g;
}

template <typename T, typename U>
const std::function<U(T)>& memo (std::function<U(std::function<U(T)>, T)>  frec){
    std::unordered_map<T,U>* table = new std::unordered_map<T,U>;

    std::function<U(T)>* g = new std::function<U(T)>;
    *g = [table, frec, g](T n){
        try{
            return table->at(n);
        }
        catch(const std::out_of_range& e){
            U r = frec(*g, n);
            table->insert({n,r});
            return r;
        }
    };
    return *g;
}

//Gestion propre de la mémoire par l'utilisation d'un objet
//En conservant les variables de la cloture dans un objet, il n'est plus nécessaire
//de les allouer dans le tas.

template <typename T, typename U> //Type de l'argumement, Type de retour
class Memo {

public:
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

    U apply(T arg) const {
        return fmemo(arg);
    };

private:
    std::unordered_map<T, U> table;
    std::function<U(T)> fmemo;
};

#endif
