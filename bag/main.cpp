// Mukhammadrizo Maribjonov DS-AI 4

#include <bits/stdc++.h>
using namespace std;

class CellInfo {
public:

    // char, amount
    pair<char, size_t> cell;

    CellInfo(char c, size_t amount) {
        cell.first = c;
        cell.second = amount;
    };

    CellInfo() {}
};

class Bag {
public:
    // vector of cells
    vector<CellInfo> cells;

    // for memoization inserted chars
    vector<bool> elements;
    Bag() {
        for (int i = 0; i < 26; ++i) {
            elements.push_back(0);
        }

        cells = vector<CellInfo>(26);
    }


    void Insert(char val, size_t n) {
        // new element
        if (!elements[val-97]) {
            cells[val-97] = CellInfo(val, n);
            elements[val-97] = 1;
        }
        // existing element
        else {
            cells[val-97].cell.second += n;
        }
    }

    void Remove(char val, size_t n) {
        // if less elements should be removed than existing elements
        if (cells[val-97].cell.second > n) {
            cells[val-97].cell.second -= n;
        }

        // more elements should be removed that existing elements
        else {
            cells[val-97].cell.second = 0;
            elements[val-97] = false;
        }
    }

    // find min char, 0 if bag is empty
    char min() {
        for (int i = 0; i < 26; i++) {
            if (elements[i]) {
                return (char) (i + 97);
            }
        }

        return 0;
    }

    // find max char, 0 if bag is empty
    char max() {
        for (int i = 25; i >= 0; i--) {
            if (elements[i]) {
                return (char) (i + 97);
            }
        }

        return 0;
    }

    // compare current and bag b by each char and amount of each char
    bool isEqual(Bag b) {

        // different amount of elements in each bag
        if (this->max() != b.max()) {
            return false;
        }

        for (int i = 0; i <= b.max()-97; ++i) {
            // i+97 th char exists only in one bag
            if (this->elements[i] != b.elements[i]) {
                return false;
            }

            CellInfo ths = this->cells[i];
            CellInfo bs = b.cells[i];

            // i+97 th chars frequency is different in 2 bags
            if (ths.cell.second != bs.cell.second) {
                return false;
            }
        }

        return true;
    }
};


int main() {
    Bag a = Bag();
    Bag b = Bag();

    int n = 0;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        char opType, inputCh;
        size_t bagN, amount;
        cin >> opType >> bagN >> inputCh >> amount;

        // insert
        if (opType == 'i') {
            // first bag insert
            if (bagN == 1) {
                a.Insert(inputCh, amount);
            }
            // second bag insert
            else {
                b.Insert(inputCh, amount);
            }
        }

        // remove
        else if (opType == 'r') {
            // remove from 1st bag
            if (bagN == 1) {
                a.Remove(inputCh, amount);
            }
            // remove from 2nd bag
            else {
                b.Remove(inputCh, amount);
            }
        }
    }

    // print max of 1st bag
    if (a.max()) {
        cout << a.max() << " ";
    } else {
        cout << -1 << " ";
    }

    // print min of 2nd bag
    if (b.min()) {
        cout << b.min() << " ";
    } else {
        cout << -1 << " ";
    }

    // check for equality of 2 bags
    cout << a.isEqual(b) << endl;
    return 0;
}
