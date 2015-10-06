#include "../../Cpp/src/fixedPoint.hpp"

using namespace std;

int main(int argc, char const *argv[]) {

    Memo<int, int64_t> tilesCount(
        [](function<int64_t(int)> f, int n){
            const int r = 2;
            const int g = 3;
            const int b = 4;

            if(n < 0)
                return (long)0;
            if(n < r)
                return (long)1;

            //Débute par un block noir + débute par un block de couleur
            return f(n-1) + f(n-r) + f(n-g) + f(n-b);
        });

    int n = 50;
    std::cout << tilesCount.apply(n) << std::endl;

    return 0;
}
