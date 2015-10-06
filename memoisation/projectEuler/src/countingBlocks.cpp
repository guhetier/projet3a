#include "../../Cpp/src/fixedPoint.hpp"

using namespace std;

int main(int argc, char const *argv[]) {
    //On coupe le problème. Une solution commence :
    //    - soit par 1 noir
    //    - soit par k>=3 rouges puis un noir puis une solution du problème pour
    //      n' = n-k-1
    //    - soit par n rouges
    Memo<int, int64_t> blockCount(
        [](function<int64_t(int)> f, int n){
        if(n < 3)
            return (int64_t)1;

        int64_t res = f(n-1); //Débute par un block noir
        for(int i = 4; i<=n; i++){
            res += f(n-i); //La solution qui débute par i-1 rouges puis un noir
        }

        return ++res; //La solution entièrement rouge
    });

    std::cout << (int64_t)blockCount.apply(50) << std::endl;

    return 0;
}
