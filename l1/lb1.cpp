#include <iostream>

using namespace std;
void t1() {
    int first_num, second_num;

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (auto& elem : arr) {
        cout << elem * elem << " ";
    }
}

void bi() {
    double x = -3;
    cout << "x    | y" << endl;
    while (x <= 3) {
        printf("%.1f | %.1f\n", x, (-3*x*x-4*x-6.5));
        x += 0.5;
    }
}
int main() {
    
    string str;
    cin >> str;
    int j = str.size()/2;
    for (size_t i = 0; i < j; i++)
    {
        cout << str[i-str.size()] << endl;
        if (str[i] != str[i-str.size()]) {
            cout << "No\n";
            return 0;
        }
    }

    cout << "Yes\n";
    
    
}