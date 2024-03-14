#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

int maxSubArraySumBruteforce(vector<int>& arr) {
    int n = arr.size();
    int answer = INT_MIN;

    for (int i = 0; i < n; i++) {
        int currentSum = 0;
        for (int j = i; j < n; j++) {
            currentSum += arr[j];
            answer = max(answer, currentSum);
        }
    }

    return answer;
}

int maxCrossingSum(vector<int>& arr, int low, int mid, int high) {
    int leftSum = INT_MIN, rightSum = INT_MIN;

    int sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        leftSum = max(leftSum, sum);
    }

    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += arr[i];
        rightSum = max(rightSum, sum);
    }

    return leftSum + rightSum;
}

int maxSubArraySumDivideConquer(vector<int>& arr, int low, int high) {
    if (low == high) {
        return arr[low];
    }

    int mid = low + (high - low) / 2;

    int leftSum = maxSubArraySumDivideConquer(arr, low, mid);
    int rightSum = maxSubArraySumDivideConquer(arr, mid + 1, high);
    int crossSum = maxCrossingSum(arr, low, mid, high);

    return max({leftSum, rightSum, crossSum});
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

    int result1 = maxSubArraySumBruteforce(arr);
    int result2 = maxSubArraySumDivideConquer(arr, 0, arr.size() - 1);

    cout << "Maximum subarray sum using Brute Force: " << result1 << endl;
    cout << "Maximum subarray sum using Divide and Conquer: " << result2 << endl;
    
    return 0;
}
