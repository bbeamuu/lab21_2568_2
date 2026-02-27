#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Please input numbers to find average." << std::endl;
        return 0;
    }

    std::vector<double> numbers;
    for (int i = 1; i < argc; ++i) {
        std::istringstream iss(argv[i]);
        double num;
        if (iss >> num) {
            numbers.push_back(num);
        }
    }

    double sum = 0;
    for (const auto& num : numbers) {
        sum += num;
    }

    double average = sum / numbers.size();
    std::cout << "---------------------------------" << std::endl;
    std::cout << "Average of " << numbers.size() << " numbers = " << std::fixed << std::setprecision(0) <<average << std::endl;
    std::cout << "---------------------------------" << std::endl;

    return 0;
}

