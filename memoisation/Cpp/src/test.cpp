//#include "fixedPoint.hpp"
#include <iostream>
#include <unordered_map>

using namespace std;

struct MyPair{
    int x;
    int y;

    MyPair(int x, int y){
        this->x = x;
        this->y = y;
    }

    bool operator==(const MyPair &other) const {
        return (x == other.x
            && y == other.y);
  }


};

struct MyHash{
    std::size_t operator()(const tuple<int, int> k) const{
        return ((hash<int>()(get<0>(k))
               ^ (hash<int>()(get<1>(k)) << 1)) >> 1);
    }
};

namespace std{
    template<>
    struct hash<MyPair>{
        std::size_t operator()(const MyPair& k) const{
            return ((hash<int>()(k.x)
                   ^ (hash<int>()(k.y) << 1)) >> 1);
        }
    };

    template<>
    struct hash<tuple<int, int>> {
        std::size_t operator()(const tuple<int, int> k) const{
            return ((hash<int>()(get<0>(k))
                   ^ (hash<int>()(get<1>(k)) << 1)) >> 1);
        }
    };

    template<>
    struct equal_to<tuple<int, int>> {
        bool operator()(const tuple<int, int>& a, const tuple<int, int>& b) const{
            return a == b;
        }
    };
}

int main(int argc, char const *argv[]) {

    unordered_map<tuple<int,int>, int, MyHash> test;

    /*Memo<int, int> fibo ([](function<int(int)> f, int n){
        if (n<2)
            return 1;

        return f(n-1) + f(n-2);
    });*/

    test[make_tuple(1, 1)] = 1;
    test[make_tuple(2, 2)] = 2;

    std::cout << "hello world " << test[make_tuple(1,1)] << std::endl;

    return 0;
}
