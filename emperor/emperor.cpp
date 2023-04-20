#include <iostream>
#include <bits/stdc++.h>
using namespace std;
int main() {
    unsigned long long int nOfBottles = 0;
    ifstream inputFile ("input.txt");
    ofstream outputFile;
    outputFile.open("output.txt");

    // reading number of bottles from input.txt
    inputFile >> nOfBottles;

    // power-set of x people gives us 2^x unique, non-repeating, combinations of people (order doesn't matter). We can give unique bottle to each of 2^x combinations
    // and a pair which dies drank poison bottle.
    outputFile << ((int) log2(nOfBottles-1)) + 1 << endl;
    inputFile.close();
    outputFile.close();
    return 0;
}
