// Example program
#include "test.hh"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

Dumb::Dumb(vector<int> vec) {
    this->v = vec;
}

vector<int>& Dumb::getV() {
    return this->v;
}

int main()
{
    vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "a.size() = " << a.size() << endl;
    int *f = &a[0];
    int *s = &a[1];
    cout << f << endl;
    cout << s << endl;
    vector<int> b;
    
    std::copy(a.begin(), a.begin() + 2, std::back_inserter(b));
    
    cout << "b.size() = " << b.size() << endl;
    for (int n : b)
        cout << "n = " << n << endl;


    Dumb d(a);

    vector<int> c;

    vector<int> v1 = d.getV();
    for (unsigned int i = 0; i < v1.size(); i++) {
        cout << "v1[" << i << "] at " << &v1[i] << endl;
    }
    vector<int> v2 = d.getV();
    cout << &(v1) << endl;
    cout << &(v2) << endl;
    std::copy(d.getV().begin(), d.getV().begin() + 2, std::back_inserter(c));
    cout << "c.size() = " << c.size() << endl;

}

