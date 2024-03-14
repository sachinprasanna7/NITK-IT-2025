#include <iostream>

using namespace std;

int solve(int a, int b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return a + solve(a, b - 1);
}

int main() {
    int num1, num2;

    cout << "Enter the first positive integer: ";
    cin >> num1;

    cout << "Enter the second positive integer: ";
    cin >> num2;

    if (num1 <= 0 || num2 <= 0) {
        std::cout << "Please enter positive integers only." << endl;
        return 1;
    }

    int result = solve(num1, num2);
    cout << "The product of " << num1 << " and " << num2 << " is: " << result << endl;
    return 0;
}
