#include <iostream>
#include <vector>

using namespace std;

struct MinMax {
    int min;
    int max;
};

MinMax solve(vector<int>& arr, int low, int high) {
    MinMax result, left, right;
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    if (high == low + 1) {
        result.min = min(arr[low], arr[high]);
        result.max = max(arr[low], arr[high]);
        return result;
    }

    int mid = (low + high) / 2;
    left = solve(arr, low, mid);
    right = solve(arr, mid + 1, high);

    result.min = min(left.min, right.min);
    result.max = max(left.max, right.max);

    return result;
}

int main() {
    vector<int> arr;

    int n;
    cout<<"Enter the size of the array: ";
    cin>>n;

    cout<<endl;
    for(int i = 0; i < n; i++) {
        int temp;
        cout<<"Enter element "<<i + 1<<": ";
        cin>>temp;
        arr.push_back(temp);
    }

    if (n == 0) {
        cout << "Array is empty." << endl;
        return 1;
    }

    MinMax result = solve(arr, 0, n - 1);

    cout << "\n\nMinimum element: " << result.min << endl;
    cout << "Maximum element: " << result.max << endl<<endl;

    return 0;
}
