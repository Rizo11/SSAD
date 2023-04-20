#include <iostream>

using namespace std;


class C {
    
public:
    int a;

    // default constructor
    C() { a = 0; }

    // copy constructor
    C(const C&c) {
        cout << "Copy contructor was called" << endl;
        a = c.a;
    }

    C(int i) {
        a = i;
    }

};

void f(C c) {
    
}

int main() {

    C a = C(4);
    cout << a.a << endl;

    C b = a;
    cout << b.a << endl;
    
    return 0;
}