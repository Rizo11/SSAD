// Mukhammadrizo Maribjonov m.maribjonov@innopolis DS-AI 4

#include <bits/stdc++.h>
using namespace std;

/* representation of mathematical object 2D matrix in C++ class */
class Matrix {
public:
    // array stores 2D matrix
    vector<vector<int>> array = vector<vector<int>>();
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


    /* returns true if current matrix and B have the equal rows, columns */
    bool checkDimensionAdditionSubtraction(Matrix B) {

        if (B.rows == this->rows && B.columns == this->columns) {
            return true;
        }

        return false;
    }

    /* returns true if current matrix's columns equal to matrix B's rows */
    bool checkDimensionMultiplication(Matrix B) {
        if (B.columns == this->rows) {
            return true;
        }

        return false;
    }

    /* constructor */
    Matrix(int rows, int columns) {
        this->rows = rows;
        this->columns = columns;

        // initialize matrix with zeros
        this->array = vector<vector<int>>(rows, vector<int> (columns, 0));
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
    int& operator()(int row, int column) {
        return array[row][column];
    }

    /* returns difference between current matrix and matrix B */
    Matrix operator-(Matrix B) {
        Matrix result = Matrix(this->rows, this->columns);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                result(i, j, this->array[i][j] - B.array[i][j] );
            }
        }

        return result;
    }

    /* returns sum of current matrix and matrix B */
    Matrix operator+(Matrix B) {
        Matrix result = Matrix(this->rows, this->columns);
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                result(i, j, B(i, j) + this->array[i][j]);
            }
        }

        return result;
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

    /* returns transpose of current matrix */
    Matrix T () {
        Matrix AT = Matrix(columns, rows);
        for (int i = 0; i < this->columns; ++i) {
            for (int j = 0; j < this->rows; ++j) {
                AT(i, j, this->array[j][i]);
            }
        }

        return AT;
    }

    /* prints one line of Matrix m */
    void printLine(int line) {

        for (int j = 0; j < this->columns; ++j) {
            if(abs(this->array[line][j])<0.0001)
                cout << "0 ";
            else {
                printf("%d ", this->array[line][j]);
            }
        }
    }

    /* prints values of matrix A and I */
    void printM(Matrix I) {
        for (int i = 0; i < this->getRows(); ++i) {
            this->printLine(i);
            I.printLine( i);
            cout << endl;
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

    /* Diagonal normalization for squared matrix and Identity*/
    void diagonalNormalize(Matrix& b) {
        for (int i = 0; i < this->getRows(); ++i) {
            double factor = 1/ this->array[i][i];
            this->array[i][i] = 1;
            for (int j = 0; j < b.getColumns(); ++j) {
                b(i,j)  *= factor;
            }
        }
    }

    /* calculates elimination matrix to eliminate value at [row][col] */
    Matrix calculateERowCol( int row, int column) {
        int n = this->getRows();
        Matrix E(n, n);
        double pivot = this->array[row][column] / this->array[column][column];
        E = this->makeIdentity(this->getRows());

        E(row,column, -pivot);

        return E;
    }
};

/* extension of Matrix class with addition of findInverse function, which solves AA^(-1) = I */
class MatrixEliminationPermutation : public Matrix{
public:

    MatrixEliminationPermutation() : Matrix(){
    }
    MatrixEliminationPermutation(int rows, int cols) : Matrix(rows, cols){
    }

    /* returns determinant of matrix A*/
    void task3(Matrix A) {
        double det = 1.0;
        size_t step = 1;
        int n = this->getRows();

        // print 3x3 Indentity
        Matrix I = this->makeIdentity(3);
        I.printM();

        // E 21 for A
        Matrix E21 = A.calculateERowCol(1, 0);
        E21.printM();

        // print E21 * A
        (E21*A).printM();

        // P 21 for A
        Matrix P21 = A.CalculatePij(1, 0);
        P21.printM();


        // print P21 * A
        (P21*A).printM();
    }

};

int main() {
    
    int rows = 0, columns = 0;
    int input = 0;


    cin >> rows;
    columns = rows;

    MatrixEliminationPermutation A = MatrixEliminationPermutation(rows, rows);
    
    // read matrix A
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            cin >> input;
            A(i, j, input);
        }
    }


    A.task3(A);

    return 0;
}