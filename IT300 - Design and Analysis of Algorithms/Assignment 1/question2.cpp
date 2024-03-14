#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>  

using namespace std;

int karatsubaMultiply(int x, int y) {
    
    if (x < 10 || y < 10) {
        return x * y;
    }

    int size = max(static_cast<int>(log10(x)), static_cast<int>(log10(y))) + 1;
    int half_size = static_cast<int>(std::ceil(size / 2.0));

    int a = x / static_cast<int>(pow(10, half_size));
    int b = x % static_cast<int>(pow(10, half_size));
    int c = y / static_cast<int>(pow(10, half_size));
    int d = y % static_cast<int>(pow(10, half_size));

    // Recursion
    int ac = karatsubaMultiply(a, c);
    int bd = karatsubaMultiply(b, d);
    int ad_bc = karatsubaMultiply(a + b, c + d) - ac - bd;

    return static_cast<int>(pow(10, 2 * half_size)) * ac +
           static_cast<int>(pow(10, half_size)) * ad_bc + bd;
}

int solve(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return a + solve(a, b - 1);
}

int main() {
    int num1, num2;

    cout << "Enter the first integer: ";
    cin >> num1;

    cout << "Enter the second integer: ";
    cin >> num2;

    auto start = chrono::high_resolution_clock::now();
    int result = karatsubaMultiply(num1, num2);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;

    cout << "\nResult using Karatsuba's algorithm: " << result << endl;
    cout << "Time taken: " << duration.count() << " seconds" << endl;

    auto start1 = chrono::high_resolution_clock::now();
    int result1 = solve(num1, num2);
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double> duration1 = end1 - start1;

    cout << "\nResult using Recursive algorithm: " << result1 << endl;
    cout << "Time taken: " << duration1.count() << " seconds" << endl;

    return 0;
}
