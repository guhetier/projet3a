#include "fixedPoint.hpp"
#include "hash.hpp"

#include <iostream>
#include <unordered_map>
#include <functional>
#include <tuple>
#include <vector>

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
    // template<>
    // struct hash<MyPair>{
    //     std::size_t operator()(const MyPair& k) const{
    //         return ((hash<int>()(k.x)
    //                ^ (hash<int>()(k.y) << 1)) >> 1);
    //     }
    // };

    // template<>
    // struct hash<tuple<int, int>> {
    //     std::size_t operator()(const tuple<int, int> k) const{
    //         return ((hash<int>()(get<0>(k))
    //                ^ (hash<int>()(get<1>(k)) << 1)) >> 1);
    //     }
    // };

    template<>
    struct equal_to<tuple<int, int>> {
        bool operator()(const tuple<int, int>& a, const tuple<int, int>& b) const{
            return a == b;
        }
    };
}



int main(int argc, char const *argv[]) {
    auto myhash = [](const pair<int, int> k){
            return ((hash<int>()(get<0>(k))
                   ^ (hash<int>()(get<1>(k)) << 1)) >> 1);
        };

    mem::hash<int> h;
    mem::hash<pair<int, int>> g;
    mem::hash<double> t;

    cout << h(4) << endl << g(make_pair(2, 2)) << endl << t(2.5) << endl;


    auto fib = [](function<int(pair<int, int>)> f, tuple<int, int> p){
        int n = get<0>(p);
        if (n<2)
            return 1;

        return f(make_pair(n-1,0)) + f(make_pair(n-2,0));
    };

    Memo<pair<int, int>, int> fibo (fib, 10, g);

    std::cout << "hello world " << fibo(make_pair(5,0)) << std::endl;
    return 0;
}
