#include <iostream>
#include <fstream>

using namespace  std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    ofstream output;

    output.open("output.txt");
    output << "Hello, World!" << endl;

    return 0;
}
