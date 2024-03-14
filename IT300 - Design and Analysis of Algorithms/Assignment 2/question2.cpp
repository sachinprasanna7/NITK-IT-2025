#include <iostream>
#include <vector>

using namespace std;

int countSplitInversions(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int splitInv = 0;

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            // If the element in the right subarray is smaller, it forms inversions with all remaining elements in the left subarray
            arr[k++] = R[j++];
            splitInv += (mid - left + 1 - i);
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }

    return splitInv;
}

int mergeSortAndCount(vector<int>& arr, int left, int right) {
    int answer = 0;
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Counting inversions in the left and right subarrays
        int leftInv = mergeSortAndCount(arr, left, mid);
        int rightInv = mergeSortAndCount(arr, mid + 1, right);

        // Merging the sorted halves and counting inversions in the merge step
        int splitInv = countSplitInversions(arr, left, mid, right);

        answer = leftInv + rightInv + splitInv;
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

    vector <int> temp = arr;

    // Counting inversions and printing the result
    int inversions = mergeSortAndCount(arr, 0, n - 1);

    cout << "Number of inversions: " << inversions << "\n";

    // Printing the inversions
    cout << "Inversions: ";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (temp[i] > temp[j]) {
                cout << "(" << temp[i] << ", " << temp[j] << ") ";
            }
        }
    }

    return 0;
}
