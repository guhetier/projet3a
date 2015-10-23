#include "../../Cpp/src/fixedPoint.hpp"

using namespace std;

int m = 50;

int main(int argc, char const *argv[]) {

    long max = 1000000;
    int n = m;

    //On coupe le problème. Une solution commence :
    //    - soit par 1 noir
    //    - soit par k>=3 rouges puis un noir puis une solution du problème pour
    //      n' = n-k-1
    //    - soit par n rouges
    Memo<int, long> blockCount(
        [](function<long(int)> f, int n){
        if(n < m)
            return 1L;

        int64_t res = f(n-1); //Débute par un block noir
        for(int i = m+1; i<=n; i++){
            res += f(n-i); //La solution qui débute par i-1 rouges puis un noir
        }

        return ++res; //La solution entièrement rouge
    });

    //On cherche désormais quand le nombre de solution dépasse max.
    //La solution étant mémoisée, on va brutalement calculer la valeur pour
    //chaque n, ce qui se fera en temps relativement cours à chaque itération
    //(solution des sous problèmes déjà connues)
    //on attends un complexité en O(max^2)

    while(blockCount(n) < max)
        n++;

    std::cout << n << std::endl;

    return 0;
}
