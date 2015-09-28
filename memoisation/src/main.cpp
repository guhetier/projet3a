#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

struct Memoise {
    unordered_map<int, int> table;
    function<list<int>(int)> next;
    function<int(int,int)> action;

    Memoise (){
        table = {{0,1},{1,1}};
    }

    Memoise (const unordered_map<int,int>& init,
        const function<list<int>(int)> &next, const function<int(int,int)> &action)
        :table(init){
            this->next = next;
            this->action = action;
    }

    int fiboAuto (int n){
        try{
            return table.at(n);;
        }
        catch(const out_of_range& e){
            list<int> needed = next(n);
            int a = fiboAuto(needed.front());
            needed.pop_front();
            int b = fiboAuto(needed.front());

            return (table[n] = action(a,b));
        }
    }

};

int main(){
    Memoise m({{0,1},{1,1}},
        [](int n)->list<int>{ return {n-1, n-2};},
        [](int a, int b)->int { return a+b;});

    cout << "Hello world !" << endl;
    cout << "Fibonacci 5 : " << m.fiboAuto(5) << endl;

    return 0;
}
