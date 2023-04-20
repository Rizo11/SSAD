#include <iostream>

using namespace std;

void f (const int a) {
    cout << "double&" << endl;
    // a += 3.14;
}



int main() {

    int a, c;
    const int b = 777; // compile-time expression
    a = 5;
    c = 5;
    // b = 5; // Error

    const int x = a + b; // run-time expression
    //x = 5;
    float A[x];
}