#include "fixedPoint.hpp"
#include "hash.hpp"

#include <iostream>
#include <unordered_map>
#include <functional>
#include <tuple>
#include <vector>

using namespace std;



int main(int argc, char const *argv[]) {

    auto fib = [](function<int(pair<int, int>)> f, pair<int, int> p){
        int n = get<0>(p);
        if (n<2)
            return 1;

        return f(make_pair(n-1,0)) + f(make_pair(n-2,0));
    };

    Memo<pair<int, int>, int> fibo (fib);

    std::cout << "hello world " << fibo(make_pair(5,0)) << std::endl;
    return 0;
}
