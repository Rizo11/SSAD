#include <iostream>

using namespace std;

class C {
public:
    int instance_memebr;
    static int class_memeber;

    C() {
        instance_memebr = 0;
        class_memeber = 5;
    }
};


class A {
public:
    virtual void a() = 0;
    virtual void b() { };
    void c() {
        int k;
    }
    A() {}
};

class B : A {
    
};

int main() {
    C c1 = C();
    cout << c1.instance_memebr << endl;
    // cout << C::class_memeber << endl;
    C c2 = C();
    // c2.class_memeber = 6;
    // printf("%d\n", c2.class_memeber);

    A* a = new A();

    return 0;
}