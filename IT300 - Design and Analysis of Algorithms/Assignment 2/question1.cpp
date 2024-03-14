#include <iostream>
#include <vector>

using namespace std;

int countInversions(vector<int>& arr) {
    int n = arr.size();
    int answer = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                // If the element at index i is greater than the element at index j, it forms an inversion with all elements to its right
                answer++;
                cout << "(" << arr[i] << ", " << arr[j] << ") ";
            }
        }
    }

    return answer;
}

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter the elements of the array:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Count inversions and print the result
    int inversions = countInversions(arr);

    cout << "\nNumber of inversions: " << inversions << "\n";

    return 0;
}
