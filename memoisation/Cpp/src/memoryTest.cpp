#include "fixedPoint.hpp"
#include "listBucket.hpp"
#include "bucketHashTable.hpp"
#include "listHashTable.hpp"

#include <iostream>
#include <functional>
#include <chrono>

using namespace std;



int main(int argc, char const *argv[]) {

    auto pascal = [](function<long(pair<int, int>)> f, pair<long, long> p){
        int n = get<0>(p);
        int k = get<1>(p);

        if(n<k)
            return (long)0;
        if(k == 0)
            return (long)1;

        return f(make_pair(n-1,k)) + f(make_pair(n-1, k-1));
    };

    // Command line arguments
    if(argc < 3){
        cout << "Arguments required : n k [t]" << endl;
        return 0;
    }

    int n = atoi(argv[1]);
    int k = atoi(argv[2]);
    int t = n;

    if(argc > 3){
        t = atoi(argv[3]);
    }

    //Memo<pair<int, int>, long,
    //    ListHashTable<pair<int, int>, long>> tpMemoised (pascal, t);

    Memo<pair<int, int>, long> tpMemoised (pascal, t);

    Memo<pair<int, int>, long,
        BucketHashTable<pair<int, int>, long,
        ListBucket<pair<int, int>, long>, 5>> tpCached (pascal, t);

    pair<int, int> args = make_pair(n, k);

    chrono::steady_clock::time_point start;
    chrono::steady_clock::time_point end;

    /*start = chrono::steady_clock::now();
    long res1 = tpMemoised(args);
    end = chrono::steady_clock::now();

    cout << n << " " << k << " " << t << " " << res1 << " " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << endl;
    */
    start = chrono::steady_clock::now();
    long res2 = tpCached(args);
    end = chrono::steady_clock::now();

    cout << n << " " << k << " " << t << " " << res2 << " " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;

    return 0;
}
