#include "fixedPoint.hpp"
#include "hash.hpp"
#include "listBucket.hpp"
#include "bucketHashTable.hpp"
#include "listHashTable.hpp"

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

    auto pascal = [](function<long(pair<int, int>)> f, pair<long, long> p){
        int n = get<0>(p);
        int k = get<1>(p);

        if(n<k)
            return (long)0;
        if(k == 0)
            return (long)1;

        return f(make_pair(n-1,k)) + f(make_pair(n-1, k-1));
    };

    Memo<pair<int, int>, int, ListHashTable<pair<int, int>, int>> fibo (fib);
    Memo<pair<int, int>, int,
        BucketHashTable<pair<int, int>, int,
        ListBucket<pair<int, int>, int>>> fibo2 (fib);

    Memo<pair<int, int>, long> trianglePascal(pascal);

    std::cout << "hello world " << trianglePascal(make_pair(9000,4000)) << std::endl;
    return 0;
}
