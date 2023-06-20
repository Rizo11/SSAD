#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> myMap;
    myMap["key1"] = 1;
    myMap["key2"] = 2;

    std::cout << myMap["key1"] << std::endl; // Output: 1
    std::cout << myMap["key2"] << std::endl; // Output: 2
    std::cout << myMap["key3"] << std::endl; // Output: 0 (default value for int)

    return 0;
}