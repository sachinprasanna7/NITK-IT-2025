#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <random>

using namespace std;
using namespace chrono;

// Insertion sort
void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

// Selection sort
void selectionSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        int mini = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[mini]) {
                mini = j;
            }
        }
        swap(arr[i], arr[mini]);
    }
}

// Bubble sort
void bubbleSort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

// Merge sort
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> leftArr(n1);
    vector<int> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = arr[left+i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = arr[mid+1+j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i++];
        } 
        
        else {
            arr[k] = rightArr[j++];
        }
        k++;
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] = rightArr[j++];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

// Quick sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i+1], arr[high]);
    return i+1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Function to generate random vector of given size
vector<int> generateRandomVector(int size) {
    
    vector<int> vec;

    // Seed for random number generation
    std::random_device rd;
    std::mt19937 gen(rd());

    // Parameters for getting data from normal distribution 
    double mean = 50000.0;
    double stddev = 20000.0;

    // Normal distribution
    normal_distribution<double> distribution(mean, stddev);

    for (int i = 0; i < size; ++i) {
        // Sampling from the normal distribution and push back to the vector
        vec.push_back(static_cast<int>(distribution(gen)));
    }

    return vec;
}

int main() {

    vector<int> sizes = {10000, 20000, 30000, 40000, 50000};

    vector <vector <int>> data(5, vector<int>(5));

    ofstream myfile;
    myfile.open("results.dat");

    myfile << "Size,Selection,Insertion,Bubble,Merge,Quick" << endl;

    int i = 0;
    // Looping through sorting algorithms
    for (const auto& size : sizes) {
        vector<int> arr1 = generateRandomVector(size);
        vector<int> arr2 = arr1;
        vector<int> arr3 = arr1;
        vector<int> arr4 = arr1;
        vector<int> arr5 = arr1;

        cout << "Input size: " << size << endl;

        // Measuring and plot insertion sort
        auto start = high_resolution_clock::now();
        insertionSort(arr1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        cout << "Insertion sort: " << duration.count() << " ms" << endl;
        data[i][0] = duration.count();


        // Measuring and plot selection sort
        start = high_resolution_clock::now();
        selectionSort(arr2);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        cout << "Selection sort: " << duration.count() << " ms" << endl;
        data[i][1] = duration.count();

        // Measuring and plot bubble sort
        start = high_resolution_clock::now();
        bubbleSort(arr3);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        cout << "Bubble sort: " << duration.count() << " ms" << endl;
        data[i][2] = duration.count();


        // Measuring and plot merge sort
        start = high_resolution_clock::now();
        mergeSort(arr4, 0, arr4.size() - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        cout << "Merge sort: " << duration.count() << " ms" << endl;
        data[i][3] = duration.count();


        // Measuring and plot quick sort
        start = high_resolution_clock::now();
        quickSort(arr5, 0, arr5.size() - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<milliseconds>(stop - start);

        cout << "Quick sort: " << duration.count() << " ms" << endl;
        data[i][4] = duration.count();

        myfile << size << " " << data[i][0] << " " << data[i][1] << " " << data[i][2]
                   << " " << data[i][3] << " " << data[i][4] << std::endl;

        cout<<endl<<endl;

    }

    myfile.close();

    return 0;

}
