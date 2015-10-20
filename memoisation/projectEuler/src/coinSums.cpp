#include <iostream>
#include <queue>

using namespace std;

int monaie(int val, queue<int> coins){
    int c = coins.front();
    coins.pop();

    if(c == 1 || val == 0)
        return 1;

    int n = 0;
    int sum = 0;
    while(c*n <= val){
        sum += monaie(val - c*n, coins);
        n++;
    }
    return sum;
}

int main(int argc, char const *argv[]) {

    cout << monaie(200, queue<int>({200,100,50, 20, 10, 5, 2, 1})) << endl;
    return 0;
}
