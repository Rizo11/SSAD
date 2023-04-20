#include <iostream>
#include <vector>
#include <math.h>

#include <iostream>
#include <iomanip>
#include <complex>
#include <cmath>

using namespace std;

using namespace std::complex_literals;

int fib(int n) {
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return 1;
    } else {
        return fib(--n) + fib(--n);
    }
}

int findEl(vector<int> a, int value, int begin, int end) {
    if (begin > end) {
        return -1;
    }
    if (a[(end+begin)/2] == value) {
        return (end+begin)/2;
    } else if (a[(end+begin)/2] > value) {
        return findEl(a, value, begin, (end+begin)/2);
    } else {
        return findEl(a, value, (end+begin)/2, end);
    }
}

class Rect {
public:
    int L, W, H;
};

class Cube {
public:
    int a;
};

class Sphere {
public:
    int a;
};

class Cone {
public:
    int r, h;
};

class Volume {
public:
    double volume (Cube a) {
        return pow(a.a, 3);
    }

    double cilinder(Rect a) {
        return a.H * a.L * a.W;
    }

    double volume (Sphere a) {
        return 4 * 3.14 * pow(a.a, 3)/3;
    }

    double volume (Cone a) {
        return 3.14 * pow(a.r, 2) * a.h/3;
    }
};

complex<int> add(complex<int> a, complex<int> b) {
    return a + b;
}

complex<int> sub(complex<int> a, complex<int> b) {
    return a - b;
}

void f (complex<int> (*add)(complex<int> a, complex<int> b), complex<int> (*sub)(complex<int> a, complex<int> b)) {
    cout << *(add) << endl;

    cout << *(sub) << endl;
}

int main() {
    complex<int> a, b;
    a = 1;
    b = 2;

    complex<int> (*add)(complex<int>, complex<int>);
    complex<int> (*sub)(complex<int>, complex<int>);

    f(add, sub);

    return 0;
}
