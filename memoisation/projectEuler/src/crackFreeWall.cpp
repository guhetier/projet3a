#include "../../Cpp/src/fixedPoint.hpp"
#include "../../Cpp/src/hash.hpp"
#include <vector>
#include <tuple>
#include <bitset>
#include <functional>

using namespace std;

/*
On est tenté par une approche par dichotomie.

Ou par une approche linéaire ou on retient les solutions compatibles avec une ligne

On code une ligne sur un entier : si le ieme bit est à 1,
il y a une coupure après le ième bloc
*/

void genLines(int l, int enCours, vector<long>& allLines){
    if(l<2)
        return;
    if(l<4){
        allLines.push_back(enCours);
        return;
    }

    genLines(l-2, enCours | 1<<(l-2), allLines);
    genLines(l-3, enCours | 1<<(l-3), allLines);
}

vector<long> allLines;

int main(int argc, char const *argv[]) {

    int n = 10, l = 32;


    genLines(l, 0, allLines);
    cout << bitset<32>(allLines[8]) << endl;

    auto frec = [](function<int(pair<int, int>)> f, pair<int, int> a){
        int l = get<0>(a);
        int h = get<1>(a);

        if(h == 1)
            return 1;

        int sum = 0;
        for(auto i = allLines.begin(); i != allLines.end(); i++){
            if((l & *i) == 0){
                sum += f(make_pair(*i, h-1));
            }
        }
        return sum;
    };

    Memo<pair<int,int>, int> wall(frec);

    cout << wall(make_pair(0, n+1)) << endl;

    return 0;
}
