// Mukhammadrizo Maribjonov DS-AI 4

#include <bits/stdc++.h>
using namespace std;


/* represents a column vector of matrix*/
class ColumnVector {
public:
    vector<double> column;
    size_t nOfColumns_;
    ColumnVector() {}

    ColumnVector(vector<double> input, size_t nOfColumns) {
        this->column = input;
        this->nOfColumns_ = nOfColumns;
    }

    ColumnVector(size_t nOfColumns) {
        this->column = vector<double>(nOfColumns, 0);
        this->nOfColumns_ = nOfColumns;
    }

    void set(size_t index, double value) {
        this->column[index] = value;
    }

    double& operator[] (size_t index) {
        return column[index];
    }
};

// represent matrix object in c++
class Matrix {
public:
    vector<ColumnVector> columns_;
    size_t mOfRows;
    size_t nOfColumns;

    Matrix() {}

    Matrix(ColumnVector inputMatrix, size_t colSize, size_t rowSize) {
        this->columns_.push_back(inputMatrix);
        this->nOfColumns = colSize;
        this->mOfRows = rowSize;
    }

    Matrix(vector<ColumnVector> inputMatrix, size_t colSize, size_t rowSize) {
        this->columns_ = inputMatrix;
        this->nOfColumns = colSize;
        this->mOfRows = rowSize;
    }

    // used for indexing
    double& operator() (size_t row, size_t column) {
        return columns_[column][row];
    }
};

/* Solves Ax = b. b will be replaced by x. A becomes A inverse */
void gaussj(Matrix &a, Matrix &b) {
    int i, icol, irow, j, k, l, ll, n = a.mOfRows, m = b.nOfColumns;
    double big, dum, pivinv;

    // to track pivoting
    vector<int> indxc(n), indxr(n), ipiv(n);

    for (j=0;j<n;j++) ipiv[j]=0;

    // main loop over the columns to be reduced
    for (i=0;i<n;i++) {
        big=0.0;
        // search for a pivot
        for (j=0;j<n;j++)
            if (ipiv[j] != 1)
                for (k=0;k<n;k++) {
                    if (ipiv[k] == 0) {
                        double element = abs(a(j, k));
                        if (element >= big) {
                            big=element;
                            irow=j;
                            icol=k;
                        }
                    }
                }

        ++(ipiv[icol]);

        // interchange rows, if needed, to put the pivot
        //element on the diagonal

        if (irow != icol) {
            for (l=0;l<n;l++) swap(a(irow, l), a(icol, l));
            swap(b(irow, 0),b(icol, 0));
        }
        indxr[i]=irow;
        indxc[i]=icol;
        // divide the pivot row by the
        //pivot element, located at irow and icol
        if (a(icol, icol) == 0.0) {
            if (100*abs(b(icol, 0)) != 0.0) {
                cout << "NO\n";
                exit (0);
            }
            cout << "INF\n";
            exit (0);
        }

        pivinv=1.0/a(icol, icol);
        a(icol, icol)=1.0;
        for (l=0;l<n;l++) {
            double d = a(icol, l);
            d *= pivinv;
            a(icol, l) *= pivinv;
        }
        b(icol, 0) *= pivinv;

        // reduce rows for pivots
        for (ll=0;ll<n;ll++) {
            if (ll != icol) {
                dum=a(ll, icol);
                a(ll, icol)=0.0;
                for (l=0;l<n;l++) a(ll, l) -= a(icol, l) *dum;
                b(ll, 0) -= b(icol, 0)*dum;
            }
        }

    }

    // reverse order that the permutation
    for (l=n-1;l>=0;l--) {
        if (indxr[l] != indxc[l])
            for (k=0;k<n;k++)
                swap(a(k, indxr[l]),a(k, indxc[l]));
    }
}

int main() {
    int n = 0;
    cin >> n;

    vector<ColumnVector> Av(n, ColumnVector(n));
    ColumnVector bv = ColumnVector(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double d;
            cin >> d;
            Av[j].set(i, d);
        }
    }

    for (int j = 0; j < n; ++j) {
        double d;
        cin >> d;
        bv.set(j, d);
    }

    Matrix A = Matrix(Av, n, n);
    Matrix b = Matrix(bv, 1, n);
    gaussj(A, b);

    for (int i = 0; i < n; ++i) {
        if (abs(b.columns_[0][i]) < 0.01 || b.columns_[0][i] == -0.0) {
            cout << 0.00 << endl;
        } else {
            double val = round(b.columns_[0][i]*100);
            val /= 100;
            cout << fixed<< setprecision(2) << val << endl;
        }
    }

    return 0;
}
