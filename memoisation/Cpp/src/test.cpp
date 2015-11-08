#include "fixedPoint.hpp"
#include "hash.hpp"
#include "bucketHashTable.hpp"
#include "listHashTable.hpp"
#include "finiteListHashTable.hpp"

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

    ListHashTable<string, int> table;
    table.add("test", 4);

    BucketHashTable<int, int> test(5);
    std::cout << table.get("test") << std::endl;

    std::cout << "hello world " << fibo(make_pair(5,0)) << std::endl;
    return 0;
}
