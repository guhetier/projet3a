#include "../../Cpp/src/fixedPoint.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    int n = 50;

    Memo<int, int64_t> tilesCount2(
        [](function<int64_t(int)> f, int n){
            int s = 2;

            if(n < s)
                return (long)1;
            if(n==s)
                return (long)2;

            //Débute par un block noir + débute par un block de couleur
            return f(n-1) + f(n-s);
        });
    long res = tilesCount2.apply(n);

    Memo<int, int64_t> tilesCount3(
        [](function<int64_t(int)> f, int n){
            int s = 3;

            if(n < s)
                return (long)1;
            if(n==s)
                return (long)2;

            //Débute par un block noir + débute par un block de couleur
            return f(n-1) + f(n-s);
        });
    res += tilesCount3.apply(n);

    Memo<int, int64_t> tilesCount4(
        [](function<int64_t(int)> f, int n){
            int s = 4;

            if(n < s)
                return (long)1;

            if(n==s)
                return (long)2;

            //Débute par un block noir + débute par un block de couleur
            return f(n-1) + f(n-s);
        });
    res += tilesCount4.apply(n);
    std::cout << res-3 << std::endl;

    return 0;
}
