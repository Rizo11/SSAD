#include <iostream>

using namespace std;

class C {
public:
    int a;
    C() {a = 0;}
    C(int input) : a(input) {
        cout << "ctor" << endl;
    }

    ~C() {
        cout << "destructed\n";
    }
};
// returns rvalue
int getRValue() {
    return 10;
}

int& getLValue() {
    int value = 10;
    static C test = C(value);
    test.a++;
    return test.a;
}

int& get(int& i) {
    cout << "i: " << i << endl;
    return i;
}

char& g(char& i) {
    cout << "char: " << i << endl;
    return i;
}

void fun(int& t) {
    t = 10;
}

class Widget {
public:
  Widget(Widget&& rhs) noexcept {
    cout << "Copy?" << endl;
  };    // rhs is an lvalue, though it has an rvalue reference type

  Widget() {
    cout << "Default" << endl;
  }
};

void someFunc(Widget&& w) {

}

int main() {

    // usually lvalue is a thing to the left of =
    // usually rvalue is a thing to the right of =
    int i = 10;
    i = getRValue();
    i = getLValue();
    cout << i << endl;  
    i = getLValue();
    i = getLValue();
    getLValue() += getLValue();
    cout << getLValue() << endl;
    i = getLValue();
    cout << i << endl;

    i = 10;
    get(i) = 1;
    cout << "i: " << i << endl;

    char&& ch1 = 'a';
    g(ch1) = 'b';
    // cout << "ch: " << ch << endl;
    char ch = 'a';
    if constexpr (is_lvalue_reference<decltype(('a'))>::value) {
        cout << "expression is lvalue\n";
    }
    if constexpr (is_rvalue_reference<decltype(('a'))>::value) {
        cout << "expression is xvalue\n";
    }
    if constexpr (is_rvalue_reference<decltype(('a'))>::value) {
        cout << "expression is prvalue\n";
    }


    Widget wid = Widget();
    Widget w = wid;                     // wid is some Widget

    // someFunc(wid);                  // in this call to someFunc,
                                    // w is a copy of wid that's
                                    // created via copy construction

    // someFunc(std::move(wid)); 




    return 0;
}