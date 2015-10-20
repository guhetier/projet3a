#include "../../Cpp/src/fixedPoint.hpp"
#include <functional>
#include <vector>
using namespace std;

int main(int argc, char const *argv[]) {
    int n = 50;

    Memo<pair<int,int>, long> tilesCount(
        [](function<long(pair<int, int>)> f, pair<int, int> t){
            int s = get<0>(t);
            int n = get<1>(t);

            if(n < s)
                return (long)1;
            if(n==s)
                return (long)2;

            //Débute par un block noir + débute par un block de couleur
            return f({s,n-1}) + f({s,n-s});
        });

    long res = tilesCount(make_pair(1,n));
    res += tilesCount(make_pair(2,n));
    res += tilesCount(make_pair(3,n));
    std::cout << res-3 << std::endl;

    return 0;
}
