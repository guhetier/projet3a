#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

struct Memoise {
    unordered_map<int, int> table;
    function<list<int>(int)> next;
    function<int(list<int>, int)> action;

    Memoise (const unordered_map<int,int>& init,
        const function<list<int>(int)> &next, const function<int(list<int>, int)> &action)
        :table(init){
            this->next = next;
            this->action = action;
    }

    int fMem (int n){
        try{
            return table.at(n);;
        }
        catch(const out_of_range& e){
            list<int> needed = next(n);
            list<int> result;
            for(int i: needed)
                result.push_back(fMem(i));

            return (table[n] = action(result, n));
        }
    }

    const unordered_map<int, int>& getTable() const {
        return table;
    }

};

int main(){
    Memoise fibo({{0,1},{1,1}},
        [](int n)->list<int>{ return {n-1, n-2};},
        [](list<int> l, int n)->int { int r = 0; for(int i : l) r += i; return r;});

    cout << "Fibonacci 5 : " << fibo.fMem(5) << endl;

    vector<int> tab({1, 2, 5, -4, 3});
    Memoise subSum({{0,tab[0]}},
        [](int n)->list<int>{ list<int> l; for(int i=0; i<n; l.push_back(i++))
            ; return l;},
        [tab](list<int> l, int n)->int{ return tab[n] >= 0 ? l.back() + tab[n] : tab[n];});

    subSum.fMem(4);
    int m = 0;
    for(auto i : subSum.getTable()){
        if(i.second > m)
            m = i.second;
    }
    std::cout << "Plus grand sous tableau : " << m << std::endl;

    return 0;
}
