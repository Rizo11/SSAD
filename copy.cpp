#include <iostream>

using namespace std;

class Test {
public:
    int data;
    Test(int input) : data(input) {
        cout << "user 1" << endl;
    }

    // user defined copy constructor
    // Test(const Test& t) : data(t.data) {
    //     cout << "user 2" << endl;
    // }

    // compiler generated
    // Test::Test(const Test&) {
    //     cout << "compiler" << endl;
    // }
};


int main() {
    int a = 1;
    Test t = Test(2);
    Test t2 = Test(t);
    cout << t2.data << endl;
    return 0;
}