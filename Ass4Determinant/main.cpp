// Mukhammadrizo Maribjonov m.maribjonov@innopolis DS-AI 4

#include <bits/stdc++.h>
using namespace std;

/* representation of mathematical object 2D matrix in C++ class */
class Matrix {
public:
    // array stores 2D matrix
    vector<vector<double>> array = vector<vector<double>>();
    int rows = 0;
    int columns = 0;

    /* returns the size of the row */
    int getRows() const {
        return rows;
    }

    /* returns the size of the columns */
    int getColumns() const {
        return columns;
    }

    /* constructor */
    Matrix(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;

        // initialize matrix with zeros
        this->array = vector<vector<double>>(rows, vector<double> (columns, 0));
    }

    Matrix() {}

    /* returns current matrix with values of matrix B */
    Matrix* operator=(Matrix B) {
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                this->array[i][j] = B(i, j);
            }
        }

        return this;
    }

    /* overloading () for putting value to matrix at given row, column */
    void operator()(int row, int column, double value) {
        array[row][column] = value;
    }

    /* indexing matrix at row, col*/
    double & operator()(int row, int column) {
        return array[row][column];
    }

    /* returns product of current matrix and matrix B */
    Matrix operator*(Matrix B) {
        Matrix result = Matrix(this->rows, B.columns);

        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < B.columns; ++j) {
                double product = 0;
                for (int k = 0; k < this->columns; ++k) {
                    double ths = this->array[i][k];
                    double b = B(k, j);
                    product += ths*b;
                }
                result(i, j, product);
            }
        }

        return result;
    }

    /* prints one line of Matrix m */
    void printLine(int line) {

        for (int j = 0; j < this->columns; ++j) {

            // if printing last line
            if (j == this->columns-1) {
                if(abs(this->array[line][j])<0.0001)
                    cout << "0.00";
                else {
                    printf("%.2f", this->array[line][j]);
                }
            } else {
                if(abs(this->array[line][j])<0.0001)
                    cout << "0.00 ";
                else {
                    printf("%.2f ", this->array[line][j]);
                }
            }
        }
    }

    /* prints one line of Matrix m */
    void printM() {
        for (int j = 0; j < this->columns; ++j) {
            this->printLine(j);
            cout << endl;
        }
    }

    /* returns identity matrix with n columns/rows */
    Matrix makeIdentity(int n) {
        Matrix I = Matrix(n, n);
        for (int i = 0; i < n; ++i) {
            I(i, i) = 1;
        }

        return I;
    }

    /* Calculates Permutation matrix to move exchange row i with j */
    Matrix CalculatePij(int i, int j) {
        Matrix p = this->makeIdentity(this->getRows());

        for (int k = 0; k < p.getColumns(); ++k) {
            double tmp = p(i, k);
            p(i, k, p(j, k));
            p(j, k, tmp);
        }

        return p;
    }

    /* calculates elimination matrix to eliminate value at [row][col] */
    Matrix calculateERowCol( int row, int column, double factor) {
        int n = this->getRows();
        Matrix E(n, n);
        double pivot = this->array[row][column] / this->array[column][column];
        E = this->makeIdentity(this->getRows());

        E(row,column, -pivot);

        return E;
    }
};

/* extension of Matrix class with addition of findInverse function, which solves AA^(-1) = I */
class MatrixDeterminant : public Matrix{
public:

    MatrixDeterminant() : Matrix(){
    }
    MatrixDeterminant(int rows, int cols) : Matrix(rows, cols){
    }

    /* returns determinant of matrix A */
    double determinant(Matrix A) {
        double det = 1.0;
        size_t step = 1;
        int n = this->getRows();
        for (int k = 0; k < n-1; k++) {
            int r = k;
            double max_value = abs(A(k,k));

            // find maximum value in column k
            for (int i = k+1; i < n; i++) {
                if (abs(A(i,k)) > max_value) {
                    max_value = abs(A(i,k));
                    r = i;
                }
            }

            if (max_value == 0.0) {
                return 0.0;
            }

            if (r != k) {

                // swap rows r, k of A
                Matrix Prk = this->CalculatePij(r, k);
                A = Prk*A;


                cout << "step: " << "permutation" << endl;
                A.printM();
                det *= -1.0;
            }

            // elimination
            for (int i = k+1; i < n; i++) {
                double factor = A(i,k) / A(k,k);

                Matrix Eik = A.calculateERowCol( i, k, factor);
                A = Eik*A;
                A(i,k) = 0.0;

                cout << "step: " << "elimination" << endl;
                A.printM();
            }
            det *= A(k,k);
        }

        det *= A(n-1,n-1);

        // print determinant
        cout << "result:" << endl;
        cout << fixed << setprecision(2) << det << endl;

        return det;
    }

};

int main() {

    int rows = 0;
    int input = 0;

    cout << "Input the dimensions of a matrix:" << endl;
    cin >> rows;

    MatrixDeterminant A = MatrixDeterminant(rows, rows);

    cout << "n: Input n*n elements of a matrix:" << endl;

    // read matrix A
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            cin >> input;
            A(i, j, input);
        }
    }


    A.determinant(A);

    return 0;
}