
#include "fixedPoint.hpp"
#include "functionTry.hpp"
#include <iostream>
#include <chrono>

using namespace std;

int main(int argc, char const *argv[]) {
    auto fibbo = []( function<int(int)> f, int n){
        if(n<2)
            return 1;
        else
            return f(n-1) + f(n-2);
    };

    int n = 30;

    cout << "Begin..." << endl;
    cout << "\nRecursive calculation" << endl;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    int r1 = rec<int, int>(fibbo)(n);

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    std::cout << "\tRecursion took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << "us.\n";

    cout << "\tResult was : " << r1 << endl;

    cout << "\nMemoised calculation" << endl;
    start = chrono::steady_clock::now();

    Memo<int, int> fib(fibbo);
    int r2 = (n);
    //int r2 = memo<int, int>(fibbo)(n);

    end = chrono::steady_clock::now();

    std::cout << "\tMemoisation took "
              << chrono::duration_cast<chrono::microseconds>(end - start).count()
              << "us.\n";

    cout << "\tResult was :" << r2 << endl;

    return 0;
}
