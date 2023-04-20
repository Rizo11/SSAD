#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;
const double EPS = 1e-9;

int main() {
    int n;
    cin >> n;

    vector<vector<double>> A(n, vector<double>(n));
    vector<double> b(n), x(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }

    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }

    for (int k = 0; k < n; ++k) {
        int pivot_row = k, pivot_col = k;
        double max_val = -numeric_limits<double>::infinity();

        for (int i = k; i < n; ++i) {
            for (int j = k; j < n; ++j) {
                if (abs(A[i][j]) > max_val) {
                    max_val = abs(A[i][j]);
                    pivot_row = i;
                    pivot_col = j;
                }
            }
        }

        if (abs(A[pivot_row][pivot_col]) < EPS) {
            cout << "NO" << endl;
            return 0;
        }

        swap(A[k], A[pivot_row]);
        swap(b[k], b[pivot_row]);
        swap(p[k], p[pivot_col]);

        for (int i = k + 1; i < n; ++i) {
            double factor = A[i][k] / A[k][k];
            for (int j = k; j < n; ++j) {
                A[i][j] -= A[k][j] * factor;
            }
            b[i] -= b[k] * factor;
        }
    }

    for (int i = n - 1; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++j) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }

    for (int i = 0; i < n; ++i) {
        if (abs(A[i][i]) < EPS && abs(b[i]) > EPS) {
            cout << "NO" << endl;
            return 0;
        }
    }

    bool infinite_solutions = false;
    for (int i = 0; i < n; ++i) {
        if (abs(A[i][i]) < EPS && abs(b[i]) < EPS) {
            infinite_solutions = true;
            break;
        }
    }

    if (infinite_solutions) {
        cout << "INF" << endl;
    } else {
        for (int i = 0; i < n; ++i) {
            cout << "x[" << p[i] << "] = " << x[i] << endl;
        }
    }

    return 0;
}