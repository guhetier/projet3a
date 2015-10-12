#include "../../Cpp/src/fixedPoint.hpp"
#include <functional>
#include <vector>
using namespace std;

struct MyHash {
    size_t operator()(vector<int> t){
        hash<int> h;
        return h(t[0]) ^ h(t[1]);
    }
};

struct MyEq {
    bool operator()(vector<int> t, vector<int> q){
        return t[0]==q[0] && t[1] == q[1];
    }
};

int main(int argc, char const *argv[]) {
    int n = 50;

    Memo<vector<int>, long> tilesCount(
        [](function<long(vector<int>)> f, vector<int> t){
            int s = t[0];
            int n = t[1];

            if(n < s)
                return (long)1;
            if(n==s)
                return (long)2;

            //Débute par un block noir + débute par un block de couleur
            return f({s,n-1}) + f({s,n-s});
        },
    MyHash(), MyEq());


    //unordered_map<int, tuple<int,int>> t(MyHash, MyEq);
    // long res = tilesCount(make_pair(1,n));
    // res += tilesCount(make_pair(2,n));
    // res += tilesCount(make_pair(3,n));
    // std::cout << res-3 << std::endl;

    return 0;
}
