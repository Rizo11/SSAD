#include <iostream>

using namespace std;

class P {
public:
    virtual void F1() {cout << "P1";}
    void F2() {cout << "P2";}
};

class C : public P {
public:
    void F1() {cout << "Ch1";}
    void F2() {cout << "Ch2";}
};

int main() {
    C A;
    P* B = &A;

    double **q;
    double *p;
    double x;
    p = &x;
    q = &p;

    cout << "q  " << *q << endl;
    cout << "x  " << &x << endl;
    cout << "q  " << *(&q ) << endl;
    cout << "x= " << x << endl;
}