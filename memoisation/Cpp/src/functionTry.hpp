#ifndef FUNCTION_TRY
#define FUNCTION_TRY

#include <unordered_map>
#include <iostream>
#include <functional>


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
#endif
